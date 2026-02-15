#if UTIL_STR

#pragma once

#include <stddef.h>
#include "wch/util/mem.h"

//------------------------------------------------------------------------------

size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);

//------------------------------------------------------------------------------

char *strcpy(char *d, const char *s);
char *strncpy(char *d, const char *s, size_t n);

//------------------------------------------------------------------------------

int strcmp(const char *l, const char *r);
int strncmp(const char *l, const char *r, size_t n);

//------------------------------------------------------------------------------

char *strchr(const char *s, int c);

static inline char *strrchr(const char *s, int c) {
  size_t len = strlen(s);
  return memrchr(s, c, len + 1); }

//==============================================================================
// KMP (Knuth-Morris-Pratt) string search algorithm
// Memory:  O(m) bytes - only pattern length (LPS table on stack)
// Time:    O(n+m) preprocessing + search - guaranteed linear
// Average: O(n) - very fast, no backtracking in text
// Worst:   O(n+m) - still linear even for repetitive patterns
// Use cases:
// - Repeated searches with same pattern (LPS computed once)
// - Guaranteed linear time required (real-time systems)
// - Pattern has repetitive structure (e.g., "ababab")
// - Text scanning where no backtracking allowed

const char *strkmp(const char *haystack, size_t haylen, const char *needle, size_t neelen);
const char *strstr_kmp(const char *haystack, const char *needle);  // wrapper

//------------------------------------------------------------------------------
// Sunday String Search Algorithm
// Memory:  0 bytes - no preprocessing table needed
// Time:    O(n×m) worst case, O(n/m) average - often faster than KMP
// Average: O(n/m) - very fast for random text
// Worst:   O(n×m) - slow for repetitive patterns
// Use cases:
// - One-time searches (different patterns each time)
// - Absolute minimum memory required (zero overhead)
// - Random/non-repetitive text
// - Short patterns in large text
// - When average case performance matters more than worst case

const char *str_sun(const char *haystack, size_t haylen, const char *needle, size_t neelen);
const char *strstr_sun(const char *haystack, const char *needle);  // wrapper

//------------------------------------------------------------------------------

#endif  /* UTIL_STR */
