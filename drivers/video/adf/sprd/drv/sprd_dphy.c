/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/err.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_graph.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/pm_runtime.h>
#include <linux/platform_device.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

#include "sprd_dphy.h"
#include "sysfs/sysfs_display.h"

LIST_HEAD(dphy_pll_head);
LIST_HEAD(dphy_ppi_head);
LIST_HEAD(dphy_glb_head);

static int regmap_tst_io_write(void *context, unsigned int reg,
				       unsigned int val)
{
	struct sprd_dphy *dphy = context;

	if (val > 0xff || reg > 0xff)
		return -EINVAL;

	pr_debug("reg = 0x%02x, val = 0x%02x\n", reg, val);

	mipi_dphy_test_write(dphy, reg, val);

	return 0;
}

static int regmap_tst_io_read(void *context, unsigned int reg,
				      unsigned int *val)
{
	struct sprd_dphy *dphy = context;
	int ret;

	if (reg > 0xff)
		return -EINVAL;

	ret = mipi_dphy_test_read(dphy, reg);
	if (ret < 0)
		return ret;

	*val = ret;

	pr_debug("reg = 0x%02x, val = 0x%02x\n", reg, *val);
	return 0;
}

static struct regmap_bus regmap_tst_io = {
	.reg_write = regmap_tst_io_write,
	.reg_read = regmap_tst_io_read,
};

static const struct regmap_config byte_config = {
	.reg_bits = 8,
	.val_bits = 8,
};

static const struct regmap_config word_config = {
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
};

static int dphy_regmap_init(struct sprd_dphy *dphy)
{
	struct dphy_context *ctx = &dphy->ctx;
	struct regmap *regmap;

	if (ctx->apbbase)
		regmap = devm_regmap_init_mmio(&dphy->dev,
			(void __iomem *)ctx->apbbase, &word_config);
	else
		regmap = devm_regmap_init(&dphy->dev, &regmap_tst_io,
					  dphy, &byte_config);

	if (IS_ERR(regmap)) {
		pr_err("dphy regmap init failed\n");
		return PTR_ERR(regmap);
	}

	ctx->regmap = regmap;

	return 0;
}

static int dphy_device_register(struct sprd_dphy *dphy,
				struct device *parent)
{
	int ret;

	dphy->dev.class = display_class;
	dphy->dev.parent = parent;
	dphy->dev.of_node = parent->of_node;
	dev_set_name(&dphy->dev, "dphy%d", dphy->ctx.id);
	dev_set_drvdata(&dphy->dev, dphy);

	ret = device_register(&dphy->dev);
	if (ret)
		pr_err("dphy device register failed\n");

	return ret;
}

static int sprd_dphy_resume(struct sprd_dphy *dphy)
{
	int ret;

	if (dphy->glb && dphy->glb->power)
		dphy->glb->power(&dphy->ctx, true);
	if (dphy->glb && dphy->glb->enable)
		dphy->glb->enable(&dphy->ctx);

	ret = mipi_dphy_configure(dphy);
	if (ret) {
		pr_err("sprd dphy init failed\n");
		return -EINVAL;
	}

	pr_info("dphy resume OK\n");
	return ret;
}

static int sprd_dphy_suspend(struct sprd_dphy *dphy)
{
	int ret;

	ret = mipi_dphy_close(dphy);
	if (ret)
		pr_err("sprd dphy close failed\n");

	if (dphy->glb && dphy->glb->disable)
		dphy->glb->disable(&dphy->ctx);
	if (dphy->glb && dphy->glb->power)
		dphy->glb->power(&dphy->ctx, false);

	pr_info("dphy suspend OK\n");
	return ret;
}

static int dphy_context_init(struct sprd_dphy *dphy,
				struct device_node *np)
{
	struct resource r;
	uint32_t tmp;

	dphy->ctx.chip_id = 0xffffffff;

	if (dphy->glb && dphy->glb->parse_dt)
		dphy->glb->parse_dt(&dphy->ctx, np);

	dphy->ctx.freq = dphy->panel->phy_freq;
	dphy->ctx.lanes = dphy->panel->lane_num;

	if (!of_address_to_resource(np, 0, &r)) {
		dphy->ctx.ctrlbase = (unsigned long)
		    ioremap_nocache(r.start, resource_size(&r));
		if (dphy->ctx.ctrlbase == 0) {
			pr_err("dphy ctrlbase ioremap failed\n");
			return -EFAULT;
		}
	} else {
		pr_err("parse dphy ctrl reg base failed\n");
		return -EINVAL;
	}

	if (!of_address_to_resource(np, 1, &r)) {
		pr_info("this dphy has apb reg base\n");
		dphy->ctx.apbbase = (unsigned long)
		    ioremap_nocache(r.start, resource_size(&r));
		if (dphy->ctx.apbbase == 0) {
			pr_err("dphy apbbase ioremap failed\n");
			return -EFAULT;
		}
	}

	if (!of_property_read_u32(np, "dev-id", &tmp))
		dphy->ctx.id = tmp;
	mutex_init(&dphy->ctx.hop_lock);
	return 0;
}

static int sprd_dphy_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct sprd_dphy *dphy;
	struct device *dsi_dev;
	const char *str;

	dphy = kzalloc(sizeof(struct sprd_dphy), GFP_KERNEL);
	if (!dphy)
		return -ENOMEM;

	dphy->panel = platform_get_drvdata(pdev);
	if (dphy->panel == NULL) {
		pr_err("error: dphy->panel is null\n");
		goto err;
	}
	dsi_dev = dev_get_prev(&pdev->dev);
	if (!dsi_dev)
		goto err;
	dev_set_drvdata(dsi_dev, dphy->panel);

	if (!of_property_read_string(dsi_dev->of_node, "sprd,ip", &str))
		dphy->ppi = dphy_ppi_ops_attach(str);
	else
		pr_err("error: dphy ppi ops parse failed\n");

	if (!of_property_read_string(np, "sprd,ip", &str))
		dphy->pll = dphy_pll_ops_attach(str);
	else
		pr_err("error: dphy pll ops parse failed\n");

	if (!of_property_read_string(np, "sprd,soc", &str))
		dphy->glb = dphy_glb_ops_attach(str);
	else
		pr_err("error: dphy glb ops parse failed\n");

	if (dphy_context_init(dphy, pdev->dev.of_node))
		goto err;

	dphy_device_register(dphy, &pdev->dev);
	sprd_dphy_sysfs_init(&dphy->dev);
	dphy_regmap_init(dphy);
	platform_set_drvdata(pdev, dphy);

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_get_noresume(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	pr_info("dphy driver probe success\n");

	return 0;

err:
	kfree(dphy);
	return -ENODEV;
}

static int dphy_runtime_resume(struct device *dev)
{
	struct sprd_dphy *dphy = dev_get_drvdata(dev);
	struct device *next = dev_get_next(dev);

	sprd_dphy_resume(dphy);
	pm_runtime_get_sync(next);

	return 0;
}

static int dphy_runtime_suspend(struct device *dev)
{
	struct sprd_dphy *dphy = dev_get_drvdata(dev);
	struct device *next = dev_get_next(dev);

	pm_runtime_put_sync(next);
	sprd_dphy_suspend(dphy);

	return 0;
}

static const struct dev_pm_ops dphy_pm_ops = {
	.runtime_suspend = dphy_runtime_suspend,
	.runtime_resume = dphy_runtime_resume,
};

static const struct of_device_id dt_ids[] = {
	{ .compatible = "sprd,mipi-dsi-phy", },
	{},
};

static struct platform_driver sprd_dphy_driver = {
	.probe	= sprd_dphy_probe,
	.driver = {
		.name  = "sprd-dphy",
		.of_match_table	= of_match_ptr(dt_ids),
		.pm = &dphy_pm_ops,
	}
};

module_platform_driver(sprd_dphy_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("infi.chen <infi.chen@spreadtrum.com>");
MODULE_AUTHOR("Leon He <leon.he@spreadtrum.com>");
MODULE_DESCRIPTION("Spreadtrum SoC MIPI DSI PHY driver");
