#include "wchsdk_cfg.h"

#if UTIL_MEM

#include <stdint.h>
#include "wch/util/mem.h"

//------------------------------------------------------------------------------

__attribute__((weak))
void *mchr(const void *ptr, uint8_t b, size_t n) {
  const uint8_t *p = ptr;

  while (n--) {
    if (*p == b)
      return (void *)p;
    p++;
  }
  return NULL;
}

//------------------------------------------------------------------------------

__attribute__((weak))
void *mrchr(const void *ptr, uint8_t b, size_t n) {
  const uint8_t *p = (const uint8_t *)ptr + n;

  while (n--) {
    p--;
    if (*p == b)
      return (void *)p;
  }
  return NULL;
}

//------------------------------------------------------------------------------
// Simple memcpy - returns pointer to end (dst + n)

__attribute__((weak))
void *mcpy(void *restrict dst, const void *restrict src, size_t n) {
  uint8_t *d = (uint8_t *)dst;
  const uint8_t *s = (const uint8_t *)src;

  while (n--)
    *d++ = *s++;
  return d;
}

//------------------------------------------------------------------------------
// Optimized memcpy for RISC-V 32-bit
// Returns: pointer to end of destination (dst + n) for easy buffer chaining

void* mcpy_fast(void *restrict dst, const void *restrict src, size_t n) {
  // Small blocks - direct copy
  if (n < 8)
    return mcpy(dst, src, n);

  // Optimized copy
  uint8_t *d = (uint8_t *)dst;
  const uint8_t *s = (const uint8_t *)src;

  // Align destination to 4-byte boundary
  uintptr_t misalign = (uintptr_t)d & 3;
  if (__builtin_expect(misalign != 0, 0)) {
    misalign = 4 - misalign;
    n -= misalign;

    while (misalign--)
      *d++ = *s++;
  }

  uint32_t *d32 = (uint32_t *)d;

  // Shift-based unaligned load
  misalign = (uintptr_t)s & 3;
  if (__builtin_expect(misalign != 0, 0)) {
    const uint32_t *s32 = (const uint32_t *)(s - misalign);
    uint32_t prev = *s32++;
    int rshift = misalign << 3;
    int lshift = 32 - rshift;

    while (n >= 4) {
      uint32_t w = *s32++;
      *d32++ = (w << lshift) | (prev >> rshift);
      prev = w;
      n -= 4;
    }

    s = (const uint8_t *)s32 - (4 - misalign);
  } else {
    // Fast path: both aligned
    const uint32_t *s32 = (const uint32_t *)s;

    // 32-byte blocks (8x load/store)
    while (n >= 32) {
      __builtin_prefetch(s32 + 16, 0, 0);
      __builtin_prefetch(d32 + 16, 1, 0);

      d32[0] = s32[0];
      d32[1] = s32[1];
      d32[2] = s32[2];
      d32[3] = s32[3];
      d32[4] = s32[4];
      d32[5] = s32[5];
      d32[6] = s32[6];
      d32[7] = s32[7];

      d32 += 8;
      s32 += 8;
      n -= 32;
    }

    // 4-byte remainder
    while (n >= 4) {
      *d32++ = *s32++;
      n -= 4;
    }

    s = (const uint8_t *)s32;
  }

  // Tail (0-3 bytes)
  d = (uint8_t *)d32;
  while (n--)
    *d++ = *s++;
  return d;
}

//------------------------------------------------------------------------------
// Simple memset - returns pointer to end (dst + n)

__attribute__((weak))
void *mset(void *ptr, uint8_t b, size_t n) {
  uint8_t *p = (uint8_t *)ptr;

  while (n--)
    *p++ = b;
  return p;
}

//------------------------------------------------------------------------------
// Optimized memset for RISC-V 32-bit
// Returns: pointer to end of destination (dst + n) for easy buffer chaining

void* mset_fast(void *ptr, uint8_t b, size_t n) {
  // Small blocks - direct set
  if (n < 8)
    return mset(ptr, b, n);

  // Optimized set
  uint8_t *p = (uint8_t *)ptr;

  // Align destination to 4-byte boundary
  uintptr_t misalign = (uintptr_t)p & 3;
  if (__builtin_expect(misalign != 0, 0)) {
    misalign = 4 - misalign;
    n -= misalign;

    while (misalign--)
      *p++ = b;
  }
  
  // Build 32-bit word with repeated byte pattern
  uint32_t w = b;
  w|= w << 8;   // 0x000000AB -> 0x0000ABAB
  w |= w << 16;  // 0x0000ABAB -> 0xABABABAB

  uint32_t *p32 = (uint32_t *)p;

  // 32-byte blocks (8x store)
  while (n >= 32) {
    __builtin_prefetch(p32 + 16, 1, 0);

    p32[0] = w;
    p32[1] = w;
    p32[2] = w;
    p32[3] = w;
    p32[4] = w;
    p32[5] = w;
    p32[6] = w;
    p32[7] = w;

    p32 += 8;
    n -= 32;
  }

  // 4-byte remainder
  while (n >= 4) {
    *p32++ = w;
    n -= 4;
  }

  // Tail (0-3 bytes)
  p = (uint8_t *)p32;
  while (n--)
    *p++ = b;
  return p;
}

//------------------------------------------------------------------------------
// Simple memcmp

__attribute__((weak))
int mcmp(const void *vl, const void *vr, size_t n) {
  const uint8_t *l = (const uint8_t *)vl;
  const uint8_t *r = (const uint8_t *)vr;

  while (n--) {
    if (*l != *r)
      return *l - *r;
    l++;
    r++;
  }
  return 0;
}

//------------------------------------------------------------------------------

static int wordcmp(const uint32_t *l32, const uint32_t *r32) {
  const uint8_t *l = (const uint8_t *)l32;
  const uint8_t *r = (const uint8_t *)r32;

  if (l[0] != r[0])   return l[0] - r[0];
  if (l[1] != r[1])   return l[1] - r[1];
  if (l[2] != r[2])   return l[2] - r[2];
  /*  l[3] != r[3] */ return l[3] - r[3];
}

//------------------------------------------------------------------------------

int mcmp_fast(const void *vl, const void *vr, size_t n) {
  // Small blocks - direct compare
  if (n < 8)
    return mcmp(vl, vr, n);

  const uint8_t *l = (const uint8_t *)vl;
  const uint8_t *r = (const uint8_t *)vr;

  // Align left pointer to 4-byte boundary
  uintptr_t misalign = (uintptr_t)l & 3;
  if (__builtin_expect(misalign != 0, 0)) {
    misalign = 4 - misalign;
    n -= misalign;

    while (misalign--) {
      if (__builtin_expect(*l != *r, 0))
        return *l - *r;
      l++;
      r++;
    }
  }

  const uint32_t *l32 = (const uint32_t *)l;
  
  // Shift-based unaligned compare
  misalign = (uintptr_t)r & 3;
  if (__builtin_expect(misalign != 0, 0)) {
    const uint32_t *r32 = (const uint32_t *)(r - misalign);
    uint32_t prev = *r32++;
    int rshift = misalign << 3;
    int lshift = 32 - rshift;

    while (n >= 4) {
      uint32_t w = *r32++;
      uint32_t r_word = (w << lshift) | (prev >> rshift);

      if (__builtin_expect(*l32 != r_word, 0))
        return wordcmp(l32, (const uint32_t *)&r_word);

      l32++;
      prev = w;
      n -= 4;
    }

    r = (const uint8_t *)r32 - (4 - misalign);
  } else {
    // Fast path: both aligned
    const uint32_t *r32 = (const uint32_t *)r;

    // 32-byte blocks (8x compare)
    while (n >= 32) {
    __builtin_prefetch(l32 + 16, 0, 0);
    __builtin_prefetch(r32 + 16, 0, 0);

      if (__builtin_expect(l32[0] != r32[0], 0)) return wordcmp(&l32[0], &r32[0]);
      if (__builtin_expect(l32[1] != r32[1], 0)) return wordcmp(&l32[1], &r32[1]);
      if (__builtin_expect(l32[2] != r32[2], 0)) return wordcmp(&l32[2], &r32[2]);
      if (__builtin_expect(l32[3] != r32[3], 0)) return wordcmp(&l32[3], &r32[3]);
      if (__builtin_expect(l32[4] != r32[4], 0)) return wordcmp(&l32[4], &r32[4]);
      if (__builtin_expect(l32[5] != r32[5], 0)) return wordcmp(&l32[5], &r32[5]);
      if (__builtin_expect(l32[6] != r32[6], 0)) return wordcmp(&l32[6], &r32[6]);
      if (__builtin_expect(l32[7] != r32[7], 0)) return wordcmp(&l32[7], &r32[7]);

      l32 += 8;
      r32 += 8;
      n -= 32;
    }

    // 4-byte remainder
    while (n >= 4) {
      if (__builtin_expect(*l32 != *r32, 0))
        return wordcmp(l32, r32);
      l32++;
      r32++;
      n -= 4;
    }
    
    r = (const uint8_t *)r32;
  }
  
  // Tail (0-3 bytes)
  l = (const uint8_t *)l32;
  while (n--) {
    if (__builtin_expect(*l != *r, 0))
      return *l - *r;
    l++;
    r++;
  }
  
  return 0;
}

//------------------------------------------------------------------------------

__attribute__((weak))
void *mmove(void *dst, const void *src, size_t n) {
  uint8_t *d = (uint8_t *)dst;
  const uint8_t *s = (const uint8_t *)src;

  if (d < s) {
    // Copy forward
    while (n--)
      *d++ = *s++;
    return d;
  }

  if (d > s) {
    // Copy backward
    while (n) {
      n--;
      d[n] = s[n];
    }
  }

  return d + n;
}

//------------------------------------------------------------------------------

#endif  /* UTIL_MEM */
