#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include <kernel/tty.h>
#include "vga.h"
#include "psf.h"

static const size_t VGA_WIDTH = 320;
static const size_t VGA_HEIGHT = 200;
static uint16_t *const VGA_MEMORY = (uint16_t *) 0xA0000;

static size_t terminal_row;
static size_t terminal_column;
static size_t terminal_rows;
static size_t terminal_columns;
static uint8_t terminal_color;
static uint16_t *framebuffer;

/**
* Initializes the terminal by setting terminal_row and terminal_column to 0.
* It also sets the color to black background and light grey foreground.
* It also clears the whole buffer.
*/
void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_rows = psf_rows(VGA_HEIGHT);
  terminal_columns = psf_columns(VGA_WIDTH);
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  framebuffer = VGA_MEMORY;

  for (size_t y = 0; y < terminal_rows; y++) {
    for (size_t x = 0; x < terminal_columns; x++) {
      psf_putchar(' ', x, y, terminal_color & 0b00001111, terminal_color >> 4);
    }
  }
}

/**
* Sets the color of characters printed afterwards.
*/
void terminal_setcolor(uint8_t color) { terminal_color = color; }

/**
* Shifts the whole buffer up a row, clears the bottom row.
*/
void terminal_scroll() {
  terminal_row--;
  for (size_t y = 1; y < terminal_rows; y++) {
    for (size_t x = 0; x < terminal_columns; x++) {
      framebuffer[(y - 1) * VGA_WIDTH + x] = framebuffer[y * VGA_WIDTH + x];
    }
  }
  for (size_t x = 0; x < terminal_columns; x++) {
    psf_putchar(' ', x, VGA_HEIGHT - 1, terminal_color, terminal_color);
  }
}

/**
* Prints a single character to the current cursor position. Handles scrolling and the \n character.
*/
void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_column = 0;
    if (++terminal_row == terminal_rows) {
      terminal_scroll();
    }
    return;
  }
  psf_putchar(c, terminal_column, terminal_row, terminal_color & 0b00001111, terminal_color >> 4);
  if (++terminal_column == terminal_columns) {
    terminal_column = 0;
    if (++terminal_row == terminal_rows) {
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

void putpixel(int x, int y, uint8_t color) {

}