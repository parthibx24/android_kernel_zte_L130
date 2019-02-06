#ifndef _MIPI_DPHY_COMMON_H_
#define _MIPI_DPHY_COMMON_H_

#include <asm/types.h>
#include <linux/regmap.h>

#include "disp_lib.h"
#include "sprd_panel.h"

struct dphy_context {
	struct regmap *regmap;
	unsigned long ctrlbase;
	unsigned long apbbase;
	u32 freq;
	u8 lanes;
	u8 id;
	u32 chip_id;
	struct mutex hop_lock;
};

struct dphy_pll_ops {
	int (*pll_config)(struct dphy_context *ctx);
	int (*timing_config)(struct dphy_context *ctx);
	int (*hop_config)(struct dphy_context *ctx, int delta, int period);
	int (*ssc_en)(struct dphy_context *ctx, bool en);
	void (*force_pll)(struct dphy_context *ctx, int force);
};

struct dphy_ppi_ops {
	void (*rstz)(struct dphy_context *ctx, int level);
	void (*shutdownz)(struct dphy_context *ctx, int level);
	void (*force_pll)(struct dphy_context *ctx, int force);
	void (*clklane_ulps_rqst)(struct dphy_context *ctx, int en);
	void (*clklane_ulps_exit)(struct dphy_context *ctx, int en);
	void (*datalane_ulps_rqst)(struct dphy_context *ctx, int en);
	void (*datalane_ulps_exit)(struct dphy_context *ctx, int en);
	void (*stop_wait_time)(struct dphy_context *ctx, u8 byte_clk);
	void (*datalane_en)(struct dphy_context *ctx);
	void (*clklane_en)(struct dphy_context *ctx, int en);
	void (*clk_hs_rqst)(struct dphy_context *ctx, int en);
	u8 (*is_rx_direction)(struct dphy_context *ctx);
	u8 (*is_pll_locked)(struct dphy_context *ctx);
	u8 (*is_rx_ulps_esc_lane0)(struct dphy_context *ctx);
	u8 (*is_stop_state_clklane)(struct dphy_context *ctx);
	u8 (*is_stop_state_datalane)(struct dphy_context *ctx);
	u8 (*is_ulps_active_datalane)(struct dphy_context *ctx);
	u8 (*is_ulps_active_clklane)(struct dphy_context *ctx);
	void (*tst_clk)(struct dphy_context *ctx, u8 level);
	void (*tst_clr)(struct dphy_context *ctx, u8 level);
	void (*tst_en)(struct dphy_context *ctx, u8 level);
	u8 (*tst_dout)(struct dphy_context *ctx);
	void (*tst_din)(struct dphy_context *ctx, u8 data);
	void (*bist_en)(struct dphy_context *ctx, int en);
	u8 (*is_bist_ok)(struct dphy_context *ctx);
};

struct dphy_glb_ops {
	int (*parse_dt)(struct dphy_context *ctx,
			struct device_node *np);
	void (*enable)(struct dphy_context *ctx);
	void (*disable)(struct dphy_context *ctx);
	void (*power)(struct dphy_context *ctx, int enable);
};

struct sprd_dphy {
	struct device dev;
	struct dphy_context ctx;
	struct dphy_ppi_ops *ppi;
	struct dphy_pll_ops *pll;
	struct dphy_glb_ops *glb;
	struct panel_info *panel;
};

extern struct list_head dphy_pll_head;
extern struct list_head dphy_ppi_head;
extern struct list_head dphy_glb_head;

#define dphy_pll_ops_register(entry) \
	disp_ops_register(entry, &dphy_pll_head)
#define dphy_ppi_ops_register(entry) \
	disp_ops_register(entry, &dphy_ppi_head)
#define dphy_glb_ops_register(entry) \
	disp_ops_register(entry, &dphy_glb_head)

#define dphy_pll_ops_attach(str) \
	disp_ops_attach(str, &dphy_pll_head)
#define dphy_ppi_ops_attach(str) \
	disp_ops_attach(str, &dphy_ppi_head)
#define dphy_glb_ops_attach(str) \
	disp_ops_attach(str, &dphy_glb_head)

int mipi_dphy_configure(struct sprd_dphy *dphy);
void mipi_dphy_reset(struct sprd_dphy *dphy);
int mipi_dphy_hop_config(struct sprd_dphy *dphy, int delta, int period);
int mipi_dphy_ssc_en(struct sprd_dphy *dphy, bool en);
int mipi_dphy_close(struct sprd_dphy *dphy);
int mipi_dphy_wakeup_pll(struct sprd_dphy *dphy);
int mipi_dphy_data_ulps_en(struct sprd_dphy *dphy, int enable);
int mipi_dphy_clk_ulps_en(struct sprd_dphy *dphy, int enable);
void mipi_dphy_hs_clk_en(struct sprd_dphy *dphy, int enable);
void mipi_dphy_test_write(struct sprd_dphy *dphy, u8 address, u8 data);
u8 mipi_dphy_test_read(struct sprd_dphy *dphy, u8 address);

#endif /* _MIPI_DPHY_COMMON_H_ */
