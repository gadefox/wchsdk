// Copyright (c) 2026 gadefox <gadefoxren@gmail.com>

#include "wchsdk_cfg.h"

#if UTIL_FMT

#include "wch/util/fmt.h"
#include "wch/util/mem.h"
#include "wch/util/str.h"

//------------------------------------------------------------------------------

#if !UTIL_MEM
#error "snprintf requires UTIL_MEM = 1"
#endif  /* UTIL_MEM */


#if !UTIL_STR
#error "format requires UTIL_STR = 1"
#endif  /* UTIL_STR */

//==============================================================================
// Format objects

#ifdef UTIL_FMT_OBJS

static void *fmt_data;
static fmt_handler_t fmt_handler;
static fmt_free_t fmt_free;

//------------------------------------------------------------------------------

void fmt_set(void *data, fmt_handler_t handler, fmt_free_t free) {
  fmt_data = data;
  fmt_handler = handler;
  fmt_free = free;
}

#endif  /* UTIL_FMT_OBJS */

//==============================================================================
// Format buffer

size_t fmt_buf_puts(fmt_buf_t *buf, char *s, size_t len) {
  // Counting mode - just return requested length
  if (!buf)
    return len;

  // Limit to available space
  if (len > buf->free)
    len = buf->free;

  memcpy(buf->ptr, s, len);
  buf->ptr += len;
  buf->free -= len;
  return len;
}

//------------------------------------------------------------------------------

size_t fmt_buf_pad(fmt_buf_t *buf, int padc, size_t padw) {
  // Counting mode
  if (!buf)
    return padw;

  // Limit to available space
  if (padw > buf->free)
    padw = buf->free;
  
  memset(buf->ptr, padc, padw);
  buf->ptr += padw;
  buf->free -= padw;
  return padw;
}

//==============================================================================

size_t itoa(char *buf, long value, uint8_t radix, bool uppercase, bool unsig) {
  bool negative;
  unsigned long uvalue;

  if (!unsig && value < 0) {
    negative = true;
    uvalue = -(unsigned long)value;
  } else {
    negative = false;
    uvalue = (unsigned long)value;
  }
  
  char hexc = uppercase ? 'A' : 'a';
  char *p = buf;
  
  // Build string backwards
  do {
    int digit = uvalue % radix;
    *p++ = digit < 10 ? digit + '0' : digit + hexc - 10;
    uvalue /= radix;
  } while (uvalue > 0);
 
  if (negative)
    *p++ = '-'; 

  size_t len = p - buf;

  // Copy reversed to buffer
  for (size_t i = 0; i < len; i++) {
    char c = buf[i];
    buf[i] = buf[len - i - 1];
    buf[len - i - 1] = c;
  }

  return len;
}

//==============================================================================
// xxprintf functions

static size_t vpprintf(fmt_buf_t *buf, const char *fmt, va_list va) {
  char bn[11];  // max: "-2147483648" = 11 chars (10 + '\0')
  size_t n = 0;

  while (true) {
    char c = *fmt++;
    if (!c)
      break;

    if (c != '%')
      n += fmt_buf_puts(buf, &c, 1);
    else {
      // Zero padding requested
      char padc = ' ';
      c = *fmt++;
      if (!c)
        padc = '\0';

      size_t padw = 0;
      while (c >= '0' && c <= '9') {
        padw *= 10;
        padw += c - '0';
        c = *fmt++;
      }

      bool l = false;
      if (c == 'l') {
        l = true;
        c = *fmt++;
      }

      switch (c) {
      case '\0':
        goto end;
      case 'u':
      case 'd': {
        long value;
        if (l)
          value = va_arg(va,  long);
        else if (c == 'u')
          value = (long)va_arg(va, unsigned int);
        else
          value = (long)va_arg(va, int);

        size_t len = itoa(bn, value, 16, false, c == 'u');
        if (padw > len)
          n += fmt_buf_pad(buf, padc, padw - len);
        n += fmt_buf_puts(buf, bn, len);
        break;
      }

      case 'x':
      case 'X': {
        unsigned long value;
        if (l)
          value = va_arg(va, unsigned long);
        else
          value = (unsigned long)va_arg(va, unsigned int);

        size_t len = itoa(bn, value, 16, c == 'X', true);
        if (padw > len)
          n += fmt_buf_pad(buf, padc, padw - len);
        n += fmt_buf_puts(buf, bn, len);
        break;
      }

      case 'c':
        c = (char)(va_arg(va, int));
        if (padw > 1)
          n += fmt_buf_pad(buf, padc, padw - 1);
        n += fmt_buf_puts(buf, &c, 1);
        break;

      case 's': {
        char *s = va_arg(va, char *);
        if (!s)
          s = "(null)";  // Safety
        size_t len = strlen(s);

        if (padw > len)
          n += fmt_buf_pad(buf, padc, padw - len);
        n += fmt_buf_puts(buf, s, len);
        break;
      }

#ifdef UTIL_FMT_OBJS
      case 'O':     // Object by content (e.g. str)
      case 'R': {   // Object by representation (e.g. repr)
        void *obj = va_arg(va, void *);
        char *ptr;
        size_t len = fmt_handler(fmt_data, obj, c, padw, &ptr);

        if (padw > len)
          n += fmt_buf_pad(buf, padc, padw - len);
        n += fmt_buf_puts(buf, ptr, len);

        fmt_free(fmt_data, ptr);
        break;
      }
#endif  /* UTIL_FMT_OBJS */

      default:
        n += fmt_buf_puts(buf, &c, 1);
        break;
      }
    }
  }

end:
  return n;
}

//------------------------------------------------------------------------------

size_t vsnprintf(char *buf, size_t len, const char *fmt, va_list va) {
  if (!buf || !len)
    return vpprintf(NULL, fmt, va);  // Counting mode

  fmt_buf_t fb;
  fb.ptr = buf;
  fb.free = len - 1;  // for '\0'

  vpprintf(&fb, fmt, va);
  *fb.ptr = '\0';

  return fb.ptr - fb.ptr;
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

#endif  /* UTIL_FMT */
