#pragma once

#include "wch/hw/def.h"

/******************************************************************************/
/*                          Reset and Clock Control                           */
/******************************************************************************/

#define RCC_BASE  (AHBPERIPH_BASE + 0x1000)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define RCC_CTLR       0
#define RCC_CFGR0      4
#define RCC_INTR       8
#define RCC_APB2PRSTR  12
#define RCC_APB1PRSTR  16
#define RCC_AHBPCENR   20
#define RCC_APB2PCENR  24
#define RCC_APB1PCENR  28
#define RCC_RSTSCKR    36

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t CTLR;       /* Clock Control Register                */
  __IO uint32_t CFGR0;      /* Clock Configuration Register 0        */
  __IO uint32_t INTR;       /* Clock Interrupt Register              */
  __IO uint32_t APB2PRSTR;  /* APB2 Peripheral Reset Register        */
  __IO uint32_t APB1PRSTR;  /* APB1 Peripheral Reset Register        */
  __IO uint32_t AHBPCENR;   /* AHB Peripheral Clock Enable Register  */
  __IO uint32_t APB2PCENR;  /* APB2 Peripheral Clock Enable Register */
  __IO uint32_t APB1PCENR;  /* APB1 Peripheral Clock Enable Register */
       uint32_t RESERVED;
  __IO uint32_t RSTSCKR;    /* Control/Status Register               */
} rcc_t;

#define RCC  ((rcc_t *)RCC_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/********************  Bit definition for RCC_CTLR register  ********************/

#define RCC_HSION   0x00000001 /* Internal High Speed clock enable */
#define RCC_HSIRDY  0x00000002 /* Internal High Speed clock ready flag */

#define RCC_HSITRIM_MSK 0xF8  /* Internal High Speed clock trimming */
#define RCC_HSITRIM_POS 3
#define RCC_HSITRIM(x)  (((x) & RCC_HSITRIM_MSK) >> RCC_HSITRIM_POS)

#define RCC_HSICAL_MSK 0x0000FF00 /* Internal High Speed clock Calibration */
#define RCC_HSICAL_POS 8
#define RCC_HSICAL(x)  (((x) & RCC_HSICAL_MSK) >> RCC_HSICAL_POS)

#define RCC_HSEON   0x00010000 /* External High Speed clock enable */
#define RCC_HSERDY  0x00020000 /* External High Speed clock ready flag */
#define RCC_HSEBYP  0x00040000 /* External High Speed clock Bypass */
#define RCC_CSSON   0x00080000 /* Clock Security System monitoring function of HSE */

#define RCC_PLLON   0x01000000 /* PLL enable */
#define RCC_PLLRDY  0x02000000 /* PLL clock ready flag */

/*******************  Bit definition for RCC_CFGR0 register  *******************/
#define RCC_PLLSRC 0x00010000 /* HSE as PLL entry clock source */

// System clock Switch
#define RCC_SW_MSK 0x00000003 /* SW[1:0] bits */
#define RCC_SW_HSI 0x00000000 /* HSI selected as system clock */
#define RCC_SW_HSE 0x00000001 /* HSE selected as system clock */
#define RCC_SW_PLL 0x00000002 /* PLL selected as system clock */

// System Clock Switch Status
#define RCC_SWS_MSK 0x0000000C /* SWS[3:2] bits */
#define RCC_SWS_HSI 0x00000000 /* HSI oscillator used as system clock */
#define RCC_SWS_HSE 0x00000004 /* HSE oscillator used as system clock */
#define RCC_SWS_PLL 0x00000008 /* PLL used as system clock */

#define RCC_HPRE_MSK    0x000000F0 /* HPRE[3:0] bits (AHB prescaler) */
#define RCC_HPRE_DIV1   0x00000000 /* SYSCLK not divided */
#define RCC_HPRE_DIV2   0x00000010 /* SYSCLK divided by 2 */
#define RCC_HPRE_DIV3   0x00000020 /* SYSCLK divided by 3 */
#define RCC_HPRE_DIV4   0x00000030 /* SYSCLK divided by 4 */
#define RCC_HPRE_DIV5   0x00000040 /* SYSCLK divided by 5 */
#define RCC_HPRE_DIV6   0x00000050 /* SYSCLK divided by 6 */
#define RCC_HPRE_DIV7   0x00000060 /* SYSCLK divided by 7 */
#define RCC_HPRE_DIV8   0x00000070 /* SYSCLK divided by 8 */
#define RCC_HPRE_DIV16  0x000000B0 /* SYSCLK divided by 16 */
#define RCC_HPRE_DIV32  0x000000C0 /* SYSCLK divided by 32 */
#define RCC_HPRE_DIV64  0x000000D0 /* SYSCLK divided by 64 */
#define RCC_HPRE_DIV128 0x000000E0 /* SYSCLK divided by 128 */
#define RCC_HPRE_DIV256 0x000000F0 /* SYSCLK divided by 256 */

#define RCC_ADCPRE_MSK    0x0000F800 /* ADCPRE[4:0] bits (ADC prescaler) */
#define RCC_ADCPRE_DIV2   0x00000000 /* HBCLK divided by 2 */
#define RCC_ADCPRE_DIV4   0x00004000 /* HBCLK divided by 4 */
#define RCC_ADCPRE_DIV6   0x00008000 /* HBCLK divided by 6 */
#define RCC_ADCPRE_DIV8   0x0000C000 /* HBCLK divided by 8 */
#define RCC_ADCPRE_DIV12  0x0000A000 /* HBCLK divided by 12 */
#define RCC_ADCPRE_DIV16  0x0000E000 /* HBCLK divided by 16 */
#define RCC_ADCPRE_DIV24  0x0000A800 /* HBCLK divided by 24 */
#define RCC_ADCPRE_DIV32  0x0000E800 /* HBCLK divided by 32 */
#define RCC_ADCPRE_DIV48  0x0000B000 /* HBCLK divided by 48 */
#define RCC_ADCPRE_DIV64  0x0000F000 /* HBCLK divided by 64 */
#define RCC_ADCPRE_DIV96  0x0000B800 /* HBCLK divided by 96 */
#define RCC_ADCPRE_DIV128 0x0000F800 /* HBCLK divided by 128 */

#define RCC_MCO_MSK 0x07000000 /* MCO[2:0] bits (Microcontroller Clock Output) */
#define RCC_MCO_NO  0x00000000 /* No clock */
#define RCC_MCO_SYS 0x04000000 /* System clock selected as MCO source */
#define RCC_MCO_HSI 0x05000000 /* HSI clock selected as MCO source */
#define RCC_MCO_HSE 0x06000000 /* HSE clock selected as MCO source  */
#define RCC_MCO_PLL 0x07000000 /* PLL clock divided by 2 selected as MCO source */

/*******************  Bit definition for RCC_INTR register  ********************/
#define RCC_LSIRDYF  0x00000001 /* LSI Ready Interrupt flag */
#define RCC_HSIRDYF  0x00000004 /* HSI Ready Interrupt flag */
#define RCC_HSERDYF  0x00000008 /* HSE Ready Interrupt flag */
#define RCC_PLLRDYF  0x00000010 /* PLL Ready Interrupt flag */
#define RCC_CSSF     0x00000080 /* Clock Security System Interrupt flag */
#define RCC_LSIRDYIE 0x00000100 /* LSI Ready Interrupt Enable */
#define RCC_HSIRDYIE 0x00000400 /* HSI Ready Interrupt Enable */
#define RCC_HSERDYIE 0x00000800 /* HSE Ready Interrupt Enable */
#define RCC_PLLRDYIE 0x00001000 /* PLL Ready Interrupt Enable */
#define RCC_LSIRDYC  0x00010000 /* LSI Ready Interrupt Clear */
#define RCC_HSIRDYC  0x00040000 /* HSI Ready Interrupt Clear */
#define RCC_HSERDYC  0x00080000 /* HSE Ready Interrupt Clear */
#define RCC_PLLRDYC  0x00100000 /* PLL Ready Interrupt Clear */
#define RCC_CSSC     0x00800000 /* Clock Security System Interrupt Clear */

/*****************  Bit definition for RCC_APB2PRSTR register  *****************/
#define RCC_AFIORST  0x00000001 /* Alternate Function I/O reset */
#define RCC_IOPARST  0x00000004 /* I/O port A reset */
#define RCC_IOPCRST  0x00000010 /* I/O port C reset */
#define RCC_IOPDRST  0x00000020 /* I/O port D reset */
#define RCC_ADC1RST  0x00000200 /* ADC 1 interface reset */
#define RCC_TIM1RST  0x00000800 /* TIM1 Timer reset */
#define RCC_SPI1RST  0x00001000 /* SPI 1 reset */
#define RCC_UART1RST 0x00004000 /* UART1 reset */

/*****************  Bit definition for RCC_APB1PRSTR register  *****************/
#define RCC_TIM2RST 0x00000001 /* Timer 2 reset */
#define RCC_WWDGRST 0x00000800 /* Window Watchdog reset */
#define RCC_I2C1RST 0x00200000 /* I2C 1 reset */
#define RCC_PWRRST  0x10000000 /* Power interface reset */

/******************  Bit definition for RCC_AHBPCENR register  ******************/
#define RCC_DMA1EN 0x00000001 /* DMA1 clock enable */
#define RCC_SRAMEN 0x00000004 /* SRAM interface clock enable */

/******************  Bit definition for RCC_APB2PCENR register  *****************/
#define RCC_AFIOEN  0x00000001 /* Alternate Function I/O clock enable */
#define RCC_IOPAEN  0x00000004 /* I/O port A clock enable */
#define RCC_IOPCEN  0x00000010 /* I/O port C clock enable */
#define RCC_IOPDEN  0x00000020 /* I/O port D clock enable */
#define RCC_ADC1EN  0x00000200 /* ADC 1 interface clock enable */
#define RCC_TIM1EN  0x00000800 /* TIM1 Timer clock enable */
#define RCC_SPI1EN  0x00001000 /* SPI 1 clock enable */
#define RCC_UART1EN 0x00004000 /* UART1 clock enable */

/*****************  Bit definition for RCC_APB1PCENR register  ******************/
#define RCC_TIM2EN 0x00000001 /* Timer 2 clock enabled*/
#define RCC_WWDGEN 0x00000800 /* Window Watchdog clock enable */
#define RCC_I2C1EN 0x00200000 /* I2C 1 clock enable */
#define RCC_PWREN  0x10000000 /* Power interface clock enable */

/*******************  Bit definition for RCC_RSTSCKR register  ********************/
#define RCC_LSION    0x00000001 /* Internal Low Speed oscillator enable */
#define RCC_LSIRDY   0x00000002 /* Internal Low Speed oscillator Ready */
#define RCC_RMVF     0x01000000 /* Remove reset flag */
#define RCC_PINRSTF  0x04000000 /* PIN reset flag */
#define RCC_PORRSTF  0x08000000 /* POR/PDR reset flag */
#define RCC_SFTRSTF  0x10000000 /* Software Reset flag */
#define RCC_IWDGRSTF 0x20000000 /* Independent Watchdog reset flag */
#define RCC_WWDGRSTF 0x40000000 /* Window watchdog reset flag */
#define RCC_LPWRRSTF 0x80000000 /* Low-Power reset flag */

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
