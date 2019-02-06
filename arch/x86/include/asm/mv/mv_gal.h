/* ----------------------------------------------------------------------------
 *  Copyright (C) 2015 Intel Corporation

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License Version 2
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  You should have received a copy of the GNU General Public License Version 2
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.

  ---------------------------------------------------------------------------*/

/*
 * NOTES:
 * 1) This source file is included in guests including Linux and purposely
 * kept in line with Linux kernel coding guidelines for ease of portability and
 * maintainability. See linux/Documentation/CodingStyle for coding guidelines.
 * Please check all further changes are compliant with Linux coding standard
 * and clear all commands reported by Linux checkpatch.pl
 * Use command: linux/scripts/checkpatch.pl -f <filename>
 * Clear ALL warnings and errors reported.
 *
*/

#ifndef _MV_GAL_H
#define _MV_GAL_H

#ifdef __KERNEL__
#include <linux/interrupt.h>
#endif

#include "mv_hypercalls.h"

enum boot_mode {
	ENUM_BOOT_MODE_POWER_OFF = 1,
	ENUM_BOOT_MODE_RECOVERY,
	ENUM_BOOT_MODE_FASTBOOT,
	ENUM_BOOT_MODE_NORMAL,
	ENUM_BOOT_MODE_ALARM,
	ENUM_BOOT_MODE_SLEEP,
	ENUM_BOOT_MODE_SPECIAL,
	ENUM_BOOT_MODE_CALIBRATION,
	ENUM_BOOT_MODE_AUTODLOADER,
	ENUM_BOOT_MODE_IQMODE,
	ENUM_BOOT_MODE_SPRDISK,
	ENUM_BOOT_MODE_NORMAL2,
	ENUM_BOOT_MODE_SYS_CRASH,
	ENUM_BOOT_MODE_SHUT_DOWN
};

/*
 * VMM initialization for primary and secondary
 */
int mv_init(void);
int mv_init_secondary(void);

/********************************************************************
 * VMM adaptation layer initialization. should be called once at system start up
 ********************************************************************/
void mv_gal_init(struct mv_shared_data *data);

/********************************************************************
 * Returns OS ID of the guest
 ********************************************************************/
uint32_t mv_gal_os_id(void);

/********************************************************************
 * VMM adaptation physical/virtual memory translation.
 ********************************************************************/
void *mv_gal_ptov(mv_paddr_t paddr);
mv_paddr_t mv_gal_vtop(void *vaddr);

/********************************************************************
 * VMM vlink lookup by name
 ********************************************************************/
mv_paddr_t mv_gal_vlink_lookup(const char *name, mv_paddr_t plnk);

/********************************************************************
 * adaption for os memalloc
 ********************************************************************/
void *mv_gal_os_memalloc(uint32_t size);
void mv_gal_os_memfree(void *pmem);

/********************************************************************
 * attach/detach HIRQ callback.
 ********************************************************************/
#ifdef __KERNEL__
void *mv_gal_register_hirq_callback(uint32_t hirq,
				    irq_handler_t cb, void *cookie);
#else
void *mv_gal_register_hirq_callback(uint32_t hirq,
				    void (*cb)(void *, uint32_t),
				    void *cookie);
#endif

void mv_gal_hirq_detach(void *id);

int mv_map_vcpu_shmem(void);

/********************************************************************
 * Get per VCPU-Mobilevisor shared data
 ********************************************************************/
struct mv_shared_data *mv_gal_get_shared_data(void);

/********************************************************************
 * print to mv log and loops
 ********************************************************************/
void mv_gal_panic(char *panic_msg);

/********************************************************************
 * adaption for os memalloc
 ********************************************************************/
void *mv_gal_os_memalloc(uint32_t size);
void mv_gal_os_memfree(void *pmem);

/********************************************************************
 * adaption for os mutex
 * init should allocate memory
 * return:   0 success
 *            -1 fail
 * how to use:
 * void *mutex;
 * mv_gal_mutex_init(&mutex);
 * mv_gal_mutex_obtain(mutex);
 * mv_gal_mutex_release(mutex);
 * mv_gal_mutex_delete(mutex);
 ********************************************************************/
int32_t mv_gal_mutex_init(void **mutex, char *name);
int32_t mv_gal_mutex_obtain(void *mutex);
int32_t mv_gal_mutex_release(void *mutex);
int32_t mv_gal_mutex_delete(void *mutex);

/********************************************************************
 * adaption for os semaphore
 * init should allocate memory
 * return:   0 success
 *            -1 fail
 * how to use:
 * void *sem;
 * mv_gal_sem_init(&sem);
 * mv_gal_sem_obtain(sem);
 * mv_gal_sem_release(sem);
 * mv_gal_sem_delete(sem);
 ********************************************************************/
int32_t mv_gal_sem_init(void **sem, char *name);
int32_t mv_gal_sem_obtain(void *sem);
int32_t mv_gal_sem_release(void *sem);
int32_t mv_gal_sem_delete(void *sem);

/********************************************************************
 * adaption for os thread create
 * will allocate memory thread ctrl
 * return:   0 success
 *            -1 fail
 ********************************************************************/
int32_t mv_gal_thread_create(char *name, uint8_t *stack, uint32_t stack_size,
			     void (*fn)(void *), void *cookie);

#endif				/* _MV_GAL_H */
