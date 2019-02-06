/*
 * Copyright (C) 2016 Spreadtrum Communications Inc.
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

#ifndef _LINUX_COMPAT_SPRD_ION_H
#define _LINUX_COMPAT_SPRD_ION_H

int compat_get_custom_data(unsigned int cmd,
			   void __user *data32,
			   void __user **data);

int compat_put_custom_data(unsigned int cmd,
			   void __user *data32,
			   void __user *data);

#endif /* _LINUX_COMPAT_SPRD_ION_H */
