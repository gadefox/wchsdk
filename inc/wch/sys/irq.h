#if SYS_IRQ

#pragma once

#include <stdint.h>
#include "wch/sys/csr.h"

//------------------------------------------------------------------------------

#if !SYS_CSR
#error "IRQ requires SYS_CSR = 1"
#endif  /* SYS_CSR */

//------------------------------------------------------------------------------
// Enable Global Interrupt
static inline void irq_enable() {
  csr_set_mstatus(MSTATUS_MIE | MSTATUS_MPIE); }

//------------------------------------------------------------------------------
// Disable Global Interrupt

static inline void irq_disable(void) {
  csr_clear_mstatus(MSTATUS_MIE | MSTATUS_MPIE); }

//------------------------------------------------------------------------------
// Is Global Interrupt enabled (0 = no)

static inline uint32_t irq_is_enabled(void) {
  uint32_t mstatus = csr_get_mstatus();
  return mstatus & MSTATUS_MIE; }

//------------------------------------------------------------------------------
// Core exception handlers

void nmi_handler(void);
void hard_fault_handler(void);
void ecall_m_mode_handler(void);
void ecall_u_mode_handler(void);
void break_point_handler(void);

void isr_sw(void);

//------------------------------------------------------------------------------
// SysTick handlers

void isr_stk(void);

//------------------------------------------------------------------------------
// System handlers

void isr_wwdg(void);
void isr_pvd(void);
void isr_tamper(void);
void isr_rtc(void);
void isr_rtc_alarm(void);
void isr_flash(void);
void isr_rcc(void);

//------------------------------------------------------------------------------
// External interrupts

void isr_exti0(void);
void isr_exti1(void);
void isr_exti2(void);
void isr_exti3(void);
void isr_exti4(void);
void isr_exti7_0(void);
void isr_exti9_5(void);
void isr_exti15_10(void);
void isr_exti15_8(void);
void isr_exti25_16(void);
void isr_awu(void);

//------------------------------------------------------------------------------
// DMA handlers

void isr_dma1_channel1(void);
void isr_dma1_channel2(void);
void isr_dma1_channel3(void);
void isr_dma1_channel4(void);
void isr_dma1_channel5(void);
void isr_dma1_channel6(void);
void isr_dma1_channel7(void);
void isr_dma1_channel8(void);
void isr_dma1_channel9(void);
void isr_dma1_channel10(void);
void isr_dma1_channel11(void);

void isr_dma2_channel1(void);
void isr_dma2_channel2(void);
void isr_dma2_channel3(void);
void isr_dma2_channel4(void);
void isr_dma2_channel5(void);
void isr_dma2_channel6(void);
void isr_dma2_channel7(void);
void isr_dma2_channel8(void);
void isr_dma2_channel9(void);
void isr_dma2_channel10(void);
void isr_dma2_channel11(void);

//------------------------------------------------------------------------------
// ADC handlers

void isr_adc1(void);
void isr_adc1_2(void);

//------------------------------------------------------------------------------
// USB handlers

void isr_usb_fs(void);
void isr_usb_fs_wake_up(void);
void isr_usb_hp_can1_tx(void);
void isr_usb_lp_can1_rx0(void);
void isr_usb_wake_up(void);
void isr_usb_hs_wake_up(void);
void isr_usb_hs(void);
void isr_otg_fs(void);
void isr_usb_pd(void);
void isr_usb_pd_wake_up(void);

//------------------------------------------------------------------------------
// CAN handlers

void isr_can1_tx(void);
void isr_can1_rx0(void);
void isr_can1_rx1(void);
void isr_can1_sce(void);

void isr_can2_tx(void);
void isr_can2_rx0(void);
void isr_can2_tx1(void);
void isr_can2_sce(void);

//------------------------------------------------------------------------------
// Timer handlers

void isr_tim1_brk(void);
void isr_tim1_brk(void);
void isr_tim1_up(void);
void isr_tim1_trg(void);
void isr_tim1_cc(void);

void isr_tim2_brk(void);
void isr_tim2_brk(void);
void isr_tim2_up(void);
void isr_tim2_trg(void);
void isr_tim2_cc(void);

void isr_tim3_brk(void);
void isr_tim3_brk(void);
void isr_tim3_up(void);
void isr_tim3_trg(void);
void isr_tim3_cc(void);

void isr_tim4_brk(void);
void isr_tim4_brk(void);
void isr_tim4_up(void);
void isr_tim4_trg(void);
void isr_tim4_cc(void);

void isr_tim5_brk(void);
void isr_tim5_brk(void);
void isr_tim5_up(void);
void isr_tim5_trg(void);
void isr_tim5_cc(void);

void isr_tim6_brk(void);
void isr_tim6_brk(void);
void isr_tim6_up(void);
void isr_tim6_trg(void);
void isr_tim6_cc(void);

void isr_tim7_brk(void);
void isr_tim7_brk(void);
void isr_tim7_up(void);
void isr_tim7_trg(void);
void isr_tim7_cc(void);

void isr_tim8_brk(void);
void isr_tim8_brk(void);
void isr_tim8_up(void);
void isr_tim8_trg(void);
void isr_tim8_cc(void);

void isr_tim9_brk(void);
void isr_tim9_brk(void);
void isr_tim9_up(void);
void isr_tim9_trg(void);
void isr_tim9_cc(void);

void isr_tim10_brk(void);
void isr_tim10_brk(void);
void isr_tim10_up(void);
void isr_tim10_trg(void);
void isr_tim10_cc(void);

void isr_lptim_wake_up(void);
void isr_lptim(void);

//------------------------------------------------------------------------------
// I2C handlers

void isr_i2c1_ev(void);
void isr_i2c1_er(void);
void isr_i2c2_ev(void);
void isr_i2c2_er(void);

//------------------------------------------------------------------------------
// SPI handlers

void isr_spi1(void);
void isr_spi2(void);
void isr_spi3(void);

//------------------------------------------------------------------------------
// USART handlers

void isr_usart1(void);
void isr_usart2(void);
void isr_usart3(void);
void isr_usart4(void);
void isr_usart5(void);
void isr_usart6(void);
void isr_usart7(void);
void isr_usart8(void);

//------------------------------------------------------------------------------
// Other peripheral handlers

void isr_eth(void);
void isr_eth_wake_up(void);
void isr_osc_32k_cal(void);
void isr_osc_wake_up(void);
void isr_bb(void);
void isr_lle(void);
void isr_rng(void);
void isr_fsmc(void);
void isr_sdio(void);
void isr_dvp(void);
void isr_pioc(void);
void isr_opa(void);
void isr_cmp_wake_up(void);

//------------------------------------------------------------------------------

#endif  /* SYS_IRQ */
