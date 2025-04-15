#include <stdlib.h>

__attribute__((__noreturn__))
void panic(const char *msg) {
  #if defined(__is_libk)
  printf("kernel: panic: %s\n", msg);
  asm volatile("hlt");
  #endif
  while (1);
  __builtin_unreachable();
}