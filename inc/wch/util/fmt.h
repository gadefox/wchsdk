#if UTIL_FMT

#pragma once

#include <stdarg.h>

//------------------------------------------------------------------------------

int itoa(long value, unsigned int radix, int uppercase, int unsig, char *buffer);

//------------------------------------------------------------------------------

int vsnprintf(char *buffer, unsigned int len, const char *fmt, va_list va);
int snprintf(char *buffer, unsigned int len, const char *fmt, ...);

//------------------------------------------------------------------------------

typedef int (*vpprintf_puts_t)(char *s, int len, void *buf);

int vpprintf(vpprintf_puts_t puts, void *buf, const char *fmt, va_list va);
int pprintf(vpprintf_puts_t puts, void *buf, const char *fmt, ...);

//------------------------------------------------------------------------------

int snprintf(char *buffer, unsigned int len, const char *format, ...);
int sprintf(char *buffer, const char *format, ...);

//------------------------------------------------------------------------------

#endif  /* UTIL_FMT */
