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

#include "ion.h"
#include <linux/delay.h>
#include <linux/sprd_ion.h>
#include <linux/workqueue.h>
#include "sprd_dispc.h"
#include "sprd_round_corner.h"

#define DISPC_INT_FBC_PLD_ERR_MASK	BIT(8)
#define DISPC_INT_FBC_HDR_ERR_MASK	BIT(9)

#define DISPC_INT_MMU_INV_WR_MASK	BIT(19)
#define DISPC_INT_MMU_INV_RD_MASK	BIT(18)
#define DISPC_INT_MMU_VAOR_WR_MASK	BIT(17)
#define DISPC_INT_MMU_VAOR_RD_MASK	BIT(16)

#define XFBC8888_HEADER_SIZE(w, h) (ALIGN((w) * (h) / (8 * 8) / 2, 128))
#define XFBC8888_PAYLOAD_SIZE(w, h) (w * h * 4)
#define XFBC8888_BUFFER_SIZE(w, h) (XFBC8888_HEADER_SIZE(w, h) \
				+ XFBC8888_PAYLOAD_SIZE(w, h))

#define XFBC565_HEADER_SIZE(w, h) (ALIGN((w) * (h) / (16 * 8) / 2, 128))
#define XFBC565_PAYLOAD_SIZE(w, h) (w * h * 2)
#define XFBC565_BUFFER_SIZE(w, h) (XFBC565_HEADER_SIZE(w, h) \
				+ XFBC565_PAYLOAD_SIZE(w, h))

#define update_work	wb_work

struct layer_reg {
	u32 addr[4];
	u32 ctrl;
	u32 size;
	u32 pitch;
	u32 pos;
	u32 alpha;
	u32 ck;
	u32 pallete;
	u32 crop_start;
};

struct wb_region_reg {
	u32 pos;
	u32 size;
};

struct dpu_reg {
	u32 dpu_version;
	u32 dpu_ctrl;
	u32 dpu_cfg0;
	u32 dpu_cfg1;
	u32 dpu_cfg2;
	u32 dpu_secure;
	u32 reserved_0x0018_0x001C[2];
	u32 panel_size;
	u32 blend_size;
	u32 reserved_0x0028;
	u32 bg_color;
	struct layer_reg layers[8];
	u32 wb_base_addr;
	u32 wb_ctrl;
	u32 wb_cfg;
	u32 wb_pitch;
	struct wb_region_reg region[3];
	u32 reserved_0x01D8_0x01DC[2];
	u32 dpu_int_en;
	u32 dpu_int_clr;
	u32 dpu_int_sts;
	u32 dpu_int_raw;
	u32 dpi_ctrl;
	u32 dpi_h_timing;
	u32 dpi_v_timing;
	u32 reserved_0x01FC;
	u32 dpu_enhance_cfg;
	u32 reserved_0x0204_0x020C[3];
	u32 epf_epsilon;
	u32 epf_gain0_3;
	u32 epf_gain4_7;
	u32 epf_diff;
	u32 reserved_0x0220_0x023C[8];
	u32 hsv_lut_addr;
	u32 hsv_lut_wdata;
	u32 hsv_lut_rdata;
	u32 reserved_0x024C_0x027C[13];
	u32 cm_coef01_00;
	u32 cm_coef03_02;
	u32 cm_coef11_10;
	u32 cm_coef13_12;
	u32 cm_coef21_20;
	u32 cm_coef23_22;
	u32 reserved_0x0298_0x02BC[10];
	u32 slp_cfg0;
	u32 slp_cfg1;
	u32 slp_cfg2;
	u32 slp_cfg3;
	u32 slp_lut_addr;
	u32 slp_lut_wdata;
	u32 slp_lut_rdata;
	u32 reserved_0x02DC_0x02FC[9];
	u32 gamma_lut_addr;
	u32 gamma_lut_wdata;
	u32 gamma_lut_rdata;
	u32 reserved_0x030C_0x033C[13];
	u32 checksum_en;
	u32 checksum0_start_pos;
	u32 checksum0_end_pos;
	u32 checksum1_start_pos;
	u32 checksum1_end_pos;
	u32 checksum0_result;
	u32 checksum1_result;
	u32 reserved_0x035C;
	u32 dpu_sts[18];
	u32 reserved_0x03A8_0x03AC[2];
	u32 dpu_fbc_cfg0;
	u32 dpu_fbc_cfg1;
	u32 reserved_0x03B8_0x03EC[14];
	u32 rf_ram_addr;
	u32 rf_ram_rdata_low;
	u32 rf_ram_rdata_high;
	u32 reserved_0x03FC_0x07FC[257];
	u32 mmu_en;
	u32 mmu_update;
	u32 mmu_min_vpn;
	u32 mmu_vpn_range;
	u32 mmu_pt_addr;
	u32 mmu_default_page;
	u32 mmu_vaor_addr_rd;
	u32 mmu_vaor_addr_wr;
	u32 mmu_inv_addr_rd;
	u32 mmu_inv_addr_wr;
	u32 mmu_uns_addr_rd;
	u32 mmu_uns_addr_wr;
	u32 mmu_miss_cnt;
	u32 mmu_pt_update_qos;
	u32 mmu_version;
	u32 mmu_min_ppn1;
	u32 mmu_ppn_range1;
	u32 mmu_min_ppn2;
	u32 mmu_ppn_range2;
	u32 mmu_vpn_paor_rd;
	u32 mmu_vpn_paor_wr;
	u32 mmu_ppn_paor_rd;
	u32 mmu_ppn_paor_wr;
	u32 mmu_reg_au_manage;
	u32 mmu_page_rd_ch;
	u32 mmu_page_wr_ch;
	u32 mmu_read_page_cmd_cnt;
	u32 mmu_read_page_latency_cnt;
	u32 mmu_page_max_latency;
};

struct wb_region {
	u32 index;
	u16 pos_x;
	u16 pos_y;
	u16 size_w;
	u16 size_h;
};

struct enhance_module {
	u32 scl_en: 1;
	u32 epf_en: 1;
	u32 hsv_en: 1;
	u32 cm_en: 1;
	u32 slp_en: 1;
	u32 gamma_en: 1;
	u32 blp_en: 1;
};

struct scale_cfg {
	u32 in_w;
	u32 in_h;
};

struct epf_cfg {
	u16 epsilon0;
	u16 epsilon1;
	s8 gain0;
	u8 gain1;
	u8 gain2;
	u8 gain3;
	s8 gain4;
	u8 gain5;
	u8 gain6;
	u8 gain7;
	u8 max_diff;
	u8 min_diff;
};

struct hsv_entry {
	u16 hue;
	u16 sat;
};

struct hsv_lut {
	struct hsv_entry table[360];
};

struct gamma_entry {
	u16 r;
	u16 g;
	u16 b;
};

struct gamma_lut {
	u16 r[256];
	u16 g[256];
	u16 b[256];
};

struct cm_cfg {
	short coef00;
	short coef01;
	short coef02;
	short coef03;
	short coef10;
	short coef11;
	short coef12;
	short coef13;
	short coef20;
	short coef21;
	short coef22;
	short coef23;
};

struct slp_cfg {
	u8 brightness;
	u8 conversion_matrix;
	u8 brightness_step;
	u8 second_bright_factor;
	u8 first_percent_th;
	u8 first_max_bright_th;
};

static struct epf_cfg epf = {
	.epsilon0 = 30,
	.epsilon1 = 1000,
	.gain0 = -8,
	.gain1 = 8,
	.gain2 = 32,
	.gain3 = 160,
	.gain4 = 24,
	.gain5 = 8,
	.gain6 = 32,
	.gain7 = 160,
	.max_diff = 80,
	.min_diff = 40,
};
static struct scale_cfg scale_copy;
static struct cm_cfg cm_copy;
static struct slp_cfg slp_copy;
static struct gamma_lut gamma_copy;
static struct hsv_lut hsv_copy;
static u32 enhance_en;

static bool need_scale;
static bool is_scaling;
static bool need_wait_te;
static bool evt_update;
static bool evt_stop;
static int wb_en;
static int max_vsync_count;
static int vsync_count;
static struct sprd_adf_hwlayer wb_layer;
static struct wb_region region[3];
static int wb_xfbc_en = 1;
static bool sprd_corner_support;
static int sprd_corner_radius;
module_param(wb_xfbc_en, int, 0644);
module_param(max_vsync_count, int, 0644);

static void dpu_enhance_reload(struct dispc_context *ctx);
static void dpu_clean(struct dispc_context *ctx);
static void dpu_layer(struct dispc_context *ctx,
		    struct sprd_adf_hwlayer *hwlayer);
static void dpu_write_back(struct dispc_context *ctx,
		struct wb_region region[], u8 count);

static u32 dpu_get_version(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	return reg->dpu_version;
}

static int dpu_parse_dt(struct dispc_context *ctx,
				struct device_node *np)
{
	int ret = 0;

	ret = of_property_read_u32(np, "sprd,corner-radius",
					&sprd_corner_radius);
	if (!ret) {
		sprd_corner_support = 1;
		pr_info("round corner support, radius = %d.\n",
					sprd_corner_radius);
	} else
		return 0;

	if (sprd_corner_support) {
		sprd_corner_hwlayer_init(ctx->panel->height,
				ctx->panel->width, sprd_corner_radius);

		/* change id value based on different dispc chip */
		corner_layer_top.hwlayer_id = 5;
		corner_layer_bottom.hwlayer_id = 6;
	}

	return 0;
}

static void check_mmu_isr(struct dispc_context *ctx, uint32_t reg_val)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	uint32_t int_mask = (DISPC_INT_MMU_VAOR_RD_MASK |
			DISPC_INT_MMU_VAOR_WR_MASK |
			DISPC_INT_MMU_INV_RD_MASK |
			DISPC_INT_MMU_INV_WR_MASK);
	uint32_t val = reg_val & int_mask;

	if (val) {
		pr_err("--- iommu interrupt err: 0x%04x ---\n", val);

		pr_err("iommu invalid read error, addr: 0x%08x\n",
			reg->mmu_inv_addr_rd);
		pr_err("iommu invalid write error, addr: 0x%08x\n",
			reg->mmu_inv_addr_wr);
		pr_err("iommu va out of range read error, addr: 0x%08x\n",
			reg->mmu_vaor_addr_rd);
		pr_err("iommu va out of range write error, addr: 0x%08x\n",
			reg->mmu_vaor_addr_wr);
		pr_err("BUG: iommu failure at %s:%d/%s()!\n",
			__FILE__, __LINE__, __func__);
		panic("iommu panic\n");
	}
}

static u32 dpu_isr(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	u32 reg_val;

	if (!reg) {
		pr_err("invalid reg\n");
		return 0;
	}

	reg_val = reg->dpu_int_sts;
	reg->dpu_int_clr = reg_val;

	/*disable err interrupt */
	if (reg_val & DISPC_INT_ERR_MASK)
		reg->dpu_int_en &= ~DISPC_INT_ERR_MASK;

	/*dpu update done isr */
	if (reg_val & DISPC_INT_UPDATE_DONE_MASK) {
		evt_update = true;
		wake_up_interruptible_all(&ctx->wait_queue);
	}

	/*dpu vsync isr */
	if (reg_val & DISPC_INT_DPI_VSYNC_MASK) {
		/*write back feature*/
		if (vsync_count == max_vsync_count && wb_en) {
			dpu_write_back(ctx, region, 1);
			schedule_work(&ctx->update_work);
		}
		vsync_count++;
	}

	/* dpu stop done isr */
	if (reg_val & DISPC_INT_DONE_MASK) {
		evt_stop = true;
		wake_up_interruptible_all(&ctx->wait_queue);
	}

	/* dpu write back done isr */
	if (reg_val & DISPC_INT_WB_DONE_MASK) {
		wb_en = false;
		/*
		 * The write back is a time-consuming operation. If there is a
		 * flip occurs before write back done, the write back buffer is
		 * no need to display. Or the new frame will be covered by the
		 * write back buffer, which is not we wanted.
		 */
		if (vsync_count > max_vsync_count) {
			dpu_clean(ctx);
			dpu_layer(ctx, &wb_layer);
			schedule_work(&ctx->update_work);
			/*reg_val |= DISPC_INT_FENCE_SIGNAL_REQUEST;*/
		}
		pr_debug("wb done\n");
	}

	/* dpu write back error isr */
	if (reg_val & DISPC_INT_WB_FAIL_MASK) {
		pr_err("dpu write back fail\n");
		/*give a new chance to write back*/
		wb_en = true;
		vsync_count = 0;
	}

	/* dpu ifbc payload error isr */
	if (reg_val & DISPC_INT_FBC_PLD_ERR_MASK)
		pr_err("dpu ifbc payload error\n");

	/* dpu ifbc header error isr */
	if (reg_val & DISPC_INT_FBC_HDR_ERR_MASK)
		pr_err("dpu ifbc header error\n");

	check_mmu_isr(ctx, reg_val);

	return reg_val;
}

static int32_t dpu_wait_stop_done(struct dispc_context *ctx)
{
	int rc;

	/* if this function was called more than once without */
	/* calling dpu_run() in the middle, return directly */
	if (ctx->is_stopped && (!evt_stop)) {
		pr_info("dpu has already stopped!\n");
		return 0;
	}

	/*wait for stop done interrupt*/
	rc = wait_event_interruptible_timeout(ctx->wait_queue, evt_stop,
					       msecs_to_jiffies(500));
	evt_stop = false;
	ctx->is_stopped = true;

	if (!rc) {
		/* time out */
		pr_err("dpu wait for stop done time out!\n");
		return -1;
	}

	return 0;
}

static int32_t dpu_wait_update_done(struct dispc_context *ctx)
{
	int rc;

	/*wait for reg update done interrupt*/
	rc = wait_event_interruptible_timeout(ctx->wait_queue, evt_update,
					       msecs_to_jiffies(500));
	evt_update = false;

	if (!rc) {
		/* time out */
		pr_err("dpu wait for reg update done time out!\n");
		return -1;
	}

	return 0;
}

static void dpu_stop(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	if (!reg)
		return;

	if (ctx->if_type == SPRD_DISPC_IF_DPI)
		reg->dpu_ctrl |= BIT(1);

	dpu_wait_stop_done(ctx);
	pr_info("dpu stop\n");
}

static void dpu_run(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	if (!reg)
		return;

	evt_update = false;

	if (ctx->if_type == SPRD_DISPC_IF_DPI) {
		if (ctx->is_stopped) {
			/* dpu run */
			reg->dpu_ctrl |= BIT(0);

			ctx->is_stopped = false;
			pr_info("dpu run\n");
		} else {
			/*dpu register update trigger*/
			reg->dpu_ctrl |= BIT(2);

			/*make sure all the regs are updated to the shadow*/
			dpu_wait_update_done(ctx);
		}

		/* if the underflow err was disabled in isr, re-enable it */
		reg->dpu_int_en |= DISPC_INT_ERR_MASK;

	} else if (ctx->if_type == SPRD_DISPC_IF_EDPI) {

		/* dpu run */
		reg->dpu_ctrl |= BIT(0);
		ctx->is_stopped = false;
		if (need_wait_te) {
		/* when backlight on, read ram speed exceed write may */
		/* display some mass on screen */
			pr_info("dpu first run need wait te\n");
			dpu_wait_stop_done(ctx);
			/*wait te*/
			mdelay(20);
			need_wait_te = false;
		}
	}
}

static void dpu_write_back(struct dispc_context *ctx,
		struct wb_region region[], u8 count)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	u16 w, h;

	if (count == 0)
		return;

	w = reg->blend_size & 0xFFFF;
	h = reg->blend_size >> 16;

	wb_layer.dst_w = w;
	wb_layer.dst_h = h;
	wb_layer.compression = wb_xfbc_en;
	wb_layer.header_size_r = XFBC8888_HEADER_SIZE(w, h);
	wb_layer.pitch[0] = w * 4;

	reg->region[0].pos = 0;
	reg->region[0].size = (w >> 3) | ((h >> 3) << 16);
	reg->wb_ctrl = BIT(0);
	reg->wb_pitch = w;

	if (wb_xfbc_en) {
		reg->wb_cfg = (2 << 1) | BIT(0);
		reg->wb_base_addr = wb_layer.iova_plane[0] +
				wb_layer.header_size_r;
	} else {
		reg->wb_cfg = 0;
		reg->wb_base_addr = wb_layer.iova_plane[0];
	}
}

static void writeback_update_handler(struct work_struct *data)
{
	int ret;
	struct dispc_context *ctx =
		container_of(data, struct dispc_context, update_work);
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	ret = down_trylock(&ctx->refresh_lock);
	if (ret != 1) {
		reg->dpu_ctrl |= BIT(2);
		dpu_wait_update_done(ctx);
		up(&ctx->refresh_lock);
	} else
		pr_debug("cannot acquire lock for wb_lock\n");
}

static int dpu_write_back_config(struct dispc_context *ctx)
{
	int ret;
	static int need_config = 1;
	struct panel_info *panel = ctx->panel;
	u32 wb_addr_v;
	size_t wb_buf_size;
	struct sprd_dispc *dispc =
		(struct sprd_dispc *)container_of(ctx, struct sprd_dispc, ctx);

	if (!need_config) {
		pr_debug("write back has configed\n");
		return 0;
	}

	wb_buf_size = XFBC8888_BUFFER_SIZE(panel->width, panel->height);
	ret = sprd_dispc_wb_buf_alloc(dispc, ION_HEAP_ID_MASK_FB,
					&wb_buf_size, &(wb_addr_v));
	if (ret)
		return -1;

	wb_layer.hwlayer_id = 7;
	wb_layer.n_planes = 1;
	wb_layer.alpha = 0xff;
	wb_layer.format = DRM_FORMAT_ABGR8888;
	wb_layer.iova_plane[0] = wb_addr_v;

	max_vsync_count = 0;
	need_config = 0;

	pr_info("wb_xfbc_en = %d\n", wb_xfbc_en);
	INIT_WORK(&ctx->update_work, writeback_update_handler);

	return 0;
}

static int dpu_init(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct panel_info *panel = ctx->panel;
	static bool is_running = true;
	u32 size;

	if (reg == NULL) {
		pr_err("dpu base address is null!");
		return -1;
	}

	if (panel == NULL) {
		pr_err("ctx->panel is null!");
		return -1;
	}

	/* set bg color */
	reg->bg_color = 0;

	/* set dpu output size */
	size = (panel->width & 0xffff) | ((panel->height) << 16);
	reg->panel_size = size;
	reg->blend_size = size;

	reg->dpu_cfg0 = 0;
	reg->dpu_cfg1 = 0x004466da;
	reg->dpu_cfg2 = 0;

	if (is_running)
		is_running = false;
	else
		dpu_clean(ctx);

	reg->mmu_en = 0;
	reg->mmu_min_ppn1 = 0;
	reg->mmu_ppn_range1 = 0xffff;
	reg->mmu_min_ppn2 = 0;
	reg->mmu_ppn_range2 = 0xffff;
	reg->mmu_vpn_range = 0x1ffff;

	reg->dpu_int_clr = 0xffff;

	dpu_enhance_reload(ctx);

	dpu_write_back_config(ctx);

	return 0;
}

static void dpu_uninit(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	if (!reg)
		return;

	reg->dpu_int_en = 0;
	reg->dpu_int_clr = 0xff;
	need_wait_te = true;
}

enum {
	DPU_LAYER_FORMAT_YUV422_2PLANE,
	DPU_LAYER_FORMAT_YUV420_2PLANE,
	DPU_LAYER_FORMAT_YUV420_3PLANE,
	DPU_LAYER_FORMAT_ARGB8888,
	DPU_LAYER_FORMAT_RGB565,
	DPU_LAYER_FORMAT_XFBC_ARGB8888 = 8,
	DPU_LAYER_FORMAT_XFBC_RGB565,
	DPU_LAYER_FORMAT_MAX_TYPES,
};

/*
 * Because in OpenGL/PNG, the RGBA color stored in memory such that R
 * is at lowest address, G after it, B after that, and A last(the highest
 * address). Which is equivalent to ABGR in DRM format. That means the
 * color order in OpenGL(Android) is inverse in DRM(kernel).
 *
 * When the function implementBufferFormatConfig() was corrected in
 * vendor/sprd/modules/hwcomposer/SprdADFWrapper.cpp, the hal_to_drm_format()
 * could be removed.
 */
static u32 hal_to_drm_format(u32 hal_format)
{
	switch (hal_format) {
	case DRM_FORMAT_RGBA8888:
		return DRM_FORMAT_ABGR8888;
	case DRM_FORMAT_RGBX8888:
		return DRM_FORMAT_XBGR8888;
	case DRM_FORMAT_BGRA8888:
		return DRM_FORMAT_ARGB8888;
	case DRM_FORMAT_RGB888:
		return DRM_FORMAT_BGR888;
	default:
		return hal_format;
	}
}

static u32 dpu_img_ctrl(u32 format, u32 blending, u32 compression)
{
	int reg_val = 0;

	/* layer enable */
	reg_val |= BIT(0);

	/* need to convert the HAL_PIXEL_FORMAT* to DRM_FORMAT* first */
	format = hal_to_drm_format(format);

	switch (format) {
	case DRM_FORMAT_BGRA8888:
		/* BGRA8888 -> ARGB8888 */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
		if (compression)
			/* XFBC-ARGB8888 */
			reg_val |= (DPU_LAYER_FORMAT_XFBC_ARGB8888 << 4);
		else
			reg_val |= (DPU_LAYER_FORMAT_ARGB8888 << 4);
		break;
	case DRM_FORMAT_RGBX8888:
	case DRM_FORMAT_RGBA8888:
		/* RGBA8888 -> ABGR8888 */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
	case DRM_FORMAT_ABGR8888:
		/* rb switch */
		reg_val |= BIT(10);
	case DRM_FORMAT_ARGB8888:
		if (compression)
			/* XFBC-ARGB8888 */
			reg_val |= (DPU_LAYER_FORMAT_XFBC_ARGB8888 << 4);
		else
			reg_val |= (DPU_LAYER_FORMAT_ARGB8888 << 4);
		break;
	case DRM_FORMAT_XBGR8888:
		/* rb switch */
		reg_val |= BIT(10);
	case DRM_FORMAT_XRGB8888:
		if (compression)
			/* XFBC-ARGB8888 */
			reg_val |= (DPU_LAYER_FORMAT_XFBC_ARGB8888 << 4);
		else
			reg_val |= (DPU_LAYER_FORMAT_ARGB8888 << 4);
		break;
	case DRM_FORMAT_BGR565:
		/* rb switch */
		reg_val |= BIT(10);
	case DRM_FORMAT_RGB565:
		if (compression)
			/* XFBC-RGB565 */
			reg_val |= (DPU_LAYER_FORMAT_XFBC_RGB565 << 4);
		else
			reg_val |= (DPU_LAYER_FORMAT_RGB565 << 4);
		break;
	case DRM_FORMAT_NV12:
		/*2-Lane: Yuv420 */
		reg_val |= DPU_LAYER_FORMAT_YUV420_2PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 10;
		break;
	case DRM_FORMAT_NV21:
		/*2-Lane: Yuv420 */
		reg_val |= DPU_LAYER_FORMAT_YUV420_2PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 10;
		break;
	case DRM_FORMAT_NV16:
		/*2-Lane: Yuv422 */
		reg_val |= DPU_LAYER_FORMAT_YUV422_2PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B3B2B1B0 << 10;
		break;
	case DRM_FORMAT_NV61:
		/*2-Lane: Yuv422 */
		reg_val |= DPU_LAYER_FORMAT_YUV422_2PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 10;
		break;
	case DRM_FORMAT_YUV420:
		reg_val |= DPU_LAYER_FORMAT_YUV420_3PLANE << 4;
		/*Y endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 8;
		/*UV endian */
		reg_val |= SPRD_IMG_DATA_ENDIAN_B0B1B2B3 << 10;
		break;
	default:
		pr_err("error: invalid format %c%c%c%c\n", format,
						format >> 8,
						format >> 16,
						format >> 24);
		break;
	}

	switch (blending) {
	case HWC_BLENDING_NONE:
		/* don't do blending, maybe RGBX */
		/* alpha mode select - layer alpha */
		reg_val |= BIT(2);
		break;
	case HWC_BLENDING_COVERAGE:
		/*Normal mode*/
		reg_val &= (~BIT(16));
		break;
	case HWC_BLENDING_PREMULT:
		/*Pre-mult mode*/
		reg_val |= BIT(16);
		break;
	default:
		/* alpha mode select - layer alpha */
		reg_val |= BIT(2);
		break;
	}

	return reg_val;
}

static void dpu_clean(struct dispc_context *ctx)
{
	int i;
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	for (i = 0; i < 8; i++)
		reg->layers[i].ctrl = 0;
}

static void dpu_bgcolor(struct dispc_context *ctx, u32 color)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;

	if (!reg)
		return;

	reg->bg_color = color;
	dpu_clean(ctx);
}

static void dpu_layer(struct dispc_context *ctx,
		    struct sprd_adf_hwlayer *hwlayer)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct layer_reg *layer;
	u32 addr;
	int size;
	int offset;
	int wd;
	int i;

	if (!reg)
		return;

	layer = &reg->layers[hwlayer->hwlayer_id];
	offset = (hwlayer->dst_x & 0xffff) | ((hwlayer->dst_y) << 16);

	if (hwlayer->start_w && hwlayer->start_h)
		size = (hwlayer->start_w & 0xffff) | ((hwlayer->start_h) << 16);
	else
		size = (hwlayer->dst_w & 0xffff) | ((hwlayer->dst_h) << 16);

	if (adf_format_is_rgb(hwlayer->format))
		wd = adf_format_bpp(hwlayer->format) / 8;
	else
		wd = adf_format_plane_cpp(hwlayer->format, 0);

	for (i = 0; i < hwlayer->n_planes; i++) {
		addr = hwlayer->iova_plane[i];

		/* dpu r2p0 just support xfbc-rgb */
		if (hwlayer->compression)
			addr += hwlayer->header_size_r;

		if (addr % 16)
			pr_err("layer addr[%d] is not 16 bytes align, it's 0x%08x\n",
				i, addr);
		layer->addr[i] = addr;
	}

	layer->pos = offset;
	layer->size = size;
	layer->crop_start = (hwlayer->start_y << 16) | hwlayer->start_x;
	layer->alpha = hwlayer->alpha;

	if (adf_format_num_planes(hwlayer->format) == 3)
		/* UV pitch is 1/2 of Y pitch*/
		layer->pitch = (hwlayer->pitch[0] / wd) |
				(hwlayer->pitch[0] / wd << 15);
	else
		layer->pitch = hwlayer->pitch[0] / wd;

	layer->ctrl = dpu_img_ctrl(hwlayer->format, hwlayer->blending,
		hwlayer->compression);

	pr_debug("dst_x = %d, dst_y = %d, dst_w = %d, dst_h = %d\n",
				hwlayer->dst_x, hwlayer->dst_y,
				hwlayer->dst_w, hwlayer->dst_h);
	pr_debug("start_x = %d, start_y = %d, start_w = %d, start_h = %d\n",
				hwlayer->start_x, hwlayer->start_y,
				hwlayer->start_w, hwlayer->start_h);
}

static void dpu_scaling(struct dispc_context *ctx,
			struct sprd_adf_hwlayer *hwlayer)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct panel_info *panel = ctx->panel;

	if (need_scale && (!is_scaling)) {
		if ((hwlayer->dst_w != panel->width) &&
		    (hwlayer->dst_h != panel->height)) {
			reg->blend_size = (hwlayer->dst_h << 16) |
					  hwlayer->dst_w;
			reg->epf_epsilon = (epf.epsilon1 << 16) |
					   epf.epsilon0;
			reg->epf_gain0_3 = (epf.gain3 << 24) |
					   (epf.gain2 << 16) |
					   (epf.gain1 << 8) |
					   epf.gain0;
			reg->epf_gain4_7 = (epf.gain7 << 24) |
					   (epf.gain6 << 16) |
					   (epf.gain5 << 8) |
					   epf.gain4;
			reg->epf_diff = (epf.max_diff << 8) |
					epf.min_diff;
			reg->dpu_enhance_cfg |= (BIT(0) | BIT(1));
			enhance_en |= (BIT(0) | BIT(1));
			is_scaling = true;
			pr_info("top layer is %d x %d, start scaling\n",
				hwlayer->dst_w, hwlayer->dst_h);
		} else
			pr_info("top layer is %d x %d, no need to scale\n",
				hwlayer->dst_w, hwlayer->dst_h);
	}

	if ((!need_scale) && is_scaling) {
		if ((hwlayer->dst_w == panel->width) &&
		    (hwlayer->dst_h == panel->height)) {
			reg->blend_size = (panel->height << 16) |
					  panel->width;
			reg->dpu_enhance_cfg &= ~(BIT(0) | BIT(1));
			enhance_en &= ~(BIT(0) | BIT(1));
			is_scaling = false;
			pr_info("top layer is %d x %d, stop scaling\n",
				hwlayer->dst_w, hwlayer->dst_h);
		} else
			pr_info("top layer is %d x %d, keep scaling\n",
				hwlayer->dst_w, hwlayer->dst_h);
	}
}

static void dpu_flip(struct dispc_context *ctx,
			struct sprd_restruct_config *config)
{
	int i;
	struct sprd_adf_hwlayer *hwlayer = NULL;

	/* make sure the dpu is in stop status, sharkl3 edpi no shadow regs */
	/* can only be updated in the rising edge of dpu_RUN bit */
	if (ctx->if_type == SPRD_DISPC_IF_EDPI)
		dpu_wait_stop_done(ctx);

	vsync_count = 0;
	if (max_vsync_count && (config->number_hwlayer > 1))
		wb_en = true;
	else
		wb_en = false;

	dpu_clean(ctx);

	for (i = 0; i < config->number_hwlayer; i++) {
		hwlayer = &config->hwlayers[i];
		dpu_layer(ctx, hwlayer);
	}

	if (sprd_corner_support) {
		dpu_layer(ctx, &corner_layer_top);
		dpu_layer(ctx, &corner_layer_bottom);
	}

	/*
	 * The scaling can only be triggered in bootanimation & Settings UI.
	 * So just check the top layer size to enable/disable dpu scaling.
	 */
	dpu_scaling(ctx, hwlayer);
}

static void dpu_dpi_init(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct panel_info *panel = ctx->panel;
	struct rgb_timing *rgb;
	u32 reg_val = 0;
	u32 int_mask = 0;

	if (!reg || !panel)
		return;

	int_mask |= (DISPC_INT_MMU_VAOR_RD_MASK |
		DISPC_INT_MMU_VAOR_WR_MASK |
		DISPC_INT_MMU_INV_RD_MASK |
		DISPC_INT_MMU_INV_WR_MASK);

	if (ctx->if_type == SPRD_DISPC_IF_DPI) {
		/*use dpi as interface */
		reg->dpu_cfg0 &= ~(BIT(0));

		/* disable Halt function for SPRD DSI */
		/* reg_val |= BIT(16); */

		reg->dpi_ctrl = reg_val;

		rgb = &panel->rgb_timing;
		/* set dpi timing */
		reg->dpi_h_timing = (rgb->hsync << 0) |
				(rgb->hbp << 8) |
				(rgb->hfp << 20);
		reg->dpi_v_timing = (rgb->vsync << 0) |
				(rgb->vbp << 8) |
				(rgb->vfp << 20);

		/*enable dpu update done INT */
		int_mask |= DISPC_INT_UPDATE_DONE_MASK;
		/* enable dpu DONE  INT */
		int_mask |= DISPC_INT_DONE_MASK;
		/* enable dpu dpi vsync */
		int_mask |= DISPC_INT_DPI_VSYNC_MASK;
		/* enable dpu TE INT */
		int_mask |= DISPC_INT_TE_MASK;
		/* enable underflow err INT */
		int_mask |= DISPC_INT_ERR_MASK;
		/* enable write back done INT */
		int_mask |= DISPC_INT_WB_DONE_MASK;
		/* enable write back fail INT */
		int_mask |= DISPC_INT_WB_FAIL_MASK;
		/* enable ifbc payload error INT */
		int_mask |= DISPC_INT_FBC_PLD_ERR_MASK;
		/* enable ifbc header error INT */
		int_mask |= DISPC_INT_FBC_HDR_ERR_MASK;

		reg->dpu_int_en = int_mask;

	} else if (ctx->if_type == SPRD_DISPC_IF_EDPI) {
		/*use edpi as interface */
		reg->dpu_cfg0 |= BIT(0);

		/*te pol */
		if (panel->te_pol == SPRD_POLARITY_NEG)
			reg_val |= BIT(9);

		/*use external te */
		reg_val |= BIT(10);

		/*enable te */
		reg_val |= BIT(8);

		reg->dpi_ctrl = reg_val;

		/* enable dpu DONE  INT */
		int_mask |= DISPC_INT_DONE_MASK;
		/* enable DISPC TE  INT for edpi*/
		int_mask |= DISPC_INT_TE_MASK;
		/* enable ifbc payload error INT */
		int_mask |= DISPC_INT_FBC_PLD_ERR_MASK;
		/* enable ifbc header error INT */
		int_mask |= DISPC_INT_FBC_HDR_ERR_MASK;

		reg->dpu_int_en = int_mask;
	}
}

static void dpu_enhance_set(struct dispc_context *ctx, u32 id, void *param)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct scale_cfg *scale;
	struct cm_cfg *cm;
	struct slp_cfg *slp;
	struct gamma_lut *gamma;
	struct hsv_lut *hsv;
	u32 *p;
	int i;

	if (!reg)
		return;

	switch (id) {
	case ENHANCE_CFG_ID_ENABLE:
		p = param;
		reg->dpu_enhance_cfg |= *p;
		pr_info("enhance module enable: 0x%x\n", *p);
		break;
	case ENHANCE_CFG_ID_DISABLE:
		p = param;
		reg->dpu_enhance_cfg &= ~(*p);
		pr_info("enhance module disable: 0x%x\n", *p);
		break;
	case ENHANCE_CFG_ID_SCL:
		memcpy(&scale_copy, param, sizeof(scale_copy));
		scale = &scale_copy;
		reg->blend_size = (scale->in_h << 16) | scale->in_w;
		reg->epf_epsilon = (epf.epsilon1 << 16) | epf.epsilon0;
		reg->epf_gain0_3 = (epf.gain3 << 24) | (epf.gain2 << 16) |
				(epf.gain1 << 8) | epf.gain0;
		reg->epf_gain4_7 = (epf.gain7 << 24) | (epf.gain6 << 16) |
				(epf.gain5 << 8) | epf.gain4;
		reg->epf_diff = (epf.max_diff << 8) | epf.min_diff;
		reg->dpu_enhance_cfg |= (BIT(0) | BIT(1));
		pr_info("enhance scaling: %ux%u\n", scale->in_w, scale->in_h);
		break;
	case ENHANCE_CFG_ID_HSV:
		memcpy(&hsv_copy, param, sizeof(hsv_copy));
		hsv = &hsv_copy;
		for (i = 0; i < 360; i++) {
			reg->hsv_lut_addr = i;
			udelay(1);
			reg->hsv_lut_wdata = (hsv->table[i].sat << 16) |
						hsv->table[i].hue;
		}
		reg->dpu_enhance_cfg |= BIT(2);
		pr_info("enhance hsv set\n");
		break;
	case ENHANCE_CFG_ID_CM:
		memcpy(&cm_copy, param, sizeof(cm_copy));
		cm = &cm_copy;
		reg->cm_coef01_00 = (cm->coef01 << 16) | cm->coef00;
		reg->cm_coef03_02 = (cm->coef03 << 16) | cm->coef02;
		reg->cm_coef11_10 = (cm->coef11 << 16) | cm->coef10;
		reg->cm_coef13_12 = (cm->coef13 << 16) | cm->coef12;
		reg->cm_coef21_20 = (cm->coef21 << 16) | cm->coef20;
		reg->cm_coef23_22 = (cm->coef23 << 16) | cm->coef22;
		reg->dpu_enhance_cfg |= BIT(3);
		pr_info("enhance cm set\n");
		break;
	case ENHANCE_CFG_ID_SLP:
		memcpy(&slp_copy, param, sizeof(slp_copy));
		slp = &slp_copy;
		reg->slp_cfg0 = (slp->second_bright_factor << 24) |
				(slp->brightness_step << 16) |
				(slp->conversion_matrix << 8) |
				slp->brightness;
		reg->slp_cfg1 = (slp->first_max_bright_th << 8) |
				slp->first_percent_th;
		reg->dpu_enhance_cfg |= BIT(4);
		pr_info("enhance slp set\n");
		break;
	case ENHANCE_CFG_ID_GAMMA:
		memcpy(&gamma_copy, param, sizeof(gamma_copy));
		gamma = &gamma_copy;
		for (i = 0; i < 256; i++) {
			reg->gamma_lut_addr = i;
			udelay(1);
			reg->gamma_lut_wdata = (gamma->r[i] << 20) |
						(gamma->g[i] << 10) |
						gamma->b[i];
			pr_debug("0x%02x: r=%u, g=%u, b=%u\n", i,
				gamma->r[i], gamma->g[i], gamma->b[i]);
		}
		reg->dpu_enhance_cfg |= BIT(5);
		pr_info("enhance gamma set\n");
		break;
	default:
		break;
	}

	/* update trigger */
	reg->dpu_ctrl |= BIT(2);
	dpu_wait_update_done(ctx);

	enhance_en = reg->dpu_enhance_cfg;
}

static void dpu_enhance_get(struct dispc_context *ctx, u32 id, void *param)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct scale_cfg *scale;
	struct epf_cfg *ep;
	struct slp_cfg *slp;
	struct gamma_lut *gamma;
	u32 *p32;
	int i, val;

	if (!reg)
		return;

	switch (id) {
	case ENHANCE_CFG_ID_ENABLE:
		p32 = param;
		*p32 = reg->dpu_enhance_cfg;
		pr_info("enhance module enable get\n");
		break;
	case ENHANCE_CFG_ID_SCL:
		scale = param;
		val = reg->blend_size;
		scale->in_w = val & 0xffff;
		scale->in_h = val >> 16;
		pr_info("enhance scaling get\n");
		break;
	case ENHANCE_CFG_ID_EPF:
		ep = param;

		val = reg->epf_epsilon;
		ep->epsilon0 = val;
		ep->epsilon1 = val >> 16;

		val = reg->epf_gain0_3;
		ep->gain0 = val;
		ep->gain1 = val >> 8;
		ep->gain2 = val >> 16;
		ep->gain3 = val >> 24;

		val = reg->epf_gain4_7;
		ep->gain4 = val;
		ep->gain5 = val >> 8;
		ep->gain6 = val >> 16;
		ep->gain7 = val >> 24;

		val = reg->epf_diff;
		ep->min_diff = val;
		ep->max_diff = val >> 8;
		pr_info("enhance epf get\n");
		break;
	case ENHANCE_CFG_ID_HSV:
		dpu_stop(ctx);
		p32 = param;
		for (i = 0; i < 360; i++) {
			reg->hsv_lut_addr = i;
			udelay(1);
			*p32++ = reg->hsv_lut_rdata;
		}
		dpu_run(ctx);
		pr_info("enhance hsv get\n");
		break;
	case ENHANCE_CFG_ID_CM:
		p32 = param;
		*p32++ = reg->cm_coef01_00;
		*p32++ = reg->cm_coef03_02;
		*p32++ = reg->cm_coef11_10;
		*p32++ = reg->cm_coef13_12;
		*p32++ = reg->cm_coef21_20;
		*p32++ = reg->cm_coef23_22;
		pr_info("enhance cm get\n");
		break;
	case ENHANCE_CFG_ID_SLP:
		slp = param;

		val = reg->slp_cfg0;
		slp->brightness = val;
		slp->conversion_matrix = val >> 8;
		slp->brightness_step = val >> 16;
		slp->second_bright_factor = val >> 24;

		val = reg->slp_cfg1;
		slp->first_percent_th = val;
		slp->first_max_bright_th = val >> 8;
		pr_info("enhance slp get\n");
		break;
	case ENHANCE_CFG_ID_GAMMA:
		dpu_stop(ctx);
		gamma = param;
		for (i = 0; i < 256; i++) {
			reg->gamma_lut_addr = i;
			udelay(1);
			val = reg->gamma_lut_rdata;
			gamma->r[i] = (val >> 20) & 0x3FF;
			gamma->g[i] = (val >> 10) & 0x3FF;
			gamma->b[i] = val & 0x3FF;
			pr_debug("0x%02x: r=%u, g=%u, b=%u\n", i,
				gamma->r[i], gamma->g[i], gamma->b[i]);
		}
		dpu_run(ctx);
		pr_info("enhance gamma get\n");
		break;
	default:
		break;
	}
}

static void dpu_enhance_reload(struct dispc_context *ctx)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct panel_info *panel = ctx->panel;
	struct scale_cfg *scale;
	struct cm_cfg *cm;
	struct slp_cfg *slp;
	struct gamma_lut *gamma;
	struct hsv_lut *hsv;
	int i;

	if (!reg)
		return;

	if (enhance_en & BIT(0)) {
		scale = &scale_copy;
		reg->blend_size = (scale->in_h << 16) | scale->in_w;
		pr_info("enhance scaling from %ux%u to %ux%u\n",
			scale->in_w, scale->in_h, panel->width, panel->height);
	}

	if (enhance_en & BIT(1)) {
		reg->epf_epsilon = (epf.epsilon1 << 16) | epf.epsilon0;
		reg->epf_gain0_3 = (epf.gain3 << 24) | (epf.gain2 << 16) |
				(epf.gain1 << 8) | epf.gain0;
		reg->epf_gain4_7 = (epf.gain7 << 24) | (epf.gain6 << 16) |
				(epf.gain5 << 8) | epf.gain4;
		reg->epf_diff = (epf.max_diff << 8) | epf.min_diff;
	}

	if (enhance_en & BIT(2)) {
		hsv = &hsv_copy;
		for (i = 0; i < 360; i++) {
			reg->hsv_lut_addr = i;
			udelay(1);
			reg->hsv_lut_wdata = (hsv->table[i].sat << 16) |
						hsv->table[i].hue;
		}
		pr_info("enhance hsv reload\n");
	}

	if (enhance_en & BIT(3)) {
		cm = &cm_copy;
		reg->cm_coef01_00 = (cm->coef01 << 16) | cm->coef00;
		reg->cm_coef03_02 = (cm->coef03 << 16) | cm->coef02;
		reg->cm_coef11_10 = (cm->coef11 << 16) | cm->coef10;
		reg->cm_coef13_12 = (cm->coef13 << 16) | cm->coef12;
		reg->cm_coef21_20 = (cm->coef21 << 16) | cm->coef20;
		reg->cm_coef23_22 = (cm->coef23 << 16) | cm->coef22;
		pr_info("enhance cm reload\n");
	}

	if (enhance_en & BIT(4)) {
		slp = &slp_copy;
		reg->slp_cfg0 = (slp->second_bright_factor << 24) |
				(slp->brightness_step << 16) |
				(slp->conversion_matrix << 8) |
				slp->brightness;
		reg->slp_cfg1 = (slp->first_max_bright_th << 8) |
				slp->first_percent_th;
		pr_info("enhance slp reload\n");
	}

	if (enhance_en & BIT(5)) {
		gamma = &gamma_copy;
		for (i = 0; i < 256; i++) {
			reg->gamma_lut_addr = i;
			udelay(1);
			reg->gamma_lut_wdata = (gamma->r[i] << 20) |
						(gamma->g[i] << 10) |
						gamma->b[i];
			pr_debug("0x%02x: r=%u, g=%u, b=%u\n", i,
				gamma->r[i], gamma->g[i], gamma->b[i]);
		}
		pr_info("enhance gamma reload\n");
	}

	reg->dpu_enhance_cfg = enhance_en;
}

static int dpu_modeset(struct dispc_context *ctx,
		struct drm_mode_modeinfo *mode)
{
	struct dpu_reg *reg = (struct dpu_reg *)ctx->base;
	struct panel_info *panel = ctx->panel;

	if (!reg)
		return -ENODEV;

	scale_copy.in_w = mode->hdisplay;
	scale_copy.in_h = mode->vdisplay;

	if ((mode->hdisplay != panel->width) ||
	    (mode->vdisplay != panel->height))
		need_scale = true;
	else
		need_scale = false;

	pr_info("begin switch to %u x %u\n", mode->hdisplay, mode->vdisplay);

	return 0;
}

static struct dispc_core_ops dpu_lite_r2p0_ops = {
	.parse_dt = dpu_parse_dt,
	.version = dpu_get_version,
	.init = dpu_init,
	.uninit = dpu_uninit,
	.run = dpu_run,
	.stop = dpu_stop,
	.isr = dpu_isr,
	.ifconfig = dpu_dpi_init,
	.flip = dpu_flip,
	.bg_color = dpu_bgcolor,
	.enhance_set = dpu_enhance_set,
	.enhance_get = dpu_enhance_get,
	.modeset = dpu_modeset,
};

static struct ops_entry entry = {
	.ver = "dpu-lite-r2p0",
	.ops = &dpu_lite_r2p0_ops,
};

static int __init dispc_core_register(void)
{
	return dispc_core_ops_register(&entry);
}

subsys_initcall(dispc_core_register);
