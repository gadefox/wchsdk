#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                    External Interrupt/Event Controller                     */
/******************************************************************************/

#define EXTI_BASE  (APB2PERIPH_BASE + 0x0400)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define EXTI_INTENR  0
#define EXTI_EVENR   4
#define EXTI_RTENR   8
#define EXTI_FTENR   12
#define EXTI_SWIEVR  16
#define EXTI_INTFR   20

#else

//------------------------------------------------------------------------------

/* EXTI mode enumeration */
typedef enum {
  EXTI_MODE_INTERRUPT = 0x00,
  EXTI_MODE_EVENT     = 0x04
} exti_mode_t;

/* EXTI Trigger enumeration */
typedef enum {
  EXTI_TRIGGER_RISING         = 0x08,
  EXTI_TRIGGER_FALLING        = 0x0C,
  EXTI_TRIGGER_RISING_FALLING = 0x10
} exti_trigger_t;

typedef struct {
  __IO uint32_t INTENR; /* Interrupt Enable Register            */
  __IO uint32_t EVENR;  /* Event Capture Register               */
  __IO uint32_t RTENR;  /* Rising Edge Trigger Enable Register  */
  __IO uint32_t FTENR;  /* Falling Edge Trigger Enable Register */
  __IO uint32_t SWIEVR; /* Soft Interrupt Event Register        */
  __IO uint32_t INTFR;  /* Interrupt Flag Register              */
} exti_t;

#define EXTI  ((exti_t *)EXTI_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* GPIO_Port */
#define EXTI_GPIOA  ((uint8_t)0x00)
#define EXTI_GPIOC  ((uint8_t)0x02)
#define EXTI_GPIOD  ((uint8_t)0x03)

/* EXTI_Lines */
#define EXTI_NOLINE ((uint32_t)0x00000)  /* No interrupt selected */

#define EXTI_LINE0 ((uint32_t)0x00001) /* External interrupt line 0 */
#define EXTI_LINE1 ((uint32_t)0x00002) /* External interrupt line 1 */
#define EXTI_LINE2 ((uint32_t)0x00004) /* External interrupt line 2 */
#define EXTI_LINE3 ((uint32_t)0x00008) /* External interrupt line 3 */
#define EXTI_LINE4 ((uint32_t)0x00010) /* External interrupt line 4 */
#define EXTI_LINE5 ((uint32_t)0x00020) /* External interrupt line 5 */
#define EXTI_LINE6 ((uint32_t)0x00040) /* External interrupt line 6 */
#define EXTI_LINE7 ((uint32_t)0x00080) /* External interrupt line 7 */
#define EXTI_LINE8 ((uint32_t)0x00100) /* External interrupt line 8 Connected to the PVD Output */
#define EXTI_LINE9 ((uint32_t)0x00200) /* External interrupt line 9 Connected to the PWR Auto Wake-up event*/

/*******************  Bit definition for EXTI_INTENR register  *******************/
#define EXTI_INTENR0 ((uint32_t)0x00000001) /* Interrupt Mask on line 0 */
#define EXTI_INTENR1 ((uint32_t)0x00000002) /* Interrupt Mask on line 1 */
#define EXTI_INTENR2 ((uint32_t)0x00000004) /* Interrupt Mask on line 2 */
#define EXTI_INTENR3 ((uint32_t)0x00000008) /* Interrupt Mask on line 3 */
#define EXTI_INTENR4 ((uint32_t)0x00000010) /* Interrupt Mask on line 4 */
#define EXTI_INTENR5 ((uint32_t)0x00000020) /* Interrupt Mask on line 5 */
#define EXTI_INTENR6 ((uint32_t)0x00000040) /* Interrupt Mask on line 6 */
#define EXTI_INTENR7 ((uint32_t)0x00000080) /* Interrupt Mask on line 7 */
#define EXTI_INTENR8 ((uint32_t)0x00000100) /* Interrupt Mask on line 8 */
#define EXTI_INTENR9 ((uint32_t)0x00000200) /* Interrupt Mask on line 9 */

/*******************  Bit definition for EXTI_EVENR register  *******************/
#define EXTI_EVENR0 ((uint32_t)0x00000001) /* Event Mask on line 0 */
#define EXTI_EVENR1 ((uint32_t)0x00000002) /* Event Mask on line 1 */
#define EXTI_EVENR2 ((uint32_t)0x00000004) /* Event Mask on line 2 */
#define EXTI_EVENR3 ((uint32_t)0x00000008) /* Event Mask on line 3 */
#define EXTI_EVENR4 ((uint32_t)0x00000010) /* Event Mask on line 4 */
#define EXTI_EVENR5 ((uint32_t)0x00000020) /* Event Mask on line 5 */
#define EXTI_EVENR6 ((uint32_t)0x00000040) /* Event Mask on line 6 */
#define EXTI_EVENR7 ((uint32_t)0x00000080) /* Event Mask on line 7 */
#define EXTI_EVENR8 ((uint32_t)0x00000100) /* Event Mask on line 8 */
#define EXTI_EVENR9 ((uint32_t)0x00000200) /* Event Mask on line 9 */

/******************  Bit definition for EXTI_RTENR register  *******************/
#define EXTI_RTENR0 ((uint32_t)0x00000001) /* Rising trigger event configuration bit of line 0 */
#define EXTI_RTENR1 ((uint32_t)0x00000002) /* Rising trigger event configuration bit of line 1 */
#define EXTI_RTENR2 ((uint32_t)0x00000004) /* Rising trigger event configuration bit of line 2 */
#define EXTI_RTENR3 ((uint32_t)0x00000008) /* Rising trigger event configuration bit of line 3 */
#define EXTI_RTENR4 ((uint32_t)0x00000010) /* Rising trigger event configuration bit of line 4 */
#define EXTI_RTENR5 ((uint32_t)0x00000020) /* Rising trigger event configuration bit of line 5 */
#define EXTI_RTENR6 ((uint32_t)0x00000040) /* Rising trigger event configuration bit of line 6 */
#define EXTI_RTENR7 ((uint32_t)0x00000080) /* Rising trigger event configuration bit of line 7 */
#define EXTI_RTENR8 ((uint32_t)0x00000100) /* Rising trigger event configuration bit of line 8 */
#define EXTI_RTENR9 ((uint32_t)0x00000200) /* Rising trigger event configuration bit of line 9 */

/******************  Bit definition for EXTI_FTENR register  *******************/
#define EXTI_FTENR0 ((uint32_t)0x00000001) /* Falling trigger event configuration bit of line 0 */
#define EXTI_FTENR1 ((uint32_t)0x00000002) /* Falling trigger event configuration bit of line 1 */
#define EXTI_FTENR2 ((uint32_t)0x00000004) /* Falling trigger event configuration bit of line 2 */
#define EXTI_FTENR3 ((uint32_t)0x00000008) /* Falling trigger event configuration bit of line 3 */
#define EXTI_FTENR4 ((uint32_t)0x00000010) /* Falling trigger event configuration bit of line 4 */
#define EXTI_FTENR5 ((uint32_t)0x00000020) /* Falling trigger event configuration bit of line 5 */
#define EXTI_FTENR6 ((uint32_t)0x00000040) /* Falling trigger event configuration bit of line 6 */
#define EXTI_FTENR7 ((uint32_t)0x00000080) /* Falling trigger event configuration bit of line 7 */
#define EXTI_FTENR8 ((uint32_t)0x00000100) /* Falling trigger event configuration bit of line 8 */
#define EXTI_FTENR9 ((uint32_t)0x00000200) /* Falling trigger event configuration bit of line 9 */

/******************  Bit definition for EXTI_SWIEVR register  ******************/
#define EXTI_SWIEVR0 ((uint32_t)0x00000001) /* Software Interrupt on line 0 */
#define EXTI_SWIEVR1 ((uint32_t)0x00000002) /* Software Interrupt on line 1 */
#define EXTI_SWIEVR2 ((uint32_t)0x00000004) /* Software Interrupt on line 2 */
#define EXTI_SWIEVR3 ((uint32_t)0x00000008) /* Software Interrupt on line 3 */
#define EXTI_SWIEVR4 ((uint32_t)0x00000010) /* Software Interrupt on line 4 */
#define EXTI_SWIEVR5 ((uint32_t)0x00000020) /* Software Interrupt on line 5 */
#define EXTI_SWIEVR6 ((uint32_t)0x00000040) /* Software Interrupt on line 6 */
#define EXTI_SWIEVR7 ((uint32_t)0x00000080) /* Software Interrupt on line 7 */
#define EXTI_SWIEVR8 ((uint32_t)0x00000100) /* Software Interrupt on line 8 */
#define EXTI_SWIEVR9 ((uint32_t)0x00000200) /* Software Interrupt on line 9 */

/*******************  Bit definition for EXTI_INTFR register  ********************/
#define EXTI_INTF0 ((uint32_t)0x00000001) /* Pending bit for line 0 */
#define EXTI_INTF1 ((uint32_t)0x00000002) /* Pending bit for line 1 */
#define EXTI_INTF2 ((uint32_t)0x00000004) /* Pending bit for line 2 */
#define EXTI_INTF3 ((uint32_t)0x00000008) /* Pending bit for line 3 */
#define EXTI_INTF4 ((uint32_t)0x00000010) /* Pending bit for line 4 */
#define EXTI_INTF5 ((uint32_t)0x00000020) /* Pending bit for line 5 */
#define EXTI_INTF6 ((uint32_t)0x00000040) /* Pending bit for line 6 */
#define EXTI_INTF7 ((uint32_t)0x00000080) /* Pending bit for line 7 */
#define EXTI_INTF8 ((uint32_t)0x00000100) /* Pending bit for line 8 */
#define EXTI_INTF9 ((uint32_t)0x00000200) /* Pending bit for line 9 */

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
