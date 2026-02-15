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

char *strchr(const char *s, unsigned char c);
static inline char *strrchr(const char *s, unsigned char c) {
  size_t len = strlen(s);
  return mrchr(s, c, len + 1); }

char *strstr(const char *h, const char *n);

//------------------------------------------------------------------------------

#endif  /* UTIL_STR */
