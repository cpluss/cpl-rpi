#include <stdint.h>

#include "uart.h"
#include "sys.h"
#include "gpu.h"
#include "log.h"

void kmain(uint32_t r0, uint32_t r1, uint32_t atags) {
    // Enable logging, the first thing we do
    log_init();

    // Initialize the GPU at 800x600 resolution
    gpu_init(800, 600);
    // Clear to a black color
    gpu_clear(0);

    //Test to write a character
    gpu_putchar('A', 10, 10, RGB(255, 0, 0));
}
