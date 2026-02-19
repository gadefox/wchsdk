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

#ifndef SYS_PLL
#define SYS_PLL  2
#endif  /* SYS_PLL */

//------------------------------------------------------------------------------

#if SYS_HSE_FREQ
#define SYSCLK  (SYS_HSE_FREQ * SYS_PLL)
#else  /* SYS_HSI_FREQ */
#define SYSCLK  (SYS_HSI_FREQ * SYS_PLL)
#endif  /* SYS_HSI_FREQ || SYS_HSE_FREQ */

//------------------------------------------------------------------------------
// Bus prescalers

#ifndef SYS_AHBP
#define SYS_AHBP  1         // AHB prescaler (1, 2, 4, 8, 16, ...)
#endif

#ifndef SYS_APB1P
#define SYS_APB1P  1        // APB1 prescaler (1, 2, 4, 8, 16)
#endif

#ifndef SYS_APB2P
#define SYS_APB2P  1        // APB2 prescaler (1, 2, 4, 8, 16)
#endif

//------------------------------------------------------------------------------
// Derived clocks

#define HCLK   (SYSCLK / SYS_AHBP)
#define PCLK1  (HCLK / SYS_APB1P)
#define PCLK2  (HCLK / SYS_APB2P)

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
// Nop

static inline void nop(void) {
  asm volatile("nop"); }

static inline void assert(void) {
  asm volatile("1: j 1b"); }

//------------------------------------------------------------------------------
