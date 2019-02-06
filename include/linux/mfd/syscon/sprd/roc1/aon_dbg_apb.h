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


#ifndef AON_DBG_APB_H
#define AON_DBG_APB_H



#define REG_AON_DBG_APB_APCPU_COMM_CTRL          (0x0000)
#define REG_AON_DBG_APB_APCPU_PROT_CTRL          (0x0004)
#define REG_AON_DBG_APB_CSSYS_CFG                (0x0008)
#define REG_AON_DBG_APB_CR5_PROT_CTRL            (0x000C)
#define REG_AON_DBG_APB_APCPU_PROT_CTRL_NON_SEC  (0x0010)
#define REG_AON_DBG_APB_CSSYS_CFG_NON_SEC        (0x0014)
#define REG_AON_DBG_APB_CR5_PROT_CTRL_NON_SEC    (0x0018)
#define REG_AON_DBG_APB_DEBUG_BOND_OPTION        (0x001C)

/* REG_AON_DBG_APB_APCPU_COMM_CTRL */

#define BIT_AON_DBG_APB_APCPU_AWSTASHLPIDENS   BIT(20)
#define BIT_AON_DBG_APB_APCPU_AWSTASHLPIDS(x)  (((x) & 0xF) << 16)
#define BIT_AON_DBG_APB_APCPU_CFGTE(x)         (((x) & 0xFF) << 8)
#define BIT_AON_DBG_APB_APCPU_AA64NAA32(x)     (((x) & 0xFF))

/* REG_AON_DBG_APB_APCPU_PROT_CTRL */

#define BIT_AON_DBG_APB_APCPU_SPNIDEN          BIT(3)
#define BIT_AON_DBG_APB_APCPU_SPIDEN           BIT(2)
#define BIT_AON_DBG_APB_APCPU_NIDEN            BIT(1)
#define BIT_AON_DBG_APB_APCPU_DBGEN            BIT(0)

/* REG_AON_DBG_APB_CSSYS_CFG */

#define BIT_AON_DBG_APB_DAP_DEVICEEN           BIT(31)
#define BIT_AON_DBG_APB_DAP_DBGEN              BIT(30)
#define BIT_AON_DBG_APB_DAP_SPIDBGEN           BIT(29)
#define BIT_AON_DBG_APB_ESE_DBGEN              BIT(12)
#define BIT_AON_DBG_APB_VDSP_DBGEN             BIT(11)
#define BIT_AON_DBG_APB_GPU_DBGEN              BIT(10)
#define BIT_AON_DBG_APB_TG_JTAG_EN             BIT(9)
#define BIT_AON_DBG_APB_LTE_JTAG_EN            BIT(8)
#define BIT_AON_DBG_APB_AON_CM4_DBGEN          BIT(7)
#define BIT_AON_DBG_APB_DJTAG_EN               BIT(6)
#define BIT_AON_DBG_APB_AG_JTAG_EN             BIT(5)
#define BIT_AON_DBG_APB_MJTAG_EN               BIT(4)
#define BIT_AON_DBG_APB_CSSYS_NIDEN            BIT(3)
#define BIT_AON_DBG_APB_CSSYS_SPNIDEN          BIT(2)
#define BIT_AON_DBG_APB_CSSYS_SPIDEN           BIT(1)
#define BIT_AON_DBG_APB_CSSYS_DBGEN            BIT(0)

/* REG_AON_DBG_APB_CR5_PROT_CTRL */

#define BIT_AON_DBG_APB_CR5_NIDEN              BIT(1)
#define BIT_AON_DBG_APB_CR5_DBGEN              BIT(0)

/* REG_AON_DBG_APB_APCPU_PROT_CTRL_NON_SEC */

#define BIT_AON_DBG_APB_APCPU_SPNIDEN_NON_SEC  BIT(3)
#define BIT_AON_DBG_APB_APCPU_SPIDEN_NON_SEC   BIT(2)
#define BIT_AON_DBG_APB_APCPU_NIDEN_NON_SEC    BIT(1)
#define BIT_AON_DBG_APB_APCPU_DBGEN_NON_SEC    BIT(0)

/* REG_AON_DBG_APB_CSSYS_CFG_NON_SEC */

#define BIT_AON_DBG_APB_DAP_DEVICEEN_NON_SEC   BIT(31)
#define BIT_AON_DBG_APB_DAP_DBGEN_NON_SEC      BIT(30)
#define BIT_AON_DBG_APB_DAP_SPIDBGEN_NON_SEC   BIT(29)
#define BIT_AON_DBG_APB_ESE_DBGEN_NON_SEC      BIT(12)
#define BIT_AON_DBG_APB_VDSP_DBGEN_NON_SEC     BIT(11)
#define BIT_AON_DBG_APB_GPU_DBGEN_NON_SEC      BIT(10)
#define BIT_AON_DBG_APB_TG_JTAG_EN_NON_SEC     BIT(9)
#define BIT_AON_DBG_APB_LTE_JTAG_EN_NON_SEC    BIT(8)
#define BIT_AON_DBG_APB_AON_CM4_DBGEN_NON_SEC  BIT(7)
#define BIT_AON_DBG_APB_DJTAG_EN_NON_SEC       BIT(6)
#define BIT_AON_DBG_APB_AG_JTAG_EN_NON_SEC     BIT(5)
#define BIT_AON_DBG_APB_MJTAG_EN_NON_SEC       BIT(4)
#define BIT_AON_DBG_APB_CSSYS_NIDEN_NON_SEC    BIT(3)
#define BIT_AON_DBG_APB_CSSYS_SPNIDEN_NON_SEC  BIT(2)
#define BIT_AON_DBG_APB_CSSYS_SPIDEN_NON_SEC   BIT(1)
#define BIT_AON_DBG_APB_CSSYS_DBGEN_NON_SEC    BIT(0)

/* REG_AON_DBG_APB_CR5_PROT_CTRL_NON_SEC */

#define BIT_AON_DBG_APB_CR5_NIDEN_NON_SEC      BIT(1)
#define BIT_AON_DBG_APB_CR5_DBGEN_NON_SEC      BIT(0)

/* REG_AON_DBG_APB_DEBUG_BOND_OPTION */

#define BIT_AON_DBG_APB_EFUSE_DEBUG_BOND_OFF   BIT(31)
#define BIT_AON_DBG_APB_EFUSE_SECURE_DEBUG     BIT(30)


#endif /* AON_DBG_APB_H */


