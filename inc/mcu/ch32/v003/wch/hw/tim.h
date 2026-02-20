#pragma once

#include "wch/hw/def.h"

/******************************************************************************/
/*                                    TIM                                     */
/******************************************************************************/

#define TIM1_BASE  (APB2PERIPH_BASE + 0x2C00)
#define TIM2_BASE  (APB1PERIPH_BASE + 0x0000)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define TIM_CTLR1      0
#define TIM_CTLR2      4
#define TIM_SMCFGR     8
#define TIM_DMAINTENR  12
#define TIM_INTFR      16
#define TIM_SWEVGR     20
#define TIM_CHCTLR1    24
#define TIM_CHCTLR2    28
#define TIM_CCER       32
#define TIM_CNT        36
#define TIM_PSC        40
#define TIM_ATRLR      44
#define TIM_RPTCR      48
#define TIM_CH1CVR     52
#define TIM_CH2CVR     56
#define TIM_CH3CVR     60
#define TIM_CH4CVR     64
#define TIM_BDTR       68
#define TIM_DMACFGR    72
#define TIM_DMAADR     76

#else

//------------------------------------------------------------------------------

typedef enum {
  TIM_TIMING,    /* 0; Freeze - OC2REF unchanged */
  TIM_ACTIVE,    /* 1; Set high on match */
  TIM_INACTIVE,  /* 2; Set low on match */
  TIM_TOGGLE,    /* 3; Toggle on match */
  TIM_FORCE_LO,  /* 4; Force low */
  TIM_FORCE_HI,  /* 5; Force high */
  TIM_PWM1,      /* 6; PWM1: active while cnt < ccr */
  TIM_PWM2       /* 7; PWM2: active while cnt > ccr */
} tim_chctlr_ocm_t;

typedef enum {
  TIM_OUT,      /* 0; comparison capture channel 2 is configured as an output */
  TIM_IN_TI2,   /* 1; comparison capture channel 2 is configured as an input and IC2 is mapped on TI2 */
  TIM_IN_TI1,   /* 2; comparison capture channel 2 is configured as an input and IC2 is mapped on TI1 */
  TIM_IN_TRC    /* 3; Compare Capture Channel 2 is configured as an input and IC2 is mapped on TRC. This mode works only when the internal trigger input is selected (by the TS bit) */
} tim_chctlr_ccs_t;

typedef enum {
  TIM_CF_NO,       /*  0; no filter, sampled at fDTS */
  TIM_CF_D1N2,     /*  1; Sampling frequency Fsampling=Fck_int, N=2 */
  TIM_CF_D1N4,     /*  2; Sampling frequency Fsampling=Fck_int, N=4 */
  TIM_CF_D1N8,     /*  3; Sampling frequency Fsampling=Fck_int, N=8 */
  TIM_CF_D2N6,     /*  4; Sampling frequency Fsampling = Fdts/2, N = 6 */
  TIM_CF_D2N8,     /*  5; Sampling frequency Fsampling = Fdts/2, N = 8 */
  TIM_CF_D4N6,     /*  6; Sampling frequency Fsampling = Fdts/4, N = 6 */
  TIM_CF_D4N8,     /*  7; Sampling frequency Fsampling = Fdts/4, N = 8 */
  TIM_CF_D8N6,     /*  8; Sampling frequency Fsampling = Fdts/8, N = 6 */
  TIM_CF_D8N8,     /*  9; Sampling frequency Fsampling = Fdts/8, N = 8 */
  TIM_CF_D16N5,    /* 10; Sampling frequency Fsampling = Fdts/16, N = 5 */
  TIM_CF_D16N6,    /* 11; Sampling frequency Fsampling = Fdts/16, N = 6 */
  TIM_CF_D16N8,    /* 12; Sampling frequency Fsampling = Fdts/16, N = 8 */
  TIM_CF_D32N5,    /* 13; Sampling frequency Fsampling = Fdts/32, N = 5 */
  TIM_CF_D32N6,    /* 14; Sampling frequency Fsampling = Fdts/32, N = 6 */
  TIM_CF_D32N8     /* 15; Sampling frequency Fsampling = Fdts/32, N = 8 */
} tim_chctlr_cf_t;

typedef enum {
  TIM_PSC_DIV1,    /* 0; One capture is triggered for each edge detected on the capture input */
  TIM_PSC_DIV2,    /* 1; Capture triggered every 2 events */
  TIM_PSC_DIV4,    /* 2; Capture triggered every 4 events */
  TIM_PSC_DIV8     /* 3; Capture triggered every 8 events */
} tim_chctlr_pcs_t;

typedef struct {
  __IO uint16_t CTLR1;      /* Control Register 1                       */
       uint16_t RESERVED0;
  __IO uint16_t CTLR2;      /* Control Register 2                       */
       uint16_t RESERVED1;
  __IO uint16_t SMCFGR;     /* Slave Mode Control Register              */
       uint16_t RESERVED2;
  __IO uint16_t DMAINTENR;  /* DMA/Interrupt Enable Register            */
       uint16_t RESERVED3;
  __IO uint16_t INTFR;      /* Interrupt Status Register                */
       uint16_t RESERVED4;
  __IO uint16_t SWEVGR;     /* Event Generation Register                */
       uint16_t RESERVED5;
  __IO uint32_t CHCTLR[2];  /* R16! Compare/Capture Control Register x  */
  __IO uint16_t CCER;       /* Compare/Capture Enable Register          */
       uint16_t RESERVED8;
  __IO uint16_t CNT;        /* Counters                                 */
       uint16_t RESERVED9;
  __IO uint16_t PSC;        /* Counting Clock Prescaler                 */
       uint16_t RESERVED10;
  __IO uint16_t ATRLR;      /* Auto-reload value register               */
       uint16_t RESERVED11;
  __IO uint16_t RPTCR;      /* Recurring Count Value Register           */
       uint16_t RESERVED12;
  __IO uint32_t CHCVR[4];   /* Compare/Capture Register x               */
  __IO uint16_t BDTR;       /* Brake and Deadband Registers             */
       uint16_t RESERVED13;
  __IO uint16_t DMACFGR;    /* DMA Control Register                     */
       uint16_t RESERVED14;
  __IO uint16_t DMAADR;     /* DMA Address Register For Continuous Mode */
       uint16_t RESERVED15;
} tim_t;

#define TIM1  ((tim_t *)TIM1_BASE)
#define TIM2  ((tim_t *)TIM2_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/*******************  Bit definition for TIM_CTLR1 register  ********************/
#define TIM_CEN  0x0001 /* Counter enable */
#define TIM_UDIS 0x0002 /* Update disable */
#define TIM_URS  0x0004 /* Update request source */
#define TIM_OPM  0x0008 /* One pulse mode */
#define TIM_DIR  0x0010 /* Count down ARR -> 0 */

/* Center-aligned mode selection */
#define TIM_CMS_MSK    0x0060  /* CMS[6:5] bits */
#define TIM_CMS_EDGEA  0x0000  /* The counter counts up or down based on the direction bit */
#define TIM_CMS_CENTA1 0x0020  /* OC IRQ flag set when counting down */
#define TIM_CMS_CENTA2 0x0040  /* OC IRQ flag set when counting up */
#define TIM_CMS_CENTA3 0x0060  /* OC IRQ flag set when counting up and down */

#define TIM_ARPE 0x0080 /* Auto-reload preload enable */

/* Clock division */ 
#define TIM_CKD_MSK  0x0300 /* CKD[9:8] bits */
#define TIM_CKD_OFF  0x0000
#define TIM_CKD_MUL2 0x0100
#define TIM_CKD_MUL4 0x0200

/*******************  Bit definition for TIM_CTLR2 register  ********************/
#define TIM_CCPC 0x0001 /* Capture/Compare Preloaded Control */
#define TIM_CCUS 0x0004 /* Capture/Compare Control Update Selection */
#define TIM_CCDS 0x0008 /* Capture/Compare DMA Selection */

/* Master Mode Selection */
#define TIM_MMS_MSK    0x0070 /* MMS[6:4] bits */
#define TIM_MMS_RESET  0x0000
#define TIM_MMS_CNTEN  0x0010
#define TIM_MMS_UPDATE 0x0020
#define TIM_MMS_PULSE  0x0030
#define TIM_MMS_OC1REF 0x0040
#define TIM_MMS_OC2REF 0x0050
#define TIM_MMS_OC3REF 0x0060
#define TIM_MMS_OC4REF 0x0070

#define TIM_TI1S  0x0080 /* TI1 Selection */
#define TIM_OIS1  0x0100 /* Output Idle state 1 (OC1 output) */
#define TIM_OIS1N 0x0200 /* Output Idle state 1 (OC1N output) */
#define TIM_OIS2  0x0400 /* Output Idle state 2 (OC2 output) */
#define TIM_OIS2N 0x0800 /* Output Idle state 2 (OC2N output) */
#define TIM_OIS3  0x1000 /* Output Idle state 3 (OC3 output) */
#define TIM_OIS3N 0x2000 /* Output Idle state 3 (OC3N output) */
#define TIM_OIS4  0x4000 /* Output Idle state 4 (OC4 output) */

/*******************  Bit definition for TIM_SMCFGR register  *******************/

/* Slave mode selection */
#define TIM_SMS_MSK   0x0007  /* SMS[2:0] bits */
#define TIM_SMS_CKINT 0x0000  /* Driven by the internal clock CK_INT */
#define TIM_SMS_ENC1  0x0001  /* Encoder mode 1, where the core counter increments or decrements the count at the edge of TI2FP2 depending on the level of TI1FP1 */
#define TIM_SMS_ENC2  0x0002  /* Encoder mode 2, where the core counter increments or decrements the count at the edge of TI1FP1, depending on the level of TI2FP2 */
#define TIM_SMS_ENC3  0x0003  /* Encoder mode 3, where the core counter increments and decrements the count on the edges of TI1FP1 and TI2FP2 depending on the input level of another signal */
#define TIM_SMS_RESET 0x0004  /* Reset mode, where the rising edge of the trigger input (TRGI) will initialize the counter and generate a signal to update the registers */
#define TIM_SMS_GATED 0x0005  /* Gated mode, when the trigger input (TRGI) is high, the counter clock is turned on; at the trigger input becomes low, the counter is stopped, and the counter starts and stops are controlled */
#define TIM_SMS_TRIG  0x0006  /* Trigger mode, where the counter is started on the rising edge of the trigger input TRGI and only the start of the counter is controlled */
#define TIM_SMS_EXT   0x0007  /* External clock mode 1, rising edge of the selected trigger input (TRGI) drives the counter */

/* Trigger selection */
#define TIM_TS_MSK     0x0070 /* TS[6:4] bits */
#define TIM_TS_ITR0    0x0000
#define TIM_TS_ITR1    0x0010
#define TIM_TS_ITR2    0x0020
#define TIM_TS_ITR3    0x0030
#define TIM_TS_TI1F_ED 0x0040
#define TIM_TS_TI1FP1  0x0050
#define TIM_TS_TI2FP2  0x0060
#define TIM_TS_ETRF    0x0070

#define TIM_MSM 0x0080 /* Master/slave mode */

/* Externally triggered filtering */
#define TIM_ETF_MSK   0x0F00  /* ETF[11:8] bits */
#define TIM_ETF_D1N2  0x0100  /* Sampling frequency Fsampling=Fck_int, N=2 */
#define TIM_ETF_D1N4  0x0200  /* Sampling frequency Fsampling=Fck_int, N=4 */
#define TIM_ETF_D1N8  0x0300  /* Sampling frequency Fsampling=Fck_int, N=8 */
#define TIM_ETF_D2N6  0x0400  /* Sampling frequency Fsampling = Fdts/2, N = 6 */
#define TIM_ETF_D2N8  0x0500  /* Sampling frequency Fsampling = Fdts/2, N = 8 */
#define TIM_ETF_D4N6  0x0600  /* Sampling frequency Fsampling = Fdts/4, N = 6 */
#define TIM_ETF_D4N8  0x0700  /* Sampling frequency Fsampling = Fdts/4, N = 8 */
#define TIM_ETF_D8N6  0x0800  /* Sampling frequency Fsampling = Fdts/8, N = 6 */
#define TIM_ETF_D8N8  0x0900  /* Sampling frequency Fsampling = Fdts/8, N = 8 */
#define TIM_ETF_D16N5 0x0A00  /* Sampling frequency Fsampling = Fdts/16, N = 5 */
#define TIM_ETF_D16N6 0x0B00  /* Sampling frequency Fsampling = Fdts/16, N = 6 */
#define TIM_ETF_D16N8 0x0C00  /* Sampling frequency Fsampling = Fdts/16, N = 8 */
#define TIM_ETF_D32N5 0x0D00  /* Sampling frequency Fsampling = Fdts/32, N = 5 */
#define TIM_ETF_D32N6 0x0E00  /* Sampling frequency Fsampling = Fdts/32, N = 6 */
#define TIM_ETF_D32N8 0x0F00  /* Sampling frequency Fsampling = Fdts/32, N = 8 */

/* External trigger prescaler */
#define TIM_ETPS_MSK  0x3000 /* ETPS[13:12] bits */
#define TIM_ETPS_DIV1 0x0000 /* Prescaler off */
#define TIM_ETPS_DIV2 0x1000 /* ETRP frequency divided by 2 */
#define TIM_ETPS_DIV4 0x2000 /* ETRP frequency divided by 4 */
#define TIM_ETPS_DIV8 0x3000 /* ETRP frequency divided by 8 */

#define TIM_ECE 0x4000 /* External clock enable */
#define TIM_ETP 0x8000 /* External trigger polarity */

/*******************  Bit definition for TIM_DMAINTENR register  *******************/
#define TIM_UIE   0x0001 /* Update interrupt enable */
#define TIM_CC1IE 0x0002 /* Capture/Compare 1 interrupt enable */
#define TIM_CC2IE 0x0004 /* Capture/Compare 2 interrupt enable */
#define TIM_CC3IE 0x0008 /* Capture/Compare 3 interrupt enable */
#define TIM_CC4IE 0x0010 /* Capture/Compare 4 interrupt enable */
#define TIM_COMIE 0x0020 /* COM interrupt enable */
#define TIM_TIE   0x0040 /* Trigger interrupt enable */
#define TIM_BIE   0x0080 /* Break interrupt enable */
#define TIM_UDE   0x0100 /* Update DMA request enable */
#define TIM_CC1DE 0x0200 /* Capture/Compare 1 DMA request enable */
#define TIM_CC2DE 0x0400 /* Capture/Compare 2 DMA request enable */
#define TIM_CC3DE 0x0800 /* Capture/Compare 3 DMA request enable */
#define TIM_CC4DE 0x1000 /* Capture/Compare 4 DMA request enable */
#define TIM_COMDE 0x2000 /* COM DMA request enable */
#define TIM_TDE   0x4000 /* Trigger DMA request enable */

/********************  Bit definition for TIM_INTFR register  ********************/
#define TIM_UIF   0x0001 /* Update interrupt Flag */
#define TIM_CC1IF 0x0002 /* Capture/Compare 1 interrupt Flag */
#define TIM_CC2IF 0x0004 /* Capture/Compare 2 interrupt Flag */
#define TIM_CC3IF 0x0008 /* Capture/Compare 3 interrupt Flag */
#define TIM_CC4IF 0x0010 /* Capture/Compare 4 interrupt Flag */
#define TIM_COMIF 0x0020 /* COM interrupt Flag */
#define TIM_TIF   0x0040 /* Trigger interrupt Flag */
#define TIM_BIF   0x0080 /* Break interrupt Flag */
#define TIM_CC1OF 0x0200 /* Capture/Compare 1 Overcapture Flag */
#define TIM_CC2OF 0x0400 /* Capture/Compare 2 Overcapture Flag */
#define TIM_CC3OF 0x0800 /* Capture/Compare 3 Overcapture Flag */
#define TIM_CC4OF 0x1000 /* Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_SWEVGR register  ********************/
#define TIM_UG   0x0001 /* Update Generation */
#define TIM_CC1G 0x0002 /* Capture/Compare 1 Generation */
#define TIM_CC2G 0x0004 /* Capture/Compare 2 Generation */
#define TIM_CC3G 0x0008 /* Capture/Compare 3 Generation */
#define TIM_CC4G 0x0010 /* Capture/Compare 4 Generation */
#define TIM_COMG 0x0020 /* Capture/Compare Control Update Generation */
#define TIM_TG   0x0040 /* Trigger Generation */
#define TIM_BG   0x0080 /* Break Generation */

/******************  Bit definition for TIM_CHCTLRx register  *******************/

/* Output Compare x Mode */
#define TIM_OC1M_MSK 0x0070 /* OC1M[6:4] bits */
#define TIM_OC2M_MSK 0x7000 /* OC1M[14:12] bits */
#define TIM_OC1M_POS 4
#define TIM_OC2M_POS 12

/* Capture/Compare x Selection */
#define TIM_CC1S_MSK 0x0003 /* CC1S[1:0] bits */
#define TIM_CC2S_MSK 0x0300 /* CC2S[9:8] bits */
#define TIM_CC1S_POS 0
#define TIM_CC2S_POS 8

#define TIM_OC1FE 0x0004 /* Output Compare 1 Fast enable */
#define TIM_OC1PE 0x0008 /* Output Compare 1 Preload enable */
#define TIM_OC1CE 0x0080 /* Output Compare 1Clear Enable */

#define TIM_OC2FE 0x0400 /* Output Compare 2 Fast enable */
#define TIM_OC2PE 0x0800 /* Output Compare 2 Preload enable */
#define TIM_OC2CE 0x8000 /* Output Compare 2 Clear Enable */

/* Input Capture x Prescaler */
#define TIM_IC1PSC_MSK 0x000C /* IC1PSC[3:2] bits */
#define TIM_IC2PSC_MSK 0x0C00 /* IC2PSC[11:10] bits */
#define TIM_IC1PSC_POS 2
#define TIM_IC2PSC_POS 10

/* Input Capture x Filter */
#define TIM_IC1F_MSK 0x00F0 /* IC1F[7:4] bits */
#define TIM_IC2F_MSK 0xF000 /* IC2F[15:12] bits */
#define TIM_IC1F_POS 4
#define TIM_IC2F_POS 12

/*******************  Bit definition for TIM_CCER register  *******************/
#define TIM_CC1E  0x0001 /* Capture/Compare 1 output enable */
#define TIM_CC1P  0x0002 /* Capture/Compare 1 output Polarity (falling) */

#define TIM_CC2E  0x0010 /* Capture/Compare 2 output enable */
#define TIM_CC2P  0x0020 /* Capture/Compare 2 output Polarity (falling) */

#define TIM_CC3E  0x0100 /* Capture/Compare 3 output enable */
#define TIM_CC3P  0x0200 /* Capture/Compare 3 output Polarity (falling) */

#define TIM_CC4E  0x1000 /* Capture/Compare 4 output enable */
#define TIM_CC4P  0x2000 /* Capture/Compare 4 output Polarity (falling) */

/*******************  Bit definition for TIM_CNT register  ********************/
#define TIM_CNT_MSK 0xFFFF /* Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define TIM_PSC_MSK 0xFFFF /* Prescaler Value */

/*******************  Bit definition for TIM_ATRLR register  ********************/
#define TIM_ARR_MSK 0xFFFF /* actual auto-reload Value */

/*******************  Bit definition for TIM_RPTCR register  ********************/
#define TIM_REP_MSK 0xFF /* Repetition Counter Value */

/*******************  Bit definition for TIM_CHxCVR register  *******************/
#define TIM_CCR_MSK 0x0000FFFF /* Capture/Compare x Value */

#define TIM_LEVEL 0x00010000 /* The level indication bit corresponding to the captured value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define TIM_DTG_MSK  0x00FF /* DTG[0:7] bits (Dead-Time Generator set-up) */

#define TIM_LOCK_MSK 0x0300 /* LOCK[9:8] bits (Lock Configuration) */
#define TIM_LOCK_L0  0x0000
#define TIM_LOCK_L1  0x0100
#define TIM_LOCK_L2  0x0200
#define TIM_LOCK_L3  0x0300

#define TIM_OSSI 0x0400 /* Off-State Selection for Idle mode */
#define TIM_OSSR 0x0800 /* Off-State Selection for Run mode */
#define TIM_BKE  0x1000 /* Break enable */
#define TIM_BKP  0x2000 /* Break Polarity */
#define TIM_AOE  0x4000 /* Automatic Output enable */
#define TIM_MOE  0x8000 /* Main Output enable */

/*******************  Bit definition for TIM_DMACFGR register  ********************/

/* DMA Base Address */
#define TIM_DMA_MSK   0x001F /* DBA[4:0] bits */
#define TIM_DMA_CR1   0x0000
#define TIM_DMA_CR2   0x0001
#define TIM_DMA_SMCR  0x0002
#define TIM_DMA_DIER  0x0003
#define TIM_DMA_SR    0x0004
#define TIM_DMA_EGR   0x0005
#define TIM_DMA_CCMR1 0x0006
#define TIM_DMA_CCMR2 0x0007
#define TIM_DMA_CCER  0x0008
#define TIM_DMA_CNT   0x0009
#define TIM_DMA_PSC   0x000A
#define TIM_DMA_ARR   0x000B
#define TIM_DMA_RCR   0x000C
#define TIM_DMA_CCR1  0x000D
#define TIM_DMA_CCR2  0x000E
#define TIM_DMA_CCR3  0x000F
#define TIM_DMA_CCR4  0x0010
#define TIM_DMA_BDTR  0x0011
#define TIM_DMA_DCR   0x0012

/* DMA Burst Length */
#define TIM_DBL_MSK 0x1F00 /* DBL[12:8] bits */
#define TIM_DBL_1T  0x0000
#define TIM_DBL_2T  0x0100
#define TIM_DBL_3T  0x0200
#define TIM_DBL_4T  0x0300
#define TIM_DBL_5T  0x0400
#define TIM_DBL_6T  0x0500
#define TIM_DBL_7T  0x0600
#define TIM_DBL_8T  0x0700
#define TIM_DBL_9T  0x0800
#define TIM_DBL_10T 0x0900
#define TIM_DBL_11T 0x0A00
#define TIM_DBL_12T 0x0B00
#define TIM_DBL_13T 0x0C00
#define TIM_DBL_14T 0x0D00
#define TIM_DBL_15T 0x0E00
#define TIM_DBL_16T 0x0F00
#define TIM_DBL_17T 0x1000
#define TIM_DBL_18T 0x1100

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
