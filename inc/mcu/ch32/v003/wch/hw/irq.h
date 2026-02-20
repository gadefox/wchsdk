#pragma once

/******************************************************************************/
/*                     Interrupt and IRQ Definitions                          */
/******************************************************************************/

/* Interrupt Number Definition, according to the selected device */
typedef enum {
  /******  RISC-V Processor Exceptions Numbers *******************************/
  IRQ_NMI        = 2,  /* 2 Non Maskable Interrupt                      */
  IRQ_HARD_FAULT = 3,  /* 3 Exception Interrupt                         */
  IRQ_STK        = 12, /* 12 System timer Interrupt                     */
  IRQ_SW         = 14, /* 14 software Interrupt                         */

  /******  RISC-V specific Interrupt Numbers *********************************/
  IRQ_WWDG       = 16, /* Window WatchDog Interrupt                     */
  IRQ_PVD        = 17, /* PVD through EXTI Line detection Interrupt     */
  IRQ_FLASH      = 18, /* FLASH global Interrupt                        */
  IRQ_RCC        = 19, /* RCC global Interrupt                          */
  IRQ_EXTI7_0    = 20, /* External Line[7:0] Interrupts                 */
  IRQ_AWU        = 21, /* AWU global Interrupt                          */
  IRQ_DMA1_CH1  = 22, /* DMA1 Channel 1 global Interrupt               */
  IRQ_DMA1_CH2  = 23, /* DMA1 Channel 2 global Interrupt               */
  IRQ_DMA1_CH3  = 24, /* DMA1 Channel 3 global Interrupt               */
  IRQ_DMA1_CH4  = 25, /* DMA1 Channel 4 global Interrupt               */
  IRQ_DMA1_CH5  = 26, /* DMA1 Channel 5 global Interrupt               */
  IRQ_DMA1_CH6  = 27, /* DMA1 Channel 6 global Interrupt               */
  IRQ_DMA1_CH7  = 28, /* DMA1 Channel 7 global Interrupt               */
  IRQ_ADC       = 29, /* ADC global Interrupt                          */
  IRQ_I2C1_EV   = 30, /* I2C1 Event Interrupt                          */
  IRQ_I2C1_ER   = 31, /* I2C1 Error Interrupt                          */
  IRQ_UART1     = 32, /* UART1 global Interrupt                        */
  IRQ_SPI1      = 33, /* SPI1 global Interrupt                         */
  IRQ_TIM1_BRK  = 34, /* TIM1 Break Interrupt                          */
  IRQ_TIM1_UP   = 35, /* TIM1 Update Interrupt                         */
  IRQ_TIM1_TRG  = 36, /* TIM1 Trigger and Commutation Interrupt        */
  IRQ_TIM1_CC   = 37, /* TIM1 Capture Compare Interrupt                */
  IRQ_TIM2      = 38, /* TIM2 global Interrupt                         */
  IRQ_MAX       = 39
} irq_t;

#define IVT_DEFAULT  "\
  .align  2                                                                \n\
  .option norvc;                                                           \n\
  j reset_handler                                                          \n\
  .word   0                                                                \n\
  .word   nmi_handler                  /* NMI Handler */                   \n\
  .word   hard_fault_handler           /* Hard Fault Handler */            \n\
  .word   0                                                                \n\
  .word   0                                                                \n\
  .word   0                                                                \n\
  .word   0                                                                \n\
  .word   0                                                                \n\
  .word   0                                                                \n\
  .word   0                                                                \n\
  .word   0                                                                \n\
  .word   isr_stk                      /* SysTick Handler */               \n\
  .word   0                                                                \n\
  .word   isr_sw                       /* SW Handler */                    \n\
  .word   0                                                                \n\
  .word   isr_wwdg                     /* Window Watchdog */               \n\
  .word   isr_pvd                      /* PVD through EXTI Line detect*/   \n\
  .word   isr_flash                    /* Flash */                         \n\
  .word   isr_rcc                      /* RCC */                           \n\
  .word   isr_exti7_0                  /* EXTI Line 7..0 */                \n\
  .word   isr_awu                      /* AWU */                           \n\
  .word   isr_dma1_ch1                 /* DMA1 Channel 1 */                \n\
  .word   isr_dma1_ch2                 /* DMA1 Channel 2 */                \n\
  .word   isr_dma1_ch3                 /* DMA1 Channel 3 */                \n\
  .word   isr_dma1_ch4                 /* DMA1 Channel 4 */                \n\
  .word   isr_dma1_ch5                 /* DMA1 Channel 5 */                \n\
  .word   isr_dma1_ch6                 /* DMA1 Channel 6 */                \n\
  .word   isr_dma1_ch7                 /* DMA1 Channel 7 */                \n\
  .word   isr_adc1                     /* ADC1 */                          \n\
  .word   isr_i2c1_ev                  /* I2C1 Event */                    \n\
  .word   isr_i2c1_er                  /* I2C1 Error */                    \n\
  .word   isr_uart1                    /* UART1 */                         \n\
  .word   isr_spi1                     /* SPI1 */                          \n\
  .word   isr_tim1_brk                 /* TIM1 Break */                    \n\
  .word   isr_tim1_up                  /* TIM1 Update */                   \n\
  .word   isr_tim1_trg                 /* TIM1 Trigger and Commutation */  \n\
  .word   isr_tim1_cc                  /* TIM1 Capture Compare */          \n\
  .word   isr_tim2                     /* TIM2 */                          \n"

//------------------------------------------------------------------------------

/*
 * This file contains various parts of the official WCH EVT Headers which
 * were originally under a restrictive license.
 *
 * The collection of this file was generated by
 * cnlohr, 2023-02-18 and
 * AlexanderMandera, 2023-06-23
 * gadefox, 2026
 *
 * While originally under a restrictive copyright, WCH has approved use
 * under MIT-licensed use, because of inclusion in Zephyr, as well as other
 * open-source licensed projects.
 *
 * These copies of the headers from WCH are available now under:
 *
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
