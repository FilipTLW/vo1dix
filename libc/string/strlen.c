#include <string.h>

/**
* This function calculates the length of a string by counting up until a null character is found.
*/
size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len]) // count up until a null character comes
    len++;
  return len;
}

