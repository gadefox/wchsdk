#pragma once

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
