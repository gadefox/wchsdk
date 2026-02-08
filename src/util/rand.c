// Psuedo Random Number Generator using a Linear Feedback Shift Register
// Copyright ADBeta (c) 2024; Released under the MIT Licence

#include "wchsdk_cfg.h"

#if UTIL_RAND

#include "wch/util/rand.h"

//------------------------------------------------------------------------------

#ifndef UTIL_RAND_STRENGTH
#define UTIL_RAND_STRENGTH  2
#endif  /* UTIL_RAND_STRENGTH */

//------------------------------------------------------------------------------
// set the random LFSR values seed by default to a known-good value

static uint32_t lfsr = 0x747AA32F;

//------------------------------------------------------------------------------
// Updates the LFSR by getting a new tap bit, for MSB, then shifting
//  the LFSR >> 1, appending the new MSB.
//  Taps bits 0, 1, 21 and 31
//  return: 0x01 or 0x00, as a LSB translation of the tapped MSB for the LFSR
static uint8_t lfsr_update(void) {
  // Shifting to MSB to make calculations more efficient later
  uint32_t bit_31 = lfsr & 0x80000000;
  uint32_t bit_21 = (lfsr << 10) & 0x80000000;
  uint32_t bit_01 = (lfsr << 30) & 0x80000000;
  uint32_t bit_00 = (lfsr << 31) & 0x80000000;

  // Calculate the MSB to be put into the LFSR
  uint32_t msb = bit_31 ^ bit_21 ^ bit_01 ^ bit_00;
  // Shift the lfsr and append the MSB to it
  lfsr = (lfsr >> 1) | msb;
  // Return the LSB instead of MSB
  return msb >> 31;
}

//------------------------------------------------------------------------------
// Generates a Random 32-bit number, using the LFSR - by generating a random bit
// from LFSR taps, 32 times. return: a (psuedo)random 32-bit value

static uint32_t rand_gen(int bits) {
  uint32_t rand_out = 0;

  for (int i = 0; i < bits; i++) {
    // Shift the current rand value for the new LSB
    rand_out = rand_out << 1;
    // Append the LSB
    rand_out |= lfsr_update();
  }

  return rand_out;
}

//------------------------------------------------------------------------------
// Seeds the Random LFSR to the value passed

void rand_seed(const uint32_t seed_val) {
  lfsr = seed_val;
}

//------------------------------------------------------------------------------
// Generates a Random (32-bit) Number, based on the RANDOM_STRENGTH you have
// selected

uint32_t rand_new(void) {
  uint32_t rand_out = 0;

  // If RANDOM_STRENGTH is level 1, Update LFSR Once, then return it
#if UTIL_RAND_STRENGTH == 1
  // Update the LFSR, discard result, and return _lsfr raw
  (void)lfsr_update();
  rand_out = _rand_lfsr;
#endif  /* RANDOM_STRENGTH */

  // If RANDOM_STRENGTH is level 2, generate a 32-bit output, using 32 random
  // bits from the LFSR
#if UTIL_RAND_STRENGTH == 2
  rand_out = rand_gen(32);
#endif

  // If RANDOM_STRENGTH is level 3, generate 2 32-bit outputs, then XOR them together
#if UTIL_RAND_STRENGTH == 3
  uint32_t rand_a = rand_gen(32);
  uint32_t rand_b = rand_gen(32);
  rand_out = rand_a ^ rand_b;
#endif  /* RANDOM_STRENGTH */

  return rand_out;
}

//------------------------------------------------------------------------------

#endif  /* UTIL_RAND */
