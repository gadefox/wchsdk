#include "wchsdk_cfg.h"

#if SYS_IRQ

#include "wch/hw/dbg.h"
//#include "wch/hw/irq.h"

#include "wch/sys/irq.h"

//------------------------------------------------------------------------------

#if SYS_IRQ_RAM
#define ISR_SECTION  ".data.isr"
#else
#define ISR_SECTION  ".init.isr"
#endif  /* SYS_IRQ_RAM */

//------------------------------------------------------------------------------
// NOTE: If you don't override a specific handler, it will just spin forever.

__attribute__((section(ISR_SECTION))) __attribute__((naked)) __attribute__((used))
static void isr_default(void) {
  // This is kind of like a crash handler.
#if USE_DEBUG_HARDFAULT && (USE_PRINTF_DEBUG || USE_PRINTF_UART || USE_PRINTF_USB)
// FIXME:
//  print_hex(riscv_get_MEPC());
//  print_hex(riscv_get_MSTATUS());
//  print_hex(riscv_get_MTVAL());
//  print_hex(riscv_get_MCAUSE());

#if USE_PRINTF_DEBUG
  while (DBG->DMDATA0 & 0x80)
    ;
  DBG->DMDATA0 = 0x0A85;
  while (DBG->DMDATA0 & 0x80)
    ;
  DBG->DMDATA0 = 0xAAAAAA83;

#elif USE_PRINTF_UART
  putchar('\n');
#endif  /* USE_PRINTF_DEBUG || USE_PRINTF_UART */

#endif  /* USE_DEBUG_HARDFAULT && ** */

  // Infinite Loop
  assert();
}

//------------------------------------------------------------------------------
// Invoked when the Clock Security detects the failure of the HSE oscilator.
// The sys clock is switched to HSI. Clears the CSSF flag in RCC->INTR

#if SYS_HSE_CSS

__attribute__((section(ISR_SECTION))) __attribute((weak)) __attribute__((used))
void nmi_handler(void) {
  // Clear the clock security int flag
  RCC->INTR |= RCC_CSSC;
}

#else
void nmi_handler(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
#endif  /* SYS_HSE_CSS */

//==============================================================================
// NOTE: This makes it so that all of the interrupt handlers just alias to
// `isr_default` unless they are individually overridden.

//------------------------------------------------------------------------------
// Core exception handlers
void hard_fault_handler(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void ecall_m_mode_handler(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void ecall_u_mode_handler(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void break_point_handler(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_sw(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// SysTick handlers
void isr_stk(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// System handlers
void isr_wwdg(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_pvd(void)        __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tamper(void)     __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_rtc(void)        __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_rtc_alarm(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_flash(void)      __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_rcc(void)        __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// External interrupts
void isr_exti0(void)      __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_exti1(void)      __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_exti2(void)      __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_exti3(void)      __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_exti4(void)      __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_exti7_0(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_exti9_5(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_exti15_10(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_exti15_8(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_exti25_16(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_awu(void)        __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// DMA handlers
void isr_dma1_channel1(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel2(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel3(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel4(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel5(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel6(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel7(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel8(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel9(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel10(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma1_channel11(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_dma2_channel1(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel2(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel3(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel4(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel5(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel6(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel7(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel8(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel9(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel10(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dma2_channel11(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// ADC handlers
void isr_adc1(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_adc1_2(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// USB handlers
void isr_usbfs(void)            __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usbfs_wake_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usb_hp_can1_tx(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usb_lp_can1_rx0(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usb_wake_up(void)      __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usbhs_wake_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usbhs(void)            __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_otg_fs(void)           __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usbpd(void)            __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usbpd_wake_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// CAN handlers
void isr_can1_tx(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_can1_rx0(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_can1_rx1(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_can1_sce(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_can2_tx(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_can2_rx0(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_can2_rx1(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_can2_sce(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// Timer handlers
void isr_tim1(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim1_brk(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim1_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim1_trg(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim1_cc(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_tim2(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim2_brk(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim2_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim2_trg(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim2_cc(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_tim3(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim3_brk(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim3_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim3_trg(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim3_cc(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_tim4(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim4_brk(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim4_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim4_trg(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim4_cc(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_tim5(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim5_brk(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim5_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim5_trg(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim5_cc(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_tim6(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim6_brk(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim6_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim6_trg(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim6_cc(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_tim7(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim7_brk(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim7_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim7_trg(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim7_cc(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_tim8(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim8_brk(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim8_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim8_trg(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim8_cc(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_tim9(void)       __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim9_brk(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim9_up(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim9_trg(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim9_cc(void)    __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_tim10(void)      __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim10_brk(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim10_up(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim10_trg(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_tim10_cc(void)   __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

void isr_lptim_wake_up(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_lptim(void)          __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// I2C handlers
void isr_i2c1_ev(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_i2c1_er(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_i2c2_ev(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_i2c2_er(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// SPI handlers
void isr_spi1(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_spi2(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_spi3(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// USART handlers
void isr_usart1(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usart2(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usart3(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usart4(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usart5(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usart6(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usart7(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_usart8(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------
// Other peripheral handlers
void isr_eth(void)          __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_eth_wake_up(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_osc_32k_cal(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_osc_wake_up(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_bb(void)           __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_lle(void)          __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_rng(void)          __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_fsmc(void)         __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_sdio(void)         __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_dvp(void)          __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_pioc(void)         __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_opa(void)          __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));
void isr_cmp_wake_up(void)  __attribute__((section(ISR_SECTION))) __attribute((weak, alias("isr_default"))) __attribute__((used));

//------------------------------------------------------------------------------

#endif  /* SYS_IRQ */
