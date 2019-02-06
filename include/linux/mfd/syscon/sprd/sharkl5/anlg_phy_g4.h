/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-05-10 14:14:24
 *
 */


#ifndef ANLG_PHY_G4_H
#define ANLG_PHY_G4_H



#define REG_ANLG_PHY_G4_ANALOG_THM1_1_THM1_CTL               (0x0000)
#define REG_ANLG_PHY_G4_ANALOG_THM1_1_THM1_RESERVED_CTL      (0x0004)
#define REG_ANLG_PHY_G4_ANALOG_THM1_1_REG_SEL_CFG_0          (0x0008)
#define REG_ANLG_PHY_G4_ANALOG_EFUSE4K_EFUSE_PIN_PW_CTL      (0x000C)
#define REG_ANLG_PHY_G4_ANALOG_EFUSE4K_REG_SEL_CFG_0         (0x0010)

/* REG_ANLG_PHY_G4_ANALOG_THM1_1_THM1_CTL */

#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_RSTN              BIT(27)
#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_RUN               BIT(26)
#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_PD                BIT(25)
#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_VALID             BIT(24)
#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_BG_RBIAS_MODE     BIT(23)
#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_TEST_SEL(x)       (((x) & 0x3) << 21)
#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_BP_MODE           BIT(20)
#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_DATA(x)           (((x) & 0x3FF) << 10)
#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_BP_DATA(x)        (((x) & 0x3FF))

/* REG_ANLG_PHY_G4_ANALOG_THM1_1_THM1_RESERVED_CTL */

#define BIT_ANLG_PHY_G4_ANALOG_THM1_1_THM_RESERVED(x)       (((x) & 0xFFFF))

/* REG_ANLG_PHY_G4_ANALOG_THM1_1_REG_SEL_CFG_0 */

#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_THM1_1_THM_RSTN      BIT(3)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_THM1_1_THM_RUN       BIT(2)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_THM1_1_THM_PD        BIT(1)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_THM1_1_THM_RESERVED  BIT(0)

/* REG_ANLG_PHY_G4_ANALOG_EFUSE4K_EFUSE_PIN_PW_CTL */

#define BIT_ANLG_PHY_G4_ANALOG_EFUSE4K_EFS_ENK1             BIT(4)
#define BIT_ANLG_PHY_G4_ANALOG_EFUSE4K_EFS_ENK2             BIT(3)
#define BIT_ANLG_PHY_G4_ANALOG_EFUSE4K_EFS_TRCS             BIT(2)
#define BIT_ANLG_PHY_G4_ANALOG_EFUSE4K_EFS_AT1              BIT(1)
#define BIT_ANLG_PHY_G4_ANALOG_EFUSE4K_EFS_AT0              BIT(0)

/* REG_ANLG_PHY_G4_ANALOG_EFUSE4K_REG_SEL_CFG_0 */

#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_EFUSE4K_EFS_ENK1     BIT(1)
#define BIT_ANLG_PHY_G4_DBG_SEL_ANALOG_EFUSE4K_EFS_ENK2     BIT(0)


#endif /* ANLG_PHY_G4_H */


