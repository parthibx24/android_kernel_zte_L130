/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-06-28 19:05:47
 *
 */


#ifndef ANLG_PHY_G15_H
#define ANLG_PHY_G15_H



#define REG_ANLG_PHY_G15_ANALOG_THM1_0_THM1_CTL            (0x0000)
#define REG_ANLG_PHY_G15_ANALOG_THM1_0_THM1_RESERVED_CTL   (0x0004)
#define REG_ANLG_PHY_G15_ANALOG_THM1_0_WRAP_GLUE_CTRL      (0x0008)

/* REG_ANLG_PHY_G15_ANALOG_THM1_0_THM1_CTL */

#define BIT_ANLG_PHY_G15_ANALOG_THM1_0_THM_BG_RBIAS_MODE                        BIT(13)
#define BIT_ANLG_PHY_G15_ANALOG_THM1_0_THM_TEST_SEL(x)                          (((x) & 0x3) << 11)
#define BIT_ANLG_PHY_G15_ANALOG_THM1_0_THM_BP_MODE                              BIT(10)
#define BIT_ANLG_PHY_G15_ANALOG_THM1_0_THM_BP_DATA(x)                           (((x) & 0x3FF))

/* REG_ANLG_PHY_G15_ANALOG_THM1_0_THM1_RESERVED_CTL */

#define BIT_ANLG_PHY_G15_ANALOG_THM1_0_THM_RESERVED(x)                          (((x) & 0xFFFF))

/* REG_ANLG_PHY_G15_ANALOG_THM1_0_WRAP_GLUE_CTRL */

#define BIT_ANLG_PHY_G15_ANALOG_THM1_0_DGB_SEL_THM_RESERVED_BIT0_CONVERT_CYCLE  BIT(1)
#define BIT_ANLG_PHY_G15_ANALOG_THM1_0_DGB_SEL_THM_RESERVED_BIT3_SENSOR_SEL     BIT(0)


#endif /* ANLG_PHY_G15_H */


