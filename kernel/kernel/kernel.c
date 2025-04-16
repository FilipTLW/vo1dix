#include <kernel/tty.h>
#include <kernel/init.h>
#include <stdio.h>

/**
* Entry point for the kernel, called by the bootloader.
*/
void kernel_main(void *info) {
  /* Initialize terminal interface */
  terminal_initialize();

  /* Initialize architecture specific stuff */
  arch_init(info);
}
