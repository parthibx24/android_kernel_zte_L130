/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANLG_PHY_G10_REG_H
#define _ANLG_PHY_G10_REG_H


#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_CLK_CTRL_0          0x0000
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_MODU_CTRL_0         0x0004
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DIV_CTRL_0          0x0008
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_PWR_CTRL_0          0x000C
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_ADC_CTRL_0          0x0010
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_ADC_DATA_0          0x0014
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_PLL_BIST_0          0x0018
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_WRAP_GLUE_CTRL      0x001C
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DUMY_RW0            0x0020
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DUMY_RO0            0x0024
#define REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_REG_SEL_CFG_0       0x0028

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_CLK_CTRL_0
// Register Offset : 0x0000
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_N(x)                                 (((x) & 0x7F) << 10)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_IBIAS(x)                             (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_LPF(x)                               (((x) & 0x7) << 5)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_VSET(x)                              (((x) & 0x7) << 2)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_CLKOUT_EN                            BIT(1)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_LOCK_DONE                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_MODU_CTRL_0
// Register Offset : 0x0004
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_NINT(x)                              (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_KINT(x)                              (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_SDM_EN                               BIT(1)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_MOD_EN                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DIV_CTRL_0
// Register Offset : 0x0008
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_DIV_S                                BIT(12)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_DIV_SEL(x)                           (((x) & 0xF) << 8)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_RESERVED(x)                          (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_PWR_CTRL_0
// Register Offset : 0x000C
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_PD                                   BIT(2)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_THM0_PD                                   BIT(1)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_RST                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_ADC_CTRL_0
// Register Offset : 0x0010
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_THM0_RSTN                                 BIT(22)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_THM0_RUN                                  BIT(21)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_THM0_CALI_EN                              BIT(20)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_THM0_ITUNE(x)                             (((x) & 0xF) << 16)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_THM0_RESERVED(x)                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_ADC_DATA_0
// Register Offset : 0x0014
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_THM0_DATA(x)                              (((x) & 0xFF) << 1)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_THM0_VALID                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_PLL_BIST_0
// Register Offset : 0x0018
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_BIST_EN                              BIT(24)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_BIST_CTRL(x)                         (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_BIST_CNT(x)                          (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_WRAP_GLUE_CTRL
// Register Offset : 0x001C
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DPLL_REF_SEL                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DUMY_RW0
// Register Offset : 0x0020
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DUMMY_RW0(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DUMY_RO0
// Register Offset : 0x0024
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_DUMMY_RO0(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G10_ANALOG_DPLL_THM_TOP_1_REG_SEL_CFG_0
// Register Offset : 0x0028
// Description:
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_DPLL_CLKOUT_EN                    BIT(9)
#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_DPLL_DIV_SEL                      BIT(8)
#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_DPLL_PD                           BIT(7)
#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_THM0_PD                           BIT(6)
#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_DPLL_RST                          BIT(5)
#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_THM0_RSTN                         BIT(4)
#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_THM0_RUN                          BIT(3)
#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_THM0_CALI_EN                      BIT(2)
#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_THM0_ITUNE                        BIT(1)
#define BIT_ANLG_PHY_G10_DBG_SEL_ANALOG_DPLL_THM_TOP_1_THM0_RESERVED                     BIT(0)


#endif
