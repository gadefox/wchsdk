#if SYS_IRQ

#pragma once

#include <stdint.h>
#include "wch/sys/def.h"

//------------------------------------------------------------------------------

#if SYS_HPE_ENABLE
#define IRQ_DECORATOR __attribute__((interrupt("WCH-Interrupt-fast")))
#else
#define IRQ_DECORATOR __attribute__((interrupt))
#endif

//------------------------------------------------------------------------------

#if SYS_IVT_RAM
#define IVT_SECTION  ".data.isr_entry"
#else
#define IVT_SECTION  ".text.isr_entry"
#endif  /* SYS_IVT_RAM */

//------------------------------------------------------------------------------

void reset_handler(void);
void reset_entry(void);

void isr_default_entry(void);
void isr_entry(void);

//------------------------------------------------------------------------------
// Enable Global Interrupt
static inline void irq_enable() {
  uint32_t result;
  asm volatile(ZICSR "csrr %0,"
                     "mstatus" : "=r"(result));
  result |= 0x88;
  asm volatile(ZICSR "csrw mstatus, %0" : : "r"(result));
}

//------------------------------------------------------------------------------
// Disable Global Interrupt
static inline void irq_disable() {
  uint32_t result;
  asm volatile(ZICSR "csrr %0,"
                     "mstatus" : "=r"(result));
  result &= ~0x88;
  asm volatile(ZICSR "csrw mstatus, %0" : : "r"(result));
}

//------------------------------------------------------------------------------
// Is Global Interrupt enabled (1 = yes, 0 = no)
static inline uint8_t irq_is_enabled(void) {
  uint32_t result;
  asm volatile(ZICSR "csrr %0,"
                     "mstatus" : "=r"(result));
  return (result & 0x08) != 0u;
}

//------------------------------------------------------------------------------
// Invoked when the Clock Security detects the failure of the HSE oscilator.
// The sys clock is switched to HSI. Clears the CSSF flag in RCC->INTR

#if SYS_XTAL_CSS

static inline void nmi_css_handler(void) {
  RCC->INTR |= RCC_CSSC; }  // clear the clock security int flag

#endif  /* SYS_XTAL_CSS */

//------------------------------------------------------------------------------

void nmi_handler(void);

//------------------------------------------------------------------------------
// Core exception handlers
void hard_fault_handler(void);
void ecall_m_mode_handler(void);
void ecall_u_mode_handler(void);
void break_point_handler(void);

void irq_sw(void);

//------------------------------------------------------------------------------
// SysTick handlers
void irq_stk(void);

//------------------------------------------------------------------------------
// System handlers
void irq_wwdg(void);
void irq_pvd(void);
void irq_tamper(void);
void irq_rtc(void);
void irq_rtc_alarm(void);
void irq_flash(void);
void irq_rcc(void);

//------------------------------------------------------------------------------
// External interrupts
void irq_exti0(void);
void irq_exti1(void);
void irq_exti2(void);
void irq_exti3(void);
void irq_exti4(void);
void irq_exti7_0(void);
void irq_exti9_5(void);
void irq_exti15_10(void);
void irq_exti15_8(void);
void irq_exti25_16(void);
void irq_awu(void);

//------------------------------------------------------------------------------
// DMA handlers
void irq_dma1_channel1(void);
void irq_dma1_channel2(void);
void irq_dma1_channel3(void);
void irq_dma1_channel4(void);
void irq_dma1_channel5(void);
void irq_dma1_channel6(void);
void irq_dma1_channel7(void);
void irq_dma1_channel8(void);
void irq_dma1_channel9(void);
void irq_dma1_channel10(void);
void irq_dma1_channel11(void);

void irq_dma2_channel1(void);
void irq_dma2_channel2(void);
void irq_dma2_channel3(void);
void irq_dma2_channel4(void);
void irq_dma2_channel5(void);
void irq_dma2_channel6(void);
void irq_dma2_channel7(void);
void irq_dma2_channel8(void);
void irq_dma2_channel9(void);
void irq_dma2_channel10(void);
void irq_dma2_channel11(void);

//------------------------------------------------------------------------------
// ADC handlers
void irq_adc1(void);
void irq_adc1_2(void);

//------------------------------------------------------------------------------
// USB handlers
void irq_usb_fs(void);
void irq_usb_fs_wake_up(void);
void irq_usb_hp_can1_tx(void);
void irq_usb_lp_can1_rx0(void);
void irq_usb_wake_up(void);
void irq_usb_hs_wake_up(void);
void irq_usb_hs(void);
void irq_otg_fs(void);
void irq_usb_pd(void);
void irq_usb_pd_wake_up(void);

//------------------------------------------------------------------------------
// CAN handlers
void irq_can1_tx(void);
void irq_can1_rx0(void);
void irq_can1_rx1(void);
void irq_can1_sce(void);

void irq_can2_tx(void);
void irq_can2_rx0(void);
void irq_can2_tx1(void);
void irq_can2_sce(void);

//------------------------------------------------------------------------------
// Timer handlers
void irq_tim1_brk(void);
void irq_tim1_brk(void);
void irq_tim1_up(void);
void irq_tim1_trg(void);
void irq_tim1_cc(void);

void irq_tim2_brk(void);
void irq_tim2_brk(void);
void irq_tim2_up(void);
void irq_tim2_trg(void);
void irq_tim2_cc(void);

void irq_tim3_brk(void);
void irq_tim3_brk(void);
void irq_tim3_up(void);
void irq_tim3_trg(void);
void irq_tim3_cc(void);

void irq_tim4_brk(void);
void irq_tim4_brk(void);
void irq_tim4_up(void);
void irq_tim4_trg(void);
void irq_tim4_cc(void);

void irq_tim5_brk(void);
void irq_tim5_brk(void);
void irq_tim5_up(void);
void irq_tim5_trg(void);
void irq_tim5_cc(void);

void irq_tim6_brk(void);
void irq_tim6_brk(void);
void irq_tim6_up(void);
void irq_tim6_trg(void);
void irq_tim6_cc(void);

void irq_tim7_brk(void);
void irq_tim7_brk(void);
void irq_tim7_up(void);
void irq_tim7_trg(void);
void irq_tim7_cc(void);

void irq_tim8_brk(void);
void irq_tim8_brk(void);
void irq_tim8_up(void);
void irq_tim8_trg(void);
void irq_tim8_cc(void);

void irq_tim9_brk(void);
void irq_tim9_brk(void);
void irq_tim9_up(void);
void irq_tim9_trg(void);
void irq_tim9_cc(void);

void irq_tim10_brk(void);
void irq_tim10_brk(void);
void irq_tim10_up(void);
void irq_tim10_trg(void);
void irq_tim10_cc(void);

void irq_lptim_wake_up(void);
void irq_lptim(void);

//------------------------------------------------------------------------------
// I2C handlers
void irq_i2c1_ev(void);
void irq_i2c1_er(void);
void irq_i2c2_ev(void);
void irq_i2c2_er(void);

//------------------------------------------------------------------------------
// SPI handlers
void irq_spi1(void);
void irq_spi2(void);
void irq_spi3(void);

//------------------------------------------------------------------------------
// USART handlers
void irq_usart1(void);
void irq_usart2(void);
void irq_usart3(void);
void irq_usart4(void);
void irq_usart5(void);
void irq_usart6(void);
void irq_usart7(void);
void irq_usart8(void);

//------------------------------------------------------------------------------
// Other peripheral handlers
void irq_eth(void);
void irq_eth_wake_up(void);
void irq_osc_32k_cal(void);
void irq_osc_wake_up(void);
void irq_bb(void);
void irq_lle(void);
void irq_rng(void);
void irq_fsmc(void);
void irq_sdio(void);
void irq_dvp(void);
void irq_pioc(void);
void irq_opa(void);
void irq_cmp_wake_up(void);

//------------------------------------------------------------------------------

#endif  /* SYS_IRQ */
