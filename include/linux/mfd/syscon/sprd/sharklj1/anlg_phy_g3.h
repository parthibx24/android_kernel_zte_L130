/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANLG_PHY_G3_REG_H
#define _ANLG_PHY_G3_REG_H



#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL0          0x0000
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL1          0x0004
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL2          0x0008
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL3          0x000C
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_BIST_CTRL      0x0010
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL0          0x0014
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL1          0x0018
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL2          0x001C
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL3          0x0020
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_BIST_CTRL      0x0024
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL_THM_CTRL        0x0028
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_CTRL_0          0x002C
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_CTRL_1          0x0030
#define REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_REG_SEL_CFG_0        0x0034

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL0
// Register Offset : 0x0000
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_N(x)                                   (((x) & 0x7FF) << 8)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_IBIAS(x)                               (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_LPF(x)                                 (((x) & 0x7) << 3)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_SDM_EN                                 BIT(2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_MOD_EN                                 BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_DIV_S                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL1
// Register Offset : 0x0004
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_NINT(x)                                (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_KINT(x)                                (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_PD                                     BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_RST                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL2
// Register Offset : 0x0008
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_RESERVED(x)                            (((x) & 0xFF) << 3)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_POSTDIV                                BIT(2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CLKOUT_EN                              BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_LOCK_DONE                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CTRL3
// Register Offset : 0x000C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_CCS_CTRL(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_BIST_CTRL
// Register Offset : 0x0010
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_BIST_EN                                BIT(24)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_BIST_CTRL(x)                           (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL0_BIST_CNT(x)                            (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL0
// Register Offset : 0x0014
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_N(x)                                   (((x) & 0x7FF) << 8)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_IBIAS(x)                               (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_LPF(x)                                 (((x) & 0x7) << 3)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_SDM_EN                                 BIT(2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_MOD_EN                                 BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_DIV_S                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL1
// Register Offset : 0x0018
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_NINT(x)                                (((x) & 0x7F) << 25)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_KINT(x)                                (((x) & 0x7FFFFF) << 2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_PD                                     BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_RST                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL2
// Register Offset : 0x001C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_RESERVED(x)                            (((x) & 0xFF) << 3)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_POSTDIV                                BIT(2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CLKOUT_EN                              BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_LOCK_DONE                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CTRL3
// Register Offset : 0x0020
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_CCS_CTRL(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_BIST_CTRL
// Register Offset : 0x0024
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_BIST_EN                                BIT(24)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_BIST_CTRL(x)                           (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL1_BIST_CNT(x)                            (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_MPLL_THM_CTRL
// Register Offset : 0x0028
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_TEST_THM0_SEL                                BIT(13)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_ANALOG_PLL_RESERVED(x)                       (((x) & 0x7FF) << 2)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_TEST_CLK_EN                                  BIT(1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_TEST_SEL                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_CTRL_0
// Register Offset : 0x002C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_BJT_SEL                                 BIT(24)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_PD                                      BIT(23)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_RSTN                                    BIT(22)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_RUN                                     BIT(21)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_CALI_EN                                 BIT(20)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_ITUNE(x)                                (((x) & 0xF) << 16)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_RESERVED(x)                             (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_CTRL_1
// Register Offset : 0x0030
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_DATA(x)                                 (((x) & 0xFF) << 1)
#define BIT_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_THM0_VALID                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G3_ANALOG_MPLL_THM_TOP_REG_SEL_CFG_0
// Register Offset : 0x0034
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_MPLL0_PD                             BIT(11)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_MPLL0_RST                            BIT(10)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_MPLL0_CLKOUT_EN                      BIT(9)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_MPLL1_PD                             BIT(8)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_MPLL1_RST                            BIT(7)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_MPLL1_CLKOUT_EN                      BIT(6)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_THM0_PD                              BIT(5)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_THM0_RSTN                            BIT(4)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_THM0_RUN                             BIT(3)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_THM0_CALI_EN                         BIT(2)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_THM0_ITUNE                           BIT(1)
#define BIT_ANLG_PHY_G3_DBG_SEL_ANALOG_MPLL_THM_TOP_THM0_RESERVED                        BIT(0)


#endif
