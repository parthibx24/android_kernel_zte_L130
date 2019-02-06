/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-27 19:24:16
 *
 */


#ifndef APCPU_TOP_CLK_CORE_H
#define APCPU_TOP_CLK_CORE_H



#define REG_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG       (0x0020)
#define REG_APCPU_TOP_CLK_CORE_CGM_CORE1_CFG       (0x0024)
#define REG_APCPU_TOP_CLK_CORE_CGM_CORE2_CFG       (0x0028)
#define REG_APCPU_TOP_CLK_CORE_CGM_CORE3_CFG       (0x002C)
#define REG_APCPU_TOP_CLK_CORE_CGM_CORE4_CFG       (0x0030)
#define REG_APCPU_TOP_CLK_CORE_CGM_CORE5_CFG       (0x0034)
#define REG_APCPU_TOP_CLK_CORE_CGM_CORE6_CFG       (0x0038)
#define REG_APCPU_TOP_CLK_CORE_CGM_CORE7_CFG       (0x003C)
#define REG_APCPU_TOP_CLK_CORE_CGM_SCU_CFG         (0x0040)
#define REG_APCPU_TOP_CLK_CORE_CGM_ACE_CFG         (0x0044)
#define REG_APCPU_TOP_CLK_CORE_CGM_AXI_PERIPH_CFG  (0x0048)
#define REG_APCPU_TOP_CLK_CORE_CGM_AXI_ACP_CFG     (0x004C)
#define REG_APCPU_TOP_CLK_CORE_CGM_ATB_CFG         (0x0050)
#define REG_APCPU_TOP_CLK_CORE_CGM_DEBUG_APB_CFG   (0x0054)
#define REG_APCPU_TOP_CLK_CORE_CGM_GIC_CFG         (0x0058)
#define REG_APCPU_TOP_CLK_CORE_CGM_PERIPH_CFG      (0x005C)

/* REG_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_DIV(x)            (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE0_CFG_CGM_CORE0_SEL(x)            (((x) & 0x7))

/* REG_APCPU_TOP_CLK_CORE_CGM_CORE1_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE1_CFG_CGM_CORE1_DIV(x)            (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE1_CFG_CGM_CORE1_SEL(x)            (((x) & 0x7))

/* REG_APCPU_TOP_CLK_CORE_CGM_CORE2_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE2_CFG_CGM_CORE2_DIV(x)            (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE2_CFG_CGM_CORE2_SEL(x)            (((x) & 0x7))

/* REG_APCPU_TOP_CLK_CORE_CGM_CORE3_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE3_CFG_CGM_CORE3_DIV(x)            (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE3_CFG_CGM_CORE3_SEL(x)            (((x) & 0x7))

/* REG_APCPU_TOP_CLK_CORE_CGM_CORE4_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE4_CFG_CGM_CORE4_DIV(x)            (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE4_CFG_CGM_CORE4_SEL(x)            (((x) & 0x7))

/* REG_APCPU_TOP_CLK_CORE_CGM_CORE5_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE5_CFG_CGM_CORE5_DIV(x)            (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE5_CFG_CGM_CORE5_SEL(x)            (((x) & 0x7))

/* REG_APCPU_TOP_CLK_CORE_CGM_CORE6_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE6_CFG_CGM_CORE6_DIV(x)            (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE6_CFG_CGM_CORE6_SEL(x)            (((x) & 0x7))

/* REG_APCPU_TOP_CLK_CORE_CGM_CORE7_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE7_CFG_CGM_CORE7_DIV(x)            (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_CORE7_CFG_CGM_CORE7_SEL(x)            (((x) & 0x7))

/* REG_APCPU_TOP_CLK_CORE_CGM_SCU_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_SCU_CFG_CGM_SCU_DIV(x)                (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_SCU_CFG_CGM_SCU_SEL(x)                (((x) & 0x7))

/* REG_APCPU_TOP_CLK_CORE_CGM_ACE_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_ACE_CFG_CGM_ACE_DIV(x)                (((x) & 0x7) << 8)

/* REG_APCPU_TOP_CLK_CORE_CGM_AXI_PERIPH_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_AXI_PERIPH_CFG_CGM_AXI_PERIPH_DIV(x)  (((x) & 0x7) << 8)

/* REG_APCPU_TOP_CLK_CORE_CGM_AXI_ACP_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_AXI_ACP_CFG_CGM_AXI_ACP_DIV(x)        (((x) & 0x7) << 8)

/* REG_APCPU_TOP_CLK_CORE_CGM_ATB_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_ATB_CFG_CGM_ATB_DIV(x)                (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_ATB_CFG_CGM_ATB_SEL(x)                (((x) & 0x3))

/* REG_APCPU_TOP_CLK_CORE_CGM_DEBUG_APB_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_DEBUG_APB_CFG_CGM_DEBUG_APB_DIV(x)    (((x) & 0x7) << 8)

/* REG_APCPU_TOP_CLK_CORE_CGM_GIC_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_GIC_CFG_CGM_GIC_DIV(x)                (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_GIC_CFG_CGM_GIC_SEL(x)                (((x) & 0x3))

/* REG_APCPU_TOP_CLK_CORE_CGM_PERIPH_CFG */

#define BIT_APCPU_TOP_CLK_CORE_CGM_PERIPH_CFG_CGM_PERIPH_DIV(x)          (((x) & 0x7) << 8)
#define BIT_APCPU_TOP_CLK_CORE_CGM_PERIPH_CFG_CGM_PERIPH_SEL(x)          (((x) & 0x3))


#endif /* APCPU_TOP_CLK_CORE_H */

