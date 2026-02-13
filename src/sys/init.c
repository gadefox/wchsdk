#include "wchsdk_cfg.h"

#if SYS_INIT

#include "wch/hw/flash.h"
#include "wch/hw/rcc.h"
#include "wch/sys/def.h"
#include "wch/sys/init.h"
#include "wch/io/dbg.h"
#include "wch/io/uart.h"

//------------------------------------------------------------------------------

#if XTAL_BYPASS
#define BYPASS  RCC_HSEBYP
#else
#define BYPASS  0
#endif  /* XTAL_BYPASS */

#if SYS_CLK_SEC
#define CLKSEC  RCC_CSSON  // Enable clock security system
#else
#define CLKSEC  0
#endif  /* SYS_CLK_SEC */

//------------------------------------------------------------------------------

#ifdef SYS_CONSTRUCTORS

extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);

void call_constructors(void) {
  for (void (**ctor)(void) = __init_array_start; ctor < __init_array_end; ++ctor)
    (*ctor)();
}

#endif  /* SYS_CONSTRUCTORS */

//------------------------------------------------------------------------------

void sys_init(void) {
  // Flash latency settings.
#if SYS_FREQ > 25000000
  FLASH->ACTLR = FLASH_ACTLR_LATENCY_1; // +1 Cycle Latency
#else
  FLASH->ACTLR = FLASH_ACTLR_LATENCY_0; // +0 Cycle Latency
#endif  /* SYS_FREQ */

// External crystal
#if SYS_XTAL_FREQ

#if SYS_PLL
  RCC->CFGR0 = RCC_SW_HSE | RCC_PLLSRC_HSE_MUL2;
  RCC->CTLR = CLKSEC | BYPASS | RCC_HSEON | RCC_PLLON;
#else
  RCC->CFGR0 = RCC_SW_HSE;
  RCC->CTLR = CLKSEC | BYPASS | RCC_HSEON;
#endif  /* SYS_PLL */

// Internal clock
#else  /* SYS_HSI_FREQ */

#if SYS_PLL
  RCC->CFGR0 = RCC_HPRE_DIV1 | RCC_PLLSRC_HSI_MUL2;
  RCC->CTLR = CLKSEC | RCC_HSION | RCC_PLLON | (SYS_HSI_TRIM << 3);
#else
  RCC->CFGR0 = RCC_HPRE_DIV1;                     // PLLCLK = HCLK = SYSCLK = APB1
  RCC->CTLR = CLKSEC | RCC_HSION | (SYS_HSI_TRIM << 3);
#endif  /* SYS_PLL */

#endif  /* SYS_HSI_FREQ || SYS_XTAL_FREQ */

  // PLL
#if SYS_PLL
  while (!(RCC->CTLR & RCC_PLLRDY));              // Wait till PLL is ready
  RCC->CFGR0 &= ~RCC_SW;
  RCC->CFGR0 |= RCC_SW_PLL;                       // Select PLL as system clock source
  while ((RCC->CFGR0 & RCC_SWS) != RCC_SWS_PLL);  // Wait till PLL is used as system clock source
#endif  /* SYS_PLL */

#if USE_UART
  // FIXME:
//  uart_setup(UART_BRR);
#endif

#if IO_DBG
  debug_setup();
#endif

#ifdef SYS_CONSTRUCTORS
  call_constructors();
#endif  /* SYS_CONSTRUCTORS */
}

//------------------------------------------------------------------------------

#endif  /* SYS_INIT */
