#include <kernel/tty.h>
#include <kernel/init.h>
#include <kernel/debug.h>
#include <sys/io.h>

/**
* Entry point for the kernel, called by the bootloader.
*/
void kernel_main(void *info) {
	arch_early_init(info);
	kdbg_init();

	/* Initialize terminal interface */
	terminal_initialize();

	/* Initialize architecture specific stuff */
	arch_init(info);

	kdbg_log("kernel", "vo1dix kernel initialzed.");
}
