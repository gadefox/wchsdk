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

/* UART_Private_Defines */
#define CTLR1_UE_SET   ((uint16_t)0x2000) /* UART Enable Mask */
#define CTLR1_UE_RESET ((uint16_t)0xDFFF) /* UART Disable Mask */

#define CTLR1_WAKE_MASK ((uint16_t)0xF7FF) /* UART WakeUp Method Mask */

#define CTLR1_RWU_SET   ((uint16_t)0x0002) /* UART mute mode Enable Mask */
#define CTLR1_RWU_RESET ((uint16_t)0xFFFD) /* UART mute mode Enable Mask */
#define CTLR1_SBK_SET   ((uint16_t)0x0001) /* UART Break Character send Mask */

// NOTE:Overloaded Definition
#define UART_CTLR1_CLEAR_MASK ((uint16_t)0xE9F3) /* UART CR1 Mask */
#define CTLR2_ADDRESS_MASK     ((uint16_t)0xFFF0) /* UART address Mask */

#define CTLR2_LINEN_SET   ((uint16_t)0x4000) /* UART LIN Enable Mask */
#define CTLR2_LINEN_RESET ((uint16_t)0xBFFF) /* UART LIN Disable Mask */

#define CTLR2_LBDL_MASK        ((uint16_t)0xFFDF) /* UART LIN Break detection Mask */
#define CTLR2_STOP_CLEAR_MASK  ((uint16_t)0xCFFF) /* UART CR2 STOP Bits Mask */
#define CTLR2_CLOCK_CLEAR_MASK ((uint16_t)0xF0FF) /* UART CR2 Clock Mask */

#define CTLR3_SCEN_SET   ((uint16_t)0x0020) /* UART SC Enable Mask */
#define CTLR3_SCEN_RESET ((uint16_t)0xFFDF) /* UART SC Disable Mask */

#define CTLR3_NACK_SET   ((uint16_t)0x0010) /* UART SC NACK Enable Mask */
#define CTLR3_NACK_RESET ((uint16_t)0xFFEF) /* UART SC NACK Disable Mask */

#define CTLR3_HDSEL_SET   ((uint16_t)0x0008) /* UART Half-Duplex Enable Mask */
#define CTLR3_HDSEL_RESET ((uint16_t)0xFFF7) /* UART Half-Duplex Disable Mask */

#define CTLR3_IRLP_MASK  ((uint16_t)0xFFFB) /* UART IrDA LowPower mode Mask */
#define CTLR3_CLEAR_MASK ((uint16_t)0xFCFF) /* UART CR3 Mask */

#define CTLR3_IREN_SET   ((uint16_t)0x0002) /* UART IrDA Enable Mask */
#define CTLR3_IREN_RESET ((uint16_t)0xFFFD) /* UART IrDA Disable Mask */
#define GPR_LSB_MASK     ((uint16_t)0x00FF) /* Guard Time Register LSB Mask */
#define GPR_MSB_MASK     ((uint16_t)0xFF00) /* Guard Time Register MSB Mask */
#define IT_MASK          ((uint16_t)0x001F) /* UART Interrupt Mask */

/* UART OverSampling-8 Mask */
#define CTLR1_OVER8_SET   ((uint16_t)0x8000) /* UART OVER8 mode Enable Mask */
#define CTLR1_OVER8_RESET ((uint16_t)0x7FFF) /* UART OVER8 mode Disable Mask */

/* UART One Bit Sampling Mask */
#define CTLR3_ONEBITE_SET   ((uint16_t)0x0800) /* UART ONEBITE mode Enable Mask */
#define CTLR3_ONEBITE_RESET ((uint16_t)0xF7FF) /* UART ONEBITE mode Disable Mask */

/*******************  Bit definition for UART_STATR register  *******************/
#define UART_STATR_PE   ((uint16_t)0x0001) /* Parity Error */
#define UART_STATR_FE   ((uint16_t)0x0002) /* Framing Error */
#define UART_STATR_NE   ((uint16_t)0x0004) /* Noise Error Flag */
#define UART_STATR_ORE  ((uint16_t)0x0008) /* OverRun Error */
#define UART_STATR_IDLE ((uint16_t)0x0010) /* IDLE line detected */
#define UART_STATR_RXNE ((uint16_t)0x0020) /* Read Data Register Not Empty */
#define UART_STATR_TC   ((uint16_t)0x0040) /* Transmission Complete */
#define UART_STATR_TXE  ((uint16_t)0x0080) /* Transmit Data Register Empty */
#define UART_STATR_LBD  ((uint16_t)0x0100) /* LIN Break Detection Flag */
#define UART_STATR_CTS  ((uint16_t)0x0200) /* CTS Flag */

/*******************  Bit definition for UART_DATAR register  *******************/
#define UART_DATAR_DR ((uint16_t)0x01FF) /* Data value */

/******************  Bit definition for UART_BRR register  *******************/
#define UART_BRR_DIV_Fraction ((uint16_t)0x000F) /* Fraction of UARTDIV */
#define UART_BRR_DIV_Mantissa ((uint16_t)0xFFF0) /* Mantissa of UARTDIV */

/******************  Bit definition for UART_CTLR1 register  *******************/
#define UART_CTLR1_SBK    ((uint16_t)0x0001) /* Send Break */
#define UART_CTLR1_RWU    ((uint16_t)0x0002) /* Receiver wakeup */
#define UART_CTLR1_RE     ((uint16_t)0x0004) /* Receiver Enable */
#define UART_CTLR1_TE     ((uint16_t)0x0008) /* Transmitter Enable */
#define UART_CTLR1_IDLEIE ((uint16_t)0x0010) /* IDLE Interrupt Enable */
#define UART_CTLR1_RXNEIE ((uint16_t)0x0020) /* RXNE Interrupt Enable */
#define UART_CTLR1_TCIE   ((uint16_t)0x0040) /* Transmission Complete Interrupt Enable */
#define UART_CTLR1_TXEIE  ((uint16_t)0x0080) /* PE Interrupt Enable */
#define UART_CTLR1_PEIE   ((uint16_t)0x0100) /* PE Interrupt Enable */
#define UART_CTLR1_PS     ((uint16_t)0x0200) /* Parity Selection */
#define UART_CTLR1_PCE    ((uint16_t)0x0400) /* Parity Control Enable */
#define UART_CTLR1_WAKE   ((uint16_t)0x0800) /* Wakeup method */
#define UART_CTLR1_M      ((uint16_t)0x1000) /* Word length */
#define UART_CTLR1_UE     ((uint16_t)0x2000) /* UART Enable */
#define UART_CTLR1_OVER8  ((uint16_t)0x8000) /* UART Oversmapling 8-bits */

/******************  Bit definition for UART_CTLR2 register  *******************/
#define UART_CTLR2_ADD   ((uint16_t)0x000F) /* Address of the UART node */
#define UART_CTLR2_LBDL  ((uint16_t)0x0020) /* LIN Break Detection Length */
#define UART_CTLR2_LBDIE ((uint16_t)0x0040) /* LIN Break Detection Interrupt Enable */
#define UART_CTLR2_LBCL  ((uint16_t)0x0100) /* Last Bit Clock pulse */
#define UART_CTLR2_CPHA  ((uint16_t)0x0200) /* Clock Phase */
#define UART_CTLR2_CPOL  ((uint16_t)0x0400) /* Clock Polarity */
#define UART_CTLR2_CLKEN ((uint16_t)0x0800) /* Clock Enable */

#define UART_CTLR2_STOP  ((uint16_t)0x3000) /* STOP[1:0] bits (STOP bits) */
#define UART_CTLR2_STOP0 ((uint16_t)0x1000) /* Bit 0 */
#define UART_CTLR2_STOP1 ((uint16_t)0x2000) /* Bit 1 */

#define UART_CTLR2_LINEN ((uint16_t)0x4000) /* LIN mode enable */

/******************  Bit definition for UART_CTLR3 register  *******************/
#define UART_CTLR3_EIE    ((uint16_t)0x0001) /* Error Interrupt Enable */
#define UART_CTLR3_IREN   ((uint16_t)0x0002) /* IrDA mode Enable */
#define UART_CTLR3_IRLP   ((uint16_t)0x0004) /* IrDA Low-Power */
#define UART_CTLR3_HDSEL  ((uint16_t)0x0008) /* Half-Duplex Selection */
#define UART_CTLR3_NACK   ((uint16_t)0x0010) /* Smartcard NACK enable */
#define UART_CTLR3_SCEN   ((uint16_t)0x0020) /* Smartcard mode enable */
#define UART_CTLR3_DMAR   ((uint16_t)0x0040) /* DMA Enable Receiver */
#define UART_CTLR3_DMAT   ((uint16_t)0x0080) /* DMA Enable Transmitter */
#define UART_CTLR3_RTSE   ((uint16_t)0x0100) /* RTS Enable */
#define UART_CTLR3_CTSE   ((uint16_t)0x0200) /* CTS Enable */
#define UART_CTLR3_CTSIE  ((uint16_t)0x0400) /* CTS Interrupt Enable */
#define UART_CTLR3_ONEBIT ((uint16_t)0x0800) /* One Bit method */

/******************  Bit definition for UART_GPR register  ******************/
#define UART_GPR_PSC  ((uint16_t)0x00FF) /* PSC[7:0] bits (Prescaler value) */
#define UART_GPR_PSC0 ((uint16_t)0x0001) /* Bit 0 */
#define UART_GPR_PSC1 ((uint16_t)0x0002) /* Bit 1 */
#define UART_GPR_PSC2 ((uint16_t)0x0004) /* Bit 2 */
#define UART_GPR_PSC3 ((uint16_t)0x0008) /* Bit 3 */
#define UART_GPR_PSC4 ((uint16_t)0x0010) /* Bit 4 */
#define UART_GPR_PSC5 ((uint16_t)0x0020) /* Bit 5 */
#define UART_GPR_PSC6 ((uint16_t)0x0040) /* Bit 6 */
#define UART_GPR_PSC7 ((uint16_t)0x0080) /* Bit 7 */

#define UART_GPR_GT ((uint16_t)0xFF00) /* Guard time value */

/* UART_Word_Length */
#define UART_WORDLENGTH_8B ((uint16_t)0x0000)
#define UART_WORDLENGTH_9B ((uint16_t)0x1000)

/* UART_Stop_Bits */
#define UART_STOPBITS1   ((uint16_t)0x0000)
#define UART_STOPBITS0_5 ((uint16_t)0x1000)
#define UART_STOPBITS2   ((uint16_t)0x2000)
#define UART_STOPBITS1_5 ((uint16_t)0x3000)

/* UART_Parity */
#define UART_PARITY_NO   ((uint16_t)0x0000)
#define UART_PARITY_EVEN ((uint16_t)0x0400)
#define UART_PARITY_ODD  ((uint16_t)0x0600)

/* UART_Mode */
#define UART_MODE_RX ((uint16_t)0x0004)
#define UART_MODE_TX ((uint16_t)0x0008)

/* UART_Hardware_Flow_Control */
#define UART_HWFLOW_CONTROL_NONE    ((uint16_t)0x0000)
#define UART_HWFLOW_CONTROL_RTS     ((uint16_t)0x0100)
#define UART_HWFLOW_CONTROL_CTS     ((uint16_t)0x0200)
#define UART_HWFLOW_CONTROL_RTS_CTS ((uint16_t)0x0300)

/* UART_Clock */
#define UART_CLOCK_DISABLE ((uint16_t)0x0000)
#define UART_CLOCK_ENABLE  ((uint16_t)0x0800)

/* UART_Clock_Polarity */
#define UART_CPOL_LOW  ((uint16_t)0x0000)
#define UART_CPOL_HIGH ((uint16_t)0x0400)

/* UART_Clock_Phase */
#define UART_CPHA_1EDGE ((uint16_t)0x0000)
#define UART_CPHA_2EDGE ((uint16_t)0x0200)

/* UART_Last_Bit */
#define UART_LASTBIT_DISABLE ((uint16_t)0x0000)
#define UART_LASTBIT_ENABLE  ((uint16_t)0x0100)

/* UART_Interrupt_definition */
#define UART_IT_PE     ((uint16_t)0x0028)
#define UART_IT_TXE    ((uint16_t)0x0727)
#define UART_IT_TC     ((uint16_t)0x0626)
#define UART_IT_RXNE   ((uint16_t)0x0525)
#define UART_IT_ORE_RX ((uint16_t)0x0325)
#define UART_IT_IDLE   ((uint16_t)0x0424)
#define UART_IT_LBD    ((uint16_t)0x0846)
#define UART_IT_CTS    ((uint16_t)0x096A)
#define UART_IT_ERR    ((uint16_t)0x0060)
#define UART_IT_ORE_ER ((uint16_t)0x0360)
#define UART_IT_NE     ((uint16_t)0x0260)
#define UART_IT_FE     ((uint16_t)0x0160)

#define UART_IT_ORE UART_IT_ORE_ER

/* UART_DMA_Requests */
#define UART_DMAREQ_TX ((uint16_t)0x0080)
#define UART_DMAREQ_RX ((uint16_t)0x0040)

/* UART_WakeUp_methods */
#define UART_WAKEUP_IDLE_LINE    ((uint16_t)0x0000)
#define UART_WAKEUP_ADDRESS_MARK ((uint16_t)0x0800)

/* UART_LIN_Break_Detection_Length */
#define UART_LINBREAK_DETECT_LENGTH_10B ((uint16_t)0x0000)
#define UART_LINBREAK_DETECT_LENGTH_11B ((uint16_t)0x0020)

/* UART_IrDA_Low_Power */
#define UART_IRDAMODE_LOWPOWER ((uint16_t)0x0004)
#define UART_IRDAMODE_NORMAL   ((uint16_t)0x0000)

/* UART_Flags */
#define UART_FLAG_CTS  ((uint16_t)0x0200)
#define UART_FLAG_LBD  ((uint16_t)0x0100)
#define UART_FLAG_TXE  ((uint16_t)0x0080)
#define UART_FLAG_TC   ((uint16_t)0x0040)
#define UART_FLAG_RXNE ((uint16_t)0x0020)
#define UART_FLAG_IDLE ((uint16_t)0x0010)
#define UART_FLAG_ORE  ((uint16_t)0x0008)
#define UART_FLAG_NE   ((uint16_t)0x0004)
#define UART_FLAG_FE   ((uint16_t)0x0002)
#define UART_FLAG_PE   ((uint16_t)0x0001)

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
