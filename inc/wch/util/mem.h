#if UTIL_MEM

#pragma once

#include <stddef.h>
#include <stdint.h>

//------------------------------------------------------------------------------

void *memchr(const void *ptr, int b, size_t n);
void *memrchr(const void *ptr, int b, size_t n);

//------------------------------------------------------------------------------

void *memcpy(void *restrict dst, const void *restrict src, size_t n);
void *memcpy_fast(void *restrict dst, const void *restrict src, size_t n);

//------------------------------------------------------------------------------

void *memset(void *ptr, int b, size_t n);
void *memset_fast(void *ptr, uint8_t b, size_t n);

//------------------------------------------------------------------------------

int wordcmp(const uint32_t *l32, const uint32_t *r32);
int memcmp(const void *pl, const void *vr, size_t n);
int memcmp_fast(const void *vl, const void *vr, size_t n);

//------------------------------------------------------------------------------

void *memmove(void *dst, const void *src, size_t n);

//------------------------------------------------------------------------------

#endif  /* UTIL_MEM */
