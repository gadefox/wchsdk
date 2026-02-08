#if UTIL_MEM

#pragma once

#include <stddef.h>

//------------------------------------------------------------------------------

int memcmp(const void *vl, const void *vr, size_t n);

void *memset(void *dest, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);

void *memchr(const void *src, int c, size_t n);
void *memrchr(const void *m, int c, size_t n);

//------------------------------------------------------------------------------

#endif  /* UTIL_MEM */
