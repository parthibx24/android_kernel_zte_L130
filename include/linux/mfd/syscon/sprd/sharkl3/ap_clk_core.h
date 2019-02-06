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


#ifndef AP_CLK_CORE_H
#define AP_CLK_CORE_H



#define REG_AP_CLK_CORE_CGM_AP_APB_CFG     (0x0020)
#define REG_AP_CLK_CORE_CGM_CE_CFG         (0x0024)
#define REG_AP_CLK_CORE_CGM_NANDC_ECC_CFG  (0x0028)
#define REG_AP_CLK_CORE_CGM_NANDC_26M_CFG  (0x002C)
#define REG_AP_CLK_CORE_CGM_EMMC_32K_CFG   (0x0030)
#define REG_AP_CLK_CORE_CGM_SDIO0_32K_CFG  (0x0034)
#define REG_AP_CLK_CORE_CGM_SDIO1_32K_CFG  (0x0038)
#define REG_AP_CLK_CORE_CGM_SDIO2_32K_CFG  (0x003C)
#define REG_AP_CLK_CORE_CGM_OTG_UTMI_CFG   (0x0040)
#define REG_AP_CLK_CORE_CGM_UART0_CFG      (0x0044)
#define REG_AP_CLK_CORE_CGM_UART1_CFG      (0x0048)
#define REG_AP_CLK_CORE_CGM_UART2_CFG      (0x004C)
#define REG_AP_CLK_CORE_CGM_UART3_CFG      (0x0050)
#define REG_AP_CLK_CORE_CGM_UART4_CFG      (0x0054)
#define REG_AP_CLK_CORE_CGM_I2C0_CFG       (0x0058)
#define REG_AP_CLK_CORE_CGM_I2C1_CFG       (0x005C)
#define REG_AP_CLK_CORE_CGM_I2C2_CFG       (0x0060)
#define REG_AP_CLK_CORE_CGM_I2C3_CFG       (0x0064)
#define REG_AP_CLK_CORE_CGM_I2C4_CFG       (0x0068)
#define REG_AP_CLK_CORE_CGM_I2C5_CFG       (0x006C)
#define REG_AP_CLK_CORE_CGM_I2C6_CFG       (0x0070)
#define REG_AP_CLK_CORE_CGM_SPI0_CFG       (0x0074)
#define REG_AP_CLK_CORE_CGM_SPI1_CFG       (0x0078)
#define REG_AP_CLK_CORE_CGM_SPI2_CFG       (0x007C)
#define REG_AP_CLK_CORE_CGM_SPI3_CFG       (0x0080)
#define REG_AP_CLK_CORE_CGM_IIS0_CFG       (0x0084)
#define REG_AP_CLK_CORE_CGM_IIS1_CFG       (0x0088)
#define REG_AP_CLK_CORE_CGM_IIS2_CFG       (0x008C)
#define REG_AP_CLK_CORE_CGM_SIM0_CFG       (0x0090)
#define REG_AP_CLK_CORE_CGM_SIM0_32K_CFG   (0x0094)

/* REG_AP_CLK_CORE_CGM_AP_APB_CFG */

#define BIT_AP_CLK_CORE_CGM_AP_APB_CFG_CGM_AP_APB_SEL(x)        (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_CE_CFG */

#define BIT_AP_CLK_CORE_CGM_CE_CFG_CGM_CE_DIV(x)                (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_CE_CFG_CGM_CE_SEL                   BIT(0)

/* REG_AP_CLK_CORE_CGM_NANDC_ECC_CFG */

#define BIT_AP_CLK_CORE_CGM_NANDC_ECC_CFG_CGM_NANDC_ECC_DIV(x)  (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_NANDC_ECC_CFG_CGM_NANDC_ECC_SEL(x)  (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_NANDC_26M_CFG */

#define BIT_AP_CLK_CORE_CGM_NANDC_26M_CFG_CGM_NANDC_26M_SEL     BIT(0)

/* REG_AP_CLK_CORE_CGM_EMMC_32K_CFG */

#define BIT_AP_CLK_CORE_CGM_EMMC_32K_CFG_CGM_EMMC_32K_SEL       BIT(0)

/* REG_AP_CLK_CORE_CGM_SDIO0_32K_CFG */

#define BIT_AP_CLK_CORE_CGM_SDIO0_32K_CFG_CGM_SDIO0_32K_SEL     BIT(0)

/* REG_AP_CLK_CORE_CGM_SDIO1_32K_CFG */

#define BIT_AP_CLK_CORE_CGM_SDIO1_32K_CFG_CGM_SDIO1_32K_SEL     BIT(0)

/* REG_AP_CLK_CORE_CGM_SDIO2_32K_CFG */

#define BIT_AP_CLK_CORE_CGM_SDIO2_32K_CFG_CGM_SDIO2_32K_SEL     BIT(0)

/* REG_AP_CLK_CORE_CGM_OTG_UTMI_CFG */

#define BIT_AP_CLK_CORE_CGM_OTG_UTMI_CFG_CGM_OTG_UTMI_PAD_SEL   BIT(16)

/* REG_AP_CLK_CORE_CGM_UART0_CFG */

#define BIT_AP_CLK_CORE_CGM_UART0_CFG_CGM_UART0_DIV(x)          (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_UART0_CFG_CGM_UART0_SEL(x)          (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_UART1_CFG */

#define BIT_AP_CLK_CORE_CGM_UART1_CFG_CGM_UART1_DIV(x)          (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_UART1_CFG_CGM_UART1_SEL(x)          (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_UART2_CFG */

#define BIT_AP_CLK_CORE_CGM_UART2_CFG_CGM_UART2_DIV(x)          (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_UART2_CFG_CGM_UART2_SEL(x)          (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_UART3_CFG */

#define BIT_AP_CLK_CORE_CGM_UART3_CFG_CGM_UART3_DIV(x)          (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_UART3_CFG_CGM_UART3_SEL(x)          (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_UART4_CFG */

#define BIT_AP_CLK_CORE_CGM_UART4_CFG_CGM_UART4_DIV(x)          (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_UART4_CFG_CGM_UART4_SEL(x)          (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C0_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C0_CFG_CGM_I2C0_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C0_CFG_CGM_I2C0_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C1_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C1_CFG_CGM_I2C1_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C1_CFG_CGM_I2C1_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C2_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C2_CFG_CGM_I2C2_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C2_CFG_CGM_I2C2_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C3_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C3_CFG_CGM_I2C3_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C3_CFG_CGM_I2C3_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C4_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C4_CFG_CGM_I2C4_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C4_CFG_CGM_I2C4_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C5_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C5_CFG_CGM_I2C5_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C5_CFG_CGM_I2C5_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C6_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C6_CFG_CGM_I2C6_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C6_CFG_CGM_I2C6_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SPI0_CFG */

#define BIT_AP_CLK_CORE_CGM_SPI0_CFG_CGM_SPI0_PAD_SEL           BIT(16)
#define BIT_AP_CLK_CORE_CGM_SPI0_CFG_CGM_SPI0_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SPI0_CFG_CGM_SPI0_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SPI1_CFG */

#define BIT_AP_CLK_CORE_CGM_SPI1_CFG_CGM_SPI1_PAD_SEL           BIT(16)
#define BIT_AP_CLK_CORE_CGM_SPI1_CFG_CGM_SPI1_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SPI1_CFG_CGM_SPI1_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SPI2_CFG */

#define BIT_AP_CLK_CORE_CGM_SPI2_CFG_CGM_SPI2_PAD_SEL           BIT(16)
#define BIT_AP_CLK_CORE_CGM_SPI2_CFG_CGM_SPI2_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SPI2_CFG_CGM_SPI2_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SPI3_CFG */

#define BIT_AP_CLK_CORE_CGM_SPI3_CFG_CGM_SPI3_PAD_SEL           BIT(16)
#define BIT_AP_CLK_CORE_CGM_SPI3_CFG_CGM_SPI3_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SPI3_CFG_CGM_SPI3_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_IIS0_CFG */

#define BIT_AP_CLK_CORE_CGM_IIS0_CFG_CGM_IIS0_DIV(x)            (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CORE_CGM_IIS0_CFG_CGM_IIS0_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_IIS1_CFG */

#define BIT_AP_CLK_CORE_CGM_IIS1_CFG_CGM_IIS1_DIV(x)            (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CORE_CGM_IIS1_CFG_CGM_IIS1_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_IIS2_CFG */

#define BIT_AP_CLK_CORE_CGM_IIS2_CFG_CGM_IIS2_DIV(x)            (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CORE_CGM_IIS2_CFG_CGM_IIS2_SEL(x)            (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SIM0_CFG */

#define BIT_AP_CLK_CORE_CGM_SIM0_CFG_CGM_SIM0_DIV(x)            (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SIM0_CFG_CGM_SIM0_SEL(x)            (((x) & 0x7))

/* REG_AP_CLK_CORE_CGM_SIM0_32K_CFG */

#define BIT_AP_CLK_CORE_CGM_SIM0_32K_CFG_CGM_SIM0_32K_SEL       BIT(0)


#endif /* AP_CLK_CORE_H */

