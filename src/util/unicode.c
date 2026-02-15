// Copyright © 2005-2020 Rich Felker, et al.

#include "wchsdk_cfg.h"

#if UTIL_UNICODE

#include "wch/util/unicode.h"

//------------------------------------------------------------------------------

#if UNICODE_ENABLE
#define MB_MAX  4
#else
#define MB_MAX  1
#endif

//------------------------------------------------------------------------------

__attribute__((weak)) int errno;

//------------------------------------------------------------------------------

__attribute__((weak))
size_t wcrtomb(char *restrict s, wchar_t wc, mbstate_t *restrict st) {
  if (!s)
    return 1;

  if ((unsigned)wc < 0x80) {
    *s = wc;
    return 1;
  }

  if (MB_MAX == 1) {
    if (!((unsigned)wc - 0xDF80 < 0x80)) {
      errno = 0x02; // EILSEQ
      return -1;
    }
    *s = wc;
    return 1;
  }

  if ((unsigned)wc < 0x800) {
    *s++ = 0xC0 | (wc >> 6);
    *s = 0x80 | (wc & 0x3F);
    return 2;
  }

  if ((unsigned)wc < 0xD800 || (unsigned)wc - 0xE000 < 0x2000) {
    *s++ = 0xE0 | (wc >> 12);
    *s++ = 0x80 | ((wc >> 6) & 0x3F);
    *s = 0x80 | (wc & 0x3F);
    return 3;
  }

  if ((unsigned)wc - 0x10000 < 0x100000) {
    *s++ = 0xF0 | (wc >> 18);
    *s++ = 0x80 | ((wc >> 12) & 0x3F);
    *s++ = 0x80 | ((wc >> 6) & 0x3F);
    *s = 0x80 | (wc & 0x3F);
    return 4;
  }

  errno = 0x02; // EILSEQ;
  return -1;
}

//------------------------------------------------------------------------------

#endif /* UTIL_UNICODE */
