#include <stdint.h>

#include "uart.h"
#include "sys.h"

void kmain(uint32_t r0, uint32_t r1, uint32_t atags) {
    uart_init();

    uart_puts("UART Initialized ...\n");
    gpu_t *gpu = RequestFramebuffer(800, 600);
    uart_puts("Got framebuffer from gpu!\n");

    // Clear the screen
    uint y, x, off;
    for(y = 0; y < 600; y++) {
        for(x = 0; x < 800; x++) {
            // Calculate offset
            off = (y * gpu->pitch) + (x * 3);

            //Update the data
            *(char*)(gpu->pointer + off)     = 0xFF; //R
            *(char*)(gpu->pointer + off + 1) = 0x00; //G
            *(char*)(gpu->pointer + off + 2) = 0x00; //B
        }
    }
}
