#ifndef ARCH_I386_BDA_H
#define ARCH_I386_BDA_H

#include <stdint.h>

/**
 * Struct for storing BDA provided by the BIOS located at memory address 0x400
 */
struct BIOS_DATA {
	uint16_t com1;
	uint16_t com2;
	uint16_t com3;
	uint16_t com4;

	uint16_t lpt1;
	uint16_t lpt2;
	uint16_t lpt3;

	uint16_t ebda_addr;

	uint16_t hardware_flags;
};

extern struct BIOS_DATA *bios_data;

#endif
