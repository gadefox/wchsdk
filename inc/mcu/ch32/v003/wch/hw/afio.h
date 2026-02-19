#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                     General Alternate Function I/O                         */
/******************************************************************************/

#define AFIO_BASE  APB2PERIPH_BASE

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define AFIO_PCFR1   4
#define AFIO_EXTICR  8

#else

//------------------------------------------------------------------------------

typedef struct {
       uint32_t RESERVED;
  __IO uint32_t PCFR1;      /* Remap Register 1 */
  __IO uint32_t EXTICR;     /* External Interrupt Configuration Register 1*/
} afio_t;

#define AFIO  ((afio_t *)AFIO_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/******************  Bit definition for AFIO_PCFR1register  *******************/
#define AFIO_PCFR1_SPI1_REMAP    0x00000001 /* SPI1 remapping */
#define AFIO_PCFR1_I2C1_REMAP    0x00000002 /* I2C1 remapping */
#define AFIO_PCFR1_UART1_REMAP   0x00000004 /* UART1 remapping */
#define AFIO_PCFR1_UART1_REMAP_1 0x00200000 /* UART1 remapping higher bit */

#define AFIO_PCFR1_TIM1_REMAP_MSK   0x000000C0 /* TIM1_REMAP[1:0] bits (TIM1 remapping) */
#define AFIO_PCFR1_TIM1_REMAP_NO    0x00000000 /* No remap      (ETR/PC5, CH1/PD2, CH2/PA1, CH3/PC3, CH4/PC4, BKIN/PC2, CH1N/PD0, CH2N/PA2, CH3N/PD1) */
#define AFIO_PCFR1_TIM1_REMAP_PART1 0x00000040 /* Partial remap (ETR/PC5, CH1/PC6, CH2/PC7, CH3/PC0, CH4/PD3, BKIN/PC1, CH1N/PC3, CH2N/PC4, CH3N/PD1) */
#define AFIO_PCFR1_TIM1_REMAP_PART2 0x00000080 /* Partial remap (ETR/PD4, CH1/PD2, CH2/PA1, CH3/PC3, CH4/PC4, BKIN/PC2, CH1N/PD0, CN2N/PA2, CH3N/PD1) */
#define AFIO_PCFR1_TIM1_REMAP_FULL  0x000000C0 /* Full remap    (ETR/PC2, CH1/PC4, CH2/PC7, CH3/PC5, CH4/PD4, BKIN/PC1, CH1N/PC3, CH2N/PD2, CH3N/PC6) */

#define AFIO_PCFR1_TIM2_REMAP_MSK   0x00000300 /* TIM2_REMAP[1:0] bits (TIM2 remapping) */
#define AFIO_PCFR1_TIM2_REMAP_NO    0x00000000 /* No remap      (CH1/ETR/PD4, CH2/PD3, CH3/PC0, CH4/PD4) */
#define AFIO_PCFR1_TIM2_REMAP_PART1 0x00000100 /* Partial remap (CH1/ETR/PC5, CH2/PC2, CH3/PD4, CH4/PC1) */
#define AFIO_PCFR1_TIM2_REMAP_PART2 0x00000200 /* Partial remap (CH1/ETR/PC1, CH2/PD3, CH3/PC0, CH4/PD7) */
#define AFIO_PCFR1_TIM2_REMAP_FULL  0x00000300 /* Full remap    (CH1/ETR/PC1, CH2/PC7, CH3/PD6, CH4/PD5) */

#define AFIO_PCFR1_PA12_REMAP         0x00008000 /* Port D0/Port D1 mapping on OSC_IN/OSC_OUT */
#define AFIO_PCFR1_ADC1_ETRGINJ_REMAP 0x00020000 /* ADC 1 External Trigger Injected Conversion remapping */
#define AFIO_PCFR1_ADC1_ETRGREG_REMAP 0x00040000 /* ADC 1 External Trigger Regular Conversion remapping */

#define AFIO_PCFR1_I2C1_HIGH_BIT_REMAP 0x00400000
#define AFIO_PCFR1_TIM1_1_RM           0x00800000

#define AFIO_PCFR1_SWCFG_MSK 0x07000000 /* SWCFG[2:0] bits (Serial Wire IO Debug configuration) */
#define AFIO_PCFR1_SWCFG_OFF 0x04000000 /* SWD (SDI) disabled */

/*****************  Bit definition for AFIO_EXTICR register  *****************/
#define AFIO_EXTICR_MSK0 0x00000003 /* EXTI 0 configuration */
#define AFIO_EXTICR_PA0  0x00000000 /* PA[0] pin */
#define AFIO_EXTICR_PC0  0x00000002 /* PC[0] pin */
#define AFIO_EXTICR_PD0  0x00000003 /* PD[0] pin */

#define AFIO_EXTICR_MSK1 0x0000000C /* EXTI 1 configuration */
#define AFIO_EXTICR_PA1  0x00000000 /* PA[1] pin */
#define AFIO_EXTICR_PC1  0x00000008 /* PC[1] pin */
#define AFIO_EXTICR_PD1  0x0000000C /* PD[1] pin */

#define AFIO_EXTICR_MSK2 0x00000030 /* EXTI 2 configuration */
#define AFIO_EXTICR_PA2  0x00000000 /* PA[2] pin */
#define AFIO_EXTICR_PC2  0x00000020 /* PC[2] pin */
#define AFIO_EXTICR_PD2  0x00000030 /* PD[2] pin */

#define AFIO_EXTICR_MSK3 0x000000C0 /* EXTI 3 configuration */
#define AFIO_EXTICR_PA3  0x00000000 /* PA[3] pin */
#define AFIO_EXTICR_PC3  0x00000080 /* PC[3] pin */
#define AFIO_EXTICR_PD3  0x000000C0 /* PD[3] pin */

#define AFIO_EXTICR_MSK4 0x00000300 /* EXTI 4 configuration */
#define AFIO_EXTICR_PA4  0x00000000 /* PA[4] pin */
#define AFIO_EXTICR_PC4  0x00000200 /* PC[4] pin */
#define AFIO_EXTICR_PD4  0x00000300 /* PD[4] pin */

#define AFIO_EXTICR_MSK5 0x00000C00 /* EXTI 5 configuration */
#define AFIO_EXTICR_PA5  0x00000000 /* PA[5] pin */
#define AFIO_EXTICR_PC5  0x00000800 /* PC[5] pin */
#define AFIO_EXTICR_PD5  0x00000C00 /* PD[5] pin */

#define AFIO_EXTICR_MSK6 0x00003000 /* EXTI 6 configuration */
#define AFIO_EXTICR_PA6  0x00000000 /* PA[6] pin */
#define AFIO_EXTICR_PC6  0x00002000 /* PC[6] pin */
#define AFIO_EXTICR_PD6  0x00003000 /* PD[6] pin */

#define AFIO_EXTICR_MSK7 0x0000C000 /* EXTI 7 configuration */
#define AFIO_EXTICR_PA7  0x00000000 /* PA[7] pin */
#define AFIO_EXTICR_PC7  0x00008000 /* PC[7] pin */
#define AFIO_EXTICR_PD7  0x0000C000 /* PD[7] pin */

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
