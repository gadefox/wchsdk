#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*         Universal Synchronous Asynchronous Receiver Transmitter            */
/******************************************************************************/

#define USART1_BASE  (APB2PERIPH_BASE + 0x3800)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define USART_STATR  0
#define USART_DATAR  4
#define USART_BRR    8
#define USART_CTLR1  12
#define USART_CTLR2  16
#define USART_CTLR3  20
#define USART_GPR    24

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t STATR;  /* USART Status Register                        */
  __IO uint32_t DATAR;  /* USART Data Register                          */
  __IO uint32_t BRR;    /* USART Baud Rate Register                     */
  __IO uint32_t CTLR1;  /* USART Control Register 1                     */
  __IO uint32_t CTLR2;  /* USART Control Register 2                     */
  __IO uint32_t CTLR3;  /* USART Control Register 3                     */
  __IO uint32_t GPR;    /* USART Protection Time and Prescaler Register */
} usart_t;

#define USART1  ((usart_t *)USART1_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* USART_Private_Defines */
#define CTLR1_UE_SET   ((uint16_t)0x2000) /* USART Enable Mask */
#define CTLR1_UE_RESET ((uint16_t)0xDFFF) /* USART Disable Mask */

#define CTLR1_WAKE_MASK ((uint16_t)0xF7FF) /* USART WakeUp Method Mask */

#define CTLR1_RWU_SET   ((uint16_t)0x0002) /* USART mute mode Enable Mask */
#define CTLR1_RWU_RESET ((uint16_t)0xFFFD) /* USART mute mode Enable Mask */
#define CTLR1_SBK_SET   ((uint16_t)0x0001) /* USART Break Character send Mask */

// NOTE:Overloaded Definition
#define USART_CTLR1_CLEAR_MASK ((uint16_t)0xE9F3) /* USART CR1 Mask */
#define CTLR2_ADDRESS_MASK     ((uint16_t)0xFFF0) /* USART address Mask */

#define CTLR2_LINEN_SET   ((uint16_t)0x4000) /* USART LIN Enable Mask */
#define CTLR2_LINEN_RESET ((uint16_t)0xBFFF) /* USART LIN Disable Mask */

#define CTLR2_LBDL_MASK        ((uint16_t)0xFFDF) /* USART LIN Break detection Mask */
#define CTLR2_STOP_CLEAR_MASK  ((uint16_t)0xCFFF) /* USART CR2 STOP Bits Mask */
#define CTLR2_CLOCK_CLEAR_MASK ((uint16_t)0xF0FF) /* USART CR2 Clock Mask */

#define CTLR3_SCEN_SET   ((uint16_t)0x0020) /* USART SC Enable Mask */
#define CTLR3_SCEN_RESET ((uint16_t)0xFFDF) /* USART SC Disable Mask */

#define CTLR3_NACK_SET   ((uint16_t)0x0010) /* USART SC NACK Enable Mask */
#define CTLR3_NACK_RESET ((uint16_t)0xFFEF) /* USART SC NACK Disable Mask */

#define CTLR3_HDSEL_SET   ((uint16_t)0x0008) /* USART Half-Duplex Enable Mask */
#define CTLR3_HDSEL_RESET ((uint16_t)0xFFF7) /* USART Half-Duplex Disable Mask */

#define CTLR3_IRLP_MASK  ((uint16_t)0xFFFB) /* USART IrDA LowPower mode Mask */
#define CTLR3_CLEAR_MASK ((uint16_t)0xFCFF) /* USART CR3 Mask */

#define CTLR3_IREN_SET   ((uint16_t)0x0002) /* USART IrDA Enable Mask */
#define CTLR3_IREN_RESET ((uint16_t)0xFFFD) /* USART IrDA Disable Mask */
#define GPR_LSB_MASK     ((uint16_t)0x00FF) /* Guard Time Register LSB Mask */
#define GPR_MSB_MASK     ((uint16_t)0xFF00) /* Guard Time Register MSB Mask */
#define IT_MASK          ((uint16_t)0x001F) /* USART Interrupt Mask */

/* USART OverSampling-8 Mask */
#define CTLR1_OVER8_SET   ((uint16_t)0x8000) /* USART OVER8 mode Enable Mask */
#define CTLR1_OVER8_RESET ((uint16_t)0x7FFF) /* USART OVER8 mode Disable Mask */

/* USART One Bit Sampling Mask */
#define CTLR3_ONEBITE_SET   ((uint16_t)0x0800) /* USART ONEBITE mode Enable Mask */
#define CTLR3_ONEBITE_RESET ((uint16_t)0xF7FF) /* USART ONEBITE mode Disable Mask */

/*******************  Bit definition for USART_STATR register  *******************/
#define USART_STATR_PE   ((uint16_t)0x0001) /* Parity Error */
#define USART_STATR_FE   ((uint16_t)0x0002) /* Framing Error */
#define USART_STATR_NE   ((uint16_t)0x0004) /* Noise Error Flag */
#define USART_STATR_ORE  ((uint16_t)0x0008) /* OverRun Error */
#define USART_STATR_IDLE ((uint16_t)0x0010) /* IDLE line detected */
#define USART_STATR_RXNE ((uint16_t)0x0020) /* Read Data Register Not Empty */
#define USART_STATR_TC   ((uint16_t)0x0040) /* Transmission Complete */
#define USART_STATR_TXE  ((uint16_t)0x0080) /* Transmit Data Register Empty */
#define USART_STATR_LBD  ((uint16_t)0x0100) /* LIN Break Detection Flag */
#define USART_STATR_CTS  ((uint16_t)0x0200) /* CTS Flag */

/*******************  Bit definition for USART_DATAR register  *******************/
#define USART_DATAR_DR ((uint16_t)0x01FF) /* Data value */

/******************  Bit definition for USART_BRR register  *******************/
#define USART_BRR_DIV_Fraction ((uint16_t)0x000F) /* Fraction of USARTDIV */
#define USART_BRR_DIV_Mantissa ((uint16_t)0xFFF0) /* Mantissa of USARTDIV */

/******************  Bit definition for USART_CTLR1 register  *******************/
#define USART_CTLR1_SBK    ((uint16_t)0x0001) /* Send Break */
#define USART_CTLR1_RWU    ((uint16_t)0x0002) /* Receiver wakeup */
#define USART_CTLR1_RE     ((uint16_t)0x0004) /* Receiver Enable */
#define USART_CTLR1_TE     ((uint16_t)0x0008) /* Transmitter Enable */
#define USART_CTLR1_IDLEIE ((uint16_t)0x0010) /* IDLE Interrupt Enable */
#define USART_CTLR1_RXNEIE ((uint16_t)0x0020) /* RXNE Interrupt Enable */
#define USART_CTLR1_TCIE   ((uint16_t)0x0040) /* Transmission Complete Interrupt Enable */
#define USART_CTLR1_TXEIE  ((uint16_t)0x0080) /* PE Interrupt Enable */
#define USART_CTLR1_PEIE   ((uint16_t)0x0100) /* PE Interrupt Enable */
#define USART_CTLR1_PS     ((uint16_t)0x0200) /* Parity Selection */
#define USART_CTLR1_PCE    ((uint16_t)0x0400) /* Parity Control Enable */
#define USART_CTLR1_WAKE   ((uint16_t)0x0800) /* Wakeup method */
#define USART_CTLR1_M      ((uint16_t)0x1000) /* Word length */
#define USART_CTLR1_UE     ((uint16_t)0x2000) /* USART Enable */
#define USART_CTLR1_OVER8  ((uint16_t)0x8000) /* USART Oversmapling 8-bits */

/******************  Bit definition for USART_CTLR2 register  *******************/
#define USART_CTLR2_ADD   ((uint16_t)0x000F) /* Address of the USART node */
#define USART_CTLR2_LBDL  ((uint16_t)0x0020) /* LIN Break Detection Length */
#define USART_CTLR2_LBDIE ((uint16_t)0x0040) /* LIN Break Detection Interrupt Enable */
#define USART_CTLR2_LBCL  ((uint16_t)0x0100) /* Last Bit Clock pulse */
#define USART_CTLR2_CPHA  ((uint16_t)0x0200) /* Clock Phase */
#define USART_CTLR2_CPOL  ((uint16_t)0x0400) /* Clock Polarity */
#define USART_CTLR2_CLKEN ((uint16_t)0x0800) /* Clock Enable */

#define USART_CTLR2_STOP   ((uint16_t)0x3000) /* STOP[1:0] bits (STOP bits) */
#define USART_CTLR2_STOP_0 ((uint16_t)0x1000) /* Bit 0 */
#define USART_CTLR2_STOP_1 ((uint16_t)0x2000) /* Bit 1 */

#define USART_CTLR2_LINEN ((uint16_t)0x4000) /* LIN mode enable */

/******************  Bit definition for USART_CTLR3 register  *******************/
#define USART_CTLR3_EIE    ((uint16_t)0x0001) /* Error Interrupt Enable */
#define USART_CTLR3_IREN   ((uint16_t)0x0002) /* IrDA mode Enable */
#define USART_CTLR3_IRLP   ((uint16_t)0x0004) /* IrDA Low-Power */
#define USART_CTLR3_HDSEL  ((uint16_t)0x0008) /* Half-Duplex Selection */
#define USART_CTLR3_NACK   ((uint16_t)0x0010) /* Smartcard NACK enable */
#define USART_CTLR3_SCEN   ((uint16_t)0x0020) /* Smartcard mode enable */
#define USART_CTLR3_DMAR   ((uint16_t)0x0040) /* DMA Enable Receiver */
#define USART_CTLR3_DMAT   ((uint16_t)0x0080) /* DMA Enable Transmitter */
#define USART_CTLR3_RTSE   ((uint16_t)0x0100) /* RTS Enable */
#define USART_CTLR3_CTSE   ((uint16_t)0x0200) /* CTS Enable */
#define USART_CTLR3_CTSIE  ((uint16_t)0x0400) /* CTS Interrupt Enable */
#define USART_CTLR3_ONEBIT ((uint16_t)0x0800) /* One Bit method */

/******************  Bit definition for USART_GPR register  ******************/
#define USART_GPR_PSC   ((uint16_t)0x00FF) /* PSC[7:0] bits (Prescaler value) */
#define USART_GPR_PSC_0 ((uint16_t)0x0001) /* Bit 0 */
#define USART_GPR_PSC_1 ((uint16_t)0x0002) /* Bit 1 */
#define USART_GPR_PSC_2 ((uint16_t)0x0004) /* Bit 2 */
#define USART_GPR_PSC_3 ((uint16_t)0x0008) /* Bit 3 */
#define USART_GPR_PSC_4 ((uint16_t)0x0010) /* Bit 4 */
#define USART_GPR_PSC_5 ((uint16_t)0x0020) /* Bit 5 */
#define USART_GPR_PSC_6 ((uint16_t)0x0040) /* Bit 6 */
#define USART_GPR_PSC_7 ((uint16_t)0x0080) /* Bit 7 */

#define USART_GPR_GT ((uint16_t)0xFF00) /* Guard time value */

/* USART_Word_Length */
#define USART_WORDLENGTH_8B ((uint16_t)0x0000)
#define USART_WORDLENGTH_9B ((uint16_t)0x1000)

/* USART_Stop_Bits */
#define USART_STOPBITS_1   ((uint16_t)0x0000)
#define USART_STOPBITS_0_5 ((uint16_t)0x1000)
#define USART_STOPBITS_2   ((uint16_t)0x2000)
#define USART_STOPBITS_1_5 ((uint16_t)0x3000)

/* USART_Parity */
#define USART_PARITY_NO   ((uint16_t)0x0000)
#define USART_PARITY_EVEN ((uint16_t)0x0400)
#define USART_PARITY_ODD  ((uint16_t)0x0600)

/* USART_Mode */
#define USART_MODE_RX ((uint16_t)0x0004)
#define USART_MODE_TX ((uint16_t)0x0008)

/* USART_Hardware_Flow_Control */
#define USART_HWFLOW_CONTROL_NONE    ((uint16_t)0x0000)
#define USART_HWFLOW_CONTROL_RTS     ((uint16_t)0x0100)
#define USART_HWFLOW_CONTROL_CTS     ((uint16_t)0x0200)
#define USART_HWFLOW_CONTROL_RTS_CTS ((uint16_t)0x0300)

/* USART_Clock */
#define USART_CLOCK_DISABLE ((uint16_t)0x0000)
#define USART_CLOCK_ENABLE  ((uint16_t)0x0800)

/* USART_Clock_Polarity */
#define USART_CPOL_LOW  ((uint16_t)0x0000)
#define USART_CPOL_HIGH ((uint16_t)0x0400)

/* USART_Clock_Phase */
#define USART_CPHA_1EDGE ((uint16_t)0x0000)
#define USART_CPHA_2EDGE ((uint16_t)0x0200)

/* USART_Last_Bit */
#define USART_LASTBIT_DISABLE ((uint16_t)0x0000)
#define USART_LASTBIT_ENABLE  ((uint16_t)0x0100)

/* USART_Interrupt_definition */
#define USART_IT_PE     ((uint16_t)0x0028)
#define USART_IT_TXE    ((uint16_t)0x0727)
#define USART_IT_TC     ((uint16_t)0x0626)
#define USART_IT_RXNE   ((uint16_t)0x0525)
#define USART_IT_ORE_RX ((uint16_t)0x0325)
#define USART_IT_IDLE   ((uint16_t)0x0424)
#define USART_IT_LBD    ((uint16_t)0x0846)
#define USART_IT_CTS    ((uint16_t)0x096A)
#define USART_IT_ERR    ((uint16_t)0x0060)
#define USART_IT_ORE_ER ((uint16_t)0x0360)
#define USART_IT_NE     ((uint16_t)0x0260)
#define USART_IT_FE     ((uint16_t)0x0160)

#define USART_IT_ORE USART_IT_ORE_ER

/* USART_DMA_Requests */
#define USART_DMAREQ_TX ((uint16_t)0x0080)
#define USART_DMAREQ_RX ((uint16_t)0x0040)

/* USART_WakeUp_methods */
#define USART_WAKEUP_IDLE_LINE    ((uint16_t)0x0000)
#define USART_WAKEUP_ADDRESS_MARK ((uint16_t)0x0800)

/* USART_LIN_Break_Detection_Length */
#define USART_LINBREAK_DETECT_LENGTH_10B ((uint16_t)0x0000)
#define USART_LINBREAK_DETECT_LENGTH_11B ((uint16_t)0x0020)

/* USART_IrDA_Low_Power */
#define USART_IRDAMODE_LOWPOWER ((uint16_t)0x0004)
#define USART_IRDAMODE_NORMAL   ((uint16_t)0x0000)

/* USART_Flags */
#define USART_FLAG_CTS  ((uint16_t)0x0200)
#define USART_FLAG_LBD  ((uint16_t)0x0100)
#define USART_FLAG_TXE  ((uint16_t)0x0080)
#define USART_FLAG_TC   ((uint16_t)0x0040)
#define USART_FLAG_RXNE ((uint16_t)0x0020)
#define USART_FLAG_IDLE ((uint16_t)0x0010)
#define USART_FLAG_ORE  ((uint16_t)0x0008)
#define USART_FLAG_NE   ((uint16_t)0x0004)
#define USART_FLAG_FE   ((uint16_t)0x0002)
#define USART_FLAG_PE   ((uint16_t)0x0001)

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
