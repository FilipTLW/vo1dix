#include <kernel/tty.h>
#include <kernel/init.h>

/**
* Entry point for the kernel, called by the bootloader.
*/
void kernel_main(void) {
  /* Initialize terminal interface */
  terminal_initialize();

  /* Initialize architecture specific stuff */
  arch_init();
}
