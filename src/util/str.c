#include "wchsdk_cfg.h"

#if UTIL_STR

#include <stdbool.h>
#include <stdint.h>

#include "wch/util/str.h"

//------------------------------------------------------------------------------

#if !UTIL_MEM
#error "string requires UTIL_MEM = 1"
#endif  /* UTIL_MEM */

//==============================================================================
// strxx functions

__attribute__((weak))
size_t strlen(const char *s) {
  const char *p = s;
  while (*p)
    p++;
  return p - s;
}

//------------------------------------------------------------------------------
// Optimized strlen for RISC-V 32-bit

__attribute__((weak))
size_t strlen_fast(const char *s) {
  const char *p = s;

  // Align pointer to 4-byte boundary
  uintptr_t misalign = (uintptr_t)p & 3;
  if (__builtin_expect(misalign != 0, 0)) {
    misalign = 4 - misalign;
    while (misalign--) {
      if (!*p)
        return p - s;
      p++;
    }
  }

  // 4 bytes
  const uint32_t *p32 = (const uint32_t *)p;

  while (true) {
    uint32_t w = *p32;

    if ((w - 0x01010101) & ~w & 0x80808080) {
      p = (const char *)p32;
      while (*p)
        p++;
      return p - s;
    }

    p32++;
  }
}

//------------------------------------------------------------------------------

__attribute__((weak))
size_t strnlen(const char *s, size_t n) {
  const char *p = memchr(s, '\0', n);
  return p ? p - s : n;
}

//------------------------------------------------------------------------------

__attribute__((weak))
char *strcpy(char *d, const char *s) {
  while (*s)
    *d++ = *s++;
  *d = '\0';  // Terminate
  return d;
}

//------------------------------------------------------------------------------

__attribute__((weak))
char *strncpy(char *d, const char *s, size_t n) {
  // Copy up to n characters
  while (n-- && *s)
    *d++ = *s++;
  *d = '\0';  // Terminate
  return d;
}

//------------------------------------------------------------------------------

__attribute__((weak))
int strcmp(const char *l, const char *r) {
  while (*l && *l == *r)
    l++, r++;
  return *(unsigned char *)l - *(unsigned char *)r;
}

//------------------------------------------------------------------------------

__attribute__((weak))
int strncmp(const char *l, const char *r, size_t n) {
  if (!n)
    return 0;

  while (n-- && *l && *l == *r)
    l++, r++;

  return *(unsigned char *)l - *(unsigned char *)r;
}

//------------------------------------------------------------------------------

__attribute__((weak))
char *strchr(const char *s, int c) {
  while (*s) {
    if (*s == c)
      return (char *)s;
    s++;
  }
  return *s == c ? (char *)s : NULL;    // Check for '\0' match
}

//==============================================================================
// KMP (Knuth-Morris-Pratt) string search algorithm

const char *strkmp(const char *haystack, size_t haylen, const char *needle, size_t neelen) {
  // Build LPS
  unsigned char len = 0;
  unsigned char lps[neelen];
  lps[0] = 0;

  for (size_t i = 1; i < neelen; ) {
    if (needle[i] == needle[len])
      lps[i++] = ++len;
    else if (len > 0)
      len = lps[len - 1];
    else
      lps[i++] = 0;
  }
  
  // Search
  const char *p = haystack;
  const char *end = p + haylen;
  unsigned char j = 0;

  while (p < end) {
    if (*p == needle[j]) {
      p++, j++;
      if (j == neelen)
        return p - neelen;  // Return pointer to start of match
    } else if (j > 0)
      j = lps[j - 1];
    else
      p++;
  }

  return NULL;
}

//------------------------------------------------------------------------------

const char *strstr_kmp(const char *haystack, const char *needle) {
  // Handle edge cases
  if (!needle || !needle[0])
    return haystack;  // Empty needle matches at start
  if (!haystack || !haystack[0])
    return NULL;      // Empty haystack
  
  // Get lengths
  size_t haylen = strlen(haystack);
  size_t neelen = strlen(needle);
  
  // Search using KMP
  return strkmp(haystack, haylen, needle, neelen);
}

//------------------------------------------------------------------------------
// Sunday String Search Algorithm

const char *strsun(const char *haystack, size_t haylen, const char *needle, size_t neelen) {
  const char *p = haystack;
  const char *end = (haystack + haylen) - neelen;
  
  while (p <= end) {
    // Match needle
    size_t j;
    for (j = 0; j < neelen && p[j] == needle[j]; j++);

    if (j == neelen)
      return p;  // Found - return pointer to start of match

    // Look at character AFTER current window
    if (p >= end)
      break;

    char next = p[neelen];

    // Find this character in needle (search backwards)
    size_t shift = neelen + 1;
    for (size_t k = neelen; k > 0; k--) {
      if (needle[k - 1] == next) {
        shift = neelen - (k - 1);
        break;
      }
    }
    p += shift;
  }

  return NULL;
}

//------------------------------------------------------------------------------

const char *strstr_sun(const char *haystack, const char *needle) {
  // Handle edge cases
  if (!needle || !needle[0])
    return haystack;  // Empty needle matches at start
  if (!haystack || !haystack[0])
    return NULL;      // Empty haystack

  // Get lengths
  size_t haylen = strlen(haystack);
  size_t neelen = strlen(needle);

  // Search using Sunday
  return strsun(haystack, haylen, needle, neelen);
}

//------------------------------------------------------------------------------

#endif  /* UTIL_STR */
