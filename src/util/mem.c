// Copyright © 2005-2020 Rich Felker, et al.

#include "wchsdk_cfg.h"

#if UTIL_MEM

#include <stdint.h>
#include "wch/util/mem.h"

//------------------------------------------------------------------------------

__attribute__((weak))
void *__memrchr(const void *m, int c, size_t n) {
  const unsigned char *s = m;
  c = (unsigned char)c;
  while (n--)
    if (s[n] == c)
      return (void *)(s + n);
  return 0;
}

//------------------------------------------------------------------------------

__attribute__((weak))
void *memcpy(void *dest, const void *src, size_t n) {
  unsigned char *d = dest;
  const unsigned char *s = src;
  for (; n; n--)
    *d++ = *s++;
  return dest;
}

//------------------------------------------------------------------------------

__attribute__((weak))
int memcmp(const void *vl, const void *vr, size_t n) {
  const unsigned char *l = vl, *r = vr;
  for (; n && *l == *r; n--, l++, r++)
    ;
  return n ? *l - *r : 0;
}

//------------------------------------------------------------------------------

__attribute__((weak))
 void *memmove(void *dest, const void *src, size_t n) {
  char *d = dest;
  const char *s = src;

  if (d == s)
    return d;
  if ((uintptr_t)s - (uintptr_t)d - n <= -2 * n)
    return memcpy(d, s, n);

  if (d < s) {
    for (; n; n--)
      *d++ = *s++;
  } else {
    while (n)
      n--, d[n] = s[n];
  }

  return dest;
}

//------------------------------------------------------------------------------

__attribute__((weak))
void *memchr(const void *src, int c, size_t n) {
  const unsigned char *s = src;
  c = (unsigned char)c;
  for (; n && *s != c; s++, n--)
    ;
  return n ? (void *)s : 0;
}

//------------------------------------------------------------------------------

#endif  /* UTIL_MEM */
