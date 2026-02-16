#if SYS_STK

#pragma once

#include <stdint.h>

#include "wch/hw/stk.h"
#include "wch/sys/def.h"

//------------------------------------------------------------------------------

#if SYS_STK_DIV8
#define STKCLK  (HCLK / 8)   // HCLK/8 for time base
#else
#define STKCLK  HCLK         // HCLK for time base
#endif  /* SYS_STK_DIV8 */

//------------------------------------------------------------------------------

#define STK_MS  (STKCLK / 1000)
#define STK_US  (STK_MS / 1000)

#define ms_to_stk(n) ((n) * STK_MS)
#define us_to_stk(n) ((n) * STK_US)

#define stk_elapsed(deadline)  (time_elapsed(STK->CNT, deadline) >= 0)

//------------------------------------------------------------------------------
// NOTE: MCUs without a 64-bit timer must call this function at least once
// every 2^32 ticks to ensure that the most significant bits are not lost.

uint64_t stk_get64(void);

//------------------------------------------------------------------------------

static inline void stk_delay(uint32_t ticks) {
  uint32_t deadline = STK->CNT + ticks;
  while (!stk_elapsed(deadline)); }

static inline void delay_ms(uint32_t ms) {
  uint32_t ticks = ms_to_stk(ms);
  stk_delay(ticks); }

static inline void delay_us(uint32_t us) {
  uint32_t ticks = us_to_stk(us);
  stk_delay(ticks); }

//------------------------------------------------------------------------------

#endif  /* SYS_STK */
