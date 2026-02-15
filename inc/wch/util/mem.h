#if UTIL_MEM

#pragma once

#include <stddef.h>
#include <stdint.h>

//------------------------------------------------------------------------------

void *mchr(const void *ptr, uint8_t b, size_t n);
void *mrchr(const void *ptr, uint8_t b, size_t n);

//------------------------------------------------------------------------------

void *mcpy(void *restrict dst, const void *restrict src, size_t n);
void *mcpy_fast(void *restrict dst, const void *restrict src, size_t n);

//------------------------------------------------------------------------------

void *mset(void *ptr, uint8_t b, size_t n);
void *mset_fast(void *ptr, uint8_t b, size_t n);

//------------------------------------------------------------------------------

int mcmp(const void *pl, const void *vr, size_t n);
int mcmp_fast(const void *vl, const void *vr, size_t n);

//------------------------------------------------------------------------------

void *mmove(void *dst, const void *src, size_t n);

//------------------------------------------------------------------------------

#endif  /* UTIL_MEM */
