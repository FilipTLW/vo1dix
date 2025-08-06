#include "serial.h"
#include "serial_ports.h"
#include <sys/io.h>
#include <stdint.h>

void serial_init(uint16_t port) {
	// Disable interrupts
	outb(0x0, port + COM_OFFSET_INT);
	// Set DLAB bit to 1
	outb(0b10000000, port + COM_OFFSET_LCR);
	// Set baud rate to 38400 (115200 / 3)
	outb(0x3, port + COM_OFFSET_BAUDL);
	outb(0x0, port + COM_OFFSET_BAUDH);
	// Set DLAB bit to 0, set data bits to 7, set stop bits to 1, set parity to none
	outb(0b00000010, port + COM_OFFSET_LCR);
}

void serial_putc(uint16_t port, uint8_t c) {
	outb(c, port);
}
