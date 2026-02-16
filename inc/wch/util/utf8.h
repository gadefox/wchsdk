#ifdef UTIL_UTF8

#pragma once

#include <stddef.h>

//------------------------------------------------------------------------------
// UTF-8 range boundaries

#define UTF8_CONT_PREFIX   0x80      // 10xxxxxx
#define UTF8_CONT_MASK     0x3F      // 6 bits

#define UTF8_1BYTE_MAX     0x80      // 0-127: ASCII

#define UTF8_2BYTE_MAX     0x800     // 128-2047
#define UTF8_2BYTE_PREFIX  0xC0      // 110xxxxx
#define UTF8_2BYTE_MASK    0x1F      // 5 bits

#define UTF8_3BYTE_MAX     0x10000   // BMP end
#define UTF8_3BYTE_PREFIX  0xE0      // 1110xxxx
#define UTF8_3BYTE_MASK    0x0F      // 4 bits
#define UTF8_SURROGATE_LO  0xD800    // UTF-16 surrogate start
#define UTF8_SURROGATE_HI  0xE000    // UTF-16 surrogate end

#define UTF8_4BYTE_MAX     0x110000  // Unicode max
#define UTF8_4BYTE_PREFIX  0xF0      // 11110xxx
#define UTF8_4BYTE_MASK    0b111     // 3 bits

#define UTF8_5BYTE_PREFIX  0xF8      // 111110xx
#define UTF8_5BYTE_MASK    0b11      // 2 bits

//------------------------------------------------------------------------------

char *utf8_encode(char *s, wchar_t wc);
const char *utf8_decode(const char *s, wchar_t *wc);

//------------------------------------------------------------------------------

#endif /* UTIL_UTF8 */
