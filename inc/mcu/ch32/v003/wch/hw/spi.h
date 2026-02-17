#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                        Serial Peripheral Interface                         */
/******************************************************************************/

#define SPI1_BASE  (APB2PERIPH_BASE + 0x3000)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define SPI_CTLR1   0
#define SPI_CTLR2   4
#define SPI_STATR   8
#define SPI_DATAR   12
#define SPI_CRCR    16
#define SPI_RCRCR   20
#define SPI_TCRCR   24
#define SPI_HSCR    36

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint16_t CTLR1;      /* SPI Control Register 1          */
       uint16_t RESERVED0;
  __IO uint16_t CTLR2;      /* SPI Control Register 1          */
       uint16_t RESERVED1;
  __IO uint16_t STATR;      /* SPI Status Register             */
       uint16_t RESERVED2;
  __IO uint16_t DATAR;      /* SPI Data Register               */
       uint16_t RESERVED3;
  __IO uint16_t CRCR;       /* SPI Polynomial Register         */
       uint16_t RESERVED4;
  __IO uint16_t RCRCR;      /* SPI Receive CRC Register        */
       uint16_t RESERVED5;
  __IO uint16_t TCRCR;      /* SPI Transmit CRC Register       */
       uint16_t RESERVED6;
       uint32_t RESERVED7;
       uint32_t RESERVED8;
  __IO uint16_t HSCR;       /* SPI High-speed control register */
       uint16_t RESERVED9;
} spi_t;

#define SPI1  ((spi_t *)SPI1_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* SPI SPE mask */
#define CTLR1_SPE_SET   ((uint16_t)0x0040)
#define CTLR1_SPE_RESET ((uint16_t)0xFFBF)

/* SPI CRCNext mask */
#define CTLR1_CRCNEXT_SET ((uint16_t)0x1000)

/* SPI CRCEN mask */
#define CTLR1_CRCEN_SET   ((uint16_t)0x2000)
#define CTLR1_CRCEN_RESET ((uint16_t)0xDFFF)

/* SPI SSOE mask */
#define CTLR2_SSOE_SET   ((uint16_t)0x0004)
#define CTLR2_SSOE_RESET ((uint16_t)0xFFFB)

/* SPI registers Masks */
// NOTE:Overloaded Definition
#define SPI_CTLR1_CLEAR_MASK ((uint16_t)0x3040)
#define I2SCFGR_CLEAR_MASK   ((uint16_t)0xF040)

/*******************  Bit definition for SPI_CTLR1 register  ********************/
#define SPI_CTLR1_CPHA ((uint16_t)0x0001) /* Clock Phase */
#define SPI_CTLR1_CPOL ((uint16_t)0x0002) /* Clock Polarity */
#define SPI_CTLR1_MSTR ((uint16_t)0x0004) /* Master Selection */

#define SPI_CTLR1_BR  ((uint16_t)0x0038) /* BR[2:0] bits (Baud Rate Control) */
#define SPI_CTLR1_BR0 ((uint16_t)0x0008) /* Bit 0 */
#define SPI_CTLR1_BR1 ((uint16_t)0x0010) /* Bit 1 */
#define SPI_CTLR1_BR2 ((uint16_t)0x0020) /* Bit 2 */

#define SPI_CTLR1_SPE      ((uint16_t)0x0040) /* SPI Enable */
#define SPI_CTLR1_LSBFIRST ((uint16_t)0x0080)
#define SPI_CTLR1_SSI      ((uint16_t)0x0100) /* Internal slave select */
#define SPI_CTLR1_SSM      ((uint16_t)0x0200) /* Software slave management */
#define SPI_CTLR1_RXONLY   ((uint16_t)0x0400) /* Receive only */
#define SPI_CTLR1_DFF      ((uint16_t)0x0800) /* Data Frame Format */
#define SPI_CTLR1_CRCNEXT  ((uint16_t)0x1000) /* Transmit CRC next */
#define SPI_CTLR1_CRCEN    ((uint16_t)0x2000) /* Hardware CRC calculation enable */
#define SPI_CTLR1_BIDIOE   ((uint16_t)0x4000) /* Output enable in bidirectional mode */
#define SPI_CTLR1_BIDIMODE ((uint16_t)0x8000) /* Bidirectional data mode enable */

/*******************  Bit definition for SPI_CTLR2 register  ********************/
#define SPI_CTLR2_RXDMAEN ((uint8_t)0x01) /* Rx Buffer DMA Enable */
#define SPI_CTLR2_TXDMAEN ((uint8_t)0x02) /* Tx Buffer DMA Enable */
#define SPI_CTLR2_SSOE    ((uint8_t)0x04) /* SS Output Enable */
#define SPI_CTLR2_ERRIE   ((uint8_t)0x20) /* Error Interrupt Enable */
#define SPI_CTLR2_RXNEIE  ((uint8_t)0x40) /* RX buffer Not Empty Interrupt Enable */
#define SPI_CTLR2_TXEIE   ((uint8_t)0x80) /* Tx buffer Empty Interrupt Enable */

/********************  Bit definition for SPI_STATR register  ********************/
#define SPI_STATR_RXNE   ((uint8_t)0x01) /* Receive buffer Not Empty */
#define SPI_STATR_TXE    ((uint8_t)0x02) /* Transmit buffer Empty */
#define SPI_STATR_CHSIDE ((uint8_t)0x04) /* Channel side */
#define SPI_STATR_UDR    ((uint8_t)0x08) /* Underrun flag */
#define SPI_STATR_CRCERR ((uint8_t)0x10) /* CRC Error flag */
#define SPI_STATR_MODF   ((uint8_t)0x20) /* Mode fault */
#define SPI_STATR_OVR    ((uint8_t)0x40) /* Overrun flag */
#define SPI_STATR_BSY    ((uint8_t)0x80) /* Busy flag */

/********************  Bit definition for SPI_DATAR register  ********************/
#define SPI_DATAR_DR ((uint16_t)0xFFFF) /* Data Register */

/*******************  Bit definition for SPI_CRCR register  ******************/
#define SPI_CRCR_CRCPOLY ((uint16_t)0xFFFF) /* CRC polynomial register */

/******************  Bit definition for SPI_RCRCR register  ******************/
#define SPI_RCRCR_RXCRC ((uint16_t)0xFFFF) /* Rx CRC Register */

/******************  Bit definition for SPI_TCRCR register  ******************/
#define SPI_TCRCR_TXCRC ((uint16_t)0xFFFF) /* Tx CRC Register */

/******************  Bit definition for SPI_HSCR register  ******************/
#define SPI_HSCR_HSRXEN ((uint16_t)0x0001)

/* SPI_data_direction */
#define SPI_DIRECTION_2LINES_FULLDUPLEX ((uint16_t)0x0000)
#define SPI_DIRECTION_2LINES_RXONLY     ((uint16_t)0x0400)
#define SPI_DIRECTION_1LINE_RX          ((uint16_t)0x8000)
#define SPI_DIRECTION_1LINE_TX          ((uint16_t)0xC000)

/* SPI_mode */
#define SPI_MODE_MASTER ((uint16_t)0x0104) /* Sets MSTR, as well as SSI, which is required for Master Mode */
#define SPI_MODE_SLAVE  ((uint16_t)0x0000)

/* SPI_data_size */
#define SPI_DATASIZE_16B ((uint16_t)0x0800)
#define SPI_DATASIZE_8B  ((uint16_t)0x0000)

/* SPI_Clock_Polarity */
#define SPI_CPOL_LOW  ((uint16_t)0x0000)
#define SPI_CPOL_HIGH ((uint16_t)0x0002)

/* SPI_Clock_Phase */
#define SPI_CPHA_1EDGE ((uint16_t)0x0000)
#define SPI_CPHA_2EDGE ((uint16_t)0x0001)

/* SPI_Slave_Select_management */
#define SPI_NSS_SOFT ((uint16_t)0x0200)
#define SPI_NSS_HARD ((uint16_t)0x0000)

/* SPI_BaudRate_Prescaler */
#define SPI_BAUDRATE_PRESCALER2   ((uint16_t)0x0000)
#define SPI_BAUDRATE_PRESCALER4   ((uint16_t)0x0008)
#define SPI_BAUDRATE_PRESCALER8   ((uint16_t)0x0010)
#define SPI_BAUDRATE_PRESCALER16  ((uint16_t)0x0018)
#define SPI_BAUDRATE_PRESCALER32  ((uint16_t)0x0020)
#define SPI_BAUDRATE_PRESCALER64  ((uint16_t)0x0028)
#define SPI_BAUDRATE_PRESCALER128 ((uint16_t)0x0030)
#define SPI_BAUDRATE_PRESCALER256 ((uint16_t)0x0038)

/* SPI_MSB transmission */
#define SPI_FIRSTBIT_MSB ((uint16_t)0x0000)

/* SPI_I2S_DMA_transfer_requests */
#define SPI_I2S_DMAREQ_TX ((uint16_t)0x0002)
#define SPI_I2S_DMAREQ_RX ((uint16_t)0x0001)

/* SPI_NSS_internal_software_management */
#define SPI_NSSINTERNALSOFT_SET   ((uint16_t)0x0100)
#define SPI_NSSINTERNALSOFT_RESET ((uint16_t)0xFEFF)

/* SPI_CRC_Transmit_Receive */
#define SPI_CRC_TX ((uint8_t)0x00)
#define SPI_CRC_RX ((uint8_t)0x01)

/* SPI_direction_transmit_receive */
#define SPI_DIRECTION_RX ((uint16_t)0xBFFF)
#define SPI_DIRECTION_TX ((uint16_t)0x4000)

/* SPI_I2S_interrupts_definition */
#define SPI_I2S_IT_TXE  ((uint8_t)0x71)
#define SPI_I2S_IT_RXNE ((uint8_t)0x60)
#define SPI_I2S_IT_ERR  ((uint8_t)0x50)
#define SPI_I2S_IT_OVR  ((uint8_t)0x56)
#define SPI_IT_MODF     ((uint8_t)0x55)
#define SPI_IT_CRCERR   ((uint8_t)0x54)
#define I2S_IT_UDR      ((uint8_t)0x53)

/* SPI_I2S_flags_definition */
#define SPI_I2S_FLAG_RXNE ((uint16_t)0x0001)
#define SPI_I2S_FLAG_TXE  ((uint16_t)0x0002)
#define I2S_FLAG_CHSIDE   ((uint16_t)0x0004)
#define I2S_FLAG_UDR      ((uint16_t)0x0008)
#define SPI_FLAG_CRCERR   ((uint16_t)0x0010)
#define SPI_FLAG_MODF     ((uint16_t)0x0020)
#define SPI_I2S_FLAG_OVR  ((uint16_t)0x0040)
#define SPI_I2S_FLAG_BSY  ((uint16_t)0x0080)

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
