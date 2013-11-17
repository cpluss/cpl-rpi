#include "gpu.h"
#include "sys.h"

#include "log.h"

/* The default character character font, before I implement/port ttf */
#include "default-font.h"

/* We need to store a copy of the gpu structure returned by 
   the actual gpu */
static gpu_t *gpu;

void gpu_init(uint w, uint h) {
    gpu = RequestFramebuffer(w, h);
    log_write(LOG_INFO, "GPU: Acquired framebuffer.");
}

/* Clear the screen to a single color */
void gpu_clear(uint color) {
    uint y, x;
    for(y = 0; y < gpu->height; y++) {
        for(x = 0; x < gpu->width; x++) {
            gpu_putpixel(x, y, color);
        }
    }
}

/* Draw a pixel with a specific color */
void gpu_putpixel(uint x, uint y, uint color) {
    // Calculate the pixels memory offset
    uint off = (y * gpu->pitch) + 3*x;

    // Set the actual pixel color
    *(uint*)(gpu->pointer + off) = color;
}

/* Default and simple way to draw a character */
void gpu_putchar(char v, uint x, uint y, uint color) {
    if(v > 128) {
        v = 4;
    }

    uint8_t *c = number_font[v], i, j;
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 12; j++) {
            if(c[i] & (1 << (8 - j))) {
                gpu_putpixel(x + j, y + i, color);
            } else {
                gpu_putpixel(x + j, y + i, 0); //Assume black background
            }
        }
    }
}
