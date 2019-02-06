#ifndef __UMW2652_glb_H__
#define __UMW2652_glb_H__

/* UMW2652 is the lite of sc2355 */
#include "sc2355_glb.h"

#define MARLIN_LITE_CHIPID 0x2355B000

/**************GNSS BEG**************/
#ifdef GNSS_CP_START_ADDR
#undef GNSS_CP_START_ADDR
#define GNSS_CP_START_ADDR 0x40A50000
#endif

#ifdef GNSS_FIRMWARE_MAX_SIZE
#undef GNSS_FIRMWARE_MAX_SIZE
#define GNSS_FIRMWARE_MAX_SIZE 0x2B000
#endif
/**************GNSS END**************/

/**************WCN BEG**************/
#ifdef FIRMWARE_MAX_SIZE
#undef FIRMWARE_MAX_SIZE
#define FIRMWARE_MAX_SIZE 0xe7400
#endif

#ifdef SYNC_ADDR
#undef SYNC_ADDR
#define SYNC_ADDR 0x405E73B0
#endif

#ifdef ARM_DAP_BASE_ADDR
#undef ARM_DAP_BASE_ADDR
#define ARM_DAP_BASE_ADDR 0X40060000
#endif

#ifdef ARM_DAP_REG1
#undef ARM_DAP_REG1
#define ARM_DAP_REG1 0X40060000
#endif

#ifdef ARM_DAP_REG2
#undef ARM_DAP_REG2
#define ARM_DAP_REG2 0X40060004
#endif

#ifdef ARM_DAP_REG3
#undef ARM_DAP_REG3
#define ARM_DAP_REG3 0X4006000C
#endif

#ifdef BTWF_STATUS_REG
#undef BTWF_STATUS_REG
#define BTWF_STATUS_REG 0x400600fc
#endif

#ifdef WIFI_AON_MAC_SIZE
#undef WIFI_AON_MAC_SIZE
#define WIFI_AON_MAC_SIZE 0x120
#endif

#ifdef WIFI_RAM_SIZE
#undef WIFI_RAM_SIZE
#define WIFI_RAM_SIZE 0x4a800
#endif

#ifdef WIFI_GLB_REG_SIZE
#undef WIFI_GLB_REG_SIZE
#define WIFI_GLB_REG_SIZE 0x58
#endif

#ifdef BT_ACC_SIZE
#undef BT_ACC_SIZE
#define BT_ACC_SIZE 0x8f4
#endif

#ifdef BT_MODEM_SIZE
#undef BT_MODEM_SIZE
#define BT_MODEM_SIZE 0x310
#endif

/* for marlin3Lite */
#define APB_ENB1			0x4008801c
#define DBG_CM4_EB			BIT(10)
#define DAP_CTRL			0x4008828c
#define CM4_DAP_SEL_BTWF_LITE		BIT(1)

#define BTWF_XLT_WAIT		0x10
#define BTWF_XLTBUF_WAIT	0x20
#define BTWF_PLL_PWR_WAIT	0x40
/**************WCN END**************/

#endif
