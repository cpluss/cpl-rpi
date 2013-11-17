#ifndef GPU_H
#define GPU_H

#include "types.h"

/* All the interfacing with the GPU will be
   handled here (except for the framebuffer aqcuisition, that
   takes place in sys.c). */

/* The default font, before I implement/port ttf */
//#include "default_font.h"

/* Initialize the gpu in a specific resolution */
void gpu_init(uint width, uint height);

/* Plot a single pixel at a given location */
void gpu_putpixel(uint x, uint y, uint color);

/* Clear the screen to a single color */
void gpu_clear(uint color);

#define RGB(r,g,b) (b << 16 | g << 8 | r)
/* Default and simple way to draw a character */
void gpu_putchar(char c, uint x, uint y, uint color);

#endif
