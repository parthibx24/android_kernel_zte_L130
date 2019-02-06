/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-06-28 19:05:48
 *
 */


#ifndef PUB_APB_H
#define PUB_APB_H



#define REG_PUB_APB_DDR_EB                          (0x0000)
#define REG_PUB_APB_DDR_SOFT_RST                    (0x0004)
#define REG_PUB_APB_DDL_MASK_CTRL                   (0x1000)
#define REG_PUB_APB_LP_COMPITABLE_WITH_L3           (0x3100)
#define REG_PUB_APB_PUB_DDR_CHN_LP_CTRL             (0x3104)
#define REG_PUB_APB_AXI_LPC_CTRL_PUNUM_CFG_0        (0x3108)
#define REG_PUB_APB_AXI_LPC_CTRL_PUNUM_CFG_1        (0x310C)
#define REG_PUB_APB_AXI_LPC_CTRL_PUNUM_DPU_ISP      (0x3110)
#define REG_PUB_APB_AXI_LPC_CTRL_PUNUM_ISP_VDSP     (0x3114)
#define REG_PUB_APB_AXI_LPC_CTRL_PUNUM_AP_0         (0x3118)
#define REG_PUB_APB_AXI_LPC_CTRL_PUNUM_AP_1         (0x311C)
#define REG_PUB_APB_AXI_LPC_CTRL_PUNUM_PUB_AG_IPA2  (0x3120)
#define REG_PUB_APB_DMC_EXT_LPCTRL_CFG              (0x31A0)
#define REG_PUB_APB_DMC_EXT_LPCTRL_SEQL             (0x31A4)
#define REG_PUB_APB_DMC_EXT_LPCTRL_SEQH             (0x31A8)
#define REG_PUB_APB_DMC_EXT_LPCTRL_STEP             (0x31AC)
#define REG_PUB_APB_QOS_SELECT                      (0x31B0)
#define REG_PUB_APB_DPLL_PRE_DIV_STATUS             (0x31C0)
#define REG_PUB_APB_DFI_BWMON_TIMER                 (0x31C4)
#define REG_PUB_APB_QOS_SWITCH                      (0x31C8)
#define REG_PUB_APB_PUB_BUS_CK_EB                   (0x31CC)
#define REG_PUB_APB_AXI_LPC_CTRL_3                  (0x31D0)
#define REG_PUB_APB_PUB_INT_CG_EN                   (0x31D4)
#define REG_PUB_APB_TIMER_ENABLE                    (0x31D8)
#define REG_PUB_APB_VOTE_CTRL                       (0x31E0)
#define REG_PUB_APB_VOTE_STATUS                     (0x31E4)
#define REG_PUB_APB_DFS_HW_CTRL3                    (0x31F0)
#define REG_PUB_APB_QOS_FIXED_CTRL0                 (0x31F4)
#define REG_PUB_APB_QOS_FIXED_CTRL1                 (0x31F8)
#define REG_PUB_APB_QOS_FIXED_CTRL2                 (0x31FC)
#define REG_PUB_APB_PUB_AXI_QOS_URGENT_REG_0        (0x3200)
#define REG_PUB_APB_PUB_AXI_QOS_URGENT_REG_1        (0x3204)
#define REG_PUB_APB_PUB_INT_CTRL                    (0x32F0)
#define REG_PUB_APB_DFS_STATUS                      (0x32F4)
#define REG_PUB_APB_DFS_STATUS1                     (0x32F8)
#define REG_PUB_APB_DFS_FC_REQ_DELAY                (0x32FC)
#define REG_PUB_APB_PUB_LP_GEN_CTRL                 (0x333C)
#define REG_PUB_APB_AXI_LPC_CTRL_0                  (0x334C)
#define REG_PUB_APB_AXI_LPC_CTRL_1                  (0x3350)
#define REG_PUB_APB_AXI_LPC_CTRL_2                  (0x3354)
#define REG_PUB_APB_FENCING_CTRL                    (0x3358)
#define REG_PUB_APB_CP_ESE_BASE_ADDR                (0x3360)
#define REG_PUB_APB_CLK_PUB_DFS_CTRL                (0x3364)
#define REG_PUB_APB_BIST_CTRL                       (0x3400)
#define REG_PUB_APB_DMC_SOFT_RST_CTRL               (0x3404)
#define REG_PUB_APB_MC_IDLE_WAIT_CTRL               (0x3414)
#define REG_PUB_APB_QOS_THRESHOLD_0                 (0x3418)
#define REG_PUB_APB_QOS_THRESHOLD_1                 (0x341C)
#define REG_PUB_APB_DMC_DDR_CLK_CTRL                (0x4000)
#define REG_PUB_APB_DMC_CLK_INIT_SW_START           (0x4004)
#define REG_PUB_APB_DMC_CLK_STATE                   (0x4008)
#define REG_PUB_APB_DMC_CLK_INIT_CFG                (0x400C)
#define REG_PUB_APB_DMC_DESKEW_WAIT_CFG             (0x4010)
#define REG_PUB_APB_DMC_DESKEW_WAIT_CNT0            (0x4014)
#define REG_PUB_APB_DMC_DESKEW_WAIT_CNT1            (0x4018)
#define REG_PUB_APB_DMC_DESKEW_WAIT_CNT2            (0x401C)
#define REG_PUB_APB_DMC_DESKEW_WAIT_CNT3            (0x4020)
#define REG_PUB_APB_DMC_DDL_CTRL                    (0x402C)
#define REG_PUB_APB_DFS_PURE_SW_CTRL                (0x4100)
#define REG_PUB_APB_DFS_SW_CTRL                     (0x4104)
#define REG_PUB_APB_DFS_SW_CTRL1                    (0x4108)
#define REG_PUB_APB_DFS_SW_CTRL2                    (0x410C)
#define REG_PUB_APB_DFS_SW_CTRL3                    (0x4110)
#define REG_PUB_APB_DFS_HW_CTRL                     (0x4114)
#define REG_PUB_APB_DFS_HW_CTRL1                    (0x4118)
#define REG_PUB_APB_DFS_HW_CTRL2                    (0x411C)
#define REG_PUB_APB_DFS_HW_RATIO_SET0               (0x4120)
#define REG_PUB_APB_DFS_HW_RATIO_SET1               (0x4124)
#define REG_PUB_APB_DFS_HW_RATIO_SET2               (0x4128)
#define REG_PUB_APB_DFS_HW_RATIO_SET3               (0x412C)
#define REG_PUB_APB_DFS_HW_RATIO_SET4               (0x4130)
#define REG_PUB_APB_DFS_HW_RATIO_SET5               (0x4134)
#define REG_PUB_APB_DFS_HW_RATIO_SET6               (0x4138)
#define REG_PUB_APB_DFS_HW_RATIO_SET7               (0x413C)
#define REG_PUB_APB_VOTE_MASTER_EN                  (0x4310)
#define REG_PUB_APB_VOTE_FSM_CNT                    (0x4314)
#define REG_PUB_APB_THRESHOLD_INC_FREQ_0            (0x4318)
#define REG_PUB_APB_THRESHOLD_INC_FREQ_1            (0x431C)
#define REG_PUB_APB_THRESHOLD_INC_FREQ_2            (0x4320)
#define REG_PUB_APB_THRESHOLD_INC_FREQ_3            (0x4324)
#define REG_PUB_APB_THRESHOLD_INC_FREQ_4            (0x4328)
#define REG_PUB_APB_THRESHOLD_INC_FREQ_5            (0x432C)
#define REG_PUB_APB_THRESHOLD_INC_FREQ_6            (0x4330)
#define REG_PUB_APB_THRESHOLD_INC_FREQ_7            (0x4334)
#define REG_PUB_APB_TEST_DSKPLL_BIST_CNT            (0x4340)
#define REG_PUB_APB_PUB_STATUS_MON_CTRL             (0x6200)
#define REG_PUB_APB_PUB_ST_IDLE_CYC_CNT             (0x6204)
#define REG_PUB_APB_PUB_ST_WR_CYC_CNT               (0x6208)
#define REG_PUB_APB_PUB_ST_RD_CYC_CNT               (0x620C)
#define REG_PUB_APB_PUB_ST_SR_CYC_CNT               (0x6210)
#define REG_PUB_APB_PUB_ST_LS_CYC_CNT               (0x6214)
#define REG_PUB_APB_PUB_ST_LS_TIME_CNT              (0x6218)
#define REG_PUB_APB_PUB_DFS_F0_CYC_CNT              (0x621C)
#define REG_PUB_APB_PUB_DFS_F1_CYC_CNT              (0x6220)
#define REG_PUB_APB_PUB_DFS_F2_CYC_CNT              (0x6224)
#define REG_PUB_APB_PUB_DFS_F3_CYC_CNT              (0x6228)
#define REG_PUB_APB_PUB_DFS_F4_CYC_CNT              (0x622C)
#define REG_PUB_APB_PUB_DFS_F5_CYC_CNT              (0x6230)
#define REG_PUB_APB_PUB_DFS_F6_CYC_CNT              (0x6234)
#define REG_PUB_APB_PUB_DFS_F7_CYC_CNT              (0x6238)
#define REG_PUB_APB_PUB_DFS_CNT                     (0x623C)
#define REG_PUB_APB_VOTE_CTRL_DPU_0                 (0x6400)
#define REG_PUB_APB_VOTE_CTRL_DCAM_0                (0x6404)
#define REG_PUB_APB_VOTE_CTRL_PUBCP_0               (0x6408)
#define REG_PUB_APB_VOTE_CTRL_WTLCP_0               (0x640C)
#define REG_PUB_APB_VOTE_CTRL_WTLCP1_0              (0x6410)
#define REG_PUB_APB_VOTE_CTRL_AGCP_0                (0x6414)
#define REG_PUB_APB_VOTE_CTRL_SW_0                  (0x6418)
#define REG_PUB_APB_VOTE_CTRL_DPU_1                 (0x6420)
#define REG_PUB_APB_VOTE_CTRL_DCAM_1                (0x6424)
#define REG_PUB_APB_VOTE_CTRL_PUBCP_1               (0x6428)
#define REG_PUB_APB_VOTE_CTRL_WTLCP_1               (0x642C)
#define REG_PUB_APB_VOTE_CTRL_WTLCP1_1              (0x6430)
#define REG_PUB_APB_VOTE_CTRL_AGCP_1                (0x6434)
#define REG_PUB_APB_VOTE_CTRL_SW_1                  (0x6438)
#define REG_PUB_APB_DFS_GFREE_CTRL                  (0x6500)
#define REG_PUB_APB_DFS_SW_CTRL_APPEND              (0x6600)
#define REG_PUB_APB_AWURGENT_DBG_CTRL               (0x6800)
#define REG_PUB_APB_ARURGENT_DBG_CTRL               (0x6804)
#define REG_PUB_APB_LSLP_SRE_SIM                    (0x6808)
#define REG_PUB_APB_PUB0_DUMMY_REG0                 (0x8000)
#define REG_PUB_APB_PUB0_DUMMY_REG1                 (0x8004)

/* REG_PUB_APB_DDR_EB */


/* REG_PUB_APB_DDR_SOFT_RST */


/* REG_PUB_APB_DDL_MASK_CTRL */

#define BIT_PUB_APB_DDL_MASK_CTRL(x)                             (((x) & 0x7))

/* REG_PUB_APB_LP_COMPITABLE_WITH_L3 */

#define BIT_PUB_APB_LP_CTRL_DMC_SLEEP_EN                         BIT(0)

/* REG_PUB_APB_PUB_DDR_CHN_LP_CTRL */

#define BIT_PUB_APB_DDR_CHN7_AXI_LP_EN                           BIT(15)
#define BIT_PUB_APB_DDR_CHN6_AXI_LP_EN                           BIT(14)
#define BIT_PUB_APB_DDR_CHN5_AXI_LP_EN                           BIT(13)
#define BIT_PUB_APB_DDR_CHN4_AXI_LP_EN                           BIT(12)
#define BIT_PUB_APB_DDR_CHN3_AXI_LP_EN                           BIT(11)
#define BIT_PUB_APB_DDR_CHN2_AXI_LP_EN                           BIT(10)
#define BIT_PUB_APB_DDR_CHN1_AXI_LP_EN                           BIT(9)
#define BIT_PUB_APB_DDR_CHN0_AXI_LP_EN                           BIT(8)
#define BIT_PUB_APB_DDR_CH7_AXI_STOP_SEL                         BIT(7)
#define BIT_PUB_APB_DDR_CH6_AXI_STOP_SEL                         BIT(6)
#define BIT_PUB_APB_DDR_CH5_AXI_STOP_SEL                         BIT(5)
#define BIT_PUB_APB_DDR_CH4_AXI_STOP_SEL                         BIT(4)
#define BIT_PUB_APB_DDR_CH3_AXI_STOP_SEL                         BIT(3)
#define BIT_PUB_APB_DDR_CH2_AXI_STOP_SEL                         BIT(2)
#define BIT_PUB_APB_DDR_CH1_AXI_STOP_SEL                         BIT(1)
#define BIT_PUB_APB_DDR_CH0_AXI_STOP_SEL                         BIT(0)

/* REG_PUB_APB_AXI_LPC_CTRL_PUNUM_CFG_0 */

#define BIT_PUB_APB_PU_NUM_PUB_CFG_S2(x)                         (((x) & 0xFF) << 24)
#define BIT_PUB_APB_PU_NUM_PUB_CFG_S1(x)                         (((x) & 0xFF) << 16)
#define BIT_PUB_APB_PU_NUM_PUB_CFG_S0(x)                         (((x) & 0xFF) << 8)
#define BIT_PUB_APB_PU_NUM_PUB_CFG_M0(x)                         (((x) & 0xFF))

/* REG_PUB_APB_AXI_LPC_CTRL_PUNUM_CFG_1 */

#define BIT_PUB_APB_PU_NUM_PUB_CFG_S3(x)                         (((x) & 0xFF))

/* REG_PUB_APB_AXI_LPC_CTRL_PUNUM_DPU_ISP */

#define BIT_PUB_APB_PU_NUM_DPU_ISP_S0(x)                         (((x) & 0xFF) << 16)
#define BIT_PUB_APB_PU_NUM_DPU_ISP_M1(x)                         (((x) & 0xFF) << 8)
#define BIT_PUB_APB_PU_NUM_DPU_ISP_M0(x)                         (((x) & 0xFF))

/* REG_PUB_APB_AXI_LPC_CTRL_PUNUM_ISP_VDSP */

#define BIT_PUB_APB_PU_NUM_ISP_VDSP_S0(x)                        (((x) & 0xFF) << 16)
#define BIT_PUB_APB_PU_NUM_ISP_VDSP_M1(x)                        (((x) & 0xFF) << 8)
#define BIT_PUB_APB_PU_NUM_ISP_VDSP_M0(x)                        (((x) & 0xFF))

/* REG_PUB_APB_AXI_LPC_CTRL_PUNUM_AP_0 */

#define BIT_PUB_APB_PU_NUM_AP_AON_ESE_IPA1_M3(x)                 (((x) & 0xFF) << 24)
#define BIT_PUB_APB_PU_NUM_AP_AON_ESE_IPA1_M2(x)                 (((x) & 0xFF) << 16)
#define BIT_PUB_APB_PU_NUM_AP_AON_ESE_IPA1_M1(x)                 (((x) & 0xFF) << 8)
#define BIT_PUB_APB_PU_NUM_AP_AON_ESE_IPA1_M0(x)                 (((x) & 0xFF))

/* REG_PUB_APB_AXI_LPC_CTRL_PUNUM_AP_1 */

#define BIT_PUB_APB_PU_NUM_AP_AON_ESE_IPA1_S0(x)                 (((x) & 0xFF))

/* REG_PUB_APB_AXI_LPC_CTRL_PUNUM_PUB_AG_IPA2 */

#define BIT_PUB_APB_PU_NUM_PUB_AG_IPA2_S0(x)                     (((x) & 0xFF) << 24)
#define BIT_PUB_APB_PU_NUM_PUB_AG_IPA2_M2(x)                     (((x) & 0xFF) << 16)
#define BIT_PUB_APB_PU_NUM_PUB_AG_IPA2_M1(x)                     (((x) & 0xFF) << 8)
#define BIT_PUB_APB_PU_NUM_PUB_AG_IPA2_M0(x)                     (((x) & 0xFF))

/* REG_PUB_APB_DMC_EXT_LPCTRL_CFG */

#define BIT_PUB_APB_SOFT_CMD_NUM(x)                              (((x) & 0x7) << 8)
#define BIT_PUB_APB_SOFT_CMD_FC_SEL(x)                           (((x) & 0x3) << 4)
#define BIT_PUB_APB_SOFT_CMD_RESP                                BIT(3)
#define BIT_PUB_APB_SOFT_CMD_DONE                                BIT(2)
#define BIT_PUB_APB_SOFT_CMD_START                               BIT(0)

/* REG_PUB_APB_DMC_EXT_LPCTRL_SEQL */

#define BIT_PUB_APB_SOFT_CMD_SEQL(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_EXT_LPCTRL_SEQH */

#define BIT_PUB_APB_SOFT_CMD_SEQH(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_EXT_LPCTRL_STEP */

#define BIT_PUB_APB_SOFT_CMD_STEP(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_QOS_SELECT */


/* REG_PUB_APB_DPLL_PRE_DIV_STATUS */

#define BIT_PUB_APB_DPLL_PRE_DIV_MONITOR_GATE_AUTO_EN_STATUS(x)  (((x) & 0x3) << 2)
#define BIT_PUB_APB_DPLL_PRE_DIV_MONITOR_WAIT_EN_STATUS(x)       (((x) & 0x3))

/* REG_PUB_APB_DFI_BWMON_TIMER */

#define BIT_PUB_APB_DFI_MON_IDLE_CNT(x)                          (((x) & 0xFF) << 8)
#define BIT_PUB_APB_DFI_MON_TIMER_DELAY(x)                       (((x) & 0xFF))

/* REG_PUB_APB_QOS_SWITCH */

#define BIT_PUB_APB_URGENT_CHN_SEL                               BIT(1)
#define BIT_PUB_APB_QOS_URGENT_SEL                               BIT(0)

/* REG_PUB_APB_PUB_BUS_CK_EB */

#define BIT_PUB_APB_LP_STAT_MTX_CG_EN                            BIT(11)
#define BIT_PUB_APB_CHN_DMC_STOP_CG_EN                           BIT(10)
#define BIT_PUB_APB_OT_DETECT_CLK_EB                             BIT(9)
#define BIT_PUB_APB_PUB_CLK_CSSYS_PTM_EB                         BIT(8)
#define BIT_PUB_APB_PUB_APB_PTM_REG_EB                           BIT(7)
#define BIT_PUB_APB_PUB_CLK_DMC_PTM_EB                           BIT(6)
#define BIT_PUB_APB_PUB_APB_INT_EB                               BIT(5)
#define BIT_PUB_APB_PUB_APB_BIST_REG_EB                          BIT(4)
#define BIT_PUB_APB_PUB_AHB_QOSC_REG_EB                          BIT(3)
#define BIT_PUB_APB_PUB_AHB_REG_EB                               BIT(2)
#define BIT_PUB_APB_PUB_AHB_BUS_EB                               BIT(1)
#define BIT_PUB_APB_PUB_PHY_REG_EB                               BIT(0)

/* REG_PUB_APB_AXI_LPC_CTRL_3 */

#define BIT_PUB_APB_CSYSACK_SYNC_SEL_AP_AON_ESE_IPA1_S0          BIT(31)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_AP_AON_ESE_IPA1_S0          BIT(30)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_AP_AON_ESE_IPA1_M3          BIT(29)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_AP_AON_ESE_IPA1_M3          BIT(28)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_AP_AON_ESE_IPA1_M2          BIT(27)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_AP_AON_ESE_IPA1_M2          BIT(26)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_AP_AON_ESE_IPA1_M1          BIT(25)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_AP_AON_ESE_IPA1_M1          BIT(24)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_AP_AON_ESE_IPA1_M0          BIT(23)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_AP_AON_ESE_IPA1_M0          BIT(22)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_ISP_VDSP_S0                 BIT(21)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_ISP_VDSP_S0                 BIT(20)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_ISP_VDSP_M1                 BIT(19)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_ISP_VDSP_M1                 BIT(18)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_ISP_VDSP_M0                 BIT(17)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_ISP_VDSP_M0                 BIT(16)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_DPU_ISP_S0                  BIT(15)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_DPU_ISP_S0                  BIT(14)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_DPU_ISP_M1                  BIT(13)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_DPU_ISP_M1                  BIT(12)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_DPU_ISP_M0                  BIT(11)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_DPU_ISP_M0                  BIT(10)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_PUB_CFG_S3                  BIT(9)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_PUB_CFG_S3                  BIT(8)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_PUB_CFG_S2                  BIT(7)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_PUB_CFG_S2                  BIT(6)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_PUB_CFG_S1                  BIT(5)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_PUB_CFG_S1                  BIT(4)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_PUB_CFG_S0                  BIT(3)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_PUB_CFG_S0                  BIT(2)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_PUB_CFG_M0                  BIT(1)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_PUB_CFG_M0                  BIT(0)

/* REG_PUB_APB_PUB_INT_CG_EN */

#define BIT_PUB_APB_INT_DFS_VOTE_DONE_CG_EN                      BIT(10)
#define BIT_PUB_APB_MEM_FW_PUB_CACTIVE_CG_EN                     BIT(9)
#define BIT_PUB_APB_INT_DMC_MPU_VIO_CG_EN                        BIT(8)
#define BIT_PUB_APB_INT_MEM_FW_CG_EN                             BIT(7)
#define BIT_PUB_APB_INT_DFS_GIVEUP_CG_EN                         BIT(6)
#define BIT_PUB_APB_INT_DFS_DENY_CG_EN                           BIT(5)
#define BIT_PUB_APB_INT_DFS_ERROR_CG_EN                          BIT(4)
#define BIT_PUB_APB_INT_HARDWARE_DFS_EXIT_CG_EN                  BIT(3)
#define BIT_PUB_APB_INT_DFS_COMPLETE_CG_EN                       BIT(2)
#define BIT_PUB_APB_INT_DFI_BUS_MONITOR_CG_EN                    BIT(1)
#define BIT_PUB_APB_INT_REQ_PUB_PTM_CG_EN                        BIT(0)

/* REG_PUB_APB_TIMER_ENABLE */

#define BIT_PUB_APB_PTM_TIMER_EN                                 BIT(3)
#define BIT_PUB_APB_LATMON_TIMER_EN                              BIT(2)
#define BIT_PUB_APB_BWMON_TIMER_EN                               BIT(1)
#define BIT_PUB_APB_DBM_TIMER_EN                                 BIT(0)

/* REG_PUB_APB_VOTE_CTRL */

#define BIT_PUB_APB_BWVOTE_SUB_BWMON_EN                          BIT(30)
#define BIT_PUB_APB_BV_FV_EQUAL_INC_EN                           BIT(29)
#define BIT_PUB_APB_DBM_PERCENT_SEL(x)                           (((x) & 0x7) << 26)
#define BIT_PUB_APB_DFS_VOTE_DMC_REF_AG_EN                       BIT(25)
#define BIT_PUB_APB_DFS_APB_ACCESS_CLK_AUTO_EN                   BIT(24)
#define BIT_PUB_APB_VOTE_CK_OPEN_CNT(x)                          (((x) & 0xFF) << 13)
#define BIT_PUB_APB_TIMING_WINDOW_SEL(x)                         (((x) & 0x7) << 10)
#define BIT_PUB_APB_VOTE_UNIT_TRANS_EN                           BIT(9)
#define BIT_PUB_APB_SW_FORCE_VOTE_MASK_EN                        BIT(8)
#define BIT_PUB_APB_SW_FORCE_VOTE_MASK(x)                        (((x) & 0xFF))

/* REG_PUB_APB_VOTE_STATUS */

#define BIT_PUB_APB_VOTE_TAR_FRQ(x)                              (((x) & 0x7) << 9)
#define BIT_PUB_APB_VOTE_NEXT_STATE(x)                           (((x) & 0xF) << 5)
#define BIT_PUB_APB_VOTE_CUR_STATE(x)                            (((x) & 0xF) << 1)
#define BIT_PUB_APB_VOTE_BW_OVERFLOW                             BIT(0)

/* REG_PUB_APB_DFS_HW_CTRL3 */

#define BIT_PUB_APB_DFS_LOCK_DELAY_EN                            BIT(31)
#define BIT_PUB_APB_REG_DFS_LOCK_DELAY_CNT(x)                    (((x) & 0xF) << 27)
#define BIT_PUB_APB_DFI_MASK_WAIT_LSLP_EN                        BIT(24)
#define BIT_PUB_APB_DFI_MASK_WAIT_TIME_LSLP(x)                   (((x) & 0xFF) << 16)
#define BIT_PUB_APB_DFI_MASK_WAIT_EN                             BIT(8)
#define BIT_PUB_APB_DFI_MASK_WAIT_TIME(x)                        (((x) & 0xFF))

/* REG_PUB_APB_QOS_FIXED_CTRL0 */

#define BIT_PUB_APB_DMC_FIXED_QOS_EN(x)                          (((x) & 0xFF))

/* REG_PUB_APB_QOS_FIXED_CTRL1 */

#define BIT_PUB_APB_DMC_FIXED_ARQOS_CH3(x)                       (((x) & 0xF) << 28)
#define BIT_PUB_APB_DMC_FIXED_AWQOS_CH3(x)                       (((x) & 0xF) << 24)
#define BIT_PUB_APB_DMC_FIXED_ARQOS_CH2(x)                       (((x) & 0xF) << 20)
#define BIT_PUB_APB_DMC_FIXED_AWQOS_CH2(x)                       (((x) & 0xF) << 16)
#define BIT_PUB_APB_DMC_FIXED_ARQOS_CH1(x)                       (((x) & 0xF) << 12)
#define BIT_PUB_APB_DMC_FIXED_AWQOS_CH1(x)                       (((x) & 0xF) << 8)
#define BIT_PUB_APB_DMC_FIXED_ARQOS_CH0(x)                       (((x) & 0xF) << 4)
#define BIT_PUB_APB_DMC_FIXED_AWQOS_CH0(x)                       (((x) & 0xF))

/* REG_PUB_APB_QOS_FIXED_CTRL2 */

#define BIT_PUB_APB_DMC_FIXED_ARQOS_CH7(x)                       (((x) & 0xF) << 28)
#define BIT_PUB_APB_DMC_FIXED_AWQOS_CH7(x)                       (((x) & 0xF) << 24)
#define BIT_PUB_APB_DMC_FIXED_ARQOS_CH6(x)                       (((x) & 0xF) << 20)
#define BIT_PUB_APB_DMC_FIXED_AWQOS_CH6(x)                       (((x) & 0xF) << 16)
#define BIT_PUB_APB_DMC_FIXED_ARQOS_CH5(x)                       (((x) & 0xF) << 12)
#define BIT_PUB_APB_DMC_FIXED_AWQOS_CH5(x)                       (((x) & 0xF) << 8)
#define BIT_PUB_APB_DMC_FIXED_ARQOS_CH4(x)                       (((x) & 0xF) << 4)
#define BIT_PUB_APB_DMC_FIXED_AWQOS_CH4(x)                       (((x) & 0xF))

/* REG_PUB_APB_PUB_AXI_QOS_URGENT_REG_0 */

#define BIT_PUB_APB_ARQOS_URGENT_CH3(x)                          (((x) & 0xF) << 28)
#define BIT_PUB_APB_AWQOS_URGENT_CH3(x)                          (((x) & 0xF) << 24)
#define BIT_PUB_APB_ARQOS_URGENT_CH2(x)                          (((x) & 0xF) << 20)
#define BIT_PUB_APB_AWQOS_URGENT_CH2(x)                          (((x) & 0xF) << 16)
#define BIT_PUB_APB_ARQOS_URGENT_CH1(x)                          (((x) & 0xF) << 12)
#define BIT_PUB_APB_AWQOS_URGENT_CH1(x)                          (((x) & 0xF) << 8)
#define BIT_PUB_APB_ARQOS_URGENT_CH0(x)                          (((x) & 0xF) << 4)
#define BIT_PUB_APB_AWQOS_URGENT_CH0(x)                          (((x) & 0xF))

/* REG_PUB_APB_PUB_AXI_QOS_URGENT_REG_1 */

#define BIT_PUB_APB_ARQOS_URGENT_CH7(x)                          (((x) & 0xF) << 28)
#define BIT_PUB_APB_AWQOS_URGENT_CH7(x)                          (((x) & 0xF) << 24)
#define BIT_PUB_APB_ARQOS_URGENT_CH6(x)                          (((x) & 0xF) << 20)
#define BIT_PUB_APB_AWQOS_URGENT_CH6(x)                          (((x) & 0xF) << 16)
#define BIT_PUB_APB_ARQOS_URGENT_CH5(x)                          (((x) & 0xF) << 12)
#define BIT_PUB_APB_AWQOS_URGENT_CH5(x)                          (((x) & 0xF) << 8)
#define BIT_PUB_APB_ARQOS_URGENT_CH4(x)                          (((x) & 0xF) << 4)
#define BIT_PUB_APB_AWQOS_URGENT_CH4(x)                          (((x) & 0xF))

/* REG_PUB_APB_PUB_INT_CTRL */

#define BIT_PUB_APB_DFS_VOTE_DONE_INT_CLR                        BIT(15)
#define BIT_PUB_APB_DFS_VOTE_DONE_INT_EN                         BIT(14)
#define BIT_PUB_APB_DFS_GIVEUP_INT_CLR                           BIT(13)
#define BIT_PUB_APB_DFS_GIVEUP_INT_EN                            BIT(12)
#define BIT_PUB_APB_DFS_DENY_INT_CLR                             BIT(11)
#define BIT_PUB_APB_DFS_DENY_INT_EN                              BIT(10)
#define BIT_PUB_APB_DMC_MPU_VIO_INT_CLR                          BIT(9)
#define BIT_PUB_APB_DMC_MPU_VIO_INT_EN                           BIT(8)
#define BIT_PUB_APB_MEM_FW_INT_CLR                               BIT(7)
#define BIT_PUB_APB_MEM_FW_INT_EN                                BIT(6)
#define BIT_PUB_APB_DFS_ERROR_INT_CLR                            BIT(5)
#define BIT_PUB_APB_DFS_ERROR_INT_EN                             BIT(4)
#define BIT_PUB_APB_DFS_COMPLETE_INT_CLR                         BIT(3)
#define BIT_PUB_APB_DFS_COMPLETE_INT_EN                          BIT(2)
#define BIT_PUB_APB_HW_DFS_EXIT_INT_CLR                          BIT(1)
#define BIT_PUB_APB_HW_DFS_EXIT_INT_EN                           BIT(0)

/* REG_PUB_APB_DFS_STATUS */

#define BIT_PUB_APB_DFS_HW_MIN_FREQ_UP_FORCE_TRIG_ACK            BIT(30)
#define BIT_PUB_APB_DFS_USED_PLL(x)                              (((x) & 0x7) << 27)
#define BIT_PUB_APB_DFS_FC_SEL(x)                                (((x) & 0x7) << 24)
#define BIT_PUB_APB_SRC_AVAIL_PLL(x)                             (((x) & 0x7) << 21)
#define BIT_PUB_APB_DFS_URGENT_WAIT_TIMEOUT_FLAG                 BIT(20)
#define BIT_PUB_APB_DFS_GIVEUP_INT_RAW                           BIT(19)
#define BIT_PUB_APB_INT_DFS_GIVEUP                               BIT(18)
#define BIT_PUB_APB_DFS_DENY_INT_RAW                             BIT(17)
#define BIT_PUB_APB_INT_DFS_DENY                                 BIT(16)
#define BIT_PUB_APB_HW_DFS_FSM_STATE(x)                          (((x) & 0x1F) << 11)
#define BIT_PUB_APB_HW_DFS_FSM_IDLE                              BIT(10)
#define BIT_PUB_APB_INT_DMC_MPU_VIO_RAW                          BIT(9)
#define BIT_PUB_APB_INT_DMC_MPU_VIO                              BIT(8)
#define BIT_PUB_APB_INT_MEM_FW_RAW                               BIT(7)
#define BIT_PUB_APB_INT_MEM_FW                                   BIT(6)
#define BIT_PUB_APB_DFS_ERROR_INT_RAW                            BIT(5)
#define BIT_PUB_APB_INT_DFS_ERROR                                BIT(4)
#define BIT_PUB_APB_DFS_COMPLETE_INT_RAW                         BIT(3)
#define BIT_PUB_APB_INT_DFS_COMPLETE                             BIT(2)
#define BIT_PUB_APB_HW_DFS_EXIT_INT_RAW                          BIT(1)
#define BIT_PUB_APB_INT_HW_DFS_EXIT                              BIT(0)

/* REG_PUB_APB_DFS_STATUS1 */

#define BIT_PUB_APB_DFS_SW_FSM_STATE(x)                          (((x) & 0x7) << 4)
#define BIT_PUB_APB_DFS_VOTE_DONE_INT_RAW                        BIT(1)
#define BIT_PUB_APB_INT_DFS_VOTE_DONE                            BIT(0)

/* REG_PUB_APB_DFS_FC_REQ_DELAY */

#define BIT_PUB_APB_DFS_FC_REQ_DELAY(x)                          (((x) & 0x7))

/* REG_PUB_APB_PUB_LP_GEN_CTRL */

#define BIT_PUB_APB_DFS_SW_MODE                                  BIT(6)
#define BIT_PUB_APB_HW_DFS_STOP_ENABLE                           BIT(5)
#define BIT_PUB_APB_HW_DFS_RESTART_ENABLE                        BIT(4)
#define BIT_PUB_APB_AUTO_STOP_NOC_ENABLE                         BIT(3)
#define BIT_PUB_APB_AUTO_STOP_DFS_ENABLE                         BIT(2)
#define BIT_PUB_APB_PUB_DFS_EN                                   BIT(1)
#define BIT_PUB_APB_PUB_LP_EN                                    BIT(0)

/* REG_PUB_APB_AXI_LPC_CTRL_0 */

#define BIT_PUB_APB_CSYSACK_SYNC_SEL_PUB_AG_IPA2_S0              BIT(23)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_PUB_AG_IPA2_S0              BIT(22)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_PUB_AG_IPA2_M2              BIT(21)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_PUB_AG_IPA2_M2              BIT(20)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_PUB_AG_IPA2_M1              BIT(19)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_PUB_AG_IPA2_M1              BIT(18)
#define BIT_PUB_APB_CSYSACK_SYNC_SEL_PUB_AG_IPA2_M0              BIT(17)
#define BIT_PUB_APB_CACTIVE_SYNC_SEL_PUB_AG_IPA2_M0              BIT(16)
#define BIT_PUB_APB_LP_FORCE_PUB_CFG_S3                          BIT(15)
#define BIT_PUB_APB_LP_EB_PUB_CFG_S3                             BIT(14)
#define BIT_PUB_APB_LP_FORCE_PUB_CFG_S2                          BIT(13)
#define BIT_PUB_APB_LP_EB_PUB_CFG_S2                             BIT(12)
#define BIT_PUB_APB_LP_FORCE_PUB_CFG_S1                          BIT(11)
#define BIT_PUB_APB_LP_EB_PUB_CFG_S1                             BIT(10)
#define BIT_PUB_APB_LP_FORCE_PUB_CFG_S0                          BIT(9)
#define BIT_PUB_APB_LP_EB_PUB_CFG_S0                             BIT(8)
#define BIT_PUB_APB_LP_FORCE_PUB_CFG_M0                          BIT(7)
#define BIT_PUB_APB_LP_EB_PUB_CFG_M0                             BIT(6)
#define BIT_PUB_APB_LP_FORCE_ISP_VDSP_S0                         BIT(5)
#define BIT_PUB_APB_LP_EB_ISP_VDSP_S0                            BIT(4)
#define BIT_PUB_APB_LP_FORCE_ISP_VDSP_M1                         BIT(3)
#define BIT_PUB_APB_LP_EB_ISP_VDSP_M1                            BIT(2)
#define BIT_PUB_APB_LP_FORCE_ISP_VDSP_M0                         BIT(1)
#define BIT_PUB_APB_LP_EB_ISP_VDSP_M0                            BIT(0)

/* REG_PUB_APB_AXI_LPC_CTRL_1 */

#define BIT_PUB_APB_LP_FORCE_PUB_AG_IPA2_S0                      BIT(23)
#define BIT_PUB_APB_LP_EB_PUB_AG_IPA2_S0                         BIT(22)
#define BIT_PUB_APB_LP_FORCE_PUB_AG_IPA2_M2                      BIT(21)
#define BIT_PUB_APB_LP_EB_PUB_AG_IPA2_M2                         BIT(20)
#define BIT_PUB_APB_LP_FORCE_PUB_AG_IPA2_M1                      BIT(19)
#define BIT_PUB_APB_LP_EB_PUB_AG_IPA2_M1                         BIT(18)
#define BIT_PUB_APB_LP_FORCE_PUB_AG_IPA2_M0                      BIT(17)
#define BIT_PUB_APB_LP_EB_PUB_AG_IPA2_M0                         BIT(16)
#define BIT_PUB_APB_LP_FORCE_AP_AON_ESE_IPA1_S0                  BIT(15)
#define BIT_PUB_APB_LP_EB_AP_AON_ESE_IPA1_S0                     BIT(14)
#define BIT_PUB_APB_LP_FORCE_AP_AON_ESE_IPA1_M3                  BIT(13)
#define BIT_PUB_APB_LP_EB_AP_AON_ESE_IPA1_M3                     BIT(12)
#define BIT_PUB_APB_LP_FORCE_AP_AON_ESE_IPA1_M2                  BIT(11)
#define BIT_PUB_APB_LP_EB_AP_AON_ESE_IPA1_M2                     BIT(10)
#define BIT_PUB_APB_LP_FORCE_AP_AON_ESE_IPA1_M1                  BIT(9)
#define BIT_PUB_APB_LP_EB_AP_AON_ESE_IPA1_M1                     BIT(8)
#define BIT_PUB_APB_LP_FORCE_AP_AON_ESE_IPA1_M0                  BIT(7)
#define BIT_PUB_APB_LP_EB_AP_AON_ESE_IPA1_M0                     BIT(6)
#define BIT_PUB_APB_LP_FORCE_DPU_ISP_S0                          BIT(5)
#define BIT_PUB_APB_LP_EB_DPU_ISP_S0                             BIT(4)
#define BIT_PUB_APB_LP_FORCE_DPU_ISP_M1                          BIT(3)
#define BIT_PUB_APB_LP_EB_DPU_ISP_M1                             BIT(2)
#define BIT_PUB_APB_LP_FORCE_DPU_ISP_M0                          BIT(1)
#define BIT_PUB_APB_LP_EB_DPU_ISP_M0                             BIT(0)

/* REG_PUB_APB_AXI_LPC_CTRL_2 */

#define BIT_PUB_APB_LP_NUM_PUB_CFG(x)                            (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_LP_NUM(x)                                    (((x) & 0xFFFF))

/* REG_PUB_APB_FENCING_CTRL */

#define BIT_PUB_APB_DDR_FENCING_EN                               BIT(30)
#define BIT_PUB_APB_FENCING_CHNL_IDLE_CNT(x)                     (((x) & 0x3FFFFFFF))

/* REG_PUB_APB_CP_ESE_BASE_ADDR */

#define BIT_PUB_APB_ESE_BASE_ADDR(x)                             (((x) & 0x1F) << 15)
#define BIT_PUB_APB_PUB_CP_BASE_ADDR(x)                          (((x) & 0x1F) << 10)
#define BIT_PUB_APB_WTL_CP_BASE_ADDR(x)                          (((x) & 0x1F) << 5)
#define BIT_PUB_APB_AG_CP_BASE_ADDR(x)                           (((x) & 0x1F))

/* REG_PUB_APB_CLK_PUB_DFS_CTRL */

#define BIT_PUB_APB_LP_WAIT_CGM_BUSY_SEL                         BIT(2)
#define BIT_PUB_APB_CGM_PUB_DFS_SEL                              BIT(1)
#define BIT_PUB_APB_CGM_PUB_DFS_EN                               BIT(0)

/* REG_PUB_APB_BIST_CTRL */

#define BIT_PUB_APB_BIST_PORT7_ADDR_MUX                          BIT(23)
#define BIT_PUB_APB_BIST_PORT6_ADDR_MUX                          BIT(22)
#define BIT_PUB_APB_BIST_PORT5_ADDR_MUX                          BIT(21)
#define BIT_PUB_APB_BIST_PORT4_ADDR_MUX                          BIT(20)
#define BIT_PUB_APB_BIST_PORT3_ADDR_MUX                          BIT(19)
#define BIT_PUB_APB_BIST_PORT2_ADDR_MUX                          BIT(18)
#define BIT_PUB_APB_BIST_PORT1_ADDR_MUX                          BIT(17)
#define BIT_PUB_APB_BIST_PORT0_ADDR_MUX                          BIT(16)
#define BIT_PUB_APB_BIST_FAIL_FLAG_CH2                           BIT(10)
#define BIT_PUB_APB_BIST_FAIL_FLAG_CH1                           BIT(9)
#define BIT_PUB_APB_BIST_FAIL_FLAG_CH0                           BIT(8)
#define BIT_PUB_APB_BIST_PORT7_EN                                BIT(7)
#define BIT_PUB_APB_BIST_PORT6_EN                                BIT(6)
#define BIT_PUB_APB_BIST_PORT5_EN                                BIT(5)
#define BIT_PUB_APB_BIST_PORT4_EN                                BIT(4)
#define BIT_PUB_APB_BIST_PORT3_EN                                BIT(3)
#define BIT_PUB_APB_BIST_PORT2_EN                                BIT(2)
#define BIT_PUB_APB_BIST_PORT1_EN                                BIT(1)
#define BIT_PUB_APB_BIST_PORT0_EN                                BIT(0)

/* REG_PUB_APB_DMC_SOFT_RST_CTRL */

#define BIT_PUB_APB_DMC_SOFT_RST                                 BIT(2)
#define BIT_PUB_APB_DCC_SOFT_RST                                 BIT(1)
#define BIT_PUB_APB_DDRPHY_SOFT_RST                              BIT(0)

/* REG_PUB_APB_MC_IDLE_WAIT_CTRL */

#define BIT_PUB_APB_MC_IDLE_WAIT_CTRL(x)                         (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_QOS_THRESHOLD_0 */

#define BIT_PUB_APB_AWQOS_THRESHOLD_WTL_AG(x)                    (((x) & 0xF) << 28)
#define BIT_PUB_APB_ARQOS_THRESHOLD_WTL_AG(x)                    (((x) & 0xF) << 24)
#define BIT_PUB_APB_AWQOS_THRESHOLD_DPU_ISP(x)                   (((x) & 0xF) << 20)
#define BIT_PUB_APB_ARQOS_THRESHOLD_DPU_ISP(x)                   (((x) & 0xF) << 16)
#define BIT_PUB_APB_AWQOS_THRESHOLD_AP_AON(x)                    (((x) & 0xF) << 12)
#define BIT_PUB_APB_ARQOS_THRESHOLD_AP_AON(x)                    (((x) & 0xF) << 8)
#define BIT_PUB_APB_AON_AWQOS(x)                                 (((x) & 0xF) << 4)
#define BIT_PUB_APB_AON_ARQOS(x)                                 (((x) & 0xF))

/* REG_PUB_APB_QOS_THRESHOLD_1 */

#define BIT_PUB_APB_AWQOS_THRESHOLD_ISP_VDSP(x)                  (((x) & 0xF) << 4)
#define BIT_PUB_APB_ARQOS_THRESHOLD_ISP_VDSP(x)                  (((x) & 0xF))

/* REG_PUB_APB_DMC_DDR_CLK_CTRL */

#define BIT_PUB_APB_PUB_CLK_DFS_SLEEP_AUTO_GATE_EN               BIT(31)
#define BIT_PUB_APB_CLK_AON_APB_AUTO_GATE_EN                     BIT(30)
#define BIT_PUB_APB_CLK_DMC_REF_AUTO_GATE_EN                     BIT(29)
#define BIT_PUB_APB_PUB_CLK_DFS_AUTO_GATE_EN                     BIT(28)
#define BIT_PUB_APB_DMC_DFI_MON_AUTO_GATE_EN                     BIT(27)
#define BIT_PUB_APB_DMC_SREF_AUTO_GATE_EN                        BIT(26)
#define BIT_PUB_APB_DDR_PHY_AUTO_GATE_EN                         BIT(25)
#define BIT_PUB_APB_DDR_UMCTL_AUTO_GATE_EN                       BIT(24)
#define BIT_PUB_APB_PUB_CLK_DMC_BIST_EB                          BIT(23)
#define BIT_PUB_APB_PUB_CLK_DMC_REF_EB                           BIT(22)
#define BIT_PUB_APB_PUB_CLK_CSSYS_EB                             BIT(21)
#define BIT_PUB_APB_PUB_CLK_AON_APB_EB                           BIT(20)
#define BIT_PUB_APB_PUB_CLK_PHY_X2_FORCE_PHASE(x)                (((x) & 0x3) << 18)
#define BIT_PUB_APB_PUB_CLK_PHY_X2_FORCE_PHASE_SEL               BIT(17)
#define BIT_PUB_APB_PUB_CLK_PHY_X2_FORCE_BYP                     BIT(16)
#define BIT_PUB_APB_PUB_CLK_DFS_EB                               BIT(15)
#define BIT_PUB_APB_PUB_CLK_DMC_X1_PTM_EB                        BIT(14)
#define BIT_PUB_APB_PUB_CLK_MLB_D2_EB                            BIT(13)
#define BIT_PUB_APB_PUB_CLK_DMC_D2_EB                            BIT(12)
#define BIT_PUB_APB_PUB_CLK_DMC_X1_EB                            BIT(11)
#define BIT_PUB_APB_PUB_CLK_PHY_X2_EB                            BIT(10)
#define BIT_PUB_APB_PUB_CLK_DCC_EB                               BIT(9)
#define BIT_PUB_APB_PUB_DDR_CLK_EB                               BIT(8)
#define BIT_PUB_APB_TIMER_CLK_AON_APB_OPEN_EN                    BIT(7)
#define BIT_PUB_APB_PUB_CLK_DMC_X1_PTM_AUTO_GATE_EN              BIT(6)
#define BIT_PUB_APB_PUB_CLK_MLB_D2_CGM_SEL                       BIT(5)
#define BIT_PUB_APB_PUB_CLK_DMC_D2_CGM_SEL                       BIT(4)
#define BIT_PUB_APB_PUB_CLK_DMC_X1_CGM_SEL                       BIT(3)
#define BIT_PUB_APB_PUB_CLK_PHY_X2_CGM_SEL                       BIT(2)
#define BIT_PUB_APB_PUB_CLK_DCC_CGM_SEL                          BIT(1)
#define BIT_PUB_APB_PUB_DDR_CLK_CGM_SEL                          BIT(0)

/* REG_PUB_APB_DMC_CLK_INIT_SW_START */

#define BIT_PUB_APB_DMC_CLK_INIT_SW_START                        BIT(0)

/* REG_PUB_APB_DMC_CLK_STATE */

#define BIT_PUB_APB_DFS_LP_CTRL_CUR_STATE(x)                     (((x) & 0x7) << 12)
#define BIT_PUB_APB_DMC_CLK_HW_CUR_STATE(x)                      (((x) & 0xF) << 4)
#define BIT_PUB_APB_DMC_CUR_CLK_MODE(x)                          (((x) & 0x3) << 2)
#define BIT_PUB_APB_DMC_CLK_INIT_SW_DONE                         BIT(0)

/* REG_PUB_APB_DMC_CLK_INIT_CFG */

#define BIT_PUB_APB_PTM_LSLP_CLK_KEEP_ON_EN                      BIT(25)
#define BIT_PUB_APB_DMC_DFI_MON_LSLP_AG_EN                       BIT(24)
#define BIT_PUB_APB_DMC_STOP_WAIT_CNT(x)                         (((x) & 0xFF) << 16)
#define BIT_PUB_APB_DMC_SLEEP_FORCE_FINISH_MODE                  BIT(8)
#define BIT_PUB_APB_DESKEW_PLL_PD_DEFAULT_SW                     BIT(5)
#define BIT_PUB_APB_DESKEW_PLL_PD_DEFAULT_SEL                    BIT(4)
#define BIT_PUB_APB_DMC_SLEEP_CLK_AUTO_MODE                      BIT(1)
#define BIT_PUB_APB_DFS_CLK_AUTO_MODE                            BIT(0)

/* REG_PUB_APB_DMC_DESKEW_WAIT_CFG */

#define BIT_PUB_APB_DSKDLL_DCC_FINE_WAIT_SRC_SW                  BIT(10)
#define BIT_PUB_APB_DSKDLL_DCC_COARSE_WAIT_SRC_SW                BIT(9)
#define BIT_PUB_APB_DSKPLL_LOCK_WAIT_SRC_SW                      BIT(8)
#define BIT_PUB_APB_DDL_ADJS_V_WAIT_EN                           BIT(3)
#define BIT_PUB_APB_DSKDLL_DCC_FINE_WAIT_EN                      BIT(2)
#define BIT_PUB_APB_DSKDLL_DCC_COARSE_WAIT_EN                    BIT(1)
#define BIT_PUB_APB_DSKPLL_LOCK_WAIT_EN                          BIT(0)

/* REG_PUB_APB_DMC_DESKEW_WAIT_CNT0 */

#define BIT_PUB_APB_WAIT_CNT_DSKPLL_PWRON_TIME(x)                (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_WAIT_CNT_DSKPLL_LOCK_TIME(x)                 (((x) & 0xFFFF))

/* REG_PUB_APB_DMC_DESKEW_WAIT_CNT1 */

#define BIT_PUB_APB_WAIT_CNT_DSKDLL_DCC_FINE_TIME(x)             (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_WAIT_CNT_DSKDLL_DCC_COARSE_TIME(x)           (((x) & 0xFFFF))

/* REG_PUB_APB_DMC_DESKEW_WAIT_CNT2 */

#define BIT_PUB_APB_WAIT_CNT_DFS_RESET_OFF_TIME(x)               (((x) & 0xFF) << 24)
#define BIT_PUB_APB_WAIT_CNT_DFS_RESET_ON_TIME(x)                (((x) & 0xFF) << 16)
#define BIT_PUB_APB_WAIT_CNT_DFS_CLK_OFF_TIME(x)                 (((x) & 0xFF))

/* REG_PUB_APB_DMC_DESKEW_WAIT_CNT3 */

#define BIT_PUB_APB_WAIT_CNT_DDL_ADJS_V_HIGH_TIME(x)             (((x) & 0xFF) << 16)
#define BIT_PUB_APB_WAIT_CNT_DDL_ADJS_V_LOW_TIME(x)              (((x) & 0xFF))

/* REG_PUB_APB_DMC_DDL_CTRL */

#define BIT_PUB_APB_PTEST_DDL_SCOUT                              BIT(26)
#define BIT_PUB_APB_PTEST_DDL_SCIN                               BIT(25)
#define BIT_PUB_APB_PTEST_DDL_SE                                 BIT(24)
#define BIT_PUB_APB_DMC_DDL_SW_ADJS(x)                           (((x) & 0x1FF) << 8)
#define BIT_PUB_APB_DMC_DDL_SW_UPDATE                            BIT(7)
#define BIT_PUB_APB_DMC_DDL_SW_BYPASS                            BIT(6)
#define BIT_PUB_APB_DMC_DDL_SW_RESET                             BIT(5)
#define BIT_PUB_APB_DMC_DDL_SW_ADJS_VALID                        BIT(4)
#define BIT_PUB_APB_DMC_DDL_CFG_SRC_PURE_SW                      BIT(1)
#define BIT_PUB_APB_DMC_DDL_CFG_SRC_SW                           BIT(0)

/* REG_PUB_APB_DFS_PURE_SW_CTRL */

#define BIT_PUB_APB_EMC_CKG_MDLL_SEL_PURE_SW(x)                  (((x) & 0x3) << 30)
#define BIT_PUB_APB_PUB_DFS_SW_LOCK_REQ                          BIT(27)
#define BIT_PUB_APB_PUB_DFS_SW_LOCK_MODE                         BIT(26)
#define BIT_PUB_APB_EMC_CKG_MODE_PURE_SW(x)                      (((x) & 0x3) << 24)
#define BIT_PUB_APB_EMC_CKG_D2_SEL_PURE_SW(x)                    (((x) & 0xF) << 20)
#define BIT_PUB_APB_PURE_SW_DFS_CLK_MODE(x)                      (((x) & 0x3) << 18)
#define BIT_PUB_APB_PURE_SW_DFS_DENY                             BIT(16)
#define BIT_PUB_APB_PURE_SW_DFS_ACK                              BIT(15)
#define BIT_PUB_APB_PURE_SW_DFS_RESP                             BIT(14)
#define BIT_PUB_APB_PURE_SW_DFS_FC_REQ                           BIT(13)
#define BIT_PUB_APB_PURE_SW_DFS_REQ                              BIT(12)
#define BIT_PUB_APB_PURE_SW_DFS_FC_ACK                           BIT(11)
#define BIT_PUB_APB_PURE_SW_DFS_FRQ_SEL(x)                       (((x) & 0x7) << 8)
#define BIT_PUB_APB_EMC_CKG_SEL_PURE_SW(x)                       (((x) & 0x7F) << 1)
#define BIT_PUB_APB_DFS_SW_DFS_MODE                              BIT(0)

/* REG_PUB_APB_DFS_SW_CTRL */

#define BIT_PUB_APB_PUB_DFS_SWITCH_TYPE                          BIT(31)
#define BIT_PUB_APB_PUB_DFS_SW_SWITCH_PERIOD(x)                  (((x) & 0xFF) << 22)
#define BIT_PUB_APB_PUB_DFS_SW_RATIO_DEFAULT(x)                  (((x) & 0x7F) << 15)
#define BIT_PUB_APB_PUB_DFS_SW_RATIO(x)                          (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB_DFS_SW_DENY                              BIT(7)
#define BIT_PUB_APB_PUB_DFS_SW_FRQ_SEL(x)                        (((x) & 0x7) << 4)
#define BIT_PUB_APB_PUB_DFS_SW_RESP                              BIT(3)
#define BIT_PUB_APB_PUB_DFS_SW_ACK                               BIT(2)
#define BIT_PUB_APB_PUB_DFS_SW_REQ                               BIT(1)
#define BIT_PUB_APB_PUB_DFS_SW_ENABLE                            BIT(0)

/* REG_PUB_APB_DFS_SW_CTRL1 */

#define BIT_PUB_APB_PUB_DFS_SW_UG_DENY_EN                        BIT(22)
#define BIT_PUB_APB_PUB_DFS_SW_LP_DENY_EN                        BIT(21)
#define BIT_PUB_APB_PUB_DFS_SW_UG_CHK_EN                         BIT(20)
#define BIT_PUB_APB_PUB_DFS_SW_CLK_MODE_DEFAULT(x)               (((x) & 0x3) << 18)
#define BIT_PUB_APB_PUB_DFS_SW_CLK_MODE(x)                       (((x) & 0x3) << 16)
#define BIT_PUB_APB_PUB_DFS_SW_RATIO_MDLL_DEFAULT(x)             (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB_DFS_SW_RATIO_D2_DEFAULT(x)               (((x) & 0xF) << 8)
#define BIT_PUB_APB_PUB_DFS_SW_RATIO_MDLL(x)                     (((x) & 0x3) << 4)
#define BIT_PUB_APB_PUB_DFS_SW_RATIO_D2(x)                       (((x) & 0xF))

/* REG_PUB_APB_DFS_SW_CTRL2 */

#define BIT_PUB_APB_PUB_DFS_SW_DDL_ADJS_DEFAULT(x)               (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_PUB_DFS_SW_DDL_ADJS(x)                       (((x) & 0x1FF))

/* REG_PUB_APB_DFS_SW_CTRL3 */

#define BIT_PUB_APB_PUB_DFS_URGENT_WAIT_TIMEOUT_PERIOD(x)        (((x) & 0x3FF) << 18)
#define BIT_PUB_APB_PUB_DFS_URGENT_WAIT_TIMEOUT_EN               BIT(17)
#define BIT_PUB_APB_PUB_DFS_SW_URGENT_WAIT_EN                    BIT(16)
#define BIT_PUB_APB_PUB_DFS_SW_URGENT_DENY_EN(x)                 (((x) & 0xFFFF))

/* REG_PUB_APB_DFS_HW_CTRL */

#define BIT_PUB_APB_PUB_DFS_HW_DDL_ADJS_DEFAULT(x)               (((x) & 0x1FF) << 22)
#define BIT_PUB_APB_PUB_DFS_HW_CLK_MODE_DEFAULT(x)               (((x) & 0x3) << 20)
#define BIT_PUB_APB_PUB_DFS_HW_RATIO_D2_DEFAULT(x)               (((x) & 0xF) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_RATIO_DEFAULT(x)                  (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB_DFS_HW_INITIAL_FREQ(x)                   (((x) & 0x7) << 4)
#define BIT_PUB_APB_PUB_DFS_HW_STOP                              BIT(2)
#define BIT_PUB_APB_PUB_DFS_HW_START                             BIT(1)
#define BIT_PUB_APB_PUB_DFS_HW_ENABLE                            BIT(0)

/* REG_PUB_APB_DFS_HW_CTRL1 */

#define BIT_PUB_APB_SW_FORCE_EXIT_SW_LP_WAIT_ACK                 BIT(31)
#define BIT_PUB_APB_SW_FORCE_EXIT_HW_LP_WAIT_ACK                 BIT(30)
#define BIT_PUB_APB_SW_FORCE_EXIT_LP_WAIT_REQ                    BIT(29)
#define BIT_PUB_APB_PUB_DFS_HW_MIN_FREQ_UP_FORCE_TRIG            BIT(28)
#define BIT_PUB_APB_PUB_DFS_HW_BWMON_MIN_EN                      BIT(27)
#define BIT_PUB_APB_PUB_DFS_HW_BWMON_MIN_FREQ(x)                 (((x) & 0x7) << 24)
#define BIT_PUB_APB_PUB_DFS_HW_AVAIL_FREQ_EN(x)                  (((x) & 0xFF) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_RATIO_MDLL_DEFAULT(x)             (((x) & 0x3) << 13)
#define BIT_PUB_APB_PUB_DFS_HW_CHECK_PLL_EN                      BIT(12)
#define BIT_PUB_APB_PUB_DFS_HW_MIN_FREQ_UP(x)                    (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB_DFS_HW_MIN_FREQ_DN(x)                    (((x) & 0x7) << 4)
#define BIT_PUB_APB_PUB_DFS_HW_MIN_EN_UP                         BIT(3)
#define BIT_PUB_APB_PUB_DFS_HW_MIN_EN_DN                         BIT(2)
#define BIT_PUB_APB_PUB_DFS_HW_MIN_LOAD                          BIT(1)
#define BIT_PUB_APB_PUB_DFS_LP_PROT_EN                           BIT(0)

/* REG_PUB_APB_DFS_HW_CTRL2 */

#define BIT_PUB_APB_DFS_INC_REQ_HOLD_EN                          BIT(31)
#define BIT_PUB_APB_DFS_DEC_TO_INC_EN                            BIT(30)
#define BIT_PUB_APB_PUB_DFS_HW_DEC_UG_DENY_EN                    BIT(29)
#define BIT_PUB_APB_PUB_DFS_HW_INC_UG_DENY_EN                    BIT(28)
#define BIT_PUB_APB_PUB_DFS_HW_DEC_LP_DENY_EN                    BIT(27)
#define BIT_PUB_APB_PUB_DFS_HW_INC_LP_DENY_EN                    BIT(26)
#define BIT_PUB_APB_PUB_DFS_HW_DEC_UG_CHK_EN                     BIT(25)
#define BIT_PUB_APB_PUB_DFS_HW_INC_UG_CHK_EN                     BIT(24)
#define BIT_PUB_APB_PUB_DFS_HW_URGENT_WAIT_EN                    BIT(16)
#define BIT_PUB_APB_PUB_DFS_HW_URGENT_DENY_EN(x)                 (((x) & 0xFFFF))

/* REG_PUB_APB_DFS_HW_RATIO_SET0 */

#define BIT_PUB_APB_PUB_DFS_HW_F3_RATIO(x)                       (((x) & 0x7F) << 24)
#define BIT_PUB_APB_PUB_DFS_HW_F2_RATIO(x)                       (((x) & 0x7F) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_F1_RATIO(x)                       (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB_DFS_HW_F0_RATIO(x)                       (((x) & 0x7F))

/* REG_PUB_APB_DFS_HW_RATIO_SET1 */

#define BIT_PUB_APB_PUB_DFS_HW_F7_RATIO(x)                       (((x) & 0x7F) << 24)
#define BIT_PUB_APB_PUB_DFS_HW_F6_RATIO(x)                       (((x) & 0x7F) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_F5_RATIO(x)                       (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB_DFS_HW_F4_RATIO(x)                       (((x) & 0x7F))

/* REG_PUB_APB_DFS_HW_RATIO_SET2 */

#define BIT_PUB_APB_PUB_DFS_HW_F7_RATIO_D2(x)                    (((x) & 0xF) << 28)
#define BIT_PUB_APB_PUB_DFS_HW_F6_RATIO_D2(x)                    (((x) & 0xF) << 24)
#define BIT_PUB_APB_PUB_DFS_HW_F5_RATIO_D2(x)                    (((x) & 0xF) << 20)
#define BIT_PUB_APB_PUB_DFS_HW_F4_RATIO_D2(x)                    (((x) & 0xF) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_F3_RATIO_D2(x)                    (((x) & 0xF) << 12)
#define BIT_PUB_APB_PUB_DFS_HW_F2_RATIO_D2(x)                    (((x) & 0xF) << 8)
#define BIT_PUB_APB_PUB_DFS_HW_F1_RATIO_D2(x)                    (((x) & 0xF) << 4)
#define BIT_PUB_APB_PUB_DFS_HW_F0_RATIO_D2(x)                    (((x) & 0xF))

/* REG_PUB_APB_DFS_HW_RATIO_SET3 */

#define BIT_PUB_APB_PUB_DFS_HW_F7_RATIO_MDLL(x)                  (((x) & 0x3) << 30)
#define BIT_PUB_APB_PUB_DFS_HW_F6_RATIO_MDLL(x)                  (((x) & 0x3) << 28)
#define BIT_PUB_APB_PUB_DFS_HW_F5_RATIO_MDLL(x)                  (((x) & 0x3) << 26)
#define BIT_PUB_APB_PUB_DFS_HW_F4_RATIO_MDLL(x)                  (((x) & 0x3) << 24)
#define BIT_PUB_APB_PUB_DFS_HW_F3_RATIO_MDLL(x)                  (((x) & 0x3) << 22)
#define BIT_PUB_APB_PUB_DFS_HW_F2_RATIO_MDLL(x)                  (((x) & 0x3) << 20)
#define BIT_PUB_APB_PUB_DFS_HW_F1_RATIO_MDLL(x)                  (((x) & 0x3) << 18)
#define BIT_PUB_APB_PUB_DFS_HW_F0_RATIO_MDLL(x)                  (((x) & 0x3) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_F7_CLK_MODE(x)                    (((x) & 0x3) << 14)
#define BIT_PUB_APB_PUB_DFS_HW_F6_CLK_MODE(x)                    (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB_DFS_HW_F5_CLK_MODE(x)                    (((x) & 0x3) << 10)
#define BIT_PUB_APB_PUB_DFS_HW_F4_CLK_MODE(x)                    (((x) & 0x3) << 8)
#define BIT_PUB_APB_PUB_DFS_HW_F3_CLK_MODE(x)                    (((x) & 0x3) << 6)
#define BIT_PUB_APB_PUB_DFS_HW_F2_CLK_MODE(x)                    (((x) & 0x3) << 4)
#define BIT_PUB_APB_PUB_DFS_HW_F1_CLK_MODE(x)                    (((x) & 0x3) << 2)
#define BIT_PUB_APB_PUB_DFS_HW_F0_CLK_MODE(x)                    (((x) & 0x3))

/* REG_PUB_APB_DFS_HW_RATIO_SET4 */

#define BIT_PUB_APB_PUB_DFS_HW_F1_DDL_ADJS(x)                    (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_F0_DDL_ADJS(x)                    (((x) & 0x1FF))

/* REG_PUB_APB_DFS_HW_RATIO_SET5 */

#define BIT_PUB_APB_PUB_DFS_HW_F3_DDL_ADJS(x)                    (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_F2_DDL_ADJS(x)                    (((x) & 0x1FF))

/* REG_PUB_APB_DFS_HW_RATIO_SET6 */

#define BIT_PUB_APB_PUB_DFS_HW_F5_DDL_ADJS(x)                    (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_F4_DDL_ADJS(x)                    (((x) & 0x1FF))

/* REG_PUB_APB_DFS_HW_RATIO_SET7 */

#define BIT_PUB_APB_PUB_DFS_HW_F7_DDL_ADJS(x)                    (((x) & 0x1FF) << 16)
#define BIT_PUB_APB_PUB_DFS_HW_F6_DDL_ADJS(x)                    (((x) & 0x1FF))

/* REG_PUB_APB_VOTE_MASTER_EN */

#define BIT_PUB_APB_DFS_VOTE_DEC_EN                              BIT(31)
#define BIT_PUB_APB_VOTE_HW_DFS_DEC_MASK_EN                      BIT(30)
#define BIT_PUB_APB_VOTE_HW_DFS_INC_MASK_EN                      BIT(29)

/* REG_PUB_APB_VOTE_FSM_CNT */

#define BIT_PUB_APB_DFS_INTERVAL_CNT(x)                          (((x) & 0x7FFF) << 15)
#define BIT_PUB_APB_VOTE_INTERVAL_CNT(x)                         (((x) & 0x7FFF))

/* REG_PUB_APB_THRESHOLD_INC_FREQ_0 */

#define BIT_PUB_APB_THRD_INC_F0(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_THRESHOLD_INC_FREQ_1 */

#define BIT_PUB_APB_THRD_INC_F1(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_THRESHOLD_INC_FREQ_2 */

#define BIT_PUB_APB_THRD_INC_F2(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_THRESHOLD_INC_FREQ_3 */

#define BIT_PUB_APB_THRD_INC_F3(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_THRESHOLD_INC_FREQ_4 */

#define BIT_PUB_APB_THRD_INC_F4(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_THRESHOLD_INC_FREQ_5 */

#define BIT_PUB_APB_THRD_INC_F5(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_THRESHOLD_INC_FREQ_6 */

#define BIT_PUB_APB_THRD_INC_F6(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_THRESHOLD_INC_FREQ_7 */

#define BIT_PUB_APB_THRD_INC_F7(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_TEST_DSKPLL_BIST_CNT */

#define BIT_PUB_APB_TEST_DSKPLL_BIST_CNT(x)                      (((x) & 0xFFFF))

/* REG_PUB_APB_PUB_STATUS_MON_CTRL */

#define BIT_PUB_APB_DFS_COUNT_EN                                 BIT(9)
#define BIT_PUB_APB_PUB_DFS_STA_EN                               BIT(8)
#define BIT_PUB_APB_DMC_ST_MON_SEL(x)                            (((x) & 0x3) << 1)
#define BIT_PUB_APB_PUB_TOP_MON_EN                               BIT(0)

/* REG_PUB_APB_PUB_ST_IDLE_CYC_CNT */

#define BIT_PUB_APB_DMC_ST_IDLE_CYCLE_CNT(x)                     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_ST_WR_CYC_CNT */

#define BIT_PUB_APB_DMC_ST_WRITE_CYCLE_CNT(x)                    (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_ST_RD_CYC_CNT */

#define BIT_PUB_APB_DMC_ST_READ_CYCLE_CNT(x)                     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_ST_SR_CYC_CNT */

#define BIT_PUB_APB_DMC_ST_SREF_CYCLE_CNT(x)                     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_ST_LS_CYC_CNT */

#define BIT_PUB_APB_DMC_ST_LIGHT_CYCLE_CNT(x)                    (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_ST_LS_TIME_CNT */

#define BIT_PUB_APB_DMC_ST_SREF_CNT(x)                           (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_DMC_ST_LIGHT_CNT(x)                          (((x) & 0xFFFF))

/* REG_PUB_APB_PUB_DFS_F0_CYC_CNT */

#define BIT_PUB_APB_DFS_F0_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_DFS_F1_CYC_CNT */

#define BIT_PUB_APB_DFS_F1_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_DFS_F2_CYC_CNT */

#define BIT_PUB_APB_DFS_F2_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_DFS_F3_CYC_CNT */

#define BIT_PUB_APB_DFS_F3_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_DFS_F4_CYC_CNT */

#define BIT_PUB_APB_DFS_F4_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_DFS_F5_CYC_CNT */

#define BIT_PUB_APB_DFS_F5_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_DFS_F6_CYC_CNT */

#define BIT_PUB_APB_DFS_F6_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_DFS_F7_CYC_CNT */

#define BIT_PUB_APB_DFS_F7_CYCLE_CNT(x)                          (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_DFS_CNT */

#define BIT_PUB_APB_DFS_COUNT(x)                                 (((x) & 0x3FF))

/* REG_PUB_APB_VOTE_CTRL_DPU_0 */

#define BIT_PUB_APB_DPU_BV_EN                                    BIT(31)
#define BIT_PUB_APB_DPU_FV_EN                                    BIT(30)
#define BIT_PUB_APB_HW_VOTE_DPU_FLAG_EN                          BIT(29)
#define BIT_PUB_APB_BFV_VOTE_DPU_SW                              BIT(25)
#define BIT_PUB_APB_VOTE_DPU_ACK                                 BIT(23)
#define BIT_PUB_APB_VOTE_DPU_HW_ACK                              BIT(22)
#define BIT_PUB_APB_FREQ_VOTE_DPU(x)                             (((x) & 0x7) << 16)

/* REG_PUB_APB_VOTE_CTRL_DCAM_0 */

#define BIT_PUB_APB_DCAM_BV_EN                                   BIT(31)
#define BIT_PUB_APB_DCAM_FV_EN                                   BIT(30)
#define BIT_PUB_APB_HW_VOTE_DCAM_FLAG_EN                         BIT(29)
#define BIT_PUB_APB_BFV_VOTE_DCAM_SW                             BIT(25)
#define BIT_PUB_APB_VOTE_DCAM_ACK                                BIT(23)
#define BIT_PUB_APB_VOTE_DCAM_HW_ACK                             BIT(22)
#define BIT_PUB_APB_FREQ_VOTE_DCAM(x)                            (((x) & 0x7) << 16)

/* REG_PUB_APB_VOTE_CTRL_PUBCP_0 */

#define BIT_PUB_APB_PUBCP_BV_EN                                  BIT(31)
#define BIT_PUB_APB_PUBCP_FV_EN                                  BIT(30)
#define BIT_PUB_APB_BW_VOTE_PUBCP_FLAG                           BIT(25)
#define BIT_PUB_APB_FREQ_VOTE_PUBCP_FLAG                         BIT(24)
#define BIT_PUB_APB_VOTE_PUBCP_ACK                               BIT(23)
#define BIT_PUB_APB_FREQ_VOTE_PUBCP(x)                           (((x) & 0x7) << 16)

/* REG_PUB_APB_VOTE_CTRL_WTLCP_0 */

#define BIT_PUB_APB_WTLCP_BV_EN                                  BIT(31)
#define BIT_PUB_APB_WTLCP_FV_EN                                  BIT(30)
#define BIT_PUB_APB_BW_VOTE_WTLCP_FLAG                           BIT(25)
#define BIT_PUB_APB_FREQ_VOTE_WTLCP_FLAG                         BIT(24)
#define BIT_PUB_APB_VOTE_WTLCP_ACK                               BIT(23)
#define BIT_PUB_APB_FREQ_VOTE_WTLCP(x)                           (((x) & 0x7) << 16)

/* REG_PUB_APB_VOTE_CTRL_WTLCP1_0 */

#define BIT_PUB_APB_WTLCP1_BV_EN                                 BIT(31)
#define BIT_PUB_APB_WTLCP1_FV_EN                                 BIT(30)
#define BIT_PUB_APB_BW_VOTE_WTLCP1_FLAG                          BIT(25)
#define BIT_PUB_APB_FREQ_VOTE_WTLCP1_FLAG                        BIT(24)
#define BIT_PUB_APB_VOTE_WTLCP1_ACK                              BIT(23)
#define BIT_PUB_APB_FREQ_VOTE_WTLCP1(x)                          (((x) & 0x7) << 16)

/* REG_PUB_APB_VOTE_CTRL_AGCP_0 */

#define BIT_PUB_APB_AGCP_BV_EN                                   BIT(31)
#define BIT_PUB_APB_AGCP_FV_EN                                   BIT(30)
#define BIT_PUB_APB_BW_VOTE_AGCP_FLAG                            BIT(25)
#define BIT_PUB_APB_FREQ_VOTE_AGCP_FLAG                          BIT(24)
#define BIT_PUB_APB_VOTE_AGCP_ACK                                BIT(23)
#define BIT_PUB_APB_FREQ_VOTE_AGCP(x)                            (((x) & 0x7) << 16)

/* REG_PUB_APB_VOTE_CTRL_SW_0 */

#define BIT_PUB_APB_SW_BV_EN                                     BIT(31)
#define BIT_PUB_APB_SW_FV_EN                                     BIT(30)
#define BIT_PUB_APB_BW_VOTE_SW_FLAG                              BIT(25)
#define BIT_PUB_APB_FREQ_VOTE_SW_FLAG                            BIT(24)
#define BIT_PUB_APB_VOTE_SW_ACK                                  BIT(23)
#define BIT_PUB_APB_FREQ_VOTE_SW(x)                              (((x) & 0x7) << 16)

/* REG_PUB_APB_VOTE_CTRL_DPU_1 */

#define BIT_PUB_APB_BW_VOTE_DPU(x)                               (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_VOTE_CTRL_DCAM_1 */

#define BIT_PUB_APB_BW_VOTE_DCAM(x)                              (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_VOTE_CTRL_PUBCP_1 */

#define BIT_PUB_APB_BW_VOTE_PUBCP(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_VOTE_CTRL_WTLCP_1 */

#define BIT_PUB_APB_BW_VOTE_WTLCP(x)                             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_VOTE_CTRL_WTLCP1_1 */

#define BIT_PUB_APB_BW_VOTE_WTLCP1(x)                            (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_VOTE_CTRL_AGCP_1 */

#define BIT_PUB_APB_BW_VOTE_AGCP(x)                              (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_VOTE_CTRL_SW_1 */

#define BIT_PUB_APB_BW_VOTE_SW(x)                                (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DFS_GFREE_CTRL */

#define BIT_PUB_APB_DFS_GFREE_HW_BYPASS_EN                       BIT(24)
#define BIT_PUB_APB_DFS_GFREE_SW_OPEN_DELAY(x)                   (((x) & 0x1FF) << 10)
#define BIT_PUB_APB_DFS_GFREE_SW_CLOSE_DELAY(x)                  (((x) & 0x1FF) << 1)
#define BIT_PUB_APB_DFS_GFREE_SW_BYPASS                          BIT(0)

/* REG_PUB_APB_DFS_SW_CTRL_APPEND */

#define BIT_PUB_APB_PUB_DFS_SW_SWITCH_PERIOD_APPEND(x)           (((x) & 0xF))

/* REG_PUB_APB_AWURGENT_DBG_CTRL */

#define BIT_PUB_APB_AWURGENT_DBG_AI(x)                           (((x) & 0x3) << 28)
#define BIT_PUB_APB_AWURGENT_DBG_IPA2(x)                         (((x) & 0x3) << 26)
#define BIT_PUB_APB_AWURGENT_DBG_AGCP(x)                         (((x) & 0x3) << 24)
#define BIT_PUB_APB_AWURGENT_DBG_PUBCP(x)                        (((x) & 0x3) << 22)
#define BIT_PUB_APB_AWURGENT_DBG_WTLCP(x)                        (((x) & 0x3) << 20)
#define BIT_PUB_APB_AWURGENT_DBG_IPA1(x)                         (((x) & 0x3) << 18)
#define BIT_PUB_APB_AWURGENT_DBG_ESE(x)                          (((x) & 0x3) << 16)
#define BIT_PUB_APB_AWURGENT_DBG_AON(x)                          (((x) & 0x3) << 14)
#define BIT_PUB_APB_AWURGENT_DBG_AP(x)                           (((x) & 0x3) << 12)
#define BIT_PUB_APB_AWURGENT_DBG_VDSP(x)                         (((x) & 0x3) << 10)
#define BIT_PUB_APB_AWURGENT_DBG_MM_ISP(x)                       (((x) & 0x3) << 8)
#define BIT_PUB_APB_AWURGENT_DBG_ISP_RAW(x)                      (((x) & 0x3) << 6)
#define BIT_PUB_APB_AWURGENT_DBG_DPU(x)                          (((x) & 0x3) << 4)
#define BIT_PUB_APB_AWURGENT_DBG_GPU(x)                          (((x) & 0x3) << 2)
#define BIT_PUB_APB_AWURGENT_DBG_CPU(x)                          (((x) & 0x3))

/* REG_PUB_APB_ARURGENT_DBG_CTRL */

#define BIT_PUB_APB_ARURGENT_DBG_AI(x)                           (((x) & 0x3) << 28)
#define BIT_PUB_APB_ARURGENT_DBG_IPA2(x)                         (((x) & 0x3) << 26)
#define BIT_PUB_APB_ARURGENT_DBG_AGCP(x)                         (((x) & 0x3) << 24)
#define BIT_PUB_APB_ARURGENT_DBG_PUBCP(x)                        (((x) & 0x3) << 22)
#define BIT_PUB_APB_ARURGENT_DBG_WTLCP(x)                        (((x) & 0x3) << 20)
#define BIT_PUB_APB_ARURGENT_DBG_IPA1(x)                         (((x) & 0x3) << 18)
#define BIT_PUB_APB_ARURGENT_DBG_ESE(x)                          (((x) & 0x3) << 16)
#define BIT_PUB_APB_ARURGENT_DBG_AON(x)                          (((x) & 0x3) << 14)
#define BIT_PUB_APB_ARURGENT_DBG_AP(x)                           (((x) & 0x3) << 12)
#define BIT_PUB_APB_ARURGENT_DBG_VDSP(x)                         (((x) & 0x3) << 10)
#define BIT_PUB_APB_ARURGENT_DBG_MM_ISP(x)                       (((x) & 0x3) << 8)
#define BIT_PUB_APB_ARURGENT_DBG_ISP_RAW(x)                      (((x) & 0x3) << 6)
#define BIT_PUB_APB_ARURGENT_DBG_DPU(x)                          (((x) & 0x3) << 4)
#define BIT_PUB_APB_ARURGENT_DBG_GPU(x)                          (((x) & 0x3) << 2)
#define BIT_PUB_APB_ARURGENT_DBG_CPU(x)                          (((x) & 0x3))

/* REG_PUB_APB_LSLP_SRE_SIM */

#define BIT_PUB_APB_SRE_FLAG_DBG                                 BIT(1)
#define BIT_PUB_APB_SRE_REQ_DBG                                  BIT(0)

/* REG_PUB_APB_PUB0_DUMMY_REG0 */

#define BIT_PUB_APB_PUB0_DUMMY_REG0(x)                           (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB0_DUMMY_REG1 */

#define BIT_PUB_APB_PUB0_DUMMY_REG1(x)                           (((x) & 0xFFFFFFFF))


#endif /* PUB_APB_H */


