#pragma once

#include "wch/hw/def.h"

/******************************************************************************/
/*                             DMA Controller                                 */
/******************************************************************************/

#define DMA1_BASE  AHBPERIPH_BASE

#define DMA1_CHANNEL1_BASE  (DMA1_BASE + 0x08)
#define DMA1_CHANNEL2_BASE  (DMA1_CHANNEL1_BASE + 0x14)  /* DMA1_BASE + 0x1C */
#define DMA1_CHANNEL3_BASE  (DMA1_CHANNEL2_BASE + 0x14)  /* DMA1_BASE + 0x30 */
#define DMA1_CHANNEL4_BASE  (DMA1_CHANNEL3_BASE + 0x14)  /* DMA1_BASE + 0x44 */
#define DMA1_CHANNEL5_BASE  (DMA1_CHANNEL4_BASE + 0x14)  /* DMA1_BASE + 0x58 */
#define DMA1_CHANNEL6_BASE  (DMA1_CHANNEL5_BASE + 0x14)  /* DMA1_BASE + 0x6C */
#define DMA1_CHANNEL7_BASE  (DMA1_CHANNEL6_BASE + 0x14)  /* DMA1_BASE + 0x80 */

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define DMA_INTFR   0
#define DMA_INTFCR  4

#define DMA_CHANNEL_CFGR   0
#define DMA_CHANNEL_CNTR   4
#define DMA_CHANNEL_PADDR  8
#define DMA_CHANNEL_MADDR  12

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t CFGR;  /* DMA Configuration Register      */
  __IO uint32_t CNTR;  /* DMA Number of Data Register     */
  __IO uint32_t PADDR; /* DMA Peripheral Address Register */
  __IO uint32_t MADDR; /* DMA Memory Address Register     */
       uint32_t RESERVED;
} dma_channel_t;

#define DMA1_CHANNEL1  ((dma_channel_t *)DMA1_CHANNEL1_BASE)
#define DMA1_CHANNEL2  ((dma_channel_t *)DMA1_CHANNEL2_BASE)
#define DMA1_CHANNEL3  ((dma_channel_t *)DMA1_CHANNEL3_BASE)
#define DMA1_CHANNEL4  ((dma_channel_t *)DMA1_CHANNEL4_BASE)
#define DMA1_CHANNEL5  ((dma_channel_t *)DMA1_CHANNEL5_BASE)
#define DMA1_CHANNEL6  ((dma_channel_t *)DMA1_CHANNEL6_BASE)
#define DMA1_CHANNEL7  ((dma_channel_t *)DMA1_CHANNEL7_BASE)

//------------------------------------------------------------------------------

typedef enum {
  DMA_INTF_GL1 = 0x1,  /* Global interrupt flag */
  DMA_INTF_TC1 = 0x2,  /* Transfer Complete flag */
  DMA_INTF_HT1 = 0x4,  /* Half Transfer flag */
  DMA_INTF_TE1 = 0x8   /* Transfer Error flag */
} dma_intf_t;

typedef struct {
  __IO uint32_t INTFR;  /* DMA Interrupt Status Register     */
  __IO uint32_t INTFCR; /* DMA Interrupt Flag Clear Register */
  dma_channel_t ch[7];
} dma_t;

#define DMA1  ((dma_t *)DMA1_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/******************  Bit definition for DMA_INTFCR register  ******************/
#define DMA_INTF_MSK1 0x0000000F  /* [3:0]   Channel 1 interrupt pending bit masks */
#define DMA_INTF_MSK2 0x000000F0  /* [7:4]   Channel 2 interrupt pending bit masks */
#define DMA_INTF_MSK3 0x00000F00  /* [11:8]  Channel 3 interrupt pending bit masks */
#define DMA_INTF_MSK4 0x0000F000  /* [15:12] Channel 4 interrupt pending bit masks */
#define DMA_INTF_MSK5 0x000F0000  /* [19:16] Channel 5 interrupt pending bit masks */
#define DMA_INTF_MSK6 0x00F00000  /* [23:20] Channel 6 interrupt pending bit masks */
#define DMA_INTF_MSK7 0x0F000000  /* [27:24] Channel 7 interrupt pending bit masks */

#define DMA_INTF_POS1 0
#define DMA_INTF_POS2 4
#define DMA_INTF_POS3 8
#define DMA_INTF_POS4 12
#define DMA_INTF_POS5 16
#define DMA_INTF_POS6 20
#define DMA_INTF_POS7 24

/*******************  Bit definition for DMA_CFGR register  *******************/
#define DMA_EN   0x00000001 /* Channel enable*/
#define DMA_TCIE 0x00000002 /* Transfer complete interrupt enable */
#define DMA_HTIE 0x00000004 /* Half Transfer interrupt enable */
#define DMA_TEIE 0x00000008 /* Transfer error interrupt enable */
#define DMA_DIR  0x00000010 /* Data transfer direction (Setting = Memory -> Peripheral) */
#define DMA_CIRC 0x00000020 /* Circular mode */
#define DMA_PINC 0x00000040 /* Peripheral increment mode */
#define DMA_MINC 0x00000080 /* Memory increment mode */

/* Peripheral size */
#define DMA_PSIZE_MSK      0x00000300 /* PSIZE[9:8] bits */
#define DMA_PSIZE_BYTE     0x00000000
#define DMA_PSIZE_HALFWORD 0x00000100
#define DMA_PSIZE_WORD     0x00000200

/* Memory size */
#define DMA_MSIZE_MSK      0x00000C00 /* MSIZE[11:10] bits */
#define DMA_MSIZE_BYTE     0x00000000
#define DMA_MSIZE_HALFWORD 0x00000400
#define DMA_MSIZE_WORD     0x00000800

/* Channel Priority level */
#define DMA_PRIOR_MSK    0x00003000 /* PL[13:12] bits */
#define DMA_PRIOR_LOW    0x00000000
#define DMA_PRIOR_MEDIUM 0x00001000
#define DMA_PRIOR_HIGH   0x00002000

#define DMA_MEM2MEM 0x00004000 /* Memory to memory mode */

/******************  Bit definition for DMA_CNTR register  ******************/
#define DMA_CNT_NDT 0x0000FFFF /* Number of data to Transfer */

/******************  Bit definition for DMA_PADDR register  *******************/
#define DMA_PADD_PA 0xFFFFFFFF /* Peripheral Address */

/******************  Bit definition for DMA_MADDR register  *******************/
#define DMA_MADD_MA 0xFFFFFFFF /* Memory Address */

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
