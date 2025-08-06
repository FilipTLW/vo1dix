#ifndef _KERNEL_DEBUG_H
#define _KERNEL_DEBUG_H

void kdbg_init();
void kdbg_write(const char *restrict, ...);

#define kdbg_log(SUBSYSTEM, FORMAT, ...) \
	kdbg_write("kdbg [" SUBSYSTEM "]: " FORMAT "\n", ## __VA_ARGS__)

#endif
