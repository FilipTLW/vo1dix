#include <kernel/debug.h>
#include "bda.h"
#include "serial.h"
#include "serial_ports.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static uint16_t COM1;

static void print(const char *data, size_t length) {
	const unsigned char *bytes = (const unsigned char *) data;
	for (size_t i = 0; i < length; i++)
		serial_putc(COM1, bytes[i]);
}

void kdbg_init() {
	COM1 = bios_data->com1;
	serial_init(COM1);
	kdbg_log("kdbg", "Initialized kdbg on COM1");
}

void kdbg_write(const char *restrict format, ...) {
  va_list parameters;
  va_start(parameters, format);

  int written = 0;

  while (*format != '\0') {
    size_t maxrem = INT_MAX - written;

    if (format[0] != '%' || format[1] == '%') {
      if (format[0] == '%')
        format++;
      size_t amount = 1;
      while (format[amount] && format[amount] != '%')
        amount++;
      if (maxrem < amount) {
        // TODO: Set errno to EOVERFLOW.
        return;
      }
      print(format, amount);
      format += amount;
      written += amount;
      continue;
    }

    const char *format_begun_at = format++;

    if (*format == 'c') {
      format++;
      char c = (char) va_arg(parameters, int /* char promotes to int */);
      if (!maxrem) {
        // TODO: Set errno to EOVERFLOW.
        return;
      }
      print(&c, sizeof(c));
        return;
      written++;
    } else if (*format == 's') {
      format++;
      const char *str = va_arg(parameters, const char *);
      size_t len = strlen(str);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return;
      }
      print(str, len);
      written += len;
    } else if (*format == 'd') {
      format++;
      int d = va_arg(parameters, int);
      char buf[11];
      itoa(d, buf, 10);
      size_t len = strlen(buf);
      if (maxrem < len) {
        return;
      }
      print(buf, len);
      written += len;
    } else if (*format == 'x') {
      format++;
      int x = va_arg(parameters, int);
      char buf[11];
      itoa(x, buf, 16);
      size_t len = strlen(buf);
      if (maxrem < len) {
        return;
      }
      print(buf, len);
      written += len;
    } else {
      format = format_begun_at;
      size_t len = strlen(format);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return;
      }
      print(format, len);
      written += len;
      format += len;
    }
  }

  va_end(parameters);
}


