#ifndef LOG_H
#define LOG_H

/*
 This is a very basic logging "service" for debug messages (uart)
 and (in the future) regular messages written directly to the screen
 */

#define LOG_WARN  0x01
#define LOG_DEBUG 0x02
#define LOG_INFO  0x04
#define LOG_ERR   0x08

void log_debug(const char *msg);
void log_warning(const char *msg);
void log_err(const char *msg);
void log_info(const char *msg);

/* Write to the appropriate logs depending on the flags provided */
void log_write(uint flags, const char *msg);

#endif
