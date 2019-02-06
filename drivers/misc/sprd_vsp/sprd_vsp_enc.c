/*
 * Copyright (C) 2012--2015 Spreadtrum Communications Inc.
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

#include <linux/cdev.h>
#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/mfd/syscon/sprd-glb.h>
#include <linux/mfd/syscon.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/sprd_iommu.h>
#include <linux/sprd_ion.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/wait.h>
#include <linux/wakelock.h>
#include <linux/compat.h>
#include <uapi/video/sprd_vsp.h>
#include <uapi/video/sprd_vsp_pw_domain.h>
#include "vsp_common.h"

#define VSP_MINOR MISC_DYNAMIC_MINOR
#define VSP_AQUIRE_TIMEOUT_MS 500
#define VSP_INIT_TIMEOUT_MS 200
#define DEFAULT_FREQ_DIV 0x0

#define ARM_INT_STS_OFF                 0x10
#define ARM_INT_MASK_OFF                0x14
#define ARM_INT_CLR_OFF                 0x18
#define ARM_INT_RAW_OFF                 0x1C

#define VSP_INT_STS_OFF         0x0
#define VSP_INT_MASK_OFF        0x04
#define VSP_INT_CLR_OFF         0x08
#define VSP_INT_RAW_OFF         0x0c

static unsigned long sprd_vsp_phys_addr;
static unsigned long sprd_vsp_base;
static unsigned long vsp_glb_reg_base;
static unsigned int vsp_softreset_reg_offset;
static unsigned int vsp_reset_mask;

static struct vsp_dev_t vsp_hw_dev;
static struct wake_lock vsp_wakelock;
static atomic_t vsp_instance_cnt = ATOMIC_INIT(0);

static struct clock_name_map_t clock_name_map[SPRD_VSP_CLK_LEVEL_NUM];

static int max_freq_level = SPRD_VSP_CLK_LEVEL_NUM;

static irqreturn_t vsp_isr(int irq, void *data);

static long vsp_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	u32 mm_eb_reg;
	struct clk *clk_parent;
	unsigned long frequency;
	struct vsp_iommu_map_data mapdata;
	struct vsp_iommu_map_data ummapdata;
	struct vsp_fh *vsp_fp = filp->private_data;

	if (vsp_fp == NULL) {
		pr_err("vsp_ioctl error occurred, vsp_fp == NULL\n");
		return -EINVAL;
	}

	switch (cmd) {
	case VSP_CONFIG_FREQ:
		get_user(vsp_hw_dev.freq_div, (int __user *)arg);
		clk_parent = vsp_get_clk_src_name(clock_name_map,
				vsp_hw_dev.freq_div, max_freq_level);
		vsp_hw_dev.vsp_parent_clk = clk_parent;
		pr_debug("VSP_CONFIG_FREQ %d\n", vsp_hw_dev.freq_div);
		break;

	case VSP_GET_FREQ:
		frequency = clk_get_rate(vsp_hw_dev.vsp_clk);
		ret = find_vsp_freq_level(clock_name_map,
			frequency, max_freq_level);
		put_user(ret, (int __user *)arg);
		pr_debug("vsp ioctl VSP_GET_FREQ %d\n", ret);
		break;

	case VSP_ENABLE:
		pr_debug("vsp_enc ioctl VSP_ENABLE\n");
		wake_lock(&vsp_wakelock);

		ret = vsp_clk_enable(&vsp_hw_dev);
		if (ret == 0)
			vsp_fp->is_clock_enabled = 1;
		if (vsp_hw_dev.iommu_exist_flag)
			sprd_iommu_resume(vsp_hw_dev.vsp_dev);
		break;

	case VSP_DISABLE:
		pr_debug("vsp ioctl VSP_DISABLE\n");
		if (vsp_hw_dev.iommu_exist_flag)
			sprd_iommu_suspend(vsp_hw_dev.vsp_dev);
		if (vsp_fp->is_clock_enabled == 1)
			vsp_clk_disable(&vsp_hw_dev);

		vsp_fp->is_clock_enabled = 0;
		wake_unlock(&vsp_wakelock);
		break;

	case VSP_ACQUAIRE:
		pr_debug("vsp_enc ioctl VSP_ACQUAIRE begin\n");
		ret = down_timeout(&vsp_hw_dev.vsp_mutex,
				   msecs_to_jiffies(VSP_AQUIRE_TIMEOUT_MS));
		if (ret) {
			pr_err("vsp error timeout\n");
			/* up(&vsp_hw_dev.vsp_mutex); */
			return ret;
		}

		vsp_hw_dev.vsp_fp = vsp_fp;

		vsp_fp->is_vsp_aquired = 1;
		pr_debug("vsp_enc ioctl VSP_ACQUAIRE end\n");
		break;

	case VSP_RELEASE:
		pr_debug("vsp_enc ioctl VSP_RELEASE\n");

		vsp_fp->is_vsp_aquired = 0;
		vsp_hw_dev.vsp_fp = NULL;
		up(&vsp_hw_dev.vsp_mutex);
		break;

	case VSP_COMPLETE:
		pr_debug("vsp_enc ioctl VSP_COMPLETE\n");
		ret = wait_event_interruptible_timeout(vsp_fp->wait_queue_work,
						       vsp_fp->condition_work,
						       msecs_to_jiffies
						       (VSP_INIT_TIMEOUT_MS));
		if (ret == -ERESTARTSYS) {
			pr_info("vsp complete -ERESTARTSYS\n");
			vsp_fp->vsp_int_status |= (1 << 30);
			put_user(vsp_fp->vsp_int_status, (int __user *)arg);
			ret = -EINVAL;
		} else {
			vsp_fp->vsp_int_status &= (~(1 << 30));
			if (ret == 0) {
				pr_err("vsp complete  timeout 0x%x\n",
				       readl_relaxed((void *)(vsp_glb_reg_base +
						VSP_INT_RAW_OFF)));
				vsp_fp->vsp_int_status |= (1 << 31);
				ret = -ETIMEDOUT;
				/* clear vsp int */
				writel_relaxed((1 << 1) | (1 << 2) | (1 << 4) |
					       (1 << 5),
					       (void *)(vsp_glb_reg_base +
							VSP_INT_CLR_OFF));
				writel_relaxed((1 << 0) | (1 << 1) | (1 << 2),
					       (void *)(sprd_vsp_base +
							ARM_INT_CLR_OFF));
			} else {
				ret = 0;
			}
			put_user(vsp_fp->vsp_int_status, (int __user *)arg);
			vsp_fp->vsp_int_status = 0;
			vsp_fp->condition_work = 0;
		}
		pr_debug("vsp_enc ioctl VSP_COMPLETE end\n");
		break;

	case VSP_RESET:
		pr_debug("vsp_enc ioctl VSP_RESET\n");

		regmap_update_bits(gpr_mm_ahb, vsp_softreset_reg_offset,
				   vsp_reset_mask, vsp_reset_mask);
		regmap_update_bits(gpr_mm_ahb, vsp_softreset_reg_offset,
				   vsp_reset_mask, 0);
		break;

	case VSP_HW_INFO:

		pr_debug("vsp ioctl VSP_HW_INFO\n");

		regmap_read(gpr_aon_apb, REG_AON_APB_APB_EB0, &mm_eb_reg);

		put_user(mm_eb_reg, (int __user *)arg);

		break;

	case VSP_VERSION:

		pr_debug("vsp version -enter\n");
		put_user(vsp_hw_dev.version, (int __user *)arg);

		break;

	case VSP_GET_IOMMU_STATUS:

		ret = sprd_iommu_attach_device(vsp_hw_dev.vsp_dev);

		break;

	case VSP_GET_IOVA:

		ret =
		    copy_from_user((void *)&mapdata,
				   (const void __user *)arg,
				   sizeof(struct vsp_iommu_map_data));
		if (ret) {
			pr_err("copy mapdata failed, ret %d\n", ret);
			return ret;
		}

		ret = vsp_get_iova(&vsp_hw_dev, &mapdata,
					(void __user *)arg);

		break;

	case VSP_FREE_IOVA:

		ret =
		    copy_from_user((void *)&ummapdata,
				   (const void __user *)arg,
				   sizeof(struct vsp_iommu_map_data));
		if (ret) {
			pr_err("copy ummapdata failed, ret %d\n", ret);
			return ret;
		}

		ret = vsp_free_iova(&vsp_hw_dev, &ummapdata);

		break;

	case VSP_SET_CODEC_ID:
		get_user(vsp_fp->codec_id, (int __user *)arg);
		codec_instance_count[vsp_fp->codec_id]++;
		pr_debug("set codec_id %d counter %d\n", vsp_fp->codec_id,
			codec_instance_count[vsp_fp->codec_id]);
		break;

	case VSP_GET_CODEC_COUNTER:

		put_user(codec_instance_count[vsp_fp->codec_id],
			(int __user *)arg);
		pr_debug("total vsp_enc counter %d\n",
			codec_instance_count[vsp_fp->codec_id]);
		break;

	default:
		pr_err("bad vsp_enc-ioctl cmd %d\n", cmd);
		return -EINVAL;
	}

	return ret;
}

static irqreturn_t vsp_isr(int irq, void *data)
{
	int int_status;
	int ret = 0xff;		/* 0xff : invalid */
	struct vsp_fh *vsp_fp = vsp_hw_dev.vsp_fp;

	if (vsp_fp == NULL) {
		pr_err("vsp_isr error occurred, vsp_fp == NULL\n");
		return IRQ_NONE;
	}
	/* check which module occur interrupt and clear coresponding bit */
	int_status =
	    readl_relaxed((void *)(vsp_glb_reg_base + VSP_INT_STS_OFF));
	if ((int_status >> 0) & 0x1) {
		/* BSM_BUF_OVF DONE */
		writel_relaxed((1 << 0),
			       (void *)(vsp_glb_reg_base + VSP_INT_CLR_OFF));
		ret = (1 << 0);
	} else if ((int_status >> 1) & 0x1) {
		/* VLC SLICE DONE */
		writel_relaxed((1 << 1),
			       (void *)(vsp_glb_reg_base + VSP_INT_CLR_OFF));
		ret = (1 << 1);
	} else if ((int_status >> 2) & 0x1) {
		/* MBW SLICE DONE */
		writel_relaxed((1 << 2),
			       (void *)(vsp_glb_reg_base + VSP_INT_CLR_OFF));
		ret = (1 << 2);
	} else if ((int_status >> 4) & 0x1) {
		/* VLD ERR */
		writel_relaxed((1 << 4),
			       (void *)(vsp_glb_reg_base + VSP_INT_CLR_OFF));
		ret = (1 << 4);
	} else if ((int_status >> 5) & 0x1) {
		/* TIMEOUT ERR */
		writel_relaxed((1 << 5),
			       (void *)(vsp_glb_reg_base + VSP_INT_CLR_OFF));
		ret = (1 << 5);
	} else
		return IRQ_NONE;

	/* clear VSP accelerator interrupt bit */
	int_status = readl_relaxed((void *)(sprd_vsp_base + ARM_INT_STS_OFF));
	if ((int_status >> 2) & 0x1) {
		/* VSP ACC INT */
		writel_relaxed((1 << 2),
			       (void *)(sprd_vsp_base + ARM_INT_CLR_OFF));
	}

	if (vsp_fp != NULL) {
		vsp_fp->vsp_int_status = ret;
		vsp_fp->condition_work = 1;
		wake_up_interruptible(&vsp_fp->wait_queue_work);
	}

	return IRQ_HANDLED;
}

struct sprd_vsp_cfg_data whale2_vsp_enc_data = {
	.version = WHALE2,
	.max_freq_level = 4,
	.softreset_reg_offset = 0x4,
	.reset_mask = BIT(4),
};

static const struct of_device_id of_match_table_vsp[] = {
	{.compatible = "sprd,whale2-vsp-enc", .data = &whale2_vsp_enc_data},
	{},
};

static int vsp_parse_dt(struct platform_device *pdev)
{
	struct device *dev = &(pdev->dev);
	struct device_node *np = dev->of_node;
	struct device_node *vsp_clk_np = NULL;
	struct resource *res;
	int i, clk_count = 0;
	const char *clk_name;
	const char *clk_compitale = "sprd,muxed-clock";

	pr_info("vsp_enc_parse_dt called !\n");

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "no reg of property specified\n");
		pr_err("vsp: failed to parse_dt!\n");
		return -EINVAL;
	}

	sprd_vsp_phys_addr = res->start;
	sprd_vsp_base = (unsigned long)devm_ioremap_resource(&pdev->dev, res);
	if (!sprd_vsp_base)
		BUG();

	vsp_glb_reg_base = sprd_vsp_base + 0x1000;

	pr_info("sprd_vsp_enc_phys_addr = %lx\n", sprd_vsp_phys_addr);
	pr_info("sprd_vsp_enc_base = %lx\n", sprd_vsp_base);
	pr_info("vsp_enc_glb_reg_base = %lx\n", vsp_glb_reg_base);

	vsp_hw_dev.version = vsp_hw_dev.vsp_cfg_data->version;
	max_freq_level = vsp_hw_dev.vsp_cfg_data->max_freq_level;
	vsp_softreset_reg_offset =
	    vsp_hw_dev.vsp_cfg_data->softreset_reg_offset;
	vsp_reset_mask = vsp_hw_dev.vsp_cfg_data->reset_mask;

	vsp_hw_dev.irq = platform_get_irq(pdev, 0);
	vsp_hw_dev.dev_np = np;
	vsp_hw_dev.vsp_dev = dev;

	pr_info("vsp_enc: irq = 0x%x, version = 0x%0x\n", vsp_hw_dev.irq,
		vsp_hw_dev.version);

	gpr_aon_apb =
	    syscon_regmap_lookup_by_phandle(np, "sprd,syscon-aon-apb");
	if (IS_ERR(gpr_aon_apb))
		pr_err("%s:failed to find vsp,aon-apb\n", __func__);

	gpr_mm_ahb = syscon_regmap_lookup_by_phandle(np, "sprd,syscon-mm-ahb");
	if (IS_ERR(gpr_mm_ahb))
		pr_err("%s:failed to find vsp,mm-ahb\n", __func__);

	clk_compitale = "sprd,composite-clock";
	for_each_compatible_node(vsp_clk_np, NULL, clk_compitale) {
		if (of_property_read_string_index
		    (vsp_clk_np, "clock-output-names", 0, &clk_name) < 0)
			continue;
		if (!strcmp(clk_name, "clk_vsp_enc")) {
			pr_info("clk [%s], device node: %p\n", clk_name,
				vsp_clk_np);
			break;
		}
	}

	clk_count = of_clk_get_parent_count(vsp_clk_np);
	if (clk_count != max_freq_level) {
		pr_err("failed to get vsp_enc clock count\n");
		return -EINVAL;
	}

	for (i = 0; i < clk_count; i++) {
		struct clk *clk_parent;
		char *name_parent;
		unsigned long frequency;

		name_parent = (char *)of_clk_get_parent_name(vsp_clk_np, i);
		clk_parent = of_clk_get(vsp_clk_np, i);
		frequency = clk_get_rate(clk_parent);
		pr_info("vsp_enc clk in dts file: clk[%d] = (%ld, %s)\n", i,
			frequency, name_parent);

		clock_name_map[i].name = name_parent;
		clock_name_map[i].freq = frequency;
		clock_name_map[i].clk_parent = clk_parent;
	}

	vsp_hw_dev.iommu_exist_flag =
		(sprd_iommu_attach_device(vsp_hw_dev.vsp_dev) == 0) ? 1 : 0;
	pr_info("iommu_vsp_enc enabled %d\n", vsp_hw_dev.iommu_exist_flag);

	return 0;
}

static int vsp_nocache_mmap(struct file *filp, struct vm_area_struct *vma)
{
	pr_info("@vsp[%s]\n", __func__);
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_pgoff = (sprd_vsp_phys_addr >> PAGE_SHIFT);
	if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			    vma->vm_end - vma->vm_start, vma->vm_page_prot))
		return -EAGAIN;
	pr_info("@vsp_enc mmap %x,%lx,%x\n", (unsigned int)PAGE_SHIFT,
		(unsigned long)vma->vm_start,
		(unsigned int)(vma->vm_end - vma->vm_start));
	return 0;
}

static int vsp_open(struct inode *inode, struct file *filp)
{
	int ret;
	struct vsp_fh *vsp_fp = kmalloc(sizeof(struct vsp_fh), GFP_KERNEL);
	int instance_cnt = atomic_read(&vsp_instance_cnt);

	pr_info("vsp_enc_open called %p,vsp_instance_cnt %d\n",
		vsp_fp, instance_cnt);

	if (vsp_fp == NULL) {
		pr_err("vsp open error occured\n");
		return -EINVAL;
	}
	filp->private_data = vsp_fp;
	vsp_fp->is_clock_enabled = 0;
	vsp_fp->is_vsp_aquired = 0;

	init_waitqueue_head(&vsp_fp->wait_queue_work);
	vsp_fp->vsp_int_status = 0;
	vsp_fp->condition_work = 0;

	vsp_pw_on(VSP_PW_DOMAIN_VSP_ENC);

	ret = vsp_get_mm_clk(&vsp_hw_dev);

	atomic_inc_return(&vsp_instance_cnt);

	pr_info("vsp_enc open: ret %d\n", ret);

	return ret;
}

static int vsp_release(struct inode *inode, struct file *filp)
{
	struct vsp_fh *vsp_fp = filp->private_data;
	int instance_cnt = atomic_read(&vsp_instance_cnt);

	if (vsp_fp == NULL) {
		pr_err("vsp_enc release error occured, vsp_fp == NULL\n");
		return -EINVAL;
	}

	pr_info("vsp_enc release: instance_cnt %d\n", instance_cnt);

	atomic_dec_return(&vsp_instance_cnt);

	if (vsp_fp->is_clock_enabled) {
		pr_err("error occurred and close clock\n");
		vsp_clk_disable(&vsp_hw_dev);
		vsp_fp->is_clock_enabled = 0;
	}

	if (vsp_fp->is_vsp_aquired) {
		pr_err("error occurred and up vsp_mutex\n");
		up(&vsp_hw_dev.vsp_mutex);
	}

	vsp_pw_off(VSP_PW_DOMAIN_VSP_ENC);

	pr_info("vsp_enc release %p\n", vsp_fp);
	kfree(filp->private_data);
	filp->private_data = NULL;

	return 0;
}

static const struct file_operations vsp_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = vsp_ioctl,
	.mmap = vsp_nocache_mmap,
	.open = vsp_open,
	.release = vsp_release,
	.unlocked_ioctl = vsp_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = compat_vsp_ioctl,
#endif
};

static struct miscdevice vsp_dev = {
	.minor = VSP_MINOR,
	.name = "sprd_vsp_enc",
	.fops = &vsp_fops,
};

static int vsp_probe(struct platform_device *pdev)
{
	int ret;
	struct device_node *node = pdev->dev.of_node;
	const struct of_device_id *of_id;

	pr_info("vsp_enc probe called !\n");

	of_id = of_match_node(of_match_table_vsp, node);
	if (of_id)
		vsp_hw_dev.vsp_cfg_data =
		    (struct sprd_vsp_cfg_data *)of_id->data;
	else
		panic("%s: Not find matched id!", __func__);

	if (pdev->dev.of_node) {
		if (vsp_parse_dt(pdev)) {
			pr_err("vsp_parse_dt failed\n");
			return -EINVAL;
		}
	}

	wake_lock_init(&vsp_wakelock, WAKE_LOCK_SUSPEND,
		       "pm_message_wakelock_vsp");

	sema_init(&vsp_hw_dev.vsp_mutex, 1);

	vsp_hw_dev.freq_div = max_freq_level;

	vsp_hw_dev.vsp_clk = NULL;
	vsp_hw_dev.clk_ahb_vsp = NULL;
	vsp_hw_dev.clk_emc_vsp = NULL;
	vsp_hw_dev.vsp_parent_clk = NULL;
	vsp_hw_dev.clk_mm_eb = NULL;
	vsp_hw_dev.clk_axi_gate_vsp = NULL;
	vsp_hw_dev.clk_ahb_gate_vsp_eb = NULL;
	vsp_hw_dev.clk_vsp_ckg = NULL;
	vsp_hw_dev.vsp_fp = NULL;
	vsp_hw_dev.light_sleep_en = false;
	codec_instance_count[VSP_ENC] = 0;

	ret = misc_register(&vsp_dev);
	if (ret) {
		pr_err("cannot register miscdev on minor=%d (%d)\n",
		       VSP_MINOR, ret);
		goto errout;
	}

	/* register isr */
	ret =
	    devm_request_irq(&pdev->dev, vsp_hw_dev.irq, vsp_isr,
			     0, "VSP_ENC", &vsp_hw_dev);
	if (ret) {
		pr_err("vsp: failed to request irq!\n");
		ret = -EINVAL;
		goto errout;
	}

	return 0;

errout:
	misc_deregister(&vsp_dev);

	return ret;
}

static int vsp_remove(struct platform_device *pdev)
{
	pr_info("vsp_remove called !\n");

	misc_deregister(&vsp_dev);

	free_irq(vsp_hw_dev.irq, &vsp_hw_dev);

	if (vsp_hw_dev.vsp_parent_clk)
		clk_put(vsp_hw_dev.vsp_parent_clk);

	if (vsp_hw_dev.vsp_clk)
		clk_put(vsp_hw_dev.vsp_clk);

	if (vsp_hw_dev.clk_ahb_vsp)
		clk_put(vsp_hw_dev.clk_ahb_vsp);

	if (vsp_hw_dev.clk_emc_vsp)
		clk_put(vsp_hw_dev.clk_emc_vsp);

	if (vsp_hw_dev.clk_ahb_gate_vsp_eb)
		clk_put(vsp_hw_dev.clk_ahb_gate_vsp_eb);

	if (vsp_hw_dev.clk_axi_gate_vsp)
		clk_put(vsp_hw_dev.clk_axi_gate_vsp);

	if (vsp_hw_dev.clk_vsp_ckg)
		clk_put(vsp_hw_dev.clk_vsp_ckg);

	if (vsp_hw_dev.clk_mm_eb)
		clk_put(vsp_hw_dev.clk_mm_eb);

	pr_info("vsp_remove Success !\n");
	return 0;
}

static struct platform_driver vsp_driver = {
	.probe = vsp_probe,
	.remove = vsp_remove,

	.driver = {
		   .owner = THIS_MODULE,
		   .name = "sprd_vsp_enc",
		   .of_match_table = of_match_ptr(of_match_table_vsp),
		   },
};

module_platform_driver(vsp_driver);

MODULE_DESCRIPTION("SPRD VSP_ENC Driver");
MODULE_LICENSE("GPL");
