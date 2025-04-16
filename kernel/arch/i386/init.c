#include <kernel/init.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <stdint.h>

#include "vga.h"
#include "psf.h"

extern char _binary_arch_i386_font_inconsolata_16r_psf_start;
void arch_init(void* info) {
  terminal_setcolor(vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK));
  printf("            ____    .___.__        \n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK));
  printf("___  ______/_   | __| _/|__|__  ___\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK));
  printf("\\  \\/ /  _ \\|   |/ __ | |  \\  \\/  /\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK));
  printf(" \\   (  <_> )   / /_/ | |  |>    < \n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK));
  printf("  \\_/ \\____/|___\\____ | |__/__/\\_ \\\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK));
  printf("                     \\/          \\/\n");
  terminal_setcolor(vga_entry_color(VGA_COLOR_MAGENTA, VGA_COLOR_BLACK));

  printf("Vo1dix ");

  terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
  printf("v0.0.1 on i386\n(c) 2025 Filip Myslinski\n");
}