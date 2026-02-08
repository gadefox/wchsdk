#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                               Power Control                                */
/******************************************************************************/

#define PWR_BASE  (APB1PERIPH_BASE + 0x7000)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define PWR_CTLR    0
#define PWR_CSR     4
#define PWR_AWUCSR  8
#define PWR_AWUWR   12
#define PWR_AWUPSC  16

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t CTLR;   /* Power Control Register                       */
  __IO uint32_t CSR;    /* Power Control/Status Register                */
  __IO uint32_t AWUCSR; /* Auto-wakeup Control/Status Register          */
  __IO uint32_t AWUWR;  /* Auto-wakeup Window Comparison Value Register */
  __IO uint32_t AWUPSC; /* Auto-wakeup Crossover Factor Register        */
} pwr_t;

#define PWR  ((pwr_t *)PWR_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* CTLR register bit mask */
#define CTLR_DS_MASK  ((uint32_t)0xFFFFFFFD)
#define CTLR_PLS_MASK ((uint32_t)0xFFFFFF1F)
#define AWUPSC_MASK   ((uint32_t)0xFFFFFFF0)
#define AWUWR_MASK    ((uint32_t)0xFFFFFFC0)

/********************  Bit definition for PWR_CTLR register  ********************/
#define PWR_CTLR_PDDS  ((uint32_t)0x00000002) /* Power Down Deepsleep */
#define PWR_CTLR_PVDE  ((uint32_t)0x00000010) /* Power Voltage Detector Enable */
#define PWR_CTLR_PLS   ((uint32_t)0x000000E0) /* PLS[2:0] bits (PVD Level Selection) */
#define PWR_CTLR_PLS_0 ((uint32_t)0x00000020)
#define PWR_CTLR_PLS_1 ((uint32_t)0x00000040)
#define PWR_CTLR_PLS_2 ((uint32_t)0x00000080)

#define PWR_PVDLEVEL_0 ((uint32_t)0x00000000)
#define PWR_PVDLEVEL_1 ((uint32_t)0x00000020)
#define PWR_PVDLEVEL_2 ((uint32_t)0x00000040)
#define PWR_PVDLEVEL_3 ((uint32_t)0x00000060)
#define PWR_PVDLEVEL_4 ((uint32_t)0x00000080)
#define PWR_PVDLEVEL_5 ((uint32_t)0x000000A0)
#define PWR_PVDLEVEL_6 ((uint32_t)0x000000C0)
#define PWR_PVDLEVEL_7 ((uint32_t)0x000000E0)

/*******************  Bit definition for PWR_CSR register  ********************/
#define PWR_CSR_PVDO ((uint32_t)0x00000004) /* PVD Output */

/*******************  Bit definition for PWR_AWUCSR register  ********************/
#define PWR_AWUCSR_AWUEN ((uint32_t)0x00000002)

/*******************  Bit definition for PWR_AWUWR register  ********************/
#define PWR_AWUWR ((uint32_t)0x0000003F)

/*******************  Bit definition for PWR_AWUPSC register  ********************/
#define PWR_AWUPSC       ((uint32_t)0x0000000F)
#define PWR_AWUPSC_0     ((uint32_t)0x00000000)
#define PWR_AWUPSC_OFF0  ((uint32_t)0x00000000)
#define PWR_AWUPSC_OFF1  ((uint32_t)0x00000001)
#define PWR_AWUPSC_2     ((uint32_t)0x00000002)
#define PWR_AWUPSC_4     ((uint32_t)0x00000003)
#define PWR_AWUPSC_8     ((uint32_t)0x00000004)
#define PWR_AWUPSC_16    ((uint32_t)0x00000005)
#define PWR_AWUPSC_32    ((uint32_t)0x00000006)
#define PWR_AWUPSC_64    ((uint32_t)0x00000007)
#define PWR_AWUPSC_128   ((uint32_t)0x00000008)
#define PWR_AWUPSC_256   ((uint32_t)0x00000009)
#define PWR_AWUPSC_512   ((uint32_t)0x0000000A)
#define PWR_AWUPSC_1024  ((uint32_t)0x0000000B)
#define PWR_AWUPSC_2048  ((uint32_t)0x0000000C)
#define PWR_AWUPSC_4096  ((uint32_t)0x0000000D)
#define PWR_AWUPSC_10240 ((uint32_t)0x0000000E)
#define PWR_AWUPSC_61440 ((uint32_t)0x0000000F)

/* PVD_detection_level */
#define PWR_PVDLEVEL_2V9 ((uint32_t)0x00000000)
#define PWR_PVDLEVEL_3V1 ((uint32_t)0x00000020)
#define PWR_PVDLEVEL_3V3 ((uint32_t)0x00000040)
#define PWR_PVDLEVEL_3V5 ((uint32_t)0x00000060)
#define PWR_PVDLEVEL_3V7 ((uint32_t)0x00000080)
#define PWR_PVDLEVEL_3V9 ((uint32_t)0x000000A0)
#define PWR_PVDLEVEL_4V1 ((uint32_t)0x000000C0)
#define PWR_PVDLEVEL_4V4 ((uint32_t)0x000000E0)

/* PWR_AWU_Prescaler */
#define PWR_AWU_PRESCALER_1     ((uint32_t)0x00000000)
#define PWR_AWU_PRESCALER_2     ((uint32_t)0x00000002)
#define PWR_AWU_PRESCALER_4     ((uint32_t)0x00000003)
#define PWR_AWU_PRESCALER_8     ((uint32_t)0x00000004)
#define PWR_AWU_PRESCALER_16    ((uint32_t)0x00000005)
#define PWR_AWU_PRESCALER_32    ((uint32_t)0x00000006)
#define PWR_AWU_PRESCALER_64    ((uint32_t)0x00000007)
#define PWR_AWU_PRESCALER_128   ((uint32_t)0x00000008)
#define PWR_AWU_PRESCALER_256   ((uint32_t)0x00000009)
#define PWR_AWU_PRESCALER_512   ((uint32_t)0x0000000A)
#define PWR_AWU_PRESCALER_1024  ((uint32_t)0x0000000B)
#define PWR_AWU_PRESCALER_2048  ((uint32_t)0x0000000C)
#define PWR_AWU_PRESCALER_4096  ((uint32_t)0x0000000D)
#define PWR_AWU_PRESCALER_10240 ((uint32_t)0x0000000E)
#define PWR_AWU_PRESCALER_61440 ((uint32_t)0x0000000F)

/* STOP_mode_entry */
#define PWR_STANDBYENTRY_WFI ((uint8_t)0x01)
#define PWR_STANDBYENTRY_WFE ((uint8_t)0x02)

/* PWR_Flag */
#define PWR_FLAG_PVDO ((uint32_t)0x00000004)

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
