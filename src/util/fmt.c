// Copyright (c) 2013,2014 Michal Ludvig <michal@logix.cz>

#include "wchsdk_cfg.h"

#if UTIL_FMT

#include "wch/util/fmt.h"
#include "wch/util/str.h"

//------------------------------------------------------------------------------

int itoa(long value, unsigned int radix, int uppercase, int unsig, char *buffer) {
  char *pbuffer = buffer;
  int negative = 0;
  int i, len;

  /* No support for unusual radixes. */
  if (radix > 16)
    return 0;

  if (value < 0 && !unsig) {
    negative = 1;
    value = -value;
  }

  /* This builds the string back to front ... */
  do {
    int digit = value % radix;
    *(pbuffer++) = (digit < 10 ? '0' + digit : (uppercase ? 'A' : 'a') + digit - 10);
    value /= radix;
  } while (value > 0);

  if (negative)
    *(pbuffer++) = '-';

  *(pbuffer) = '\0';

  /* ... now we reverse it (could do it recursively but will
   * conserve the stack space) */
  len = (pbuffer - buffer);
  for (i = 0; i < len / 2; i++) {
    char j = buffer[i];
    buffer[i] = buffer[len - i - 1];
    buffer[len - i - 1] = j;
  }

  return len;
}

//------------------------------------------------------------------------------

static int pad(char *ptr, int len, char pad_char, int pad_to, char *buffer) {
  int i;
  int overflow = 0;
  char *pbuffer = buffer;
  if (pad_to == 0)
    pad_to = len;
  if (len > pad_to) {
    len = pad_to;
    overflow = 1;
  }
  for (i = pad_to - len; i > 0; i--)
    *(pbuffer++) = pad_char;
  for (i = len; i > 0; i--)
    *(pbuffer++) = *(ptr++);
  len = pbuffer - buffer;
  if (overflow) {
    for (i = 0; i < 3 && pbuffer > buffer; i++)
      *(pbuffer-- - 1) = '*';
  }
  return len;
}

//------------------------------------------------------------------------------

struct mini_buff {
  char         *buffer;
  char         *pbuffer;
  unsigned int len;
};

static int mini_puts(char *s, int len, void *buf) {
  if (!buf)
    return len;
  struct mini_buff *b = buf;
  char *p0 = b->buffer;
  int i;
  /* Copy to buffer */
  for (i = 0; i < len; i++) {
    if (b->pbuffer == b->buffer + b->len - 1)
      break;
    *(b->pbuffer++) = s[i];
  }
  *(b->pbuffer) = 0;
  return b->pbuffer - p0;
}

//------------------------------------------------------------------------------

#ifdef MINI_PRINTF_ENABLE_OBJECTS

typedef int  (*printf_handler_t)(void *data, void *obj, int ch, int len_hint, char **buf);
typedef void (*printf_free_t)   (void *data, void *buf);

static printf_handler_t mini_handler = 0;
static printf_free_t    mini_handler_freeor = 0;
static void            *mini_handler_data = 0;

//------------------------------------------------------------------------------

void printf_set_handler(void *data, printf_handler_t handler, printf_free_t freeor) {
  mini_handler = handler;
  mini_handler_freeor = freeor;
  mini_handler_data = data;
}

#endif  /* MINI_PRINTF_ENABLE_OBJECTS */

//------------------------------------------------------------------------------

int vsnprintf(char *buffer, unsigned int len, const char *fmt, va_list va) {
  struct mini_buff b;
  b.buffer = buffer;
  b.pbuffer = buffer;
  b.len = len;
  if (len == 0)
    buffer = (void *)0;
  int n = vpprintf(mini_puts, (buffer != (void *)0) ? &b : (void *)0, fmt, va);
  if (buffer == (void *)0)
    return n;
  return b.pbuffer - b.buffer;
}

//------------------------------------------------------------------------------

int vpprintf(vpprintf_puts_t puts, void *buf, const char *fmt, va_list va) {
  char bf[24];
  char bf2[24];
  char ch;

#ifdef MINI_PRINTF_ENABLE_OBJECTS
  void *obj;
#endif

  if (puts == (void *)0) {
    /* run puts in counting mode. */
    puts = mini_puts;
    buf = (void *)0;
  }
  int n = 0;
  while ((ch = *(fmt++))) {
    int len;
    if (ch != '%') {
      len = 1;
      len = puts(&ch, len, buf);
    } else {
      char pad_char = ' ';
      int pad_to = 0;
      char l = 0;
      char *ptr;

      ch = *(fmt++);

      /* Zero padding requested */
      if (ch == '0')
        pad_char = '0';
      while (ch >= '0' && ch <= '9') {
        pad_to = pad_to * 10 + (ch - '0');
        ch = *(fmt++);
      }
      if (pad_to > (signed int)sizeof(bf))
        pad_to = sizeof(bf);
      if (ch == 'l') {
        l = 1;
        ch = *(fmt++);
      }

      switch (ch) {
      case 0:
        goto end;
      case 'u':
      case 'd':
        if (l)
          len = itoa(va_arg(va, unsigned long), 10, 0, (ch == 'u'), bf2);
        else {
          if (ch == 'u')
            len = itoa((unsigned long)va_arg(va, unsigned int), 10, 0, 1, bf2);
          else
            len = itoa((long)va_arg(va, int), 10, 0, 0, bf2);
        }
        len = pad(bf2, len, pad_char, pad_to, bf);
        len = puts(bf, len, buf);
        break;

      case 'x':
      case 'X':
        if (l)
          len = itoa(va_arg(va, unsigned long), 16, (ch == 'X'), 1, bf2);
        else
          len = itoa((unsigned long)va_arg(va, unsigned int), 16, (ch == 'X'), 1, bf2);
        len = pad(bf2, len, pad_char, pad_to, bf);
        len = puts(bf, len, buf);
        break;

      case 'c':
        ch = (char)(va_arg(va, int));
        len = pad(&ch, 1, pad_char, pad_to, bf);
        len = puts(bf, len, buf);
        break;

      case 's':
        ptr = va_arg(va, char *);
        len = strlen(ptr);
        if (pad_to > 0) {
          len = pad(ptr, len, pad_char, pad_to, bf);
          len = puts(bf, len, buf);
        } else
          len = puts(ptr, len, buf);
        break;

#ifdef MINI_PRINTF_ENABLE_OBJECTS
      case 'O': /* Object by content (e.g. str) */
      case 'R': /* Object by representation (e.g. repr)*/
        obj = va_arg(va, void *);
        len = mini_handler(mini_handler_data, obj, ch, pad_to, &ptr);
        if (pad_to > 0) {
          len = pad(ptr, len, pad_char, pad_to, bf);
          len = puts(bf, len, buf);
        } else
          len = puts(ptr, len, buf);
        mini_handler_freeor(mini_handler_data, ptr);
        break;
#endif  /* MINI_PRINTF_ENABLE_OBJECTS */

      default:
        len = 1;
        len = puts(&ch, len, buf);
        break;
      }
    }
    n = n + len;
  }
end:
  return n;
}

//------------------------------------------------------------------------------

int snprintf(char *buffer, unsigned int len, const char *fmt, ...) {
  int ret;
  va_list va;
  va_start(va, fmt);
  ret = vsnprintf(buffer, len, fmt, va);
  va_end(va);

  return ret;
}

//------------------------------------------------------------------------------

int pprintf(vpprintf_puts_t puts, void *buf, const char *fmt, ...) {
  int ret;
  va_list va;
  va_start(va, fmt);
  ret = vpprintf(puts, buf, fmt, va);
  va_end(va);

  return ret;
}

//------------------------------------------------------------------------------

__attribute__((weak))
int snprintf(char *buffer, unsigned int len, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int ret = vsnprintf(buffer, len, format, args);
  va_end(args);
  return ret;
}

//------------------------------------------------------------------------------

__attribute__((weak))
int sprintf(char *buffer, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int ret = vsnprintf(buffer, INT_MAX, format, args);
  va_end(args);
  return ret;
}

//------------------------------------------------------------------------------

#endif  /* UTIL_FMT */
