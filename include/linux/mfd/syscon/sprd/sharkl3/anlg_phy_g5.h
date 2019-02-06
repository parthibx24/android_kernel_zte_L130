/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-27 19:24:15
 *
 */


#ifndef ANLG_PHY_G5_H
#define ANLG_PHY_G5_H



#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_PWR_CTRL        (0x0000)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_SINE_CTRL       (0x0004)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_BB_BG_CTRL             (0x0008)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANALOG_TEST            (0x000C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL0             (0x0010)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL1             (0x0014)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL2             (0x0018)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL3             (0x001C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL4             (0x0020)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_CTRL1           (0x0024)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_CTRL1           (0x0028)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_CTRL1             (0x002C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_RSVD            (0x0030)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_CTRL          (0x0034)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_CTRL0             (0x003C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_CTRL1             (0x0040)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_BB_WCN_CTRL1           (0x0044)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_BB_USB20_26M_CTRL      (0x0048)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_WRAP_GLUE_CTRL         (0x004C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_CTRL2             (0x0050)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_CTRL          (0x0054)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS0          (0x0058)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C0_R0     (0x005C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C0_R1     (0x0060)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C0_R2     (0x0064)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C0_R3     (0x0068)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C1_R0     (0x006C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C1_R1     (0x0070)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C1_R2     (0x0074)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C1_R3     (0x0078)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C2_R0     (0x007C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C2_R1     (0x0080)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C2_R2     (0x0084)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C2_R3     (0x0088)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C3_R0     (0x008C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C3_R1     (0x0090)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C3_R2     (0x0094)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C3_R3     (0x0098)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_DUMY            (0x009C)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_RAMP_CTRL0        (0x00A0)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_RAMP_CTRL1        (0x00A4)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_REG_SEL_CFG_0          (0x00A8)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_REG_SEL_CFG_1          (0x00AC)
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_REF_SEL      (0x00B0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_PWR_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_PD                       BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_PD                       BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_REC_26MHZ_0_BUF_PD              BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_BB_BG_PD                        BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_SINE_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_REC_26MHZ_0_CUR_SEL(x)          (((x) & 0x3) << 17)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_SEL(x)                    (((x) & 0x3F) << 11)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_SINDRV_ENA                      BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_SINDRV_ENA_SQUARE               BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_SINE_DRV_SEL                    BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_CLK26M_RESERVED(x)              (((x) & 0xF) << 4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_REC_26MHZ_SR_TRIM(x)            (((x) & 0xF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_BB_BG_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_BB_BG_RBIAS_MODE                BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_BB_CON_BG                       BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANALOG_TEST */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_ANALOG_TESTMUX(x)               (((x) & 0xFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_MACRO_TYPE(x)              (((x) & 0xFF) << 24)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_REG_VERSION(x)             (((x) & 0xF) << 20)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_N(x)                       (((x) & 0x7FF) << 8)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_IBIAS(x)                   (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_LPF(x)                     (((x) & 0x7) << 3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_SDM_EN                     BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_MOD_EN                     BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_DIV_S                      BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_NINT(x)                    (((x) & 0x7F) << 23)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_KINT(x)                    (((x) & 0x7FFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL2 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_LOCK_DONE                  BIT(31)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_26M_SEL                    BIT(29)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_RST                        BIT(25)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_PD                         BIT(24)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_REF_SEL(x)                 (((x) & 0x3) << 20)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_DIV_EN                     BIT(11)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_DIV1_EN                    BIT(1)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL3 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_RESERVED(x)                (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_26M_DIV(x)                 (((x) & 0x3F) << 8)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_SSC_CTRL(x)                (((x) & 0xFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL4 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_CTRL(x)               (((x) & 0xFF) << 17)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_EN                    BIT(16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_CNT(x)                (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_CTRL1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_RESERVED(x)              (((x) & 0x3) << 18)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_APCOUT_SEL(x)                 (((x) & 0x3) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_LOW_V_CON                BIT(15)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_BPRES                    BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_D(x)                     (((x) & 0x3FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_CTRL1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_RESERVED(x)              (((x) & 0x3) << 18)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_APCOUT_SEL(x)                 (((x) & 0x3) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_LOW_V_CON                BIT(15)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_BPRES                    BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_D(x)                     (((x) & 0x3FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_CTRL1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_G0(x)                      (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_G1(x)                      (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_G2(x)                      (((x) & 0x3))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_RSVD */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_RESERVED(x)              (((x) & 0xFF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_LVDSRFPLL_REF_SEL(x)            (((x) & 0x3))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_EN                     BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_OD                     BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_DIV(x)                 (((x) & 0x3))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_CTRL0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_ADCLDOREF(x)            (((x) & 0x1F) << 12)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_ADCLDO_V(x)             (((x) & 0xF) << 8)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_CHOP_CLKSEL(x)          (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_CLKSEL(x)               (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_BIAS(x)           (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_UGBUF_BIAS(x)           (((x) & 0x3))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_CTRL1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_VCMI(x)           (((x) & 0x3) << 14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_VCMO(x)           (((x) & 0x3) << 12)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_UGBUF_CTRL(x)                (((x) & 0x3) << 10)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_ADCLDO_EN               BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_CAPCHOP_EN        BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_CHOP_EN           BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_UGBUF_CHOP_EN           BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_EN                BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_OFFSET_EN         BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_INPUT_EN                BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_UGBUF_EN                BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_DATA_EDGE_SEL     BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_DOUT_TSEN_SDADC                 BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_BB_WCN_CTRL1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_WCN_ATE_SEL                     BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_WCN_LDO_EN                      BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_WCN_CLK_PATH_VDDRES(x)          (((x) & 0x7) << 9)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_WCN_FASTCHARGE_EN               BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_WCN_CLK_EN                      BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_WCN_CLK_DIFF_EN                 BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_WCN_DRIVE_CTRL(x)               (((x) & 0x7) << 3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_WCN_LDO_OUT(x)                  (((x) & 0x7))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_BB_USB20_26M_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_CLK26MHZ_U2_SEL                 BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_CLK26MHZ_U2_EN                  BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_WRAP_GLUE_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_PD_SEL                     BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_RST_SEL                    BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_CTRL2 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_RSTN              BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_SDADC_CLK_MUX           BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_RESERVED(x)             (((x) & 0xFF) << 5)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_BIST_EN                 BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_BIST_CODE(x)            (((x) & 0x7) << 1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RG_TSEN_TEST_CLK_SEL            BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_CTRL_RESERVED(x)           (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_CFG3(x)           (((x) & 0x7) << 13)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_CFG2(x)           (((x) & 0x7) << 10)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_CFG1(x)           (((x) & 0x7) << 7)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_CFG0(x)           (((x) & 0x7) << 4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_CODE(x)           (((x) & 0x7) << 1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_EN                BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_STS0_RESERVED(x)           (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_STS0_RESERVED1(x)          (((x) & 0x1F) << 11)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_CODE_SEL          BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_TIME_SEL_CFG3(x)  (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_TIME_SEL_CFG2(x)  (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_TIME_SEL_CFG1(x)  (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_TIME_SEL_CFG0(x)  (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_BYPASS            BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_BIST_DONE              BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C0_R0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_STS0_C0_R0_RESERVED(x)     (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C0_RES0(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C0_R1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C0_R1_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C0_RES1(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C0_R2 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C0_R2_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C0_RES2(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C0_R3 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C0_R3_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C0_RES3(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C1_R0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C1_R0_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C1_RES0(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C1_R1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C1_R1_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C1_RES1(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C1_R2 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C1_R2_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C1_RES2(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C1_R3 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C1_R3_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C1_RES3(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C2_R0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C2_R0_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C2_RES0(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C2_R1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C2_R1_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C2_RES1(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C2_R2 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C2_R2_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C2_RES2(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C2_R3 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C2_R3_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C2_RES3(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C3_R0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C3_R0_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C3_RES0(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C3_R1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C3_R1_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C3_RES1(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C3_R2 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C3_R2_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C3_RES2(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_STS_C3_R3 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TSEN_C3_R3_RESERVED(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TST_TSEN_C3_RES3(x)             (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_DUMY */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_ANALOG_BB_DUMY_IN(x)            (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_ANALOG_BB_DUMY_OUT(x)           (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_RAMP_CTRL0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RAMP_AAPC_MAX_RANGE(x)          (((x) & 0x3FFF) << 14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RAMP_AAPC_MIN_RANGE(x)          (((x) & 0x3FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_RAMP_CTRL1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RAMP_AAPC_FREQ_SEL(x)           (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RAMP_AAPC_STEP_SEL(x)           (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RAMP_AAPC_DATA_SEL              BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RAMP_AAPC_RSTN                  BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_REG_SEL_CFG_0 */

#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_PD               BIT(31)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_PD               BIT(30)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_REC_26MHZ_0_BUF_PD      BIT(29)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_SINDRV_ENA              BIT(28)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_SINDRV_ENA_SQUARE       BIT(27)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_N                  BIT(26)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_IBIAS              BIT(25)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_LPF                BIT(24)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_SDM_EN             BIT(23)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_MOD_EN             BIT(22)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_DIV_S              BIT(21)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_NINT               BIT(20)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_KINT               BIT(19)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_PD                 BIT(18)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_RST                BIT(17)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_REF_SEL            BIT(16)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_RESERVED           BIT(15)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_26M_DIV            BIT(14)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_BIST_CTRL          BIT(13)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_BIST_EN            BIT(12)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_RESERVED         BIT(11)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_APCOUT_SEL            BIT(10)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_LOW_V_CON        BIT(9)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_BPRES            BIT(8)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_D                BIT(7)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_RESERVED         BIT(6)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_APCOUT_SEL            BIT(5)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_LOW_V_CON        BIT(4)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_BPRES            BIT(3)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_D                BIT(2)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_AAPC_G0                 BIT(1)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_AAPC_G1                 BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_REG_SEL_CFG_1 */

#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_DIV_EN             BIT(8)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_DIV1_EN            BIT(7)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_AAPC_G2                 BIT(6)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RG_TSEN_SDADC_RSTN      BIT(5)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RG_TSEN_SDADC_CLK_MUX   BIT(4)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RG_TSEN_RESERVED        BIT(3)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RG_TSEN_BIST_EN         BIT(2)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RG_TSEN_BIST_CODE       BIT(1)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RG_TSEN_TEST_CLK_SEL    BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_REF_SEL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_REF_SEL(x)            (((x) & 0x3))


#endif /* ANLG_PHY_G5_H */

