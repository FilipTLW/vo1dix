#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) {
#if defined(__is_libk)
  printf("kernel: panic: abort()\n");
  asm volatile("hlt"); // halt the CPU TODO: implement proper panic logic
#else
  printf("abort()\n");
#endif
  while (1) { }
  __builtin_unreachable();
}