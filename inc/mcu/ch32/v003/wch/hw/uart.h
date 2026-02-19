#pragma once

#include "wch/hw/base.h"
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

/* UART_Interrupt_definition */
#define UART_IT_PE     0x0028
#define UART_IT_FE     0x0160
#define UART_IT_NE     0x0260
#define UART_IT_ORE_RX 0x0325
#define UART_IT_ORE_ER 0x0360
#define UART_IT_TC     0x0626
#define UART_IT_TXE    0x0727
#define UART_IT_RXNE   0x0525
#define UART_IT_LBD    0x0846
#define UART_IT_CTS    0x096A
#define UART_IT_IDLE   0x0424
#define UART_IT_ERR    0x0060

/*******************  Bit definition for UART_STATR register  *******************/
#define UART_STATR_PE   0x0001 /* Parity Error */
#define UART_STATR_FE   0x0002 /* Framing Error */
#define UART_STATR_NE   0x0004 /* Noise Error Flag */
#define UART_STATR_ORE  0x0008 /* OverRun Error */
#define UART_STATR_IDLE 0x0010 /* IDLE line detected */
#define UART_STATR_RXNE 0x0020 /* Read Data Register Not Empty */
#define UART_STATR_TC   0x0040 /* Transmission Complete */
#define UART_STATR_TXE  0x0080 /* Transmit Data Register Empty */
#define UART_STATR_LBD  0x0100 /* LIN Break Detection Flag */
#define UART_STATR_CTS  0x0200 /* CTS Flag */

/*******************  Bit definition for UART_DATAR register  *******************/
#define UART_DATAR_DR_MSK 0x01FF /* Data value */

/******************  Bit definition for UART_BRR register  *******************/
#define UART_BRR_FRACTION_MSK 0x000F /* Fraction of UARTDIV */
#define UART_BRR_MANTISSA_MSK 0xFFF0 /* Mantissa of UARTDIV */

/******************  Bit definition for UART_CTLR1 register  *******************/
#define UART_CTLR1_SBK    0x0001 /* Send Break */
#define UART_CTLR1_RWU    0x0002 /* Receiver wakeup */
#define UART_CTLR1_RXE    0x0004 /* Receiver Enable */
#define UART_CTLR1_TXE    0x0008 /* Transmitter Enable */
#define UART_CTLR1_IDLEIE 0x0010 /* IDLE Interrupt Enable */
#define UART_CTLR1_RXNEIE 0x0020 /* RXNE Interrupt Enable */
#define UART_CTLR1_TCIE   0x0040 /* Transmission Complete Interrupt Enable */
#define UART_CTLR1_TXEIE  0x0080 /* PE Interrupt Enable */
#define UART_CTLR1_PEIE   0x0100 /* PE Interrupt Enable */
#define UART_CTLR1_WAKE   0x0800 /* Wakeup method */
#define UART_CTLR1_LEN9B  0x1000 /* Word length */
#define UART_CTLR1_UE     0x2000 /* UART Enable */
#define UART_CTLR1_OVER8  0x8000 /* UART Oversmapling 8-bits */

#define UART_PARITY_MSK  0x0600
#define UART_PARITY_NO   0x0000
#define UART_PARITY_EVEN 0x0400
#define UART_PARITY_ODD  0x0600

/******************  Bit definition for UART_CTLR2 register  *******************/
#define UART_CTLR2_ADD_MSK 0x000F /* Address of the UART node */
#define UART_CTLR2_LBDL    0x0020 /* LIN Break Detection Length */
#define UART_CTLR2_LBDIE   0x0040 /* LIN Break Detection Interrupt Enable */
#define UART_CTLR2_LBCL    0x0100 /* Last Bit Clock pulse */
#define UART_CTLR2_CPHA    0x0200 /* Clock Phase */
#define UART_CTLR2_CPOL    0x0400 /* Clock Polarity */
#define UART_CTLR2_CLKEN   0x0800 /* Clock Enable */

#define UART_CTLR2_STOP_MSK 0x3000 /* STOP[1:0] bits (STOP bits) */
#define UART_STOPBITS1   0x0000
#define UART_STOPBITS0_5 0x1000
#define UART_STOPBITS2   0x2000
#define UART_STOPBITS1_5 0x3000

#define UART_CTLR2_LINEN 0x4000 /* LIN mode enable */

/******************  Bit definition for UART_CTLR3 register  *******************/
#define UART_CTLR3_EIE    0x0001 /* Error Interrupt Enable */
#define UART_CTLR3_IREN   0x0002 /* IrDA mode Enable */
#define UART_CTLR3_IRLP   0x0004 /* IrDA Low-Power */
#define UART_CTLR3_HDSEL  0x0008 /* Half-Duplex Selection */
#define UART_CTLR3_NACK   0x0010 /* Smartcard NACK enable */
#define UART_CTLR3_SCEN   0x0020 /* Smartcard mode enable */
#define UART_CTLR3_DMARX  0x0040 /* DMA Enable Receiver */
#define UART_CTLR3_DMATX  0x0080 /* DMA Enable Transmitter */
#define UART_CTLR3_RTSE   0x0100 /* RTS Enable */
#define UART_CTLR3_CTSE   0x0200 /* CTS Enable */
#define UART_CTLR3_CTSIE  0x0400 /* CTS Interrupt Enable */
#define UART_CTLR3_ONEBIT 0x0800 /* One Bit method */

/******************  Bit definition for UART_GPR register  ******************/
#define UART_GPR_PSC_MSK 0x00FF /* PSC[7:0] bits (Prescaler value) */
#define UART_GPR_PSC0 0x0001 /* Bit 0 */
#define UART_GPR_PSC1 0x0002 /* Bit 1 */
#define UART_GPR_PSC2 0x0004 /* Bit 2 */
#define UART_GPR_PSC3 0x0008 /* Bit 3 */
#define UART_GPR_PSC4 0x0010 /* Bit 4 */
#define UART_GPR_PSC5 0x0020 /* Bit 5 */
#define UART_GPR_PSC6 0x0040 /* Bit 6 */
#define UART_GPR_PSC7 0x0080 /* Bit 7 */

#define UART_GPR_GT_MSK 0xFF00 /* Guard time value */

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
