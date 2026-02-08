#pragma once

#include <stdint.h>

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
#define ASM_ASSERT(COND) \
  .if (!(COND)); \
  .err; \
  .endif

//------------------------------------------------------------------------------

#define CONCAT(A, B)  A##B
#define EXP(A, B)     CONCAT(A, B)

//------------------------------------------------------------------------------
