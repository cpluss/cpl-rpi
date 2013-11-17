#include "gpu.h"
#include "console.h"

// Keep track of cursor location
static console_t cons;
#define PADDING 1

void console_init(uint width, uint height) {
    cons.x = cons.y = PADDING;
    cons.width = width;
    cons.height = height;
}

void console_putc(char c) {
    // Did we get a backspace character?
    if(c == '\b') {
        if(cons.x <= 0) {
            cons.x = 0;
            if(cons.y > 0) {
                cons.y -= CHAR_HEIGHT - PADDING;
            }
        } else {
            cons.x -= CHAR_WIDTH - PADDING;
        }
        
        return;
    }
    // Did we get a newline ?
    if(c == '\n') {
        if(cons.y < cons.height) {
            cons.y += CHAR_HEIGHT + PADDING;
            cons.x = 0;
        }

        return;
    }

    // Print the character
    gpu_putchar(c, cons.x, cons.y, 0xffffff);

    // Increment cursor position
    cons.x += CHAR_WIDTH + PADDING;

    if(cons.x >= cons.width) {
        cons.x = 0;
        cons.y += CHAR_HEIGHT + PADDING;
    }
}

void console_puts(const char *s) {
    while(*s) {
        console_putc(*s++);
    }
}
