/*----------------------------------------------------------------------
 * Copyright © 2005-2020 Rich Felker, et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
----------------------------------------------------------------------*/

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
