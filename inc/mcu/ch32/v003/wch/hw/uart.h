#pragma once

#include "wch/hw/def.h"

/******************************************************************************/
/*         Universal Synchronous Asynchronous Receiver Transmitter            */
/******************************************************************************/

#define UART1_BASE  (APB2PERIPH_BASE + 0x3800)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define UART_STATR  0
#define UART_DATAR  4
#define UART_BRR    8
#define UART_CTLR1  12
#define UART_CTLR2  16
#define UART_CTLR3  20
#define UART_GPR    24

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t STATR;  /* UART Status Register                        */
  __IO uint32_t DATAR;  /* UART Data Register                          */
  __IO uint32_t BRR;    /* UART Baud Rate Register                     */
  __IO uint32_t CTLR1;  /* UART Control Register 1                     */
  __IO uint32_t CTLR2;  /* UART Control Register 2                     */
  __IO uint32_t CTLR3;  /* UART Control Register 3                     */
  __IO uint32_t GPR;    /* UART Protection Time and Prescaler Register */
} uart_t;

#define UART1  ((uart_t *)UART1_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/*******************  Bit definition for UART_STATR register  *******************/
#define UART_PE   0x0001 /* Parity Error */
#define UART_FE   0x0002 /* Framing Error */
#define UART_NE   0x0004 /* Noise Error Flag */
#define UART_ORE  0x0008 /* OverRun Error */
#define UART_IDLE 0x0010 /* IDLE line detected */
#define UART_RXNE 0x0020 /* Read Data Register Not Empty */
#define UART_TC   0x0040 /* Transmission Complete */
#define UART_TXE  0x0080 /* Transmit Data Register Empty */
#define UART_LBD  0x0100 /* LIN Break Detection Flag */
#define UART_CTS  0x0200 /* CTS Flag */

/*******************  Bit definition for UART_DATAR register  *******************/
#define UART_DR_MSK 0x01FF /* Data value */

/******************  Bit definition for UART_BRR register  *******************/
#define UART_FRACTION_MSK 0x000F /* Fraction of UARTDIV */
#define UART_MANTISSA_MSK 0xFFF0 /* Mantissa of UARTDIV */

/******************  Bit definition for UART_CTLR1 register  *******************/
#define UART_SBK    0x0001 /* Send Break */
#define UART_RWU    0x0002 /* Receiver wakeup */
#define UART_RXEN   0x0004 /* Receiver Enable */
#define UART_TXEN   0x0008 /* Transmitter Enable */
#define UART_IDLEIE 0x0010 /* IDLE Interrupt Enable */
#define UART_RXNEIE 0x0020 /* RXNE Interrupt Enable */
#define UART_TCIEN  0x0040 /* Transmission Complete Interrupt Enable */
#define UART_TXEIEN 0x0080 /* PE Interrupt Enable */
#define UART_PEIEN  0x0100 /* PE Interrupt Enable */
#define UART_WAKE   0x0800 /* Wakeup method */
#define UART_LEN9B  0x1000 /* Word length */
#define UART_UE     0x2000 /* UART Enable */
#define UART_OVER8  0x8000 /* UART Oversmapling 8-bits */

#define UART_PAR_MSK  0x0600
#define UART_PAR_NO   0x0000
#define UART_PAR_EVEN 0x0400
#define UART_PAR_ODD  0x0600

/******************  Bit definition for UART_CTLR2 register  *******************/
#define UART_ADD_MSK 0x000F /* Address of the UART node */

#define UART_LBDL    0x0020 /* LIN Break Detection Length */
#define UART_LBDIE   0x0040 /* LIN Break Detection Interrupt Enable */
#define UART_LBCL    0x0100 /* Last Bit Clock pulse */
#define UART_CPHA    0x0200 /* Clock Phase */
#define UART_CPOL    0x0400 /* Clock Polarity */
#define UART_CLKEN   0x0800 /* Clock Enable */

#define UART_STOP_MSK 0x3000 /* STOP[1:0] bits (STOP bits) */
#define UART_STOP1   0x0000
#define UART_STOP0_5 0x1000
#define UART_STOP2   0x2000
#define UART_STOP1_5 0x3000

#define UART_LINEN 0x4000 /* LIN mode enable */

/******************  Bit definition for UART_CTLR3 register  *******************/
#define UART_EIE   0x0001 /* Error Interrupt Enable */
#define UART_IREN  0x0002 /* IrDA mode Enable */
#define UART_IRLP  0x0004 /* IrDA Low-Power */
#define UART_HDSEL 0x0008 /* Half-Duplex Selection */
#define UART_NACK  0x0010 /* Smartcard NACK enable */
#define UART_SCEN  0x0020 /* Smartcard mode enable */
#define UART_DMARX 0x0040 /* DMA Enable Receiver */
#define UART_DMATX 0x0080 /* DMA Enable Transmitter */
#define UART_RTSE  0x0100 /* RTS Enable */
#define UART_CTSE  0x0200 /* CTS Enable */
#define UART_CTSIE 0x0400 /* CTS Interrupt Enable */
#define UART_1BIT  0x0800 /* One Bit method */

/******************  Bit definition for UART_GPR register  ******************/
#define UART_PSC_MSK 0x00FF /* PSC[7:0] bits (Prescaler value) */
#define UART_GT_MSK  0xFF00 /* GT[15:8] bits (Guard time value) */

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
