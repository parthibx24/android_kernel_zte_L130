/*
 * Copyright (C) 2017-2018 Spreadtrum Communications Inc.
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

#ifndef _ISP_PATH_H_
#define _ISP_PATH_H_


int isp_cfg_ctx_fetch_info(struct isp_pipe_context *pctx);
int isp_cfg_path(struct isp_path_desc *path);


int isp_set_path(struct isp_path_desc *path);

int isp_path_set_fetch_frm(
		struct isp_pipe_context *pctx,
		struct camera_frame *frame,
		struct img_addr *fetch_addr);

int isp_path_set_store_frm(
		struct isp_path_desc *path,
		struct camera_frame *frame);

#endif
