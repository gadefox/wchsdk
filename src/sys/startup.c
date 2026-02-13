#include "wchsdk_cfg.h"

#if SYS_STARTUP

#include "wch/sys/startup.h"
#include "wch/hw/irq.h"
#include "wch/hw/stk.h"

//------------------------------------------------------------------------------

#if !SYS_IRQ
#error "startup requires SYS_IRQ = 1"
#endif  /* SYS_IRQ */

//------------------------------------------------------------------------------

#if SYS_ISR_IN_RAM
#define IRQ_SECTION  ".data.irq_entry"
#else
#define IRQ_SECTION  ".text.irq_entry"
#endif  /* SYS_ISR_IN_RAM */

//------------------------------------------------------------------------------

extern int main(void);

//------------------------------------------------------------------------------

__attribute__((naked)) __attribute((section(".text.reset_handler"))) __attribute__((used))
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

#if HPE_ENABLE  // Enabled nested and hardware (HPE) stack, since it's really good on the x035.
   "li      t0, 0x1888      \n\
    csrs    mstatus, t0     \n\
    li      t0, 0x0b        \n\
    csrw    0x804, t0       \n"
#else
   "li      a0, 0x1880      \n\
    csrw    mstatus, a0     \n"
#endif  /* HPE_ENABLE */

   "li      a3, 0x3         \n\
    la      a0, irq_entry   \n\
    or      a0, a0, a3      \n\
    csrw    mtvec, a0"
    :
    :
    : "a0", "a3", "memory");

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
2:"
    :
    :
    : "a0", "a1", "a2", "a3", "memory");

  // Setup the interrupt vector, processor status and INTSYSCR.
  asm volatile(
   "li      t0, 0x1F        \n\
    csrw    0xBC0, t0       \n\
    li      t0, 0x1888      \n\
    csrs    mstatus, t0     \n"

#if HPE_ENABLE  // Enabled nested and hardware (HPE) stack, since it's really good on the x035.
   "li      t0, 0x0B        \n\
    csrw    0x804, t0       \n"
#endif  /* HPE_ENABLE */
   "la      t0, irq_entry   \n\
    ori     t0, t0, 3       \n\
    csrw    mtvec, t0"
    :
    : [irq_entry]"r"(irq_entry)
    : "t0", "memory");

#if STK_HCLK
  STK->CTLR = STK_CTLR_STE | STK_CTLR_STCLK;
#else
  STK->CTLR = STK_CTLR_STE;
#endif  /* STK_HCLK */

  // set mepc to be main as the root app.
  asm volatile(
    "csrw   mepc, %[main]\n"
    "mret"
    :
    : [main]"r"(main));
}

//------------------------------------------------------------------------------

#if USE_ISR_IN_RAM

__attribute__((naked)) __attribute((section(".init"))) __attribute((naked))
void reset_entry(void) {
  asm volatile(
   ".align  2               \n\
    .option push;           \n\
    .option norvc;          \n\
    j       reset_handler   \n\
    .option pop             \n");
}

//------------------------------------------------------------------------------

__attribute__((naked)) __attribute((section(IRQ_SECTION))) __attribute((weak,alias("irq_entry_default"))) __attribute((naked))
void irq_entry(void);

__attribute__((naked)) __attribute((section(IRQ_SECTION))) __attribute((naked))
void irq_entry_default(void) {
  asm volatile(IRQ_VECTOR_TABLE_DEFAULT);
}

#else  /* !USE_ISR_IN_RAM */

//------------------------------------------------------------------------------

__attribute__((naked)) __attribute((section(".init"))) __attribute((weak,alias("irq_entry_default"))) __attribute((naked))
void irq_entry(void);

__attribute__((naked)) __attribute((section(".init"))) __attribute((naked))
void irq_entry_default(void) {
#if USE_TINYVECTOR
  asm volatile("\n\
    .align  2\n\
    .option push;\n\
    .option norvc;\n\
      j     reset_handler\n\
    .option pop;\n");
#else
  asm volatile(IRQ_VECTOR_TABLE_DEFAULT);
#endif  /* USE_TINYVECTOR */
}

#endif  /* USE_ISR_IN_RAM */

//------------------------------------------------------------------------------

#endif  /* SYS_STARTUP */
