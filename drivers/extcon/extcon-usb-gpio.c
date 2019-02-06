/**
 * drivers/extcon/extcon-usb-gpio.c - USB GPIO extcon driver
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com
 * Author: Roger Quadros <rogerq@ti.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/extcon.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/workqueue.h>

#define USB_GPIO_DEBOUNCE_MS	20	/* ms */

struct usb_extcon_info {
	struct device *dev;
	struct extcon_dev *edev;

	struct gpio_desc *id_gpiod;
	struct gpio_desc *vbus_gpiod;
	int id_irq;
	int vbus_irq;
	int level_trigger;
	int trigger_irq;

	unsigned long debounce_jiffies;
	struct delayed_work wq_detcable;
};

static const unsigned int usb_extcon_cable[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

/*
 * "USB" = VBUS and "USB-HOST" = !ID, so we have:
 * Both "USB" and "USB-HOST" can't be set as active at the
 * same time so if "USB-HOST" is active (i.e. ID is 0)  we keep "USB" inactive
 * even if VBUS is on.
 *
 *  State              |    ID   |   VBUS
 * ----------------------------------------
 *  [1] USB            |    H    |    H
 *  [2] none           |    H    |    L
 *  [3] USB-HOST       |    L    |    H
 *  [4] USB-HOST       |    L    |    L
 *
 * In case we have only one of these signals:
 * - VBUS only - we want to distinguish between [1] and [2], so ID is always 1.
 * - ID only - we want to distinguish between [1] and [4], so VBUS = ID.
*/
static void usb_extcon_detect_cable(struct work_struct *work)
{
	int id, vbus;
	unsigned int trigger;
	struct usb_extcon_info *info = container_of(to_delayed_work(work),
						    struct usb_extcon_info,
						    wq_detcable);

	/* check ID and VBUS and update cable state */
	id = info->id_gpiod ?
		gpiod_get_value_cansleep(info->id_gpiod) : 1;
	vbus = info->vbus_gpiod ?
		gpiod_get_value_cansleep(info->vbus_gpiod) : id;

	if (info->level_trigger) {
		if (info->trigger_irq == info->id_irq && info->id_gpiod) {
			trigger = irqd_get_trigger_type(
					irq_get_irq_data(info->id_irq));

			/* Ignore incorrect ID trigger */
			if (((trigger & IRQF_TRIGGER_LOW) && (id > 0)) ||
			    ((trigger & IRQF_TRIGGER_HIGH) && (id == 0))) {
				enable_irq(info->id_irq);
				return;
			}

			if (id) {
				trigger &= ~IRQF_TRIGGER_HIGH;
				trigger |= IRQF_TRIGGER_LOW;
			} else {
				trigger &= ~IRQF_TRIGGER_LOW;
				trigger |= IRQF_TRIGGER_HIGH;
			}

			irq_set_irq_type(info->id_irq, trigger);
			enable_irq(info->id_irq);
		} else if (info->trigger_irq == info->vbus_irq &&
			   info->vbus_gpiod) {
			trigger = irqd_get_trigger_type(
					irq_get_irq_data(info->vbus_irq));

			/* Ignore incorrect VBUS trigger */
			if (((trigger & IRQF_TRIGGER_LOW) && (vbus > 0)) ||
			    ((trigger & IRQF_TRIGGER_HIGH) && (vbus == 0))) {
				enable_irq(info->vbus_irq);
				return;
			}

			if (vbus) {
				trigger &= ~IRQF_TRIGGER_HIGH;
				trigger |= IRQF_TRIGGER_LOW;
			} else {
				trigger &= ~IRQF_TRIGGER_LOW;
				trigger |= IRQF_TRIGGER_HIGH;
			}

			irq_set_irq_type(info->vbus_irq, trigger);
			enable_irq(info->vbus_irq);
		}
	}

	/* at first we clean states which are no longer active */
	if (id)
		extcon_set_cable_state_(info->edev,
					EXTCON_USB_HOST, false);
	if (!vbus)
		extcon_set_cable_state_(info->edev,
					EXTCON_USB, false);

	if (!id) {
		extcon_set_cable_state_(info->edev,
					EXTCON_USB_HOST, true);
	} else {
		if (vbus)
			extcon_set_cable_state_(info->edev,
						EXTCON_USB, true);
	}
}

static irqreturn_t usb_irq_handler(int irq, void *dev_id)
{
	struct usb_extcon_info *info = dev_id;

	if (info->level_trigger) {
		info->trigger_irq = irq;
		disable_irq_nosync(irq);
	}

	queue_delayed_work(system_power_efficient_wq, &info->wq_detcable,
			   info->debounce_jiffies);

	return IRQ_HANDLED;
}

static int usb_extcon_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct usb_extcon_info *info;
	unsigned long id_irqflags, vbus_irqflags;
	int ret;
	int id_active_low, vbus_active_low;

	if (!np)
		return -EINVAL;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = dev;
	info->id_gpiod = devm_gpiod_get_optional(&pdev->dev, "id", GPIOD_IN);
	info->vbus_gpiod = devm_gpiod_get_optional(&pdev->dev, "vbus",
						   GPIOD_IN);

	if (!info->id_gpiod && !info->vbus_gpiod) {
		dev_err(dev, "failed to get gpios\n");
		return -ENODEV;
	}

	if (IS_ERR(info->id_gpiod))
		return PTR_ERR(info->id_gpiod);

	if (IS_ERR(info->vbus_gpiod))
		return PTR_ERR(info->vbus_gpiod);

	info->level_trigger = of_property_read_bool(np, "extcon,level-trigger");
	info->trigger_irq = -1;
	id_active_low = info->id_gpiod ?
		gpiod_is_active_low(info->id_gpiod) : 0;
	vbus_active_low = info->vbus_gpiod ?
		gpiod_is_active_low(info->vbus_gpiod) : 0;

	info->edev = devm_extcon_dev_allocate(dev, usb_extcon_cable);
	if (IS_ERR(info->edev)) {
		dev_err(dev, "failed to allocate extcon device\n");
		return -ENOMEM;
	}

	ret = devm_extcon_dev_register(dev, info->edev);
	if (ret < 0) {
		dev_err(dev, "failed to register extcon device\n");
		return ret;
	}

	if (info->id_gpiod)
		ret = gpiod_set_debounce(info->id_gpiod,
					 USB_GPIO_DEBOUNCE_MS * 1000);
	if (!ret && info->vbus_gpiod)
		ret = gpiod_set_debounce(info->vbus_gpiod,
					 USB_GPIO_DEBOUNCE_MS * 1000);

	if (ret < 0)
		info->debounce_jiffies = msecs_to_jiffies(USB_GPIO_DEBOUNCE_MS);

	INIT_DELAYED_WORK(&info->wq_detcable, usb_extcon_detect_cable);

	if (info->level_trigger) {
		id_irqflags = id_active_low ?
			IRQF_TRIGGER_HIGH : IRQF_TRIGGER_LOW;
		vbus_irqflags = vbus_active_low ?
			IRQF_TRIGGER_LOW : IRQF_TRIGGER_HIGH;
	} else {
		id_irqflags = vbus_irqflags = IRQF_TRIGGER_RISING |
			IRQF_TRIGGER_FALLING;
	}

	if (info->id_gpiod) {
		gpio_direction_input(desc_to_gpio(info->id_gpiod));
		info->id_irq = gpiod_to_irq(info->id_gpiod);
		if (info->id_irq < 0) {
			dev_err(dev, "failed to get ID IRQ\n");
			return info->id_irq;
		}

		ret = devm_request_threaded_irq(dev, info->id_irq, NULL,
						usb_irq_handler,
						id_irqflags | IRQF_ONESHOT,
						pdev->name, info);
		if (ret < 0) {
			dev_err(dev, "failed to request handler for ID IRQ\n");
			return ret;
		}
	}

	if (info->vbus_gpiod) {
		gpio_direction_input(desc_to_gpio(info->vbus_gpiod));
		info->vbus_irq = gpiod_to_irq(info->vbus_gpiod);
		if (info->vbus_irq < 0) {
			dev_err(dev, "failed to get VBUS IRQ\n");
			return info->vbus_irq;
		}

		ret = devm_request_threaded_irq(dev, info->vbus_irq, NULL,
						usb_irq_handler,
						vbus_irqflags | IRQF_ONESHOT,
						pdev->name, info);
		if (ret < 0) {
			dev_err(dev, "failed to request handler for VBUS IRQ\n");
			return ret;
		}
	}

	platform_set_drvdata(pdev, info);
	device_init_wakeup(dev, true);

	/* Perform initial detection */
	usb_extcon_detect_cable(&info->wq_detcable.work);

	return 0;
}

static int usb_extcon_remove(struct platform_device *pdev)
{
	struct usb_extcon_info *info = platform_get_drvdata(pdev);

	cancel_delayed_work_sync(&info->wq_detcable);
	device_init_wakeup(&pdev->dev, false);

	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int usb_extcon_suspend(struct device *dev)
{
	struct usb_extcon_info *info = dev_get_drvdata(dev);
	int ret = 0;

	if (device_may_wakeup(dev)) {
		if (info->id_gpiod) {
			ret = enable_irq_wake(info->id_irq);
			if (ret)
				return ret;
		}
		if (info->vbus_gpiod) {
			ret = enable_irq_wake(info->vbus_irq);
			if (ret) {
				if (info->id_gpiod)
					disable_irq_wake(info->id_irq);

				return ret;
			}
		}
	}

	/*
	 * We don't want to process any IRQs after this point
	 * as GPIOs used behind I2C subsystem might not be
	 * accessible until resume completes. So disable IRQ.
	 */
	if (info->id_gpiod)
		disable_irq(info->id_irq);
	if (info->vbus_gpiod)
		disable_irq(info->vbus_irq);

	if (!device_may_wakeup(dev))
		pinctrl_pm_select_sleep_state(dev);

	return ret;
}

static int usb_extcon_resume(struct device *dev)
{
	struct usb_extcon_info *info = dev_get_drvdata(dev);
	int ret = 0;

	if (!device_may_wakeup(dev))
		pinctrl_pm_select_default_state(dev);

	if (device_may_wakeup(dev)) {
		if (info->id_gpiod) {
			ret = disable_irq_wake(info->id_irq);
			if (ret)
				return ret;
		}
		if (info->vbus_gpiod) {
			ret = disable_irq_wake(info->vbus_irq);
			if (ret) {
				if (info->id_gpiod)
					enable_irq_wake(info->id_irq);

				return ret;
			}
		}
	}

	if (info->id_gpiod)
		enable_irq(info->id_irq);
	if (info->vbus_gpiod)
		enable_irq(info->vbus_irq);

	if (!device_may_wakeup(dev))
		queue_delayed_work(system_power_efficient_wq,
				   &info->wq_detcable, 0);

	return ret;
}
#endif

static SIMPLE_DEV_PM_OPS(usb_extcon_pm_ops,
			 usb_extcon_suspend, usb_extcon_resume);

static const struct of_device_id usb_extcon_dt_match[] = {
	{ .compatible = "linux,extcon-usb-gpio", },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, usb_extcon_dt_match);

static const struct platform_device_id usb_extcon_platform_ids[] = {
	{ .name = "extcon-usb-gpio", },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(platform, usb_extcon_platform_ids);

static struct platform_driver usb_extcon_driver = {
	.probe		= usb_extcon_probe,
	.remove		= usb_extcon_remove,
	.driver		= {
		.name	= "extcon-usb-gpio",
		.pm	= &usb_extcon_pm_ops,
		.of_match_table = usb_extcon_dt_match,
	},
	.id_table = usb_extcon_platform_ids,
};

static int __init usb_extcon_init(void)
{
	return platform_driver_register(&usb_extcon_driver);
}
rootfs_initcall(usb_extcon_init);

static void __exit usb_extcon_exit(void)
{
	platform_driver_unregister(&usb_extcon_driver);
}
module_exit(usb_extcon_exit);

MODULE_AUTHOR("Roger Quadros <rogerq@ti.com>");
MODULE_DESCRIPTION("USB GPIO extcon driver");
MODULE_LICENSE("GPL v2");
