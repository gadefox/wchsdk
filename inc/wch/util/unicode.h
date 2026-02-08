#ifdef UTIL_UNICODE

#pragma once

#include <stddef.h>

//------------------------------------------------------------------------------

extern int errno;

//------------------------------------------------------------------------------

/*
 * mbstate_t is an opaque object to keep conversion state, during multibyte
 * stream conversions.  The content must not be referenced by user programs.
 */

typedef void *mbstate_t;

//------------------------------------------------------------------------------

size_t wcrtomb(char *restrict s, wchar_t wc, mbstate_t *restrict st);

static inline int wctomb(char *s, wchar_t wc) {
  if (s)
    return wcrtomb(s, wc, 0);
  return 0;
}

//------------------------------------------------------------------------------

#endif /* UTIL_UNICODE */
