#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x289c2d83, "module_layout" },
	{ 0xf41abcfa, "single_release" },
	{ 0xc380a262, "seq_read" },
	{ 0x7cc7ca6c, "seq_lseek" },
	{ 0xe268034e, "remove_proc_entry" },
	{ 0xd2b9b590, "proc_create" },
	{ 0xecc9cdd8, "printk" },
	{ 0x477493c2, "seq_printf" },
	{ 0x40c7247c, "si_meminfo" },
	{ 0xfcd9bb7b, "single_open" },
	{ 0xbdfb6dbb, "__fentry__" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

