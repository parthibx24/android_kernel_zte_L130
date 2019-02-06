/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-05-10 14:14:25
 *
 */


#ifndef PUB_AHB_H
#define PUB_AHB_H



#define REG_PUB_AHB_DMC_EXT_LPCTRL_CFG        (0x3000)
#define REG_PUB_AHB_DMC_EXT_LPCTRL_SEQL       (0x3004)
#define REG_PUB_AHB_DMC_EXT_LPCTRL_SEQH       (0x3008)
#define REG_PUB_AHB_DMC_EXT_LPCTRL_STEP       (0x300C)
#define REG_PUB_AHB_MPU_DUMP_ADDR             (0x3010)
#define REG_PUB_AHB_DMC_MPU_VIO_ADDR          (0x3014)
#define REG_PUB_AHB_DMC_MPU_VIO_CMD           (0x3018)
#define REG_PUB_AHB_DMC_MPU_BASE_CFG          (0x301C)
#define REG_PUB_AHB_MPU_CFG0                  (0x3020)
#define REG_PUB_AHB_MPU_CFG0_ID_MASK_VAL      (0x3024)
#define REG_PUB_AHB_MPU_CFG0_LOW_RANGE        (0x3028)
#define REG_PUB_AHB_MPU_CFG0_HIGH_RANGE       (0x302C)
#define REG_PUB_AHB_MPU_CFG1                  (0x3030)
#define REG_PUB_AHB_MPU_CFG1_ID_MASK_VAL      (0x3034)
#define REG_PUB_AHB_MPU_CFG1_LOW_RANGE        (0x3038)
#define REG_PUB_AHB_MPU_CFG1_HIGH_RANGE       (0x303C)
#define REG_PUB_AHB_MPU_CFG2                  (0x3040)
#define REG_PUB_AHB_MPU_CFG2_ID_MASK_VAL      (0x3044)
#define REG_PUB_AHB_MPU_CFG2_LOW_RANGE        (0x3048)
#define REG_PUB_AHB_MPU_CFG2_HIGH_RANGE       (0x304C)
#define REG_PUB_AHB_MPU_CFG3                  (0x3050)
#define REG_PUB_AHB_MPU_CFG3_ID_MASK_VAL      (0x3054)
#define REG_PUB_AHB_MPU_CFG3_LOW_RANGE        (0x3058)
#define REG_PUB_AHB_MPU_CFG3_HIGH_RANGE       (0x305C)
#define REG_PUB_AHB_MPU_CFG4                  (0x3060)
#define REG_PUB_AHB_MPU_CFG4_ID_MASK_VAL      (0x3064)
#define REG_PUB_AHB_MPU_CFG4_LOW_RANGE        (0x3068)
#define REG_PUB_AHB_MPU_CFG4_HIGH_RANGE       (0x306C)
#define REG_PUB_AHB_MPU_CFG5                  (0x3070)
#define REG_PUB_AHB_MPU_CFG5_ID_MASK_VAL      (0x3074)
#define REG_PUB_AHB_MPU_CFG5_LOW_RANGE        (0x3078)
#define REG_PUB_AHB_MPU_CFG5_HIGH_RANGE       (0x307C)
#define REG_PUB_AHB_MPU_CFG6                  (0x3080)
#define REG_PUB_AHB_MPU_CFG6_ID_MASK_VAL      (0x3084)
#define REG_PUB_AHB_MPU_CFG6_LOW_RANGE        (0x3088)
#define REG_PUB_AHB_MPU_CFG6_HIGH_RANGE       (0x308C)
#define REG_PUB_AHB_MPU_CFG7                  (0x3090)
#define REG_PUB_AHB_MPU_CFG7_ID_MASK_VAL      (0x3094)
#define REG_PUB_AHB_MPU_CFG7_LOW_RANGE        (0x3098)
#define REG_PUB_AHB_MPU_CFG7_HIGH_RANGE       (0x309C)
#define REG_PUB_AHB_MPU_CFG8                  (0x30A0)
#define REG_PUB_AHB_MPU_CFG8_ID_MASK_VAL      (0x30A4)
#define REG_PUB_AHB_MPU_CFG8_LOW_RANGE        (0x30A8)
#define REG_PUB_AHB_MPU_CFG8_HIGH_RANGE       (0x30AC)
#define REG_PUB_AHB_MPU_CFG9                  (0x30B0)
#define REG_PUB_AHB_MPU_CFG9_ID_MASK_VAL      (0x30B4)
#define REG_PUB_AHB_MPU_CFG9_LOW_RANGE        (0x30B8)
#define REG_PUB_AHB_MPU_CFG9_HIGH_RANGE       (0x30BC)
#define REG_PUB_AHB_MPU_CFG10                 (0x30C0)
#define REG_PUB_AHB_MPU_CFG10_ID_MASK_VAL     (0x30C4)
#define REG_PUB_AHB_MPU_CFG10_LOW_RANGE       (0x30C8)
#define REG_PUB_AHB_MPU_CFG10_HIGH_RANGE      (0x30CC)
#define REG_PUB_AHB_MPU_CFG11                 (0x30D0)
#define REG_PUB_AHB_MPU_CFG11_ID_MASK_VAL     (0x30D4)
#define REG_PUB_AHB_MPU_CFG11_LOW_RANGE       (0x30D8)
#define REG_PUB_AHB_MPU_CFG11_HIGH_RANGE      (0x30DC)
#define REG_PUB_AHB_MPU_CFG12                 (0x30E0)
#define REG_PUB_AHB_MPU_CFG12_ID_MASK_VAL     (0x30E4)
#define REG_PUB_AHB_MPU_CFG12_LOW_RANGE       (0x30E8)
#define REG_PUB_AHB_MPU_CFG12_HIGH_RANGE      (0x30EC)
#define REG_PUB_AHB_MPU_CFG13                 (0x30F0)
#define REG_PUB_AHB_MPU_CFG13_ID_MASK_VAL     (0x30F4)
#define REG_PUB_AHB_MPU_CFG13_LOW_RANGE       (0x30F8)
#define REG_PUB_AHB_MPU_CFG13_HIGH_RANGE      (0x30FC)
#define REG_PUB_AHB_MPU_CFG14                 (0x3100)
#define REG_PUB_AHB_MPU_CFG14_ID_MASK_VAL     (0x3104)
#define REG_PUB_AHB_MPU_CFG14_LOW_RANGE       (0x3108)
#define REG_PUB_AHB_MPU_CFG14_HIGH_RANGE      (0x310C)
#define REG_PUB_AHB_MPU_CFG15                 (0x3110)
#define REG_PUB_AHB_MPU_CFG15_ID_MASK_VAL     (0x3114)
#define REG_PUB_AHB_MPU_CFG15_LOW_RANGE       (0x3118)
#define REG_PUB_AHB_MPU_CFG15_HIGH_RANGE      (0x311C)

/* REG_PUB_AHB_DMC_EXT_LPCTRL_CFG */

#define BIT_PUB_AHB_SOFT_CMD_NUM(x)           (((x) & 0x7) << 8)
#define BIT_PUB_AHB_SOFT_CMD_FC_SEL(x)        (((x) & 0x7) << 4)
#define BIT_PUB_AHB_SOFT_CMD_RESP             BIT(3)
#define BIT_PUB_AHB_SOFT_CMD_DONE             BIT(2)
#define BIT_PUB_AHB_SOFT_CMD_START            BIT(0)

/* REG_PUB_AHB_DMC_EXT_LPCTRL_SEQL */

#define BIT_PUB_AHB_SOFT_CMD_SEQL(x)          (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_EXT_LPCTRL_SEQH */

#define BIT_PUB_AHB_SOFT_CMD_SEQH(x)          (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_EXT_LPCTRL_STEP */

#define BIT_PUB_AHB_SOFT_CMD_STEP(x)          (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_DUMP_ADDR */

#define BIT_PUB_AHB_MPU_DUMP_ADDR(x)          (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_MPU_VIO_ADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_ADDR(x)       (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_MPU_VIO_CMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_CMD(x)        (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_MPU_BASE_CFG */

#define BIT_PUB_AHB_DMC_MPU_VIO_INT_REQ       BIT(1)
#define BIT_PUB_AHB_MPU_EN                    BIT(0)

/* REG_PUB_AHB_MPU_CFG0 */

#define BIT_PUB_AHB_MPU_CFG0(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG0_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG0_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG0_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG0_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG0_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG0_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG1 */

#define BIT_PUB_AHB_MPU_CFG1(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG1_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG1_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG1_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG1_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG1_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG1_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG2 */

#define BIT_PUB_AHB_MPU_CFG2(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG2_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG2_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG2_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG2_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG2_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG2_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG3 */

#define BIT_PUB_AHB_MPU_CFG3(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG3_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG3_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG3_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG3_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG3_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG3_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG4 */

#define BIT_PUB_AHB_MPU_CFG4(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG4_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG4_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG4_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG4_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG4_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG4_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG5 */

#define BIT_PUB_AHB_MPU_CFG5(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG5_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG5_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG5_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG5_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG5_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG5_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG6 */

#define BIT_PUB_AHB_MPU_CFG6(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG6_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG6_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG6_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG6_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG6_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG6_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG7 */

#define BIT_PUB_AHB_MPU_CFG7(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG7_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG7_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG7_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG7_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG7_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG7_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG8 */

#define BIT_PUB_AHB_MPU_CFG8(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG8_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG8_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG8_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG8_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG8_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG8_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG9 */

#define BIT_PUB_AHB_MPU_CFG9(x)               (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG9_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG9_ID_MASK_VAL(x)   (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG9_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG9_LOW_RANGE(x)     (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG9_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG9_HIGH_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG10 */

#define BIT_PUB_AHB_MPU_CFG10(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG10_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG10_ID_MASK_VAL(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG10_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG10_LOW_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG10_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG10_HIGH_RANGE(x)   (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG11 */

#define BIT_PUB_AHB_MPU_CFG11(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG11_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG11_ID_MASK_VAL(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG11_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG11_LOW_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG11_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG11_HIGH_RANGE(x)   (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG12 */

#define BIT_PUB_AHB_MPU_CFG12(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG12_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG12_ID_MASK_VAL(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG12_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG12_LOW_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG12_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG12_HIGH_RANGE(x)   (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG13 */

#define BIT_PUB_AHB_MPU_CFG13(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG13_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG13_ID_MASK_VAL(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG13_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG13_LOW_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG13_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG13_HIGH_RANGE(x)   (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG14 */

#define BIT_PUB_AHB_MPU_CFG14(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG14_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG14_ID_MASK_VAL(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG14_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG14_LOW_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG14_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG14_HIGH_RANGE(x)   (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG15 */

#define BIT_PUB_AHB_MPU_CFG15(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_MPU_CFG15_ID_MASK_VAL */

#define BIT_PUB_AHB_MPU_CFG15_ID_MASK_VAL(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_MPU_CFG15_LOW_RANGE */

#define BIT_PUB_AHB_MPU_CFG15_LOW_RANGE(x)    (((x) & 0x7FFFFFF))

/* REG_PUB_AHB_MPU_CFG15_HIGH_RANGE */

#define BIT_PUB_AHB_MPU_CFG15_HIGH_RANGE(x)   (((x) & 0x7FFFFFF))


#endif /* PUB_AHB_H */


