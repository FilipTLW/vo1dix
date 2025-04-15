#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "Vo1dix must be compiled with a ix86-elf cross compiler"
#endif

#if !defined(__i386__)
#error "Vo1dix must be compiled with a ix86-elf cross compiler"
#endif

enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
};

/**
* This function combines a foreground color and a background color and returns the result.
*/
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) { return fg | bg << 4; }

/**
* This function extends a char with a color value, in the result the lower byte represents the character while the upper
* byte represents the color.
*/
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) { return (uint16_t) uc | (uint16_t) color << 8; }

/**
* This function calculates the length of a string by counting up until a null character is found.
*/
size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len]) // count up until a null character comes
    len++;
  return len;
}

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer = (uint16_t *) VGA_MEMORY;

/**
* Initializes the terminal by setting terminal_row and terminal_column to 0.
* It also sets the color to black background and light grey foreground.
* It also clears the whole buffer.
*/
void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

/**
* Sets the color of characters printed afterwards.
*/
void terminal_setcolor(uint8_t color) { terminal_color = color; }

/**
* Manipulates the buffer by changing a character at (x, y) to c with color color.
*/
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

/**
* Shifts the whole buffer up a row, clears the bottom row.
*/
void terminal_scroll() {
  terminal_row--;
  for (size_t y = 1; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      const size_t target_index = (y - 1) * VGA_WIDTH + x;
      terminal_buffer[target_index] = terminal_buffer[index];
    }
  }
  for (size_t x = 0; x < VGA_WIDTH; x++) {
    const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(' ', terminal_color);
  }
}

/**
* Prints a single character to the current cursor position. Handles scrolling and the \n character.
*/
void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT) {
      terminal_scroll();
    }
    return;
  }
  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  if (++terminal_column == VGA_WIDTH) {
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT) {
      terminal_scroll();
    }
  }
}

/**
* Prints a fixed-size string to the terminal.
*/
void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

/**
* Prints a null-terminated string to the terminal.
*/
void terminal_writestring(const char *data) { terminal_write(data, strlen(data)); }

/**
* Entry point for the kernel, called by the bootloader.
*/
void kernel_main(void) {
  /* Initialize terminal interface */
  terminal_initialize();

  terminal_setcolor(vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK));
  terminal_writestring("            ____    .___.__        \n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK));
  terminal_writestring("___  ______/_   | __| _/|__|__  ___\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK));
  terminal_writestring("\\  \\/ /  _ \\|   |/ __ | |  \\  \\/  /\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK));
  terminal_writestring(" \\   (  <_> )   / /_/ | |  |>    < \n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK));
  terminal_writestring("  \\_/ \\____/|___\\____ | |__/__/\\_ \\\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK));
  terminal_writestring("                     \\/          \\/\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK));

  terminal_writestring("Vo1dix ");

  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  terminal_writestring("v0.0.1\n(c) 2025 Filip Myslinski");
}
