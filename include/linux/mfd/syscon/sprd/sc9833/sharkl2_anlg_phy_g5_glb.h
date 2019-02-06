/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _ANLG_PHY_G5_REG_H
#define _ANLG_PHY_G5_REG_H



#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_2L_CLKLANE                   0x0000
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_2L_STATE                     0x0004
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_2L_CTRL                      0x0008
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_2L_RES                       0x000C
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_PHY_BIST_TEST               0x0010
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_REG_SEL_CFG_0                    0x0014
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CLKLANE_STATE_M       0x0018
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_STATE_M               0x001C
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CTRL_M                0x0020
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CTRL_CSI_2P2L                  0x0024
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_RES                   0x0028
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CLKLANE_STATE_S       0x002C
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_STATE_S               0x0030
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CTRL_S                0x0034
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXCLKLANE_DB          0x0038
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATA_0_DB           0x003C
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATA_1_DB           0x0040
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATA_2_DB           0x0044
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATA_3_DB           0x0048
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATAESC_DB          0x004C
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_STATE_RX_DB           0x0050
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_DATALANE_CTRL_DB      0x0054
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_ERR_DB                0x0058
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CTRL_DB               0x005C
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TEST_DB               0x0060
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_REG_SEL_CFG_0                  0x0064
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_REG_SEL_CFG_1                  0x0068
#define REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_REG_SEL_CFG_2                  0x006C

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_2L_CLKLANE
// Register Offset : 0x0000
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_STOPSTATECLK                                     BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_RXULPSCLKNOT                                     BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_RXCLKACTIVEHS                                    BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ULPSACTIVENOTCLK                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_2L_STATE
// Register Offset : 0x0004
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_RXULPSESC_0                                      BIT(18)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ULPSACTIVENOT_0                                  BIT(17)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_DIRECTION_0                                      BIT(16)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_FORCERXMODE_0                                    BIT(15)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_STOPSTATEDATA_0                                  BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRSOTHS_0                                       BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRSOTSYNCHS_0                                   BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRESC_0                                         BIT(11)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRSYNCESC_0                                     BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRCONTROL_0                                     BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ULPSACTIVENOT_1                                  BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_DIRECTION_1                                      BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_FORCERXMODE_1                                    BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_STOPSTATEDATA_1                                  BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRSOTHS_1                                       BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRSOTSYNCHS_1                                   BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRESC_1                                         BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRSYNCESC_1                                     BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ERRCONTROL_1                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_2L_CTRL
// Register Offset : 0x0008
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_PS_PD_S                                          BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_PS_PD_L                                          BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_SHUTDOWNZ                                        BIT(11)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_RSTZ                                             BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ENABLE_0                                         BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ENABLE_1                                         BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_ENABLECLK                                        BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_BISTON                                           BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_BISTOK                                           BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_IF_SEL                                           BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_RX_RCTL(x)                                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_2L_RES
// Register Offset : 0x000C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_RESERVED(x)                                      (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_CSI_RESERVEDO(x)                                     (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_PHY_BIST_TEST
// Register Offset : 0x0010
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_REFDIV(x)                                       (((x) & 0xF) << 11)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_TXREQHSCLK_DB                                   BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_BERT_RXBYTECLK_SEL(x)                           (((x) & 0x3) << 8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_BERT_D0_TXSRC_SEL(x)                            (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_BERT_D1_TXSRC_SEL(x)                            (((x) & 0x3) << 4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_BERT_D2_TXSRC_SEL                               BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_BERT_D3_TXSRC_SEL                               BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_BERT_TEST_SEL                                   BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_MIPI_BERT_REFCLK_EN                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2LANE_REG_SEL_CFG_0
// Register Offset : 0x0014
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_FORCERXMODE_0                            BIT(12)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_FORCERXMODE_1                            BIT(11)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_PS_PD_S                                  BIT(10)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_PS_PD_L                                  BIT(9)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_SHUTDOWNZ                                BIT(8)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_RSTZ                                     BIT(7)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_ENABLE_0                                 BIT(6)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_ENABLE_1                                 BIT(5)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_ENABLECLK                                BIT(4)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_BISTON                                   BIT(3)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_IF_SEL                                   BIT(2)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_RX_RCTL                                  BIT(1)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2LANE_CSI_RESERVED                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CLKLANE_STATE_M
// Register Offset : 0x0018
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_STOPSTATECLK_M                                 BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RXULPSCLKNOT_M                                 BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RXCLKACTIVEHS_M                                BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ULPSACTIVENOTCLK_M                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_STATE_M
// Register Offset : 0x001C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RXULPSESC_0_M                                  BIT(18)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ULPSACTIVENOT_0_M                              BIT(17)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_DIRECTION_0_M                                  BIT(16)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_FORCERXMODE_0_M                                BIT(15)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_STOPSTATEDATA_0_M                              BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSOTHS_0_M                                   BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSOTSYNCHS_0_M                               BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRESC_0_M                                     BIT(11)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSYNCESC_0_M                                 BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRCONTROL_0_M                                 BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ULPSACTIVENOT_1_M                              BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_DIRECTION_1_M                                  BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_FORCERXMODE_1_M                                BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_STOPSTATEDATA_1_M                              BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSOTHS_1_M                                   BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSOTSYNCHS_1_M                               BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRESC_1_M                                     BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSYNCESC_1_M                                 BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRCONTROL_1_M                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CTRL_M
// Register Offset : 0x0020
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_SHUTDOWNZ_M                                    BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RSTZ_M                                         BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLE_0_M                                     BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLE_1_M                                     BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLECLK_M                                    BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_IF_SEL_M                                       BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_BISTON_M                                       BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_BISTOK_M                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CTRL_CSI_2P2L
// Register Offset : 0x0024
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_PS_PD_S                                        BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_PS_PD_L                                        BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_MODE_SEL                                       BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RX_RCTL(x)                                     (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_RES
// Register Offset : 0x0028
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RESERVED(x)                                    (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RESERVEDO(x)                                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CLKLANE_STATE_S
// Register Offset : 0x002C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_STOPSTATECLK_S                                 BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RXULPSCLKNOT_S                                 BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RXCLKACTIVEHS_S                                BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ULPSACTIVENOTCLK_S                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_STATE_S
// Register Offset : 0x0030
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RXULPSESC_0_S                                  BIT(18)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ULPSACTIVENOT_0_S                              BIT(17)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_DIRECTION_0_S                                  BIT(16)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_FORCERXMODE_0_S                                BIT(15)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_STOPSTATEDATA_0_S                              BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSOTHS_0_S                                   BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSOTSYNCHS_0_S                               BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRESC_0_S                                     BIT(11)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSYNCESC_0_S                                 BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRCONTROL_0_S                                 BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ULPSACTIVENOT_1_S                              BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_DIRECTION_1_S                                  BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_FORCERXMODE_1_S                                BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_STOPSTATEDATA_1_S                              BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSOTHS_1_S                                   BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSOTSYNCHS_1_S                               BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRESC_1_S                                     BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRSYNCESC_1_S                                 BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ERRCONTROL_1_S                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CTRL_S
// Register Offset : 0x0034
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_SHUTDOWNZ_S                                    BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_RSTZ_S                                         BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLE_0_S                                     BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLE_1_S                                     BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLECLK_S                                    BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_IF_SEL_S                                       BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_BISTON_S                                       BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_BISTOK_S                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXCLKLANE_DB
// Register Offset : 0x0038
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTHSCLK_DB                              BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSCLK_DB                                   BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXITCLK_DB                               BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_STOPSTATECLK_DB                                BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ULPSACTIVENOTCLK_DB                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATA_0_DB
// Register Offset : 0x003C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTDATAHS_0_DB                           BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTESC_0_DB                              BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXLPDTESC_0_DB                                 BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSESC_0_DB                                 BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXIT_0_DB                                BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXTRIGGERESC_0_DB(x)                           (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXVALIDESC_0_DB                                BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREADYESC_0_DB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATA_1_DB
// Register Offset : 0x0040
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTDATAHS_1_DB                           BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTESC_1_DB                              BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXLPDTESC_1_DB                                 BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSESC_1_DB                                 BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXIT_1_DB                                BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXTRIGGERESC_1_DB(x)                           (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXVALIDESC_1_DB                                BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREADYESC_1_DB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATA_2_DB
// Register Offset : 0x0044
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTDATAHS_2_DB                           BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTESC_2_DB                              BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXLPDTESC_2_DB                                 BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSESC_2_DB                                 BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXIT_2_DB                                BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXTRIGGERESC_2_DB(x)                           (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXVALIDESC_2_DB                                BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREADYESC_2_DB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATA_3_DB
// Register Offset : 0x0048
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTDATAHS_3_DB                           BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTESC_3_DB                              BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXLPDTESC_3_DB                                 BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSESC_3_DB                                 BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXIT_3_DB                                BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXTRIGGERESC_3_DB(x)                           (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXVALIDESC_3_DB                                BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREADYESC_3_DB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TXDATAESC_DB
// Register Offset : 0x004C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXDATAESC_0_DB(x)                              (((x) & 0xFF) << 24)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXDATAESC_1_DB(x)                              (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXDATAESC_2_DB(x)                              (((x) & 0xFF) << 8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TXDATAESC_3_DB(x)                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_STATE_RX_DB
// Register Offset : 0x0050
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXCLKESC_0_DB                                  BIT(27)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXLPDTESC_0_DB                                 BIT(26)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXTRIGGERESC_0_DB(x)                           (((x) & 0xF) << 22)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXVALIDESC_0_DB                                BIT(21)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXCLKESC_1_DB                                  BIT(20)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXLPDTESC_1_DB                                 BIT(19)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXTRIGGERESC_1_DB(x)                           (((x) & 0xF) << 15)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXVALIDESC_1_DB                                BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXCLKESC_2_DB                                  BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXLPDTESC_2_DB                                 BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXTRIGGERESC_2_DB(x)                           (((x) & 0xF) << 8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXVALIDESC_2_DB                                BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXCLKESC_3_DB                                  BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXLPDTESC_3_DB                                 BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXTRIGGERESC_3_DB(x)                           (((x) & 0xF) << 1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RXVALIDESC_3_DB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_DATALANE_CTRL_DB
// Register Offset : 0x0054
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNREQUEST_0_DB                               BIT(22)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_DIRECTION_0_DB                                 BIT(21)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNDISABLE_0_DB                               BIT(20)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCERXMODE_0_DB                               BIT(19)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCETXSTOPMODE_0_DB                           BIT(18)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_STOPSTATEDATA_0_DB                             BIT(17)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNREQUEST_1_DB                               BIT(16)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNDISABLE_1_DB                               BIT(15)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCERXMODE_1_DB                               BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCETXSTOPMODE_1_DB                           BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_STOPSTATEDATA_1_DB                             BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNREQUEST_2_DB                               BIT(11)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_DIRECTION_2_DB                                 BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNDISABLE_2_DB                               BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCERXMODE_2_DB                               BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCETXSTOPMODE_2_DB                           BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_STOPSTATEDATA_2_DB                             BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNREQUEST_3_DB                               BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_DIRECTION_3_DB                                 BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNDISABLE_3_DB                               BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCERXMODE_3_DB                               BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCETXSTOPMODE_3_DB                           BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_STOPSTATEDATA_3_DB                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_ERR_DB
// Register Offset : 0x0058
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRESC_0_DB                                    BIT(19)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRSYNCESC_0_DB                                BIT(18)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTROL_0_DB                                BIT(17)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTENTIONLP0_0_DB                          BIT(16)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTENTIONLP1_0_DB                          BIT(15)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRESC_1_DB                                    BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRSYNCESC_1_DB                                BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTROL_1_DB                                BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTENTIONLP0_1_DB                          BIT(11)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTENTIONLP1_1_DB                          BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRESC_2_DB                                    BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRSYNCESC_2_DB                                BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTROL_2_DB                                BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTENTIONLP0_2_DB                          BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTENTIONLP1_2_DB                          BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRESC_3_DB                                    BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRSYNCESC_3_DB                                BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTROL_3_DB                                BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTENTIONLP0_3_DB                          BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ERRCONTENTIONLP1_3_DB                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_CTRL_DB
// Register Offset : 0x005C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_SHUTDOWNZ_DB                                   BIT(16)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_RSTZ_DB                                        BIT(15)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLE_0_DB                                    BIT(14)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLE_1_DB                                    BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLE_2_DB                                    BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLE_3_DB                                    BIT(11)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLECLK_DB                                   BIT(10)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCEPLL_DB                                    BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_PLLLOCK_DB                                     BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_BISTON_DB                                      BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_BISTDONE_DB                                    BIT(6)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_IF_SEL_DB                                      BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DEBUG_EN_DB                                        BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TRIMBG_DB(x)                                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_CSI_2P2L_TEST_DB
// Register Offset : 0x0060
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TESTDIN_DB(x)                                  (((x) & 0xFF) << 11)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TESTDOUT_DB(x)                                 (((x) & 0xFF) << 3)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TESTEN_DB                                      BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TESTCLK_DB                                     BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_DSI_TESTCLR_DB                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_REG_SEL_CFG_0
// Register Offset : 0x0064
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_FORCERXMODE_0_M                        BIT(31)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_FORCERXMODE_1_M                        BIT(30)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_SHUTDOWNZ_M                            BIT(29)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_RSTZ_M                                 BIT(28)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLE_0_M                             BIT(27)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLE_1_M                             BIT(26)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLECLK_M                            BIT(25)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_IF_SEL_M                               BIT(24)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_BISTON_M                               BIT(23)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_PS_PD_S                                BIT(22)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_PS_PD_L                                BIT(21)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_MODE_SEL                               BIT(20)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_RX_RCTL                                BIT(19)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_RESERVED                               BIT(18)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_FORCERXMODE_0_S                        BIT(17)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_FORCERXMODE_1_S                        BIT(16)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_SHUTDOWNZ_S                            BIT(15)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_RSTZ_S                                 BIT(14)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLE_0_S                             BIT(13)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLE_1_S                             BIT(12)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_ENABLECLK_S                            BIT(11)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_IF_SEL_S                               BIT(10)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_CSI_BISTON_S                               BIT(9)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTHSCLK_DB                      BIT(8)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSCLK_DB                           BIT(7)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXITCLK_DB                       BIT(6)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTDATAHS_0_DB                   BIT(5)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTESC_0_DB                      BIT(4)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXLPDTESC_0_DB                         BIT(3)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSESC_0_DB                         BIT(2)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXIT_0_DB                        BIT(1)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXTRIGGERESC_0_DB                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_REG_SEL_CFG_1
// Register Offset : 0x0068
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXVALIDESC_0_DB                        BIT(31)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTDATAHS_1_DB                   BIT(30)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTESC_1_DB                      BIT(29)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXLPDTESC_1_DB                         BIT(28)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSESC_1_DB                         BIT(27)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXIT_1_DB                        BIT(26)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXTRIGGERESC_1_DB                      BIT(25)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXVALIDESC_1_DB                        BIT(24)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTDATAHS_2_DB                   BIT(23)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTESC_2_DB                      BIT(22)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXLPDTESC_2_DB                         BIT(21)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSESC_2_DB                         BIT(20)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXIT_2_DB                        BIT(19)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXTRIGGERESC_2_DB                      BIT(18)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXVALIDESC_2_DB                        BIT(17)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTDATAHS_3_DB                   BIT(16)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXREQUESTESC_3_DB                      BIT(15)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXLPDTESC_3_DB                         BIT(14)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSESC_3_DB                         BIT(13)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXULPSEXIT_3_DB                        BIT(12)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXTRIGGERESC_3_DB                      BIT(11)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXVALIDESC_3_DB                        BIT(10)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXDATAESC_0_DB                         BIT(9)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXDATAESC_1_DB                         BIT(8)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXDATAESC_2_DB                         BIT(7)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TXDATAESC_3_DB                         BIT(6)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNREQUEST_0_DB                       BIT(5)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNDISABLE_0_DB                       BIT(4)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCERXMODE_0_DB                       BIT(3)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCETXSTOPMODE_0_DB                   BIT(2)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNREQUEST_1_DB                       BIT(1)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNDISABLE_1_DB                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANLG_PHY_G5_ANALOG_MIPI_CSI_2P2LANE_REG_SEL_CFG_2
// Register Offset : 0x006C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCERXMODE_1_DB                       BIT(25)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCETXSTOPMODE_1_DB                   BIT(24)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNREQUEST_2_DB                       BIT(23)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNDISABLE_2_DB                       BIT(22)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCERXMODE_2_DB                       BIT(21)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCETXSTOPMODE_2_DB                   BIT(20)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNREQUEST_3_DB                       BIT(19)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TURNDISABLE_3_DB                       BIT(18)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCERXMODE_3_DB                       BIT(17)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCETXSTOPMODE_3_DB                   BIT(16)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_SHUTDOWNZ_DB                           BIT(15)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_RSTZ_DB                                BIT(14)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLE_0_DB                            BIT(13)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLE_1_DB                            BIT(12)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLE_2_DB                            BIT(11)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLE_3_DB                            BIT(10)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_ENABLECLK_DB                           BIT(9)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_FORCEPLL_DB                            BIT(8)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_BISTON_DB                              BIT(7)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_IF_SEL_DB                              BIT(6)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DEBUG_EN_DB                                BIT(5)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TRIMBG_DB                              BIT(4)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TESTDIN_DB                             BIT(3)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TESTEN_DB                              BIT(2)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TESTCLK_DB                             BIT(1)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_MIPI_CSI_2P2LANE_DSI_TESTCLR_DB                             BIT(0)


#endif
