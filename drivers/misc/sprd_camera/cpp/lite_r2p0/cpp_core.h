/*
 * Copyright (C) 2015-2016 Spreadtrum Communications Inc.
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
#ifndef _CPP_CORE_H_
#define _CPP_CORE_H_

#include <linux/types.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <video/sprd_mm.h>
#include <linux/dma-buf.h>
#include <linux/scatterlist.h>
#include <linux/sprd_iommu.h>
#include <linux/sprd_ion.h>

struct cpp_iommu_info {
	struct device *dev;
	unsigned int mfd[3];
	struct sg_table *table[3];
	void *buf[3];
	size_t size[3];
	unsigned long iova[3];
	struct dma_buf *dmabuf_p[3];
	unsigned int offset[3];
};

struct cpp_addr {
	void __iomem *io_base;
	long reserved;
};
void cpp_print_reg(void *);
int cpp_get_sg_table(struct cpp_iommu_info *pfinfo);
int cpp_get_addr(struct cpp_iommu_info *pfinfo);
int cpp_free_addr(struct cpp_iommu_info *pfinfo);
struct file *sprd_cpp_k_open(void);
int sprd_cpp_k_close(struct file *filp);
int rot_k_start(struct file *file, void *rot_param);
int scale_k_start(struct file *file, void *scale_param);

#endif

