#pragma once

#include "wch/hw/base.h"
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

typedef struct {
  __IO uint32_t INTFR;  /* DMA Interrupt Status Register     */
  __IO uint32_t INTFCR; /* DMA Interrupt Flag Clear Register */
  dma_channel_t ch[7];
} dma_t;

#define DMA1  ((dma_t *)DMA1_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* DMA_data_transfer_direction */
#define DMA_DIR_PERIPHDST ((uint32_t)0x00000010)
#define DMA_DIR_PERIPHSRC ((uint32_t)0x00000000)

/* DMA_peripheral_incremented_mode */
#define DMA_PERIPHINC_EN  ((uint32_t)0x00000040)

/* DMA_memory_incremented_mode */
#define DMA_MEMINC_EN  ((uint32_t)0x00000080)

/* DMA_peripheral_data_size */
#define DMA_PERIPH_BYTE     ((uint32_t)0x00000000)
#define DMA_PERIPH_HALFWORD ((uint32_t)0x00000100)
#define DMA_PERIPH_WORD     ((uint32_t)0x00000200)

/* DMA_memory_data_size */
#define DMA_MEMORY_BYTE     ((uint32_t)0x00000000)
#define DMA_MEMORY_HALFWORD ((uint32_t)0x00000400)
#define DMA_MEMORY_WORD     ((uint32_t)0x00000800)

/* DMA_circular_normal_mode */
#define DMA_MODE_CIRCULAR ((uint32_t)0x00000020)
#define DMA_MODE_NORMAL   ((uint32_t)0x00000000)

/* DMA_priority_level */
#define DMA_PRIORITY_VERYHIGH ((uint32_t)0x00003000)
#define DMA_PRIORITY_HIGH     ((uint32_t)0x00002000)
#define DMA_PRIORITY_MEDIUM   ((uint32_t)0x00001000)
#define DMA_PRIORITY_LOW      ((uint32_t)0x00000000)

/* DMA_memory_to_memory */
#define DMA_M2M_EN  ((uint32_t)0x00004000)

/* DMA_interrupts_definition */
#define DMA_MASK1 ((uint32_t)0x0000000F)  /* Channel 1 interrupt pending bit masks */
#define DMA_GL1   ((uint32_t)0x00000001)  /* Channel 1 Global interrupt flag */
#define DMA_TC1   ((uint32_t)0x00000002)  /* Channel 1 Transfer Complete flag */
#define DMA_HT1   ((uint32_t)0x00000004)  /* Channel 1 Half Transfer flag */
#define DMA_TE1   ((uint32_t)0x00000008)  /* Channel 1 Transfer Error flag */

#define DMA_MASK2 ((uint32_t)0x000000F0)  /* Channel 2 interrupt pending bit masks */
#define DMA_GL2   ((uint32_t)0x00000010)  /* Channel 2 Global interrupt flag */
#define DMA_TC2   ((uint32_t)0x00000020)  /* Channel 2 Transfer Complete flag */
#define DMA_HT2   ((uint32_t)0x00000040)  /* Channel 2 Half Transfer flag */
#define DMA_TE2   ((uint32_t)0x00000080)  /* Channel 2 Transfer Error flag */

#define DMA_MASK3 ((uint32_t)0x00000F00)  /* Channel 3 interrupt pending bit masks */
#define DMA_GL3   ((uint32_t)0x00000100)  /* Channel 3 Global interrupt flag */
#define DMA_TC3   ((uint32_t)0x00000200)  /* Channel 3 Transfer Complete flag */
#define DMA_HT3   ((uint32_t)0x00000400)  /* Channel 3 Half Transfer flag */
#define DMA_TE3   ((uint32_t)0x00000800)  /* Channel 3 Transfer Error flag */

#define DMA_MASK4 ((uint32_t)0x0000F000)  /* Channel 4 interrupt pending bit masks */
#define DMA_GL4   ((uint32_t)0x00001000)  /* Channel 4 Global interrupt flag */
#define DMA_TC4   ((uint32_t)0x00002000)  /* Channel 4 Transfer Complete flag */
#define DMA_HT4   ((uint32_t)0x00004000)  /* Channel 4 Half Transfer flag */
#define DMA_TE4   ((uint32_t)0x00008000)  /* Channel 4 Transfer Error flag */

#define DMA_MASK5 ((uint32_t)0x000F0000)  /* Channel 5 interrupt pending bit masks */
#define DMA_GL5   ((uint32_t)0x00010000)  /* Channel 5 Global interrupt flag */
#define DMA_TC5   ((uint32_t)0x00020000)  /* Channel 5 Transfer Complete flag */
#define DMA_HT5   ((uint32_t)0x00040000)  /* Channel 5 Half Transfer flag */
#define DMA_TE5   ((uint32_t)0x00080000)  /* Channel 5 Transfer Error flag */

#define DMA_MASK6 ((uint32_t)0x00F00000)  /* Channel 6 interrupt pending bit masks */
#define DMA_GL6   ((uint32_t)0x00100000)  /* Channel 6 Global interrupt flag */
#define DMA_TC6   ((uint32_t)0x00200000)  /* Channel 6 Transfer Complete flag */
#define DMA_HT6   ((uint32_t)0x00400000)  /* Channel 6 Half Transfer flag */
#define DMA_TE6   ((uint32_t)0x00800000)  /* Channel 6 Transfer Error flag */

#define DMA_MASK7 ((uint32_t)0x0F000000)  /* Channel 7 interrupt pending bit masks */
#define DMA_GL7   ((uint32_t)0x01000000)  /* Channel 7 Global interrupt flag */
#define DMA_TC7   ((uint32_t)0x02000000)  /* Channel 7 Transfer Complete flag */
#define DMA_HT7   ((uint32_t)0x04000000)  /* Channel 7 Half Transfer flag */
#define DMA_TE7   ((uint32_t)0x08000000)  /* Channel 7 Transfer Error flag */

/* DMA registers Masks */
#define CFGR_CLEAR_MASK ((uint32_t)0xFFFF800F)

/*******************  Bit definition for DMA_CFGR register  *******************/
#define DMA_CFGR_EN   ((uint16_t)0x0001) /* Channel enable*/
#define DMA_CFGR_TCIE ((uint16_t)0x0002) /* Transfer complete interrupt enable */
#define DMA_CFGR_HTIE ((uint16_t)0x0004) /* Half Transfer interrupt enable */
#define DMA_CFGR_TEIE ((uint16_t)0x0008) /* Transfer error interrupt enable */
#define DMA_CFGR_DIR  ((uint16_t)0x0010) /* Data transfer direction (Setting = Memory -> Peripheral) */
#define DMA_CFGR_CIRC ((uint16_t)0x0020) /* Circular mode */
#define DMA_CFGR_PINC ((uint16_t)0x0040) /* Peripheral increment mode */
#define DMA_CFGR_MINC ((uint16_t)0x0080) /* Memory increment mode */

#define DMA_CFGR_PSIZE   ((uint16_t)0x0300) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CFGR_PSIZE_0 ((uint16_t)0x0100) /* Bit 0 */
#define DMA_CFGR_PSIZE_1 ((uint16_t)0x0200) /* Bit 1 */

#define DMA_CFGR_MSIZE   ((uint16_t)0x0C00) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CFGR_MSIZE_0 ((uint16_t)0x0400) /* Bit 0 */
#define DMA_CFGR_MSIZE_1 ((uint16_t)0x0800) /* Bit 1 */

#define DMA_CFGR_PL   ((uint16_t)0x3000) /* PL[1:0] bits(Channel Priority level) */
#define DMA_CFGR_PL_0 ((uint16_t)0x1000) /* Bit 0 */
#define DMA_CFGR_PL_1 ((uint16_t)0x2000) /* Bit 1 */

#define DMA_CFGR_MEM2MEM ((uint16_t)0x4000) /* Memory to memory mode */

/******************  Bit definition for DMA_CNTR register  ******************/
#define DMA_CNTR_NDT ((uint16_t)0xFFFF) /* Number of data to Transfer */

/******************  Bit definition for DMA_PADDR register  *******************/
#define DMA_PADDR_PA ((uint32_t)0xFFFFFFFF) /* Peripheral Address */

/******************  Bit definition for DMA_MADDR register  *******************/
#define DMA_MADDR_MA ((uint32_t)0xFFFFFFFF) /* Memory Address */

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
