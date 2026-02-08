#if SYS_STK

#pragma once

#include <stdint.h>
#include "wch/mcu/def.h"

//------------------------------------------------------------------------------

void stk_delay(uint32_t ticks);

// Get a 64-bit timestamp.  Please in general try to use 32-bit timestamps
// whenever possible.  Use functions that automatically handle rollover
// correctly like TimeElapsed32( start, end ).  Only use this in cases where
// you must act on time periods exceeding 2^31 ticks.
//
// Also, if you are on a platform without a hardware 64-bit timer, you must
// call this function at least once every 2^32 ticks to make sure MSBs aren't
// lost.
uint64_t stk_get64(void);

//------------------------------------------------------------------------------

static inline void delay_us(uint32_t us) {
  stk_delay(us_to_ticks(us)); }

static inline void delay_ms(uint32_t ms) {
  stk_delay(ms_to_ticks(ms)); }

//------------------------------------------------------------------------------

#endif  /* SYS_STK */
