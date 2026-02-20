#pragma once

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
  GPIO_IN     = 0,
  GPIO_OUT2   = 2,  // 2 MHz
  GPIO_OUT10  = 1,  // 10 MHz
  GPIO_OUT30  = 3   // 30 MHz
} gpio_dir_t;

#define GPIO_OD   0x4   // Universal open-drain output mode
#define GPIO_MUX  0x8   // Multiplexed function

//------------------------------------------------------------------------------

typedef enum {
  // Input mode
  GPIO_ANALOG = GPIO_IN,
  GPIO_FLOAT  = GPIO_IN | 0x04,
  GPIO_PUPD   = GPIO_IN | 0x08,  // With pull-up and pull-down mode

  // Output mode: push-pull
  GPIO_PP2  = GPIO_OUT2,
  GPIO_PP10 = GPIO_OUT10,
  GPIO_PP30 = GPIO_OUT30,

  // Output mode: open-drain
  GPIO_OD2  = GPIO_OUT2 | GPIO_OD,
  GPIO_OD10 = GPIO_OUT10 | GPIO_OD,
  GPIO_OD30 = GPIO_OUT30 | GPIO_OD,

  // Output mode: multiplexed function push-pull
  GPIO_APP2  = GPIO_OUT2 |  GPIO_MUX,
  GPIO_APP10 = GPIO_OUT10 | GPIO_MUX,
  GPIO_APP30 = GPIO_OUT30 | GPIO_MUX,
  
  // Output mode: multiplexed function open-drain
  GPIO_AOD2  = GPIO_OUT2 | GPIO_OD | GPIO_MUX,
  GPIO_AOD10 = GPIO_OUT10 | GPIO_OD | GPIO_MUX,
  GPIO_AOD30 = GPIO_OUT30 | GPIO_OD | GPIO_MUX
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

#define GPIOA_CFGLR  ((__IO gpio_cfglr_t *)&GPIOA->CFGLR)
#define GPIOC_CFGLR  ((__IO gpio_cfglr_t *)&GPIOC->CFGLR)
#define GPIOD_CFGLR  ((__IO gpio_cfglr_t *)&GPIOD->CFGLR)

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
} gpio_indr_t;

#define GPIOA_INDR  ((__I gpio_indr_t *)&GPIOA->INDR)
#define GPIOC_INDR  ((__I gpio_indr_t *)&GPIOC->INDR)
#define GPIOD_INDR  ((__I gpio_indr_t *)&GPIOD->INDR)

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
} gpio_outdr_t;

#define GPIOA_OUTDR  ((__IO gpio_outdr_t *)&GPIOA->OUTDR)
#define GPIOC_OUTDR  ((__IO gpio_outdr_t *)&GPIOC->OUTDR)
#define GPIOD_OUTDR  ((__IO gpio_outdr_t *)&GPIOD->OUTDR)

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
} gpio_bshr_t;

#define GPIOA_BSHR  ((__IO gpio_bshr_t *)&GPIOA->BSHR)
#define GPIOC_BSHR  ((__IO gpio_bshr_t *)&GPIOC->BSHR)
#define GPIOD_BSHR  ((__IO gpio_bshr_t *)&GPIOD->BSHR)

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
} gpio_bcr_t;

#define GPIOA_BCR  ((__IO gpio_bc_t *)&GPIOA->BCR)
#define GPIOC_BCR  ((__IO gpio_bc_t *)&GPIOC->BCR)
#define GPIOD_BCR  ((__IO gpio_bc_t *)&GPIOD->BCR)

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
#define GPIO_PIN0 0x00000001 /* Pin 0 selected */
#define GPIO_PIN1 0x00000002 /* Pin 1 selected */
#define GPIO_PIN2 0x00000004 /* Pin 2 selected */
#define GPIO_PIN3 0x00000008 /* Pin 3 selected */
#define GPIO_PIN4 0x00000010 /* Pin 4 selected */
#define GPIO_PIN5 0x00000020 /* Pin 5 selected */
#define GPIO_PIN6 0x00000040 /* Pin 6 selected */
#define GPIO_PIN7 0x00000080 /* Pin 7 selected */

#define GPIO_PIN_ALL 0x000000FF /* All pins selected */

/******************  Bit definition for GPIO_BSHR register  *******************/
#define GPIO_RST0 0x00010000 /* Port x Reset bit 0 */
#define GPIO_RST1 0x00020000 /* Port x Reset bit 1 */
#define GPIO_RST2 0x00040000 /* Port x Reset bit 2 */
#define GPIO_RST3 0x00080000 /* Port x Reset bit 3 */
#define GPIO_RST4 0x00100000 /* Port x Reset bit 4 */
#define GPIO_RST5 0x00200000 /* Port x Reset bit 5 */
#define GPIO_RST6 0x00400000 /* Port x Reset bit 6 */
#define GPIO_RST7 0x00800000 /* Port x Reset bit 7 */

#define GPIO_RST_ALL 0x00FF0000 /* All pins reset */

/******************  Bit definition for GPIO_LCKR register  *******************/
#define GPIO_LCKK 0x00010000 /* Lock key */

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
