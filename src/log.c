#include "log.h"
#include "uart.h"

void log_debug(const char *msg) {
    uart_puts(msg);
    uart_puts("\n");
}
void log_warning(const char *msg) {
    uart_puts(msg);
    uart_puts("\n");
}
void log_err(const char *msg) {
    uart_puts(msg);
    uart_puts("\n");
}
void log_info(const char *msg) {
    uart_puts(msg);
    uart_puts("\n");
}

/* Write a log message to the appropriate logs
   determined by the flags provided */
void log_write(uint flags, const char *msg) {
    // Determine where to write to
    if(flags & LOG_DEBUG) {
        log_debug(msg);
    }
    if(flags & LOG_WARN) {
        log_warning(msg);
    }
    if(flags & LOG_INFO) {
        log_info(msg);
    }
    if(flags & LOG_ERR) {
        log_err(msg);
    }
}

/* Enable logging features such as UART */
void log_init() {
    uart_init();
    log_write(LOG_INFO, "LOG: Logging has been initialized.");
}
