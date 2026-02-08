#pragma once

/******************************************************************************/
/*                     Interrupt and IRQ Definitions                          */
/******************************************************************************/

/* Interrupt Number Definition, according to the selected device */
typedef enum {
  /******  RISC-V Processor Exceptions Numbers *******************************/
  IRQ_NMI            = 2,  /* 2 Non Maskable Interrupt                      */
  IRQ_HARD_FAULT     = 3,  /* 3 Exception Interrupt                         */
  IRQ_STK            = 12, /* 12 System timer Interrupt                     */
  IRQ_SW             = 14, /* 14 software Interrupt                         */

  /******  RISC-V specific Interrupt Numbers *********************************/
  IRQ_WWDG           = 16, /* Window WatchDog Interrupt                     */
  IRQ_PVD            = 17, /* PVD through EXTI Line detection Interrupt     */
  IRQ_FLASH          = 18, /* FLASH global Interrupt                        */
  IRQ_RCC            = 19, /* RCC global Interrupt                          */
  IRQ_EXTI7_0        = 20, /* External Line[7:0] Interrupts                 */
  IRQ_AWU            = 21, /* AWU global Interrupt                          */
  IRQ_DMA1_CHANNEL1  = 22, /* DMA1 Channel 1 global Interrupt               */
  IRQ_DMA1_CHANNEL2  = 23, /* DMA1 Channel 2 global Interrupt               */
  IRQ_DMA1_CHANNEL3  = 24, /* DMA1 Channel 3 global Interrupt               */
  IRQ_DMA1_CHANNEL4  = 25, /* DMA1 Channel 4 global Interrupt               */
  IRQ_DMA1_CHANNEL5  = 26, /* DMA1 Channel 5 global Interrupt               */
  IRQ_DMA1_CHANNEL6  = 27, /* DMA1 Channel 6 global Interrupt               */
  IRQ_DMA1_CHANNEL7  = 28, /* DMA1 Channel 7 global Interrupt               */
  IRQ_ADC            = 29, /* ADC global Interrupt                          */
  IRQ_I2C1_EV        = 30, /* I2C1 Event Interrupt                          */
  IRQ_I2C1_ER        = 31, /* I2C1 Error Interrupt                          */
  IRQ_USART1         = 32, /* USART1 global Interrupt                       */
  IRQ_SPI1           = 33, /* SPI1 global Interrupt                         */
  IRQ_TIM1_BRK       = 34, /* TIM1 Break Interrupt                          */
  IRQ_TIM1_UP        = 35, /* TIM1 Update Interrupt                         */
  IRQ_TIM1_TRG       = 36, /* TIM1 Trigger and Commutation Interrupt        */
  IRQ_TIM1_CC        = 37, /* TIM1 Capture Compare Interrupt                */
  IRQ_TIM2           = 38  /* TIM2 global Interrupt                         */
} irq_t;

#define IRQ_VECTOR_TABLE_DEFAULT  "\n\
  .align  2                                                                \n\
  .option push;                                                            \n\
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
  .word   irq_stk                      /* SysTick Handler */               \n\
  .word   0                                                                \n\
  .word   irq_sw                       /* SW Handler */                    \n\
  .word   0                                                                \n\
  .word   irq_wwdg                     /* Window Watchdog */               \n\
  .word   irq_pvd                      /* PVD through EXTI Line detect*/   \n\
  .word   irq_flash                    /* Flash */                         \n\
  .word   irq_rcc                      /* RCC */                           \n\
  .word   irq_exti7_0                  /* EXTI Line 7..0 */                \n\
  .word   irq_awu                      /* AWU */                           \n\
  .word   irq_dma1_channel1            /* DMA1 Channel 1 */                \n\
  .word   irq_dma1_channel2            /* DMA1 Channel 2 */                \n\
  .word   irq_dma1_channel3            /* DMA1 Channel 3 */                \n\
  .word   irq_dma1_channel4            /* DMA1 Channel 4 */                \n\
  .word   irq_dma1_channel5            /* DMA1 Channel 5 */                \n\
  .word   irq_dma1_channel6            /* DMA1 Channel 6 */                \n\
  .word   irq_dma1_channel7            /* DMA1 Channel 7 */                \n\
  .word   irq_adc1                     /* ADC1 */                          \n\
  .word   irq_i2c1_ev                  /* I2C1 Event */                    \n\
  .word   irq_i2c1_er                  /* I2C1 Error */                    \n\
  .word   irq_usart1                   /* USART1 */                        \n\
  .word   irq_spi1                     /* SPI1 */                          \n\
  .word   irq_tim1_brk                 /* TIM1 Break */                    \n\
  .word   irq_tim1_up                  /* TIM1 Update */                   \n\
  .word   irq_tim1_trg                 /* TIM1 Trigger and Commutation */  \n\
  .word   irq_tim1_cc                  /* TIM1 Capture Compare */          \n\
  .word   irq_tim2                     /* TIM2 */                          \n\
  .option pop;\n"

//------------------------------------------------------------------------------

/*
 * This file contains various parts of the official WCH EVT Headers which
 * were originally under a restrictive license.
 *
 * The collection of this file was generated by
 * cnlohr, 2023-02-18 and
 * AlexanderMandera, 2023-06-23
 * It was significantly reworked into several files cnlohr, 2025-01-29
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
