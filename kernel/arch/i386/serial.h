#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

#include <stdint.h>

void serial_init(uint16_t);
void serial_putc(uint16_t, uint8_t);

#endif
