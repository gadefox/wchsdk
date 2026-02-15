#if UTIL_FMT

#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//==============================================================================
// Format objects

#ifdef UTIL_FMT_OBJS

typedef int (*fmt_handler_t)(void *data, void *obj, char c, size_t len_hint, char **buf);
typedef void (*fmt_free_t)(void *data, void *buf);

//------------------------------------------------------------------------------

void fmt_set(void *data, fmt_handler_t handler, fmt_free_t free);

#endif  /* UTIL_FMT_OBJS */

//==============================================================================
// Format buffer

typedef struct {
  char  *ptr;
  size_t free;
} fmt_buf_t;

typedef size_t (*fmt_puts_t)(fmt_buf_t *buf, char *s, size_t len);

size_t fmt_buf_puts(fmt_buf_t *buf, char *s, size_t len);
size_t fmt_buf_pad(fmt_buf_t *buf, int padc, size_t padw);

//==============================================================================
// Number conversion

size_t itoa(char *buf, long value, uint8_t radix, bool uppercase, bool unsig);

//==============================================================================
// Returns the number of characters actually written (excluding the terminating '\0')

size_t vsnprintf(char *buf, size_t len, const char *fmt, va_list va);
size_t snprintf(char *buf, size_t len, const char *fmt, ...);

//------------------------------------------------------------------------------

#endif  /* UTIL_FMT */
