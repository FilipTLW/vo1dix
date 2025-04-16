#include "psf.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

extern char _binary_arch_i386_font_inconsolata_16r_psf_start;

void psf_putchar(unsigned short int c,
                     int cx, int cy,
                     uint32_t fg, uint32_t bg) {
  struct PSF_FONT *font = (struct PSF_FONT *)&_binary_arch_i386_font_inconsolata_16r_psf_start;
  unsigned char *glyph = (unsigned char *)&_binary_arch_i386_font_inconsolata_16r_psf_start
      + font->headersize + (c>0&&c<font->numglyph?c:0) * font->bytesperglyph;
  int offs = (320 * cy * font->height) + cx * font->width;
  int x, y, line, mask;
  for (y = 0; y < font->height; y++) {
    line = offs;
    mask=1<<(font->width-1);
    for (x = 0; x < font->width; x++) {
      uint32_t color = *((unsigned int *)glyph) & mask ? fg : bg;
      *((uint32_t *)(0xA0000 + line)) = color;
      mask >>= 1;
      line += 1;
    }
    glyph += (font->width + 7)/8;
    offs += 320;
  }
}

size_t psf_columns(size_t screen_width) {
  struct PSF_FONT *font = (struct PSF_FONT *)&_binary_arch_i386_font_inconsolata_16r_psf_start;
  return screen_width / font->width;
}

size_t psf_rows(size_t screen_height) {
  struct PSF_FONT *font = (struct PSF_FONT *)&_binary_arch_i386_font_inconsolata_16r_psf_start;
  return screen_height / font->height;
}
