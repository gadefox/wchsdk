#include "wchsdk_cfg.h"

#if SYS_INIT

#include "wch/hw/flash.h"
#include "wch/hw/rcc.h"

#include "wch/sys/def.h"
#include "wch/sys/init.h"
#include "wch/sys/util.h"

//------------------------------------------------------------------------------

static inline void sys_init_flash(void) {
  // Flash latency settings.
#if SYSCLK > 25000000
  FLASH->ACTLR = FLASH_ACTLR_LATENCY_1; // +1 Cycle Latency
#else
  FLASH->ACTLR = FLASH_ACTLR_LATENCY_0; // +0 Cycle Latency
#endif  /* SYSCLK */
}

//------------------------------------------------------------------------------
// External crystal definitions

#if SYS_HSE_BYPASS
#define BYPASS  RCC_HSEBYP
#else
#define BYPASS  0
#endif  /* SYS_HSE_BYPASS */

#if SYS_HSE_CSS
#define CLKSEC  RCC_CSSON  // Enable clock security system
#else
#define CLKSEC  0
#endif  /* SYS_HSE_CSS */

//------------------------------------------------------------------------------
// External crystal initialization

static inline bool sys_init_xtal(void) {
  RCC->CTLR = RCC_HSEON | CLKSEC | BYPASS;

  // Wait for HSE ready with timeout (~50ms @ 24MHz)
  if (!wait_mask(&RCC->CTLR, RCC_HSERDY, true, ms_to_stk(50))) {
    RCC->CTLR &= ~RCC_HSEON;
    return false;
  }

#if SYS_PLL
  RCC->CFGR0 = RCC_PLLSRC_HSE_MUL2 | RCC_SW_HSE;
#else
  RCC->CFGR0 = RCC_SW_HSE;
#endif  /* SYS_PLL */

  return true;
}

//------------------------------------------------------------------------------
// Internal clock

static inline void sys_init_rc(void) {
  // Enable HSI with trim
  RCC->CTLR = RCC_HSION | (SYS_HSI_TRIM << 3);

  // Wait for HSI ready (typically 1-2 µs, but safety first)
  while (!(RCC->CTLR & RCC_HSIRDY));

#if SYS_PLL
  RCC->CFGR0 = RCC_PLLSRC_HSI_MUL2 | RCC_HPRE_DIV1;
#else
  RCC->CFGR0 = RCC_HPRE_DIV1;   // PLLCLK = HCLK = SYSCLK = APB1
#endif  /* SYS_PLL */
}

//------------------------------------------------------------------------------

#if SYS_PLL

static inline void sys_init_pll(void) {
  RCC->CTLR |= RCC_PLLON;

  // Wait till PLL is ready
  while (!(RCC->CTLR & RCC_PLLRDY));

  // Select PLL as system clock source
  RCC->CFGR0 &= ~RCC_SW;
  RCC->CFGR0 |= RCC_SW_PLL;

  // Wait till PLL is used as system clock source
  while ((RCC->CFGR0 & RCC_SWS) != RCC_SWS_PLL);
}

#endif  /* SYS_PLL */

//------------------------------------------------------------------------------

void sys_init(void) {
  sys_init_flash();

#if SYS_HSE_FREQ
  // Try HSE first
  if (!sys_init_xtal())
    sys_init_rc();     // HSE failed, fallback to HSI
#else
  // Use HSI directly
  sys_init_rc();
#endif  /* SYS_HSI_FREQ || SYS_HSE_FREQ */

#if SYS_PLL
  sys_init_pll();
#endif  /* SYS_PLL */
}

//------------------------------------------------------------------------------

#endif  /* SYS_INIT */
