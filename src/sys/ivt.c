#include "wchsdk_cfg.h"

#if SYS_CORE

#include "wch/hw/irq.h"
#include "wch/hw/stk.h"

#include "wch/sys/csr.h"
#include "wch/sys/ivt.h"
#include "wch/sys/stk.h"

#include "wch/util/mem.h"

//------------------------------------------------------------------------------

#if SYS_IVT_MEMFAST
#define MEMSET  memset_fast
#define MEMCPY  memcpy_fast
#else
#define MEMSET  memset
#define MEMCPY  memcpy
#endif  /* SYS_IVT_MEMFAST */

//------------------------------------------------------------------------------

extern uint32_t _sbss, _ebss, _edata, _data_lma, _data_vma;
extern int main(void);

//------------------------------------------------------------------------------

__attribute((section(".text.reset"))) __attribute__((naked)) __attribute__((used))
void reset_handler(void) {
  asm volatile(
   ".option push                        \n\
    .option norelax                     \n\
    la      gp, __global_pointer$       \n\
    .option pop                         \n\
    la      sp, _eusrstack              \n"
    : : : "memory");

  // Setup processor status and INTSYSCR.
#if SYS_HPE
  // Enabled nested and hw stack, since it's really good on the x035.
  csr_write_mstatus(MSTATUS_MIE | MSTATUS_MPIE | MSTATUS_MPP_M);
  csr_write_intsyscr(INTSYSCR_INESTENMRW | INTSYSCR_HWSTKEN);
#else
  csr_write_mstatus(MSTATUS_MPIE | MSTATUS_MPP_M);
#endif  /* SYS_HPE */

  // Setup the interrupt vector
  csr_write_mtvec((uint32_t)ivt_entry | MTVEC_IVT | MTVEC_ABS);

  // Clear global variables; Copy .data from flash to RAM
  MEMSET(&_sbss, 0, _ebss - _sbss);
  MEMCPY(&_data_vma, &_data_lma, _edata - _data_vma);

  // Set sys tick clock
  stk_init();

  // Set mepc to be main as the root app.
  csr_write_mepc((uint32_t)main);
  assert();
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

#endif  /* SYS_CORE */
