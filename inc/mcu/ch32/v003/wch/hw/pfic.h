#pragma once

#include "wch/hw/def.h"

/******************************************************************************/
/*                     Program Fast Interrupt Controller                      */
/******************************************************************************/

#define PFIC_BASE  (CORE_PERIPH_BASE + 0xE000)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define PFIC_ISR       0
#define PFIC_IPR       32
#define PFIC_ITHRESDR  64
#define PFIC_CFGR      72
#define PFIC_GISR      76
#define PFIC_VTFIDR    80
#define PFIC_VTFADDR   96
#define PFIC_IENR      256
#define PFIC_IRER      352
#define PFIC_IPSR      448
#define PFIC_IPRR      544
#define PFIC_IACTR     640
#define PFIC_IPRIOR    864
#define PFIC_SCTLR     2932

#else

//------------------------------------------------------------------------------
// Memory mapped structure for Program Fast Interrupt Controller (PFIC)

typedef struct {
   __I uint32_t ISR[2];             /* Interrupt Enable Status Register x                  */
       uint32_t RESERVED0[6];       /* =8-2 */
   __I uint32_t IPR[2];             /* Interrupt Pending Status Register x                 */
       uint32_t RESERVED1[6];       /* =8-2 */
  __IO uint32_t ITHRESDR;           /* Interrupt Priority Threshold Configuration Register */
       uint32_t RESERVED2;
  __IO uint32_t CFGR;               /* Interrupt Configuration Register                    */
   __I uint32_t GISR;               /* Interrupt Global Status Register                    */
  __IO uint8_t  VTFIDR[2];          /* VTF ID Configuration Register                       */
       uint8_t  RESERVED3[14];      /* 0x10-2 */
  __IO uint32_t VTFADDR[2];         /* VTF 1 Offset register x                             */
       uint32_t RESERVED4[38];      /* 40-2 */
   __O uint32_t IENR[2];            /* Interrupt Enable Setting Register x                 */
       uint32_t RESERVED5[30];      /* 0x20-2 */
   __O uint32_t IRER[2];            /* Interrupt Enable Clear Register x                   */
       uint32_t RESERVED6[30];      /* 0x20-2 */
   __O uint32_t IPSR[2];            /* Interrupt Pending Status Register x                 */
       uint32_t RESERVED7[30];      /* 0x20-2 */
   __O uint32_t IPRR[2];            /* Interrupt Pending Clear Register x                  */
       uint32_t RESERVED8[30];      /* 0x20-2 */
  __IO uint32_t IACTR[2];           /* Interrupt Activation Status Register x              */
       uint32_t RESERVED9[62];      /* 0x40-2 */
  __IO uint8_t  IPRIOR[IRQ_MAX];    /* Interrupt Priority Configuration Register           */
       uint8_t  RESERVED10[0x910 - IRQ_MAX];
  __IO uint32_t SCTLR;              /* System Control Register                             */
} pfic_t;

#define PFIC  ((pfic_t *)PFIC_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/*******************  Bit definition for PFIC_IPRIORx register  *****************/

// Nesting level 1 enabled: Bits 7:6
#define PFIC_PRIOR0 0x00
#define PFIC_PRIOR1 0x40
#define PFIC_PRIOR2 0x80
#define PFIC_PRIOR3 0xC0

// Nesting level 2 enabled:
#define PFIC_SUBPRIOR 0x40  /* Bit 6 : subpriority */
#define PFIC_PREEMPT  0x80  /* Bit 7 : preemption level enabled */

/*******************  Bit definition for PFIC_SCTLR register  ******************/
#define PFIC_SLEEPONEXIT 0x00000002 /* Bit 1  : 1 = Enter sleep after ISR exit; 0 = Return to main program */
#define PFIC_SLEEPDEEP   0x00000004 /* Bit 2  : 1 = DEEPSLEEP; 0 = SLEEP */
#define PFIC_WFITOWFE    0x00000008 /* Bit 3  : 1 = Treat WFI as WFE; 0 = Normal WFI behavior */
#define PFIC_SEVONPEND   0x00000010 /* Bit 4  : 1 = All events and all interrupts (even disabled) wake system; 0 = Only enabled events and enabled interrupts wake system */
#define PFIC_SETEVENT    0x00000020 /* Bit 5  : Set event for WFE wakeup */
#define PFIC_SYSRESET    0x80000000 /* Bit 31 : System reset (write 1 to reset, auto clear) */

// Bit definition for PFIC_ISR1, PFIC_IPR1, PFIC_IPSR1, PFIC_IPRR1, PFIC_IACTR1,
// PFIC_IENR1, PFIC_IRER1 registers
#define PFIC1_ISR2  0x00000004 /* Bit 2  : Interrupt 2 */
#define PFIC1_ISR3  0x00000008 /* Bit 3  : Interrupt 3 */
#define PFIC1_ISR12 0x00001000 /* Bit 12 : Interrupt 12 */
#define PFIC1_ISR14 0x00004000 /* Bit 14 : Interrupt 14 */
#define PFIC1_ISR16 0x00010000 /* Bit 16 : Interrupt 16 */
#define PFIC1_ISR17 0x00020000 /* Bit 17 : Interrupt 17 */
#define PFIC1_ISR18 0x00040000 /* Bit 18 : Interrupt 18 */
#define PFIC1_ISR19 0x00080000 /* Bit 19 : Interrupt 19 */
#define PFIC1_ISR20 0x00100000 /* Bit 20 : Interrupt 20 */
#define PFIC1_ISR21 0x00200000 /* Bit 21 : Interrupt 21 */
#define PFIC1_ISR22 0x00400000 /* Bit 22 : Interrupt 22 */
#define PFIC1_ISR23 0x00800000 /* Bit 23 : Interrupt 23 */
#define PFIC1_ISR24 0x01000000 /* Bit 24 : Interrupt 24 */
#define PFIC1_ISR25 0x02000000 /* Bit 25 : Interrupt 25 */
#define PFIC1_ISR26 0x04000000 /* Bit 26 : Interrupt 26 */
#define PFIC1_ISR27 0x08000000 /* Bit 27 : Interrupt 27 */
#define PFIC1_ISR28 0x10000000 /* Bit 28 : Interrupt 28 */
#define PFIC1_ISR29 0x20000000 /* Bit 29 : Interrupt 29 */
#define PFIC1_ISR30 0x40000000 /* Bit 30 : Interrupt 30 */
#define PFIC1_ISR31 0x80000000 /* Bit 31 : Interrupt 31 */

// Bit definition for PFIC_ISR2, PFIC_IPR2, PFIC_IENR2, PFIC_IRER2, PFIC_IPSR2,
// PFIC_IPRR2, PFIC_IACTR2 registers
#define PFIC2_ISR32 0x00000001 /* Bit 0  : Interrupt 32 enable status */
#define PFIC2_ISR33 0x00000002 /* Bit 1  : Interrupt 33 enable status */
#define PFIC2_ISR34 0x00000004 /* Bit 2  : Interrupt 34 enable status */
#define PFIC2_ISR35 0x00000008 /* Bit 3  : Interrupt 35 enable status */
#define PFIC2_ISR36 0x00000010 /* Bit 4  : Interrupt 36 enable status */
#define PFIC2_ISR37 0x00000020 /* Bit 5  : Interrupt 37 enable status */
#define PFIC2_ISR38 0x00000040 /* Bit 6  : Interrupt 38 enable status */

/*******************  Bit definition for PFIC_CFGR register  ****************/
#define PFIC_RSTSYS 0x00000080 /* Bit 7 : System reset (write 1 to reset, auto clear) */

#define PFIC_KEY1 0xFA050000 /* KEY1 */
#define PFIC_KEY2 0xBCAF0000 /* KEY2 */
#define PFIC_KEY3 0xBEEF0000 /* KEY3 */

/*******************  Bit definition for PFIC_GISR register  ****************/
#define PFIC_GACTSTA  0x00000100 /* Bit 8  : Any interrupt active */
#define PFIC_GPENDSTA 0x00000200 /* Bit 9  : Any interrupt pending */

#define PFIC_NEST_MSK    0x000000FF /* Bits 7:0 */
#define PFIC_NEST_NOIRQ  0x00000000 /* No interrupt in progress */
#define PFIC_NEST_LEVEL1 0x00000001 /* Level 1 interrupt in progress */
#define PFIC_NEST_LEVEL2 0x00000003 /* Level 2 interrupt in progress */

/*******************  Bit definition for PFIC_VTFADDRx register  ***********/
#define PFIC_VTFADD_EN 0x00000001 /* Bit 0 : Enable VTFx interrupt */

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
