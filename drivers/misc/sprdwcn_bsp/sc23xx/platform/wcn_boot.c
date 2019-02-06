/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/firmware.h>
#include <linux/file.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/marlin_platform.h>
#include <linux/mfd/sprd/pmic_glb_reg.h>
#include <linux/mfd/syscon.h>
#include <linux/mfd/syscon/sprd-glb.h>
#include <linux/of_gpio.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/regmap.h>
#include <linux/sdiom_rx_api.h>
#include <linux/sdiom_tx_api.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/unistd.h>
#include <linux/vmalloc.h>
#include <linux/workqueue.h>

#include "wcn_gnss.h"
#include "rf/rf.h"
#include "../sleep/sdio_int.h"
#include "../sleep/slp_mgr.h"
#include "mem_pd_mgr.h"
#include <soc/sprd/wcn_bus.h>
#include "wcn_op.h"
#include "wcn_parn_parser.h"
#include "rdc_debug.h"
#include "wcn_dump.h"
#include "wcn_misc.h"
#include "wcn_log.h"
#include "wcn_procfs.h"
#include "mdbg_type.h"
#include "../include/wcn_glb_reg.h"

#ifndef REG_PMU_APB_XTL_WAIT_CNT0
#define REG_PMU_APB_XTL_WAIT_CNT0 0xe42b00ac
#endif

static char BTWF_FIRMWARE_PATH[255];
static char GNSS_FIRMWARE_PATH[255];

struct wcn_sync_info_t {
	unsigned int init_status;
	unsigned int mem_pd_bt_start_addr;
	unsigned int mem_pd_bt_end_addr;
	unsigned int mem_pd_wifi_start_addr;
	unsigned int mem_pd_wifi_end_addr;
	unsigned int prj_type;
	unsigned short tsx_dac_data;
	unsigned short rsved;
} __packed;

struct tsx_data {
	u32 flag; /* cali flag ref */
	u16 dac; /* AFC cali data */
	u16 reserved;
};

struct tsx_cali {
	u32 init_flag;
	struct tsx_data tsxdata;
};

struct marlin_device {
	int coexist;
	int wakeup_ap;
	int ap_send_data;
	int reset;
	int chip_en;
	int int_ap;
	/* power sequence */
	/* VDDIO->DVDD12->chip_en->rst_N->AVDD12->AVDD33 */
	struct regulator *dvdd12;
	struct regulator *avdd12;
	/* for PCIe */
	struct regulator *avdd18;
	/* for wifi PA, BT TX RX */
	struct regulator *avdd33;
	/* for internal 26M clock */
	struct regulator *dcxo18;
	struct clk *clk_32k;

	struct clk *clk_parent;
	struct clk *clk_enable;
	struct mutex power_lock;
	struct completion carddetect_done;
	struct completion download_done;
	struct completion gnss_download_done;
	unsigned long power_state;
	char *write_buffer;
	struct delayed_work power_wq;
	struct work_struct download_wq;
	struct work_struct gnss_dl_wq;
	bool no_power_off;
	bool wait_ge2_disabled;
	bool is_btwf_in_sysfs;
	bool is_gnss_in_sysfs;
	int wifi_need_download_ini_flag;
	int first_power_on_flag;
	unsigned char download_finish_flag;
	int loopcheck_status_change;
	struct wcn_sync_info_t sync_f;
	struct tsx_cali tsxcali;
	char *btwf_path;
	char *gnss_path;
};

struct wifi_calibration {
	struct wifi_config_t config_data;
	struct wifi_cali_t cali_data;
};

static struct wifi_calibration wifi_data;
struct completion ge2_completion;
static int first_call_flag;
marlin_reset_callback marlin_reset_func;
void *marlin_callback_para;

struct marlin_device *marlin_dev;
struct sprdwcn_gnss_ops *gnss_ops;

unsigned char  flag_reset;
char functionmask[8];
static unsigned int reg_val;
static unsigned int clk_wait_val;
static unsigned int cp_clk_wait_val;
static unsigned int marlin2_clk_wait_reg;

/* for PMIC control */
static struct regmap *reg_map;

#define IMG_HEAD_MAGIC "WCNM"
#define IMG_MARLINAB_TAG "MLAB"
#define IMG_MARLINAC_TAG "MLAC"
#define MARLIN2_AA	1
#define MARLIN2_AB	2
#define MARLIN2_AA_CHIP 0x23490000
#define MARLIN_MASK 0x27F
#define GNSS_MASK 0x080
#define AUTO_RUN_MASK 0X100

#define AFC_CALI_FLAG 0x54463031 /* cali flag */
#define AFC_CALI_READ_FINISH 0x12121212
#define WCN_AFC_CALI_PATH "/productinfo/wcn/tsx_bt_data.txt"

/* #define E2S(x) { case x: return #x; } */

struct head {
	char magic[4];
	unsigned int version;
	unsigned int img_count;
};

struct imageinfo {
	char tag[4];
	unsigned int offset;
	unsigned int size;
};

static unsigned long int chip_id;

unsigned int marlin_get_wcn_chipid(void)
{
	int ret;

	if (unlikely(chip_id != 0))
		return chip_id;
	ret = sprdwcn_bus_reg_read(CHIPID_REG, &chip_id, 4);
	if (ret < 0) {
		WCN_ERR("marlin read chip ID fail\n");
		return 0;
	}
	WCN_INFO("marlin: chipid=%lx, %s\n", chip_id, __func__);

	return chip_id;
}

/* get the subsys string */
const char *strno(int subsys)
{
	switch (subsys) {
	case MARLIN_BLUETOOTH:
		return "MARLIN_BLUETOOTH";
	case MARLIN_FM:
		return "MARLIN_FM";
	case MARLIN_WIFI:
		return "MARLIN_WIFI";
	case MARLIN_WIFI_FLUSH:
		return "MARLIN_WIFI_FLUSH";
	case MARLIN_SDIO_TX:
		return "MARLIN_SDIO_TX";
	case MARLIN_SDIO_RX:
		return "MARLIN_SDIO_RX";
	case MARLIN_MDBG:
		return "MARLIN_MDBG";
	case MARLIN_GNSS:
		return "MARLIN_GNSS";
	case WCN_AUTO:
		return "WCN_AUTO";
	case MARLIN_ALL:
		return "MARLIN_ALL";
	default: return "MARLIN_SUBSYS_UNKNOWN";
	}
/* #undef E2S */
}

/* tsx/dac init */
int marlin_tsx_cali_data_read(struct tsx_data *p_tsx_data)
{
	u32 size = 0;
	u32 read_len = 0;
	struct file *file;
	loff_t offset = 0;
	char *pdata;

	file = filp_open(WCN_AFC_CALI_PATH, O_RDONLY, 0);
	if (IS_ERR(file)) {
		WCN_ERR("open file error\n");
		return -1;
	}
	WCN_INFO("open image "WCN_AFC_CALI_PATH" successfully\n");

	/* read file to buffer */
	size = sizeof(struct tsx_data);
	pdata = (char *)p_tsx_data;
	do {
		read_len = kernel_read(file, offset, pdata, size);
		if (read_len > 0) {
			size -= read_len;
			pdata += read_len;
		}
	} while ((read_len > 0) && (size > 0));
	fput(file);
	WCN_INFO("After read, data =%p dac value %02x\n", pdata,
			 p_tsx_data->dac);

	return 0;
}

static u16 marlin_tsx_cali_data_get(void)
{
	int ret;

	WCN_INFO("tsx cali init flag %d\n", marlin_dev->tsxcali.init_flag);

	if (marlin_dev->tsxcali.init_flag == AFC_CALI_READ_FINISH)
		return marlin_dev->tsxcali.tsxdata.dac;

	ret = marlin_tsx_cali_data_read(&marlin_dev->tsxcali.tsxdata);
	marlin_dev->tsxcali.init_flag = AFC_CALI_READ_FINISH;
	if (ret != 0) {
		marlin_dev->tsxcali.tsxdata.dac = 0xffff;
		WCN_INFO("tsx cali read fail! default 0xffff\n");
		return marlin_dev->tsxcali.tsxdata.dac;
	}

	if (marlin_dev->tsxcali.tsxdata.flag != AFC_CALI_FLAG) {
		marlin_dev->tsxcali.tsxdata.dac = 0xffff;
		WCN_INFO("tsx cali flag fail! default 0xffff\n");
		return marlin_dev->tsxcali.tsxdata.dac;
	}
	WCN_INFO("dac flag %d value:0x%x\n",
			    marlin_dev->tsxcali.tsxdata.flag,
			    marlin_dev->tsxcali.tsxdata.dac);

	return marlin_dev->tsxcali.tsxdata.dac;
}

static int marlin_judge_imagepack(char *buffer)
{
	int ret;
	struct head *imghead;

	if (buffer == NULL)
		return -1;
	imghead = vmalloc(sizeof(struct head));
	if (!imghead) {
		WCN_ERR("%s no memory\n", __func__);
		return -1;
	}
	memcpy(imghead, buffer, sizeof(struct head));
	WCN_INFO("marlin image  pack type:%s in the func %s:\n",
		imghead->magic, __func__);
	ret = strncmp(IMG_HEAD_MAGIC, imghead->magic, 4);
	vfree(imghead);

	return ret;
}


static struct imageinfo *marlin_judge_images(char *buffer)
{

	struct imageinfo *imginfo = NULL;

	if (buffer == NULL)
		return NULL;
	imginfo = vmalloc((sizeof(struct imageinfo)));
	if (!imginfo) {
		WCN_ERR("%s no memory\n", __func__);
		return NULL;
	}

	if (chip_id == MARLIN_AC_CHIPID || chip_id == MARLIN_AD_CHIPID) {
		WCN_INFO("%s marlin is AC(AD) !!!!\n",  __func__);
		memcpy(imginfo, (buffer + sizeof(struct head)),
			sizeof(struct imageinfo));
		if (!strncmp(IMG_MARLINAC_TAG, imginfo->tag, 4)) {
			WCN_INFO("marlin imginfo1 type is %s in the func %s:\n",
				imginfo->tag, __func__);
			return imginfo;
		}
		WCN_ERR("Marlin can't find marlin AC(AD) image!!!\n");
		vfree(imginfo);
		return NULL;
	} else if (chip_id == MARLIN_AB_CHIPID) {
		WCN_INFO("%s marlin is AB !!!!\n", __func__);
		memcpy(imginfo,
			buffer + sizeof(struct imageinfo) + sizeof(struct head),
			sizeof(struct imageinfo));
		if (!strncmp(IMG_MARLINAB_TAG, imginfo->tag, 4)) {
			WCN_INFO("marlin imginfo1 type is %s in the func %s:\n",
				imginfo->tag, __func__);
			return imginfo;
		}
		WCN_ERR("Marlin can't find marlin AB image!!!\n");
		vfree(imginfo);
		return NULL;
	}
	WCN_ERR("Marlin can't find marlin AB or AC(AD) image!!!\n");
	vfree(imginfo);

	return NULL;
}

static char *btwf_load_firmware_data(unsigned long int imag_size)
{
	int read_len, size, i, opn_num_max = 15;
	char *buffer = NULL;
	char *data = NULL;
	struct file *file;
	loff_t offset = 0;

	MDBG_LOG("%s entry\n", __func__);

	file = filp_open(BTWF_FIRMWARE_PATH, O_RDONLY, 0);
	for (i = 1; i <= opn_num_max; i++) {
		if (IS_ERR(file)) {
			WCN_INFO("try open file %s,count_num:%d,%s\n",
				BTWF_FIRMWARE_PATH, i, __func__);
			ssleep(1);
			file = filp_open(BTWF_FIRMWARE_PATH, O_RDONLY, 0);
		} else
			break;
	}
	if (IS_ERR(file)) {
		WCN_ERR("%s open file %s error\n",
			BTWF_FIRMWARE_PATH, __func__);
		return NULL;
	}
	MDBG_LOG("marlin %s open image file  successfully\n",
		__func__);
	size = imag_size;
	buffer = vmalloc(size);
	if (!buffer) {
		fput(file);
		WCN_ERR("no memory for image\n");
		return NULL;
	}

	read_len = kernel_read(file, 0, functionmask, 8);
	if ((functionmask[0] == 0x00) && (functionmask[1] == 0x00))
		offset = offset + 8;
	else
		functionmask[7] = 0;

	data = buffer;
	do {
		read_len = kernel_read(file, offset, buffer, size);
		if (read_len > 0) {
			size -= read_len;
			buffer += read_len;
		}
	} while ((read_len > 0) && (size > 0));
	fput(file);
	WCN_INFO("%s finish read_Len:%d\n", __func__, read_len);
	if (read_len <= 0)
		return NULL;

	return data;
}

static int marlin_download_from_partition(void)
{
	int err, len, trans_size, ret;
	unsigned long int imgpack_size, img_size;
	char *buffer = NULL;
	char *temp = NULL;
	struct imageinfo *imginfo = NULL;

	img_size = imgpack_size =  FIRMWARE_MAX_SIZE;

	WCN_INFO("%s entry\n", __func__);
	temp = buffer = btwf_load_firmware_data(imgpack_size);
	if (!buffer) {
		WCN_INFO("%s buff is NULL\n", __func__);
		return -1;
	}

	ret = marlin_judge_imagepack(buffer);
	if (!ret) {
		WCN_INFO("marlin %s imagepack is WCNM type,need parse it\n",
			__func__);
		marlin_get_wcn_chipid();

		imginfo = marlin_judge_images(buffer);
		vfree(temp);
		if (!imginfo) {
			WCN_ERR("marlin:%s imginfo is NULL\n", __func__);
			return -1;
		}
		imgpack_size = imginfo->offset + imginfo->size;
		temp = buffer = btwf_load_firmware_data(imgpack_size);
		if (!buffer) {
			WCN_ERR("marlin:%s buffer is NULL\n", __func__);
			vfree(imginfo);
			return -1;
		}
		buffer += imginfo->offset;
		img_size = imginfo->size;
		vfree(imginfo);
	}

	len = 0;
	while (len < img_size) {
		trans_size = (img_size - len) > PACKET_SIZE ?
				PACKET_SIZE : (img_size - len);
		memcpy(marlin_dev->write_buffer, buffer + len, trans_size);
		err = sprdwcn_bus_direct_write(CP_START_ADDR + len,
			marlin_dev->write_buffer, trans_size);
		if (err < 0) {
			WCN_ERR(" %s: dt write SDIO error:%d\n", __func__, err);
			vfree(temp);
			return -1;
		}
		len += PACKET_SIZE;
	}
	vfree(temp);
	WCN_INFO("%s finish and successful\n", __func__);

	return 0;
}

int wcn_gnss_ops_register(struct sprdwcn_gnss_ops *ops)
{
	if (gnss_ops) {
		WARN_ON(1);
		return -EBUSY;
	}

	gnss_ops = ops;

	return 0;
}

void wcn_gnss_ops_unregister(void)
{
	gnss_ops = NULL;
}

static char *gnss_load_firmware_data(unsigned long int imag_size)
{
	int read_len, size, i, opn_num_max = 15;
	char *buffer = NULL;
	char *data = NULL;
	struct file *file;

	MDBG_LOG("%s entry\n", __func__);
	if (gnss_ops && (gnss_ops->set_file_path))
		gnss_ops->set_file_path(&GNSS_FIRMWARE_PATH[0]);
	else
		WCN_ERR("%s gnss_ops set_file_path error\n", __func__);
	file = filp_open(GNSS_FIRMWARE_PATH, O_RDONLY, 0);
	for (i = 1; i <= opn_num_max; i++) {
		if (IS_ERR(file)) {
			WCN_INFO("try open file %s,count_num:%d,%s\n",
				GNSS_FIRMWARE_PATH, i, __func__);
			ssleep(1);
			file = filp_open(GNSS_FIRMWARE_PATH, O_RDONLY, 0);
		} else
			break;
	}
	if (IS_ERR(file)) {
		WCN_ERR("%s marlin3 gnss open file %s error\n",
			GNSS_FIRMWARE_PATH, __func__);
		return NULL;
	}
	MDBG_LOG("%s open image file  successfully\n", __func__);
	size = imag_size;
	buffer = vmalloc(size);
	if (!buffer) {
		fput(file);
		WCN_ERR("no memory for gnss img\n");
		return NULL;
	}

	data = buffer;
	do {
		read_len = kernel_read(file, 0, buffer, size);
		if (read_len > 0) {
			size -= read_len;
			buffer += read_len;
		}
	} while ((read_len > 0) && (size > 0));
	fput(file);
	WCN_INFO("%s finish read_Len:%d\n", __func__, read_len);
	if (read_len <= 0)
		return NULL;

	return data;
}

static int gnss_download_from_partition(void)
{
	int err, len, trans_size;
	unsigned long int imgpack_size, img_size;
	char *buffer = NULL;
	char *temp = NULL;

	img_size = imgpack_size =  GNSS_FIRMWARE_MAX_SIZE;

	WCN_INFO("GNSS %s entry\n", __func__);
	temp = buffer = gnss_load_firmware_data(imgpack_size);
	if (!buffer) {
		WCN_INFO("%s gnss buff is NULL\n", __func__);
		return -1;
	}

	len = 0;
	while (len < img_size) {
		trans_size = (img_size - len) > PACKET_SIZE ?
				PACKET_SIZE : (img_size - len);
		memcpy(marlin_dev->write_buffer, buffer + len, trans_size);
		err = sprdwcn_bus_direct_write(GNSS_CP_START_ADDR + len,
			marlin_dev->write_buffer, trans_size);
		if (err < 0) {
			WCN_ERR("gnss dt write %s error:%d\n", __func__, err);
			vfree(temp);
			return -1;
		}
		len += PACKET_SIZE;
	}
	vfree(temp);
	WCN_INFO("%s gnss download firmware finish\n", __func__);

	return 0;
}

static int gnss_download_firmware(void)
{
	const struct firmware *firmware;
	char *buf;
	int err;
	int i, len, count, trans_size;

	if (marlin_dev->is_gnss_in_sysfs == 1) {
		err = gnss_download_from_partition();
		return err;
	}

	WCN_INFO("%s start from /system/etc/firmware/\n", __func__);
	buf = marlin_dev->write_buffer;
	err = request_firmware_direct(&firmware, "gnssmodem.bin", NULL);
	if (err < 0) {
		WCN_ERR("%s no find gnssmodem.bin err:%d(ignore)\n",
			__func__, err);
		marlin_dev->is_gnss_in_sysfs = 1;
		err = gnss_download_from_partition();

		return err;
	}
	count = (firmware->size + PACKET_SIZE - 1) / PACKET_SIZE;
	len = 0;
	for (i = 0; i < count; i++) {
		trans_size = (firmware->size - len) > PACKET_SIZE ?
				PACKET_SIZE : (firmware->size - len);
		memcpy(buf, firmware->data + len, trans_size);
		err = sprdwcn_bus_direct_write(GNSS_CP_START_ADDR + len, buf,
				trans_size);
		if (err < 0) {
			WCN_ERR("gnss dt write %s error:%d\n", __func__, err);
			release_firmware(firmware);

			return err;
		}
		len += trans_size;
	}
	release_firmware(firmware);
	WCN_INFO("%s successfully through request_firmware!\n", __func__);

	return 0;
}

/* BT WIFI FM download */
static int btwifi_download_firmware(void)
{
	const struct firmware *firmware;
	char *buf;
	int err;
	int i, len, count, trans_size;

	if (marlin_dev->is_btwf_in_sysfs == 1) {
		err = marlin_download_from_partition();
		return err;
	}

	WCN_INFO("marlin %s from /system/etc/firmware/ start!\n", __func__);
	buf = marlin_dev->write_buffer;
	err = request_firmware_direct(&firmware, "wcnmodem.bin", NULL);
	if (err < 0) {
		WCN_ERR("no find wcnmodem.bin errno:(%d)(ignore!!)\n", err);
		marlin_dev->is_btwf_in_sysfs = 1;
		err = marlin_download_from_partition();

		return err;
	}

	count = (firmware->size + PACKET_SIZE - 1) / PACKET_SIZE;
	len = 0;

	for (i = 0; i < count; i++) {
		trans_size = (firmware->size - len) > PACKET_SIZE ?
				PACKET_SIZE : (firmware->size - len);
		memcpy(buf, firmware->data + len, trans_size);
		err = sprdwcn_bus_direct_write(CP_START_ADDR + len,
					       buf, trans_size);
		if (err < 0) {
			WCN_ERR("marlin dt write %s error:%d\n", __func__, err);
			release_firmware(firmware);
			return err;
		}
		len += trans_size;
	}

	release_firmware(firmware);
	WCN_INFO("marlin %s successfully!\n", __func__);

	return 0;
}

static int marlin_parse_dt(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct regmap *pmu_apb_gpr;
	int ret;

	if (!marlin_dev)
		return -1;

	marlin_dev->coexist = of_get_named_gpio(np,
			"m2-to-ap-coexist-gpios", 0);
	if (!gpio_is_valid(marlin_dev->coexist))
		return -EINVAL;

	marlin_dev->wakeup_ap = of_get_named_gpio(np,
			"m2-wakeup-ap-gpios", 0);
	if (!gpio_is_valid(marlin_dev->wakeup_ap))
		return -EINVAL;

	marlin_dev->ap_send_data = of_get_named_gpio(np,
			"permit-ap-send-gpios", 0);
	if (!gpio_is_valid(marlin_dev->ap_send_data))
		return -EINVAL;

	marlin_dev->reset = of_get_named_gpio(np,
			"rstn-gpios", 0);
	if (!gpio_is_valid(marlin_dev->reset))
		return -EINVAL;

	marlin_dev->chip_en = of_get_named_gpio(np,
			"chip-en-gpios", 0);
	if (!gpio_is_valid(marlin_dev->chip_en))
		return -EINVAL;

	marlin_dev->int_ap = of_get_named_gpio(np,
			"m2-to-ap-irq-gpios", 0);
	if (!gpio_is_valid(marlin_dev->int_ap))
		return -EINVAL;

	marlin_dev->dvdd12 = devm_regulator_get(&pdev->dev, "dvdd12");
	if (IS_ERR(marlin_dev->dvdd12)) {
		WCN_ERR("Get regulator of dvdd12 error!\n");
		return -1;
	}

	marlin_dev->avdd12 = devm_regulator_get(&pdev->dev, "avdd12");
	if (IS_ERR(marlin_dev->avdd12))
		WCN_ERR("Get regulator of avdd12 error!\n");

	marlin_dev->avdd33 = devm_regulator_get(&pdev->dev, "avdd33");
	if (IS_ERR(marlin_dev->avdd33))
		WCN_ERR("Get regulator of avdd33 error!\n");

	marlin_dev->dcxo18 = devm_regulator_get(&pdev->dev, "dcxo18");
	if (IS_ERR(marlin_dev->dcxo18))
		WCN_ERR("Get regulator of dcxo18 error!\n");

	marlin_dev->clk_32k = devm_clk_get(&pdev->dev, "clk_32k");
	if (IS_ERR(marlin_dev->clk_32k)) {
		WCN_ERR("can't get wcn clock dts config: clk_32k\n");
		return -1;
	}

	marlin_dev->clk_parent = devm_clk_get(&pdev->dev, "source");
	if (IS_ERR(marlin_dev->clk_parent)) {
		WCN_ERR("can't get wcn clock dts config: source\n");
		return -1;
	}
	clk_set_parent(marlin_dev->clk_32k, marlin_dev->clk_parent);

	marlin_dev->clk_enable = devm_clk_get(&pdev->dev, "enable");
	if (IS_ERR(marlin_dev->clk_enable)) {
		WCN_ERR("can't get wcn clock dts config: enable\n");
		return -1;
	}

	ret = gpio_request(marlin_dev->reset, "reset");
	if (ret)
		WCN_ERR("gpio reset request err: %d\n",
				marlin_dev->reset);

	ret = gpio_request(marlin_dev->chip_en, "chip_en");
	if (ret)
		WCN_ERR("gpio_rst request err: %d\n",
				marlin_dev->chip_en);

	ret = gpio_request(marlin_dev->int_ap, "int_ap");
	if (ret)
		WCN_ERR("gpio_rst request err: %d\n",
				marlin_dev->int_ap);

	WCN_INFO("BTWF_FIRMWARE_PATH len=%ld\n", strlen(BTWF_FIRMWARE_PATH));
	ret = of_property_read_string(np, "sprd,btwf-file-name",
				      (const char **)&marlin_dev->btwf_path);
	if (!ret) {
		WCN_INFO("btwf firmware name:%s\n", marlin_dev->btwf_path);
		strcpy(BTWF_FIRMWARE_PATH, marlin_dev->btwf_path);
		WCN_INFO("BTWG path is %s\n", BTWF_FIRMWARE_PATH);
	}

	WCN_INFO("BTWF_FIRMWARE_PATH2 len=%ld\n", strlen(BTWF_FIRMWARE_PATH));

	ret = of_property_read_string(np, "sprd,gnss-file-name",
				      (const char **)&marlin_dev->gnss_path);
	if (!ret) {
		WCN_INFO("gnss firmware name:%s\n", marlin_dev->gnss_path);
		strcpy(GNSS_FIRMWARE_PATH, marlin_dev->gnss_path);
	}

	if (of_property_read_bool(np, "sprd,no-power-off")) {
		WCN_INFO("wcn config is no power down\n");
		marlin_dev->no_power_off = true;
	}

	if (of_property_read_bool(np, "sprd,wait-ge2-disabled")) {
		WCN_INFO("this is marlin3, not need wait gps ready\n");
		marlin_dev->wait_ge2_disabled = true;
	}

	pmu_apb_gpr = syscon_regmap_lookup_by_phandle(np,
				"sprd,syscon-pmu-apb");
	if (IS_ERR(pmu_apb_gpr)) {
		WCN_ERR("%s:failed to find pmu_apb_gpr(26M)(ignore)\n",
				__func__);
		return -EINVAL;
	}
	ret = regmap_read(pmu_apb_gpr, REG_PMU_APB_XTL_WAIT_CNT0,
					&clk_wait_val);
	WCN_INFO("marlin2 clk_wait value is 0x%x\n", clk_wait_val);

	ret = of_property_read_u32(np, "sprd,reg-m2-apb-xtl-wait-addr",
			&marlin2_clk_wait_reg);
	if (ret) {
		WCN_ERR("Did not find reg-m2-apb-xtl-wait-addr\n");
		return -EINVAL;
	}
	WCN_INFO("marlin2 clk reg is 0x%x\n", marlin2_clk_wait_reg);

	return 0;
}

static int marlin_gpio_free(struct platform_device *pdev)
{
	if (!marlin_dev)
		return -1;

	gpio_free(marlin_dev->reset);
	gpio_free(marlin_dev->chip_en);
	gpio_free(marlin_dev->int_ap);

	return 0;
}

static int marlin_clk_enable(bool enable)
{
	int ret = 0;

	if (enable) {
		ret = clk_prepare_enable(marlin_dev->clk_32k);
		ret = clk_prepare_enable(marlin_dev->clk_enable);
		WCN_INFO("marlin %s successfully!\n", __func__);
	} else {
		clk_disable_unprepare(marlin_dev->clk_enable);
		clk_disable_unprepare(marlin_dev->clk_32k);
	}

	return ret;
}

static int marlin_avdd18_dcxo_enable(bool enable)
{
	int ret = 0;

	WCN_INFO("avdd18_dcxo enable 1v8 %d\n", enable);
	if (marlin_dev->dcxo18 == NULL)
		return 0;

	if (enable) {
		if (regulator_is_enabled(marlin_dev->dcxo18))
			return 0;
		regulator_set_voltage(marlin_dev->dcxo18,
					      1800000, 1800000);
		ret = regulator_enable(marlin_dev->dcxo18);
		if (ret)
			WCN_ERR("fail to enable avdd18_dcxo\n");
	} else {
		if (regulator_is_enabled(marlin_dev->dcxo18)) {
			ret = regulator_disable(marlin_dev->dcxo18);
			if (ret)
				WCN_ERR("fail to disable avdd18_dcxo\n");
		}
	}

	return ret;
}

static int marlin_digital_power_enable(bool enable)
{
	int ret = 0;

	WCN_INFO("marlin_digital_power_enable D1v2 %d\n", enable);
	if (marlin_dev->dvdd12 == NULL)
		return 0;

	if (enable) {
		/* gpio_direction_output(marlin_dev->reset, 0); */

		regulator_set_voltage(marlin_dev->dvdd12,
					      1200000, 1200000);
		ret = regulator_enable(marlin_dev->dvdd12);
	} else {
		if (regulator_is_enabled(marlin_dev->dvdd12))
			ret = regulator_disable(marlin_dev->dvdd12);
	}

	return ret;
}
static int marlin_analog_power_enable(bool enable)
{
	int ret = 0;

	if (marlin_dev->avdd12 != NULL) {
		msleep(20);
		WCN_INFO("marlin_analog_power_enable 1v2 %d\n", enable);
		if (enable) {
			regulator_set_voltage(marlin_dev->avdd12,
			1200000, 1200000);
			ret = regulator_enable(marlin_dev->avdd12);
		} else {
			if (regulator_is_enabled(marlin_dev->avdd12))
				ret =
				regulator_disable(marlin_dev->avdd12);
		}
	}

	return ret;
}

/*
 * hold cpu means cpu register is clear
 * different from reset pin gpio
 * reset gpio is all register is clear
 */
void marlin_hold_cpu(void)
{
	int ret = 0;
	unsigned int temp_reg_val;

	ret = sprdwcn_bus_reg_read(CP_RESET_REG, &temp_reg_val, 4);
	if (ret < 0) {
		WCN_ERR("%s read reset reg error:%d\n", __func__, ret);
		return;
	}
	WCN_INFO("%s reset reg val:0x%x\n", __func__, temp_reg_val);
	temp_reg_val |= 1;
	ret = sprdwcn_bus_reg_write(CP_RESET_REG, &temp_reg_val, 4);
	if (ret < 0) {
		WCN_ERR("%s write reset reg error:%d\n", __func__, ret);
		return;
	}
}

void marlin_read_cali_data(void)
{
	int err;

	WCN_INFO("marlin sync entry is_calibrated:%d\n",
		wifi_data.cali_data.cali_config.is_calibrated);

	if (!wifi_data.cali_data.cali_config.is_calibrated) {
		memset(&wifi_data.cali_data, 0x0,
			sizeof(struct wifi_cali_t));
		err = sprdwcn_bus_reg_read(CALI_OFSET_REG,
			&wifi_data.cali_data, sizeof(struct wifi_cali_t));
		if (err < 0) {
			WCN_ERR("marlin read cali data fail:%d\n", err);
			return;
		}
	}

	if ((marlin2_clk_wait_reg > 0) && (clk_wait_val > 0)) {
		sprdwcn_bus_reg_read(marlin2_clk_wait_reg,
					&cp_clk_wait_val, 4);
		WCN_INFO("marlin2 cp_clk_wait_val is 0x%x\n", cp_clk_wait_val);
		clk_wait_val = ((clk_wait_val & 0xFF00) >> 8);
		cp_clk_wait_val =
			((cp_clk_wait_val & 0xFFFFFC00) | clk_wait_val);
		WCN_INFO("marlin2 cp_clk_wait_val is modifyed 0x%x\n",
					cp_clk_wait_val);
		err = sprdwcn_bus_reg_write(marlin2_clk_wait_reg,
					       &cp_clk_wait_val, 4);
		if (err < 0)
			WCN_ERR("marlin2 write 26M error:%d\n", err);
	}

	/* write this flag to notify cp that ap read calibration data */
	reg_val = 0xbbbbbbbb;
	err = sprdwcn_bus_reg_write(CALI_REG, &reg_val, 4);
	if (err < 0) {
		WCN_ERR("marlin write cali finish error:%d\n", err);
		return;
	}

	sprdwcn_bus_runtime_get();

	complete(&marlin_dev->download_done);
}

static int marlin_write_cali_data(void)
{
	int ret = 0, init_state = 0, cali_data_offset = 0;
	int i = 0;

	WCN_INFO("tsx_dac_data:%d\n", marlin_dev->tsxcali.tsxdata.dac);
	cali_data_offset = (unsigned long)(&(marlin_dev->sync_f.tsx_dac_data))
		- (unsigned long)(&(marlin_dev->sync_f));
	WCN_INFO("cali_data_offset:0x%x\n", cali_data_offset);

	do {
		i++;
		ret = sprdwcn_bus_reg_read(SYNC_ADDR, &init_state, 4);
		if (ret < 0) {
			WCN_ERR("%s marlin3 read SYNC_ADDR error:%d\n",
				__func__, ret);
			return ret;
		}
		WCN_INFO("%s sync init_state:0x%x\n", __func__, init_state);

		if (init_state != SYNC_CALI_WAITING)
			msleep(20);
		/* wait cp in the state of waiting cali data */
		else {
			/*write cali data to cp*/
			marlin_dev->sync_f.tsx_dac_data =
					marlin_dev->tsxcali.tsxdata.dac;
			ret = sprdwcn_bus_direct_write(SYNC_ADDR +
					cali_data_offset,
					&(marlin_dev->sync_f.tsx_dac_data), 2);
			if (ret < 0) {
				WCN_ERR("write cali data error:%d\n", ret);
				return ret;
			}

			/*tell cp2 can handle cali data*/
			init_state = SYNC_CALI_WRITE_DONE;
			ret = sprdwcn_bus_reg_write(SYNC_ADDR, &init_state, 4);
			if (ret < 0) {
				WCN_ERR("write cali_done flag error:%d\n", ret);
				return ret;
			}

			i = 0;
			WCN_INFO("marlin_write_cali_data finish\n");
			return ret;
		}

		if (i > 10)
			i = 0;
	} while (i);

	return ret;

}

static int spi_read_rf_reg(unsigned int addr, unsigned int *data)
{
	unsigned int reg_data = 0;
	int ret;

	reg_data = ((addr & 0x7fff) << 16) | SPI_BIT31;
	ret = sprdwcn_bus_reg_write(SPI_BASE_ADDR, &reg_data, 4);
	if (ret < 0) {
		WCN_ERR("write SPI RF reg error:%d\n", ret);
		return ret;
	}

	usleep_range(4000, 6000);

	ret = sprdwcn_bus_reg_read(SPI_BASE_ADDR, &reg_data, 4);
	if (ret < 0) {
		WCN_ERR("read SPI RF reg error:%d\n", ret);
		return ret;
	}
	*data = reg_data & 0xffff;

	return 0;
}

static int check_cp_clock_mode(void)
{
	int ret = 0;
	unsigned int temp_val;

	WCN_INFO("%s\n", __func__);

	ret = spi_read_rf_reg(AD_DCXO_BONDING_OPT, &temp_val);
	if (ret < 0) {
		WCN_ERR("read AD_DCXO_BONDING_OPT error:%d\n", ret);
		return ret;
	}
	WCN_INFO("read AD_DCXO_BONDING_OPT val:0x%x\n", temp_val);
	if ((temp_val & tsx_mode) == tsx_mode)
		WCN_INFO("clock mode: TSX\n");
	else {
		WCN_INFO("clock mode: TCXO, outside clock\n");
		marlin_avdd18_dcxo_enable(false);
	}

	return ret;
}

/* release CPU */
static int marlin_start_run(void)
{
	int ret = 0;
	unsigned int ss_val;

	WCN_INFO("marlin_start_run\n");

	marlin_tsx_cali_data_get();
#ifdef CONFIG_WCN_SLP
	sdio_pub_int_btwf_en0();
	/* after chip power on, reset sleep status */
	slp_mgr_reset();
#endif

	ret = sprdwcn_bus_reg_read(CP_RESET_REG, &ss_val, 4);
	if (ret < 0) {
		WCN_ERR("%s read reset reg error:%d\n", __func__, ret);
		return ret;
	}
	WCN_INFO("%s read reset reg val:0x%x\n", __func__, ss_val);
	ss_val &= (~0) - 1;
	WCN_INFO("after do %s reset reg val:0x%x\n", __func__, ss_val);
	ret = sprdwcn_bus_reg_write(CP_RESET_REG, &ss_val, 4);
	if (ret < 0) {
		WCN_ERR("%s write reset reg error:%d\n", __func__, ret);
		return ret;
	}
	marlin_bootup_time_update();	/* update the time at once. */

	ret = sprdwcn_bus_reg_read(CP_RESET_REG, &ss_val, 4);
	if (ret < 0) {
		WCN_ERR("%s read reset reg error:%d\n", __func__, ret);
		return ret;
	}
	WCN_INFO("%s reset reg val:0x%x\n", __func__, ss_val);

	return ret;
}

static int check_cp_ready(void)
{
	int ret = 0;
	int i = 0;

	do {
		i++;
		ret = sprdwcn_bus_direct_read(SYNC_ADDR,
			&(marlin_dev->sync_f), sizeof(struct wcn_sync_info_t));
		if (ret < 0) {
			WCN_ERR("%s marlin3 read SYNC_ADDR error:%d\n",
				__func__, ret);
			return ret;
		}
		WCN_INFO("%s sync val:0x%x, prj_type val:0x%x\n", __func__,
				marlin_dev->sync_f.init_status,
				marlin_dev->sync_f.prj_type);
		if (marlin_dev->sync_f.init_status == SYNC_IN_PROGRESS)
			msleep(20);
		if (marlin_dev->sync_f.init_status == SYNC_ALL_FINISHED)
			i = 0;
		if (i > 4)
			i = 0;
	} while (i);

	return 0;
}
static int gnss_start_run(void)
{
	int ret = 0;
	unsigned int temp;

	WCN_INFO("gnss start run enter ");
#ifdef CONFIG_WCN_SLP
	sdio_pub_int_gnss_en0();
#endif
	ret = sprdwcn_bus_reg_read(GNSS_CP_RESET_REG, &temp, 4);
	if (ret < 0) {
		WCN_ERR("%s marlin3_gnss read reset reg error:%d\n",
			__func__, ret);
		return ret;
	}
	WCN_INFO("%s reset reg val:0x%x\n", __func__, temp);
	temp &= (~0) - 1;
	ret = sprdwcn_bus_reg_write(GNSS_CP_RESET_REG, &temp, 4);
	if (ret < 0) {
		WCN_ERR("%s marlin3_gnss write reset reg error:%d\n",
				__func__, ret);
		return ret;
	}

	return ret;
}

static int marlin_reset(int val)
{
	if (gpio_is_valid(marlin_dev->reset)) {
		gpio_direction_output(marlin_dev->reset, 0);
		mdelay(RESET_DELAY);
		gpio_direction_output(marlin_dev->reset, 1);
	}

	return 0;
}

static int chip_reset_release(int val)
{
	static unsigned int reset_count;

	if (!gpio_is_valid(marlin_dev->reset)) {
		WCN_ERR("reset gpio error\n");
		return -1;
	}
	if (val) {
		if (reset_count == 0)
			gpio_direction_output(marlin_dev->reset, 1);
		reset_count++;
	} else {
		gpio_direction_output(marlin_dev->reset, 0);
		reset_count--;
	}

	return 0;
}
void marlin_chip_en(bool enable, bool reset)
{
	static unsigned int chip_en_count;

	if (gpio_is_valid(marlin_dev->chip_en)) {
		if (reset) {
			gpio_direction_output(marlin_dev->chip_en, 0);
			WCN_INFO("marlin gnss chip en reset\n");
			msleep(100);
			gpio_direction_output(marlin_dev->chip_en, 1);
		} else if (enable) {
			if (chip_en_count == 0) {
				gpio_direction_output(marlin_dev->chip_en, 0);
				mdelay(1);
				gpio_direction_output(marlin_dev->chip_en, 1);
				mdelay(1);
				WCN_INFO("marlin chip en pull up\n");
			}
			chip_en_count++;
		} else {
			chip_en_count--;
			if (chip_en_count == 0) {
				gpio_direction_output(marlin_dev->chip_en, 0);
				WCN_INFO("marlin chip en pull down\n");
			}
		}
	}
}
EXPORT_SYMBOL_GPL(marlin_chip_en);

int set_cp_mem_status(int subsys, int val)
{
	int ret;
	unsigned int temp_val;

	return 0;

	ret = sprdwcn_bus_reg_read(REG_WIFI_MEM_CFG1, &temp_val, 4);
	if (ret < 0) {
		WCN_ERR("%s read wifimem_cfg1 error:%d\n", __func__, ret);
		return ret;
	}
	WCN_INFO("%s read btram poweron(bit22)val:0x%x\n", __func__, temp_val);

	if ((subsys == MARLIN_BLUETOOTH) && (val == 1)) {
		temp_val = temp_val & (~FORCE_SHUTDOWN_BTRAM);
		WCN_INFO("wr btram poweron(bit22) val:0x%x\n", temp_val);
		ret = sprdwcn_bus_reg_write(REG_WIFI_MEM_CFG1, &temp_val, 4);
		if (ret < 0) {
			WCN_ERR("write wifimem_cfg1 reg error:%d\n", ret);
			return ret;
		}
		return 0;
	} else if (test_bit(MARLIN_BLUETOOTH, &marlin_dev->power_state) &&
		   (subsys != MARLIN_BLUETOOTH))
		return 0;

	temp_val = temp_val | FORCE_SHUTDOWN_BTRAM;
	WCN_INFO(" shut down btram(bit22) val:0x%x\n", temp_val);
	ret = sprdwcn_bus_reg_write(REG_WIFI_MEM_CFG1, &temp_val, 4);
	if (ret < 0) {
		WCN_ERR("write wifimem_cfg1 reg error:%d\n", ret);
		return ret;
	}

	return ret;
}

int enable_spur_remove(void)
{
	int ret;
	unsigned int temp_val;

	temp_val = FM_ENABLE_SPUR_REMOVE_FREQ2_VALUE;
	ret = sprdwcn_bus_reg_write(FM_REG_SPUR_FEQ1_ADDR, &temp_val, 4);
	if (ret < 0) {
		WCN_ERR("write FM_REG_SPUR reg error:%d\n", ret);
		return ret;
	}

	return 0;
}

int disable_spur_remove(void)
{
	int ret;
	unsigned int temp_val;

	temp_val = FM_DISABLE_SPUR_REMOVE_VALUE;
	ret = sprdwcn_bus_reg_write(FM_REG_SPUR_FEQ1_ADDR, &temp_val, 4);
	if (ret < 0) {
		WCN_ERR("write disable FM_REG_SPUR reg error:%d\n", ret);
		return ret;
	}

	return 0;
}

void set_fm_supe_freq(int subsys, int val, unsigned long sub_state)
{
	switch (subsys) {
	case MARLIN_FM:
		if (test_bit(MARLIN_GNSS, &sub_state) && (val == 1))
			enable_spur_remove();
		else
			disable_spur_remove();
		break;
	case MARLIN_GNSS:
		if (test_bit(MARLIN_FM, &sub_state) && (val == 1))
			enable_spur_remove();
		else
			disable_spur_remove();
		break;
	default:
		break;
	}
}

/*
 * MARLIN_GNSS no need loopcheck action
 * MARLIN_AUTO no need loopcheck action
 */
static void power_state_notify_or_not(int subsys, int poweron)
{
	if (poweron == 1) {
		set_cp_mem_status(subsys, poweron);
		set_fm_supe_freq(subsys, poweron, marlin_dev->power_state);
	}

	if ((test_bit(MARLIN_BLUETOOTH, &marlin_dev->power_state) +
	      test_bit(MARLIN_FM, &marlin_dev->power_state) +
	      test_bit(MARLIN_WIFI, &marlin_dev->power_state) +
	      test_bit(MARLIN_MDBG, &marlin_dev->power_state)) == 1) {
		WCN_INFO("only one module open, need to notify loopcheck\n");
		marlin_dev->loopcheck_status_change = 1;
		wakeup_loopcheck_int();
	}

	if (((marlin_dev->power_state) & MARLIN_MASK) == 0) {

		WCN_INFO("marlin close, need to notify loopcheck\n");
		marlin_dev->loopcheck_status_change = 1;
		wakeup_loopcheck_int();

	}
}

static void marlin_scan_finish(void)
{
	WCN_INFO("marlin_scan_finish!\n");
	complete(&marlin_dev->carddetect_done);
}

int find_firmware_path(void)
{
	int ret;
	int pre_len;

	if (strlen(BTWF_FIRMWARE_PATH) != 0)
		return 0;

	ret = parse_firmware_path(BTWF_FIRMWARE_PATH);
	if (ret != 0) {
		WCN_ERR("can not find wcn partition\n");
		return ret;
	}
	WCN_INFO("BTWF path is %s\n", BTWF_FIRMWARE_PATH);
	pre_len = strlen(BTWF_FIRMWARE_PATH) - strlen("wcnmodem");
	memcpy(GNSS_FIRMWARE_PATH,
		BTWF_FIRMWARE_PATH,
		strlen(BTWF_FIRMWARE_PATH));
	memcpy(&GNSS_FIRMWARE_PATH[pre_len], "gnssmodem",
		strlen("gnssmodem"));
	GNSS_FIRMWARE_PATH[pre_len + strlen("gnssmodem")] = '\0';
	WCN_INFO("GNSS path is %s\n", GNSS_FIRMWARE_PATH);

	return 0;
}

static void pre_gnss_download_firmware(struct work_struct *work)
{
	static int cali_flag;
	int ret = 0;

	/* ./fstab.xxx is prevent for user space progress */
	if (marlin_dev->first_power_on_flag == 1)
		if (find_firmware_path() < 0)
			return;

	if (gnss_download_firmware() != 0) {
		WCN_ERR("gnss download firmware fail\n");
		return;
	}

	if (gnss_ops && (gnss_ops->write_data)) {
		if (gnss_ops->write_data() != 0)
			return;
	} else
		WCN_ERR("%s gnss_ops write_data error\n", __func__);

	if (gnss_start_run() != 0)
		WCN_ERR("gnss start run fail\n");

	if (cali_flag == 0) {
		WCN_INFO("gnss start to backup calidata\n");
		if (gnss_ops && gnss_ops->backup_data) {
			ret = gnss_ops->backup_data();
			if (ret == 0)
				cali_flag = 1;
		} else
			WCN_ERR("%s gnss_ops backup_data error\n", __func__);
	} else {
		WCN_INFO("gnss wait boot finish\n");
		if (gnss_ops && gnss_ops->wait_gnss_boot) {
			gnss_ops->wait_gnss_boot();
		} else
			WCN_ERR("%s gnss_ops wait boot error\n", __func__);

	}
	complete(&marlin_dev->gnss_download_done);	/* temp */

}

static void pre_btwifi_download_sdio(struct work_struct *work)
{
	if (btwifi_download_firmware() == 0 &&
		marlin_start_run() == 0) {
		check_cp_clock_mode();
		marlin_write_cali_data();
		mem_pd_save_bin();
		check_cp_ready();
		complete(&marlin_dev->download_done);
		/* wcn_debug_init(); */
	}
	sprdwcn_bus_runtime_get();
}

static void sdio_scan_card(void)
{
	init_completion(&marlin_dev->carddetect_done);
	sprdwcn_bus_rescan();
	if (wait_for_completion_timeout(&marlin_dev->carddetect_done,
		msecs_to_jiffies(CARD_DETECT_WAIT_MS)) == 0)
		WCN_ERR("wait SDIO rescan card time out\n");

}

/* for example: wifipa bound XTLEN3 */
int pmic_bound_xtl_assert(unsigned int enable)
{
	unsigned int val;

	regmap_read(reg_map, ANA_REG_GLB_LDO_XTL_EN10, &val);
	WCN_INFO("%s:%d, XTL_EN10 =0x%x\n", __func__, enable, val);
	regmap_update_bits(reg_map,
			   ANA_REG_GLB_LDO_XTL_EN10,
			   BIT_LDO_WIFIPA_EXT_XTL3_EN,
			   enable);
	regmap_read(reg_map, ANA_REG_GLB_LDO_XTL_EN10, &val);
	WCN_INFO("after XTL_EN10 =0x%x\n", val);

	return 0;
}

void wifipa_enable(int enable)
{
	int ret = -1;

	if (marlin_dev->avdd33) {
		WCN_INFO("marlin_analog_power_enable 3v3 %d\n", enable);
		msleep(20);
		if (enable) {
			if (regulator_is_enabled(marlin_dev->avdd33))
				return;
			regulator_set_voltage(marlin_dev->avdd33,
					      3300000, 3300000);
			ret = regulator_enable(marlin_dev->avdd33);
			if (ret)
				WCN_ERR("fail to enable wifipa\n");
		} else {
			if (regulator_is_enabled(marlin_dev->avdd33)) {
				ret =
				regulator_disable(marlin_dev->avdd33);
				if (ret)
					WCN_ERR("fail to disable wifipa\n");
				WCN_INFO(" wifi pa disable\n");
			}
		}
	}
}


void set_wifipa_status(int subsys, int val)
{
	if (val == 1) {
		if (((subsys == MARLIN_BLUETOOTH) || (subsys == MARLIN_WIFI)) &&
		    ((marlin_dev->power_state & 0x5) == 0)) {
			wifipa_enable(1);
			pmic_bound_xtl_assert(1);
		}

		if (((subsys != MARLIN_BLUETOOTH) && (subsys != MARLIN_WIFI)) &&
		    ((marlin_dev->power_state & 0x5) == 0)) {
			wifipa_enable(0);
			pmic_bound_xtl_assert(0);
		}

	} else {
		if (((subsys == MARLIN_BLUETOOTH) &&
		     ((marlin_dev->power_state & 0x4) == 0)) ||
		    ((subsys == MARLIN_WIFI) &&
		     ((marlin_dev->power_state & 0x1) == 0))) {
			wifipa_enable(0);
			pmic_bound_xtl_assert(0);
		}
	}
}

/*
 * RST_N (LOW)
 * VDDIO -> DVDD12/11 ->CHIP_EN ->DVDD_CORE(inner)
 * ->(>=550uS) RST_N (HIGH)
 * ->(>=100uS) ADVV12
 * ->(>=10uS)  AVDD33
 */
int chip_power_on(int subsys)
{
	marlin_avdd18_dcxo_enable(true);
	marlin_clk_enable(true);
	marlin_digital_power_enable(true);
	marlin_chip_en(true, false);
	msleep(20);
	chip_reset_release(1);
	marlin_analog_power_enable(true);
	sdio_scan_card();
	loopcheck_first_boot_set();
	chip_poweroff_deinit();
	sdio_pub_int_poweron(true);

	return 0;
}

int chip_power_off(int subsys)
{
	marlin_avdd18_dcxo_enable(false);
	marlin_clk_enable(false);
	marlin_chip_en(false, false);
	marlin_digital_power_enable(false);
	marlin_analog_power_enable(false);
	chip_reset_release(0);
	marlin_dev->wifi_need_download_ini_flag = 0;
	chip_poweroff_deinit();
	marlin_dev->power_state = 0;
	sprdwcn_bus_remove_card();
	loopcheck_first_boot_clear();
	sdio_pub_int_poweron(false);

	return 0;
}

int gnss_powerdomain_open(void)
{
	/* add by this. */
	int ret = 0, retry_cnt = 0;
	unsigned int temp;

	WCN_INFO("%s\n", __func__);

	ret = sprdwcn_bus_reg_read(CGM_GNSS_FAKE_CFG, &temp, 4);
	if (ret < 0) {
		WCN_ERR("%s read CGM_GNSS_FAKE_CFG error:%d\n", __func__, ret);
		return ret;
	}
	WCN_INFO("%s CGM_GNSS_FAKE_CFG:0x%x\n", __func__, temp);
	temp = temp & (~(CGM_GNSS_FAKE_SEL));
	ret = sprdwcn_bus_reg_write(CGM_GNSS_FAKE_CFG, &temp, 4);
	if (ret < 0) {
		WCN_ERR("write CGM_GNSS_FAKE_CFG err:%d\n", ret);
		return ret;
	}

	ret = sprdwcn_bus_reg_read(PD_GNSS_SS_AON_CFG4, &temp, 4);
	if (ret < 0) {
		WCN_ERR("%s read PD_GNSS_SS_AON_CFG4 err:%d\n", __func__, ret);
		return ret;
	}
	WCN_INFO("%s PD_GNSS_SS_AON_CFG4:0x%x\n", __func__, temp);
	temp = temp & (~(FORCE_DEEP_SLEEP));
	WCN_INFO("%s PD_GNSS_SS_AON_CFG4:0x%x\n", __func__, temp);
	ret = sprdwcn_bus_reg_write(PD_GNSS_SS_AON_CFG4, &temp, 4);
	if (ret < 0) {
		WCN_ERR("write PD_GNSS_SS_AON_CFG4 err:%d\n", ret);
		return ret;
	}

	/* wait gnss sys power on finish */
	do {
		usleep_range(3000, 6000);

		ret = sprdwcn_bus_reg_read(CHIP_SLP_REG, &temp, 4);
		if (ret < 0) {
			WCN_ERR("%s read CHIP_SLP_REG err:%d\n", __func__, ret);
			return ret;
		}

		WCN_INFO("%s CHIP_SLP_REG:0x%x\n", __func__, temp);
		retry_cnt++;
	} while ((!(temp & GNSS_SS_PWRON_FINISH)) && (retry_cnt < 3));

	return 0;
}

int gnss_powerdomain_close(void)
{
	/* add by this. */
	int ret = 0;
	unsigned int temp;

	WCN_INFO("%s\n", __func__);

	ret = sprdwcn_bus_reg_read(PD_GNSS_SS_AON_CFG4, &temp, 4);
	if (ret < 0) {
		WCN_ERR("read PD_GNSS_SS_AON_CFG4 err:%d\n", ret);
		return ret;
	}
	WCN_INFO("%s PD_GNSS_SS_AON_CFG4:0x%x\n", __func__, temp);
	temp = (temp | FORCE_DEEP_SLEEP | PD_AUTO_EN) &
		(~(CHIP_DEEP_SLP_EN));
	WCN_INFO("%s PD_GNSS_SS_AON_CFG4:0x%x\n", __func__, temp);
	ret = sprdwcn_bus_reg_write(PD_GNSS_SS_AON_CFG4, &temp, 4);
	if (ret < 0) {
		WCN_ERR("write PD_GNSS_SS_AON_CFG4 err:%d\n", ret);
		return ret;
	}

	return 0;
}

int open_power_ctl(void)
{
	marlin_dev->no_power_off = 0;
	clear_bit(WCN_AUTO, &marlin_dev->power_state);

	return 0;
}
EXPORT_SYMBOL_GPL(open_power_ctl);

static int marlin_set_power(int subsys, int val)
{
	unsigned long timeleft;

	WCN_INFO("mutex_lock\n");
	mutex_lock(&marlin_dev->power_lock);

	if (!marlin_dev->wait_ge2_disabled) {
		first_call_flag++;
		if (first_call_flag == 1) {
			WCN_INFO("(marlin2+ge2)waiting ge2 download finish\n");
			timeleft
				= wait_for_completion_timeout(
				&ge2_completion, 12*HZ);
			if (!timeleft)
				WCN_ERR("wait ge2 timeout\n");
		}
		first_call_flag = 2;
	}

	WCN_INFO("marlin power state:%lx, subsys: [%s] power %d\n",
			marlin_dev->power_state, strno(subsys), val);
	init_completion(&marlin_dev->download_done);
	init_completion(&marlin_dev->gnss_download_done);

	/*  power on */
	if (val) {
		/* 1. when the first open:
		 * `- first download gnss, and then download btwifi
		 */
		marlin_dev->first_power_on_flag++;
		if (marlin_dev->first_power_on_flag == 1) {
			WCN_INFO("the first power on start\n");
			chip_power_on(subsys);
			set_wifipa_status(subsys, val);
			set_bit(subsys, &marlin_dev->power_state);

			WCN_INFO("GNSS start to auto download\n");
			schedule_work(&marlin_dev->gnss_dl_wq);
			timeleft
				= wait_for_completion_timeout(
				&marlin_dev->gnss_download_done, 10*HZ);
			if (!timeleft) {
				WCN_ERR("GNSS download timeout\n");
				goto out;
			}
			WCN_INFO("gnss auto download finished and run ok\n");
			WCN_INFO("then marlin start to download\n");
			schedule_work(&marlin_dev->download_wq);
			timeleft = wait_for_completion_timeout(
				&marlin_dev->download_done,
				msecs_to_jiffies(POWERUP_WAIT_MS));
			if (!timeleft) {
				WCN_ERR("marlin download timeout\n");
				goto out;
			}
			marlin_dev->download_finish_flag = 1;
			WCN_INFO("then marlin download finished and run ok\n");
			marlin_dev->first_power_on_flag = 2;
			WCN_INFO("mutex_unlock\n");
			mutex_unlock(&marlin_dev->power_lock);
			power_state_notify_or_not(subsys, val);
			if (subsys == WCN_AUTO) {
				marlin_set_power(WCN_AUTO, false);
				return 0;
			}
			return 0;
		}
		/* 2. the second time, WCN_AUTO coming */
		else if (subsys == WCN_AUTO) {
			if (marlin_dev->no_power_off) {
				WCN_INFO("have power on, no action\n");
				set_wifipa_status(subsys, val);
				set_bit(subsys, &marlin_dev->power_state);
			}

			else {
				WCN_INFO("!1st,not to bkup gnss cal, no act\n");
			}
		}

		/* 3. when GNSS open,
		 *	  |- GNSS and MARLIN have power on and ready
		 */
		else if ((((marlin_dev->power_state) & AUTO_RUN_MASK) != 0)
			|| (((marlin_dev->power_state) & GNSS_MASK) != 0)) {
			WCN_INFO("GNSS and marlin have ready\n");
			if (((marlin_dev->power_state) & MARLIN_MASK) == 0)
				loopcheck_first_boot_set();
			set_wifipa_status(subsys, val);
			set_bit(subsys, &marlin_dev->power_state);

			goto check_power_state_notify;
		}
		/* 4. when GNSS close, marlin open.
		 *	  ->  subsys=gps,GNSS download
		 */
		else if (((marlin_dev->power_state) & MARLIN_MASK) != 0) {
			if ((subsys == MARLIN_GNSS) || (subsys == WCN_AUTO)) {
				WCN_INFO("BTWF ready, GPS start to download\n");
				set_wifipa_status(subsys, val);
				set_bit(subsys, &marlin_dev->power_state);
				gnss_powerdomain_open();

				schedule_work(&marlin_dev->gnss_dl_wq);
				timeleft = wait_for_completion_timeout(
					&marlin_dev->gnss_download_done, 10*HZ);
				if (!timeleft) {
					WCN_ERR("GNSS download timeout\n");
					goto out;
				}

				WCN_INFO("GNSS download finished and ok\n");

			} else {
				WCN_INFO("marlin have open, GNSS is closed\n");
				set_wifipa_status(subsys, val);
				set_bit(subsys, &marlin_dev->power_state);

				goto check_power_state_notify;
			}
		}
		/* 5. when GNSS close, marlin close.no module to power on */
		else {
			WCN_INFO("no module to power on, start to power on\n");
			chip_power_on(subsys);
			set_wifipa_status(subsys, val);
			set_bit(subsys, &marlin_dev->power_state);

			/* 5.1 first download marlin, and then download gnss */
			if ((subsys == WCN_AUTO || subsys == MARLIN_GNSS)) {
				WCN_INFO("marlin start to download\n");
				schedule_work(&marlin_dev->download_wq);
				timeleft = wait_for_completion_timeout(
					&marlin_dev->download_done,
					msecs_to_jiffies(POWERUP_WAIT_MS));
				if (!timeleft) {
					WCN_ERR("marlin download timeout\n");
					goto out;
				}
				marlin_dev->download_finish_flag = 1;

				WCN_INFO("marlin dl finished and run ok\n");

				WCN_INFO("GNSS start to download\n");
				schedule_work(&marlin_dev->gnss_dl_wq);
				timeleft = wait_for_completion_timeout(
					&marlin_dev->gnss_download_done, 10*HZ);
				if (!timeleft) {
					WCN_ERR("then GNSS download timeout\n");
					goto out;
				}
				WCN_INFO("then gnss dl finished and ok\n");

			}
			/* 5.2 only download marlin, and then
			 * close gnss power domain
			 */
			else {
				WCN_INFO("only marlin start to download\n");
				schedule_work(&marlin_dev->download_wq);
				if (wait_for_completion_timeout(
					&marlin_dev->download_done,
					msecs_to_jiffies(POWERUP_WAIT_MS))
					<= 0) {

					WCN_ERR("marlin download timeout\n");
					goto out;
				}
				marlin_dev->download_finish_flag = 1;
				WCN_INFO("BTWF download finished and run ok\n");
				gnss_powerdomain_close();
			}
		}
		/* power on together's Action */
		power_state_notify_or_not(subsys, val);

		WCN_INFO("wcn chip power on and run finish: [%s]\n",
				  strno(subsys));
	/* power off */
	} else {
		if (marlin_dev->power_state == 0) {

			goto check_power_state_notify;
		}

		if (flag_reset)
			marlin_dev->power_state = 0;

		if (marlin_dev->no_power_off) {
			if (!flag_reset) {
				if (subsys != WCN_AUTO) {
					/* in order to not download again */
					set_bit(WCN_AUTO,
						&marlin_dev->power_state);
					clear_bit(subsys,
						&marlin_dev->power_state);
				}

				MDBG_LOG("marlin reset flag_reset:%d\n",
					flag_reset);

				goto check_power_state_notify;
			}
		}

		if (!marlin_dev->download_finish_flag) {

			goto check_power_state_notify;
		}

		set_wifipa_status(subsys, val);
		clear_bit(subsys, &marlin_dev->power_state);
		if (marlin_dev->power_state != 0) {
			WCN_INFO("can not power off, other module is on\n");
			if (subsys == MARLIN_GNSS)
				gnss_powerdomain_close();

			goto check_power_state_notify;
		}

		set_cp_mem_status(subsys, val);
		set_fm_supe_freq(subsys, val, marlin_dev->power_state);
		power_state_notify_or_not(subsys, val);

		WCN_INFO("wcn chip start power off!\n");
		sprdwcn_bus_runtime_put();
		chip_power_off(subsys);
		WCN_INFO("marlin power off!\n");
		marlin_dev->download_finish_flag = 0;
		if (flag_reset)
			flag_reset = FALSE;
	} /* power off end */

	/* power on off together's Action */
	WCN_INFO("mutex_unlock\n");
	mutex_unlock(&marlin_dev->power_lock);

	return 0;

out:
	sprdwcn_bus_runtime_put();
	chip_poweroff_deinit();
	marlin_clk_enable(false);
	marlin_digital_power_enable(false);
	marlin_analog_power_enable(false);
	chip_reset_release(0);
	marlin_dev->power_state = 0;
	WCN_INFO("mutex_unlock\n");
	mutex_unlock(&marlin_dev->power_lock);

	return -1;

check_power_state_notify:
	power_state_notify_or_not(subsys, val);
	WCN_INFO("mutex_unlock\n");
	mutex_unlock(&marlin_dev->power_lock);

	return 0;
}

void marlin_power_off(enum marlin_sub_sys subsys)
{
	WCN_INFO("%s all\n", __func__);

	marlin_dev->no_power_off = false;
	set_bit(subsys, &marlin_dev->power_state);
	marlin_set_power(subsys, false);
}

int marlin_get_power(enum marlin_sub_sys subsys)
{
	if (subsys == MARLIN_ALL)
		return marlin_dev->power_state != 0;
	else
		return test_bit(subsys, &marlin_dev->power_state);
}
EXPORT_SYMBOL_GPL(marlin_get_power);

bool marlin_get_download_status(void)
{
	return marlin_dev->download_finish_flag;
}
EXPORT_SYMBOL_GPL(marlin_get_download_status);

int wcn_get_module_status_changed(void)
{
	return marlin_dev->loopcheck_status_change;
}
EXPORT_SYMBOL_GPL(wcn_get_module_status_changed);

void wcn_set_module_status_changed(bool status)
{
	marlin_dev->loopcheck_status_change = status;
}
EXPORT_SYMBOL_GPL(wcn_set_module_status_changed);

int marlin_get_module_status(void)
{
	if (test_bit(MARLIN_BLUETOOTH, &marlin_dev->power_state) ||
		test_bit(MARLIN_FM, &marlin_dev->power_state) ||
		test_bit(MARLIN_WIFI, &marlin_dev->power_state) ||
		test_bit(MARLIN_MDBG, &marlin_dev->power_state))
		return 1;
	else
		return 0;
}
EXPORT_SYMBOL_GPL(marlin_get_module_status);

int is_first_power_on(enum marlin_sub_sys subsys)
{
	if (marlin_dev->wifi_need_download_ini_flag == 1)
		return 1;	/* the first */
	else
		return 0;	/* not the first */
}
EXPORT_SYMBOL_GPL(is_first_power_on);

int cali_ini_need_download(enum marlin_sub_sys subsys)
{
	unsigned int pd_wifi_st = 0;

	pd_wifi_st = mem_pd_wifi_state();
	if ((marlin_dev->wifi_need_download_ini_flag == 1) || pd_wifi_st) {
		WCN_INFO("cali_ini_need_download return 1\n");
		return 1;	/* the first */
	} else
		return 0;	/* not the first */
}
EXPORT_SYMBOL_GPL(cali_ini_need_download);

int marlin_set_wakeup(enum marlin_sub_sys subsys)
{
	int ret = 0;	/* temp */

	return 0;
	if (unlikely(marlin_dev->download_finish_flag != true))
		return -1;

	return ret;
}
EXPORT_SYMBOL_GPL(marlin_set_wakeup);

int marlin_set_sleep(enum marlin_sub_sys subsys, bool enable)
{
	return 0;	/* temp */

	if (unlikely(marlin_dev->download_finish_flag != true))
		return -1;

	return 0;
}
EXPORT_SYMBOL_GPL(marlin_set_sleep);

int marlin_reset_reg(void)
{
	init_completion(&marlin_dev->carddetect_done);
	marlin_reset(true);
	mdelay(1);
	sprdwcn_bus_rescan();
	if (wait_for_completion_timeout(&marlin_dev->carddetect_done,
		msecs_to_jiffies(CARD_DETECT_WAIT_MS))) {
		return 0;
	}
	WCN_ERR("marlin reset reg wait scan error!\n");

	return -1;
}
EXPORT_SYMBOL_GPL(marlin_reset_reg);

int start_marlin(u32 subsys)
{
	WCN_INFO("%s [%s]\n", __func__, strno(subsys));
	if (sprdwcn_bus_get_carddump_status() != 0) {
		WCN_ERR("%s SDIO card dump\n", __func__);
		return -1;
	}

	if (get_loopcheck_status()) {
		WCN_ERR("%s loopcheck status is fail\n", __func__);
		return -1;
	}

	if (subsys == MARLIN_WIFI) {
		/* not need write cali */
		if (marlin_dev->wifi_need_download_ini_flag == 0)
			/* need write cali */
			marlin_dev->wifi_need_download_ini_flag = 1;
		else
			/* not need write cali */
			marlin_dev->wifi_need_download_ini_flag = 2;
	}
	marlin_set_power(subsys, true);

	return mem_pd_mgr(subsys, true);
}
EXPORT_SYMBOL_GPL(start_marlin);

int stop_marlin(u32 subsys)
{
	if (sprdwcn_bus_get_carddump_status() != 0) {
		WCN_ERR("%s SDIO card dump\n", __func__);
		return -1;
	}

	if (get_loopcheck_status()) {
		WCN_ERR("%s loopcheck status is fail\n", __func__);
		return -1;
	}

	mem_pd_mgr(subsys, false);
	return marlin_set_power(subsys, false);
}
EXPORT_SYMBOL_GPL(stop_marlin);



static void marlin_power_wq(struct work_struct *work)
{
	WCN_INFO("%s start\n", __func__);

	/* WCN_AUTO is for auto backup gnss cali data */
	marlin_set_power(WCN_AUTO, true);

}

static int marlin_probe(struct platform_device *pdev)
{
	struct device_node *regmap_np;
	struct platform_device *pdev_regmap = NULL;

	marlin_dev = devm_kzalloc(&pdev->dev,
			sizeof(struct marlin_device), GFP_KERNEL);
	if (!marlin_dev)
		return -ENOMEM;
	marlin_dev->write_buffer = devm_kzalloc(&pdev->dev,
			PACKET_SIZE, GFP_KERNEL);
	if (marlin_dev->write_buffer == NULL) {
		devm_kfree(&pdev->dev, marlin_dev);
		WCN_ERR("marlin_probe write buffer low memory\n");
		return -ENOMEM;
	}
	mutex_init(&(marlin_dev->power_lock));
	marlin_dev->power_state = 0;
	if (marlin_parse_dt(pdev) < 0)
		WCN_INFO("marlin2 parse_dt some para not config\n");
	if (gpio_is_valid(marlin_dev->reset))
		gpio_direction_output(marlin_dev->reset, 0);
	init_completion(&ge2_completion);
	init_completion(&marlin_dev->carddetect_done);
#ifdef CONFIG_WCN_SLP
	slp_mgr_init();
#endif
	/* register ops */
	wcn_bus_init();
	/* sdiom_init or pcie_init */
	sprdwcn_bus_preinit();
	sprdwcn_bus_register_rescan_cb(marlin_scan_finish);
	sdio_pub_int_init(marlin_dev->int_ap);
	mem_pd_init();
	proc_fs_init();
	log_dev_init();
	mdbg_atcmd_owner_init();
	wcn_op_init();
	flag_reset = 0;

	INIT_WORK(&marlin_dev->download_wq, pre_btwifi_download_sdio);
	INIT_WORK(&marlin_dev->gnss_dl_wq, pre_gnss_download_firmware);
	INIT_DELAYED_WORK(&marlin_dev->power_wq, marlin_power_wq);
	schedule_delayed_work(&marlin_dev->power_wq,
			      msecs_to_jiffies(5000));

	regmap_np = of_find_compatible_node(NULL, NULL, "sprd,pmic-glb");
	if (!regmap_np) {
		WCN_ERR("get pmic glb node fail\n");
		return -ENODEV;
	}

	pdev_regmap = of_find_device_by_node(regmap_np);
	if (!pdev_regmap) {
		of_node_put(regmap_np);
		WCN_ERR("get pmic device node fail\n");
		return -ENODEV;
	}

	reg_map = dev_get_regmap(pdev_regmap->dev.parent, NULL);
	if (!reg_map) {
		WCN_ERR("get regmap error\n");
		of_node_put(regmap_np);
		return PTR_ERR(reg_map);
	}

	WCN_INFO("marlin_probe ok!\n");

	return 0;
}

static int  marlin_remove(struct platform_device *pdev)
{
	cancel_work_sync(&marlin_dev->download_wq);
	cancel_work_sync(&marlin_dev->gnss_dl_wq);
	cancel_delayed_work_sync(&marlin_dev->power_wq);
	wcn_op_exit();
	mdbg_atcmd_owner_deinit();
	log_dev_exit();
	proc_fs_exit();
	sdio_pub_int_deinit();
	mem_pd_exit();
	sprdwcn_bus_deinit();
	if (marlin_dev->power_state != 0) {
		WCN_INFO("marlin some subsys power is on, warning!\n");
		wifipa_enable(0);
		pmic_bound_xtl_assert(0);
		marlin_chip_en(false, false);
	}
	wcn_bus_deinit();
#ifdef CONFIG_WCN_SLP
	slp_mgr_deinit();
#endif
	marlin_gpio_free(pdev);
	mutex_destroy(&marlin_dev->power_lock);
	devm_kfree(&pdev->dev, marlin_dev->write_buffer);
	devm_kfree(&pdev->dev, marlin_dev);

	WCN_INFO("marlin_remove ok!\n");

	return 0;
}

static void marlin_shutdown(struct platform_device *pdev)
{
	if (marlin_dev->power_state != 0) {
		WCN_INFO("marlin some subsys power is on, warning!\n");
		wifipa_enable(0);
		pmic_bound_xtl_assert(0);
		marlin_chip_en(false, false);
	}
	WCN_INFO("marlin_shutdown end\n");
}

static int marlin_suspend(struct device *dev)
{

	WCN_INFO("[%s]enter\n", __func__);

	return 0;
}

int marlin_reset_register_notify(void *callback_func, void *para)
{
	marlin_reset_func = (marlin_reset_callback)callback_func;
	marlin_callback_para = para;

	return 0;
}
EXPORT_SYMBOL_GPL(marlin_reset_register_notify);

int marlin_reset_unregister_notify(void)
{
	marlin_reset_func = NULL;
	marlin_callback_para = NULL;

	return 0;
}
EXPORT_SYMBOL_GPL(marlin_reset_unregister_notify);

static int marlin_resume(struct device *dev)
{
	WCN_INFO("[%s]enter\n", __func__);

	return 0;
}

static const struct dev_pm_ops marlin_pm_ops = {
	.suspend = marlin_suspend,
	.resume	= marlin_resume,
};

static const struct of_device_id marlin_match_table[] = {
	{.compatible = "sprd,marlin2",},
	{.compatible = "sprd,marlin3",},
	{ },
};

static struct platform_driver marlin_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "marlin",
		.pm = &marlin_pm_ops,
		.of_match_table = marlin_match_table,
	},
	.probe = marlin_probe,
	.remove = marlin_remove,
	.shutdown = marlin_shutdown,
};

static int __init marlin_init(void)
{
	WCN_INFO("marlin_init entry!\n");

	return platform_driver_register(&marlin_driver);
}
late_initcall(marlin_init);

static void __exit marlin_exit(void)
{
	WCN_INFO("marlin_exit entry!\n");

	platform_driver_unregister(&marlin_driver);
}
module_exit(marlin_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Spreadtrum  WCN Marlin Driver");
MODULE_AUTHOR("Yufeng Yang <yufeng.yang@spreadtrum.com>");
