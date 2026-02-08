#pragma once

#include "wch/hw/base.h"
#include "wch/hw/edf.h"

/******************************************************************************/
/*                             DMA Controller                                 */
/******************************************************************************/

#define DMA1_BASE  (AHBPERIPH_BASE + 0x0000)

#define DMA1_CHANNEL1_BASE  (AHBPERIPH_BASE + 0X0008)
#define DMA1_CHANNEL2_BASE  (AHBPERIPH_BASE + 0X001C)
#define DMA1_CHANNEL3_BASE  (AHBPERIPH_BASE + 0X0030)
#define DMA1_CHANNEL4_BASE  (AHBPERIPH_BASE + 0X0044)
#define DMA1_CHANNEL5_BASE  (AHBPERIPH_BASE + 0X0058)
#define DMA1_CHANNEL6_BASE  (AHBPERIPH_BASE + 0X006C)
#define DMA1_CHANNEL7_BASE  (AHBPERIPH_BASE + 0X0080)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define DMA_CHANNEL_CFGR   0
#define DMA_CHANNEL_CNTR   4
#define DMA_CHANNEL_PADDR  8
#define DMA_CHANNEL_MADDR  12

#define DMA_INTFR   0
#define DMA_INTFCR  4

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t CFGR;  /* DMA Configuration Register      */
  __IO uint32_t CNTR;  /* DMA Number of Data Register     */
  __IO uint32_t PADDR; /* DMA Peripheral Address Register */
  __IO uint32_t MADDR; /* DMA Memory Address Register     */
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
} dma_t;

#define DMA1  ((dma_t *)DMA1_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_CHANNEL1_IT_MASK ((uint32_t)(DMA_GIF1 | DMA_TCIF1 | DMA_HTIF1 | DMA_TEIF1))
#define DMA1_CHANNEL2_IT_MASK ((uint32_t)(DMA_GIF2 | DMA_TCIF2 | DMA_HTIF2 | DMA_TEIF2))
#define DMA1_CHANNEL3_IT_MASK ((uint32_t)(DMA_GIF3 | DMA_TCIF3 | DMA_HTIF3 | DMA_TEIF3))
#define DMA1_CHANNEL4_IT_MASK ((uint32_t)(DMA_GIF4 | DMA_TCIF4 | DMA_HTIF4 | DMA_TEIF4))
#define DMA1_CHANNEL5_IT_MASK ((uint32_t)(DMA_GIF5 | DMA_TCIF5 | DMA_HTIF5 | DMA_TEIF5))
#define DMA1_CHANNEL6_IT_MASK ((uint32_t)(DMA_GIF6 | DMA_TCIF6 | DMA_HTIF6 | DMA_TEIF6))
#define DMA1_CHANNEL7_IT_MASK ((uint32_t)(DMA_GIF7 | DMA_TCIF7 | DMA_HTIF7 | DMA_TEIF7))

/* DMA2 FLAG mask */
// Editor's note: Overloaded Definition.
#define DMA2_FLAG_MASK ((uint32_t)0x10000000)

/* DMA registers Masks */
#define CFGR_CLEAR_Mask ((uint32_t)0xFFFF800F)

/*******************  Bit definition for DMA_INTFR register  ********************/
#define DMA_GIF1  ((uint32_t)0x00000001) /* Channel 1 Global interrupt flag */
#define DMA_TCIF1 ((uint32_t)0x00000002) /* Channel 1 Transfer Complete flag */
#define DMA_HTIF1 ((uint32_t)0x00000004) /* Channel 1 Half Transfer flag */
#define DMA_TEIF1 ((uint32_t)0x00000008) /* Channel 1 Transfer Error flag */
#define DMA_GIF2  ((uint32_t)0x00000010) /* Channel 2 Global interrupt flag */
#define DMA_TCIF2 ((uint32_t)0x00000020) /* Channel 2 Transfer Complete flag */
#define DMA_HTIF2 ((uint32_t)0x00000040) /* Channel 2 Half Transfer flag */
#define DMA_TEIF2 ((uint32_t)0x00000080) /* Channel 2 Transfer Error flag */
#define DMA_GIF3  ((uint32_t)0x00000100) /* Channel 3 Global interrupt flag */
#define DMA_TCIF3 ((uint32_t)0x00000200) /* Channel 3 Transfer Complete flag */
#define DMA_HTIF3 ((uint32_t)0x00000400) /* Channel 3 Half Transfer flag */
#define DMA_TEIF3 ((uint32_t)0x00000800) /* Channel 3 Transfer Error flag */
#define DMA_GIF4  ((uint32_t)0x00001000) /* Channel 4 Global interrupt flag */
#define DMA_TCIF4 ((uint32_t)0x00002000) /* Channel 4 Transfer Complete flag */
#define DMA_HTIF4 ((uint32_t)0x00004000) /* Channel 4 Half Transfer flag */
#define DMA_TEIF4 ((uint32_t)0x00008000) /* Channel 4 Transfer Error flag */
#define DMA_GIF5  ((uint32_t)0x00010000) /* Channel 5 Global interrupt flag */
#define DMA_TCIF5 ((uint32_t)0x00020000) /* Channel 5 Transfer Complete flag */
#define DMA_HTIF5 ((uint32_t)0x00040000) /* Channel 5 Half Transfer flag */
#define DMA_TEIF5 ((uint32_t)0x00080000) /* Channel 5 Transfer Error flag */
#define DMA_GIF6  ((uint32_t)0x00100000) /* Channel 6 Global interrupt flag */
#define DMA_TCIF6 ((uint32_t)0x00200000) /* Channel 6 Transfer Complete flag */
#define DMA_HTIF6 ((uint32_t)0x00400000) /* Channel 6 Half Transfer flag */
#define DMA_TEIF6 ((uint32_t)0x00800000) /* Channel 6 Transfer Error flag */
#define DMA_GIF7  ((uint32_t)0x01000000) /* Channel 7 Global interrupt flag */
#define DMA_TCIF7 ((uint32_t)0x02000000) /* Channel 7 Transfer Complete flag */
#define DMA_HTIF7 ((uint32_t)0x04000000) /* Channel 7 Half Transfer flag */
#define DMA_TEIF7 ((uint32_t)0x08000000) /* Channel 7 Transfer Error flag */

/*******************  Bit definition for DMA_INTFCR register  *******************/
#define DMA_CGIF1  ((uint32_t)0x00000001) /* Channel 1 Global interrupt clear */
#define DMA_CTCIF1 ((uint32_t)0x00000002) /* Channel 1 Transfer Complete clear */
#define DMA_CHTIF1 ((uint32_t)0x00000004) /* Channel 1 Half Transfer clear */
#define DMA_CTEIF1 ((uint32_t)0x00000008) /* Channel 1 Transfer Error clear */
#define DMA_CGIF2  ((uint32_t)0x00000010) /* Channel 2 Global interrupt clear */
#define DMA_CTCIF2 ((uint32_t)0x00000020) /* Channel 2 Transfer Complete clear */
#define DMA_CHTIF2 ((uint32_t)0x00000040) /* Channel 2 Half Transfer clear */
#define DMA_CTEIF2 ((uint32_t)0x00000080) /* Channel 2 Transfer Error clear */
#define DMA_CGIF3  ((uint32_t)0x00000100) /* Channel 3 Global interrupt clear */
#define DMA_CTCIF3 ((uint32_t)0x00000200) /* Channel 3 Transfer Complete clear */
#define DMA_CHTIF3 ((uint32_t)0x00000400) /* Channel 3 Half Transfer clear */
#define DMA_CTEIF3 ((uint32_t)0x00000800) /* Channel 3 Transfer Error clear */
#define DMA_CGIF4  ((uint32_t)0x00001000) /* Channel 4 Global interrupt clear */
#define DMA_CTCIF4 ((uint32_t)0x00002000) /* Channel 4 Transfer Complete clear */
#define DMA_CHTIF4 ((uint32_t)0x00004000) /* Channel 4 Half Transfer clear */
#define DMA_CTEIF4 ((uint32_t)0x00008000) /* Channel 4 Transfer Error clear */
#define DMA_CGIF5  ((uint32_t)0x00010000) /* Channel 5 Global interrupt clear */
#define DMA_CTCIF5 ((uint32_t)0x00020000) /* Channel 5 Transfer Complete clear */
#define DMA_CHTIF5 ((uint32_t)0x00040000) /* Channel 5 Half Transfer clear */
#define DMA_CTEIF5 ((uint32_t)0x00080000) /* Channel 5 Transfer Error clear */
#define DMA_CGIF6  ((uint32_t)0x00100000) /* Channel 6 Global interrupt clear */
#define DMA_CTCIF6 ((uint32_t)0x00200000) /* Channel 6 Transfer Complete clear */
#define DMA_CHTIF6 ((uint32_t)0x00400000) /* Channel 6 Half Transfer clear */
#define DMA_CTEIF6 ((uint32_t)0x00800000) /* Channel 6 Transfer Error clear */
#define DMA_CGIF7  ((uint32_t)0x01000000) /* Channel 7 Global interrupt clear */
#define DMA_CTCIF7 ((uint32_t)0x02000000) /* Channel 7 Transfer Complete clear */
#define DMA_CHTIF7 ((uint32_t)0x04000000) /* Channel 7 Half Transfer clear */
#define DMA_CTEIF7 ((uint32_t)0x08000000) /* Channel 7 Transfer Error clear */

/*******************  Bit definition for DMA_CFGR1 register  *******************/
#define DMA_CFGR1_EN   ((uint16_t)0x0001) /* Channel enable*/
#define DMA_CFGR1_TCIE ((uint16_t)0x0002) /* Transfer complete interrupt enable */
#define DMA_CFGR1_HTIE ((uint16_t)0x0004) /* Half Transfer interrupt enable */
#define DMA_CFGR1_TEIE ((uint16_t)0x0008) /* Transfer error interrupt enable */
#define DMA_CFGR1_DIR  ((uint16_t)0x0010) /* Data transfer direction (Setting = Memory -> Peripheral) */
#define DMA_CFGR1_CIRC ((uint16_t)0x0020) /* Circular mode */
#define DMA_CFGR1_PINC ((uint16_t)0x0040) /* Peripheral increment mode */
#define DMA_CFGR1_MINC ((uint16_t)0x0080) /* Memory increment mode */

#define DMA_CFGR1_PSIZE   ((uint16_t)0x0300) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CFGR1_PSIZE_0 ((uint16_t)0x0100) /* Bit 0 */
#define DMA_CFGR1_PSIZE_1 ((uint16_t)0x0200) /* Bit 1 */

#define DMA_CFGR1_MSIZE   ((uint16_t)0x0C00) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CFGR1_MSIZE_0 ((uint16_t)0x0400) /* Bit 0 */
#define DMA_CFGR1_MSIZE_1 ((uint16_t)0x0800) /* Bit 1 */

#define DMA_CFGR1_PL   ((uint16_t)0x3000) /* PL[1:0] bits(Channel Priority level) */
#define DMA_CFGR1_PL_0 ((uint16_t)0x1000) /* Bit 0 */
#define DMA_CFGR1_PL_1 ((uint16_t)0x2000) /* Bit 1 */

#define DMA_CFGR1_MEM2MEM ((uint16_t)0x4000) /* Memory to memory mode */

/*******************  Bit definition for DMA_CFGR2 register  *******************/
#define DMA_CFGR2_EN   ((uint16_t)0x0001) /* Channel enable */
#define DMA_CFGR2_TCIE ((uint16_t)0x0002) /* Transfer complete interrupt enable */
#define DMA_CFGR2_HTIE ((uint16_t)0x0004) /* Half Transfer interrupt enable */
#define DMA_CFGR2_TEIE ((uint16_t)0x0008) /* Transfer error interrupt enable */
#define DMA_CFGR2_DIR  ((uint16_t)0x0010) /* Data transfer direction */
#define DMA_CFGR2_CIRC ((uint16_t)0x0020) /* Circular mode */
#define DMA_CFGR2_PINC ((uint16_t)0x0040) /* Peripheral increment mode */
#define DMA_CFGR2_MINC ((uint16_t)0x0080) /* Memory increment mode */

#define DMA_CFGR2_PSIZE   ((uint16_t)0x0300) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CFGR2_PSIZE_0 ((uint16_t)0x0100) /* Bit 0 */
#define DMA_CFGR2_PSIZE_1 ((uint16_t)0x0200) /* Bit 1 */

#define DMA_CFGR2_MSIZE   ((uint16_t)0x0C00) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CFGR2_MSIZE_0 ((uint16_t)0x0400) /* Bit 0 */
#define DMA_CFGR2_MSIZE_1 ((uint16_t)0x0800) /* Bit 1 */

#define DMA_CFGR2_PL   ((uint16_t)0x3000) /* PL[1:0] bits (Channel Priority level) */
#define DMA_CFGR2_PL_0 ((uint16_t)0x1000) /* Bit 0 */
#define DMA_CFGR2_PL_1 ((uint16_t)0x2000) /* Bit 1 */

#define DMA_CFGR2_MEM2MEM ((uint16_t)0x4000) /* Memory to memory mode */

/*******************  Bit definition for DMA_CFGR3 register  *******************/
#define DMA_CFGR3_EN   ((uint16_t)0x0001) /* Channel enable */
#define DMA_CFGR3_TCIE ((uint16_t)0x0002) /* Transfer complete interrupt enable */
#define DMA_CFGR3_HTIE ((uint16_t)0x0004) /* Half Transfer interrupt enable */
#define DMA_CFGR3_TEIE ((uint16_t)0x0008) /* Transfer error interrupt enable */
#define DMA_CFGR3_DIR  ((uint16_t)0x0010) /* Data transfer direction */
#define DMA_CFGR3_CIRC ((uint16_t)0x0020) /* Circular mode */
#define DMA_CFGR3_PINC ((uint16_t)0x0040) /* Peripheral increment mode */
#define DMA_CFGR3_MINC ((uint16_t)0x0080) /* Memory increment mode */

#define DMA_CFGR3_PSIZE   ((uint16_t)0x0300) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CFGR3_PSIZE_0 ((uint16_t)0x0100) /* Bit 0 */
#define DMA_CFGR3_PSIZE_1 ((uint16_t)0x0200) /* Bit 1 */

#define DMA_CFGR3_MSIZE   ((uint16_t)0x0C00) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CFGR3_MSIZE_0 ((uint16_t)0x0400) /* Bit 0 */
#define DMA_CFGR3_MSIZE_1 ((uint16_t)0x0800) /* Bit 1 */

#define DMA_CFGR3_PL   ((uint16_t)0x3000) /* PL[1:0] bits (Channel Priority level) */
#define DMA_CFGR3_PL_0 ((uint16_t)0x1000) /* Bit 0 */
#define DMA_CFGR3_PL_1 ((uint16_t)0x2000) /* Bit 1 */

#define DMA_CFGR3_MEM2MEM ((uint16_t)0x4000) /* Memory to memory mode */

/*******************  Bit definition for DMA_CFGR4 register  *******************/
#define DMA_CFGR4_EN   ((uint16_t)0x0001) /* Channel enable */
#define DMA_CFGR4_TCIE ((uint16_t)0x0002) /* Transfer complete interrupt enable */
#define DMA_CFGR4_HTIE ((uint16_t)0x0004) /* Half Transfer interrupt enable */
#define DMA_CFGR4_TEIE ((uint16_t)0x0008) /* Transfer error interrupt enable */
#define DMA_CFGR4_DIR  ((uint16_t)0x0010) /* Data transfer direction */
#define DMA_CFGR4_CIRC ((uint16_t)0x0020) /* Circular mode */
#define DMA_CFGR4_PINC ((uint16_t)0x0040) /* Peripheral increment mode */
#define DMA_CFGR4_MINC ((uint16_t)0x0080) /* Memory increment mode */

#define DMA_CFGR4_PSIZE   ((uint16_t)0x0300) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CFGR4_PSIZE_0 ((uint16_t)0x0100) /* Bit 0 */
#define DMA_CFGR4_PSIZE_1 ((uint16_t)0x0200) /* Bit 1 */

#define DMA_CFGR4_MSIZE   ((uint16_t)0x0C00) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CFGR4_MSIZE_0 ((uint16_t)0x0400) /* Bit 0 */
#define DMA_CFGR4_MSIZE_1 ((uint16_t)0x0800) /* Bit 1 */

#define DMA_CFGR4_PL   ((uint16_t)0x3000) /* PL[1:0] bits (Channel Priority level) */
#define DMA_CFGR4_PL_0 ((uint16_t)0x1000) /* Bit 0 */
#define DMA_CFGR4_PL_1 ((uint16_t)0x2000) /* Bit 1 */

#define DMA_CFGR4_MEM2MEM ((uint16_t)0x4000) /* Memory to memory mode */

/******************  Bit definition for DMA_CFGR5 register  *******************/
#define DMA_CFGR5_EN   ((uint16_t)0x0001) /* Channel enable */
#define DMA_CFGR5_TCIE ((uint16_t)0x0002) /* Transfer complete interrupt enable */
#define DMA_CFGR5_HTIE ((uint16_t)0x0004) /* Half Transfer interrupt enable */
#define DMA_CFGR5_TEIE ((uint16_t)0x0008) /* Transfer error interrupt enable */
#define DMA_CFGR5_DIR  ((uint16_t)0x0010) /* Data transfer direction */
#define DMA_CFGR5_CIRC ((uint16_t)0x0020) /* Circular mode */
#define DMA_CFGR5_PINC ((uint16_t)0x0040) /* Peripheral increment mode */
#define DMA_CFGR5_MINC ((uint16_t)0x0080) /* Memory increment mode */

#define DMA_CFGR5_PSIZE   ((uint16_t)0x0300) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CFGR5_PSIZE_0 ((uint16_t)0x0100) /* Bit 0 */
#define DMA_CFGR5_PSIZE_1 ((uint16_t)0x0200) /* Bit 1 */

#define DMA_CFGR5_MSIZE   ((uint16_t)0x0C00) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CFGR5_MSIZE_0 ((uint16_t)0x0400) /* Bit 0 */
#define DMA_CFGR5_MSIZE_1 ((uint16_t)0x0800) /* Bit 1 */

#define DMA_CFGR5_PL   ((uint16_t)0x3000) /* PL[1:0] bits (Channel Priority level) */
#define DMA_CFGR5_PL_0 ((uint16_t)0x1000) /* Bit 0 */
#define DMA_CFGR5_PL_1 ((uint16_t)0x2000) /* Bit 1 */

#define DMA_CFGR5_MEM2MEM ((uint16_t)0x4000) /* Memory to memory mode enable */

/*******************  Bit definition for DMA_CFGR6 register  *******************/
#define DMA_CFGR6_EN   ((uint16_t)0x0001) /* Channel enable */
#define DMA_CFGR6_TCIE ((uint16_t)0x0002) /* Transfer complete interrupt enable */
#define DMA_CFGR6_HTIE ((uint16_t)0x0004) /* Half Transfer interrupt enable */
#define DMA_CFGR6_TEIE ((uint16_t)0x0008) /* Transfer error interrupt enable */
#define DMA_CFGR6_DIR  ((uint16_t)0x0010) /* Data transfer direction */
#define DMA_CFGR6_CIRC ((uint16_t)0x0020) /* Circular mode */
#define DMA_CFGR6_PINC ((uint16_t)0x0040) /* Peripheral increment mode */
#define DMA_CFGR6_MINC ((uint16_t)0x0080) /* Memory increment mode */

#define DMA_CFGR6_PSIZE   ((uint16_t)0x0300) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CFGR6_PSIZE_0 ((uint16_t)0x0100) /* Bit 0 */
#define DMA_CFGR6_PSIZE_1 ((uint16_t)0x0200) /* Bit 1 */

#define DMA_CFGR6_MSIZE   ((uint16_t)0x0C00) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CFGR6_MSIZE_0 ((uint16_t)0x0400) /* Bit 0 */
#define DMA_CFGR6_MSIZE_1 ((uint16_t)0x0800) /* Bit 1 */

#define DMA_CFGR6_PL   ((uint16_t)0x3000) /* PL[1:0] bits (Channel Priority level) */
#define DMA_CFGR6_PL_0 ((uint16_t)0x1000) /* Bit 0 */
#define DMA_CFGR6_PL_1 ((uint16_t)0x2000) /* Bit 1 */

#define DMA_CFGR6_MEM2MEM ((uint16_t)0x4000) /* Memory to memory mode */

/*******************  Bit definition for DMA_CFGR7 register  *******************/
#define DMA_CFGR7_EN   ((uint16_t)0x0001) /* Channel enable */
#define DMA_CFGR7_TCIE ((uint16_t)0x0002) /* Transfer complete interrupt enable */
#define DMA_CFGR7_HTIE ((uint16_t)0x0004) /* Half Transfer interrupt enable */
#define DMA_CFGR7_TEIE ((uint16_t)0x0008) /* Transfer error interrupt enable */
#define DMA_CFGR7_DIR  ((uint16_t)0x0010) /* Data transfer direction */
#define DMA_CFGR7_CIRC ((uint16_t)0x0020) /* Circular mode */
#define DMA_CFGR7_PINC ((uint16_t)0x0040) /* Peripheral increment mode */
#define DMA_CFGR7_MINC ((uint16_t)0x0080) /* Memory increment mode */

#define DMA_CFGR7_PSIZE   ((uint16_t)0x0300) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CFGR7_PSIZE_0 ((uint16_t)0x0100) /* Bit 0 */
#define DMA_CFGR7_PSIZE_1 ((uint16_t)0x0200) /* Bit 1 */

#define DMA_CFGR7_MSIZE   ((uint16_t)0x0C00) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CFGR7_MSIZE_0 ((uint16_t)0x0400) /* Bit 0 */
#define DMA_CFGR7_MSIZE_1 ((uint16_t)0x0800) /* Bit 1 */

#define DMA_CFGR7_PL   ((uint16_t)0x3000) /* PL[1:0] bits (Channel Priority level) */
#define DMA_CFGR7_PL_0 ((uint16_t)0x1000) /* Bit 0 */
#define DMA_CFGR7_PL_1 ((uint16_t)0x2000) /* Bit 1 */

#define DMA_CFGR7_MEM2MEM ((uint16_t)0x4000) /* Memory to memory mode enable */

/******************  Bit definition for DMA_CNTR1 register  ******************/
#define DMA_CNTR1_NDT ((uint16_t)0xFFFF) /* Number of data to Transfer */

/******************  Bit definition for DMA_CNTR2 register  ******************/
#define DMA_CNTR2_NDT ((uint16_t)0xFFFF) /* Number of data to Transfer */

/******************  Bit definition for DMA_CNTR3 register  ******************/
#define DMA_CNTR3_NDT ((uint16_t)0xFFFF) /* Number of data to Transfer */

/******************  Bit definition for DMA_CNTR4 register  ******************/
#define DMA_CNTR4_NDT ((uint16_t)0xFFFF) /* Number of data to Transfer */

/******************  Bit definition for DMA_CNTR5 register  ******************/
#define DMA_CNTR5_NDT ((uint16_t)0xFFFF) /* Number of data to Transfer */

/******************  Bit definition for DMA_CNTR6 register  ******************/
#define DMA_CNTR6_NDT ((uint16_t)0xFFFF) /* Number of data to Transfer */

/******************  Bit definition for DMA_CNTR7 register  ******************/
#define DMA_CNTR7_NDT ((uint16_t)0xFFFF) /* Number of data to Transfer */

/******************  Bit definition for DMA_PADDR1 register  *******************/
#define DMA_PADDR1_PA ((uint32_t)0xFFFFFFFF) /* Peripheral Address */

/******************  Bit definition for DMA_PADDR2 register  *******************/
#define DMA_PADDR2_PA ((uint32_t)0xFFFFFFFF) /* Peripheral Address */

/******************  Bit definition for DMA_PADDR3 register  *******************/
#define DMA_PADDR3_PA ((uint32_t)0xFFFFFFFF) /* Peripheral Address */

/******************  Bit definition for DMA_PADDR4 register  *******************/
#define DMA_PADDR4_PA ((uint32_t)0xFFFFFFFF) /* Peripheral Address */

/******************  Bit definition for DMA_PADDR5 register  *******************/
#define DMA_PADDR5_PA ((uint32_t)0xFFFFFFFF) /* Peripheral Address */

/******************  Bit definition for DMA_PADDR6 register  *******************/
#define DMA_PADDR6_PA ((uint32_t)0xFFFFFFFF) /* Peripheral Address */

/******************  Bit definition for DMA_PADDR7 register  *******************/
#define DMA_PADDR7_PA ((uint32_t)0xFFFFFFFF) /* Peripheral Address */

/******************  Bit definition for DMA_MADDR1 register  *******************/
#define DMA_MADDR1_MA ((uint32_t)0xFFFFFFFF) /* Memory Address */

/******************  Bit definition for DMA_MADDR2 register  *******************/
#define DMA_MADDR2_MA ((uint32_t)0xFFFFFFFF) /* Memory Address */

/******************  Bit definition for DMA_MADDR3 register  *******************/
#define DMA_MADDR3_MA ((uint32_t)0xFFFFFFFF) /* Memory Address */

/******************  Bit definition for DMA_MADDR4 register  *******************/
#define DMA_MADDR4_MA ((uint32_t)0xFFFFFFFF) /* Memory Address */

/******************  Bit definition for DMA_MADDR5 register  *******************/
#define DMA_MADDR5_MA ((uint32_t)0xFFFFFFFF) /* Memory Address */

/******************  Bit definition for DMA_MADDR6 register  *******************/
#define DMA_MADDR6_MA ((uint32_t)0xFFFFFFFF) /* Memory Address */

/******************  Bit definition for DMA_MADDR7 register  *******************/
#define DMA_MADDR7_MA ((uint32_t)0xFFFFFFFF) /* Memory Address */

/* DMA_data_transfer_direction */
#define DMA_DIR_PERIPHERALDST ((uint32_t)0x00000010)
#define DMA_DIR_PERIPHERALSRC ((uint32_t)0x00000000)

/* DMA_peripheral_incremented_mode */
#define DMA_PERIPHERALINC_ENABLE  ((uint32_t)0x00000040)
#define DMA_PERIPHERALINC_DISABLE ((uint32_t)0x00000000)

/* DMA_memory_incremented_mode */
#define DMA_MEMORYINC_ENABLE  ((uint32_t)0x00000080)
#define DMA_MEMORYINC_DISABLE ((uint32_t)0x00000000)

/* DMA_peripheral_data_size */
#define DMA_PERIPHERAL_DATASIZE_BYTE     ((uint32_t)0x00000000)
#define DMA_PERIPHERAL_DATASIZE_HALFWORD ((uint32_t)0x00000100)
#define DMA_PERIPHERAL_DATASIZE_WORD     ((uint32_t)0x00000200)

/* DMA_memory_data_size */
#define DMA_MEMORY_DATASIZE_BYTE     ((uint32_t)0x00000000)
#define DMA_MEMORY_DATASIZE_HALFWORD ((uint32_t)0x00000400)
#define DMA_MEMORY_DATASIZE_WORD     ((uint32_t)0x00000800)

/* DMA_circular_normal_mode */
#define DMA_MODE_CIRCULAR ((uint32_t)0x00000020)
#define DMA_MODE_NORMAL   ((uint32_t)0x00000000)

/* DMA_priority_level */
#define DMA_PRIORITY_VERYHIGH ((uint32_t)0x00003000)
#define DMA_PRIORITY_HIGH     ((uint32_t)0x00002000)
#define DMA_PRIORITY_MEDIUM   ((uint32_t)0x00001000)
#define DMA_PRIORITY_LOW      ((uint32_t)0x00000000)

/* DMA_memory_to_memory */
#define DMA_M2M_ENABLE  ((uint32_t)0x00004000)
#define DMA_M2M_DISABLE ((uint32_t)0x00000000)

/* DMA_interrupts_definition */
#define DMA_IT_TC ((uint32_t)0x00000002)
#define DMA_IT_HT ((uint32_t)0x00000004)
#define DMA_IT_TE ((uint32_t)0x00000008)

#define DMA1_IT_GL1 ((uint32_t)0x00000001)
#define DMA1_IT_TC1 ((uint32_t)0x00000002)
#define DMA1_IT_HT1 ((uint32_t)0x00000004)
#define DMA1_IT_TE1 ((uint32_t)0x00000008)
#define DMA1_IT_GL2 ((uint32_t)0x00000010)
#define DMA1_IT_TC2 ((uint32_t)0x00000020)
#define DMA1_IT_HT2 ((uint32_t)0x00000040)
#define DMA1_IT_TE2 ((uint32_t)0x00000080)
#define DMA1_IT_GL3 ((uint32_t)0x00000100)
#define DMA1_IT_TC3 ((uint32_t)0x00000200)
#define DMA1_IT_HT3 ((uint32_t)0x00000400)
#define DMA1_IT_TE3 ((uint32_t)0x00000800)
#define DMA1_IT_GL4 ((uint32_t)0x00001000)
#define DMA1_IT_TC4 ((uint32_t)0x00002000)
#define DMA1_IT_HT4 ((uint32_t)0x00004000)
#define DMA1_IT_TE4 ((uint32_t)0x00008000)
#define DMA1_IT_GL5 ((uint32_t)0x00010000)
#define DMA1_IT_TC5 ((uint32_t)0x00020000)
#define DMA1_IT_HT5 ((uint32_t)0x00040000)
#define DMA1_IT_TE5 ((uint32_t)0x00080000)
#define DMA1_IT_GL6 ((uint32_t)0x00100000)
#define DMA1_IT_TC6 ((uint32_t)0x00200000)
#define DMA1_IT_HT6 ((uint32_t)0x00400000)
#define DMA1_IT_TE6 ((uint32_t)0x00800000)
#define DMA1_IT_GL7 ((uint32_t)0x01000000)
#define DMA1_IT_TC7 ((uint32_t)0x02000000)
#define DMA1_IT_HT7 ((uint32_t)0x04000000)
#define DMA1_IT_TE7 ((uint32_t)0x08000000)

/* DMA_flags_definition */
#define DMA1_FLAG_GL1 ((uint32_t)0x00000001)
#define DMA1_FLAG_TC1 ((uint32_t)0x00000002)
#define DMA1_FLAG_HT1 ((uint32_t)0x00000004)
#define DMA1_FLAG_TE1 ((uint32_t)0x00000008)
#define DMA1_FLAG_GL2 ((uint32_t)0x00000010)
#define DMA1_FLAG_TC2 ((uint32_t)0x00000020)
#define DMA1_FLAG_HT2 ((uint32_t)0x00000040)
#define DMA1_FLAG_TE2 ((uint32_t)0x00000080)
#define DMA1_FLAG_GL3 ((uint32_t)0x00000100)
#define DMA1_FLAG_TC3 ((uint32_t)0x00000200)
#define DMA1_FLAG_HT3 ((uint32_t)0x00000400)
#define DMA1_FLAG_TE3 ((uint32_t)0x00000800)
#define DMA1_FLAG_GL4 ((uint32_t)0x00001000)
#define DMA1_FLAG_TC4 ((uint32_t)0x00002000)
#define DMA1_FLAG_HT4 ((uint32_t)0x00004000)
#define DMA1_FLAG_TE4 ((uint32_t)0x00008000)
#define DMA1_FLAG_GL5 ((uint32_t)0x00010000)
#define DMA1_FLAG_TC5 ((uint32_t)0x00020000)
#define DMA1_FLAG_HT5 ((uint32_t)0x00040000)
#define DMA1_FLAG_TE5 ((uint32_t)0x00080000)
#define DMA1_FLAG_GL6 ((uint32_t)0x00100000)
#define DMA1_FLAG_TC6 ((uint32_t)0x00200000)
#define DMA1_FLAG_HT6 ((uint32_t)0x00400000)
#define DMA1_FLAG_TE6 ((uint32_t)0x00800000)
#define DMA1_FLAG_GL7 ((uint32_t)0x01000000)
#define DMA1_FLAG_TC7 ((uint32_t)0x02000000)
#define DMA1_FLAG_HT7 ((uint32_t)0x04000000)
#define DMA1_FLAG_TE7 ((uint32_t)0x08000000)

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
