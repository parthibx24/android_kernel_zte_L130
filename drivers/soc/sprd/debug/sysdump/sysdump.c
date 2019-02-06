/*
 * Copyright (C) 2013 Spreadtrum Communications Inc.
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

#include <asm/cacheflush.h>
#include <linux/delay.h>
#include <linux/elf.h>
#include <linux/elfcore.h>
#include <linux/highuid.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/proc_fs.h>
#include <linux/reboot.h>
#include <linux/rtc.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/sysctl.h>
#include <linux/sysrq.h>
#include <linux/time.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#ifdef CONFIG_SPRD_SIPC
#include <linux/sipc.h>
#endif

#include "sysdump.h"

#ifdef CONFIG_OF
#include <linux/of_address.h>
#include <linux/of_device.h>
#endif

#include <linux/crypto.h>
#include <crypto/sha.h>
#include <linux/scatterlist.h>
#include <asm/sections.h>

#define CORE_STR	"CORE"
#ifndef ELF_CORE_EFLAGS
#define ELF_CORE_EFLAGS	0
#endif

#define SYSDUMP_MAGIC	"SPRD_SYSDUMP_119"

#define SYSDUMP_NOTE_BYTES (ALIGN(sizeof(struct elf_note), 4) +   \
			    ALIGN(sizeof(CORE_STR), 4) + \
			    ALIGN(sizeof(struct elf_prstatus), 4))

#define DUMP_REGS_SIZE min(sizeof(elf_gregset_t), sizeof(struct pt_regs))

typedef char note_buf_t[SYSDUMP_NOTE_BYTES];

note_buf_t __percpu *crash_notes;

/* An ELF note in memory */
struct memelfnote {
	const char *name;
	int type;
	unsigned int datasz;
	void *data;
};

struct sysdump_info {
	char magic[16];
	char time[32];
	char reason[32];
	char dump_path[128];
	int elfhdr_size;
	int mem_num;
	unsigned long dump_mem_paddr;
	int crash_key;
};

struct sysdump_extra {
	int enter_id;
	int enter_cpu;
	char reason[256];
	struct pt_regs cpu_context[CONFIG_NR_CPUS];
};

struct sysdump_config {
	int enable;
	int crashkey_only;
	int dump_modem;
	int reboot;
	char dump_path[128];
};

static struct sysdump_info *sprd_sysdump_info = NULL;
static unsigned long sysdump_magic_paddr = 0;

/* global var for memory hash */
static u8 g_ktxt_hash_data[SHA1_DIGEST_SIZE];
static struct scatterlist sg;
static struct hash_desc desc;

/* must be global to let gdb know */
struct sysdump_extra sprd_sysdump_extra = {
	.enter_id = -1,
	.enter_cpu = -1,
	.reason = {0},
};

static struct sysdump_config sysdump_conf = {
	.enable = 1,
	.crashkey_only = 0,
	.dump_modem = 1,
	.reboot = 1,
	.dump_path = "",
};

static int sprd_sysdump_init;

extern int sysdump_status;
extern void sprd_set_reboot_mode(const char *cmd);
extern void set_sysdump_enable(int on);

#ifdef CONFIG_SPRD_WATCHDOG_SYS
extern void sysdump_enable_watchdog(int on);
#else
#define sysdump_enable_watchdog(on) do { } while (0)
#endif

void sprd_debug_check_crash_key(unsigned int code, int value)
{
	static bool volup_p;
	static bool voldown_p;
	static int loopcount;
	static int vol_pressed;

#if 0
	/* Must be deleted later */
	pr_info("Test %s:key code(%d) value(%d),(up:%d,down:%d)\n", __func__,
		code, value, volup_p, voldown_p);
#endif

	/* Enter Force Upload
	 *  Hold volume down key first
	 *  and then press power key twice
	 *  and volume up key should not be pressed
	 */
	if (value) {
		if (code == KEY_VOLUMEUP)
			volup_p = true;
		if (code == KEY_VOLUMEDOWN)
			voldown_p = true;
		if ((!vol_pressed) && volup_p && voldown_p)
			vol_pressed = jiffies_to_msecs(jiffies);
		if (volup_p && voldown_p) {
			static unsigned long stack_dump_jiffies = 0;

			if (!stack_dump_jiffies
			    || jiffies > stack_dump_jiffies + HZ * 10)
				stack_dump_jiffies = jiffies;
			if (code == KEY_POWER) {
				pr_info("%s: Crash key count : %d\n", __func__,
					++loopcount);
				//if (loopcount == 2)
				//panic("Crash Key");
				if ((jiffies_to_msecs(jiffies) - vol_pressed) <=
				    5000) {
					if (loopcount == 2)
						panic("Crash Key");
				} else {
					volup_p = false;
					voldown_p = false;
					loopcount = 0;
					vol_pressed = 0;
				}
			}
		}
	} else {
		if (code == KEY_VOLUMEUP)
			volup_p = false;
		if (code == KEY_VOLUMEDOWN) {
			loopcount = 0;
			voldown_p = false;
		}
	}
}

static char *storenote(struct memelfnote *men, char *bufp)
{
	struct elf_note en;

#define DUMP_WRITE(addr, nr) do {memcpy(bufp, addr, nr); bufp += nr; } while (0)

	en.n_namesz = strlen(men->name) + 1;
	en.n_descsz = men->datasz;
	en.n_type = men->type;

	DUMP_WRITE(&en, sizeof(en));
	DUMP_WRITE(men->name, en.n_namesz);

	/* XXX - cast from long long to long to avoid need for libgcc.a */
	bufp = (char *)roundup((unsigned long)bufp, 4);
	DUMP_WRITE(men->data, men->datasz);
	bufp = (char *)roundup((unsigned long)bufp, 4);

#undef DUMP_WRITE

	return bufp;
}

/*
 * fill up all the fields in prstatus from the given task struct, except
 * registers which need to be filled up separately.
 */
static void fill_prstatus(struct elf_prstatus *prstatus,
			  struct task_struct *p, long signr)
{
	prstatus->pr_info.si_signo = prstatus->pr_cursig = signr;
	prstatus->pr_sigpend = p->pending.signal.sig[0];
	prstatus->pr_sighold = p->blocked.sig[0];
	rcu_read_lock();
	prstatus->pr_ppid = task_pid_vnr(rcu_dereference(p->real_parent));
	rcu_read_unlock();
	prstatus->pr_pid = task_pid_vnr(p);
	prstatus->pr_pgrp = task_pgrp_vnr(p);
	prstatus->pr_sid = task_session_vnr(p);
	if (0 /* thread_group_leader(p) */ ) {
		struct task_cputime cputime;

		/*
		 * This is the record for the group leader.  It shows the
		 * group-wide total, not its individual thread total.
		 */
		/* thread_group_cputime(p, &cputime); */
		cputime_to_timeval(cputime.utime, &prstatus->pr_utime);
		cputime_to_timeval(cputime.stime, &prstatus->pr_stime);
	} else {
		cputime_to_timeval(p->utime, &prstatus->pr_utime);
		cputime_to_timeval(p->stime, &prstatus->pr_stime);
	}
	cputime_to_timeval(p->signal->cutime, &prstatus->pr_cutime);
	cputime_to_timeval(p->signal->cstime, &prstatus->pr_cstime);
}

void crash_note_save_cpu(struct pt_regs *regs, int cpu)
{
	struct elf_prstatus prstatus;
	struct memelfnote notes;

	notes.name = CORE_STR;
	notes.type = NT_PRSTATUS;
	notes.datasz = sizeof(struct elf_prstatus);
	notes.data = &prstatus;

	memset(&prstatus, 0, sizeof(struct elf_prstatus));
	fill_prstatus(&prstatus, current, 0);
	memcpy(&prstatus.pr_reg, regs, DUMP_REGS_SIZE);
	/* memcpy(&prstatus.pr_reg, regs, sizeof(struct pt_regs)); */
	storenote(&notes, (char *)per_cpu_ptr(crash_notes, cpu));
}

static void sysdump_fill_core_hdr(struct pt_regs *regs, char *bufp)
{
	struct elf_phdr *nhdr;

	/* setup ELF header */
	bufp += sizeof(struct elfhdr);

	/* setup ELF PT_NOTE program header */
	nhdr = (struct elf_phdr *)bufp;
	memset(nhdr, 0, sizeof(struct elf_phdr));
	nhdr->p_memsz = SYSDUMP_NOTE_BYTES * NR_CPUS;

	return;
}

static int __init sysdump_magic_setup(char *str)
{
	if (str != NULL)
		sscanf(&str[0], "%lx", &sysdump_magic_paddr);

	pr_emerg("sysdump: [%s]SYSDUMP paddr from uboot: 0x%lx\n",
		 __func__, sysdump_magic_paddr);
	return 1;
}

__setup("sysdump_magic=", sysdump_magic_setup);

static unsigned long get_sprd_sysdump_info_paddr(void)
{
	struct device_node *node;
	unsigned long *magic_addr;
	unsigned long reg_phy = 0;
	int aw = 0, len = 0;

	if (sysdump_magic_paddr)
		reg_phy = sysdump_magic_paddr;
	else {
		pr_emerg
		    ("Not find sysdump_magic_paddr from bootargs,use sysdump node from dts\n");
		node = of_find_node_by_name(NULL, "sprd-sysdump");

		if (!node) {
			pr_emerg
			    ("Not find sprd-sysdump node from dts,use SPRD_SYSDUMP_MAGIC\n");
			reg_phy = SPRD_SYSDUMP_MAGIC;
		} else {
			magic_addr =
			    (unsigned long *)of_get_property(node, "magic-addr",
							     &len);
			if (!magic_addr) {
				pr_emerg
				    ("Not find magic-addr property from sprd-sysdump node\n");
				reg_phy = SPRD_SYSDUMP_MAGIC;
			} else {
				aw = of_n_addr_cells(node);
				reg_phy =
				    of_read_ulong((const __be32 *)magic_addr,
						  aw);
			}
		}
	}
	return reg_phy;
}

static void sysdump_prepare_info(int enter_id, const char *reason,
				 struct pt_regs *regs)
{
	struct timex txc;
	struct rtc_time tm;

	strncpy(sprd_sysdump_extra.reason,
		reason, sizeof(sprd_sysdump_extra.reason)-1);
	sprd_sysdump_extra.enter_id = enter_id;
	memcpy(sprd_sysdump_info->magic, SYSDUMP_MAGIC,
	       sizeof(sprd_sysdump_info->magic));

	if (reason != NULL && !strcmp(reason, "Crash Key"))
		sprd_sysdump_info->crash_key = 1;
	else
		sprd_sysdump_info->crash_key = 0;

	pr_emerg("reason: %s, sprd_sysdump_info->crash_key: %d\n",
		 reason, sprd_sysdump_info->crash_key);
	do_gettimeofday(&(txc.time));
	txc.time.tv_sec -= sys_tz.tz_minuteswest * 60;
	rtc_time_to_tm(txc.time.tv_sec, &tm);
	sprintf(sprd_sysdump_info->time, "%04d-%02d-%02d_%02d:%02d:%02d",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
		tm.tm_min, tm.tm_sec);

	memcpy(sprd_sysdump_info->dump_path, sysdump_conf.dump_path,
	       sizeof(sprd_sysdump_info->dump_path));

	sysdump_fill_core_hdr(regs,
			      (char *)sprd_sysdump_info +
			      sizeof(*sprd_sysdump_info));
	return;
}

DEFINE_PER_CPU(struct sprd_debug_core_t, sprd_debug_core_reg);
DEFINE_PER_CPU(struct sprd_debug_mmu_reg_t, sprd_debug_mmu_reg);

static inline void sprd_debug_save_context(void)
{
	unsigned long flags;
	local_irq_save(flags);
	sprd_debug_save_mmu_reg(&per_cpu
				(sprd_debug_mmu_reg, smp_processor_id()));
	sprd_debug_save_core_reg(&per_cpu
				 (sprd_debug_core_reg, smp_processor_id()));

	pr_emerg("(%s) context saved(CPU:%d)\n", __func__, smp_processor_id());
	local_irq_restore(flags);

	flush_cache_all();
}


void sysdump_enter(int enter_id, const char *reason, struct pt_regs *regs)
{
	struct pt_regs *pregs;

	if (!sysdump_conf.enable)
		return;

	if (sysdump_conf.crashkey_only) {
		if (strcmp(reason, "Crash Key")) {
			pr_emerg("SYSDUMP: crashkey mode, reason %s\n", reason);
			return;
		}
	}

	bust_spinlocks(1);
	if (sprd_sysdump_init == 0) {
		unsigned long sprd_sysdump_info_paddr;
		sprd_sysdump_info_paddr = get_sprd_sysdump_info_paddr();
		if (!sprd_sysdump_info_paddr) {
			pr_emerg("get sprd_sysdump_info_paddr failed2.\n");
			while (1) {
				pr_emerg("sprd_sysdump_info_paddr failed...\n");
				mdelay(3000);
			}
		}

		sprd_sysdump_info = (struct sysdump_info *)phys_to_virt(sprd_sysdump_info_paddr);
		pr_emerg("vaddr is %p, paddr is %p.\n", sprd_sysdump_info, (void *)sprd_sysdump_info_paddr);

		crash_notes = alloc_percpu(note_buf_t);
		if (crash_notes == NULL) {
			pr_emerg("alloc_percpu failed.\n");
			while (1) {
				pr_emerg("alloc_percpu failed...\n");
				mdelay(3000);
			}
		}
	}

	/* this should before smp_send_stop() to make sysdump_ipi enable */
	sprd_sysdump_extra.enter_cpu = smp_processor_id();

	pregs = &sprd_sysdump_extra.cpu_context[sprd_sysdump_extra.enter_cpu];
	if (regs)
		memcpy(pregs, regs, sizeof(*regs));
	else
		crash_setup_regs((struct pt_regs *)pregs, NULL);

	crash_note_save_cpu(pregs, sprd_sysdump_extra.enter_cpu);
	sprd_debug_save_context();

#ifdef CONFIG_SPRD_SIPC
	if (!(reason != NULL && strstr(reason, "cpcrash")))
		smsg_senddie(SIPC_ID_LTE);
#endif

	smp_send_stop();
	mdelay(1000);

	pr_emerg("\n");
	pr_emerg("*****************************************************\n");
	pr_emerg("*                                                   *\n");
	pr_emerg("*  Sysdump enter, preparing debug info to dump ...  *\n");
	pr_emerg("*                                                   *\n");
	pr_emerg("*****************************************************\n");
	pr_emerg("\n");

	sysdump_prepare_info(enter_id, reason, regs);

	pr_emerg("KTXT VERIFY...\n");
	crypto_hash_update(&desc, &sg, _etext-_stext);
	crypto_hash_final(&desc, g_ktxt_hash_data);

	pr_emerg("KTXT [0x%lx--0x%lx]\n",
		(unsigned long)_stext, (unsigned long)_etext);
	pr_emerg("SHA1:\n");
	pr_emerg("%x %x %x %x %x\n",
			*((unsigned int *)g_ktxt_hash_data+0),
			*((unsigned int *)g_ktxt_hash_data+1),
			*((unsigned int *)g_ktxt_hash_data+2),
			*((unsigned int *)g_ktxt_hash_data+3),
			*((unsigned int *)g_ktxt_hash_data+4));

	pr_emerg("\n");
	pr_emerg("*****************************************************\n");
	pr_emerg("*                                                   *\n");
	pr_emerg("*  Try to reboot system ...                         *\n");
	pr_emerg("*                                                   *\n");
	pr_emerg("*****************************************************\n");
	pr_emerg("\n");

	flush_cache_all();
	mdelay(1000);

	bust_spinlocks(0);

#ifdef CONFIG_SPRD_DEBUG
	if (reason != NULL && strstr(reason, "Watchdog detected hard LOCKUP"))
		while (1)
			;
#endif

	if (reason != NULL && strstr(reason, "tospanic")) {
		machine_restart("tospanic");
		return;
	}
#ifdef CONFIG_X86_64
	if (!is_x86_mobilevisor())
#endif
	{
		machine_restart("panic");
	}
	return;
}

void sysdump_ipi(struct pt_regs *regs)
{
	int cpu = smp_processor_id();

	if (sprd_sysdump_extra.enter_cpu != -1) {
		memcpy((void *)&(sprd_sysdump_extra.cpu_context[cpu]),
		       (void *)regs, sizeof(struct pt_regs));
		crash_note_save_cpu(regs, cpu);
		sprd_debug_save_context();
	}
	return;
}

static void sysdump_event(struct input_handle *handle,
	unsigned int type, unsigned int code, int value)
{
	if (type == EV_KEY && code != BTN_TOUCH)
		sprd_debug_check_crash_key(code, value);
}

static const struct input_device_id sysdump_ids[] = {
	{
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_KEY) },
	},
	{},
};

static int sysdump_connect(struct input_handler *handler,
			 struct input_dev *dev,
			 const struct input_device_id *id)
{
	struct input_handle *sysdump_handle;
	int error;

	sysdump_handle = (struct input_handle *)kzalloc(sizeof(struct input_handle), GFP_KERNEL);
	if (!sysdump_handle)
		return -ENOMEM;

	sysdump_handle->dev = dev;
	sysdump_handle->handler = handler;
	sysdump_handle->name = "sysdump";

	error = input_register_handle(sysdump_handle);
	if (error) {
		pr_emerg("Failed to register input sysrq handler, error %d\n",
			error);
		goto err_free;
	}

	error = input_open_device(sysdump_handle);
	if (error) {
		pr_emerg("Failed to open input device, error %d\n", error);
		goto err_unregister;
	}

	return 0;

 err_unregister:
	input_unregister_handle(sysdump_handle);
 err_free:
	return error;
}

static void sysdump_disconnect(struct input_handle *handle)
{
	input_close_device(handle);
	input_unregister_handle(handle);
}

static int sprd_sysdump_read(struct seq_file *s, void *v)
{
	seq_printf(s, "sysdump_status = %d\n", sysdump_status);
	return 0;
}

static int sprd_sysdump_open(struct inode *inode, struct file *file)
{
	return single_open(file, sprd_sysdump_read, NULL);
}


static ssize_t sprd_sysdump_write(struct file *file, const char __user *buf,
				size_t count, loff_t *data)
{
	char sysdump_buf[5] = {0};

	pr_emerg("sprd_sysdump_write: start!!!\n");
	if (count) {
		if (copy_from_user(sysdump_buf, buf, count)) {
			pr_emerg("sprd_sysdump_write: copy_from_user failed!!!\n");
			return -1;
		}
		sysdump_buf[count] = '\0';

		if (!strncmp(sysdump_buf, "on", 2)) {
			pr_emerg("sprd_sysdump_write: enable user version sysdump!!!\n");
			sysdump_status = 1;
			sprd_set_reboot_mode("dumpenable");
			set_sysdump_enable(1);
			sysdump_enable_watchdog(0);
		} else if (!strncmp(sysdump_buf, "off", 3)) {
			pr_emerg("sprd_sysdump_write: disable user version sysdump!!!\n");
			sysdump_status = 0;
			sprd_set_reboot_mode("dumpdisable");
			set_sysdump_enable(0);
			sysdump_enable_watchdog(1);
		}
	}

	pr_emerg("sprd_sysdump_write: end!!!\n");
	return count;
}


static struct ctl_table sysdump_sysctl_table[] = {
	{
	 .procname = "sysdump_enable",
	 .data = &sysdump_conf.enable,
	 .maxlen = sizeof(int),
	 .mode = 0644,
	 .proc_handler = proc_dointvec,
	 },
	{
	 .procname = "sysdump_crashkey_only",
	 .data = &sysdump_conf.crashkey_only,
	 .maxlen = sizeof(int),
	 .mode = 0644,
	 .proc_handler = proc_dointvec,
	 },
	{
	 .procname = "sysdump_dump_modem",
	 .data = &sysdump_conf.dump_modem,
	 .maxlen = sizeof(int),
	 .mode = 0644,
	 .proc_handler = proc_dointvec,
	 },
	{
	 .procname = "sysdump_reboot",
	 .data = &sysdump_conf.reboot,
	 .maxlen = sizeof(int),
	 .mode = 0644,
	 .proc_handler = proc_dointvec,
	 },
	{
	 .procname = "sysdump_dump_path",
	 .data = sysdump_conf.dump_path,
	 .maxlen = sizeof(sysdump_conf.dump_path),
	 .mode = 0644,
	 .proc_handler = proc_dostring,
	 },
	{}
};

static struct ctl_table sysdump_sysctl_root[] = {
	{
	 .procname = "kernel",
	 .mode = 0555,
	 .child = sysdump_sysctl_table,
	 },
	{}
};

static struct ctl_table_header *sysdump_sysctl_hdr;

static struct input_handler sysdump_handler = {
	.event = sysdump_event,
	.connect	= sysdump_connect,
	.disconnect	= sysdump_disconnect,
	.name = "sysdump_crashkey",
	.id_table	= sysdump_ids,
};

static const struct file_operations sysdump_proc_fops = {
	.owner = THIS_MODULE,
	.open = sprd_sysdump_open,
	.read = seq_read,
	.write = sprd_sysdump_write,
	.llseek = seq_lseek,
	.release = single_release,
};

int sysdump_sysctl_init(void)
{
	/*get_sprd_sysdump_info_paddr(); */
	unsigned long sprd_sysdump_info_paddr;
	struct proc_dir_entry *sysdump_proc;

	sprd_sysdump_info_paddr = get_sprd_sysdump_info_paddr();
	if (!sprd_sysdump_info_paddr)
		pr_emerg("get sprd_sysdump_info_paddr failed.\n");
	sprd_sysdump_info = (struct sysdump_info *)
	    phys_to_virt(sprd_sysdump_info_paddr);
	pr_emerg("vaddr is %p,paddr is %p\n",
		 sprd_sysdump_info, (void *)sprd_sysdump_info_paddr);

	sysdump_sysctl_hdr =
	    register_sysctl_table((struct ctl_table *)sysdump_sysctl_root);
	if (!sysdump_sysctl_hdr)
		return -ENOMEM;

	crash_notes = alloc_percpu(note_buf_t);
	if (crash_notes == NULL)
		return -ENOMEM;
	if (input_register_handler(&sysdump_handler))
		pr_emerg("regist sysdump_handler failed.\n");

	sysdump_proc = proc_create("sprd_sysdump", S_IWUSR | S_IRUSR, NULL, &sysdump_proc_fops);
	if (!sysdump_proc)
		return -ENOMEM;

	sprd_sysdump_init = 1;

	memset(g_ktxt_hash_data, 0x55, SHA1_DIGEST_SIZE);
	sg_init_one(&sg, _stext, _etext-_stext);
	desc.tfm = crypto_alloc_hash("sha1", 0, CRYPTO_ALG_ASYNC);
	crypto_hash_init(&desc);

	return 0;
}

void sysdump_sysctl_exit(void)
{
	if (sysdump_sysctl_hdr)
		unregister_sysctl_table(sysdump_sysctl_hdr);
	input_unregister_handler(&sysdump_handler);
	remove_proc_entry("sprd_sysdump", NULL);
	crypto_free_hash(desc.tfm);
}

module_init(sysdump_sysctl_init);
module_exit(sysdump_sysctl_exit);

MODULE_AUTHOR("Jianjun.He <jianjun.he@spreadtrum.com>");
MODULE_DESCRIPTION("kernel core dump for Spreadtrum");
MODULE_LICENSE("GPL");
