#include "wchsdk_cfg.h"

#if SYS_IVT

//#include "wch/hw/irq.h"
#include "wch/hw/stk.h"

#include "wch/sys/ivt.h"

//------------------------------------------------------------------------------

//#if !SYS_IRQ
//#error "startup requires SYS_IRQ = 1"
//#endif  /* SYS_IRQ */

//------------------------------------------------------------------------------

extern int main(void);

//------------------------------------------------------------------------------

__attribute((section(".text.reset"))) __attribute__((naked)) __attribute__((used))
void reset_handler(void) {
  asm volatile(
   ".option push            \n\
    .option norelax         \n\
    la      gp, __global_pointer$   \n\
    .option pop             \n\
    la      sp, _eusrstack  \n"

#if __GNUC__ > 10
    ".option arch, +zicsr   \n"
#endif
  // Setup the interrupt vector, processor status and INTSYSCR.

#if HPE_ENABLE
  // Enabled nested and hardware (HPE) stack, since it's really good on the x035.
  // mstatus = MIE | MPIE | MPP_M
   "li      t0, 0x1888      \n\
    csrs    mstatus, t0     \n\
    li      t0, 0x03        \n\
    csrw    0x804, t0       \n"     // csr: intsyscr: INESTENMRW | HWSTKEN
#else
  // mstatus = MPIE | MPP_M
   "li      a0, 0x1880      \n\
    csrw    mstatus, a0     \n"
#endif  /* HPE_ENABLE */

   "li      a3, 0x03        \n\
    la      a0, ivt_entry   \n\
    or      a0, a0, a3      \n\
    csrw    mtvec, a0" : : : "a0", "a3", "memory");

  // Careful: Use registers to prevent overwriting of self-data.
  // This clears out BSS.
  asm volatile(
   "la      a0,  _sbss      \n\
    la      a1,  _ebss      \n\
    li      a2,  0          \n\
    bge     a0, a1, 2f      \n\
1:  sw      a2,  0(a0)      \n\
    addi    a0, a0, 4       \n\
    blt     a0, a1, 1b      \n\
2:"
  // This loads DATA from FLASH to RAM.
   "la      a0, _data_lma   \n\
    la      a1, _data_vma   \n\
    la      a2, _edata      \n\
1:  beq     a1, a2, 2f      \n\
    lw      a3, 0(a0)       \n\
    sw      a3, 0(a1)       \n\
    addi    a0, a0, 4       \n\
    addi    a1, a1, 4       \n\
    bne     a1, a2, 1b      \n\
2:" : : : "a0", "a1", "a2", "a3", "memory");

#if SYS_STK_HCLK
  STK->CTLR = STK_CTLR_STE | STK_CTLR_STCLK;
#else
  STK->CTLR = STK_CTLR_STE;
#endif  /* SYS_STK_DIV8 */

  // Set mepc to be main as the root app.
  asm volatile(
    "csrw   mepc, %[main]   \n\
     mret" : : [main]"r"(main));
}

//------------------------------------------------------------------------------

#if SYS_IVT_RAM
#define IVT_SECTION  ".data.isr"
#else
#define IVT_SECTION  ".init"
#endif  /* SYS_IVT_RAM */

//------------------------------------------------------------------------------

__attribute((section(IVT_SECTION))) __attribute__((naked))
void ivt_entry(void) {
  asm volatile(IVT_DEFAULT);
}

//------------------------------------------------------------------------------

#endif  /* SYS_IVT */
