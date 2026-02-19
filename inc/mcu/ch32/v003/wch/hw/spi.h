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
#define CTLR1_SPE_SET   0x0040
#define CTLR1_SPE_RESET 0xFFBF

/* SPI CRCNext mask */
#define CTLR1_CRCNEXT_SET 0x1000

/* SPI CRCEN mask */
#define CTLR1_CRCEN_SET   0x2000
#define CTLR1_CRCEN_RESET 0xDFFF

/* SPI SSOE mask */
#define CTLR2_SSOE_SET   0x0004
#define CTLR2_SSOE_RESET 0xFFFB

/* SPI registers Masks */
// NOTE:Overloaded Definition
#define SPI_CTLR1_CLEAR_MSK 0x3040
#define I2SCFGR_CLEAR_MSK   0xF040

/*******************  Bit definition for SPI_CTLR1 register  ********************/
#define SPI_CTLR1_CPHA 0x0001 /* Clock Phase */
#define SPI_CTLR1_CPOL 0x0002 /* Clock Polarity */
#define SPI_CTLR1_MSTR 0x0004 /* Master Selection */

#define SPI_CTLR1_BR  0x0038 /* BR[2:0] bits (Baud Rate Control) */
#define SPI_CTLR1_BR0 0x0008 /* Bit 0 */
#define SPI_CTLR1_BR1 0x0010 /* Bit 1 */
#define SPI_CTLR1_BR2 0x0020 /* Bit 2 */

#define SPI_CTLR1_SPE      0x0040 /* SPI Enable */
#define SPI_CTLR1_LSBFIRST 0x0080
#define SPI_CTLR1_SSI      0x0100 /* Internal slave select */
#define SPI_CTLR1_SSM      0x0200 /* Software slave management */
#define SPI_CTLR1_RXONLY   0x0400 /* Receive only */
#define SPI_CTLR1_DFF      0x0800 /* Data Frame Format */
#define SPI_CTLR1_CRCNEXT  0x1000 /* Transmit CRC next */
#define SPI_CTLR1_CRCEN    0x2000 /* Hardware CRC calculation enable */
#define SPI_CTLR1_BIDIOE   0x4000 /* Output enable in bidirectional mode */
#define SPI_CTLR1_BIDIMODE 0x8000 /* Bidirectional data mode enable */

/*******************  Bit definition for SPI_CTLR2 register  ********************/
#define SPI_CTLR2_RXDMAEN 0x01 /* Rx Buffer DMA Enable */
#define SPI_CTLR2_TXDMAEN 0x02 /* Tx Buffer DMA Enable */
#define SPI_CTLR2_SSOE    0x04 /* SS Output Enable */
#define SPI_CTLR2_ERRIE   0x20 /* Error Interrupt Enable */
#define SPI_CTLR2_RXNEIE  0x40 /* RX buffer Not Empty Interrupt Enable */
#define SPI_CTLR2_TXEIE   0x80 /* Tx buffer Empty Interrupt Enable */

/********************  Bit definition for SPI_STATR register  ********************/
#define SPI_STATR_RXNE   0x01 /* Receive buffer Not Empty */
#define SPI_STATR_TXE    0x02 /* Transmit buffer Empty */
#define SPI_STATR_CHSIDE 0x04 /* Channel side */
#define SPI_STATR_UDR    0x08 /* Underrun flag */
#define SPI_STATR_CRCERR 0x10 /* CRC Error flag */
#define SPI_STATR_MODF   0x20 /* Mode fault */
#define SPI_STATR_OVR    0x40 /* Overrun flag */
#define SPI_STATR_BSY    0x80 /* Busy flag */

/********************  Bit definition for SPI_DATAR register  ********************/
#define SPI_DATAR_DR 0xFFFF /* Data Register */

/*******************  Bit definition for SPI_CRCR register  ******************/
#define SPI_CRCR_CRCPOLY 0xFFFF /* CRC polynomial register */

/******************  Bit definition for SPI_RCRCR register  ******************/
#define SPI_RCRCR_RXCRC 0xFFFF /* Rx CRC Register */

/******************  Bit definition for SPI_TCRCR register  ******************/
#define SPI_TCRCR_TXCRC 0xFFFF /* Tx CRC Register */

/******************  Bit definition for SPI_HSCR register  ******************/
#define SPI_HSCR_HSRXEN 0x0001

/* SPI_data_direction */
#define SPI_DIRECTION_2LINES_FULLDUPLEX 0x0000
#define SPI_DIRECTION_2LINES_RXONLY     0x0400
#define SPI_DIRECTION_1LINE_RX          0x8000
#define SPI_DIRECTION_1LINE_TX          0xC000

/* SPI_mode */
#define SPI_MODE_MASTER 0x0104 /* Sets MSTR, as well as SSI, which is required for Master Mode */
#define SPI_MODE_SLAVE  0x0000

/* SPI_data_size */
#define SPI_DATASIZE_16B 0x0800
#define SPI_DATASIZE_8B  0x0000

/* SPI_Clock_Polarity */
#define SPI_CPOL_LOW  0x0000
#define SPI_CPOL_HIGH 0x0002

/* SPI_Clock_Phase */
#define SPI_CPHA_1EDGE 0x0000
#define SPI_CPHA_2EDGE 0x0001

/* SPI_Slave_Select_management */
#define SPI_NSS_SOFT 0x0200
#define SPI_NSS_HARD 0x0000

/* SPI_BaudRate_Prescaler */
#define SPI_BAUDRATE_PRESCALER2   0x0000
#define SPI_BAUDRATE_PRESCALER4   0x0008
#define SPI_BAUDRATE_PRESCALER8   0x0010
#define SPI_BAUDRATE_PRESCALER16  0x0018
#define SPI_BAUDRATE_PRESCALER32  0x0020
#define SPI_BAUDRATE_PRESCALER64  0x0028
#define SPI_BAUDRATE_PRESCALER128 0x0030
#define SPI_BAUDRATE_PRESCALER256 0x0038

/* SPI_MSB transmission */
#define SPI_FIRSTBIT_MSB 0x0000

/* SPI_I2S_DMA_transfer_requests */
#define SPI_I2S_DMAREQ_TX 0x0002
#define SPI_I2S_DMAREQ_RX 0x0001

/* SPI_NSS_internal_software_management */
#define SPI_NSSINTERNALSOFT_SET   0x0100
#define SPI_NSSINTERNALSOFT_RESET 0xFEFF

/* SPI_CRC_Transmit_Receive */
#define SPI_CRC_TX 0x00
#define SPI_CRC_RX 0x01

/* SPI_direction_transmit_receive */
#define SPI_DIRECTION_RX 0xBFFF
#define SPI_DIRECTION_TX 0x4000

/* SPI_I2S_interrupts_definition */
#define SPI_I2S_IT_TXE  0x71
#define SPI_I2S_IT_RXNE 0x60
#define SPI_I2S_IT_ERR  0x50
#define SPI_I2S_IT_OVR  0x56
#define SPI_IT_MODF     0x55
#define SPI_IT_CRCERR   0x54
#define I2S_IT_UDR      0x53

/* SPI_I2S_flags_definition */
#define SPI_I2S_FLAG_RXNE 0x0001
#define SPI_I2S_FLAG_TXE  0x0002
#define I2S_FLAG_CHSIDE   0x0004
#define I2S_FLAG_UDR      0x0008
#define SPI_FLAG_CRCERR   0x0010
#define SPI_FLAG_MODF     0x0020
#define SPI_I2S_FLAG_OVR  0x0040
#define SPI_I2S_FLAG_BSY  0x0080

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
