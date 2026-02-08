// User-configurable macros (see wchsdk_cfg.h):
//  UTIL_RAND_STRENGTH:
//   1: Takes the LFSR variable, shifts and taps it then returns it as-is.
//      This is very fast, and provides basic random number generation.
//   2: Generates 32 random bits, which make up a 32-bit value.
//   3: Generates two 32-bit random values, then XORs them together.

#if UTIL_RAND

#pragma once

#include <stdint.h>

//------------------------------------------------------------------------------

void rand_seed(const uint32_t seed_val);
uint32_t rand_new(void);

//------------------------------------------------------------------------------

#endif  /* UTIL_RAND */
