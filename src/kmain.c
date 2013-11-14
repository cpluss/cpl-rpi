#include <stdint.h>

#include <uart.h>

// To get rid of compiler warnings of unused parameters
#define UNUSED(x) (void)(x)

const char *hello = "\r\nHello World\r\n";
const char *halting = "\r\n*** system halting ***";

void kmain(uint32_t r0, uint32_t r1, uint32_t atags) {
    UNUSED(r0);
    UNUSED(r1);
    UNUSED(atags);

    uart_init();

    uart_puts(hello);

    for(volatile int i = 0; i < 10000000; i++);

    uart_puts(halting);
}
