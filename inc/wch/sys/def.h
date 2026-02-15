#pragma once

//------------------------------------------------------------------------------

#define PACK16(lo, hi)  ((uint16_t)(lo) | ((uint16_t)(hi) << 8))
#define PACK32(lo, hi)  ((uint32_t)(lo) | ((uint32_t)(hi) << 16))
#define PACK64(lo, hi)  ((uint64_t)(lo) | ((uint64_t)(hi) << 32))

//------------------------------------------------------------------------------

#define BITS(b)     (1 << (b))
#define BITR(x, b)  (((x) >> (b)) & 1)

//------------------------------------------------------------------------------

#if __GNUC__ > 10
#define ZICSR  ".option arch, +zicsr\n"
#else
#define ZICSR
#endif  /* __GNUC__ */

//------------------------------------------------------------------------------
// Clock, ticks

#ifndef SYS_HSI_FREQ
#define SYS_HSI_FREQ  24000000  // Default (Chip default)
#endif  /* SYS_HSI_FREQ */

#ifndef SYS_HSI_TRIM
#define SYS_HSI_TRIM  0x10      // Default (Chip default)
#endif  /* SYS_HSI_TRIM */

#ifndef SYS_PLL_MUL
#define SYS_PLL_MUL  2
#endif  /* SYS_PLL_MUL */

//------------------------------------------------------------------------------

#if SYS_XTAL_FREQ
#define BASE_FREQ  SYS_XTAL_FREQ
#else  /* SYS_HSI_FREQ */
#define BASE_FREQ  SYS_HSI_FREQ
#endif  /* SYS_HSI_FREQ || SYS_XTAL_FREQ */

#define HCLK_FREQ  (BASE_FREQ * SYS_PLL_MUL)

//------------------------------------------------------------------------------

#define time_elapsed(now, start)  ((int32_t)((now) - (start)))

//------------------------------------------------------------------------------
// Add a certain number of nops.
// NOTE: These are usually executed in pairs and take two cycles,
// so you typically would use 0, 2, 4, etc.

#define NOPS(n)  asm volatile(\
                   ".rept " #n "\n \
                    c.nop       \n \
                    .endr")

//------------------------------------------------------------------------------
// nop

static inline void nop(void) {
  asm volatile("nop"); }

//------------------------------------------------------------------------------
