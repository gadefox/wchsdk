#pragma once

//------------------------------------------------------------------------------

#define PACK16(lo, hi)  ((uint16_t)(lo) | ((uint16_t)(hi) << 8))
#define PACK32(lo, hi)  ((uint32_t)(lo) | ((uint32_t)(hi) << 16))
#define PACK64(lo, hi)  ((uint64_t)(lo) | ((uint64_t)(hi) << 32))

//------------------------------------------------------------------------------

#if __GNUC__ > 10
#define ZICSR  ".option arch, +zicsr\n"
#else
#define ZICSR
#endif  /* __GNUC__ */

//------------------------------------------------------------------------------
// Clock, ticks

#ifndef MCU_HSI_FREQ
#define MCU_HSI_FREQ  24000000  // Default (Chip default)
#endif  /* MCU_HSI_FREQ */

#ifndef MCU_HSI_TRIM
#define MCU_HSI_TRIM  0x10      // Default (Chip default)
#endif  /* HSI_TRIM */

//------------------------------------------------------------------------------

#if MCU_XTAL_FREQ
#define MCU_BASE_FREQ  MCU_XTAL_FREQ
#else  /* MCU_HSI_FREQ */
#define MCU_BASE_FREQ  MCU_HSI_FREQ
#endif  /* MCU_HSI_FREQ || MCU_XTAL_FREQ */

//------------------------------------------------------------------------------

#if !MCU_PLL_MUL
#define MCU_PLL_MUL  2
#endif  /* MCU_PLL_MUL */

#define MCU_SYS_FREQ  (MCU_BASE_FREQ * MCU_PLL_MUL)

//------------------------------------------------------------------------------

#if MCU_STK_HCLK
#define MCU_TICKS_PER_US  (MCU_SYS_FREQ / 1000000)
#define MCU_TICKS_PER_MS  (MCU_SYS_FREQ / 1000)
#else
#define MCU_TICKS_PER_US  (MCU_SYS_FREQ / 8000000)
#define MCU_TICKS_PER_MS  (MCU_SYS_FREQ / 8000)
#endif  /* MCU_STK_HCLK */

//------------------------------------------------------------------------------

#define us_to_ticks(n) ((n) * MCU_TICKS_PER_US)
#define ms_to_ticks(n) ((n) * MCU_TICKS_PER_MS)

//------------------------------------------------------------------------------

#define time_elapsed(now, start)  ((int32_t)((now) - (start)))
#define stk_elapsed(deadline)     (time_elapsed(STK->CNT, deadline) >= 0)

//------------------------------------------------------------------------------
