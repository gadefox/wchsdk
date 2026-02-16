#include "wchsdk_cfg.h"

#if UTIL_JUMP

#include "wch/util/jmp.h"

//------------------------------------------------------------------------------
// CH32V003 MCU uses 32-bit single-precision floating point only

#if defined(__riscv_float_abi_double)
#define FLOAD(src, offset, dst)   "fld " #src ", " #offset "*8(" #dst ")\n"
#define FSTORE(dst, offset, src)  "fsd " #dst ", " #offset "*8(" #src ")\n"
#elif defined(__riscv_float_abi_single)
#define FLOAD(src, offset, dst)   "flw " #src ", " #offset "*4(" #dst ")\n"
#define FSTORE(dst, offset, src)  "fsw " #dst ", " #offset "*4(" #src ")\n"
#endif

//------------------------------------------------------------------------------

__attribute__((naked))
int setjmp(jmp_buf env) {
  asm volatile(
    // Common registers
    "sw ra, 0*4(a0)\n"
    "sw s0, 1*4(a0)\n"
    "sw s1, 2*4(a0)\n"
    "sw sp, 3*4(a0)\n"

  // RV32I only registers
#ifndef __riscv_abi_rve
    "sw s2, 4*4(a0)\n"
    "sw s3, 5*4(a0)\n"
    "sw s4, 6*4(a0)\n"
    "sw s5, 7*4(a0)\n"
    "sw s6, 8*4(a0)\n"
    "sw s7, 9*4(a0)\n"
    "sw s8, 10*4(a0)\n"
    "sw s9, 11*4(a0)\n"
    "sw s10, 12*4(a0)\n"
    "sw s11, 13*4(a0)\n"
#endif  /* __riscv_abi_rve */

  // FPU registers
#ifdef FSTORE
    FSTORE(fs2, 14, a0)
    FSTORE(fs3, 15, a0)
    FSTORE(fs4, 16, a0)
    FSTORE(fs5, 17, a0)
    FSTORE(fs6, 18, a0)
    FSTORE(fs7, 19, a0)
    FSTORE(fs8, 20, a0)
    FSTORE(fs9, 21, a0)
    FSTORE(fs10, 22, a0)
    FSTORE(fs11, 23, a0)
#endif  /* FSTORE */

    "li a0, 0\n"
    "ret\n");
}

//------------------------------------------------------------------------------

__attribute__((naked)) void longjmp(jmp_buf env, int val) {
  asm volatile(
    // Common registers
    "lw ra, 0*4(a0)\n"
    "lw s0, 1*4(a0)\n"
    "lw s1, 2*4(a0)\n"
    "lw sp, 3*4(a0)\n"

  // RV32I only registers
#ifndef __riscv_abi_rve
    "lw s2, 4*4(a0)\n"
    "lw s3, 5*4(a0)\n"
    "lw s4, 6*4(a0)\n"
    "lw s5, 7*4(a0)\n"
    "lw s6, 8*4(a0)\n"
    "lw s7, 9*4(a0)\n"
    "lw s8, 10*4(a0)\n"
    "lw s9, 11*4(a0)\n"
    "lw s10, 12*4(a0)\n"
    "lw s11, 13*4(a0)\n"
#endif  /* __riscv_abi_rve */

  // FPU registers
#ifdef FLOAD
    FLOAD(fs2, 14, a0)
    FLOAD(fs3, 15, a0)
    FLOAD(fs4, 16, a0)
    FLOAD(fs5, 17, a0)
    FLOAD(fs6, 18, a0)
    FLOAD(fs7, 19, a0)
    FLOAD(fs8, 20, a0)
    FLOAD(fs9, 21, a0)
    FLOAD(fs10, 22, a0)
    FLOAD(fs11, 23, a0)
#endif  /* FLOAD */

    "seqz a0, a1\n"  // a0 = (a1 == 0) ? 1 : 0
    "add  a0, a0, a1\n"
    "ret\n");
  __builtin_unreachable(); // Disable warning about no return.
}

//------------------------------------------------------------------------------

#endif  /* UTIL_JUMP */
