#pragma once

#include <stdint.h>

/* Peripheral memory map */
#define SRAM_BASE         0x20000000 /* SRAM base address in the alias region */
#define PERIPH_BASE       0x40000000 /* Peripheral base address in the alias region */
#define CORE_PERIPH_BASE  0xE0000000 /* System peripherals base address in the alias region */

#define APB1PERIPH_BASE  PERIPH_BASE
#define APB2PERIPH_BASE  (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE   (PERIPH_BASE + 0x20000)

//------------------------------------------------------------------------------

#define CONCAT_BASE(a, b)  a##b##_BASE
#define EXP_BASE(a, b)     CONCAT_BASE(a, b)

//------------------------------------------------------------------------------

#ifdef __cplusplus
#define __I  volatie
#else
#define __I  volatile const     /* defines 'read only' permissions */
#endif

#define __O   volatile          /* defines 'write only' permissions     */
#define __IO  volatile          /* defines 'read / write' permissions   */

//------------------------------------------------------------------------------

// Let us do some compile-time error checking.
#define asm_assert(cond)  \
  .if (!(cond));          \
  .err;                   \
  .endif

//------------------------------------------------------------------------------

#define CONCAT(a, b)  a##b
#define EXP(a, b)     CONCAT(a, b)

#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MIN(a, b)  ((a) < (b) ? (a) : (b))

#define BETWEEN(x, l, h)  ((unsigned)((x) - (l)) < (h) - (l))

//------------------------------------------------------------------------------
