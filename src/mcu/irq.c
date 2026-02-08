#include "wchsdk_cfg.h"

#if MCU_IRQ

#include "wch/hw/dbg.h"
#include "wch/hw/irq.h"
#include "wch/mcu/irq.h"

//------------------------------------------------------------------------------

// If you don't override a specific handler, it will just spin forever.
__attribute__((section(IRQ_SECTION))) __attribute__((naked)) __attribute__((used))
static void default_handler(void) {
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
  asm volatile("1: j 1b");
}

//------------------------------------------------------------------------------

// This makes it so that all of the interrupt handlers just alias to
// default_handler unless they are individually overridden.

#if USE_CLK_SEC
void nmi_handler(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("irq_nmi_rcc_css"))) __attribute__((used));
#else
void nmi_handler(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
#endif  /* USE_CLK_SEC */

//------------------------------------------------------------------------------
// core exception handlers
void hard_fault_handler(void)   __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void ecall_m_mode_handler(void) __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void ecall_u_mode_handler(void) __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void break_point_handler(void)  __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_sw(void)               __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// SysTick handlers
void irq_stk(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// System handlers
void irq_wwdg(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_pvd(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tamper(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_rtc(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_rtc_alarm(void)        __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_flash(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_rcc(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// External interrupts
void irq_exti0(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_exti1(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_exti2(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_exti3(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_exti4(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_exti7_0(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_exti9_5(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_exti15_10(void)        __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_exti15_8(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_exti25_16(void)        __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_awu(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// DMA handlers
void irq_dma1_channel1(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel2(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel3(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel4(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel5(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel6(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel7(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel8(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel9(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel10(void)   __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma1_channel11(void)   __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_dma2_channel1(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel2(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel3(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel4(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel5(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel6(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel7(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel8(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel9(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel10(void)   __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dma2_channel11(void)   __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// ADC handlers
void irq_adc1(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_adc1_2(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// USB handlers
void irq_usbfs(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usbfs_wake_up(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usb_hp_can1_tx(void)   __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usb_lp_can1_rx0(void)  __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usb_wake_up(void)      __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usbhs_wake_up(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usbhs(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_otg_fs(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usbpd(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usbpd_wake_up(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// CAN handlers
void irq_can1_tx(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_can1_rx0(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_can1_rx1(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_can1_sce(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_can2_tx(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_can2_rx0(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_can2_rx1(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_can2_sce(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// Timer handlers
void irq_tim1(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim1_brk(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim1_up(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim1_trg(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim1_cc(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_tim2(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim2_brk(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim2_up(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim2_trg(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim2_cc(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_tim3(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim3_brk(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim3_up(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim3_trg(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim3_cc(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_tim4(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim4_brk(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim4_up(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim4_trg(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim4_cc(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_tim5(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim5_brk(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim5_up(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim5_trg(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim5_cc(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_tim6(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim6_brk(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim6_up(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim6_trg(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim6_cc(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_tim7(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim7_brk(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim7_up(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim7_trg(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim7_cc(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_tim8(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim8_brk(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim8_up(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim8_trg(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim8_cc(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_tim9(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim9_brk(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim9_up(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim9_trg(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim9_cc(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_tim10(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim10_brk(void)        __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim10_up(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim10_trg(void)        __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_tim10_cc(void)         __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

void irq_lptim_wake_up(void)    __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_lptim(void)            __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// I2C handlers
void irq_i2c1_ev(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_i2c1_er(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_i2c2_ev(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_i2c2_er(void)          __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// SPI handlers
void irq_spi1(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_spi2(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_spi3(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// USART handlers
void irq_usart1(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usart2(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usart3(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usart4(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usart5(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usart6(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usart7(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_usart8(void)           __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------
// Other peripheral handlers
void irq_eth(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_eth_wake_up(void)      __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_osc_32k_cal(void)      __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_osc_wake_up(void)      __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_bb(void)               __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_lle(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_rng(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_fsmc(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_sdio(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_dvp(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_pioc(void)             __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_opa(void)              __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));
void irq_cmp_wake_up(void)      __attribute__((section(IRQ_SECTION))) __attribute((weak, alias("default_handler"))) __attribute__((used));

//------------------------------------------------------------------------------

#endif  /* MCU_IRQ */
