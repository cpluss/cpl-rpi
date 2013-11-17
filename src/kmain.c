#include <stdint.h>

#include "uart.h"
#include "sys.h"
#include "gpu.h"

void kmain(uint32_t r0, uint32_t r1, uint32_t atags) {
    uart_init();

    uart_puts("UART Initialized ...\n");

    gpu_init(800, 600);
    gpu_clear(RGB(255,0,0));
}
