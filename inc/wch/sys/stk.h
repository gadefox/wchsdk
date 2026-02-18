#if SYS_CORE

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/stk.h"
#include "wch/sys/def.h"

//------------------------------------------------------------------------------

#if SYS_STK_HCLK
#define STKCLK  HCLK         // HCLK for time base
#else
#define STKCLK  (HCLK / 8)   // HCLK/8 for time base
#endif  /* SYS_STK_HCLK */

//------------------------------------------------------------------------------

#define STK_MS  (STKCLK / 1000)
#define STK_US  (STK_MS / 1000)

#define ms_to_stk(n) ((n) * STK_MS)
#define us_to_stk(n) ((n) * STK_US)

//------------------------------------------------------------------------------

static inline uint32_t stk_get_count(void) {
  return STK->CNTL; }

#if SYS_STK_CNTH
static inline uint32_t stk_get_count_high(void) {
  return STK->CNTH; }
#endif  /* SYS_STK_CNTH */
 
//------------------------------------------------------------------------------

static inline bool stk_elapsed(uint32_t deadline) {
  uint32_t now = stk_get_count();
  return time_elapsed(now, deadline) >= 0; }

static inline void stk_delay(uint32_t ticks) {
  uint32_t deadline = stk_get_count() + ticks;
  while (!stk_elapsed(deadline)); }

static inline void delay_ms(uint32_t ms) {
  uint32_t ticks = ms_to_stk(ms);
  stk_delay(ticks); }

static inline void delay_us(uint32_t us) {
  uint32_t ticks = us_to_stk(us);
  stk_delay(ticks); }

//------------------------------------------------------------------------------

static inline void stk_init(void) {
#if SYS_STK_HCLK
  STK->CTLR = STK_CTLR_STE | STK_CTLR_STCLK;
#else
  STK->CTLR = STK_CTLR_STE;
#endif  /* SYS_STK_HCLK */
}

//------------------------------------------------------------------------------
// NOTE: MCUs without a 64-bit timer must call this function at least once
// every 2^32 ticks to ensure that the most significant bits are not lost.

uint64_t stk_get64(void);

//------------------------------------------------------------------------------

#endif  /* SYS_CORE */
