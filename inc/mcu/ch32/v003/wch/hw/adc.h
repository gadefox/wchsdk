#pragma once

#include "wch/hw/def.h"

/******************************************************************************/
/*                        Analog to Digital Converter                         */
/******************************************************************************/

#define ADC1_BASE  (APB2PERIPH_BASE + 0x2400)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define ADC_STATR    0
#define ADC_CTLR1    4
#define ADC_CTLR2    8
#define ADC_SAMPTR1  12
#define ADC_SAMPTR2  16
#define ADC_IOFR1    20
#define ADC_IOFR2    24
#define ADC_IOFR3    28
#define ADC_IOFR4    32
#define ADC_WDHTR    36
#define ADC_WDLTR    40
#define ADC_RSQR1    44
#define ADC_RSQR2    48
#define ADC_RSQR3    52
#define ADC_ISQR     56
#define ADC_IDATAR1  60
#define ADC_IDATAR2  64
#define ADC_IDATAR3  68
#define ADC_IDATAR4  72
#define ADC_RDATAR   76
#define ADC_DLYR     80

#else

//------------------------------------------------------------------------------

typedef enum {
  ADC_CHANNEL1,  /* 0 */
  ADC_CHANNEL2,  /* 1 */
  ADC_CHANNEL3,  /* 2 */
  ADC_CHANNEL4,  /* 3 */
  ADC_CHANNEL5,  /* 4 */
  ADC_CHANNEL6,  /* 5 */
  ADC_CHANNEL7,  /* 6 */
  ADC_CHANNEL8,  /* 7 */
  ADC_CHANNEL9,  /* 8 */
  ADC_CHANNEL10  /* 9 */
} adc_channel_t;

/* ADC_sampling_time */
typedef enum {
  ADC_SMP_3CYCLES,   /* 0 */
  ADC_SMP_9CYCLES,   /* 1 */
  ADC_SMP_15CYCLES,  /* 2 */
  ADC_SMP_30CYCLES,  /* 3 */
  ADC_SMP_43CYCLES,  /* 4 */
  ADC_SMP_57CYCLES,  /* 5 */
  ADC_SMP_73CYCLES,  /* 6 */
  ADC_SMP_241CYCLES  /* 7 */
} adc_smp_t;

typedef struct {
  __IO uint32_t STATR;          /* ADC Status Register                         */
  __IO uint32_t CTLR1;          /* ADC Control Register 1                      */
  __IO uint32_t CTLR2;          /* ADC Control Register 2                      */
  __IO uint32_t SAMPTR[2];      /* ADC Sample Time Register x                  */
  __IO uint32_t IOFR[4];        /* ADC Injected Channel Data Offset Register x */
  __IO uint32_t WDHTR;          /* ADC Watchdog High Threshold Register        */
  __IO uint32_t WDLTR;          /* ADC Watchdog Low Threshold Register         */
  __IO uint32_t RSQR[3];        /* ADC Regular Sequence Register x             */
  __IO uint32_t ISQR;           /* ADC Injected Sequence Register              */
  __IO uint32_t IDATAR[4];      /* ADC Injected Data Register x                */
  __IO uint32_t RDATAR;         /* ADC Regular Data Register                   */
  __IO uint32_t DLYR;           /* ADC Delayed Data Register                   */
} adc_t;

#define ADC1  ((adc_t *)ADC1_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* ADC_interrupts_definition */
#define ADC_IT_EOC  0x0220
#define ADC_IT_AWD  0x0140
#define ADC_IT_JEOC 0x0480

/********************  Bit definition for ADC_STATR register *********************/
#define ADC_AWD   0x00000001 /* Analog watchdog flag */
#define ADC_EOC   0x00000002 /* End of conversion */
#define ADC_JEOC  0x00000004 /* Injected channel end of conversion */
#define ADC_JSTRT 0x00000008 /* Injected channel Start flag */
#define ADC_STRT  0x00000010 /* Regular channel Start flag */

/*******************  Bit definition for ADC_CTLR1 register *********************/
#define ADC_AWDCH 0x0000001F /* AWDCH[4:0] bits (Analog watchdog channel select bits) */

#define ADC_EOCIE   0x00000020 /* Interrupt enable for EOC */
#define ADC_AWDIE   0x00000040 /* Analog Watchdog interrupt enable */
#define ADC_JEOCIE  0x00000080 /* Interrupt enable for injected channels */
#define ADC_SCAN    0x00000100 /* Scan mode */
#define ADC_AWDSGL  0x00000200 /* Enable the watchdog on a single channel in scan mode */
#define ADC_JAUTO   0x00000400 /* Automatic injected group conversion */
#define ADC_DISCEN  0x00000800 /* Discontinuous mode on regular channels */
#define ADC_JDISCEN 0x00001000 /* Discontinuous mode on injected channels */

/* Discontinuous mode channel count */
#define ADC_DISCNUM 0x0000E000 /* DISCNUM[[15:13]] bits */

#define ADC_JAWDEN 0x00400000 /* Analog watchdog enable on injected channels */
#define ADC_AWDEN  0x00800000 /* Analog watchdog enable on regular channels */

/* ADC_calibration_voltage_definition [26:25] bits */
#define ADC_CALVOL   0x06000000
#define ADC_CALVOL50 0x02000000  /* 2/4 AVDD */
#define ADC_CALVOL75 0x04000000  /* 3/4 AVDD */

/*******************  Bit definition for ADC_CTLR2 register *********************/
#define ADC_ADEN   0x00000001 /* A/D Converter ON / OFF */
#define ADC_CONT   0x00000002 /* Continuous Conversion */
#define ADC_CAL    0x00000004 /* A/D Calibration */
#define ADC_RSTCAL 0x00000008 /* Reset Calibration */
#define ADC_DMA    0x00000100 /* Direct Memory access mode */
#define ADC_ALIGN  0x00000800 /* Data Alignment */

/* External event select for injected group */
#define ADC_JEXT          0x00007000 /* JEXTSEL[14:12] bits */
#define ADC_JEXT_TIM1_CC3 0x00000000
#define ADC_JEXT_TIM1_CC4 0x00001000
#define ADC_JEXT_TIM2_CC3 0x00002000
#define ADC_JEXT_TIM2_CC4 0x00003000
#define ADC_JEXT_PD1_PA2  0x00006000
#define ADC_JEXT_SWSTART  0x00007000

#define ADC_JEXTTRIG 0x00008000 /* External Trigger Conversion mode for injected channels */

/* External Event Select for regular group */
#define ADC_EXT             0x000E0000 /* EXTSEL[2:0] bits */
#define ADC_EXT_TIM1_TRGO   0x00000000
#define ADC_EXT_TIM1_CC1    0x00020000
#define ADC_EXT_TIM1_CC2    0x00040000
#define ADC_EXT_TIM2_TRGO   0x00060000
#define ADC_EXT_TIM2_CC1    0x00080000
#define ADC_EXT_TIM2_CC2    0x000A0000
#define ADC_EXT_EXT_PD3_PC2 0x000C0000
#define ADC_EXT_SWSTART     0x000E0000

#define ADC_EXTTRIG  0x00100000 /* External Trigger Conversion mode for regular channels */
#define ADC_JSWSTART 0x00200000 /* Start Conversion of injected channels */
#define ADC_SWSTART  0x00400000 /* Start Conversion of regular channels */
#define ADC_TSVREFE  0x00800000 /* Temperature Sensor and VREFINT Enable */

/******************  Bit definition for ADC_SAMPTRx register ********************/
#define ADC_SMP  0x3FFFFFFF
#define ADC_SMP0 0x00000007 /* SMP0[2:0]   bits (Channel 0/10 Sample time selection) */
#define ADC_SMP1 0x00000038 /* SMP1[5:3]   bits (Channel 1/11 Sample time selection) */
#define ADC_SMP2 0x000001C0 /* SMP2[8:6]   bits (Channel 2/12 Sample time selection) */
#define ADC_SMP3 0x00000E00 /* SMP3[11:9]  bits (Channel 3/13 Sample time selection) */
#define ADC_SMP4 0x00007000 /* SMP4[14:12] bits (Channel 4/14 Sample time selection) */
#define ADC_SMP5 0x00038000 /* SMP5[17:15] bits (Channel 5/15 Sample time selection) */
#define ADC_SMP6 0x001C0000 /* SMP6[20:18] bits (Channel 6 Sample time selection) */
#define ADC_SMP7 0x00E00000 /* SMP7[23:21] bits (Channel 7 Sample time selection) */
#define ADC_SMP8 0x07000000 /* SMP8[26:24] bits (Channel 8 Sample time selection) */
#define ADC_SMP9 0x38000000 /* SMP9[29:27] bits (Channel 9 Sample time selection) */

#define ADC_SMP0_POS 0
#define ADC_SMP1_POS 3
#define ADC_SMP2_POS 6
#define ADC_SMP3_POS 9
#define ADC_SMP4_POS 12
#define ADC_SMP5_POS 15
#define ADC_SMP6_POS 18
#define ADC_SMP7_POS 21
#define ADC_SMP8_POS 24
#define ADC_SMP9_POS 27

/******************  Bit definition for ADC_IOFRx register  *******************/
#define ADC_JOFFSET 0x000002FF /* Data offset for injected channel x */

/*******************  Bit definition for ADC_WDHTR register *********************/
#define ADC_HT 0x000002FF /* Analog watchdog high threshold */

/*******************  Bit definition for ADC_WDLTR register *********************/
#define ADC_LT 0x000002FF /* Analog watchdog low threshold */

/*******************  Bit definition for ADC_RSQRx register *******************/
#define ADC_SQ1 0x0000001F /* SQ1[4:0] bits (1st conversion in regular sequence) */
#define ADC_SQ2 0x000003E0 /* SQ2[9:5] bits (2nd conversion in regular sequence) */
#define ADC_SQ3 0x00007C00 /* SQ3[14:10] bits (3rd conversion in regular sequence) */
#define ADC_SQ4 0x000F8000 /* SQ4[19:15] bits (4th conversion in regular sequence) */
#define ADC_SQ5 0x01F00000 /* SQ5[24:20] bits (5th conversion in regular sequence) */
#define ADC_SQ6 0x3E000000 /* SQ6[29:25] bits (6th conversion in regular sequence) */

#define ADC_SQ1_POS 0
#define ADC_SQ2_POS 5
#define ADC_SQ3_POS 10
#define ADC_SQ4_POS 15
#define ADC_SQ5_POS 20
#define ADC_SQ6_POS 25

/*******************  Bit definition for ADC_ISQR register  *******************/
#define ADC_JSQ1 0x0000001F /* JSQ1[4:0] bits (1st conversion in injected sequence) */
#define ADC_JSQ2 0x000003E0 /* JSQ2[9:5] bits (2nd conversion in injected sequence) */
#define ADC_JSQ3 0x00007C00 /* JSQ3[14:10] bits (3rd conversion in injected sequence) */
#define ADC_JSQ4 0x000F8000 /* JSQ4[19:15] bits (4th conversion in injected sequence) */
#define ADC_L    0x00F00000 /* L[23:20] bits (Regular channel sequence length) */
#define ADC_JL   0x00300000 /* JL[25:24] bits (Injected Sequence length) */

#define ADC_JSQ1_POS 0
#define ADC_JSQ2_POS 5
#define ADC_JSQ3_POS 10
#define ADC_JSQ4_POS 15
#define ADC_L_POS    20
#define ADC_JL_POS   24

/********************  Bit definition for ADC_RDATAR register *********************/
#define ADC_RDATA      0x0000FFFF /* Regular data */
#define ADC_RDATA_ADC2 0xFFFF0000 /* ADC2 data */

#define ADC_RDATA_POS 16

/********************  Bit definition for ADC_DLYR register *********************/
#define ADC_DLY_SRC 0x00000200
#define ADC_DLY_VLU 0x000001FF

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
