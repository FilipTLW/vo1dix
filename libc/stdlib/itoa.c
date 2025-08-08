#include <stdlib.h>

void itoa(int d, char *buf, int base) {
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;

  if (d < 0) {
      *p++ = '-';
      buf++;
      ud = -d;
  }

  do {
    int remainder = ud % base;

    *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
  }
  while (ud /= base);

  *p = 0;

  p1 = buf;
  p2 = p - 1;
  while (p1 < p2) {
    char tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
    p1++;
    p2--;
  }
}
