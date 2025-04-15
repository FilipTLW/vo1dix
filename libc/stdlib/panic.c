#include <stdlib.h>

void panic(const char *msg) {
  #if defined(__is_libk)
  printf("kernel: panic: %s\n", msg);
  asm volatile("hlt");
  #endif
}