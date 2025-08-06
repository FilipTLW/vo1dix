#include <sys/io.h>
#include <stdint.h>

void outb(uint8_t value, uint16_t port) {
    asm volatile ("outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}
