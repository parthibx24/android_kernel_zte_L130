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


#ifndef SLV_FW_AP0_H
#define SLV_FW_AP0_H



#define REG_SLV_FW_AP0_PORT0_DEFAULT_ADDRESS_0  (0x0000)
#define REG_SLV_FW_AP0_PORT0_DEFAULT_ADDRESS_1  (0x0004)
#define REG_SLV_FW_AP0_PORT1_DEFAULT_ADDRESS_0  (0x0008)
#define REG_SLV_FW_AP0_PORT1_DEFAULT_ADDRESS_1  (0x000C)
#define REG_SLV_FW_AP0_PORT_INT_EN              (0x0010)
#define REG_SLV_FW_AP0_PORT_INT_CLR             (0x0014)
#define REG_SLV_FW_AP0_PORT_INT_RAW             (0x0018)
#define REG_SLV_FW_AP0_PORT_INT_FIN             (0x001C)
#define REG_SLV_FW_AP0_RD_SEC_0                 (0x0020)
#define REG_SLV_FW_AP0_RD_SEC_1                 (0x0024)
#define REG_SLV_FW_AP0_RD_SEC_2                 (0x0028)
#define REG_SLV_FW_AP0_RD_SEC_3                 (0x002C)
#define REG_SLV_FW_AP0_WR_SEC_0                 (0x0030)
#define REG_SLV_FW_AP0_WR_SEC_1                 (0x0034)
#define REG_SLV_FW_AP0_WR_SEC_2                 (0x0038)
#define REG_SLV_FW_AP0_WR_SEC_3                 (0x003C)
#define REG_SLV_FW_AP0_ID0_FIRST_ADDR_0         (0x0040)
#define REG_SLV_FW_AP0_ID0_FIRST_ADDR_1         (0x0044)
#define REG_SLV_FW_AP0_ID0_LAST_ADDR_0          (0x0048)
#define REG_SLV_FW_AP0_ID0_LAST_ADDR_1          (0x004C)
#define REG_SLV_FW_AP0_ID0_MSTID_0              (0x0050)
#define REG_SLV_FW_AP0_ID0_MSTID_1              (0x0054)
#define REG_SLV_FW_AP0_ID0_MSTID_2              (0x0058)
#define REG_SLV_FW_AP0_ID0_MSTID_3              (0x005C)
#define REG_SLV_FW_AP0_ID0_MSTID_4              (0x0060)
#define REG_SLV_FW_AP0_ID0_MSTID_5              (0x0064)
#define REG_SLV_FW_AP0_ID0_MSTID_6              (0x0068)
#define REG_SLV_FW_AP0_ID0_MSTID_7              (0x006C)
#define REG_SLV_FW_AP0_ID1_FIRST_ADDR_0         (0x0070)
#define REG_SLV_FW_AP0_ID1_FIRST_ADDR_1         (0x0074)
#define REG_SLV_FW_AP0_ID1_LAST_ADDR_0          (0x0078)
#define REG_SLV_FW_AP0_ID1_LAST_ADDR_1          (0x007C)
#define REG_SLV_FW_AP0_ID1_MSTID_0              (0x0080)
#define REG_SLV_FW_AP0_ID1_MSTID_1              (0x0084)
#define REG_SLV_FW_AP0_ID1_MSTID_2              (0x0088)
#define REG_SLV_FW_AP0_ID1_MSTID_3              (0x008C)
#define REG_SLV_FW_AP0_ID1_MSTID_4              (0x0090)
#define REG_SLV_FW_AP0_ID1_MSTID_5              (0x0094)
#define REG_SLV_FW_AP0_ID1_MSTID_6              (0x0098)
#define REG_SLV_FW_AP0_ID1_MSTID_7              (0x009C)
#define REG_SLV_FW_AP0_ID2_FIRST_ADDR_0         (0x00A0)
#define REG_SLV_FW_AP0_ID2_FIRST_ADDR_1         (0x00A4)
#define REG_SLV_FW_AP0_ID2_LAST_ADDR_0          (0x00A8)
#define REG_SLV_FW_AP0_ID2_LAST_ADDR_1          (0x00AC)
#define REG_SLV_FW_AP0_ID2_MSTID_0              (0x00B0)
#define REG_SLV_FW_AP0_ID2_MSTID_1              (0x00B4)
#define REG_SLV_FW_AP0_ID2_MSTID_2              (0x00B8)
#define REG_SLV_FW_AP0_ID2_MSTID_3              (0x00BC)
#define REG_SLV_FW_AP0_ID2_MSTID_4              (0x00C0)
#define REG_SLV_FW_AP0_ID2_MSTID_5              (0x00C4)
#define REG_SLV_FW_AP0_ID2_MSTID_6              (0x00C8)
#define REG_SLV_FW_AP0_ID2_MSTID_7              (0x00CC)
#define REG_SLV_FW_AP0_ID3_FIRST_ADDR_0         (0x00D0)
#define REG_SLV_FW_AP0_ID3_FIRST_ADDR_1         (0x00D4)
#define REG_SLV_FW_AP0_ID3_LAST_ADDR_0          (0x00D8)
#define REG_SLV_FW_AP0_ID3_LAST_ADDR_1          (0x00DC)
#define REG_SLV_FW_AP0_ID3_MSTID_0              (0x00E0)
#define REG_SLV_FW_AP0_ID3_MSTID_1              (0x00E4)
#define REG_SLV_FW_AP0_ID3_MSTID_2              (0x00E8)
#define REG_SLV_FW_AP0_ID3_MSTID_3              (0x00EC)
#define REG_SLV_FW_AP0_ID3_MSTID_4              (0x00F0)
#define REG_SLV_FW_AP0_ID3_MSTID_5              (0x00F4)
#define REG_SLV_FW_AP0_ID3_MSTID_6              (0x00F8)
#define REG_SLV_FW_AP0_ID3_MSTID_7              (0x00FC)
#define REG_SLV_FW_AP0_ID4_FIRST_ADDR_0         (0x0100)
#define REG_SLV_FW_AP0_ID4_FIRST_ADDR_1         (0x0104)
#define REG_SLV_FW_AP0_ID4_LAST_ADDR_0          (0x0108)
#define REG_SLV_FW_AP0_ID4_LAST_ADDR_1          (0x010C)
#define REG_SLV_FW_AP0_ID4_MSTID_0              (0x0110)
#define REG_SLV_FW_AP0_ID4_MSTID_1              (0x0114)
#define REG_SLV_FW_AP0_ID4_MSTID_2              (0x0118)
#define REG_SLV_FW_AP0_ID4_MSTID_3              (0x011C)
#define REG_SLV_FW_AP0_ID4_MSTID_4              (0x0120)
#define REG_SLV_FW_AP0_ID4_MSTID_5              (0x0124)
#define REG_SLV_FW_AP0_ID4_MSTID_6              (0x0128)
#define REG_SLV_FW_AP0_ID4_MSTID_7              (0x012C)
#define REG_SLV_FW_AP0_ID5_FIRST_ADDR_0         (0x0130)
#define REG_SLV_FW_AP0_ID5_FIRST_ADDR_1         (0x0134)
#define REG_SLV_FW_AP0_ID5_LAST_ADDR_0          (0x0138)
#define REG_SLV_FW_AP0_ID5_LAST_ADDR_1          (0x013C)
#define REG_SLV_FW_AP0_ID5_MSTID_0              (0x0140)
#define REG_SLV_FW_AP0_ID5_MSTID_1              (0x0144)
#define REG_SLV_FW_AP0_ID5_MSTID_2              (0x0148)
#define REG_SLV_FW_AP0_ID5_MSTID_3              (0x014C)
#define REG_SLV_FW_AP0_ID5_MSTID_4              (0x0150)
#define REG_SLV_FW_AP0_ID5_MSTID_5              (0x0154)
#define REG_SLV_FW_AP0_ID5_MSTID_6              (0x0158)
#define REG_SLV_FW_AP0_ID5_MSTID_7              (0x015C)
#define REG_SLV_FW_AP0_ID6_FIRST_ADDR_0         (0x0160)
#define REG_SLV_FW_AP0_ID6_FIRST_ADDR_1         (0x0164)
#define REG_SLV_FW_AP0_ID6_LAST_ADDR_0          (0x0168)
#define REG_SLV_FW_AP0_ID6_LAST_ADDR_1          (0x016C)
#define REG_SLV_FW_AP0_ID6_MSTID_0              (0x0170)
#define REG_SLV_FW_AP0_ID6_MSTID_1              (0x0174)
#define REG_SLV_FW_AP0_ID6_MSTID_2              (0x0178)
#define REG_SLV_FW_AP0_ID6_MSTID_3              (0x017C)
#define REG_SLV_FW_AP0_ID6_MSTID_4              (0x0180)
#define REG_SLV_FW_AP0_ID6_MSTID_5              (0x0184)
#define REG_SLV_FW_AP0_ID6_MSTID_6              (0x0188)
#define REG_SLV_FW_AP0_ID6_MSTID_7              (0x018C)
#define REG_SLV_FW_AP0_ID7_FIRST_ADDR_0         (0x0190)
#define REG_SLV_FW_AP0_ID7_FIRST_ADDR_1         (0x0194)
#define REG_SLV_FW_AP0_ID7_LAST_ADDR_0          (0x0198)
#define REG_SLV_FW_AP0_ID7_LAST_ADDR_1          (0x019C)
#define REG_SLV_FW_AP0_ID7_MSTID_0              (0x01A0)
#define REG_SLV_FW_AP0_ID7_MSTID_1              (0x01A4)
#define REG_SLV_FW_AP0_ID7_MSTID_2              (0x01A8)
#define REG_SLV_FW_AP0_ID7_MSTID_3              (0x01AC)
#define REG_SLV_FW_AP0_ID7_MSTID_4              (0x01B0)
#define REG_SLV_FW_AP0_ID7_MSTID_5              (0x01B4)
#define REG_SLV_FW_AP0_ID7_MSTID_6              (0x01B8)
#define REG_SLV_FW_AP0_ID7_MSTID_7              (0x01BC)
#define REG_SLV_FW_AP0_ID8_FIRST_ADDR_0         (0x01C0)
#define REG_SLV_FW_AP0_ID8_FIRST_ADDR_1         (0x01C4)
#define REG_SLV_FW_AP0_ID8_LAST_ADDR_0          (0x01C8)
#define REG_SLV_FW_AP0_ID8_LAST_ADDR_1          (0x01CC)
#define REG_SLV_FW_AP0_ID8_MSTID_0              (0x01D0)
#define REG_SLV_FW_AP0_ID8_MSTID_1              (0x01D4)
#define REG_SLV_FW_AP0_ID8_MSTID_2              (0x01D8)
#define REG_SLV_FW_AP0_ID8_MSTID_3              (0x01DC)
#define REG_SLV_FW_AP0_ID8_MSTID_4              (0x01E0)
#define REG_SLV_FW_AP0_ID8_MSTID_5              (0x01E4)
#define REG_SLV_FW_AP0_ID8_MSTID_6              (0x01E8)
#define REG_SLV_FW_AP0_ID8_MSTID_7              (0x01EC)
#define REG_SLV_FW_AP0_ID9_FIRST_ADDR_0         (0x01F0)
#define REG_SLV_FW_AP0_ID9_FIRST_ADDR_1         (0x01F4)
#define REG_SLV_FW_AP0_ID9_LAST_ADDR_0          (0x01F8)
#define REG_SLV_FW_AP0_ID9_LAST_ADDR_1          (0x01FC)
#define REG_SLV_FW_AP0_ID9_MSTID_0              (0x0200)
#define REG_SLV_FW_AP0_ID9_MSTID_1              (0x0204)
#define REG_SLV_FW_AP0_ID9_MSTID_2              (0x0208)
#define REG_SLV_FW_AP0_ID9_MSTID_3              (0x020C)
#define REG_SLV_FW_AP0_ID9_MSTID_4              (0x0210)
#define REG_SLV_FW_AP0_ID9_MSTID_5              (0x0214)
#define REG_SLV_FW_AP0_ID9_MSTID_6              (0x0218)
#define REG_SLV_FW_AP0_ID9_MSTID_7              (0x021C)
#define REG_SLV_FW_AP0_ID10_FIRST_ADDR_0        (0x0220)
#define REG_SLV_FW_AP0_ID10_FIRST_ADDR_1        (0x0224)
#define REG_SLV_FW_AP0_ID10_LAST_ADDR_0         (0x0228)
#define REG_SLV_FW_AP0_ID10_LAST_ADDR_1         (0x022C)
#define REG_SLV_FW_AP0_ID10_MSTID_0             (0x0230)
#define REG_SLV_FW_AP0_ID10_MSTID_1             (0x0234)
#define REG_SLV_FW_AP0_ID10_MSTID_2             (0x0238)
#define REG_SLV_FW_AP0_ID10_MSTID_3             (0x023C)
#define REG_SLV_FW_AP0_ID10_MSTID_4             (0x0240)
#define REG_SLV_FW_AP0_ID10_MSTID_5             (0x0244)
#define REG_SLV_FW_AP0_ID10_MSTID_6             (0x0248)
#define REG_SLV_FW_AP0_ID10_MSTID_7             (0x024C)
#define REG_SLV_FW_AP0_ID11_FIRST_ADDR_0        (0x0250)
#define REG_SLV_FW_AP0_ID11_FIRST_ADDR_1        (0x0254)
#define REG_SLV_FW_AP0_ID11_LAST_ADDR_0         (0x0258)
#define REG_SLV_FW_AP0_ID11_LAST_ADDR_1         (0x025C)
#define REG_SLV_FW_AP0_ID11_MSTID_0             (0x0260)
#define REG_SLV_FW_AP0_ID11_MSTID_1             (0x0264)
#define REG_SLV_FW_AP0_ID11_MSTID_2             (0x0268)
#define REG_SLV_FW_AP0_ID11_MSTID_3             (0x026C)
#define REG_SLV_FW_AP0_ID11_MSTID_4             (0x0270)
#define REG_SLV_FW_AP0_ID11_MSTID_5             (0x0274)
#define REG_SLV_FW_AP0_ID11_MSTID_6             (0x0278)
#define REG_SLV_FW_AP0_ID11_MSTID_7             (0x027C)
#define REG_SLV_FW_AP0_ID12_FIRST_ADDR_0        (0x0280)
#define REG_SLV_FW_AP0_ID12_FIRST_ADDR_1        (0x0284)
#define REG_SLV_FW_AP0_ID12_LAST_ADDR_0         (0x0288)
#define REG_SLV_FW_AP0_ID12_LAST_ADDR_1         (0x028C)
#define REG_SLV_FW_AP0_ID12_MSTID_0             (0x0290)
#define REG_SLV_FW_AP0_ID12_MSTID_1             (0x0294)
#define REG_SLV_FW_AP0_ID12_MSTID_2             (0x0298)
#define REG_SLV_FW_AP0_ID12_MSTID_3             (0x029C)
#define REG_SLV_FW_AP0_ID12_MSTID_4             (0x02A0)
#define REG_SLV_FW_AP0_ID12_MSTID_5             (0x02A4)
#define REG_SLV_FW_AP0_ID12_MSTID_6             (0x02A8)
#define REG_SLV_FW_AP0_ID12_MSTID_7             (0x02AC)
#define REG_SLV_FW_AP0_ID13_FIRST_ADDR_0        (0x02B0)
#define REG_SLV_FW_AP0_ID13_FIRST_ADDR_1        (0x02B4)
#define REG_SLV_FW_AP0_ID13_LAST_ADDR_0         (0x02B8)
#define REG_SLV_FW_AP0_ID13_LAST_ADDR_1         (0x02BC)
#define REG_SLV_FW_AP0_ID13_MSTID_0             (0x02C0)
#define REG_SLV_FW_AP0_ID13_MSTID_1             (0x02C4)
#define REG_SLV_FW_AP0_ID13_MSTID_2             (0x02C8)
#define REG_SLV_FW_AP0_ID13_MSTID_3             (0x02CC)
#define REG_SLV_FW_AP0_ID13_MSTID_4             (0x02D0)
#define REG_SLV_FW_AP0_ID13_MSTID_5             (0x02D4)
#define REG_SLV_FW_AP0_ID13_MSTID_6             (0x02D8)
#define REG_SLV_FW_AP0_ID13_MSTID_7             (0x02DC)
#define REG_SLV_FW_AP0_ID14_FIRST_ADDR_0        (0x02E0)
#define REG_SLV_FW_AP0_ID14_FIRST_ADDR_1        (0x02E4)
#define REG_SLV_FW_AP0_ID14_LAST_ADDR_0         (0x02E8)
#define REG_SLV_FW_AP0_ID14_LAST_ADDR_1         (0x02EC)
#define REG_SLV_FW_AP0_ID14_MSTID_0             (0x02F0)
#define REG_SLV_FW_AP0_ID14_MSTID_1             (0x02F4)
#define REG_SLV_FW_AP0_ID14_MSTID_2             (0x02F8)
#define REG_SLV_FW_AP0_ID14_MSTID_3             (0x02FC)
#define REG_SLV_FW_AP0_ID14_MSTID_4             (0x0300)
#define REG_SLV_FW_AP0_ID14_MSTID_5             (0x0304)
#define REG_SLV_FW_AP0_ID14_MSTID_6             (0x0308)
#define REG_SLV_FW_AP0_ID14_MSTID_7             (0x030C)
#define REG_SLV_FW_AP0_ID15_FIRST_ADDR_0        (0x0310)
#define REG_SLV_FW_AP0_ID15_FIRST_ADDR_1        (0x0314)
#define REG_SLV_FW_AP0_ID15_LAST_ADDR_0         (0x0318)
#define REG_SLV_FW_AP0_ID15_LAST_ADDR_1         (0x031C)
#define REG_SLV_FW_AP0_ID15_MSTID_0             (0x0320)
#define REG_SLV_FW_AP0_ID15_MSTID_1             (0x0324)
#define REG_SLV_FW_AP0_ID15_MSTID_2             (0x0328)
#define REG_SLV_FW_AP0_ID15_MSTID_3             (0x032C)
#define REG_SLV_FW_AP0_ID15_MSTID_4             (0x0330)
#define REG_SLV_FW_AP0_ID15_MSTID_5             (0x0334)
#define REG_SLV_FW_AP0_ID15_MSTID_6             (0x0338)
#define REG_SLV_FW_AP0_ID15_MSTID_7             (0x033C)

/* REG_SLV_FW_AP0_PORT0_DEFAULT_ADDRESS_0 */

#define BIT_SLV_FW_AP0_PORT0_DEFAULT_ADDRESS_0_PORT0_DEFAULT_ADDRESS_0(x)  (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_PORT0_DEFAULT_ADDRESS_1 */

#define BIT_SLV_FW_AP0_PORT0_DEFAULT_ADDRESS_1_PORT0_DEFAULT_ADDRESS_1(x)  (((x) & 0x3))

/* REG_SLV_FW_AP0_PORT1_DEFAULT_ADDRESS_0 */

#define BIT_SLV_FW_AP0_PORT1_DEFAULT_ADDRESS_0_PORT1_DEFAULT_ADDRESS_0(x)  (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_PORT1_DEFAULT_ADDRESS_1 */

#define BIT_SLV_FW_AP0_PORT1_DEFAULT_ADDRESS_1_PORT1_DEFAULT_ADDRESS_1(x)  (((x) & 0x3))

/* REG_SLV_FW_AP0_PORT_INT_EN */

#define BIT_SLV_FW_AP0_PORT_INT_EN_PORT_1_R_EN                             BIT(3)
#define BIT_SLV_FW_AP0_PORT_INT_EN_PORT_1_W_EN                             BIT(2)
#define BIT_SLV_FW_AP0_PORT_INT_EN_PORT_0_R_EN                             BIT(1)
#define BIT_SLV_FW_AP0_PORT_INT_EN_PORT_0_W_EN                             BIT(0)

/* REG_SLV_FW_AP0_PORT_INT_CLR */

#define BIT_SLV_FW_AP0_PORT_INT_CLR_PORT_1_R_CLR                           BIT(3)
#define BIT_SLV_FW_AP0_PORT_INT_CLR_PORT_1_W_CLR                           BIT(2)
#define BIT_SLV_FW_AP0_PORT_INT_CLR_PORT_0_R_CLR                           BIT(1)
#define BIT_SLV_FW_AP0_PORT_INT_CLR_PORT_0_W_CLR                           BIT(0)

/* REG_SLV_FW_AP0_PORT_INT_RAW */

#define BIT_SLV_FW_AP0_PORT_INT_RAW_PORT_1_R_RAW                           BIT(3)
#define BIT_SLV_FW_AP0_PORT_INT_RAW_PORT_1_W_RAW                           BIT(2)
#define BIT_SLV_FW_AP0_PORT_INT_RAW_PORT_0_R_RAW                           BIT(1)
#define BIT_SLV_FW_AP0_PORT_INT_RAW_PORT_0_W_RAW                           BIT(0)

/* REG_SLV_FW_AP0_PORT_INT_FIN */

#define BIT_SLV_FW_AP0_PORT_INT_FIN_PORT_1_R_FIN                           BIT(3)
#define BIT_SLV_FW_AP0_PORT_INT_FIN_PORT_1_W_FIN                           BIT(2)
#define BIT_SLV_FW_AP0_PORT_INT_FIN_PORT_0_R_FIN                           BIT(1)
#define BIT_SLV_FW_AP0_PORT_INT_FIN_PORT_0_W_FIN                           BIT(0)

/* REG_SLV_FW_AP0_RD_SEC_0 */

#define BIT_SLV_FW_AP0_RD_SEC_0_SDIO1_REG_RD_SEC(x)                        (((x) & 0x3) << 30)
#define BIT_SLV_FW_AP0_RD_SEC_0_SDIO2_REG_RD_SEC(x)                        (((x) & 0x3) << 28)
#define BIT_SLV_FW_AP0_RD_SEC_0_EMMC_REG_RD_SEC(x)                         (((x) & 0x3) << 26)
#define BIT_SLV_FW_AP0_RD_SEC_0_PUB_CE_REG_RD_SEC(x)                       (((x) & 0x3) << 24)
#define BIT_SLV_FW_AP0_RD_SEC_0_SEC_CE_REG_RD_SEC(x)                       (((x) & 0x3) << 22)
#define BIT_SLV_FW_AP0_RD_SEC_0_AP_DVFS_REG_RD_SEC(x)                      (((x) & 0x3) << 20)
#define BIT_SLV_FW_AP0_RD_SEC_0_VDSP_REG_RD_SEC(x)                         (((x) & 0x3) << 18)
#define BIT_SLV_FW_AP0_RD_SEC_0_UFS_UNIPRO_REG_RD_SEC(x)                   (((x) & 0x3) << 16)
#define BIT_SLV_FW_AP0_RD_SEC_0_UFS_HCI_REG_RD_SEC(x)                      (((x) & 0x3) << 14)
#define BIT_SLV_FW_AP0_RD_SEC_0_UFS_UTP_REG_RD_SEC(x)                      (((x) & 0x3) << 12)
#define BIT_SLV_FW_AP0_RD_SEC_0_AI_IMG_REG_RD_SEC(x)                       (((x) & 0x3) << 10)
#define BIT_SLV_FW_AP0_RD_SEC_0_AI_CAM_REG_RD_SEC(x)                       (((x) & 0x3) << 8)
#define BIT_SLV_FW_AP0_RD_SEC_0_AI_SYS_REG_RD_SEC(x)                       (((x) & 0x3) << 6)
#define BIT_SLV_FW_AP0_RD_SEC_0_AI_CLK_REG_RD_SEC(x)                       (((x) & 0x3) << 4)
#define BIT_SLV_FW_AP0_RD_SEC_0_AI_MMU_REG_RD_SEC(x)                       (((x) & 0x3) << 2)
#define BIT_SLV_FW_AP0_RD_SEC_0_AI_DVFS_REG_RD_SEC(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_RD_SEC_1 */

#define BIT_SLV_FW_AP0_RD_SEC_1_UART2_REG_RD_SEC(x)                        (((x) & 0x3) << 30)
#define BIT_SLV_FW_AP0_RD_SEC_1_I2C0_REG_RD_SEC(x)                         (((x) & 0x3) << 28)
#define BIT_SLV_FW_AP0_RD_SEC_1_I2C1_REG_RD_SEC(x)                         (((x) & 0x3) << 26)
#define BIT_SLV_FW_AP0_RD_SEC_1_I2C2_REG_RD_SEC(x)                         (((x) & 0x3) << 24)
#define BIT_SLV_FW_AP0_RD_SEC_1_I2C3_REG_RD_SEC(x)                         (((x) & 0x3) << 22)
#define BIT_SLV_FW_AP0_RD_SEC_1_I2C4_REG_RD_SEC(x)                         (((x) & 0x3) << 20)
#define BIT_SLV_FW_AP0_RD_SEC_1_SPI0_REG_RD_SEC(x)                         (((x) & 0x3) << 18)
#define BIT_SLV_FW_AP0_RD_SEC_1_SPI1_REG_RD_SEC(x)                         (((x) & 0x3) << 16)
#define BIT_SLV_FW_AP0_RD_SEC_1_SPI2_REG_RD_SEC(x)                         (((x) & 0x3) << 14)
#define BIT_SLV_FW_AP0_RD_SEC_1_SPI3_REG_RD_SEC(x)                         (((x) & 0x3) << 12)
#define BIT_SLV_FW_AP0_RD_SEC_1_IIS0_REG_RD_SEC(x)                         (((x) & 0x3) << 10)
#define BIT_SLV_FW_AP0_RD_SEC_1_IIS1_REG_RD_SEC(x)                         (((x) & 0x3) << 8)
#define BIT_SLV_FW_AP0_RD_SEC_1_IIS2_REG_RD_SEC(x)                         (((x) & 0x3) << 6)
#define BIT_SLV_FW_AP0_RD_SEC_1_SIM0_REG_RD_SEC(x)                         (((x) & 0x3) << 4)
#define BIT_SLV_FW_AP0_RD_SEC_1_AP_APB_REG_RD_SEC(x)                       (((x) & 0x3) << 2)
#define BIT_SLV_FW_AP0_RD_SEC_1_SDIO0_REG_RD_SEC(x)                        (((x) & 0x3))

/* REG_SLV_FW_AP0_RD_SEC_2 */

#define BIT_SLV_FW_AP0_RD_SEC_2_GPU_CTRL_REG_RD_SEC(x)                     (((x) & 0x3) << 30)
#define BIT_SLV_FW_AP0_RD_SEC_2_GPU_APB_REG_RD_SEC(x)                      (((x) & 0x3) << 28)
#define BIT_SLV_FW_AP0_RD_SEC_2_GPU_DVFS_REG_RD_SEC(x)                     (((x) & 0x3) << 26)
#define BIT_SLV_FW_AP0_RD_SEC_2_ISP_REG_RD_SEC(x)                          (((x) & 0x3) << 24)
#define BIT_SLV_FW_AP0_RD_SEC_2_MM_CKG_REG_RD_SEC(x)                       (((x) & 0x3) << 22)
#define BIT_SLV_FW_AP0_RD_SEC_2_MM_AHB_REG_RD_SEC(x)                       (((x) & 0x3) << 20)
#define BIT_SLV_FW_AP0_RD_SEC_2_CSI0_REG_RD_SEC(x)                         (((x) & 0x3) << 18)
#define BIT_SLV_FW_AP0_RD_SEC_2_CSI1_REG_RD_SEC(x)                         (((x) & 0x3) << 16)
#define BIT_SLV_FW_AP0_RD_SEC_2_CSI2_REG_RD_SEC(x)                         (((x) & 0x3) << 14)
#define BIT_SLV_FW_AP0_RD_SEC_2_MM_DVFS_REG_RD_SEC(x)                      (((x) & 0x3) << 12)
#define BIT_SLV_FW_AP0_RD_SEC_2_JPG_REG_RD_SEC(x)                          (((x) & 0x3) << 10)
#define BIT_SLV_FW_AP0_RD_SEC_2_CPP_REG_RD_SEC(x)                          (((x) & 0x3) << 8)
#define BIT_SLV_FW_AP0_RD_SEC_2_DCAM_REG_RD_SEC(x)                         (((x) & 0x3) << 6)
#define BIT_SLV_FW_AP0_RD_SEC_2_FD_REG_RD_SEC(x)                           (((x) & 0x3) << 4)
#define BIT_SLV_FW_AP0_RD_SEC_2_UART0_REG_RD_SEC(x)                        (((x) & 0x3) << 2)
#define BIT_SLV_FW_AP0_RD_SEC_2_UART1_REG_RD_SEC(x)                        (((x) & 0x3))

/* REG_SLV_FW_AP0_RD_SEC_3 */

#define BIT_SLV_FW_AP0_RD_SEC_3_DMA_CONTROL_REGISTER_RD_SEC(x)             (((x) & 0x3) << 18)
#define BIT_SLV_FW_AP0_RD_SEC_3_AHB_CONTROL_REGISTER_RD_SEC(x)             (((x) & 0x3) << 16)
#define BIT_SLV_FW_AP0_RD_SEC_3_AP_CKG_REG_RD_SEC(x)                       (((x) & 0x3) << 14)
#define BIT_SLV_FW_AP0_RD_SEC_3_DPU_REG_RD_SEC(x)                          (((x) & 0x3) << 12)
#define BIT_SLV_FW_AP0_RD_SEC_3_DSI_REG_RD_SEC(x)                          (((x) & 0x3) << 10)
#define BIT_SLV_FW_AP0_RD_SEC_3_VSP_REG_RD_SEC(x)                          (((x) & 0x3) << 8)
#define BIT_SLV_FW_AP0_RD_SEC_3_VDSP_MMU0_REG_RD_SEC(x)                    (((x) & 0x3) << 6)
#define BIT_SLV_FW_AP0_RD_SEC_3_VDSP_MMU1_REG_RD_SEC(x)                    (((x) & 0x3) << 4)
#define BIT_SLV_FW_AP0_RD_SEC_3_ICU_REG_RD_SEC(x)                          (((x) & 0x3) << 2)
#define BIT_SLV_FW_AP0_RD_SEC_3_VDMA_REG_RD_SEC(x)                         (((x) & 0x3))

/* REG_SLV_FW_AP0_WR_SEC_0 */

#define BIT_SLV_FW_AP0_WR_SEC_0_SDIO1_REG_WR_SEC(x)                        (((x) & 0x3) << 30)
#define BIT_SLV_FW_AP0_WR_SEC_0_SDIO2_REG_WR_SEC(x)                        (((x) & 0x3) << 28)
#define BIT_SLV_FW_AP0_WR_SEC_0_EMMC_REG_WR_SEC(x)                         (((x) & 0x3) << 26)
#define BIT_SLV_FW_AP0_WR_SEC_0_PUB_CE_REG_WR_SEC(x)                       (((x) & 0x3) << 24)
#define BIT_SLV_FW_AP0_WR_SEC_0_SEC_CE_REG_WR_SEC(x)                       (((x) & 0x3) << 22)
#define BIT_SLV_FW_AP0_WR_SEC_0_AP_DVFS_REG_WR_SEC(x)                      (((x) & 0x3) << 20)
#define BIT_SLV_FW_AP0_WR_SEC_0_VDSP_REG_WR_SEC(x)                         (((x) & 0x3) << 18)
#define BIT_SLV_FW_AP0_WR_SEC_0_UFS_UNIPRO_REG_WR_SEC(x)                   (((x) & 0x3) << 16)
#define BIT_SLV_FW_AP0_WR_SEC_0_UFS_HCI_REG_WR_SEC(x)                      (((x) & 0x3) << 14)
#define BIT_SLV_FW_AP0_WR_SEC_0_UFS_UTP_REG_WR_SEC(x)                      (((x) & 0x3) << 12)
#define BIT_SLV_FW_AP0_WR_SEC_0_AI_IMG_REG_WR_SEC(x)                       (((x) & 0x3) << 10)
#define BIT_SLV_FW_AP0_WR_SEC_0_AI_CAM_REG_WR_SEC(x)                       (((x) & 0x3) << 8)
#define BIT_SLV_FW_AP0_WR_SEC_0_AI_SYS_REG_WR_SEC(x)                       (((x) & 0x3) << 6)
#define BIT_SLV_FW_AP0_WR_SEC_0_AI_CLK_REG_WR_SEC(x)                       (((x) & 0x3) << 4)
#define BIT_SLV_FW_AP0_WR_SEC_0_AI_MMU_REG_WR_SEC(x)                       (((x) & 0x3) << 2)
#define BIT_SLV_FW_AP0_WR_SEC_0_AI_DVFS_REG_WR_SEC(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_WR_SEC_1 */

#define BIT_SLV_FW_AP0_WR_SEC_1_UART2_REG_WR_SEC(x)                        (((x) & 0x3) << 30)
#define BIT_SLV_FW_AP0_WR_SEC_1_I2C0_REG_WR_SEC(x)                         (((x) & 0x3) << 28)
#define BIT_SLV_FW_AP0_WR_SEC_1_I2C1_REG_WR_SEC(x)                         (((x) & 0x3) << 26)
#define BIT_SLV_FW_AP0_WR_SEC_1_I2C2_REG_WR_SEC(x)                         (((x) & 0x3) << 24)
#define BIT_SLV_FW_AP0_WR_SEC_1_I2C3_REG_WR_SEC(x)                         (((x) & 0x3) << 22)
#define BIT_SLV_FW_AP0_WR_SEC_1_I2C4_REG_WR_SEC(x)                         (((x) & 0x3) << 20)
#define BIT_SLV_FW_AP0_WR_SEC_1_SPI0_REG_WR_SEC(x)                         (((x) & 0x3) << 18)
#define BIT_SLV_FW_AP0_WR_SEC_1_SPI1_REG_WR_SEC(x)                         (((x) & 0x3) << 16)
#define BIT_SLV_FW_AP0_WR_SEC_1_SPI2_REG_WR_SEC(x)                         (((x) & 0x3) << 14)
#define BIT_SLV_FW_AP0_WR_SEC_1_SPI3_REG_WR_SEC(x)                         (((x) & 0x3) << 12)
#define BIT_SLV_FW_AP0_WR_SEC_1_IIS0_REG_WR_SEC(x)                         (((x) & 0x3) << 10)
#define BIT_SLV_FW_AP0_WR_SEC_1_IIS1_REG_WR_SEC(x)                         (((x) & 0x3) << 8)
#define BIT_SLV_FW_AP0_WR_SEC_1_IIS2_REG_WR_SEC(x)                         (((x) & 0x3) << 6)
#define BIT_SLV_FW_AP0_WR_SEC_1_SIM0_REG_WR_SEC(x)                         (((x) & 0x3) << 4)
#define BIT_SLV_FW_AP0_WR_SEC_1_AP_APB_REG_WR_SEC(x)                       (((x) & 0x3) << 2)
#define BIT_SLV_FW_AP0_WR_SEC_1_SDIO0_REG_WR_SEC(x)                        (((x) & 0x3))

/* REG_SLV_FW_AP0_WR_SEC_2 */

#define BIT_SLV_FW_AP0_WR_SEC_2_GPU_CTRL_REG_WR_SEC(x)                     (((x) & 0x3) << 30)
#define BIT_SLV_FW_AP0_WR_SEC_2_GPU_APB_REG_WR_SEC(x)                      (((x) & 0x3) << 28)
#define BIT_SLV_FW_AP0_WR_SEC_2_GPU_DVFS_REG_WR_SEC(x)                     (((x) & 0x3) << 26)
#define BIT_SLV_FW_AP0_WR_SEC_2_ISP_REG_WR_SEC(x)                          (((x) & 0x3) << 24)
#define BIT_SLV_FW_AP0_WR_SEC_2_MM_CKG_REG_WR_SEC(x)                       (((x) & 0x3) << 22)
#define BIT_SLV_FW_AP0_WR_SEC_2_MM_AHB_REG_WR_SEC(x)                       (((x) & 0x3) << 20)
#define BIT_SLV_FW_AP0_WR_SEC_2_CSI0_REG_WR_SEC(x)                         (((x) & 0x3) << 18)
#define BIT_SLV_FW_AP0_WR_SEC_2_CSI1_REG_WR_SEC(x)                         (((x) & 0x3) << 16)
#define BIT_SLV_FW_AP0_WR_SEC_2_CSI2_REG_WR_SEC(x)                         (((x) & 0x3) << 14)
#define BIT_SLV_FW_AP0_WR_SEC_2_MM_DVFS_REG_WR_SEC(x)                      (((x) & 0x3) << 12)
#define BIT_SLV_FW_AP0_WR_SEC_2_JPG_REG_WR_SEC(x)                          (((x) & 0x3) << 10)
#define BIT_SLV_FW_AP0_WR_SEC_2_CPP_REG_WR_SEC(x)                          (((x) & 0x3) << 8)
#define BIT_SLV_FW_AP0_WR_SEC_2_DCAM_REG_WR_SEC(x)                         (((x) & 0x3) << 6)
#define BIT_SLV_FW_AP0_WR_SEC_2_FD_REG_WR_SEC(x)                           (((x) & 0x3) << 4)
#define BIT_SLV_FW_AP0_WR_SEC_2_UART0_REG_WR_SEC(x)                        (((x) & 0x3) << 2)
#define BIT_SLV_FW_AP0_WR_SEC_2_UART1_REG_WR_SEC(x)                        (((x) & 0x3))

/* REG_SLV_FW_AP0_WR_SEC_3 */

#define BIT_SLV_FW_AP0_WR_SEC_3_DMA_CONTROL_REGISTER_WR_SEC(x)             (((x) & 0x3) << 18)
#define BIT_SLV_FW_AP0_WR_SEC_3_AHB_CONTROL_REGISTER_WR_SEC(x)             (((x) & 0x3) << 16)
#define BIT_SLV_FW_AP0_WR_SEC_3_AP_CKG_REG_WR_SEC(x)                       (((x) & 0x3) << 14)
#define BIT_SLV_FW_AP0_WR_SEC_3_DPU_REG_WR_SEC(x)                          (((x) & 0x3) << 12)
#define BIT_SLV_FW_AP0_WR_SEC_3_DSI_REG_WR_SEC(x)                          (((x) & 0x3) << 10)
#define BIT_SLV_FW_AP0_WR_SEC_3_VSP_REG_WR_SEC(x)                          (((x) & 0x3) << 8)
#define BIT_SLV_FW_AP0_WR_SEC_3_VDSP_MMU0_REG_WR_SEC(x)                    (((x) & 0x3) << 6)
#define BIT_SLV_FW_AP0_WR_SEC_3_VDSP_MMU1_REG_WR_SEC(x)                    (((x) & 0x3) << 4)
#define BIT_SLV_FW_AP0_WR_SEC_3_ICU_REG_WR_SEC(x)                          (((x) & 0x3) << 2)
#define BIT_SLV_FW_AP0_WR_SEC_3_VDMA_REG_WR_SEC(x)                         (((x) & 0x3))

/* REG_SLV_FW_AP0_ID0_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID0_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID0_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID0_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID0_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID0_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID0_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID0_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID0_MSTID_0 */

#define BIT_SLV_FW_AP0_ID0_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID0_MSTID_1 */

#define BIT_SLV_FW_AP0_ID0_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID0_MSTID_2 */

#define BIT_SLV_FW_AP0_ID0_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID0_MSTID_3 */

#define BIT_SLV_FW_AP0_ID0_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID0_MSTID_4 */

#define BIT_SLV_FW_AP0_ID0_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID0_MSTID_5 */

#define BIT_SLV_FW_AP0_ID0_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID0_MSTID_6 */

#define BIT_SLV_FW_AP0_ID0_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID0_MSTID_7 */

#define BIT_SLV_FW_AP0_ID0_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID1_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID1_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID1_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID1_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID1_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID1_MSTID_0 */

#define BIT_SLV_FW_AP0_ID1_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_MSTID_1 */

#define BIT_SLV_FW_AP0_ID1_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_MSTID_2 */

#define BIT_SLV_FW_AP0_ID1_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_MSTID_3 */

#define BIT_SLV_FW_AP0_ID1_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_MSTID_4 */

#define BIT_SLV_FW_AP0_ID1_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_MSTID_5 */

#define BIT_SLV_FW_AP0_ID1_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_MSTID_6 */

#define BIT_SLV_FW_AP0_ID1_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID1_MSTID_7 */

#define BIT_SLV_FW_AP0_ID1_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID2_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID2_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID2_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID2_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID2_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID2_MSTID_0 */

#define BIT_SLV_FW_AP0_ID2_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_MSTID_1 */

#define BIT_SLV_FW_AP0_ID2_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_MSTID_2 */

#define BIT_SLV_FW_AP0_ID2_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_MSTID_3 */

#define BIT_SLV_FW_AP0_ID2_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_MSTID_4 */

#define BIT_SLV_FW_AP0_ID2_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_MSTID_5 */

#define BIT_SLV_FW_AP0_ID2_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_MSTID_6 */

#define BIT_SLV_FW_AP0_ID2_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID2_MSTID_7 */

#define BIT_SLV_FW_AP0_ID2_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID3_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID3_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID3_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID3_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID3_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID3_MSTID_0 */

#define BIT_SLV_FW_AP0_ID3_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_MSTID_1 */

#define BIT_SLV_FW_AP0_ID3_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_MSTID_2 */

#define BIT_SLV_FW_AP0_ID3_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_MSTID_3 */

#define BIT_SLV_FW_AP0_ID3_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_MSTID_4 */

#define BIT_SLV_FW_AP0_ID3_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_MSTID_5 */

#define BIT_SLV_FW_AP0_ID3_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_MSTID_6 */

#define BIT_SLV_FW_AP0_ID3_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID3_MSTID_7 */

#define BIT_SLV_FW_AP0_ID3_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID4_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID4_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID4_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID4_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID4_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID4_MSTID_0 */

#define BIT_SLV_FW_AP0_ID4_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_MSTID_1 */

#define BIT_SLV_FW_AP0_ID4_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_MSTID_2 */

#define BIT_SLV_FW_AP0_ID4_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_MSTID_3 */

#define BIT_SLV_FW_AP0_ID4_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_MSTID_4 */

#define BIT_SLV_FW_AP0_ID4_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_MSTID_5 */

#define BIT_SLV_FW_AP0_ID4_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_MSTID_6 */

#define BIT_SLV_FW_AP0_ID4_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID4_MSTID_7 */

#define BIT_SLV_FW_AP0_ID4_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID5_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID5_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID5_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID5_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID5_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID5_MSTID_0 */

#define BIT_SLV_FW_AP0_ID5_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_MSTID_1 */

#define BIT_SLV_FW_AP0_ID5_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_MSTID_2 */

#define BIT_SLV_FW_AP0_ID5_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_MSTID_3 */

#define BIT_SLV_FW_AP0_ID5_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_MSTID_4 */

#define BIT_SLV_FW_AP0_ID5_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_MSTID_5 */

#define BIT_SLV_FW_AP0_ID5_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_MSTID_6 */

#define BIT_SLV_FW_AP0_ID5_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID5_MSTID_7 */

#define BIT_SLV_FW_AP0_ID5_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID6_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID6_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID6_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID6_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID6_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID6_MSTID_0 */

#define BIT_SLV_FW_AP0_ID6_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_MSTID_1 */

#define BIT_SLV_FW_AP0_ID6_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_MSTID_2 */

#define BIT_SLV_FW_AP0_ID6_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_MSTID_3 */

#define BIT_SLV_FW_AP0_ID6_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_MSTID_4 */

#define BIT_SLV_FW_AP0_ID6_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_MSTID_5 */

#define BIT_SLV_FW_AP0_ID6_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_MSTID_6 */

#define BIT_SLV_FW_AP0_ID6_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID6_MSTID_7 */

#define BIT_SLV_FW_AP0_ID6_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID7_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID7_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID7_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID7_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID7_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID7_MSTID_0 */

#define BIT_SLV_FW_AP0_ID7_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_MSTID_1 */

#define BIT_SLV_FW_AP0_ID7_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_MSTID_2 */

#define BIT_SLV_FW_AP0_ID7_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_MSTID_3 */

#define BIT_SLV_FW_AP0_ID7_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_MSTID_4 */

#define BIT_SLV_FW_AP0_ID7_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_MSTID_5 */

#define BIT_SLV_FW_AP0_ID7_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_MSTID_6 */

#define BIT_SLV_FW_AP0_ID7_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID7_MSTID_7 */

#define BIT_SLV_FW_AP0_ID7_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID8_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID8_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID8_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID8_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID8_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID8_MSTID_0 */

#define BIT_SLV_FW_AP0_ID8_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_MSTID_1 */

#define BIT_SLV_FW_AP0_ID8_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_MSTID_2 */

#define BIT_SLV_FW_AP0_ID8_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_MSTID_3 */

#define BIT_SLV_FW_AP0_ID8_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_MSTID_4 */

#define BIT_SLV_FW_AP0_ID8_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_MSTID_5 */

#define BIT_SLV_FW_AP0_ID8_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_MSTID_6 */

#define BIT_SLV_FW_AP0_ID8_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID8_MSTID_7 */

#define BIT_SLV_FW_AP0_ID8_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID9_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID9_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_AP0_ID9_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID9_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID9_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_AP0_ID9_MSTID_0 */

#define BIT_SLV_FW_AP0_ID9_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_MSTID_1 */

#define BIT_SLV_FW_AP0_ID9_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_MSTID_2 */

#define BIT_SLV_FW_AP0_ID9_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_MSTID_3 */

#define BIT_SLV_FW_AP0_ID9_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_MSTID_4 */

#define BIT_SLV_FW_AP0_ID9_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_MSTID_5 */

#define BIT_SLV_FW_AP0_ID9_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_MSTID_6 */

#define BIT_SLV_FW_AP0_ID9_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID9_MSTID_7 */

#define BIT_SLV_FW_AP0_ID9_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID10_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID10_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_AP0_ID10_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID10_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID10_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_AP0_ID10_MSTID_0 */

#define BIT_SLV_FW_AP0_ID10_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_MSTID_1 */

#define BIT_SLV_FW_AP0_ID10_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_MSTID_2 */

#define BIT_SLV_FW_AP0_ID10_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_MSTID_3 */

#define BIT_SLV_FW_AP0_ID10_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_MSTID_4 */

#define BIT_SLV_FW_AP0_ID10_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_MSTID_5 */

#define BIT_SLV_FW_AP0_ID10_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_MSTID_6 */

#define BIT_SLV_FW_AP0_ID10_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID10_MSTID_7 */

#define BIT_SLV_FW_AP0_ID10_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID11_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID11_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_AP0_ID11_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID11_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID11_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_AP0_ID11_MSTID_0 */

#define BIT_SLV_FW_AP0_ID11_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_MSTID_1 */

#define BIT_SLV_FW_AP0_ID11_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_MSTID_2 */

#define BIT_SLV_FW_AP0_ID11_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_MSTID_3 */

#define BIT_SLV_FW_AP0_ID11_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_MSTID_4 */

#define BIT_SLV_FW_AP0_ID11_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_MSTID_5 */

#define BIT_SLV_FW_AP0_ID11_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_MSTID_6 */

#define BIT_SLV_FW_AP0_ID11_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID11_MSTID_7 */

#define BIT_SLV_FW_AP0_ID11_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID12_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID12_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_AP0_ID12_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID12_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID12_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_AP0_ID12_MSTID_0 */

#define BIT_SLV_FW_AP0_ID12_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_MSTID_1 */

#define BIT_SLV_FW_AP0_ID12_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_MSTID_2 */

#define BIT_SLV_FW_AP0_ID12_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_MSTID_3 */

#define BIT_SLV_FW_AP0_ID12_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_MSTID_4 */

#define BIT_SLV_FW_AP0_ID12_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_MSTID_5 */

#define BIT_SLV_FW_AP0_ID12_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_MSTID_6 */

#define BIT_SLV_FW_AP0_ID12_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID12_MSTID_7 */

#define BIT_SLV_FW_AP0_ID12_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID13_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID13_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_AP0_ID13_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID13_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID13_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_AP0_ID13_MSTID_0 */

#define BIT_SLV_FW_AP0_ID13_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_MSTID_1 */

#define BIT_SLV_FW_AP0_ID13_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_MSTID_2 */

#define BIT_SLV_FW_AP0_ID13_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_MSTID_3 */

#define BIT_SLV_FW_AP0_ID13_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_MSTID_4 */

#define BIT_SLV_FW_AP0_ID13_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_MSTID_5 */

#define BIT_SLV_FW_AP0_ID13_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_MSTID_6 */

#define BIT_SLV_FW_AP0_ID13_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID13_MSTID_7 */

#define BIT_SLV_FW_AP0_ID13_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID14_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID14_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_AP0_ID14_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID14_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID14_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_AP0_ID14_MSTID_0 */

#define BIT_SLV_FW_AP0_ID14_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_MSTID_1 */

#define BIT_SLV_FW_AP0_ID14_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_MSTID_2 */

#define BIT_SLV_FW_AP0_ID14_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_MSTID_3 */

#define BIT_SLV_FW_AP0_ID14_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_MSTID_4 */

#define BIT_SLV_FW_AP0_ID14_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_MSTID_5 */

#define BIT_SLV_FW_AP0_ID14_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_MSTID_6 */

#define BIT_SLV_FW_AP0_ID14_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID14_MSTID_7 */

#define BIT_SLV_FW_AP0_ID14_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_FIRST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID15_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_FIRST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID15_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_AP0_ID15_LAST_ADDR_0 */

#define BIT_SLV_FW_AP0_ID15_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_LAST_ADDR_1 */

#define BIT_SLV_FW_AP0_ID15_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_AP0_ID15_MSTID_0 */

#define BIT_SLV_FW_AP0_ID15_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_MSTID_1 */

#define BIT_SLV_FW_AP0_ID15_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_MSTID_2 */

#define BIT_SLV_FW_AP0_ID15_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_MSTID_3 */

#define BIT_SLV_FW_AP0_ID15_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_MSTID_4 */

#define BIT_SLV_FW_AP0_ID15_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_MSTID_5 */

#define BIT_SLV_FW_AP0_ID15_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_MSTID_6 */

#define BIT_SLV_FW_AP0_ID15_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_AP0_ID15_MSTID_7 */

#define BIT_SLV_FW_AP0_ID15_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))


#endif /* SLV_FW_AP0_H */


