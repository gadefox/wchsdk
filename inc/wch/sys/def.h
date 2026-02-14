#pragma once

//------------------------------------------------------------------------------

#define PACK16(lo, hi)  ((uint16_t)(lo) | ((uint16_t)(hi) << 8))
#define PACK32(lo, hi)  ((uint32_t)(lo) | ((uint32_t)(hi) << 16))
#define PACK64(lo, hi)  ((uint64_t)(lo) | ((uint64_t)(hi) << 32))

//------------------------------------------------------------------------------

#define BITR(x, b)  (((x) >> (b)) & 1)
#define BITS(b)     (1 << (b))

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
#endif  /* HSI_TRIM */

//------------------------------------------------------------------------------

#if SYS_XTAL_FREQ
#define SYS_BASE_FREQ  SYS_XTAL_FREQ
#else  /* SYS_HSI_FREQ */
#define SYS_BASE_FREQ  SYS_HSI_FREQ
#endif  /* SYS_HSI_FREQ || SYS_XTAL_FREQ */

//------------------------------------------------------------------------------

#if !SYS_PLL_MUL
#define SYS_PLL_MUL  2
#endif  /* SYS_PLL_MUL */

#define SYS_FREQ  (SYS_BASE_FREQ * SYS_PLL_MUL)

//------------------------------------------------------------------------------

#if SYS_STK_HCLK
#define SYS_TICKS_PER_US  (SYS_FREQ / 1000000)
#define SYS_TICKS_PER_MS  (SYS_FREQ / 1000)
#else
#define SYS_TICKS_PER_US  (SYS_FREQ / 8000000)
#define SYS_TICKS_PER_MS  (SYS_FREQ / 8000)
#endif  /* SYS_STK_HCLK */

//------------------------------------------------------------------------------

#define us_to_ticks(n) ((n) * SYS_TICKS_PER_US)
#define ms_to_ticks(n) ((n) * SYS_TICKS_PER_MS)

//------------------------------------------------------------------------------

#define time_elapsed(now, start)  ((int32_t)((now) - (start)))
#define stk_elapsed(deadline)     (time_elapsed(STK->CNT, deadline) >= 0)

//------------------------------------------------------------------------------
