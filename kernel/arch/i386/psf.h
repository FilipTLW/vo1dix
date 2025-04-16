#ifndef ARCH_I386_PSF_H
#define ARCH_I386_PSF_H

#include <stdint.h>
#include <stddef.h>

#define PSF1_FONT_MAGIC 0x0436

struct PSF1_Header {
  uint16_t magic; // Magic bytes for identification.
  uint8_t fontMode; // PSF font mode.
  uint8_t characterSize; // PSF character size.
};

#define PSF_FONT_MAGIC 0x864ab572

struct PSF_FONT {
  uint32_t magic;         /* magic bytes to identify PSF */
  uint32_t version;       /* zero */
  uint32_t headersize;    /* offset of bitmaps in file, 32 */
  uint32_t flags;         /* 0 if there's no unicode table */
  uint32_t numglyph;      /* number of glyphs */
  uint32_t bytesperglyph; /* size of each glyph */
  uint32_t height;        /* height in pixels */
  uint32_t width;         /* width in pixels */
};

void psf_putchar(unsigned short int c, int cy, int cx, uint32_t fg, uint32_t bg);
size_t psf_rows(size_t screen_height);
size_t psf_columns(size_t screen_width);

#endif