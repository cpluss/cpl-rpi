#include <stdint.h>

#include <uart.h>

void kmain(uint32_t r0, uint32_t r1, uint32_t atags) {
    uart_init();

    uart_puts("Hello world!");
}
