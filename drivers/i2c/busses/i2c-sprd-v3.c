/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * SPDX-License-Identifier: GPL-2.0
 */
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/slab.h>
#include <linux/iopoll.h>

#define I2C_CTL			0x000
#define I2C_STATUS		0x014
#define ADDR_DVD0		0x020
#define ADDR_DVD1		0x024
#define ADDR_STA0_DVD		0x028
#define ADDR_RST		0x02C

#define HW_CTL			0x030
#define HW_CHNL_PRIL		0x034
#define HW_CHNL_PRIH		0x038
#define CHNL_EN0		0x060
#define CHNL_EN1		0x064
#define ARM_CMD_WR		0x134
#define ARM_DAT_WR		0x138
#define ARM_RD_CMD		0x13C
#define ARM_RD_DATA		0x140
#define ARM_DEBUG0		0x144
#define ARM_DEBUG1		0x148
#define HW_RST			0x14C

/* I2C_CTL */
#define I2C_DVD_OPT		BIT(8)
#define I2C_OUT_OPT		BIT(7)
#define I2C_TRIM_OPT		BIT(6)
#define I2C_HS_MODE		BIT(4)
#define I2C_MODE		BIT(3)
#define I2C_EN			BIT(2)
#define I2C_INT_EN		BIT(1)
#define I2C_START		BIT(0)

/* I2C_STATUS */
#define I2C_INT			BIT(2)
#define I2C_RX_ACK		BIT(1)
#define I2C_BUSY		BIT(0)

/* ADDR_RST */
#define I2C_RST			BIT(0)

/* timeout for pm runtime autosuspend */
#define SPRD_I2C_PM_TIMEOUT	1000	/* ms */

/* HW_CTL */
#define HW_CTL_VALUE		0x30
#define PRIL_HIGH_APB		0x24

/* ARM_CMD_WR */
#define REG_ADDR_OFFSET		2
#define SLAVE_ADDR_OFFSET	10
#define ARM_RD_CMD_BUSY		BIT(31)

/* ARM_DEBUG1 */
#define CHNL_PENDING		BIT(6)
#define CHNL_SEL		GENMASK(4, 0)
#define TIMIMG_MAST_L		GENMASK(15, 0)
#define TIMIMG_MAST_H		GENMASK(31, 16)
#define CHNL_WRITE		0
#define CHNL_READ		1


#define I2C_TIMEOUT		1000
/* Absolutely safe for status update at 100 kHz I2C: */
#define I2C_WAIT		200

/* i2c data structure */
struct sprd_i2c_hw {
	struct i2c_msg *msg;
	struct i2c_adapter adap;
	struct device *dev;
	void __iomem *base;
	struct clk *clk;
	struct clk *clk_hw;
	u32 src_clk;
	int irq;
	u32 bus_freq;
	u8 *buf;
	u32 count;
	int err;
};

static void sprd_i2c_hw_dump_reg(struct sprd_i2c_hw *i2c_dev)
{
	dev_err(&i2c_dev->adap.dev,
		": ======dump i2c-%d reg=======\n", i2c_dev->adap.nr);
	dev_err(&i2c_dev->adap.dev, ": I2C_CTRL:0x%x\n",
		readl(i2c_dev->base + I2C_CTL));
	dev_err(&i2c_dev->adap.dev, ": I2C_STATUS:0x%x\n",
		readl(i2c_dev->base + I2C_STATUS));
	dev_err(&i2c_dev->adap.dev, ": ADDR_DVD0:0x%x\n",
		readl(i2c_dev->base + ADDR_DVD0));
	dev_err(&i2c_dev->adap.dev, ": ADDR_DVD1:0x%x\n",
		readl(i2c_dev->base + ADDR_DVD1));
	dev_err(&i2c_dev->adap.dev, ": ADDR_STA0_DVD:0x%x\n",
		readl(i2c_dev->base + ADDR_STA0_DVD));
	dev_err(&i2c_dev->adap.dev, ": HW_CTL:0x%x\n",
		readl(i2c_dev->base + HW_CTL));
	dev_err(&i2c_dev->adap.dev, ": HW_CHNL_PRIL:0x%x\n",
		readl(i2c_dev->base + HW_CHNL_PRIL));
	dev_err(&i2c_dev->adap.dev, ": CHNL_EN0:0x%x\n",
		readl(i2c_dev->base + CHNL_EN0));
	dev_err(&i2c_dev->adap.dev, ": ARM_CMD_WR:0x%x\n",
		readl(i2c_dev->base + ARM_CMD_WR));
	dev_err(&i2c_dev->adap.dev, ": ARM_DAT_WR:0x%x\n",
		readl(i2c_dev->base + ARM_DAT_WR));
	dev_err(&i2c_dev->adap.dev, ": ARM_RD_CMD:0x%x\n",
		readl(i2c_dev->base + ARM_RD_CMD));
	dev_err(&i2c_dev->adap.dev, ": ARM_DEBUG0:0x%x\n",
		readl(i2c_dev->base + ARM_DEBUG0));
	dev_err(&i2c_dev->adap.dev, ": ARM_DEBUG1:0x%x\n",
		readl(i2c_dev->base + ARM_DEBUG1));
}

static void sprd_i2c_hw_clear_irq(struct sprd_i2c_hw *i2c_dev)
{
	u32 tmp = readl(i2c_dev->base + I2C_STATUS);

	writel(tmp & ~I2C_INT, i2c_dev->base + I2C_STATUS);
}

static int sprd_i2c_hw_writebyte(struct sprd_i2c_hw *i2c_dev, u8 *buf, u32 len)
{
	u32 tmp, status;
	int err, cnt = I2C_TIMEOUT;

	/* only support 2 bytes, 1:reg address; 2:reg data. */
	tmp = i2c_dev->msg->addr << SLAVE_ADDR_OFFSET |
		buf[0] << REG_ADDR_OFFSET;
	sprd_i2c_hw_clear_irq(i2c_dev);

	/* len: 2 write operation, len:1 read operation */
	if (len == 2) {
		writel(tmp, i2c_dev->base + ARM_CMD_WR);
		writel(buf[1], i2c_dev->base + ARM_DAT_WR);
	} else {
		writel(tmp, i2c_dev->base + ARM_RD_CMD);
	}

	/*
	 * if we want to r/w i2c channel, we need poll until it's done,
	 * we need check there is no pending channel or.
	 * even there is pending channel but not channel 0 and 1.
	 */
	do {
		udelay(I2C_WAIT);
		tmp = readl(i2c_dev->base + ARM_DEBUG1);
		if ((!(tmp & CHNL_PENDING) &&
		     ((tmp & CHNL_SEL) == CHNL_WRITE)) ||
		    ((tmp & CHNL_SEL) == CHNL_READ))
			break;

		if ((tmp & CHNL_SEL) == CHNL_WRITE) {
			err = readl_poll_timeout_atomic(
						i2c_dev->base + I2C_STATUS,
						status,
						status & I2C_INT, I2C_WAIT,
						I2C_TIMEOUT);
			if (err) {
				dev_err(&i2c_dev->adap.dev,
					"Timed out for writing int status=0x%04x\n",
					status);
				sprd_i2c_hw_dump_reg(i2c_dev);
				i2c_dev->err = -ETIMEDOUT;
				continue;
			}
		}
	} while ((tmp & CHNL_PENDING) && cnt--);

	if (cnt <= 0) {
		dev_warn(&i2c_dev->adap.dev,
			 "Timed out for writing, timeout=%d, debug1=0x%04x\n",
			 cnt, tmp);
		sprd_i2c_hw_dump_reg(i2c_dev);
		i2c_dev->err = -ETIMEDOUT;
		return i2c_dev->err;
	}

	return 0;
}

static void sprd_i2c_hw_chnl_priority(struct sprd_i2c_hw *i2c_dev)
{
	writel(PRIL_HIGH_APB, i2c_dev->base + HW_CHNL_PRIL);
}

static void sprd_i2c_hw_clear_ack(struct sprd_i2c_hw *i2c_dev)
{
	u32 tmp = readl(i2c_dev->base + I2C_STATUS);

	writel(tmp & ~I2C_RX_ACK, i2c_dev->base + I2C_STATUS);
}

static void sprd_i2c_hw_check_noack(struct sprd_i2c_hw *i2c_dev)
{
	u32 tmp = readl(i2c_dev->base + I2C_STATUS);

	if (tmp & I2C_RX_ACK) {
		dev_warn(&i2c_dev->adap.dev,
			 "i2c report last time: no ack error !\n");
		sprd_i2c_hw_dump_reg(i2c_dev);
		writel(tmp & ~I2C_RX_ACK, i2c_dev->base + I2C_STATUS);
	}
}

static int sprd_i2c_hw_readbyte(struct sprd_i2c_hw *i2c_dev, u8 *buf, u32 len)
{
	int data, i, err;

	for (i = 0; i < len; i++) {
		err = readl_poll_timeout_atomic(i2c_dev->base + ARM_RD_DATA,
						data,
						!(data & ARM_RD_CMD_BUSY),
						I2C_WAIT, I2C_TIMEOUT);
		if (err) {
			dev_err(&i2c_dev->adap.dev,
				"Timed out for reading data=0x%04x\n",
				data);
			sprd_i2c_hw_dump_reg(i2c_dev);
			i2c_dev->err = -ETIMEDOUT;
			return i2c_dev->err;
		}

		buf[i] = data;
	}

	return 0;
}

static int sprd_i2c_hw_handle_msg(struct i2c_adapter *i2c_adap,
				  struct i2c_msg *pmsg)
{
	struct sprd_i2c_hw *i2c_dev = i2c_adap->algo_data;

	i2c_dev->msg = pmsg;
	i2c_dev->buf = pmsg->buf;
	i2c_dev->count = pmsg->len;
	i2c_dev->err = 0;

	sprd_i2c_hw_check_noack(i2c_dev);

	if (i2c_dev->count > 2) {
		dev_err(&i2c_dev->adap.dev,
			"i2c report: only support 1 byte transfer, bytes=%d !!!\n",
			i2c_dev->count);
		return -EINVAL;
	}

	writel(HW_CTL_VALUE, i2c_dev->base + HW_CTL);

	if (pmsg->flags & I2C_M_RD)
		sprd_i2c_hw_readbyte(i2c_dev, i2c_dev->buf, i2c_dev->count);
	else
		sprd_i2c_hw_writebyte(i2c_dev, i2c_dev->buf, i2c_dev->count);

	/* Transmission is done and clear ack */
	sprd_i2c_hw_clear_ack(i2c_dev);

	return i2c_dev->err;
}

static int sprd_i2c_hw_master_xfer(struct i2c_adapter *i2c_adap,
				   struct i2c_msg *msgs, int num)
{
	int im, ret;
	struct sprd_i2c_hw *i2c_dev = i2c_adap->algo_data;

	ret = pm_runtime_get_sync(i2c_dev->dev);
	if (ret < 0)
		return ret;

	for (im = 0; ret >= 0 && im != num; im++) {
		ret = sprd_i2c_hw_handle_msg(i2c_adap, &msgs[im]);
		if (ret)
			goto err_msg;
	}

err_msg:
	pm_runtime_mark_last_busy(i2c_dev->dev);
	pm_runtime_put_autosuspend(i2c_dev->dev);

	return (ret >= 0) ? im : ret;
}

static u32 sprd_i2c_hw_func(struct i2c_adapter *adap)
{
	return I2C_FUNC_SMBUS_BYTE_DATA;
}

static const struct i2c_algorithm sprd_i2c_hw_algo = {
	.master_xfer = sprd_i2c_hw_master_xfer,
	.functionality = sprd_i2c_hw_func,
};

static void  sprd_i2c_hw_set_clk(struct sprd_i2c_hw *i2c_dev, u32 freq)
{
	u32 apb_clk = i2c_dev->src_clk;
	/*
	 * From I2C databook, the prescale calculation formula:
	 * prescale = freq_i2c / (4 * freq_scl) - 1;
	 */
	u32 i2c_dvd = apb_clk / (4 * freq) - 1;
	/*
	 * From I2C databook, the high period of SCL clock is recommended as
	 * 40% (2/5), and the low period of SCL clock is recommended as 60%
	 * (3/5), then the formula should be:
	 * high = (prescale * 2 * 2) / 5
	 * low = (prescale * 2 * 3) / 5
	 */
	u32 high = ((i2c_dvd << 1) * 2) / 5;
	u32 low = ((i2c_dvd << 1) * 3) / 5;
	u32 div0 = (high & TIMIMG_MAST_L) << 16 | (low & TIMIMG_MAST_L);
	u32 div1 =  (high & TIMIMG_MAST_H) | ((low & TIMIMG_MAST_H) >> 16);

	writel(div0, i2c_dev->base + ADDR_DVD0);
	writel(div1, i2c_dev->base + ADDR_DVD1);

	/* Start hold timing = hold time(us) * source clock */
	if (freq == 400000)
		writel((6 * apb_clk) / 10000000, i2c_dev->base + ADDR_STA0_DVD);
	else if (freq == 100000)
		writel((4 * apb_clk) / 1000000, i2c_dev->base + ADDR_STA0_DVD);
}

static void sprd_i2c_hw_enable(struct sprd_i2c_hw *i2c_dev)
{
	u32 tmp = I2C_DVD_OPT;

	writel(tmp, i2c_dev->base + I2C_CTL);
	dev_dbg(&i2c_dev->adap.dev, "freq=%d\n", i2c_dev->bus_freq);

	sprd_i2c_hw_set_clk(i2c_dev, i2c_dev->bus_freq);

	tmp = readl(i2c_dev->base + I2C_CTL);
	writel(tmp | (I2C_EN | I2C_INT_EN), i2c_dev->base + I2C_CTL);
}

static int sprd_i2c_hw_clk_init(struct sprd_i2c_hw *i2c_dev)
{
	struct clk *clk_i2c, *clk_parent;

	clk_i2c = devm_clk_get(i2c_dev->dev, "i2c");
	if (IS_ERR(clk_i2c)) {
		dev_warn(&i2c_dev->adap.dev,
			 "i2c%d can't get the i2c clock\n",
			 i2c_dev->adap.nr);
		clk_i2c = NULL;
	}

	clk_parent = devm_clk_get(i2c_dev->dev, "source");
	if (IS_ERR(clk_parent)) {
		dev_warn(&i2c_dev->adap.dev,
			 "i2c%d can't get the source clock\n",
			 i2c_dev->adap.nr);
		clk_parent = NULL;
	}

	if (clk_set_parent(clk_i2c, clk_parent))
		i2c_dev->src_clk = clk_get_rate(clk_i2c);
	else
		i2c_dev->src_clk = 26000000;

	dev_dbg(&i2c_dev->adap.dev, "i2c%d set source clock is %d\n",
		i2c_dev->adap.nr, i2c_dev->src_clk);

	i2c_dev->clk = devm_clk_get(i2c_dev->dev, "enable");
	if (IS_ERR(i2c_dev->clk)) {
		dev_warn(&i2c_dev->adap.dev,
			 "i2c%d can't get the enable clock\n",
			 i2c_dev->adap.nr);
		i2c_dev->clk = NULL;
	}

	i2c_dev->clk_hw = devm_clk_get(i2c_dev->dev, "clk_hw_i2c");
	if (IS_ERR(i2c_dev->clk_hw)) {
		dev_warn(&i2c_dev->adap.dev,
			 "i2c%d can't get the clk_hw clock\n",
			 i2c_dev->adap.nr);
		i2c_dev->clk_hw = NULL;
	}

	return 0;
}

static int sprd_i2c_hw_probe(struct platform_device *pdev)
{
	int ret;
	u32 prop;
	struct sprd_i2c_hw *i2c_dev;
	struct resource *res;
	struct device_node *np = pdev->dev.of_node;

	if (!np) {
		dev_err(&pdev->dev, "no device node\n");
		return -ENODEV;
	}

	pdev->id = of_alias_get_id(np, "i2c");

	i2c_dev = devm_kzalloc(&pdev->dev, sizeof(struct sprd_i2c_hw),
			       GFP_KERNEL);
	if (!i2c_dev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2c_dev->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2c_dev->base))
		return PTR_ERR(i2c_dev->base);

	i2c_dev->irq = platform_get_irq(pdev, 0);
	if (i2c_dev->irq < 0) {
		dev_err(&pdev->dev, "failed to get irq resource\n");
		return -ENXIO;
	}

	i2c_set_adapdata(&i2c_dev->adap, i2c_dev);
	snprintf(i2c_dev->adap.name, sizeof(i2c_dev->adap.name),
		 "%s", "sprd-i2c-hw");

	i2c_dev->bus_freq = 100000;
	i2c_dev->adap.owner = THIS_MODULE;
	i2c_dev->dev = &pdev->dev;
	i2c_dev->adap.retries = 3;
	i2c_dev->adap.algo = &sprd_i2c_hw_algo;
	i2c_dev->adap.algo_data = i2c_dev;
	i2c_dev->adap.dev.parent = &pdev->dev;
	i2c_dev->adap.nr = pdev->id;
	i2c_dev->adap.dev.of_node = pdev->dev.of_node;

	if (!of_property_read_u32(pdev->dev.of_node, "clock-frequency", &prop))
		i2c_dev->bus_freq = prop;

	sprd_i2c_hw_clk_init(i2c_dev);
	platform_set_drvdata(pdev, i2c_dev);

	ret = clk_prepare_enable(i2c_dev->clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable clk !\n");
		return ret;
	}

	ret = clk_prepare_enable(i2c_dev->clk_hw);
	if (ret) {
		clk_disable_unprepare(i2c_dev->clk);
		dev_err(&pdev->dev, "failed to enable clk_hw !\n");
		return ret;
	}

	sprd_i2c_hw_enable(i2c_dev);
	sprd_i2c_hw_chnl_priority(i2c_dev);

	pm_runtime_set_autosuspend_delay(i2c_dev->dev, SPRD_I2C_PM_TIMEOUT);
	pm_runtime_use_autosuspend(i2c_dev->dev);
	pm_runtime_set_active(i2c_dev->dev);
	pm_runtime_enable(i2c_dev->dev);

	ret = pm_runtime_get_sync(i2c_dev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "i2c%d pm runtime resume failed!\n",
			pdev->id);
		goto err_rpm_put;
	}

	ret = i2c_add_numbered_adapter(&i2c_dev->adap);
	if (ret < 0) {
		dev_err(&pdev->dev, "add_adapter failed!\n");
		goto err_rpm_put;
	}

	pm_runtime_mark_last_busy(i2c_dev->dev);
	pm_runtime_put_autosuspend(i2c_dev->dev);

	return 0;

err_rpm_put:
	pm_runtime_put_noidle(i2c_dev->dev);
	pm_runtime_disable(i2c_dev->dev);
	clk_disable_unprepare(i2c_dev->clk_hw);
	clk_disable_unprepare(i2c_dev->clk);
	return ret;
}

static int sprd_i2c_hw_remove(struct platform_device *pdev)
{
	struct sprd_i2c_hw *i2c_dev = platform_get_drvdata(pdev);
	int ret = pm_runtime_get_sync(i2c_dev->dev);

	if (ret < 0)
		return ret;

	i2c_del_adapter(&i2c_dev->adap);
	clk_disable_unprepare(i2c_dev->clk_hw);
	clk_disable_unprepare(i2c_dev->clk);

	pm_runtime_put_noidle(i2c_dev->dev);
	pm_runtime_disable(i2c_dev->dev);
	return 0;
}

static int __maybe_unused sprd_i2c_hw_suspend_noirq(struct device *pdev)
{
	return pm_runtime_force_suspend(pdev);
}

static int __maybe_unused sprd_i2c_hw_resume_noirq(struct device *pdev)
{
	return pm_runtime_force_resume(pdev);
}

static int __maybe_unused sprd_i2c_hw_runtime_suspend(struct device *pdev)
{
	struct sprd_i2c_hw *i2c_dev = dev_get_drvdata(pdev);

	clk_disable_unprepare(i2c_dev->clk_hw);
	clk_disable_unprepare(i2c_dev->clk);

	return 0;
}

static int __maybe_unused sprd_i2c_hw_runtime_resume(struct device *pdev)
{
	struct sprd_i2c_hw *i2c_dev = dev_get_drvdata(pdev);
	int ret = clk_prepare_enable(i2c_dev->clk);

	if (ret) {
		dev_err(pdev, "clk enable fail !!!\n");
		return ret;
	}

	ret = clk_prepare_enable(i2c_dev->clk_hw);
	if (ret) {
		clk_disable_unprepare(i2c_dev->clk);
		dev_err(pdev, "clk_hw enable fail !!!\n");
		return ret;
	}

	sprd_i2c_hw_enable(i2c_dev);

	return 0;
}

static const struct dev_pm_ops sprd_i2c_hw_pm_ops = {
	SET_RUNTIME_PM_OPS(sprd_i2c_hw_runtime_suspend,
			   sprd_i2c_hw_runtime_resume, NULL)

	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(sprd_i2c_hw_suspend_noirq,
				      sprd_i2c_hw_resume_noirq)
};

static const struct of_device_id sprd_i2c_hw_of_match[] = {
	{ .compatible = "sprd,r9p0-i2c", },
	{},
};

static struct platform_driver sprd_i2c_hw_driver = {
	.probe = sprd_i2c_hw_probe,
	.remove = sprd_i2c_hw_remove,
	.driver = {
		.name = "sprd-i2c-r9p0",
		.of_match_table = sprd_i2c_hw_of_match,
		.pm = &sprd_i2c_hw_pm_ops,
	},
};

static int sprd_i2c_hw_init(void)
{
	return platform_driver_register(&sprd_i2c_hw_driver);
}

arch_initcall_sync(sprd_i2c_hw_init);
