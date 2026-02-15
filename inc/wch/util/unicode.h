#ifdef UTIL_UNICODE

#pragma once

#include <stddef.h>

//------------------------------------------------------------------------------

extern int errno;

//------------------------------------------------------------------------------
// mbstate_t is an opaque object to keep conversion state, during multibyte
// stream conversions.  The content must not be referenced by user programs.

typedef void *mbstate_t;

//------------------------------------------------------------------------------

size_t wcrtomb(char *restrict s, wchar_t wc, mbstate_t *restrict st);

static inline size_t wctomb(char *s, wchar_t wc) {
  if (!s)
    return 0;
  return wcrtomb(s, wc, NULL); }

//------------------------------------------------------------------------------

#endif /* UTIL_UNICODE */
