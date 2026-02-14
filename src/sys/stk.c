#include "wchsdk_cfg.h"

#if SYS_STK

#include "wch/hw/stk.h"
#include "wch/sys/stk.h"

//------------------------------------------------------------------------------

void stk_delay(uint32_t ticks) {
  uint32_t deadline = STK->CNT + ticks;
  while (time_elapsed(STK->CNT, deadline) < 0);
}

//------------------------------------------------------------------------------

// Computes a 64-bit STK timestamp from the current CPU.
// If the CPU supports a 64-bit STK, then it will make sure it
// did not race condition.  If it's a 32-bit STK, a virtual
// high word will be generated and incremented any time a wraparound
// is detected.
//
// In general, please do not use this function.  In 99% of cases, using 32-bit
// functions with proper rollover is better. For instance you can use
// TimeElapsed32( start, end ).
//
// This should only be used when you must act on time periods exceeding 2^31
// ticks.

uint64_t stk_get64(void) {
  uint32_t base = STK->CNT;

#if SYS_STK_CNTH
  uint32_t high = STK->CNTH;
  uint32_t check = STK->CNT;

  // If and only if check is higher than base can we guarantee high is
  // valid and matches the check else we need a new high.
  if (check < base)
    high = STK->CNTH;

  return PACK64(check, high);
#else

  static uint32_t last_base, high;
  if (last_base > base)
    high++;

  last_base = base;
  return PACK64(base, high);

#endif  /* SYS_STK_CNTH */
}

//------------------------------------------------------------------------------

#endif  /* SYS_STK */
