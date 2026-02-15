#if UTIL_FMT

#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

//------------------------------------------------------------------------------

#ifdef UTIL_FMT_OBJS

typedef int (*fmt_handler_t)(void *data, void *obj, char c, size_t len_hint, char **buf);
typedef void (*fmt_free_t)(void *data, void *buf);

//------------------------------------------------------------------------------

void printf_set(void *data, fmt_handler_t handler, fmt_free_t free);

#endif  /* UTIL_FMT_OBJS */

//------------------------------------------------------------------------------

size_t itoa(long value, uint8_t radix, bool uppercase, bool unsig, char *buf);
size_t pad(char *src, size_t len, char c, size_t pad_to, char *buf) {

//------------------------------------------------------------------------------

size_t vsnprintf(char *buf, unsigned int len, const char *fmt, va_list va);
szie_t snprintf(char *buf, unsigned int len, const char *fmt, ...);

//------------------------------------------------------------------------------

typedef struct {
  char  *ptr;
  char  *cur;
  size_t len;
} fmt_buf_t;

typedef size_t (*fmt_puts_t)(char *s, size_t len, fmt_buf_t *buf);

size_t vpprintf(fmt_puts_t puts, fmt_buf_t *buf, const char *fmt, va_list va);
size_t pprintf(fmt_puts_t puts, void *buf, const char *fmt, ...);

//------------------------------------------------------------------------------

size_t snprintf(char *buf, size_t len, const char *fmt, ...);
size_t sprintf(char *buf, const char *fmt, ...);

//------------------------------------------------------------------------------

#endif  /* UTIL_FMT */
