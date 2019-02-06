 /**
  * musb-sprd.c - Spreadtrum MUSB Specific Glue layer
  *
  * Copyright (c) 2016 Spreadtrum Co., Ltd.
  * http://www.spreadtrum.com
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License version 2 of
  * the License as published by the Free Software Foundation.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  */

#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/dma-mapping.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_platform.h>
#include <linux/prefetch.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/usb.h>
#include <linux/usb/charger.h>
#include <linux/usb/phy.h>
#include <linux/usb/sprd_usb.h>
#include <linux/usb/usb_phy_generic.h>
#include <linux/wakelock.h>
#include <linux/wait.h>
#include <linux/sprd_battery_common.h>

#include "musb_core.h"
#include "sprd_musbhsdma.h"

#define TA_WAIT_BCON(m) max_t(int, (m)->a_wait_bcon, OTG_TIME_A_WAIT_BCON)

#define DRIVER_DESC "Inventra Dual-Role USB Controller Driver"
#define MUSB_VERSION "6.0"
#define DRIVER_INFO DRIVER_DESC ", v" MUSB_VERSION

MODULE_DESCRIPTION(DRIVER_INFO);
MODULE_LICENSE("GPL");

#define MUSB_RECOVER_TIMEOUT 100
struct sprd_glue {
	struct device		*dev;
	struct platform_device		*musb;
	void __iomem		*base;
	int		irq;
	struct clk		*clk;
	struct phy		*phy;
	struct usb_phy		*xceiv;
	const char		*cable_detect;

	bool			hibernate_en;
	bool			pwr_collapse;
	bool			pwr_collapse_por;

	enum usb_dr_mode		dr_mode;
	enum usb_dr_mode		wq_mode;
	uint32_t		ref_clk_rate;
	int		gpio_device;
	int		gpio_host;
	int		gpio_otg;
	int		vbus_irq;
	int		usbid_irq;
	spinlock_t		lock;
	struct wake_lock		wake_lock;
	struct work_struct		work;
	struct delayed_work		recover_work;
	struct extcon_dev		*extcon;
	struct notifier_block		hot_plug_nb;

	bool		bus_active;
	bool		vbus_active;
	bool		charging_mode;
	int		host_disabled;
	int		musb_work_running;
};

static int boot_charging;

static u64 sprd_device_dma_mask = DMA_BIT_MASK(BITS_PER_LONG);

static inline struct musb *dev_to_musb_sprd(struct device *dev)
{
	return dev_get_drvdata(dev);
}

static void sprd_musb_enable(struct musb *musb)
{
	struct sprd_glue *glue = dev_get_drvdata(musb->controller->parent);
	u8 pwr;
	u8 otgextcsr;
	u8 devctl = musb_readb(musb->mregs, MUSB_DEVCTL);

	/* soft connect */
	if (glue->dr_mode == USB_DR_MODE_HOST) {
		devctl |= MUSB_DEVCTL_SESSION;
		musb_writeb(musb->mregs, MUSB_DEVCTL, devctl);
		otgextcsr = musb_readb(musb->mregs, MUSB_OTG_EXT_CSR);
		otgextcsr |= MUSB_HOST_FORCE_EN;
		musb_writeb(musb->mregs, MUSB_OTG_EXT_CSR, otgextcsr);
		dev_info(glue->dev, "sprd_musb_enable:HOST ENABLE %02x\n",
			devctl);
		musb->context.devctl = devctl;
	} else {
		pwr = musb_readb(musb->mregs, MUSB_POWER);
		if (musb->gadget_driver) {
			usb_phy_reset(glue->xceiv);
			pwr |= MUSB_POWER_SOFTCONN;
			glue->bus_active = true;
			dev_info(glue->dev, "sprd_musb_enable:MUSB_POWER_SOFTCONN\n");
		} else {
			pwr &= ~MUSB_POWER_SOFTCONN;
			dev_info(glue->dev, "sprd_musb_enable:MUSB_POWER_SOFTDISCONN\n");
			glue->bus_active = false;
		}
		musb_writeb(musb->mregs, MUSB_POWER, pwr);
	}
	musb_reset_all_fifo_2_default(musb);
}

static void sprd_musb_disable(struct musb *musb)
{
	struct sprd_glue *glue = dev_get_drvdata(musb->controller->parent);

    /*for test mode plug out/plug in*/
	musb_writeb(musb->mregs, MUSB_TESTMODE, 0x0);
	glue->bus_active = false;
}

static irqreturn_t sprd_musb_interrupt(int irq, void *__hci)
{
	irqreturn_t     retval = IRQ_NONE;
	struct musb     *musb = __hci;
	struct sprd_glue *glue = dev_get_drvdata(musb->controller->parent);
	u32 reg_dma;
	u16 mask16;
	u8  mask8;

	spin_lock(&musb->lock);

	if (!__clk_is_enabled(glue->clk)) {
		spin_unlock(&musb->lock);
		dev_err(musb->controller,
			"interrupt after close otg eb!\n");
		return retval;
	}

	mask8 = musb_readb(musb->mregs, MUSB_INTRUSBE);
	musb->int_usb = musb_readb(musb->mregs, MUSB_INTRUSB) & mask8;

	mask16 = musb_readw(musb->mregs, MUSB_INTRTXE);
	musb->int_tx = musb_readw(musb->mregs, MUSB_INTRTX) & mask16;

	mask16 = musb_readw(musb->mregs, MUSB_INTRRXE);
	musb->int_rx = musb_readw(musb->mregs, MUSB_INTRRX) & mask16;

	reg_dma = musb_readl(musb->mregs, MUSB_DMA_INTR_MASK_STATUS);

	dev_dbg(musb->controller, "sprd_musb_interrupt usb%04x tx%04x rx%04x dma%x\n",
			musb->int_usb, musb->int_tx, musb->int_rx, reg_dma);


	if (musb->int_usb || musb->int_tx || musb->int_rx)
		retval = musb_interrupt(musb);

	if (reg_dma)
		retval = sprd_dma_interrupt(musb, reg_dma);

	spin_unlock(&musb->lock);

	return retval;
}

static int sprd_musb_init(struct musb *musb)
{
	struct sprd_glue *glue = dev_get_drvdata(musb->controller->parent);

	register_ext_notifier(&glue->hot_plug_nb);

	musb->phy = glue->phy;
	musb->xceiv = glue->xceiv;
	sprd_musb_enable(musb);

	musb->isr = sprd_musb_interrupt;

	return 0;
}

static void sprd_musb_set_emphasis(struct musb *musb, bool enabled)
{
	struct sprd_glue *glue = dev_get_drvdata(musb->controller->parent);

	usb_phy_emphasis_set(glue->xceiv, enabled);
}

static int sprd_musb_exit(struct musb *musb)
{
	struct sprd_glue *glue = dev_get_drvdata(musb->controller->parent);

	dev_info(glue->dev, "sprd_musb_exit!\n");

	if (glue->usbid_irq)
		disable_irq_nosync(glue->usbid_irq);
	disable_irq_nosync(glue->vbus_irq);
	unregister_ext_notifier(&glue->hot_plug_nb);

	return 0;
}

static void sprd_musb_set_vbus(struct musb *musb, int is_on)
{
	struct usb_otg *otg = musb->xceiv->otg;
	u8 devctl;
	unsigned long timeout = 0;

	devctl = musb_readb(musb->mregs, MUSB_DEVCTL);

	if (is_on) {
		if (musb->xceiv->otg->state == OTG_STATE_A_IDLE) {
			/* start the session */
			devctl |= MUSB_DEVCTL_SESSION;
			musb_writeb(musb->mregs, MUSB_DEVCTL, devctl);
			/*
			 * Wait for the musb to set as A
			 * device to enable the VBUS
			 */
			while (musb_readb(musb->mregs, MUSB_DEVCTL) &
					 MUSB_DEVCTL_BDEVICE) {
				if (++timeout > 1000) {
					dev_err(musb->controller,
					"configured as A device timeout");
					break;
				}
			}

			otg_set_vbus(otg, 1);
		} else {
			musb->is_active = 1;
			otg->default_a = 1;
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
			devctl |= MUSB_DEVCTL_SESSION;
		}
	} else {
		musb->is_active = 0;

		/* NOTE:  we're skipping A_WAIT_VFALL -> A_IDLE and
		 * jumping right to B_IDLE...
		 */

		otg->default_a = 0;
		musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		devctl &= ~MUSB_DEVCTL_SESSION;

		MUSB_DEV_MODE(musb);
	}
	musb_writeb(musb->mregs, MUSB_DEVCTL, devctl);

	dev_dbg(musb->controller, "VBUS %s, devctl %02x\n",
		usb_otg_state_string(musb->xceiv->otg->state),
		musb_readb(musb->mregs, MUSB_DEVCTL));
}

static void sprd_musb_try_idle(struct musb *musb, unsigned long timeout)
{
	u8 otgextcsr;
	u16 txcsr;
	u32 i;
	void __iomem *mbase = musb->mregs;
	u32 csr;

	if (musb->xceiv->otg->state == OTG_STATE_A_WAIT_BCON) {
		for (i = 1; i < musb->nr_endpoints; i++) {
			csr = musb_readl(mbase, MUSB_DMA_CHN_INTR(i));
			csr |= CHN_CLEAR_INT_EN;
			musb_writel(mbase, MUSB_DMA_CHN_INTR(i), csr);

			csr = musb_readl(mbase, MUSB_DMA_CHN_PAUSE(i));
			csr |= CHN_CLR;
			musb_writel(mbase, MUSB_DMA_CHN_PAUSE(i), csr);
		}

		otgextcsr = musb_readb(musb->mregs, MUSB_OTG_EXT_CSR);
		otgextcsr |= MUSB_CLEAR_TXBUFF | MUSB_CLEAR_RXBUFF;
		musb_writeb(musb->mregs, MUSB_OTG_EXT_CSR, otgextcsr);

		for (i = 0; i < musb->nr_endpoints; i++) {
			struct musb_hw_ep *hw_ep = musb->endpoints + i;

			txcsr = musb_readw(hw_ep->regs, MUSB_TXCSR);
			if (txcsr & MUSB_TXCSR_FIFONOTEMPTY) {
				txcsr |= MUSB_TXCSR_FLUSHFIFO;
				txcsr &= ~MUSB_TXCSR_TXPKTRDY;
				musb_writew(hw_ep->regs, MUSB_TXCSR, txcsr);
				musb_writew(hw_ep->regs, MUSB_TXCSR, txcsr);
				txcsr = musb_readw(hw_ep->regs, MUSB_TXCSR);
				txcsr &= ~(MUSB_TXCSR_AUTOSET
				| MUSB_TXCSR_DMAENAB
				| MUSB_TXCSR_DMAMODE
				| MUSB_TXCSR_H_RXSTALL
				| MUSB_TXCSR_H_NAKTIMEOUT
				| MUSB_TXCSR_H_ERROR
				| MUSB_TXCSR_TXPKTRDY);
				musb_writew(hw_ep->regs, MUSB_TXCSR, txcsr);
			}
		}
	}
}

static int sprd_musb_recover(struct musb *musb)
{
	struct sprd_glue *glue = dev_get_drvdata(musb->controller->parent);

	if (is_host_active(musb))
		schedule_delayed_work(&glue->recover_work, msecs_to_jiffies(MUSB_RECOVER_TIMEOUT));
	return 0;
}

static const struct musb_platform_ops sprd_musb_ops = {
	.quirks = MUSB_DMA_SPRD,
	.init = sprd_musb_init,
	.exit = sprd_musb_exit,
	.enable = sprd_musb_enable,
	.disable = sprd_musb_disable,
	.dma_init = sprd_musb_dma_controller_create,
	.dma_exit = sprd_musb_dma_controller_destroy,
	.set_vbus = sprd_musb_set_vbus,
	.try_idle = sprd_musb_try_idle,
	.recover = sprd_musb_recover,
	.phy_set_emphasis = sprd_musb_set_emphasis,
};

#define SPRD_MUSB_MAX_EP_NUM	16
#define SPRD_MUSB_RAM_BITS	13
static struct musb_fifo_cfg sprd_musb_mode_cfg[] = {
	MUSB_EP_FIFO_DOUBLE(1, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(1, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(2, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(2, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(3, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(3, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(4, FIFO_TX, 1024),
	MUSB_EP_FIFO_DOUBLE(4, FIFO_RX, 4096),
	MUSB_EP_FIFO_SINGLE(5, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(5, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(6, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(6, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(7, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(7, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(8, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(8, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(9, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(9, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(10, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(10, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(11, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(11, FIFO_RX, 512),
	MUSB_EP_FIFO_DOUBLE(12, FIFO_TX, 512),
	MUSB_EP_FIFO_DOUBLE(12, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(13, FIFO_TX, 64),
	MUSB_EP_FIFO_SINGLE(13, FIFO_RX, 64),
	MUSB_EP_FIFO_SINGLE(14, FIFO_TX, 64),
	MUSB_EP_FIFO_SINGLE(14, FIFO_RX, 64),
	MUSB_EP_FIFO_SINGLE(15, FIFO_TX, 64),
	MUSB_EP_FIFO_SINGLE(15, FIFO_RX, 64),
};

static struct musb_hdrc_config sprd_musb_hdrc_config = {
	.fifo_cfg = sprd_musb_mode_cfg,
	.fifo_cfg_size = ARRAY_SIZE(sprd_musb_mode_cfg),
	.multipoint = false,
	.dyn_fifo = true,
	.soft_con = true,
	.num_eps = SPRD_MUSB_MAX_EP_NUM,
	.ram_bits = SPRD_MUSB_RAM_BITS,
	.dma = 0,
};

static int sprd_musb_ext_notifier(struct notifier_block *nb,
				unsigned long action, void *data)
{
	struct sprd_glue *glue = container_of(nb, struct sprd_glue,
							 hot_plug_nb);
	unsigned long flags;
	int value = gpio_get_value(glue->gpio_device);

	switch (action) {
	case CABLE_STATUS_DEV_CONN:
		if (glue->vbus_irq != -1)
			return NOTIFY_DONE;
		spin_lock_irqsave(&glue->lock, flags);
		glue->vbus_active = true;
		glue->wq_mode = USB_DR_MODE_PERIPHERAL;
		spin_unlock_irqrestore(&glue->lock, flags);
		break;
	case CABLE_STATUS_HOST_CONN:
		if ((glue->vbus_irq != -1) && (glue->vbus_active) &&
			(glue->dr_mode == USB_DR_MODE_PERIPHERAL))
			return NOTIFY_DONE;

		if (value == 1)
			return NOTIFY_DONE;

		spin_lock_irqsave(&glue->lock, flags);
		glue->vbus_active = true;
		glue->wq_mode = USB_DR_MODE_HOST;
		spin_unlock_irqrestore(&glue->lock, flags);
		break;
	case CABLE_STATUS_DEV_DISCONN:
		if (glue->vbus_irq != -1)
			return NOTIFY_DONE;
		spin_lock_irqsave(&glue->lock, flags);
		glue->vbus_active = false;
		glue->wq_mode = USB_DR_MODE_PERIPHERAL;
		spin_unlock_irqrestore(&glue->lock, flags);
		break;
	case CABLE_STATUS_HOST_DISCONN:
		if (glue->vbus_active == false)
			return NOTIFY_DONE;
		if (glue->dr_mode != USB_DR_MODE_HOST)
			return NOTIFY_DONE;
		spin_lock_irqsave(&glue->lock, flags);
		glue->vbus_active = false;
		glue->wq_mode = USB_DR_MODE_HOST;
		spin_unlock_irqrestore(&glue->lock, flags);
		break;
	default:
		/* Unknown actions */
		dev_err(glue->dev, "Unknown action 0x%lx\n", action);
		return NOTIFY_BAD;
	}

	schedule_work(&glue->work);

	return NOTIFY_DONE;
}

static irqreturn_t musb_sprd_usbid_handler(int irq, void *dev_id)
{
	struct sprd_glue *glue = (struct sprd_glue *)dev_id;
	int value;

	value = !!gpio_get_value(glue->gpio_host);
	dev_info(glue->dev, "%s called usb_id = %d\n", __func__, value);
	value = !value;
	irq_set_irq_type(irq,
		value ? IRQ_TYPE_LEVEL_HIGH : IRQ_TYPE_LEVEL_LOW);

	glue->vbus_active = value;
	glue->wq_mode = USB_DR_MODE_HOST;

	schedule_work(&glue->work);

	return IRQ_HANDLED;
}

static int musb_sprd_resume_child(struct device *dev, void *data)
{
	int ret;

	ret = pm_runtime_get_sync(dev);
	if (ret) {
		dev_err(dev, "musb child device enters resume failed!!!\n");
		return ret;
	}

	return 0;
}

static int musb_sprd_suspend_child(struct device *dev, void *data)
{
	int ret, cnt = 100;

	ret = pm_runtime_put_sync(dev);
	if (ret) {
		dev_err(dev, "enters suspend failed, ret = %d\n", ret);
		return ret;
	}

	while (!pm_runtime_suspended(dev) && --cnt > 0)
		msleep(500);

	if (cnt <= 0) {
		dev_err(dev, "musb child device enters suspend failed!!!\n");
		return -EAGAIN;
	}

	return 0;
}

static int musb_sprd_is_connect_host(struct sprd_glue *glue)
{
	struct musb *musb = platform_get_drvdata(glue->musb);
	struct usb_charger *uchger = musb->g.charger;
	enum usb_charger_type type;

	if (!uchger || !uchger->get_charger_type)
		return 0;

	type = uchger->get_charger_type(uchger);
	if (type == SDP_TYPE || type == CDP_TYPE)
		return 1;

	return 0;
}

static __init int musb_sprd_charger_mode(char *str)
{
	if (strcmp(str, "charger"))
		boot_charging = 0;
	else
		boot_charging = 1;

	return 0;
}
__setup("androidboot.mode=", musb_sprd_charger_mode);

static void musb_sprd_set_otg_en(struct sprd_glue *glue, int enable)
{
	if (gpio_is_valid(glue->gpio_otg)) {
		dev_dbg(glue->dev, "musb gpio_set_value  %d\n", enable);
		if (enable) {
			/*
			 * Two mode for ext IC:
			 * mode 1. set gpio_otg high for 0.25A
			 * mode 2. make a gpio_otg pulse high-low-high for 0.55A,
			 * mode 2 is the typical mode suggest by provider.
			 */
			gpio_set_value(glue->gpio_otg, 1);
			gpio_set_value(glue->gpio_otg, 0);
			gpio_set_value(glue->gpio_otg, 1);
		} else {
			gpio_set_value(glue->gpio_otg, 0);
		}
	} else {
		sprd_extic_otg_power(!!enable);
	}
}

static void sprd_musb_recover_work(struct work_struct *work)
{
	struct sprd_glue *glue = container_of(work,
				 struct sprd_glue, recover_work.work);
	struct musb *musb = platform_get_drvdata(glue->musb);

	dev_info(glue->dev, "try to recover musb controller\n");
	if (!glue->vbus_active || !is_host_active(musb))
		return;
	glue->vbus_active = 0;
	glue->wq_mode = USB_DR_MODE_HOST;
	schedule_work(&glue->work);
	msleep(300);
	glue->vbus_active = 1;
	glue->wq_mode = USB_DR_MODE_HOST;
	schedule_work(&glue->work);
}

static void sprd_musb_work(struct work_struct *work)
{
	struct sprd_glue *glue = container_of(work, struct sprd_glue, work);
	struct musb *musb = platform_get_drvdata(glue->musb);
	struct usb_charger *uchger = musb->g.charger;
	unsigned long flags;
	bool charging_only = false;
	int ret;
	int cnt = 100;

	if ((glue->musb_work_running == 0) &&
	    (glue->wq_mode == USB_DR_MODE_HOST)) {
		while (!musb->gadget_driver)
			msleep(50);
		msleep(50);
	}
	glue->musb_work_running = 1;
	glue->dr_mode = glue->wq_mode;
	dev_dbg(glue->dev, "%s enter: vbus = %d mode = %d\n",
			__func__, glue->vbus_active, glue->dr_mode);

	disable_irq_nosync(glue->vbus_irq);
	if (glue->vbus_active) {
		if (glue->dr_mode == USB_DR_MODE_PERIPHERAL)
			usb_gadget_set_state(&musb->g, USB_STATE_ATTACHED);

		musb->context.testmode = 0;
		musb->test_mode_nr = 0;
		musb->test_mode = false;
		/*
		* If the charger type is not SDP or CDP type, it does
		* not need to resume the device, just charging.
		*/
		while ((uchger) && (!uchger->get_charger_type)
			 && (--cnt > 0))
			msleep(100);

		if ((glue->dr_mode == USB_DR_MODE_PERIPHERAL &&
			!musb_sprd_is_connect_host(glue)) || boot_charging) {
			spin_lock_irqsave(&glue->lock, flags);
			glue->charging_mode = true;
			spin_unlock_irqrestore(&glue->lock, flags);

			dev_info(glue->dev,
			 "Don't need resume musb device in charging mode!\n");
			goto end;
		}
		cnt = 100;
		while (!pm_runtime_suspended(glue->dev)
			&& (--cnt > 0))
			msleep(200);

		if (cnt <= 0) {
			dev_err(glue->dev,
			"Wait for musb core enter suspend failed!\n");
			goto end;
		}

		if (glue->dr_mode == USB_DR_MODE_HOST)
			MUSB_HST_MODE(musb);

		ret = pm_runtime_get_sync(glue->dev);
		if (ret) {
			spin_lock_irqsave(&glue->lock, flags);
			glue->dr_mode = USB_DR_MODE_UNKNOWN;
			spin_unlock_irqrestore(&glue->lock, flags);
			dev_err(glue->dev, "Resume sprd_musb device failed!\n");
			goto end;
		}

		if (glue->dr_mode == USB_DR_MODE_HOST)
			musb_sprd_set_otg_en(glue, 1);

		ret = device_for_each_child(glue->dev, NULL,
			musb_sprd_resume_child);
		if (ret) {
			pm_runtime_put_sync(glue->dev);
			spin_lock_irqsave(&glue->lock, flags);
			glue->dr_mode = USB_DR_MODE_UNKNOWN;
			spin_unlock_irqrestore(&glue->lock, flags);
			dev_err(glue->dev, "Resume sprd_musb core failed!\n");
			goto end;
		}

		/*
		* We have resumed the dwc3 device to do enumeration,
		*  thus clear the charging mode flag.
		 */
		spin_lock_irqsave(&glue->lock, flags);
		glue->charging_mode = false;
		spin_unlock_irqrestore(&glue->lock, flags);

		if (!charging_only)
			wake_lock(&glue->wake_lock);

		dev_info(glue->dev, "is running as %s\n",
			glue->dr_mode == USB_DR_MODE_HOST ? "HOST" : "DEVICE");
		goto end;
	} else {
		spin_lock_irqsave(&glue->lock, flags);
		charging_only = glue->charging_mode;
		spin_unlock_irqrestore(&glue->lock, flags);
		usb_gadget_set_state(&musb->g, USB_STATE_REMOVED);
		if (charging_only || pm_runtime_suspended(glue->dev)) {
			dev_info(glue->dev,
					"musb device had been in suspend status!\n");
			goto end;
		}
		if (glue->dr_mode == USB_DR_MODE_PERIPHERAL) {
			u8 devctl = musb_readb(musb->mregs, MUSB_DEVCTL);

			musb_writeb(musb->mregs, MUSB_DEVCTL,
				devctl & ~MUSB_DEVCTL_SESSION);
			musb->shutdowning = 1;
			usb_phy_post_init(glue->xceiv);
			cnt = 10;
			while (musb->shutdowning && cnt-- > 0)
				msleep(50);
		}

		if (glue->dr_mode == USB_DR_MODE_HOST)
			musb_sprd_set_otg_en(glue, 0);

		musb->shutdowning = 0;

		ret = device_for_each_child(glue->dev, NULL,
					musb_sprd_suspend_child);
		if (ret) {
			dev_err(glue->dev, "musb core suspend failed!\n");
			goto end;
		}

		MUSB_DEV_MODE(musb);
		ret = pm_runtime_put_sync(glue->dev);
		if (ret) {
			dev_err(glue->dev, "musb sprd suspend failed!\n");
			goto end;
		}

		spin_lock_irqsave(&glue->lock, flags);
		glue->dr_mode = USB_DR_MODE_UNKNOWN;
		glue->charging_mode = false;
		musb->xceiv->otg->default_a = 0;
		musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		spin_unlock_irqrestore(&glue->lock, flags);
		if (!charging_only)
			wake_unlock(&glue->wake_lock);

		dev_info(glue->dev, "is shut down\n");
		goto end;
	}
end:
	enable_irq(glue->vbus_irq);
}

static irqreturn_t musb_sprd_vbus_handler(int irq, void *dev_id)
{
	struct sprd_glue *glue = (struct sprd_glue *)dev_id;
	struct musb *musb = platform_get_drvdata(glue->musb);
	int value;

	value = !!gpio_get_value(glue->gpio_device);
	dev_info(glue->dev, "%s called vbus = %d\n", __func__, value);
	irq_set_irq_type(irq,
		value ? IRQ_TYPE_LEVEL_LOW : IRQ_TYPE_LEVEL_HIGH);

	if (glue->vbus_active == value)
		return IRQ_HANDLED;
	else if (value)
		glue->wq_mode = USB_DR_MODE_PERIPHERAL;
	else if (glue->dr_mode != USB_DR_MODE_PERIPHERAL) {

		dev_info(glue->dev, "%s ignore the vbus event\n", __func__);
		return IRQ_HANDLED;
	}
	glue->vbus_active = value;

	MUSB_DEV_MODE(musb);
	schedule_work(&glue->work);

	return IRQ_HANDLED;
}

static int musb_sprd_config_usbid_int(struct sprd_glue *glue)
{
	int irq, ret;
	int value;

	ret = devm_gpio_request(glue->dev,
			glue->gpio_host, "musb usb_id detect");
	if (ret < 0)
		return ret;

	ret = gpio_direction_input(glue->gpio_host);
	if (ret < 0)
		goto err;

	irq = gpio_to_irq(glue->gpio_host);
	if (irq < 0)
		goto err;

	ret = irq_set_irq_type(irq, IRQ_TYPE_LEVEL_LOW);
	if (ret < 0)
		goto err;

	ret = devm_request_threaded_irq(glue->dev, irq,
			NULL, musb_sprd_usbid_handler,
			IRQF_SHARED | IRQF_NO_SUSPEND | IRQF_ONESHOT,
			"musb usb_id dectect irq", glue);
	value = !!gpio_get_value(glue->gpio_host);
	dev_info(glue->dev, "gpio_usb_id = %d\n", value);
	if (ret < 0)
		goto err;

	glue->usbid_irq = irq;

	return ret;
err:
	devm_gpio_free(glue->dev, glue->gpio_host);

	return ret;
}

static int musb_sprd_config_vbus_int(struct sprd_glue *glue)
{
	int irq, ret;

	ret = devm_gpio_request(glue->dev,
			glue->gpio_device, "musb vbus detect");
	if (ret < 0)
		dev_info(glue->dev, "already devm_gpio_request!\n");

	ret = gpio_direction_input(glue->gpio_device);
	if (ret < 0)
		goto err;

	irq = gpio_to_irq(glue->gpio_device);
	if (irq < 0)
		goto err;

	ret = irq_set_irq_type(irq, IRQ_TYPE_LEVEL_HIGH);
	if (ret < 0)
		goto err;

	ret = devm_request_threaded_irq(glue->dev, irq,
			NULL, musb_sprd_vbus_handler,
			IRQF_SHARED | IRQF_NO_SUSPEND,
			"musb vbus dectect irq", glue);
	if (ret < 0)
		goto err;

	glue->vbus_irq = irq;

	return ret;
err:
	devm_gpio_free(glue->dev, glue->gpio_device);

	return ret;
}

static int musb_sprd_otg_init(struct sprd_glue *glue)
{
	int ret;

	ret = devm_gpio_request(glue->dev,
			glue->gpio_otg, "musb otg ext power detect");
	if (ret < 0) {
		dev_err(glue->dev, "musb request otg-gpio error \n");
		return ret;
	}
	ret = gpio_direction_output(glue->gpio_otg, 0);
	if (ret < 0)
		dev_err(glue->dev, "musb direction output error \n");

	return ret;
}

/**
 * Store the hostvbus_status attribure.
 */
static ssize_t musb_hostvbus_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t size)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);

	if (strncmp(buf, "off", 3) == 0) {
		glue->host_disabled &= ~(0x02);
		musb_sprd_set_otg_en(glue, 0);
	} else if (strncmp(buf, "on", 2) == 0) {
		glue->host_disabled |= 0x02;
		musb_sprd_set_otg_en(glue, 1);
	}

	return size;
}
DEVICE_ATTR(vbus_control, S_IWUSR, NULL, musb_hostvbus_store);

/**
 * Store the usb status attribure when vbus on
 */
static ssize_t musb_usb_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t size)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);
	struct musb *musb;

	musb = platform_get_drvdata(glue->musb);
	if (!musb)
		return -EINVAL;

	if (strncmp(buf, "connect", 10) == 0) {
		if (!musb->shutdowning)
			usb_phy_init(glue->xceiv);
	} else if (strncmp(buf, "disconnect", 7) == 0) {
		if (!musb->shutdowning)
			usb_phy_shutdown(glue->xceiv);
	}

	return size;
}
DEVICE_ATTR(usb_control, S_IWUSR, NULL, musb_usb_store);


/**
 * Show / Store the hostenable attribure.
 */
static ssize_t musb_hostenable_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);

	return sprintf(buf, "%s\n",
		((glue->host_disabled&0x01) ? "disabled" : "enabled"));
}

static ssize_t musb_hostenable_store(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);

	if (strncmp(buf, "disable", 7) == 0) {
		glue->host_disabled |= 1;
		disable_irq(glue->usbid_irq);
	} else if (strncmp(buf, "enable", 6) == 0) {
		glue->host_disabled &= ~(0x01);
		enable_irq(glue->usbid_irq);
	} else {
		return 0;
	}

	return count;
}

DEVICE_ATTR(host_enable, S_IRUGO | S_IWUSR, musb_hostenable_show,
	musb_hostenable_store);

static ssize_t musb_otgstatus_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);
	int status;

	status = !!gpio_get_value(glue->gpio_host);
	return sprintf(buf, "%s\n", (status ? "high" : "low"));
}

/**
 * Store the otg_status attribure.
 */

DEVICE_ATTR(otg_status, S_IRUGO, musb_otgstatus_show, NULL);

static ssize_t maximum_speed_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);
	struct musb *musb;

	if (!glue)
		return -EINVAL;

	musb = platform_get_drvdata(glue->musb);
	if (!musb)
		return -EINVAL;

	return sprintf(buf, "%s\n",
		usb_speed_string(musb->config->maximum_speed));
}

static ssize_t maximum_speed_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t size)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);
	struct musb *musb;
	u32 max_speed;

	if (!glue)
		return -EINVAL;

	if (kstrtouint(buf, 0, &max_speed))
		return -EINVAL;

	if (max_speed > USB_SPEED_SUPER)
		return -EINVAL;

	musb = platform_get_drvdata(glue->musb);
	if (!musb)
		return -EINVAL;

	musb->config->maximum_speed = max_speed;
	return size;
}
static DEVICE_ATTR_RW(maximum_speed);

static ssize_t current_speed_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);
	struct musb *musb;

	if (!glue)
		return -EINVAL;

	musb = platform_get_drvdata(glue->musb);
	if (!musb)
		return -EINVAL;

	return sprintf(buf, "%s\n", usb_speed_string(musb->g.speed));
}
static DEVICE_ATTR_RO(current_speed);

static struct attribute *musb_sprd_attrs[] = {
	&dev_attr_maximum_speed.attr,
	&dev_attr_current_speed.attr,
	NULL
};
ATTRIBUTE_GROUPS(musb_sprd);

static int musb_sprd_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = pdev->dev.of_node;
	struct musb_hdrc_platform_data pdata;
	struct platform_device_info pinfo;
	struct sprd_glue *glue;
	struct musb *musb;
	int ret;

	glue = devm_kzalloc(&pdev->dev, sizeof(*glue), GFP_KERNEL);
	if (!glue)
		return -ENOMEM;

	memset(&pdata, 0, sizeof(pdata));
	if (IS_ENABLED(CONFIG_USB_MUSB_GADGET))
		pdata.mode = MUSB_PORT_MODE_GADGET;
	else if (IS_ENABLED(CONFIG_USB_MUSB_HOST))
		pdata.mode = MUSB_PORT_MODE_HOST;
	else if (IS_ENABLED(CONFIG_USB_MUSB_DUAL_ROLE))
		pdata.mode = MUSB_PORT_MODE_DUAL_ROLE;
	else
		dev_err(&pdev->dev, "Invalid or missing 'dr_mode' property\n");

	dev_info(dev, "musb probe mode=%d\n", pdata.mode);

	ret = of_property_read_string(node, "sprd,cable-detection-method",
			&glue->cable_detect);
	if (ret) {
		dev_err(dev, "fail to get cable detection method\n");
		return ret;
	}
	dev_info(dev, "musb cable detection method is %s\n",
		glue->cable_detect);

	glue->clk = of_clk_get_by_name(node, "core_clk");
	if (IS_ERR(glue->clk))
		dev_warn(dev, "no core clk specified\n");
	clk_prepare_enable(glue->clk);

	glue->xceiv = devm_usb_get_phy_by_phandle(&pdev->dev, "usb-phy", 0);
	if (IS_ERR(glue->xceiv)) {
		ret = PTR_ERR(glue->xceiv);
		dev_err(&pdev->dev, "Error getting usb-phy %d\n", ret);
		return ret;
	}

	wake_lock_init(&glue->wake_lock, WAKE_LOCK_SUSPEND, "musb-sprd");
	spin_lock_init(&glue->lock);
	INIT_WORK(&glue->work, sprd_musb_work);
	INIT_DELAYED_WORK(&glue->recover_work, sprd_musb_recover_work);

	/*  GPIOs now */
	glue->gpio_host = -1;
	glue->gpio_device =  -1;
	glue->gpio_otg = -1;
	glue->vbus_irq = -1;
	glue->dev = &pdev->dev;

	if (!strcmp(glue->cable_detect, "typec")) {
		glue->hot_plug_nb.notifier_call = sprd_musb_ext_notifier;
		glue->hot_plug_nb.priority = 0;
	}

	glue->gpio_device =  of_get_named_gpio(node, "sprd,vbus-gpios", 0);
	if (glue->gpio_device < 0) {
		glue->gpio_device = -1;
		dev_info(dev, "invalid usb vbus gpio: %d\n",
			glue->gpio_device);
		goto put_musb;
	}
	glue->gpio_otg = of_get_named_gpio(node, "sprd,otg-gpios", 0);

	platform_set_drvdata(pdev, glue);

	pdata.platform_ops = &sprd_musb_ops;
	pdata.config = &sprd_musb_hdrc_config;
	memset(&pinfo, 0, sizeof(pinfo));
	pinfo.name = "musb-hdrc";
	pinfo.id = PLATFORM_DEVID_AUTO;
	pinfo.parent = &pdev->dev;
	pinfo.res = pdev->resource;
	pinfo.num_res = pdev->num_resources;
	pinfo.data = &pdata;
	pinfo.size_data = sizeof(pdata);
	pinfo.dma_mask = sprd_device_dma_mask;

	glue->musb = platform_device_register_full(&pinfo);
	if (IS_ERR(glue->musb)) {
		ret = PTR_ERR(glue->musb);
		dev_err(&pdev->dev, "Error registering musb dev: %d\n", ret);
		return ret;
	}
	ret = musb_sprd_config_vbus_int(glue);
	if (ret) {
		dev_err(dev, "fail to config vbus-gpio\n");
		goto put_musb;
	}

	if (gpio_is_valid(glue->gpio_otg)) {
		ret = musb_sprd_otg_init(glue);
		if (ret < 0) {
			dev_err(dev, "fail to init gpio otg\n");
			goto put_musb;
		}
	} else {
		dev_info(dev, "not use gpio to detect otg");
		glue->gpio_otg = -1;
	}

	if (IS_ENABLED(CONFIG_USB_MUSB_HOST) ||
		IS_ENABLED(CONFIG_USB_MUSB_DUAL_ROLE)) {
		ret = of_get_named_gpio(node, "sprd,usb-id-gpios", 0);
		if (ret < 0) {
			dev_err(dev, "fail to get usb-id-gpio\n");
		} else {
			glue->gpio_host = ret;
			dev_info(dev, "usb-id-gpio = %d\n", ret);
			ret = musb_sprd_config_usbid_int(glue);
			if (ret < 0)
				dev_err(dev, "fail to config usb-id-gpio\n");
			else {
					device_create_file(dev,
						&dev_attr_vbus_control);
					device_create_file(dev,
						&dev_attr_host_enable);
					device_create_file(dev,
						&dev_attr_otg_status);
			}
		}
	}
	device_create_file(dev, &dev_attr_usb_control);
	musb = platform_get_drvdata(glue->musb);
	musb->g.charger->get_charger_type = sprdchg_charger_is_adapter_for_usb;

	ret = sysfs_create_groups(&glue->dev->kobj, musb_sprd_groups);
	if (ret)
		dev_warn(glue->dev, "failed to create musb attributes\n");

	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	return 0;

put_musb:
	platform_device_put(glue->musb);

	return ret;
}

static int musb_sprd_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct musb *musb = dev_to_musb_sprd(dev);
	struct sprd_glue *glue = platform_get_drvdata(pdev);

	/* this gets called on rmmod.
	 *  - Host mode: host may still be active
	 *  - Peripheral mode: peripheral is deactivated (or never-activated)
	 *  - OTG mode: both roles are deactivated (or never-activated)
	 */
	if (musb->dma_controller)
		musb_dma_controller_destroy(musb->dma_controller);
	sysfs_remove_groups(&glue->dev->kobj, musb_sprd_groups);

	cancel_work_sync(&musb->irq_work);
	cancel_delayed_work_sync(&musb->finish_resume_work);
	cancel_delayed_work_sync(&musb->deassert_reset_work);
	platform_device_unregister(glue->musb);

	return 0;
}

static void musb_sprd_release_all_request(struct musb *musb)
{
	struct musb_ep *musb_ep_in;
	struct musb_ep *musb_ep_out;
	struct musb_hw_ep *endpoints;
	struct usb_ep *ep_in;
	struct usb_ep *ep_out;
	u32 i;

	for (i = 1; i < 16; i++) {
		endpoints = &musb->endpoints[i];
		if (!endpoints)
			continue;
		musb_ep_in = &endpoints->ep_in;
		if (musb_ep_in && musb_ep_in->dma) {
			ep_in = &musb_ep_in->end_point;
			usb_ep_disable(ep_in);
		}
		musb_ep_out = &endpoints->ep_out;
		if (musb_ep_out && musb_ep_out->dma) {
			ep_out = &musb_ep_out->end_point;
			usb_ep_disable(ep_out);
		}
	}
}

static void musb_sprd_disable_all_interrupts(struct musb *musb)
{
	void __iomem	*mbase = musb->mregs;
	u16	temp;
	u32	i;
	u32	intr;

	/* disable interrupts */
	musb_writeb(mbase, MUSB_INTRUSBE, 0);
	musb_writew(mbase, MUSB_INTRTXE, 0);
	musb_writew(mbase, MUSB_INTRRXE, 0);

	/*  flush pending interrupts */
	temp = musb_readb(mbase, MUSB_INTRUSB);
	temp = musb_readw(mbase, MUSB_INTRTX);
	temp = musb_readw(mbase, MUSB_INTRRX);

	/* disable dma interrupts */
	for (i = 1; i <= MUSB_DMA_CHANNELS; i++) {
		intr = musb_readl(mbase, MUSB_DMA_CHN_INTR(i));
		intr &= ~(CHN_LLIST_INT_EN | CHN_START_INT_EN |
			CHN_CLEAR_INT_EN | CHN_FRAG_INT_EN |
			CHN_BLK_INT_EN);
		musb_writel(mbase, MUSB_DMA_CHN_INTR(i), intr);
		if (i < 16)
			intr |= CHN_LLIST_INT_CLR | CHN_START_INT_CLR |
				CHN_FRAG_INT_CLR | CHN_BLK_INT_CLR;
		else
			intr |= CHN_LLIST_INT_CLR | CHN_START_INT_CLR |
				CHN_FRAG_INT_CLR | CHN_BLK_INT_CLR |
				CHN_USBRX_LAST_INT_CLR;
		musb_writel(mbase, MUSB_DMA_CHN_INTR(i), intr);
		musb_writel(mbase, MUSB_DMA_CHN_PAUSE(i), 0x0);
		musb_writel(mbase, MUSB_DMA_CHN_CFG(i), 0x0);
	}
}

static int musb_sprd_runtime_suspend(struct device *dev)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);
	struct musb *musb = platform_get_drvdata(glue->musb);
	struct dma_controller *c = musb->dma_controller;
	struct sprd_musb_dma_controller *controller = container_of(c,
			struct sprd_musb_dma_controller, controller);
	int ret;
	unsigned long flags;

	if (glue->dr_mode == USB_DR_MODE_HOST)
		usb_phy_vbus_off(glue->xceiv);
	else
		musb_sprd_release_all_request(musb);

	if (glue->dr_mode == USB_DR_MODE_HOST) {
		ret = wait_event_timeout(controller->wait,
			(controller->used_channels == 0),
			msecs_to_jiffies(2000));
		if (ret == 0)
			dev_err(glue->dev, "wait for port suspend timeout!\n");
	}
	disable_irq(musb->nIrq);
	musb_sprd_disable_all_interrupts(musb);

	if (glue->dr_mode == USB_DR_MODE_HOST) {
		do {
			if (atomic_read(&musb->plugout_flag) == 0)
				break;

			dev_info(glue->dev, "wait for urb function done. flag:%d\n",
					atomic_read(&musb->plugout_flag));
			mdelay(1);
		} while (1);
	}

	spin_lock_irqsave(&musb->lock, flags);
	clk_disable_unprepare(glue->clk);
	spin_unlock_irqrestore(&musb->lock, flags);

	if (!musb->shutdowning)
		usb_phy_shutdown(glue->xceiv);
	dev_info(dev, "enter into suspend mode\n");

	return 0;
}

static int musb_sprd_runtime_resume(struct device *dev)
{
	struct sprd_glue *glue = dev_get_drvdata(dev);
	struct musb *musb = platform_get_drvdata(glue->musb);

	clk_prepare_enable(glue->clk);

	if (!musb->shutdowning)
		usb_phy_init(glue->xceiv);
	if (glue->dr_mode == USB_DR_MODE_HOST) {
		usb_phy_vbus_on(glue->xceiv);
		sprd_musb_enable(musb);
	}
	enable_irq(musb->nIrq);

	dev_info(dev, "enter into resume mode\n");

	return 0;
}

static int musb_sprd_runtime_idle(struct device *dev)
{
	dev_info(dev, "enter into idle mode\n");
	return 0;
}

static const struct dev_pm_ops musb_sprd_pm_ops = {
	.runtime_suspend = musb_sprd_runtime_suspend,
	.runtime_resume = musb_sprd_runtime_resume,
	.runtime_idle = musb_sprd_runtime_idle,
};

static const struct of_device_id usb_ids[] = {
	{ .compatible = "sprd,usb" },
	{}
};

MODULE_DEVICE_TABLE(of, usb_ids);

static struct platform_driver musb_sprd_driver = {
	.driver = {
		.name = "musb-sprd",
		.pm = &musb_sprd_pm_ops,
		.of_match_table = usb_ids,
	},
	.probe = musb_sprd_probe,
	.remove = musb_sprd_remove,
};

module_platform_driver(musb_sprd_driver);
