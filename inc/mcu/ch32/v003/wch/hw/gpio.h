#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                      General Purpose Function I/O                          */
/******************************************************************************/

//------------------------------------------------------------------------------

#define GPIO_BASE  (APB2PERIPH_BASE + 0x0800)

#define GPIOA_BASE  GPIO_BASE
#define GPIOC_BASE  (GPIOA_BASE + 0x0800)
#define GPIOD_BASE  (GPIOC_BASE + 0x0400)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define GPIO_CFGLR  0
#define GPIO_CFGHR  4
#define GPIO_INDR   8
#define GPIO_OUTDR  12
#define GPIO_BSHR   16
#define GPIO_BCR    20
#define GPIO_LCKR   24

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t CFGLR;          /* Port Configuration Register Low  */
  __IO uint32_t CFGHR;          /* Port Configuration Register High */
  __I  uint32_t INDR;           /* Port Input Data Register         */
  __IO uint32_t OUTDR;          /* Port Output Data Register        */
  __IO uint32_t BSHR;           /* Port Set/Reset Register          */
  __IO uint32_t BCR;            /* Port Reset Register              */
  __IO uint32_t LCKR;           /* Port Configuration Lock Register */
       uint32_t RESERVED[249];  /* 0x100-7 */
} gpio_port_t;

#define GPIOA  ((gpio_port_t *)GPIOA_BASE)
#define GPIOC  ((gpio_port_t *)GPIOC_BASE)
#define GPIOD  ((gpio_port_t *)GPIOD_BASE)

//------------------------------------------------------------------------------

typedef enum {
  GPIO_PORTA = 0,
  GPIO_PORTC = 2,
  GPIO_PORTD = 3,
  GPIO_PORT_MAX = 4
} gpio_port_id_t;

typedef struct {
  gpio_port_t ports[GPIO_PORT_MAX];
} gpio_t;

#define GPIO  ((gpio_t *)GPIO_BASE)

//------------------------------------------------------------------------------
// Configuration Mode enumeration

typedef enum {
  GPIO_DIR_IN     = 0b00,
  GPIO_DIR_OUT2   = 0b10,  // 2 MHz
  GPIO_DIR_OUT10  = 0b01,  // 10 MHz
  GPIO_DIR_OUT30  = 0b11   // 30 MHz
} gpio_dir_t;

typedef enum {
  GPIO_CNFI_ANALOG = 0b00 << 2,
  GPIO_CNFI_FLOAT  = 0b01 << 2,
  GPIO_CNFI_PUPD   = 0b10 << 2      // With pull-up and pull-down mode
} gpio_cnfi_t;

#define GPIO_CNFO_PP   0            // Universal push-pull output mode
#define GPIO_CNFO_OD   (1 << 2)     // Universal open-drain output mode
#define GPIO_CNFO_MUX  (1 << 3)     // Multiplexed function

//------------------------------------------------------------------------------

typedef enum {
  // Input mode
  GPIO_CFGI_ANALOG = GPIO_DIR_IN | GPIO_CNFI_ANALOG,
  GPIO_CFGI_FLOAT  = GPIO_DIR_IN | GPIO_CNFI_FLOAT,
  GPIO_CFGI_PUPD   = GPIO_DIR_IN | GPIO_CNFI_PUPD,

  // Output mode: push-pull
  GPIO_CFGO_PP2  = GPIO_DIR_OUT2 | GPIO_CNFO_PP,
  GPIO_CFGO_PP10 = GPIO_DIR_OUT10 | GPIO_CNFO_PP,
  GPIO_CFGO_PP30 = GPIO_DIR_OUT30 | GPIO_CNFO_PP,

  // Output mode: open-drain
  GPIO_CFGO_OD2  = GPIO_DIR_OUT2 | GPIO_CNFO_OD,
  GPIO_CFGO_OD10 = GPIO_DIR_OUT10 | GPIO_CNFO_OD,
  GPIO_CFGO_OD30 = GPIO_DIR_OUT30 | GPIO_CNFO_OD,

  // Output mode: multiplexed function push-pull
  GPIO_CFGO_MP2  = GPIO_DIR_OUT2 |  GPIO_CNFO_PP | GPIO_CNFO_MUX,
  GPIO_CFGO_MP10 = GPIO_DIR_OUT10 | GPIO_CNFO_PP | GPIO_CNFO_MUX,
  GPIO_CFGO_MP30 = GPIO_DIR_OUT30 | GPIO_CNFO_PP | GPIO_CNFO_MUX,
  
  // Output mode: multiplexed function open-drain
  GPIO_CFGO_MD2  = GPIO_DIR_OUT2 | GPIO_CNFO_OD | GPIO_CNFO_MUX,
  GPIO_CFGO_MD10 = GPIO_DIR_OUT10 | GPIO_CNFO_OD | GPIO_CNFO_MUX,
  GPIO_CFGO_MD30 = GPIO_DIR_OUT30 | GPIO_CNFO_OD | GPIO_CNFO_MUX
} gpio_cfg_t;

//------------------------------------------------------------------------------

typedef union {
  uint32_t __FULL;
  struct {
    gpio_cfg_t PIN0 : 4;
    gpio_cfg_t PIN1 : 4;
    gpio_cfg_t PIN2 : 4;
    gpio_cfg_t PIN3 : 4;
    gpio_cfg_t PIN4 : 4;
    gpio_cfg_t PIN5 : 4;
    gpio_cfg_t PIN6 : 4;
    gpio_cfg_t PIN7 : 4;
  };
} gpio_cfglr_t;

#define GPIOA_CFG  ((__IO gpio_cfglr_t *)&GPIOA->CFGLR)
#define GPIOC_CFG  ((__IO gpio_cfglr_t *)&GPIOC->CFGLR)
#define GPIOD_CFG  ((__IO gpio_cfglr_t *)&GPIOD->CFGLR)

//------------------------------------------------------------------------------

typedef union {
  uint32_t __FULL;
  const struct {
    uint32_t IDR0 : 1;
    uint32_t IDR1 : 1;
    uint32_t IDR2 : 1;
    uint32_t IDR3 : 1;
    uint32_t IDR4 : 1;
    uint32_t IDR5 : 1;
    uint32_t IDR6 : 1;
    uint32_t IDR7 : 1;
    uint32_t : 24;
  };
} gpio_in_t;

#define GPIOA_I  ((__I gpio_in_t *)&GPIOA->INDR)
#define GPIOC_I  ((__I gpio_in_t *)&GPIOC->INDR)
#define GPIOD_I  ((__I gpio_in_t *)&GPIOD->INDR)

//------------------------------------------------------------------------------

typedef union {
  uint32_t __FULL;
  struct {
    uint32_t ODR0 : 1;
    uint32_t ODR1 : 1;
    uint32_t ODR2 : 1;
    uint32_t ODR3 : 1;
    uint32_t ODR4 : 1;
    uint32_t ODR5 : 1;
    uint32_t ODR6 : 1;
    uint32_t ODR7 : 1;
    uint32_t : 24;
  };
} gpio_out_t;

#define GPIOA_O  ((__IO gpio_out_t *)&GPIOA->OUTDR)
#define GPIOC_O  ((__IO gpio_out_t *)&GPIOC->OUTDR)
#define GPIOD_O  ((__IO gpio_out_t *)&GPIOD->OUTDR)

//------------------------------------------------------------------------------

typedef union {
  uint32_t __FULL;
  struct {
    uint32_t BS0 : 1;
    uint32_t BS1 : 1;
    uint32_t BS2 : 1;
    uint32_t BS3 : 1;
    uint32_t BS4 : 1;
    uint32_t BS5 : 1;
    uint32_t BS6 : 1;
    uint32_t BS7 : 1;
    uint32_t : 8;
    uint32_t BR0 : 1;
    uint32_t BR1 : 1;
    uint32_t BR2 : 1;
    uint32_t BR3 : 1;
    uint32_t BR4 : 1;
    uint32_t BR5 : 1;
    uint32_t BR6 : 1;
    uint32_t BR7 : 1;
    uint32_t : 8;
  };
} gpio_set_t;

#define GPIOA_SET  ((__IO gpio_set_t *)&GPIOA->BSHR)
#define GPIOC_SET  ((__IO gpio_set_t *)&GPIOC->BSHR)
#define GPIOD_SET  ((__IO gpio_set_t *)&GPIOD->BSHR)

//------------------------------------------------------------------------------

typedef union {
  uint32_t __FULL;
  struct {
    uint32_t BR0 : 1;
    uint32_t BR1 : 1;
    uint32_t BR2 : 1;
    uint32_t BR3 : 1;
    uint32_t BR4 : 1;
    uint32_t BR5 : 1;
    uint32_t BR6 : 1;
    uint32_t BR7 : 1;
    uint32_t : 24;
  };
} gpio_clr_t;

#define GPIOA_CLR  ((__IO gpio_clr_t *)&GPIOA->BCR)
#define GPIOC_CLR  ((__IO gpio_clr_t *)&GPIOC->BCR)
#define GPIOD_CLR  ((__IO gpio_clr_t *)&GPIOD->BCR)

//------------------------------------------------------------------------------

typedef union {
  uint32_t __FULL;
  struct {
    uint32_t LCK0 : 1;
    uint32_t LCK1 : 1;
    uint32_t LCK2 : 1;
    uint32_t LCK3 : 1;
    uint32_t LCK4 : 1;
    uint32_t LCK5 : 1;
    uint32_t LCK6 : 1;
    uint32_t LCK7 : 1;
    uint32_t LCKK : 1;
    uint32_t : 23;
  };
} gpio_lck_t;

#define GPIOA_LCK  ((__IO gpio_lck_t *)&GPIOA->LCKR)
#define GPIOC_LCK  ((__IO gpio_lck_t *)&GPIOC->LCKR)
#define GPIOD_LCK  ((__IO gpio_lck_t *)&GPIOD->LCKR)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* GPIO_pins_define */
#define GPIO_PIN0 ((uint32_t)0x00000001) /* Pin 0 selected */
#define GPIO_PIN1 ((uint32_t)0x00000002) /* Pin 1 selected */
#define GPIO_PIN2 ((uint32_t)0x00000004) /* Pin 2 selected */
#define GPIO_PIN3 ((uint32_t)0x00000008) /* Pin 3 selected */
#define GPIO_PIN4 ((uint32_t)0x00000010) /* Pin 4 selected */
#define GPIO_PIN5 ((uint32_t)0x00000020) /* Pin 5 selected */
#define GPIO_PIN6 ((uint32_t)0x00000040) /* Pin 6 selected */
#define GPIO_PIN7 ((uint32_t)0x00000080) /* Pin 7 selected */

#define GPIO_PIN_ALL ((uint32_t)0x000000FF) /* All pins selected */

/*******************  Bit definition for GPIO_CFGLR register  *******************/
#define GPIO_CFGLR_MODE ((uint32_t)0x33333333) /* Port x mode bits */

#define GPIO_CFGLR_MODE0   ((uint32_t)0x00000003) /* MODE0[1:0] bits (Port x mode bits, pin 0) */
#define GPIO_CFGLR_MODE0_0 ((uint32_t)0x00000001) /* Bit 0 */
#define GPIO_CFGLR_MODE0_1 ((uint32_t)0x00000002) /* Bit 1 */

#define GPIO_CFGLR_MODE1   ((uint32_t)0x00000030) /* MODE1[1:0] bits (Port x mode bits, pin 1) */
#define GPIO_CFGLR_MODE1_0 ((uint32_t)0x00000010) /* Bit 0 */
#define GPIO_CFGLR_MODE1_1 ((uint32_t)0x00000020) /* Bit 1 */

#define GPIO_CFGLR_MODE2   ((uint32_t)0x00000300) /* MODE2[1:0] bits (Port x mode bits, pin 2) */
#define GPIO_CFGLR_MODE2_0 ((uint32_t)0x00000100) /* Bit 0 */
#define GPIO_CFGLR_MODE2_1 ((uint32_t)0x00000200) /* Bit 1 */

#define GPIO_CFGLR_MODE3   ((uint32_t)0x00003000) /* MODE3[1:0] bits (Port x mode bits, pin 3) */
#define GPIO_CFGLR_MODE3_0 ((uint32_t)0x00001000) /* Bit 0 */
#define GPIO_CFGLR_MODE3_1 ((uint32_t)0x00002000) /* Bit 1 */

#define GPIO_CFGLR_MODE4   ((uint32_t)0x00030000) /* MODE4[1:0] bits (Port x mode bits, pin 4) */
#define GPIO_CFGLR_MODE4_0 ((uint32_t)0x00010000) /* Bit 0 */
#define GPIO_CFGLR_MODE4_1 ((uint32_t)0x00020000) /* Bit 1 */

#define GPIO_CFGLR_MODE5   ((uint32_t)0x00300000) /* MODE5[1:0] bits (Port x mode bits, pin 5) */
#define GPIO_CFGLR_MODE5_0 ((uint32_t)0x00100000) /* Bit 0 */
#define GPIO_CFGLR_MODE5_1 ((uint32_t)0x00200000) /* Bit 1 */

#define GPIO_CFGLR_MODE6   ((uint32_t)0x03000000) /* MODE6[1:0] bits (Port x mode bits, pin 6) */
#define GPIO_CFGLR_MODE6_0 ((uint32_t)0x01000000) /* Bit 0 */
#define GPIO_CFGLR_MODE6_1 ((uint32_t)0x02000000) /* Bit 1 */

#define GPIO_CFGLR_MODE7   ((uint32_t)0x30000000) /* MODE7[1:0] bits (Port x mode bits, pin 7) */
#define GPIO_CFGLR_MODE7_0 ((uint32_t)0x10000000) /* Bit 0 */
#define GPIO_CFGLR_MODE7_1 ((uint32_t)0x20000000) /* Bit 1 */

#define GPIO_CFGLR_CNF ((uint32_t)0xCCCCCCCC) /* Port x configuration bits */

#define GPIO_CFGLR_CNF0   ((uint32_t)0x0000000C) /* CNF0[1:0] bits (Port x configuration bits, pin 0) */
#define GPIO_CFGLR_CNF0_0 ((uint32_t)0x00000004) /* Bit 0 */
#define GPIO_CFGLR_CNF0_1 ((uint32_t)0x00000008) /* Bit 1 */

#define GPIO_CFGLR_CNF1   ((uint32_t)0x000000C0) /* CNF1[1:0] bits (Port x configuration bits, pin 1) */
#define GPIO_CFGLR_CNF1_0 ((uint32_t)0x00000040) /* Bit 0 */
#define GPIO_CFGLR_CNF1_1 ((uint32_t)0x00000080) /* Bit 1 */

#define GPIO_CFGLR_CNF2   ((uint32_t)0x00000C00) /* CNF2[1:0] bits (Port x configuration bits, pin 2) */
#define GPIO_CFGLR_CNF2_0 ((uint32_t)0x00000400) /* Bit 0 */
#define GPIO_CFGLR_CNF2_1 ((uint32_t)0x00000800) /* Bit 1 */

#define GPIO_CFGLR_CNF3   ((uint32_t)0x0000C000) /* CNF3[1:0] bits (Port x configuration bits, pin 3) */
#define GPIO_CFGLR_CNF3_0 ((uint32_t)0x00004000) /* Bit 0 */
#define GPIO_CFGLR_CNF3_1 ((uint32_t)0x00008000) /* Bit 1 */

#define GPIO_CFGLR_CNF4   ((uint32_t)0x000C0000) /* CNF4[1:0] bits (Port x configuration bits, pin 4) */
#define GPIO_CFGLR_CNF4_0 ((uint32_t)0x00040000) /* Bit 0 */
#define GPIO_CFGLR_CNF4_1 ((uint32_t)0x00080000) /* Bit 1 */

#define GPIO_CFGLR_CNF5   ((uint32_t)0x00C00000) /* CNF5[1:0] bits (Port x configuration bits, pin 5) */
#define GPIO_CFGLR_CNF5_0 ((uint32_t)0x00400000) /* Bit 0 */
#define GPIO_CFGLR_CNF5_1 ((uint32_t)0x00800000) /* Bit 1 */

#define GPIO_CFGLR_CNF6   ((uint32_t)0x0C000000) /* CNF6[1:0] bits (Port x configuration bits, pin 6) */
#define GPIO_CFGLR_CNF6_0 ((uint32_t)0x04000000) /* Bit 0 */
#define GPIO_CFGLR_CNF6_1 ((uint32_t)0x08000000) /* Bit 1 */

#define GPIO_CFGLR_CNF7   ((uint32_t)0xC0000000) /* CNF7[1:0] bits (Port x configuration bits, pin 7) */
#define GPIO_CFGLR_CNF7_0 ((uint32_t)0x40000000) /* Bit 0 */
#define GPIO_CFGLR_CNF7_1 ((uint32_t)0x80000000) /* Bit 1 */

/******************  Bit definition for GPIO_BSHR register  *******************/
#define GPIO_BSHR0 ((uint32_t)0x00010000) /* Port x Reset bit 0 */
#define GPIO_BSHR1 ((uint32_t)0x00020000) /* Port x Reset bit 1 */
#define GPIO_BSHR2 ((uint32_t)0x00040000) /* Port x Reset bit 2 */
#define GPIO_BSHR3 ((uint32_t)0x00080000) /* Port x Reset bit 3 */
#define GPIO_BSHR4 ((uint32_t)0x00100000) /* Port x Reset bit 4 */
#define GPIO_BSHR5 ((uint32_t)0x00200000) /* Port x Reset bit 5 */
#define GPIO_BSHR6 ((uint32_t)0x00400000) /* Port x Reset bit 6 */
#define GPIO_BSHR7 ((uint32_t)0x00800000) /* Port x Reset bit 7 */

#define GPIO_BSHR_ALL ((uint32_t)0x00FF0000) /* All pins reset */

/******************  Bit definition for GPIO_LCKR register  *******************/
#define GPIO_LCKK ((uint32_t)0x00010000) /* Lock key */

/* GPIO_Remap_define */
#define GPIO_REMAP_SPI1          ((uint32_t)0x00000001) /* SPI1 Alternate Function mapping */

#define GPIO_PARTIALREMAP_I2C1   ((uint32_t)0x10000002) /* I2C1 Partial Alternate Function mapping */
#define GPIO_FULLREMAP_I2C1      ((uint32_t)0x10400002) /* I2C1 Full Alternate Function mapping */

#define GPIO_PARTREMAP1_UART1    ((uint32_t)0x80000004) /* UART1 Partial1 Alternate Function mapping */
#define GPIO_PARTREMAP2_UART1    ((uint32_t)0x80200000) /* UART1 Partial2 Alternate Function mapping */
#define GPIO_FULLREMAP_UART1     ((uint32_t)0x80200004) /* UART1 Full Alternate Function mapping */

#define GPIO_PARTREMAP1_TIM1     ((uint32_t)0x00160040) /* TIM1 Partial1 Alternate Function mapping */
#define GPIO_PARTREMAP2_TIM1     ((uint32_t)0x00160080) /* TIM1 Partial2 Alternate Function mapping */
#define GPIO_FULLREMAP_TIM1      ((uint32_t)0x001600C0) /* TIM1 Full Alternate Function mapping */

#define GPIO_PARTREMAP1_TIM2     ((uint32_t)0x00180100) /* TIM2 Partial1 Alternate Function mapping */
#define GPIO_PARTREMAP2_TIM2     ((uint32_t)0x00180200) /* TIM2 Partial2 Alternate Function mapping */
#define GPIO_FULLREMAP_TIM2      ((uint32_t)0x00180300) /* TIM2 Full Alternate Function mapping */

#define GPIO_REMAP_PA1_2         ((uint32_t)0x00008000) /* PA1 and PA2 Alternate Function mapping */
#define GPIO_REMAP_ADC1_ETRGINJ  ((uint32_t)0x00200002) /* ADC1 External Trigger Injected Conversion remapping */
#define GPIO_REMAP_ADC1_ETRGREG  ((uint32_t)0x00200004) /* ADC1 External Trigger Regular Conversion remapping */
#define GPIO_REMAP_LSI_CAL       ((uint32_t)0x00200080) /* LSI calibration Alternate Function mapping */
#define GPIO_REMAP_SDI_DISABLE   ((uint32_t)0x00300400) /* SDI Disabled */

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
