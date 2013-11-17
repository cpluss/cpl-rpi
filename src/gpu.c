#include "gpu.h"
#include "sys.h"

#include "log.h"

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
