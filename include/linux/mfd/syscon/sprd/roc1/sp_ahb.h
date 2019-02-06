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


#ifndef SP_AHB_H
#define SP_AHB_H



#define REG_SP_AHB_CFG_CLK_EB                (0x0000)
#define REG_SP_AHB_SOFT_RST                  (0x0004)
#define REG_SP_AHB_DMA_CTRL                  (0x0008)
#define REG_SP_AHB_SLP_CTL                   (0x000C)
#define REG_SP_AHB_CM4_CORE_CFG1             (0x0010)
#define REG_SP_AHB_CM4_CORE_SYSTICK_CFG      (0x0014)
#define REG_SP_AHB_CM4_CORE_AUXFAULT_CFG     (0x0018)
#define REG_SP_AHB_CM4_MAIN_STATOUT          (0x001C)
#define REG_SP_AHB_CM4_HWDATAD_STAT          (0x0020)
#define REG_SP_AHB_CM4_INT_STAT              (0x0024)
#define REG_SP_AHB_WDG_ENABLE                (0x0028)
#define REG_SP_AHB_FPU_CFG                   (0x0034)
#define REG_SP_AHB_AHB_MTX_CTL0              (0x0040)
#define REG_SP_AHB_AHB_MTX_CTL1              (0x0044)
#define REG_SP_AHB_AHB_MTX_CTL2              (0x0048)
#define REG_SP_AHB_AHB_MTX_CTL3              (0x004C)
#define REG_SP_AHB_AHB_MTX_CTL4              (0x0050)
#define REG_SP_AHB_SP_AON_DDR_EXTEND         (0x0060)
#define REG_SP_AHB_RES_REG                   (0x00FF)

/* REG_SP_AHB_CFG_CLK_EB */

#define BIT_SP_AHB_EIC_GPIO_EB               BIT(17)
#define BIT_SP_AHB_EIC_GPIO_RTC_EB           BIT(16)
#define BIT_SP_AHB_EIC_GPIO_RTCDV5_EB        BIT(15)
#define BIT_SP_AHB_SPI_EB                    BIT(14)
#define BIT_SP_AHB_I3C1_EB                   BIT(13)
#define BIT_SP_AHB_I3C0_EB                   BIT(12)
#define BIT_SP_AHB_GPIO_EB                   BIT(11)
#define BIT_SP_AHB_UART1_EB                  BIT(10)
#define BIT_SP_AHB_UART0_EB                  BIT(9)
#define BIT_SP_AHB_TMR_EB                    BIT(8)
#define BIT_SP_AHB_SYST_EB                   BIT(7)
#define BIT_SP_AHB_EIC_RTCDV5_EB             BIT(6)
#define BIT_SP_AHB_EIC_EB                    BIT(5)
#define BIT_SP_AHB_INTC_EB                   BIT(4)
#define BIT_SP_AHB_EIC_RTC_EB                BIT(3)
#define BIT_SP_AHB_IMC_EB                    BIT(2)
#define BIT_SP_AHB_TIC_EB                    BIT(1)

/* REG_SP_AHB_SOFT_RST */

#define BIT_SP_AHB_EIC_GPIO_SOFT_RST         BIT(15)
#define BIT_SP_AHB_SPI_SOFT_RST              BIT(14)
#define BIT_SP_AHB_I3C1_SOFT_RST             BIT(13)
#define BIT_SP_AHB_I3C0_SOFT_RST             BIT(12)
#define BIT_SP_AHB_GPIO_SOFT_RST             BIT(11)
#define BIT_SP_AHB_UART1_SOFT_RST            BIT(10)
#define BIT_SP_AHB_UART0_SOFT_RST            BIT(9)
#define BIT_SP_AHB_TMR_SOFT_RST              BIT(8)
#define BIT_SP_AHB_SYST_SOFT_RST             BIT(7)
#define BIT_SP_AHB_WDG_SOFT_RST              BIT(6)
#define BIT_SP_AHB_EIC_SOFT_RST              BIT(5)
#define BIT_SP_AHB_INTC_SOFT_RST             BIT(4)
#define BIT_SP_AHB_IMC_SOFT_RST              BIT(2)
#define BIT_SP_AHB_TIC_SOFT_RST              BIT(1)
#define BIT_SP_AHB_ARCH_SOFT_RST             BIT(0)

/* REG_SP_AHB_DMA_CTRL */

#define BIT_SP_AHB_CM4_DMA_SOFT_RST          BIT(9)
#define BIT_SP_AHB_CM4_DMA_EB                BIT(8)
#define BIT_SP_AHB_HPROT_CM4_PUB_WR(x)       (((x) & 0xF) << 4)
#define BIT_SP_AHB_HPROT_CM4_PUB_RD(x)       (((x) & 0xF))

/* REG_SP_AHB_SLP_CTL */

#define BIT_SP_AHB_SYS_AUTO_GATE_EN          BIT(2)
#define BIT_SP_AHB_CORE_AUTO_GATE_EN         BIT(0)

/* REG_SP_AHB_CM4_CORE_CFG1 */

#define BIT_SP_AHB_SOFT_EXRESPD              BIT(9)
#define BIT_SP_AHB_SOFT_TSCLK_CHG            BIT(7)
#define BIT_SP_AHB_SOFT_FIX_MSTTYPE          BIT(6)
#define BIT_SP_AHB_SOFT_DBG_RESTART          BIT(5)
#define BIT_SP_AHB_SOFT_EDBGRQ               BIT(4)
#define BIT_SP_AHB_SOFT_SLEEP_HOLD_REQ_N     BIT(3)
#define BIT_SP_AHB_SOFT_EXRESPS              BIT(2)
#define BIT_SP_AHB_SOFT_CGBYPASS             BIT(1)
#define BIT_SP_AHB_SOFT_RSTBYPASS            BIT(0)

/* REG_SP_AHB_CM4_CORE_SYSTICK_CFG */

#define BIT_SP_AHB_SOFT_STCALIB(x)           (((x) & 0x3FFFFFF) << 1)
#define BIT_SP_AHB_SOFT_STCLK                BIT(0)

/* REG_SP_AHB_CM4_CORE_AUXFAULT_CFG */

#define BIT_SP_AHB_SOFT_AUXFAULT(x)          (((x) & 0xFFFFFFFF))

/* REG_SP_AHB_CM4_MAIN_STATOUT */

#define BIT_SP_AHB_WICENACK_STAT             BIT(31)
#define BIT_SP_AHB_GATEHCLK_STAT             BIT(30)
#define BIT_SP_AHB_WAKEUP_STAT               BIT(29)
#define BIT_SP_AHB_SLEEPHOLDACKN_STAT        BIT(28)
#define BIT_SP_AHB_SLEEPINGDEEP_STAT         BIT(27)
#define BIT_SP_AHB_SLEEPING_STAT             BIT(26)
#define BIT_SP_AHB_DBGRESTARTED_STAT         BIT(24)
#define BIT_SP_AHB_HALTED_STAT               BIT(23)
#define BIT_SP_AHB_BRCHSTAT_STAT(x)          (((x) & 0xF) << 19)
#define BIT_SP_AHB_EXREQS_STAT               BIT(18)
#define BIT_SP_AHB_MEMATTRS_STAT(x)          (((x) & 0x3) << 16)
#define BIT_SP_AHB_HMASTLOCKS_STAT           BIT(15)
#define BIT_SP_AHB_HMASTERS_STAT(x)          (((x) & 0x3) << 13)
#define BIT_SP_AHB_HWRITED_STAT              BIT(12)
#define BIT_SP_AHB_EXREQD_STAT               BIT(11)
#define BIT_SP_AHB_MEMATTRD_STAT(x)          (((x) & 0x3) << 9)
#define BIT_SP_AHB_HMASTERD_STAT(x)          (((x) & 0x3) << 7)
#define BIT_SP_AHB_MEMATTRI_STAT(x)          (((x) & 0x3) << 5)
#define BIT_SP_AHB_SWV_STAT                  BIT(4)
#define BIT_SP_AHB_CDBGPWRUPREQ_STAT         BIT(0)

/* REG_SP_AHB_CM4_HWDATAD_STAT */

#define BIT_SP_AHB_HWDATAD_STAT(x)           (((x) & 0xFFFFFFFF))

/* REG_SP_AHB_CM4_INT_STAT */

#define BIT_SP_AHB_CURRPRI_STAT(x)           (((x) & 0xFF))

/* REG_SP_AHB_WDG_ENABLE */

#define BIT_SP_AHB_WDG_EB                    BIT(0)

/* REG_SP_AHB_FPU_CFG */

#define BIT_SP_AHB_FPU_DISABLE               BIT(0)

/* REG_SP_AHB_AHB_MTX_CTL0 */

#define BIT_SP_AHB_PRI_M3TOS0_ADJ_EN         BIT(31)
#define BIT_SP_AHB_PRI_M3TOS0_RND_THR(x)     (((x) & 0xF) << 27)
#define BIT_SP_AHB_PRI_M3TOS0_RND_EN         BIT(26)
#define BIT_SP_AHB_PRI_M3TOS0_SEL(x)         (((x) & 0x3) << 24)
#define BIT_SP_AHB_PRI_M2TOS0_ADJ_EN         BIT(23)
#define BIT_SP_AHB_PRI_M2TOS0_RND_THR(x)     (((x) & 0xF) << 19)
#define BIT_SP_AHB_PRI_M2TOS0_RND_EN         BIT(18)
#define BIT_SP_AHB_PRI_M2TOS0_SEL(x)         (((x) & 0x3) << 16)
#define BIT_SP_AHB_PRI_M1TOS0_ADJ_EN         BIT(15)
#define BIT_SP_AHB_PRI_M1TOS0_RND_THR(x)     (((x) & 0xF) << 11)
#define BIT_SP_AHB_PRI_M1TOS0_RND_EN         BIT(10)
#define BIT_SP_AHB_PRI_M1TOS0_SEL(x)         (((x) & 0x3) << 8)
#define BIT_SP_AHB_PRI_M0TOS0_ADJ_EN         BIT(7)
#define BIT_SP_AHB_PRI_M0TOS0_RND_THR(x)     (((x) & 0xF) << 3)
#define BIT_SP_AHB_PRI_M0TOS0_RND_EN         BIT(2)
#define BIT_SP_AHB_PRI_M0TOS0_SEL(x)         (((x) & 0x3))

/* REG_SP_AHB_AHB_MTX_CTL1 */

#define BIT_SP_AHB_PRI_M2TOS1_ADJ_EN         BIT(31)
#define BIT_SP_AHB_PRI_M2TOS1_RND_THR(x)     (((x) & 0xF) << 27)
#define BIT_SP_AHB_PRI_M2TOS1_RND_EN         BIT(26)
#define BIT_SP_AHB_PRI_M2TOS1_SEL(x)         (((x) & 0x3) << 24)
#define BIT_SP_AHB_PRI_M6TOS0_ADJ_EN         BIT(23)
#define BIT_SP_AHB_PRI_M6TOS0_RND_THR(x)     (((x) & 0xF) << 19)
#define BIT_SP_AHB_PRI_M6TOS0_RND_EN         BIT(18)
#define BIT_SP_AHB_PRI_M6TOS0_SEL(x)         (((x) & 0x3) << 16)
#define BIT_SP_AHB_PRI_M5TOS0_ADJ_EN         BIT(15)
#define BIT_SP_AHB_PRI_M5TOS0_RND_THR(x)     (((x) & 0xF) << 11)
#define BIT_SP_AHB_PRI_M5TOS0_RND_EN         BIT(10)
#define BIT_SP_AHB_PRI_M5TOS0_SEL(x)         (((x) & 0x3) << 8)
#define BIT_SP_AHB_PRI_M4TOS0_ADJ_EN         BIT(7)
#define BIT_SP_AHB_PRI_M4TOS0_RND_THR(x)     (((x) & 0xF) << 3)
#define BIT_SP_AHB_PRI_M4TOS0_RND_EN         BIT(2)
#define BIT_SP_AHB_PRI_M4TOS0_SEL(x)         (((x) & 0x3))

/* REG_SP_AHB_AHB_MTX_CTL2 */

#define BIT_SP_AHB_PRI_M0TOS2_ADJ_EN         BIT(31)
#define BIT_SP_AHB_PRI_M0TOS2_RND_THR(x)     (((x) & 0xF) << 27)
#define BIT_SP_AHB_PRI_M0TOS2_RND_EN         BIT(26)
#define BIT_SP_AHB_PRI_M0TOS2_SEL(x)         (((x) & 0x3) << 24)
#define BIT_SP_AHB_PRI_M6TOS1_ADJ_EN         BIT(23)
#define BIT_SP_AHB_PRI_M6TOS1_RND_THR(x)     (((x) & 0xF) << 19)
#define BIT_SP_AHB_PRI_M6TOS1_RND_EN         BIT(18)
#define BIT_SP_AHB_PRI_M6TOS1_SEL(x)         (((x) & 0x3) << 16)
#define BIT_SP_AHB_PRI_M5TOS1_ADJ_EN         BIT(15)
#define BIT_SP_AHB_PRI_M5TOS1_RND_THR(x)     (((x) & 0xF) << 11)
#define BIT_SP_AHB_PRI_M5TOS1_RND_EN         BIT(10)
#define BIT_SP_AHB_PRI_M5TOS1_SEL(x)         (((x) & 0x3) << 8)
#define BIT_SP_AHB_PRI_M4TOS1_ADJ_EN         BIT(7)
#define BIT_SP_AHB_PRI_M4TOS1_RND_THR(x)     (((x) & 0xF) << 3)
#define BIT_SP_AHB_PRI_M4TOS1_RND_EN         BIT(2)
#define BIT_SP_AHB_PRI_M4TOS1_SEL(x)         (((x) & 0x3))

/* REG_SP_AHB_AHB_MTX_CTL3 */

#define BIT_SP_AHB_PRI_M4TOS2_ADJ_EN         BIT(31)
#define BIT_SP_AHB_PRI_M4TOS2_RND_THR(x)     (((x) & 0xF) << 27)
#define BIT_SP_AHB_PRI_M4TOS2_RND_EN         BIT(26)
#define BIT_SP_AHB_PRI_M4TOS2_SEL(x)         (((x) & 0x3) << 24)
#define BIT_SP_AHB_PRI_M3TOS2_ADJ_EN         BIT(23)
#define BIT_SP_AHB_PRI_M3TOS2_RND_THR(x)     (((x) & 0xF) << 19)
#define BIT_SP_AHB_PRI_M3TOS2_RND_EN         BIT(18)
#define BIT_SP_AHB_PRI_M3TOS2_SEL(x)         (((x) & 0x3) << 16)
#define BIT_SP_AHB_PRI_M2TOS2_ADJ_EN         BIT(15)
#define BIT_SP_AHB_PRI_M2TOS2_RND_THR(x)     (((x) & 0xF) << 11)
#define BIT_SP_AHB_PRI_M2TOS2_RND_EN         BIT(10)
#define BIT_SP_AHB_PRI_M2TOS2_SEL(x)         (((x) & 0x3) << 8)
#define BIT_SP_AHB_PRI_M1TOS2_ADJ_EN         BIT(7)
#define BIT_SP_AHB_PRI_M1TOS2_RND_THR(x)     (((x) & 0xF) << 3)
#define BIT_SP_AHB_PRI_M1TOS2_RND_EN         BIT(2)
#define BIT_SP_AHB_PRI_M1TOS2_SEL(x)         (((x) & 0x3))

/* REG_SP_AHB_AHB_MTX_CTL4 */

#define BIT_SP_AHB_PRI_M6TOS2_ADJ_EN         BIT(15)
#define BIT_SP_AHB_PRI_M6TOS2_RND_THR(x)     (((x) & 0xF) << 11)
#define BIT_SP_AHB_PRI_M6TOS2_RND_EN         BIT(10)
#define BIT_SP_AHB_PRI_M6TOS2_SEL(x)         (((x) & 0x3) << 8)
#define BIT_SP_AHB_PRI_M5TOS2_ADJ_EN         BIT(7)
#define BIT_SP_AHB_PRI_M5TOS2_RND_THR(x)     (((x) & 0xF) << 3)
#define BIT_SP_AHB_PRI_M5TOS2_RND_EN         BIT(2)
#define BIT_SP_AHB_PRI_M5TOS2_SEL(x)         (((x) & 0x3))

/* REG_SP_AHB_SP_AON_DDR_EXTEND */

#define BIT_SP_AHB_REG_SP_AON_DDR_EXTEND(x)  (((x) & 0x3))

/* REG_SP_AHB_RES_REG */

#define BIT_SP_AHB_RES_REG_H(x)              (((x) & 0xFF) << 24)
#define BIT_SP_AHB_RES_REG_L(x)              (((x) & 0xFFFFFF))


#endif /* SP_AHB_H */


