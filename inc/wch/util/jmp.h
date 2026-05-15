#if UTIL_JUMP

#pragma once

//------------------------------------------------------------------------------

// _JBTYPE using long long to make sure the alignment is align to 8 byte,
// otherwise in rv32imafd, store/restore FPR may mis-align.
#define JBTYPE  long long

#if defined(__riscv_abi_rve)
#define JBLEN  ((4 * sizeof(long)) / sizeof(long))
#elif defined(__riscv_float_abi_double)
#define JBLEN  ((14 * sizeof(long) + 12 * sizeof(double)) / sizeof(long))
#elif defined(__riscv_float_abi_single)
#define JBLEN  ((14 * sizeof(long) + 12 * sizeof(float)) / sizeof(long))
#else
#define JBLEN  ((14 * sizeof(long)) / sizeof(long))
#endif

//------------------------------------------------------------------------------

typedef JBTYPE jmp_buf[JBLEN];

//------------------------------------------------------------------------------

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

//------------------------------------------------------------------------------

#endif  /* UTIL_JUMP */
