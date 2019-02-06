/*
 * Copyright (C) 2016 Spreadtrum Communications Inc.
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

#include <linux/interrupt.h>
#include "isp_int.h"
#include "isp_buf.h"
#include "isp_path.h"
#include "isp_block.h"
#include "isp_slw.h"
#include "isp_3dnr.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "ISP_INT: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__


static isp_isr_func p_user_func[ISP_ID_MAX][ISP_IMG_MAX];
static void *p_user_data[ISP_ID_MAX][ISP_IMG_MAX];
static spinlock_t irq_ch0_lock[ISP_MAX_COUNT];
static spinlock_t irq_ch1_lock[ISP_MAX_COUNT];

#define ISP_ZSL_BUF_NUM 2
#define ISP_HDR_NUM 3
#define ISP_3DNR_NUM 5

const unsigned int isp_ch0_irq_vect0[] = {
	ISP_INT_ISP_ALL_DONE,
	ISP_INT_SHADOW_DONE,
	ISP_INT_AEM_DONE,
	ISP_INT_AEM_START,
	ISP_INT_AEM_ERROR,
	ISP_INT_AFL_DONE,
	ISP_INT_AFL_START,
	ISP_INT_AFL_ERROR,
	ISP_INT_BINNING_DONE,
	ISP_INT_BINNING_START,
	ISP_INT_BINNING_ERROR,
	ISP_INT_PDAF_MEM_LEFT_DONE,
	ISP_INT_PDAF_MEM_RIGHT_DONE,
	ISP_INT_PDAF_DDR_START,
	ISP_INT_PDAF_SHADOW_DONE,
	ISP_INT_DCAM_SOF,
};

const unsigned int isp_ch0_irq_vect1[] = {
	ISP_INT_STORE_DONE_OUT,
	ISP_INT_SHADOW_DONE_OUT,
	ISP_INT_STORE_DONE_CAP,
	ISP_INT_SHADOW_DONE_CAP,
	ISP_INT_STORE_DONE_VID,
	ISP_INT_SHADOW_DONE_VID,
	ISP_INT_STORE_DONE_PRE,
	ISP_INT_SHADOW_DONE_PRE,
	ISP_INT_STORE_DONE_CCE,
	ISP_INT_SHADOW_DONE_CCE,
};

const unsigned int isp_ch0_irq_vect2[] = {
	ISP_INT_AFM_RGB_DONE,
	ISP_INT_AFM_RGB_START,
	ISP_INT_NR3_DONE,
	ISP_INT_FMCU_CONFIG_DONE,
	ISP_INT_FMCU_SHADOW_DONE,
};

static const unsigned int isp_ch1_irq_vect1[] = {
	ISP_INT_STORE_DONE_CAP,
};

const unsigned int isp_ch1_irq_vect2[] = {
	ISP_INT_NR3_DONE,
	ISP_INT_FMCU_CONFIG_DONE,
};

int isp_set_next_statis_buf(enum isp_id idx, struct isp_statis_module *module,
			    enum isp_3a_block_id block_index)
{
	int rtn = 0;
	struct isp_statis_frm_queue *statis_heap = NULL;
	struct isp_statis_buf_queue *p_buf_queue = NULL;
	struct isp_statis_buf *reserved_buf = NULL;
	struct isp_statis_buf node;
	int use_reserve_buf = 0;
	unsigned int statis_addr = 0;

	memset(&node, 0, sizeof(struct isp_statis_buf));
	if (block_index == ISP_AEM_BLOCK) {
		p_buf_queue = &module->aem_statis_queue;
		statis_heap = &module->aem_statis_frm_queue;
		reserved_buf = &module->aem_buf_reserved;
	} else if (block_index == ISP_AFL_BLOCK) {
		p_buf_queue = &module->afl_statis_queue;
		statis_heap = &module->afl_statis_frm_queue;
		reserved_buf = &module->afl_buf_reserved;
	} else if (block_index == ISP_PDAF_BLOCK) {
		p_buf_queue = &module->pdaf_statis_queue;
		statis_heap = &module->pdaf_statis_frm_queue;
		reserved_buf = &module->pdaf_buf_reserved;
	} else if (block_index == ISP_AFM_BLOCK) {
		p_buf_queue = &module->afm_statis_queue;
		statis_heap = &module->afm_statis_frm_queue;
		reserved_buf = &module->afm_buf_reserved;
	} else if (block_index == ISP_BINNING_BLOCK) {
		p_buf_queue = &module->binning_statis_queue;
		statis_heap = &module->binning_statis_frm_queue;
		reserved_buf = &module->binning_buf_reserved;
	}

	/*read buf addr from in_buf_queue*/
	if (isp_statis_queue_read(p_buf_queue, &node) != 0) {
		DCAM_TRACE("statis NO free buf\n");
		/*use reserved buffer*/
		if (reserved_buf->pfinfo.mfd[0] == 0)
			pr_info("NO need to cfg statis buf\n");

		memcpy(&node, reserved_buf, sizeof(struct isp_statis_buf));
		use_reserve_buf = 1;
	};

	if (node.pfinfo.dev == NULL)
		pr_debug("dev is NULL.\n");

	/*call iommu func*/
	statis_addr = node.pfinfo.iova[0];
	/*enqueue the statis buf into the array*/
	rtn = isp_statis_enqueue(statis_heap, &node);
	if (rtn) {
		pr_err("fail to enqueue statis buf\n");
		return rtn;
	}
	/*update buf addr to isp ddr addr*/
	if (block_index == ISP_AEM_BLOCK) {
		ISP_REG_WR(idx, ISP_AEM_DDR_ADDR, node.phy_addr);
		ISP_REG_MWR(idx, ISP_AEM_CFG_READY, BIT_0, 1);
	} else if (block_index == ISP_AFL_BLOCK) {
		/* TBD should modify buf size for afl */
		/* afl old*/
		ISP_REG_WR(idx,
			ISP_ANTI_FLICKER_DDR_INIT_ADDR, node.phy_addr);

		ISP_REG_MWR(idx, ISP_ANTI_FLICKER_CFG_READY, BIT_0, 1);
		/* afl new */
		ISP_REG_WR(idx,
			ISP_ANTI_FLICKER_NEW_DDR_INIT_ADDR, node.phy_addr);
		ISP_REG_WR(idx, ISP_ANTI_FLICKER_NEW_REGION3,
				(node.phy_addr + node.buf_size / 2));

		ISP_REG_MWR(idx, ISP_ANTI_FLICKER_NEW_CFG_READY, BIT_0, 1);
	} else if (block_index == ISP_PDAF_BLOCK) {
		ISP_REG_WR(idx, ISP_PDAF_PHASE_LEFT_ADDR, node.phy_addr);
		ISP_REG_WR(idx, ISP_PDAF_PHASE_RIGHT_ADDR,
			   node.phy_addr + node.buf_size/2);
		/* set pdaf cfg ready */
		ISP_REG_MWR(idx, ISP_PDAF_AF_CTRL1, BIT_0, 1);
	} else if (block_index == ISP_BINNING_BLOCK) {
		ISP_REG_WR(idx, ISP_BINNING_MEM_ADDR, node.phy_addr);
		ISP_REG_WR(idx, ISP_BINNING_CFG_READY, 1);
	}

	return rtn;
}

static int isp_get_afm_statistic(enum isp_id idx, struct isp_statis_buf *node)
{
	int ret = 0;
	int i = 0;
	int max_item = ISP_AFM_WIN_NUM*3;
	unsigned long FV0_LOW = ISP_AFM_ENHANCE_FV0_0_LOW;
	unsigned long *afm_statis = NULL;

#ifdef CONFIG_64BIT
	afm_statis =
		(unsigned long *)(((unsigned long)node->kaddr[0]) |
		((unsigned long)(node->kaddr[1] << 32)));
#else
	afm_statis = (unsigned long *)(node->kaddr[0]);
#endif

	if (!afm_statis) {
		ret = -1;
		pr_err("fail to alloc memory\n");
		return ret;
	}
	for (i = 0; i < max_item; i++)
		afm_statis[i] = ISP_REG_RD(idx, FV0_LOW + i * 4);

	return ret;
}

static void isp_ch0_fmcu_cmd_error(enum isp_id idx, void *isp_handle)
{
	unsigned long addr = 0;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	pr_info("ISP%d: fmcu cmd error Register list\n", idx);
	for (addr = 0xF000; addr <= 0xF044 ; addr += 16) {
		pr_info("0x%lx: 0x%x 0x%x 0x%x 0x%x\n",
			addr,
			ISP_REG_RD(idx, addr),
			ISP_REG_RD(idx, addr + 4),
			ISP_REG_RD(idx, addr + 8),
			ISP_REG_RD(idx, addr + 12));
	}
}

static int isp_err_pre_proc(enum isp_id idx, void *isp_handle)
{
	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	isp_ch0_fmcu_cmd_error(idx, isp_handle);

	return 0;
}

static void isp_irq_reg(enum isp_id idx,
		enum isp_irq_id irq_id, void *param)
{
	isp_isr_func user_func;
	void *user_data;
	struct camera_frame *frame_info = NULL;

	user_func = p_user_func[idx][irq_id];
	user_data = p_user_data[idx][irq_id];

	frame_info = (struct camera_frame *)param;
	if (!frame_info)
		return;

	if (user_func)
		(*user_func)(frame_info, user_data);
}

static void isp_aem_start(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_module *module = NULL;

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;

	rtn = isp_set_next_statis_buf(idx, module, ISP_AEM_BLOCK);
	if (rtn)
		pr_err("fail to set AEM next statis buf\n");
}

static void isp_aem_done(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_frm_queue *statis_heap = NULL;
	struct isp_statis_buf node;
	struct camera_frame frame_info;
	struct isp_statis_module *module = NULL;

	memset(&frame_info, 0x00, sizeof(frame_info));
	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;
	statis_heap = &module->aem_statis_frm_queue;

	/*dequeue the statis buf from a array*/
	rtn = isp_statis_dequeue(statis_heap, &node);
	if (rtn) {
		pr_err("ISP%d:fail to dequeue AEM buf error\n", idx);
		return;
	}

	if (node.phy_addr != module->aem_buf_reserved.phy_addr) {
		frame_info.buf_size = node.buf_size;
		memcpy(frame_info.pfinfo.mfd, node.pfinfo.mfd,
		       sizeof(unsigned int) * 3);
		frame_info.phy_addr = node.phy_addr;
		frame_info.vir_addr = node.vir_addr;
		frame_info.addr_offset = node.addr_offset;
		frame_info.irq_type = CAMERA_IRQ_STATIS;
		frame_info.irq_property = IRQ_AEM_STATIS;
		frame_info.frame_id = module->aem_statis_cnt;

		/*call_back func to write the buf addr to usr_buf_queue*/
		isp_irq_reg(idx, ISP_AEM_DONE, &frame_info);
	}

	module->aem_statis_cnt++;
}

static void isp_aem_error(enum isp_id idx, void *isp_handle)
{
	/*aem err proc*/
	pr_err("ISP%d: fail to aem statis INT.\n", idx);
}

static void isp_afl_start(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_module *module = NULL;

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;

	rtn = isp_set_next_statis_buf(idx, module, ISP_AFL_BLOCK);
	if (rtn)
		pr_err("fail to set AFL next statis buf\n");
}

static void isp_afl_done(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_frm_queue *statis_heap = NULL;
	struct isp_statis_buf node;
	struct camera_frame frame_info;
	struct isp_statis_module *module = NULL;

	memset(&frame_info, 0x00, sizeof(frame_info));

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;
	statis_heap = &module->afl_statis_frm_queue;

	/*dequeue the statis buf from a array*/
	rtn = isp_statis_dequeue(statis_heap, &node);
	if (rtn) {
		pr_err("ISP%d: fail to dequeue AFL buf error\n", idx);
		return;
	}

	if (node.phy_addr != module->afl_buf_reserved.phy_addr) {
		frame_info.buf_size = node.buf_size;
		memcpy(frame_info.pfinfo.mfd, node.pfinfo.mfd,
		       sizeof(unsigned int) * 3);
		frame_info.phy_addr = node.phy_addr;
		frame_info.vir_addr = node.vir_addr;
		frame_info.addr_offset = node.addr_offset;
		frame_info.irq_type = CAMERA_IRQ_STATIS;
		frame_info.irq_property = IRQ_AFL_STATIS;
		frame_info.frame_id = module->afl_statis_cnt;

		/*call_back func to write the buf addr to usr_buf_queue*/
		isp_irq_reg(idx, ISP_AFL_DONE, &frame_info);
	}
	module->afl_statis_cnt++;
}

static void isp_afl_error(enum isp_id idx, void *isp_handle)
{
	/*aem err proc*/
	pr_err("ISP%d: fail to afl statis INT\n", idx);
}

static void isp_afm_start(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_module *module = NULL;

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;

	rtn = isp_set_next_statis_buf(idx, module, ISP_AFM_BLOCK);
	if (rtn)
		pr_err("fail to set AFM next statis buf\n");
}

static void isp_afm_done(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_frm_queue *statis_heap = NULL;
	struct isp_statis_buf node;
	struct camera_frame frame_info;
	struct isp_statis_module *module = NULL;

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;
	statis_heap = &module->afm_statis_frm_queue;

	memset(&node, 0x00, sizeof(node));
	memset(&frame_info, 0x00, sizeof(frame_info));
	/*dequeue the statis buf from a array*/
	rtn = isp_statis_dequeue(statis_heap, &node);
	if (rtn) {
		pr_err("ISP%d:fail to dequeue AFM statis buf\n", idx);
		return;
	}

	if (node.phy_addr != module->afm_buf_reserved.phy_addr) {
		rtn = isp_get_afm_statistic(idx, &node);

		frame_info.buf_size = node.buf_size;
		memcpy(frame_info.pfinfo.mfd, node.pfinfo.mfd,
		       sizeof(unsigned int) * 3);
		frame_info.phy_addr = node.phy_addr;
		frame_info.vir_addr = node.vir_addr;
		frame_info.kaddr[0] = node.kaddr[0];
		frame_info.kaddr[1] = node.kaddr[1];
		frame_info.addr_offset = node.addr_offset;
		frame_info.irq_type = CAMERA_IRQ_STATIS;
		frame_info.irq_property = IRQ_AFM_STATIS;
		frame_info.frame_id = module->afm_statis_cnt;

		/*call_back func to write the buf addr to usr_buf_queue*/
		isp_irq_reg(idx, ISP_AFM_DONE, &frame_info);
	}
	module->afm_statis_cnt++;
}

static void isp_binning_error(enum isp_id idx, void *isp_handle)
{
	/*aem err proc*/
	pr_err("ISP%d:fail to binning statis INT.\n", idx);
}

static void isp_binning_start(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_module *module = NULL;

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;

	rtn = isp_set_next_statis_buf(idx, module, ISP_BINNING_BLOCK);
	if (rtn)
		pr_err("fail to set Binning next statis buf\n");
}

static void isp_binning_done(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_frm_queue *statis_heap = NULL;
	struct isp_statis_buf node;
	struct camera_frame frame_info;
	struct isp_statis_module *module = NULL;

	memset(&frame_info, 0x00, sizeof(frame_info));

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;
	statis_heap = &module->binning_statis_frm_queue;

	/*dequeue the statis buf from a array*/
	rtn = isp_statis_dequeue(statis_heap, &node);
	if (rtn) {
		pr_err("ISP%d:fail to dequeue statis buf\n", idx);
		return;
	}

	/* TBD :should to determine whether or not to use the resverd buf */
	if (node.phy_addr != module->binning_buf_reserved.phy_addr) {
		frame_info.buf_size = node.buf_size;
		memcpy(frame_info.pfinfo.mfd, node.pfinfo.mfd,
			sizeof(unsigned int) * 3);
		frame_info.phy_addr = node.phy_addr;
		frame_info.vir_addr = node.vir_addr;
		frame_info.addr_offset = node.addr_offset;
		frame_info.irq_type = CAMERA_IRQ_STATIS;
		frame_info.irq_property = IRQ_BINNING_STATIS;
		frame_info.frame_id = module->binning_statis_cnt;

		/*call_back func to write the buf addr to usr_buf_queue*/
		isp_irq_reg(idx, ISP_BINNING_DONE, &frame_info);
	}

	module->binning_statis_cnt++;
}

static void isp_pdaf_start(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_module *module = NULL;

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;

	if (dev->pdaf_status[idx] == ISP_PDAF_INIT_FLAG) {
		dev->pdaf_status[idx] = ISP_PDAF_START_FLAG;
		rtn = isp_set_next_statis_buf(idx, module, ISP_PDAF_BLOCK);
		if (rtn)
			pr_err("fail to set pdaf next statis buf\n");
	}
}

static void isp_pdaf_left_done(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_frm_queue *statis_heap = NULL;
	struct isp_statis_buf node;
	struct camera_frame frame_info;
	struct isp_statis_module *module = NULL;

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;
	statis_heap = &module->pdaf_statis_frm_queue;

	if (dev->pdaf_status[idx] ==
		(ISP_PDAF_START_FLAG | ISP_PDAF_RIGHT_DONE_FLAG)) {
		dev->pdaf_status[idx] = ISP_PDAF_INIT_FLAG;
		/*dequeue the statis buf from a array*/
		rtn = isp_statis_dequeue(statis_heap, &node);
		if (rtn) {
			pr_err("ISP%d:fail to dequeue PDAF left statis buf\n",
				idx);
			return;
		}

		/*call back when is not reserved buffer*/
		if (node.phy_addr != module->pdaf_buf_reserved.phy_addr) {
			frame_info.buf_size = node.buf_size;
			memcpy(frame_info.pfinfo.mfd, node.pfinfo.mfd,
			       sizeof(unsigned int) * 3);
			frame_info.phy_addr = node.phy_addr;
			frame_info.vir_addr = node.vir_addr;
			frame_info.addr_offset = node.addr_offset;
			frame_info.irq_type = CAMERA_IRQ_STATIS;
			frame_info.irq_property = IRQ_PDAF_STATIS;
			frame_info.frame_id = module->pdaf_statis_cnt;

			/*call_back func to*/
			/*write the buf addr to usr_buf_queue*/
			isp_irq_reg(idx, ISP_PDAF_LEFT_DONE, &frame_info);
		}
		module->pdaf_statis_cnt++;
	} else if (dev->pdaf_status[idx] == ISP_PDAF_START_FLAG)
		dev->pdaf_status[idx] |= ISP_PDAF_LEFT_DONE_FLAG;
	else
		pr_err("ISP%d:fail to left,pdaf_status\n", idx);
}

static void isp_pdaf_right_done(enum isp_id idx, void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_pipe_dev *dev = NULL;
	struct isp_statis_frm_queue *statis_heap = NULL;
	struct isp_statis_buf node;
	struct camera_frame frame_info;
	struct isp_statis_module *module = NULL;

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->statis_module_info;
	statis_heap = &module->pdaf_statis_frm_queue;
	if (dev->pdaf_status[idx] ==
		(ISP_PDAF_START_FLAG | ISP_PDAF_LEFT_DONE_FLAG)) {
		dev->pdaf_status[idx] = ISP_PDAF_INIT_FLAG;
		/*dequeue the statis buf from a array*/
		rtn = isp_statis_dequeue(statis_heap, &node);
		if (rtn) {
			pr_err("ISP%d:fail to dequeue PDAF right statis buf\n",
				idx);
			return;
		}

		/*call back when is not reserved buffer*/
		if (node.phy_addr != module->pdaf_buf_reserved.phy_addr) {
			frame_info.buf_size = node.buf_size;
			memcpy(frame_info.pfinfo.mfd, node.pfinfo.mfd,
			       sizeof(unsigned int) * 3);
			frame_info.phy_addr = node.phy_addr;
			frame_info.vir_addr = node.vir_addr;
			frame_info.addr_offset = node.addr_offset;
			frame_info.irq_type = CAMERA_IRQ_STATIS;
			frame_info.irq_property = IRQ_PDAF_STATIS;
			frame_info.frame_id = module->pdaf_statis_cnt;

			/*call_back func to*/
			/*write the buf addr to usr_buf_queue*/
			isp_irq_reg(idx, ISP_PDAF_RIGHT_DONE, &frame_info);
		}
		module->pdaf_statis_cnt++;
	} else if (dev->pdaf_status[idx] == ISP_PDAF_START_FLAG)
		dev->pdaf_status[idx] |= ISP_PDAF_RIGHT_DONE_FLAG;
	else
		pr_err("ISP%d:fail to right pdaf_status_machine\n", idx);
}

void isp_fmcu_slw_shadow(enum isp_scl_id path_id, void *isp_handle)
{
	enum isp_id idx;
	enum isp_slw_rtn rtn = ISP_RTN_SLW_SUCCESS;
	struct isp_pipe_dev *dev = NULL;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	dev = (struct isp_pipe_dev *)isp_handle;
	idx = dev->module_info.idx;

	if (dev->fmcu_slw.status == ISP_ST_STOP) {
		pr_debug("fmcu_slw ISP_ST_STOP.\n");
		return;
	}

	if (get_slw_status(dev) == ISP_ST_START) {
		rtn = set_isp_fmcu_slw_cmd(isp_handle,
			ISP_SCL_VID, 0);
		if (unlikely(rtn)) {
			pr_err("fail to set fmcu slw cmd\n");
			return;
		}
	}
	rtn = set_isp_fmcu_cmd_reg(path_id, isp_handle);
	if (rtn) {
		pr_err("fail to set fmcu cmd reg\n");
		return;
	}

	ISP_REG_MWR(idx, ISP_FMCU_CMD_READY, BIT_0, 1);
}

void isp_fmcu_slw_config(enum isp_scl_id path_id, void *isp_handle)
{
	unsigned int i = 0;
	enum isp_slw_rtn rtn = ISP_RTN_SLW_SUCCESS;
	void *data;
	isp_isr_func user_func;
	enum isp_id idx;
	enum isp_irq_id img_id;
	struct camera_frame frame;
	struct isp_pipe_dev *dev = NULL;
	struct isp_module *module = NULL;
	struct isp_path_desc *path = NULL;
	struct isp_fmcu_slw_desc *fmcu_slw = NULL;
	struct isp_fmcu_slw_info *slw_handle = NULL;
	struct camera_frame *reserved_frame = NULL;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	dev = (struct isp_pipe_dev *)isp_handle;
	idx = dev->idx;
	fmcu_slw = &dev->fmcu_slw;
	slw_handle = fmcu_slw->slw_handle;
	module = &dev->module_info;
	path = &module->isp_path[path_id];

	if (dev->fmcu_slw.status == ISP_ST_STOP) {
		pr_debug("fmcu_slw ISP_ST_STOP.\n");
		return;
	}

	if (path_id == ISP_SCL_VID)
		img_id = ISP_PATH_VID_DONE;
	else
		return;

	user_func = p_user_func[idx][img_id];
	data = p_user_data[idx][img_id];

	rtn = slowmotion_frame_dequeue(&slw_handle->insert_queue,
				       &slw_handle->slw_info);
	if (rtn)
		return;

	reserved_frame = &module->path_reserved_frame[path_id];
	if (likely(slw_handle->slw_info.is_reserved == 0)) {
		for (i = 0; i < ISP_SLW_FRM_NUM; i++) {
			rtn = isp_frame_dequeue(&slw_handle->slw_info.slw_queue,
						&frame);
			if (rtn)
				break;
			if (frame.pfinfo.mfd[0] ==
			    reserved_frame->pfinfo.mfd[0])
				continue;

			frame.width = path->dst.w;
			frame.height = path->dst.h;
			frame.irq_type = CAMERA_IRQ_IMG;
			pr_debug("ISP%d: path%d frame %p mfd=%d\n",
				 idx, path_id, &frame, frame.pfinfo.mfd[0]);
			if (user_func)
				(*user_func)(&frame, data);
		}
		slw_handle->slw_info.fmcu_num = 0;
		slowmotion_frame_enqueue(&slw_handle->empty_queue,
					 &slw_handle->slw_info);
	} else {
		pr_info("isp%d: use reserved [%d]\n", idx, path_id);
	}
}

static void isp_path_done(enum isp_id idx, enum isp_scl_id path_id,
	void *isp_handle)
{
	int  ret = 0;
	unsigned int ch_id;
	enum isp_irq_id img_id;
	struct camera_frame frame;
	struct isp_path_desc *path;
	isp_isr_func user_func;
	void *data;
	struct isp_pipe_dev *dev = NULL;
	struct isp_module *module = NULL;
	struct isp_fmcu_slw_desc *fmcu_slw = NULL;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	if (path_id >= ISP_SCL_MAX) {
		pr_err("fail to get valid img_id %d\n.", path_id);
		return;
	}

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->module_info;
	path = &module->isp_path[path_id];
	fmcu_slw = &dev->fmcu_slw;
	if (path->valid == 0) {
		pr_info("isp%d:fail to get valid path%d\n", idx, path_id);
		return;
	}

	if (path_id == ISP_SCL_PRE) {
		img_id = ISP_PATH_PRE_DONE;
		ch_id = (BIT_15 | BIT_16 | BIT_17);
	} else if (path_id == ISP_SCL_VID) {
		img_id = ISP_PATH_VID_DONE;
		ch_id = (BIT_18 | BIT_19 | BIT_20);
	} else if (path_id == ISP_SCL_CAP) {
		img_id = ISP_PATH_CAP_DONE;
		ch_id = (BIT_21 | BIT_22 | BIT_23);
	} else {
		pr_err("fail to get valid isp path id %d.\n", path_id);
		return;
	}

	user_func = p_user_func[idx][img_id];
	data = p_user_data[idx][img_id];

	if (dev->fmcu_slw.status == ISP_ST_START &&
		path_id == ISP_SCL_VID) {
		pr_info("fmcu_slw ISP_ST_START.\n");
		return;
	}

	if (path->shadow_done_cnt < 1
	    && !fmcu_slw->slw_flags
	    && path_id != ISP_SCL_CAP) {
		pr_info("path%d shadow_done_cnt %d\n",
			path_id, path->shadow_done_cnt);
		return;
	}
	path->shadow_done_cnt = 0;
	ret = isp_frame_dequeue(&path->frame_queue, &frame);
	if (ret) {
		pr_info("fail ot dequue frame queue.\n");
		return;
	}

	if (frame.pfinfo.dev == NULL)
		pr_info("ISP%d:fail to done dev %p\n",
			idx, frame.pfinfo.dev);

	pfiommu_free_addr_with_id(&frame.pfinfo,
				SPRD_IOMMU_EX_CH_WRITE, ch_id);
	if (frame.pfinfo.mfd[0] !=
	    module->path_reserved_frame[path_id].pfinfo.mfd[0]) {
		frame.width = path->dst.w;
		frame.height = path->dst.h;
		frame.irq_type = CAMERA_IRQ_IMG;
		pr_debug("ISP%d: path%d frame %p\n",
			idx, path_id, &frame);
		if (user_func)
			(*user_func)(&frame, data);
	} else {
		pr_debug("isp%d: use reserved [%d]\n", idx, path_id);
		module->path_reserved_frame[path_id].pfinfo.iova[0] = 0;
		module->path_reserved_frame[path_id].pfinfo.iova[1] = 0;
	}

	pr_debug("sprd_isp path done.\n");
}

static void isp_path_shadow_done(enum isp_id idx, enum isp_scl_id path_id,
	void *isp_handle)
{
	enum isp_drv_rtn rtn = ISP_RTN_SUCCESS;
	struct isp_path_desc *path = NULL;
	enum isp_path_index path_index = ISP_PATH_IDX_PRE;
	struct isp_pipe_dev *dev = NULL;
	struct isp_module *module = NULL;
	struct isp_path_desc *scl0 = NULL;
	struct isp_sc_array *scl_array = NULL;
	struct isp_sc_coeff *coeff = NULL;
	struct isp_sc_coeff *scl0_coeff = NULL;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->module_info;
	scl0 = &module->isp_path[ISP_SCL_0];
	scl_array = module->scl_array[idx];

	if (dev->fmcu_slw.status == ISP_ST_START &&
		path_id == ISP_SCL_VID)
		return;

	if (path_id == ISP_SCL_PRE)
		path_index = ISP_PATH_IDX_PRE;
	else if (path_id == ISP_SCL_VID)
		path_index = ISP_PATH_IDX_VID;
	else if (path_id == ISP_SCL_CAP)
		path_index = ISP_PATH_IDX_CAP;
	else {
		pr_err("fail to get valid path id %d\n", path_id);
		return;
	}

	if (module->isp_path[path_id].status == ISP_ST_START) {
		pr_debug("ISP%d: shadow s %d\n", idx, path_id);
		path = &module->isp_path[path_id];
		if (path->valid == 0) {
			pr_info("ISP%d:fail to get valid path%d\n",
				idx, path_id);
			return;
		}
		if (path->shadow_done_cnt == 1
		    && !dev->fmcu_slw.slw_flags
		    && path_id != ISP_SCL_CAP) {
			pr_info("path%d shadow_done_cnt %d\n",
				path_id, path->shadow_done_cnt);
			return;
		}
		path->shadow_done_cnt = 1;
		if (path_id == ISP_SCL_PRE) {
			isp_coeff_get_valid_node(scl_array->scl0_queue,
						 &scl0_coeff, 1);
			isp_coeff_get_valid_node(scl_array->pre_queue,
						 &coeff, 1);
		} else if (path_id == ISP_SCL_VID)
			isp_coeff_get_valid_node(scl_array->vid_queue,
						 &coeff, 1);
		else if (path_id == ISP_SCL_CAP)
			isp_coeff_get_valid_node(scl_array->cap_queue,
						 &coeff, 1);
		else
			return;
		if (coeff) {
			if (path_id == ISP_SCL_PRE && scl0_coeff)
				isp_path_set_scl(module->idx,
						 &scl0_coeff->path,
						 ISP_SCALER0_BASE);
			isp_path_set(module, &coeff->path, path_index);
			pr_debug("ISP%d: path%d updated\n", idx, path_id);
		}
		if (path_id != ISP_SCL_CAP)
			rtn = isp_path_set_next_frm(module,
				path_index, NULL);
	}
}

static void isp_dcam_sof(enum isp_id idx, void *isp_handle)
{
	struct isp_pipe_dev *dev = NULL;
	struct camera_frame frame = {0};
	isp_isr_func user_func;
	void *data;
	struct isp_k_block *isp_k_param = NULL;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	dev = (struct isp_pipe_dev *)isp_handle;
	user_func = p_user_func[idx][ISP_DCAM_SOF];
	data = p_user_data[idx][ISP_DCAM_SOF];

	frame.irq_type = CAMERA_IRQ_DONE;
	frame.irq_property = IRQ_DCAM_SOF;
	frame.type = ISP_SCL_PRE;
	frame.frame_id = dev->frame_id;
	dev->frame_id++;

	if (user_func)
		(user_func)(&frame, data);

	isp_k_param = &dev->isp_k_param;
	isp_k_param->lsc_updated = 0;

	pr_debug("isp dcam sof.\n");
}

static void isp_ch1_3dnr_done(enum isp_id idx, void *isp_handle)
{
	struct camera_frame frame = {0};
	isp_isr_func user_func;
	void *data;
	struct isp_pipe_dev *isp_dev = NULL;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	isp_3dnr_stop_preview();

	user_func = p_user_func[idx][ISP_3DNR_CAP_DONE];
	data = p_user_data[idx][ISP_3DNR_CAP_DONE];

	frame.irq_type = CAMERA_IRQ_3DNR_DONE;
	frame.irq_property = IRQ_MAX_DONE;

	if (user_func)
		user_func(&frame, data);

	isp_dev = (struct isp_pipe_dev *)isp_handle;

	pfiommu_free_addr_with_id(&isp_dev->pfinfo_3dnr[0],
				  SPRD_IOMMU_EX_CH_READ,
				  BIT_7 | BIT_8 | BIT_9 |
				  BIT_10 | BIT_11 | BIT_12);
	pfiommu_free_addr_with_id(&isp_dev->pfinfo_3dnr[1],
				  SPRD_IOMMU_EX_CH_READ,
				  BIT_7 | BIT_8 | BIT_9 |
				  BIT_10 | BIT_11 | BIT_12);
	pfiommu_free_addr_with_id(&isp_dev->pfinfo_3dnr[2],
				  SPRD_IOMMU_EX_CH_WRITE,
				  BIT_24 | BIT_25 | BIT_26 | BIT_27);

	pr_debug("isp_ch1_3dnr_done done.\n");
}

static void isp_ch0_3dnr_done(enum isp_id idx, void *isp_handle)
{
	pr_debug("isp_ch0_3dnr_done done.\n");
}

static void isp_ch1_store_cap_done_4_post_ynr(enum isp_id idx,
	void *isp_handle)
{
	struct camera_frame frame = {0};
	isp_isr_func user_func;
	void *data;
	struct isp_pipe_dev *isp_dev = NULL;

	if (!isp_handle) {
		pr_err("isp handle is NULL.\n");
		return;
	}

	isp_dev = (struct isp_pipe_dev *)isp_handle;
	if (isp_dev->is_ynr_process == 0)
		return;

	user_func = p_user_func[idx][ISP_POST_YNR_DONE];
	data = p_user_data[idx][ISP_POST_YNR_DONE];
	frame.irq_type = CAMERA_IRQ_POST_YNR_DONE;
	frame.irq_property = IRQ_MAX_DONE;

	if (user_func)
		user_func(&frame, data);

	pfiommu_free_addr(&isp_dev->pfinfo_ynr[0]);
	pfiommu_free_addr(&isp_dev->pfinfo_ynr[1]);

	complete(&isp_dev->fmcu_com);
	isp_dev->is_wait_fmcu = 0;
	isp_dev->is_ynr_process = 0;

	pr_debug("ch1 post ynr done.\n");
}

static void isp_shadow_done(enum isp_id idx, void *isp_handle)
{
	struct camera_frame frame = {0};
	isp_isr_func user_func;
	void *data;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	user_func = p_user_func[idx][ISP_SHADOW_DONE];
	data = p_user_data[idx][ISP_SHADOW_DONE];

	frame.irq_type = CAMERA_IRQ_DONE;
	frame.irq_property = IRQ_SHADOW_DONE;

	if (user_func)
		user_func(&frame, data);

	pr_debug("sprd_isp shadow done.\n");
}

static void isp_store_out_done(enum isp_id idx, void *dev)
{
	pr_debug("isp store out done.\n");
}

static void isp_shadow_out_done(enum isp_id idx, void *dev)
{
	pr_debug("isp shadow out done.\n");
}

static void isp_store_cap_done(enum isp_id idx, void *dev)
{
	/* isp_path_done(idx, ISP_SCL_CAP, dev); */
}

static void isp_shadow_cap_done(enum isp_id idx, void *dev)
{
	/* isp_path_shadow_done(idx, ISP_SCL_CAP, dev); */
}

static void isp_store_vid_done(enum isp_id idx, void *dev)
{
	pr_debug("store vid done.\n");
	isp_path_done(idx, ISP_SCL_VID, dev);
}

static void isp_shadow_vid_done(enum isp_id idx, void *dev)
{
	isp_path_shadow_done(idx, ISP_SCL_VID, dev);
	ISP_REG_MWR(idx, ISP_STORE_VIDEO_SHADOW_CLR, BIT_0, 1);
	pr_debug("shadow vid done.\n");
}

static void isp_store_pre_done(enum isp_id idx, void *dev)
{
	pr_debug("store pre done.\n");
	isp_path_done(idx, ISP_SCL_PRE, dev);
}

static void isp_shadow_pre_done(enum isp_id idx, void *dev)
{
	struct isp_pipe_dev *isp_dev = NULL;
	struct isp_path_desc *path = NULL;
	struct isp_module *module = NULL;
	struct isp_fmcu_slw_desc *fmcu_slw = NULL;

	if (!dev) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	isp_dev = (struct isp_pipe_dev *)dev;
	module = &isp_dev->module_info;
	fmcu_slw = &isp_dev->fmcu_slw;

	if (!module || !fmcu_slw) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	if (fmcu_slw->slw_flags) {
		path = &module->isp_path[ISP_SCL_PRE];
		if (!path) {
			pr_err("fail to get valid input path\n");
			return;
		}
		if (fmcu_slw->vid_num == (path->frm_deci + 1) ||
				fmcu_slw->vid_num == 0) {
			fmcu_slw->vid_num = 0;
			isp_path_shadow_done(idx, ISP_SCL_PRE, dev);
		}
		fmcu_slw->vid_num++;
		ISP_REG_MWR(idx, ISP_STORE_PREVIEW_SHADOW_CLR, BIT_0, 1);
	} else {
		isp_path_shadow_done(idx, ISP_SCL_PRE, dev);
		ISP_REG_MWR(idx, ISP_STORE_PREVIEW_SHADOW_CLR, BIT_0, 1);
	}

	pr_debug("shadow pre done.\n");
}

static void isp_store_cce_done(enum isp_id idx, void *isp_handle)
{
	struct camera_frame frame;
	struct isp_pipe_dev *dev = NULL;
	struct isp_path_desc *pre = NULL;
	struct isp_path_desc *vid = NULL;
	struct isp_path_desc *cap = NULL;
	struct isp_store_cce_desc *store_cce = NULL;
	struct isp_fmcu_slice_desc *fmcu_slice = NULL;
	unsigned int is_irq = 0x01;
	unsigned int max_zsl_num = 0;
	unsigned int skip_num = 0;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	dev = (struct isp_pipe_dev *)isp_handle;
	pre = &dev->module_info.isp_path[ISP_SCL_PRE];
	vid = &dev->module_info.isp_path[ISP_SCL_VID];
	cap = &dev->module_info.isp_path[ISP_SCL_CAP];
	store_cce = &dev->module_info.store_cce;
	fmcu_slice = &dev->fmcu_slice;

	if (cap->valid && cap->path_mode == ISP_CAP_OFFLINE)
		skip_num = cap->skip_num;
	if (vid->valid && vid->path_mode == ISP_VID_OFFLINE)
		skip_num = vid->skip_num;
	if (pre->valid && pre->path_mode == ISP_PRE_OFFLINE)
		skip_num = pre->skip_num;

	pr_debug("skip_num %d %d %d\n", skip_num, pre->skip_num, cap->skip_num);

	if (fmcu_slice->storecce_state == ISP_ST_START &&
		store_cce->read_buf_err != 1) {
		if (store_cce->shadow_done_cnt < 1
		    && dev->is_raw_capture != 1) {
			pr_debug("storecce shadow_done_cnt %d\n",
				store_cce->shadow_done_cnt);
			return;
		}
		store_cce->shadow_done_cnt = 0;
		store_cce->frm_cnt++;
		if (isp_frame_dequeue(&store_cce->frame_queue, &frame)) {
			pr_info("storecce frame deque error\n");
			return;
		}

		if (isp_frame_enqueue(&store_cce->zsl_queue, &frame)) {
			pr_info("fail to enqueue storecce zsl queue\n");
			return;
		}

		if (dev->cap_flag == DCAM_CAPTURE_START_HDR)
			max_zsl_num = ISP_HDR_NUM;
		else if (dev->cap_flag == DCAM_CAPTURE_START_3DNR)
			max_zsl_num = ISP_3DNR_NUM;
		else
			max_zsl_num = ISP_ZSL_BUF_NUM;
		if (store_cce->zsl_queue.valid_cnt > max_zsl_num
		    || (store_cce->frm_cnt <= skip_num
			&& dev->is_raw_capture != 1)) {
			if (isp_frame_dequeue(&store_cce->zsl_queue, &frame)) {
				pr_info("fail to dequeue storecce zsl deque\n");
				return;
			}
			if (isp_buf_queue_write(&store_cce->tmp_buf_queue,
				&frame)) {
				pr_info("fail to write storecce buffer queue\n");
				return;
			}
		}

		if (fmcu_slice->capture_state == ISP_ST_START) {
			if ((dev->cap_flag == DCAM_CAPTURE_START_HDR
			     || dev->cap_flag == DCAM_CAPTURE_START_3DNR)
			    && dev->cap_cur_cnt < max_zsl_num)
				return;
			if ((dev->clr_queue == 1 ||
			     store_cce->zsl_queue.valid_cnt == 0) &&
			    dev->is_raw_capture != 1) {
				pr_debug("clr_queue %d\n", dev->clr_queue);
				return;
			}

			pr_debug("storecce start fmcu %d\n", dev->cap_cur_cnt);
			if (sprd_isp_start_fmcu(isp_handle,
				DCAM_CAPTURE_START, is_irq)) {
				pr_info("fail to start slice capture\n");
				return;
			}
		}
	} else
		store_cce->read_buf_err = 0;

	pr_debug("Isp store_cce down end.\n");
}

static void isp_shadow_cce_done(enum isp_id idx, void *isp_handle)
{
	struct isp_pipe_dev *dev = NULL;
	struct isp_fmcu_slice_desc *fmcu_slice = NULL;
	struct isp_module *module = NULL;
	struct isp_sc_array *scl_array = NULL;
	struct isp_sc_coeff *store_cce_coeff = NULL;
	struct isp_store_cce_desc *store_cce = NULL;
	struct isp_path_desc *pre = NULL;
	struct isp_path_desc *vid = NULL;
	struct isp_path_desc *cap = NULL;
	struct camera_frame frame;
	unsigned int max_num = 0;
	unsigned int skip_num = 0;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	dev = (struct isp_pipe_dev *)isp_handle;
	module = &dev->module_info;
	fmcu_slice = &dev->fmcu_slice;
	scl_array = module->scl_array[idx];
	store_cce = &module->store_cce;
	pre = &dev->module_info.isp_path[ISP_SCL_PRE];
	vid = &dev->module_info.isp_path[ISP_SCL_VID];
	cap = &dev->module_info.isp_path[ISP_SCL_CAP];

	if (cap->valid && cap->path_mode == ISP_CAP_OFFLINE)
		skip_num = cap->skip_num;
	if (vid->valid && vid->path_mode == ISP_VID_OFFLINE)
		skip_num = vid->skip_num;
	if (pre->valid && pre->path_mode == ISP_PRE_OFFLINE)
		skip_num = pre->skip_num;

	pr_debug("storecce_state %d\n", fmcu_slice->storecce_state);

	memset(&frame, 0x00, sizeof(frame));
	if (fmcu_slice->storecce_state == ISP_ST_START) {
		if (module->store_cce.shadow_done_cnt == 1
		    && dev->is_raw_capture != 1) {
			pr_debug("storecce shadow_done_cnt %d\n",
				module->store_cce.shadow_done_cnt);
			goto exit;
		}
		module->store_cce.shadow_done_cnt = 1;
		isp_coeff_get_valid_node(scl_array->store_cce_queue,
					 &store_cce_coeff, 1);
		if (store_cce_coeff)
			isp_set_storecce_info(module->idx,
					      &store_cce_coeff->store_cce,
					      ISP_STOREA_BASE);

		while (dev->clr_queue == 1
		       && !isp_frame_dequeue(&store_cce->zsl_queue, &frame)) {
			pr_debug("storecce clr queue\n");
			if (isp_buf_queue_write(&store_cce->tmp_buf_queue,
						&frame)) {
				pr_info("fail to write storecce buffer queue\n");
				goto exit;
			}
		}
		dev->clr_queue = 0;
		if ((dev->cap_flag == DCAM_CAPTURE_START_HDR
		    || dev->cap_flag == DCAM_CAPTURE_START_3DNR)
		    && store_cce->frm_cnt >= skip_num) {
			dev->cap_cur_cnt++;
			pr_debug("storecce cap_cur_cnt %d\n", dev->cap_cur_cnt);

			if (dev->cap_flag == DCAM_CAPTURE_START_HDR)
				max_num = ISP_HDR_NUM;
			else if (dev->cap_flag == DCAM_CAPTURE_START_3DNR)
				max_num = ISP_3DNR_NUM;
			else
				goto exit;
			if (dev->cap_cur_cnt >= max_num) {
				ISP_REG_MWR(idx, ISP_STORE_CCE_PARAM, BIT_0, 1);
				goto exit;
			}
		}
		if (isp_storecce_set_next_frm(&dev->module_info))
			pr_err("fail to set storecce next frame\n");
	}

exit:
	ISP_REG_MWR(idx, ISP_STORE_CCE_SHADOW_CLR, BIT_0, 1);
	pr_debug("Isp cce shadow done\n");
}

static void isp_all_done(enum isp_id idx, void *isp_handle)
{
	struct isp_pipe_dev *dev = NULL;

	dev = (struct isp_pipe_dev *)isp_handle;

	s_isp_chnid[idx] = dev->isp_chn_id[idx];

	DCAM_TRACE("isp all done. isp_id:%d chn_id:%d\n",
		   idx, s_isp_chnid[idx]);
}

static void isp_ch0_fmcu_config_done(enum isp_id idx, void *dev)
{
	pr_debug("isp ch0 fmcu config done\n");
	isp_fmcu_slw_config(ISP_SCL_VID, dev);
}

static void isp_ch0_fmcu_shadow_done(enum isp_id idx, void *dev)
{
	pr_debug("isp ch0 fmcu shadow done\n");
	isp_fmcu_slw_shadow(ISP_SCL_VID, dev);
}

static int isp_storecce_buf_reset(struct isp_store_cce_desc *store_cce)
{
	int ret = 0;
	struct storecce_ion_buf *ion_buf = NULL;
	struct camera_frame frame = {0};
	unsigned int num = 0;

	if (!store_cce) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	isp_buf_queue_init(&store_cce->tmp_buf_queue);
	isp_frm_queue_clear(&store_cce->frame_queue);
	isp_frm_queue_clear(&store_cce->zsl_queue);

	for (num = 0; num < ISP_STORE_CCE_BUF_NUM; num++) {
		ion_buf = &store_cce->ion_buf[num];
		if (ion_buf == NULL)
			return -EPERM;

		if (ion_buf->y_client != NULL
		    && ion_buf->y_handle != NULL
		    && ion_buf->uv_handle != NULL
		    && ion_buf->uv_client != NULL) {
			pr_debug("storecce buffer %d has alloced\n", num);
			frame.yaddr = ion_buf->addr.yaddr;
			frame.uaddr = ion_buf->addr.uaddr;
			ret = isp_buf_queue_write(&store_cce->tmp_buf_queue,
					    &frame);
			if (ret) {
				pr_err("fail to write storecce buffer queue\n");
				return -EFAULT;
			}
		}
	}

	return ret;
}

static void isp_ch1_fmcu_config_done(enum isp_id idx, void *isp_handle)
{
	int ret = 0;
	struct isp_pipe_dev *dev = NULL;
	struct isp_path_desc *path_pre = NULL;
	struct isp_path_desc *path_vid = NULL;
	struct isp_path_desc *path_cap = NULL;
	struct isp_fmcu_slice_desc *fmcu_slice = NULL;
	isp_isr_func user_func;
	void *data;
	struct camera_frame frame;
	struct isp_module *module = NULL;
	enum isp_scl_id path_id = ISP_SCL_CAP;
	unsigned int is_irq = 0x01;

	if (!isp_handle) {
		pr_err("fail to get valid input ptr\n");
		return;
	}

	dev = (struct isp_pipe_dev *)isp_handle;

	complete(&dev->fmcu_com);
	dev->is_wait_fmcu = 0;
	pr_debug("isp start ch1 fmcu config done\n");
	if (dev->fmcu_slw.status == ISP_ST_START) {
		pr_info("fmcu_slw ISP_ST_START.\n");
		return;
	}

	fmcu_slice = &dev->fmcu_slice;
	module = &dev->module_info;

	path_pre = &module->isp_path[ISP_SCL_PRE];
	path_vid = &module->isp_path[ISP_SCL_VID];
	path_cap = &module->isp_path[ISP_SCL_CAP];

	if (path_pre->valid && path_pre->path_mode == ISP_PRE_OFFLINE) {
		path_pre->shadow_done_cnt = 1;
		isp_path_done(idx, ISP_SCL_PRE, dev);
	}

	if (path_vid->valid && path_vid->path_mode == ISP_VID_OFFLINE) {
		path_vid->shadow_done_cnt = 1;
		isp_path_done(idx, ISP_SCL_VID, dev);
	}

	if (path_cap->valid) {
		user_func = p_user_func[idx][ISP_PATH_CAP_DONE];
		data = p_user_data[idx][ISP_PATH_CAP_DONE];
		ret = isp_frame_dequeue(&path_cap->frame_queue, &frame);
		if (ret)
			return;

		pfiommu_free_addr_with_id(&frame.pfinfo,
				SPRD_IOMMU_EX_CH_WRITE,
				(BIT_21 | BIT_22 | BIT_23));

		if (frame.pfinfo.mfd[0] !=
			module->path_reserved_frame[path_id].pfinfo.mfd[0]) {
			frame.width = path_cap->dst.w;
			frame.height = path_cap->dst.h;
			frame.irq_type = CAMERA_IRQ_IMG;
			if (dev->is_raw_capture == 1) {
				frame.irq_type = CAMERA_IRQ_DONE;
				frame.irq_property = IRQ_RAW_CAP_DONE;
			}

			if (user_func)
				(*user_func)(&frame, data);
		} else {
			pr_debug("isp%d: use reserved cap\n", idx);
			module->path_reserved_frame[path_id].pfinfo.iova[0] = 0;
			module->path_reserved_frame[path_id].pfinfo.iova[1] = 0;
		}
	}

	if (dev->is_raw_capture == 1) {
		module->store_cce.valid = 0;
		module->store_cce.status = ISP_ST_STOP;
		path_cap->valid = 0;
		path_cap->status = ISP_ST_STOP;
		dev->is_raw_capture = 0;
		sprd_isp_stop(dev, 1);
		return;
	}

	if (dev->cap_flag == DCAM_CAPTURE_START_HDR
	    || dev->cap_flag == DCAM_CAPTURE_START_3DNR) {
		pr_debug("fmcu config done %d\n", dev->cap_cur_cnt);
		if (sprd_isp_start_fmcu(isp_handle,
				DCAM_CAPTURE_START, is_irq)) {
			pr_info("fail to start slice capture\n");
			return;
		}
	} else if (module->store_cce.valid == 1) {
		ret = isp_storecce_buf_reset(&module->store_cce);
		if (ret) {
			pr_err("fail to reset isp storecce buf\n");
			return;
		}

		if (isp_storecce_set_next_frm(&dev->module_info))
			pr_err("fail to set storecce next frame\n");

		module->store_cce.shadow_done_cnt = 0;

		ISP_REG_MWR(idx, ISP_STORE_CCE_PARAM, BIT_0, 0);
		fmcu_slice->storecce_state = ISP_ST_START;
	}

	pr_debug("isp end ch1 fmcu config done\n");
}

static isp_isr isp_ch0_isr_list[ISP_MAX_COUNT][4][32] = {
	[0][0][ISP_INT_ISP_ALL_DONE] = isp_all_done,
	[0][0][ISP_INT_SHADOW_DONE] = isp_shadow_done,
	[0][0][ISP_INT_AEM_START] = isp_aem_start,
	[0][0][ISP_INT_AEM_DONE] = isp_aem_done,
	[0][0][ISP_INT_AEM_ERROR] = isp_aem_error,
	[0][0][ISP_INT_AFL_START] = isp_afl_start,
	[0][0][ISP_INT_AFL_DONE] = isp_afl_done,
	[0][0][ISP_INT_AFL_ERROR] = isp_afl_error,
	[0][0][ISP_INT_BINNING_START] = isp_binning_start,
	[0][0][ISP_INT_BINNING_DONE] = isp_binning_done,
	[0][0][ISP_INT_BINNING_ERROR] = isp_binning_error,
	[0][0][ISP_INT_PDAF_DDR_START] = isp_pdaf_start,
	[0][0][ISP_INT_PDAF_SHADOW_DONE] = isp_pdaf_start,
	[0][0][ISP_INT_PDAF_MEM_LEFT_DONE] = isp_pdaf_left_done,
	[0][0][ISP_INT_PDAF_MEM_RIGHT_DONE] = isp_pdaf_right_done,
	[0][0][ISP_INT_DCAM_SOF] = isp_dcam_sof,
	[0][1][ISP_INT_STORE_DONE_OUT] = isp_store_out_done,
	[0][1][ISP_INT_SHADOW_DONE_OUT] = isp_shadow_out_done,
	[0][1][ISP_INT_STORE_DONE_CAP] = isp_store_cap_done,
	[0][1][ISP_INT_SHADOW_DONE_CAP] = isp_shadow_cap_done,
	[0][1][ISP_INT_STORE_DONE_VID] = isp_store_vid_done,
	[0][1][ISP_INT_SHADOW_DONE_VID] = isp_shadow_vid_done,
	[0][1][ISP_INT_STORE_DONE_PRE] = isp_store_pre_done,
	[0][1][ISP_INT_SHADOW_DONE_PRE] = isp_shadow_pre_done,
	[0][1][ISP_INT_STORE_DONE_CCE] = isp_store_cce_done,
	[0][1][ISP_INT_SHADOW_DONE_CCE] = isp_shadow_cce_done,
	[0][2][ISP_INT_AFM_RGB_START] = isp_afm_start,
	[0][2][ISP_INT_AFM_RGB_DONE] = isp_afm_done,
	[0][2][ISP_INT_FMCU_CONFIG_DONE] = isp_ch0_fmcu_config_done,
	[0][2][ISP_INT_FMCU_SHADOW_DONE] = isp_ch0_fmcu_shadow_done,
	[0][2][ISP_INT_NR3_DONE] = isp_ch0_3dnr_done,
	[0][2][ISP_INT_FMCU_CMD_ERROR] = isp_ch0_fmcu_cmd_error,
};

static isp_isr isp_ch1_isr_list[ISP_MAX_COUNT][4][32] = {
	[0][1][ISP_INT_STORE_DONE_CAP] = isp_ch1_store_cap_done_4_post_ynr,
	[0][2][ISP_INT_NR3_DONE] = isp_ch1_3dnr_done,
	[0][2][ISP_INT_FMCU_CONFIG_DONE] = isp_ch1_fmcu_config_done,
};

static irqreturn_t isp_isr_root_ch0(int irq, void *priv)
{
	unsigned int irq_line[4] = {0};
	unsigned int j, k;
	unsigned int vect = 0;
	unsigned long flag;
	unsigned long base_addr = s_isp_regbase[0];
	enum isp_id idx = ISP_ID_0;
	unsigned int irq_numbers[4] = {0};
	struct isp_pipe_dev *isp_handle = NULL;

	isp_handle = (struct isp_pipe_dev *)priv;

	irq_numbers[0] = ARRAY_SIZE(isp_ch0_irq_vect0);
	irq_numbers[1] = ARRAY_SIZE(isp_ch0_irq_vect1);
	irq_numbers[2] = ARRAY_SIZE(isp_ch0_irq_vect2);

	idx = isp_handle->idx;
	base_addr = s_isp_regbase[idx];

	irq_line[0] = REG_RD(base_addr + ISP_INT_INT0) & ISP_INT_LINE_MASK0;
	irq_line[1] = REG_RD(base_addr + ISP_INT_INT1) & ISP_INT_LINE_MASK1;
	irq_line[2] = REG_RD(base_addr + ISP_INT_INT2) & ISP_INT_LINE_MASK2;
	irq_line[3] = REG_RD(base_addr + ISP_INT_INT3) & ISP_INT_LINE_MASK3;

	if (unlikely(irq_line[0] == 0 && irq_line[1] == 0 && irq_line[2] == 0
		     && irq_line[3] == 0))
		return IRQ_NONE;
	/*clear the interrupt*/
	REG_WR(base_addr + ISP_INT_CLR0, irq_line[0]);
	REG_WR(base_addr + ISP_INT_CLR1, irq_line[1]);
	REG_WR(base_addr + ISP_INT_CLR2, irq_line[2]);
	REG_WR(base_addr + ISP_INT_CLR3, irq_line[3]);

	if (unlikely(ISP_IRQ_ERR_MASK0 & irq_line[0])
		|| unlikely(ISP_IRQ_ERR_MASK1 & irq_line[1])
		|| unlikely(ISP_IRQ_ERR_MASK2 & irq_line[2])) {
		pr_err("isp IRQ is error %d, INT0:0x%x, INT1:0x%x,INT2:0x%x",
			idx, irq_line[0], irq_line[1], irq_line[2]);
		/*handle the error here*/
		if (isp_err_pre_proc(idx, isp_handle))
			return IRQ_HANDLED;
	}

	/*spin_lock_irqsave protect the isr_func*/
	spin_lock_irqsave(&isp_mod_lock[idx], flag);
	for (j = 0; j < 3; j++) {
		for (k = 0; k < irq_numbers[j]; k++) {
			if (j == 0)
				vect = isp_ch0_irq_vect0[k];
			else if (j == 1)
				vect = isp_ch0_irq_vect1[k];
			else if (j == 2)
				vect = isp_ch0_irq_vect2[k];
			if (irq_line[j] & (1 << (unsigned int)vect)) {
				if (isp_ch0_isr_list[idx][j][vect])
					isp_ch0_isr_list[idx][j][vect](idx,
						isp_handle);
			}
			irq_line[j] &= ~(1 << (unsigned int)vect);
			if (!irq_line[j])
				break;
		}
	}
	/*spin_unlock_irqrestore*/
	spin_unlock_irqrestore(&isp_mod_lock[idx], flag);

	return IRQ_HANDLED;
}

static irqreturn_t isp_isr_root_ch1(int irq, void *priv)
{
	unsigned int irq_line[4] = {0};
	unsigned int j, k;
	unsigned int vect = 0;
	unsigned long flag;
	unsigned long base_addr = s_isp_regbase[0];
	enum isp_id idx = ISP_ID_0;
	unsigned int irq_numbers[4] = {0};
	struct isp_pipe_dev *isp_handle = NULL;

	isp_handle = (struct isp_pipe_dev *)priv;

	irq_numbers[1] = ARRAY_SIZE(isp_ch1_irq_vect1);
	irq_numbers[2] = ARRAY_SIZE(isp_ch1_irq_vect2);

	idx = isp_handle->idx;
	base_addr = s_isp_regbase[idx] + ISP_CH1_ADDR_OFFSET;

	irq_line[0] = REG_RD(base_addr + ISP_INT_INT0) & ISP_INT_LINE_MASK0;
	irq_line[1] = REG_RD(base_addr + ISP_INT_INT1) & ISP_INT_LINE_MASK1;
	irq_line[2] = REG_RD(base_addr + ISP_INT_INT2) & ISP_INT_LINE_MASK2;
	irq_line[3] = REG_RD(base_addr + ISP_INT_INT3) & ISP_INT_LINE_MASK3;

	if (unlikely(irq_line[0] == 0 && irq_line[1] == 0 && irq_line[2] == 0
		     && irq_line[3] == 0))
		return IRQ_NONE;
	/*clear the interrupt*/
	REG_WR(base_addr + ISP_INT_CLR0, irq_line[0]);
	REG_WR(base_addr + ISP_INT_CLR1, irq_line[1]);
	REG_WR(base_addr + ISP_INT_CLR2, irq_line[2]);
	REG_WR(base_addr + ISP_INT_CLR3, irq_line[3]);

	if (unlikely(ISP_IRQ_ERR_MASK0 & irq_line[0])
	    || unlikely(ISP_IRQ_ERR_MASK1 & irq_line[1])
	    || unlikely(ISP_IRQ_ERR_MASK2 & irq_line[2])) {
		pr_err("isp IRQ is error %d, INT0:0x%x, INT1:0x%x,INT2:0x%x",
		       idx, irq_line[0], irq_line[1],
		       irq_line[2]);
		/*handle the error here*/
		if (isp_err_pre_proc(idx, isp_handle))
			return IRQ_HANDLED;
	}

	/*spin_lock_irqsave protect the isr_func*/
	spin_lock_irqsave(&isp_mod_lock[idx], flag);
	for (j = 0; j < 3; j++) {
		for (k = 0; k < irq_numbers[j]; k++) {
			if (j == 1)
				vect = isp_ch1_irq_vect1[k];
			else if (j == 2)
				vect = isp_ch1_irq_vect2[k];
			else
				continue;
			if (irq_line[j] & (1 << (unsigned int)vect)) {
				if (isp_ch1_isr_list[idx][j][vect])
					isp_ch1_isr_list[idx][j][vect](idx,
						isp_handle);
			}
			irq_line[j] &= ~(1 << (unsigned int)vect);
			if (!irq_line[j])
				break;
		}
	}
	/*spin_unlock_irqrestore*/
	spin_unlock_irqrestore(&isp_mod_lock[idx], flag);

	return IRQ_HANDLED;
}

int isp_irq_request(struct device *p_dev, struct isp_ch_irq *irq,
	struct isp_pipe_dev *ispdev)
{
	int ret = 0;
	enum isp_id idx = 0;

	if (!p_dev || !irq || !ispdev) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	idx = ispdev->idx;
	irq_ch0_lock[idx] = __SPIN_LOCK_UNLOCKED(&irq_ch0_lock[idx]);
	irq_ch1_lock[idx] = __SPIN_LOCK_UNLOCKED(&irq_ch1_lock[idx]);

	ret = devm_request_irq(p_dev, irq->ch0, isp_isr_root_ch0,
		IRQF_SHARED, "ISP_CH0", (void *)ispdev);
	if (ret) {
		pr_err("fail to install IRQ ch0 %d\n", ret);
		goto exit;
	}

	ret = devm_request_irq(p_dev, irq->ch1, isp_isr_root_ch1,
		IRQF_SHARED, "ISP_CH1", (void *)ispdev);
	if (ret) {
		pr_err("fail to install IRQ ch1 %d\n", ret);
		goto exit;
	}

exit:
	return ret;
}

int isp_irq_free(struct isp_ch_irq *irq, struct isp_pipe_dev *ispdev)
{
	int ret = 0;
	enum isp_id idx = 0;

	if (!irq || !ispdev) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	idx = ispdev->idx;
	irq_ch0_lock[idx] = __SPIN_LOCK_UNLOCKED(&irq_ch0_lock[idx]);
	irq_ch1_lock[idx] = __SPIN_LOCK_UNLOCKED(&irq_ch1_lock[idx]);

	free_irq(irq->ch0, (void *)ispdev);
	free_irq(irq->ch1, (void *)ispdev);

	return ret;
}

int isp_irq_callback(enum isp_id idx, enum isp_irq_id irq_id,
	isp_isr_func user_func, void *user_data)
{
	unsigned long flag;

	if (!user_data) {
		pr_err("fail to get valid input ptr\n");
		return -EFAULT;
	}

	spin_lock_irqsave(&isp_mod_lock[idx], flag);
	p_user_func[idx][irq_id] = user_func;
	p_user_data[idx][irq_id] = user_data;
	spin_unlock_irqrestore(&isp_mod_lock[idx], flag);

	return 0;
}
