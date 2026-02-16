#include "wchsdk_cfg.h"

#if UTIL_UTF8

#include "wch/util/def.h"
#include "wch/util/utf8.h"

//------------------------------------------------------------------------------

__attribute__((weak))
char *utf8_encode(char *s, wchar_t wc) {
  unsigned int w = wc;

  if (w < UTF8_1BYTE_MAX) {
    *s++ = w;
    return s;
  }
  if (w < UTF8_2BYTE_MAX) {
    *s++ = UTF8_2BYTE_PREFIX | (w >> 6);
    *s++ = UTF8_CONT_PREFIX | (w & UTF8_CONT_MASK);
    return s;
  }
  if (w < UTF8_SURROGATE_LO || BETWEEN(w, UTF8_SURROGATE_HI, UTF8_3BYTE_MAX)) {
    *s++ = UTF8_3BYTE_PREFIX | (w >> 12);
    *s++ = UTF8_CONT_PREFIX | ((w >> 6) & UTF8_CONT_MASK);
    *s++ = UTF8_CONT_PREFIX | (w & UTF8_CONT_MASK);
    return s;
  }
  if (BETWEEN(w, UTF8_3BYTE_MAX, UTF8_4BYTE_MAX)) {
    *s++ = UTF8_4BYTE_PREFIX | (w >> 18);
    *s++ = UTF8_CONT_PREFIX | ((w >> 12) & UTF8_CONT_MASK);
    *s++ = UTF8_CONT_PREFIX | ((w >> 6) & UTF8_CONT_MASK);
    *s++ = UTF8_CONT_PREFIX | (w & UTF8_CONT_MASK);
    return s;
  }

  return NULL;  // Invalid codepoint
}

//------------------------------------------------------------------------------

__attribute__((weak))
const char *utf8_decode(const char *s, wchar_t *wc) {
  const unsigned char *p = (const unsigned char *)s;
  unsigned int w = *p++;

  // 1-byte: 0xxxxxxx
  if (w < UTF8_1BYTE_MAX)
    *wc = w;
  else if (BETWEEN(w, UTF8_2BYTE_PREFIX, UTF8_3BYTE_PREFIX)) {
    // 2-byte: 110xxxxx 10xxxxxx
    w = (w & UTF8_2BYTE_MASK) << 6;
    w |= *p++ & UTF8_CONT_MASK;

    *wc = w;
  } else if (BETWEEN(w, UTF8_3BYTE_PREFIX, UTF8_4BYTE_PREFIX)) {
    // 3-byte: 1110xxxx 10xxxxxx 10xxxxxx
    w = (w & UTF8_3BYTE_MASK) << 12;
    w |= (*p++ & UTF8_CONT_MASK) << 6;
    w |= *p++ & UTF8_CONT_MASK;

    *wc = w;
  } else if (BETWEEN(w, UTF8_4BYTE_PREFIX, 0xF8)) {
    // 4-byte: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    w = (w & UTF8_4BYTE_MASK) << 18;
    w |= (*p++ & UTF8_CONT_MASK) << 12;
    w |= (*p++ & UTF8_CONT_MASK) << 6;
    w |= *p++ & UTF8_CONT_MASK;

    *wc = w;
  } else
    *wc = 0xFFFD;  // Invalid UTF-8: replacement character

  return (const char *)p;
}

//------------------------------------------------------------------------------
__attribute__((weak))
size_t utf8_charlen(const char *s) {
  unsigned char w = *(unsigned char *)s;
  
  if (w < UTF8_1BYTE_MAX)
    return 1;
  if (BETWEEN(w, UTF8_2BYTE_PREFIX, UTF8_3BYTE_PREFIX))
    return 2;
  if (BETWEEN(w, UTF8_3BYTE_PREFIX, UTF8_4BYTE_PREFIX))
    return 3;
  if (BETWEEN(w, UTF8_4BYTE_PREFIX, UTF8_4BYTE_PREFIX + UTF8_4BYTE_MASK + 1))
    return 4;
  
  return 1;  // Invalid - treat as 1 byte
}

//------------------------------------------------------------------------------

#endif /* UTIL_UTF8 */
