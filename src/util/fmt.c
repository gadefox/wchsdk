// Copyright (c) 2013,2014 Michal Ludvig <michal@logix.cz>
// Copyright (c) 2026 gadefox <gadefoxren@gmail.com>

#include "wchsdk_cfg.h"

#if UTIL_FMT

#include "wch/util/fmt.h"
#include "wch/util/str.h"

//------------------------------------------------------------------------------

#if !UTIL_STR
#error "format requires UTIL_SYS = 1"
#endif  /* UTIL_STR */

//------------------------------------------------------------------------------

#ifdef UTIL_FMT_OBJS

static void *fmt_data;
static fmt_handler_t fmt_handler;
static fmt_free_t fmt_free;

//------------------------------------------------------------------------------

void printf_set(void *data, fmt_handler_t handler, fmt_free_t free) {
  fmt_data = data;
  fmt_handler = handler;
  fmt_free = free;
}

#endif  /* UTIL_FMT_OBJS */

//------------------------------------------------------------------------------

size_t itoa(long value, uint8_t radix, bool uppercase, bool unsig, char *buf) {
  bool negative = false;
  char *p = buf;

  if (!unsig && value < 0) {
    negative = true;
    value = -value;
  }

  // This builds the string back to front
  char hexc = uppercase ? 'A' : 'a';
  do {
    int digit = value % radix;
    *p++ = digit < 10 ? digit + '0' : digit + hexc - 10;
    value /= radix;
  } while (value > 0);

  if (negative) *p++ = '-';
  *p = '\0';

  // Now we reverse it (could do it recursively but will conserve the stack space
  size_t len = p - buf;
  for (int i = 0; i < len / 2; i++) {
    char c = buf[i];
    buf[i] = buf[len - i - 1];
    buf[len - i - 1] = c;
  }

  return len;
}

//------------------------------------------------------------------------------
// Pads src to pad_to length with char c. If src is longer than pad_to,
// truncates and marks overflow with "***" at the end. Caller must ensure buf
// has at least pad_to bytes. Returns: number of bytes written to buf

static size_t pad(char *src, size_t len, char c, size_t pad_to, char *buf) {
  bool overflow = false;
  char *p = buf;

  if (pad_to == 0)
    pad_to = len;
  if (len > pad_to) {
    len = pad_to;
    overflow = true;
  }

  // Padding
  for (int i = pad_to - len; i > 0; i--)
    *p++ = c;

  // Copy src
  while (len--)
    *p++ = *src++;

  len = p - buf;

  // Overflow indicator
  if (overflow && len >= 3)
    p[-3] = p[-2] = p[-1] = '*';

  return len;
}

//------------------------------------------------------------------------------

static size_t puts_internal(char *s, size_t len, fmt_buf_t *buf) {
  if (!buf)
    return len;

  // Calculate available space (reserve 1 byte for null terminator)
  char *start = buf->cur;
  size_t available = (buf->ptr + buf->len) - start - 1;
  
  // Copy what fits
  if (len > available)
    len = available;

  while (len--)
    *buf->cur++ = *s++;

  // Null terminate
  *buf->cur = '\0';
  return buf->cur - start;
}

//------------------------------------------------------------------------------

size_t vpprintf(fmt_puts_t puts, fmt_buf_t *buf, const char *fmt, va_list va) {
  char bf[24];
  char bf2[24];

#ifdef UTIL_FMT_OBJS
  void *obj;
#endif  /* UTIL_FMT_OBJS */

  if (puts == NULL) {
    // Run puts in counting mode
    puts = puts_internal;
    buf = NULL;
  }

  size_t len, n = 0;

  while (true) {
    char c = *fmt++;
    if (!c)
      break;

    if (c != '%')
      len = puts(&c, 1, buf);
    else {
      char padc = ' ';
      size_t pad_to = 0;
      bool l = false;
      char *ptr;

      c = *fmt++;

      // Zero padding requested
      if (c == '\0')
        padc = '\0';

      while (c >= '0' && c <= '9') {
        pad_to *= 10;
        pad_to += c - '0';
        c = *fmt++;
      }

      if (pad_to > sizeof(bf))
        pad_to = sizeof(bf);
      if (c == 'l') {
        l = true;
        c = *fmt++;
      }

      switch (c) {
      case '\0':
        goto end;
      case 'u':
      case 'd':
        if (l)
          len = itoa(va_arg(va, unsigned long), 10, false, c == 'u', bf2);
        else {
          if (c == 'u')
            len = itoa((unsigned long)va_arg(va, unsigned int), 10, false, true, bf2);
          else
            len = itoa((long)va_arg(va, int), 10, false, true, bf2);
        }
        len = pad(bf2, len, padc, pad_to, bf);
        len = puts(bf, len, buf);
        break;

      case 'x':
      case 'X':
        if (l)
          len = itoa(va_arg(va, unsigned long), 16, c == 'X', true, bf2);
        else
          len = itoa((unsigned long)va_arg(va, unsigned int), 16, c == 'X', true, bf2);
        len = pad(bf2, len, padc, pad_to, bf);
        len = puts(bf, len, buf);
        break;

      case 'c':
        c = (char)(va_arg(va, int));
        len = pad(&c, 1, padc, pad_to, bf);
        len = puts(bf, len, buf);
        break;

      case 's':
        ptr = va_arg(va, char *);
        len = strlen(ptr);
        if (pad_to <= 0)
          len = puts(ptr, len, buf);
        else {
          len = pad(ptr, len, padc, pad_to, bf);
          len = puts(bf, len, buf);
        }
        break;

#ifdef UTIL_FMT_OBJS
      case 'O':  // Object by content (e.g. str)
      case 'R':  // Object by representation (e.g. repr)
        obj = va_arg(va, void *);
        len = fmt_handler(fmt_data, obj, c, pad_to, &ptr);
        if (pad_to <= 0)
          len = puts(ptr, len, buf);
        else {
          len = pad(ptr, len, padc, pad_to, bf);
          len = puts(bf, len, buf);
        }
        fmt_free(fmt_data, ptr);
        break;
#endif  /* UTIL_FMT_OBJS */

      default:
        len = puts(&c, len, buf);
        break;
      }
    }

    n += len;
  }
end:
  return n;
}

//------------------------------------------------------------------------------

size_t vsnprintf(char *buf, size_t len, const char *fmt, va_list va) {
  if (!buf || !len)
    return vpprintf(puts_internal, NULL, fmt, va);  // Counting mode

  fmt_buf_t buf;
  buf.cur = buf.ptr = buf;
  buf.len = len;

  vpprintf(puts_internal, &buf, fmt, va);
  return buf.cur - buf.buf;
}

//------------------------------------------------------------------------------

size_t snprintf(char *buf, size_t len, const char *fmt, ...) {
  va_list va;
  va_start(va, fmt);
  size_t n = vsnprintf(buf, len, fmt, va);
  va_end(va);
  return n;
}

//------------------------------------------------------------------------------

int pprintf(fmt_puts_t puts, void *buf, const char *fmt, ...) {
  va_list va;
  va_start(va, fmt);
  size_t n = vpprintf(puts, buf, fmt, va);
  va_end(va);
  return n;
}

//------------------------------------------------------------------------------

__attribute__((weak))
size_t snprintf(char *buf, size_t len, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  size_t n = vsnprintf(buf, len, fmt, args);
  va_end(args);
  return n;
}

//------------------------------------------------------------------------------

__attribute__((weak))
size_t sprintf(char *buf, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  size_t n = vsnprintf(buf, INT_MAX, fmt, args);
  va_end(args);
  return n;
}

//------------------------------------------------------------------------------

#endif  /* UTIL_FMT */
