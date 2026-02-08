#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                      Inter-integrated Circuit Interface                    */
/******************************************************************************/

#define I2C1_BASE  (APB1PERIPH_BASE + 0x5400)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define I2C_CTLR1   0
#define I2C_CTLR2   4
#define I2C_OADDR1  8
#define I2C_OADDR2  12
#define I2C_DATAR   16
#define I2C_STAR1   20
#define I2C_STAR2   24
#define I2C_CKCFGR  28

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint16_t CTLR1;      /* I2C Control Register 1 */
       uint16_t RESERVED0;
  __IO uint16_t CTLR2;      /* I2C Control Register 2 */
       uint16_t RESERVED1;
  __IO uint16_t OADDR1;     /* I2C Address Register 1 */
       uint16_t RESERVED2;
  __IO uint16_t OADDR2;     /* I2C Address Register 1 */
       uint16_t RESERVED3;
  __IO uint16_t DATAR;      /* I2C Data Register      */
       uint16_t RESERVED4;
  __IO uint16_t STAR1;      /* I2C Status Register 1  */
       uint16_t RESERVED5;
  __IO uint16_t STAR2;      /* I2C Status Register 2  */
       uint16_t RESERVED6;
  __IO uint16_t CKCFGR;     /* I2C Clock Register     */
       uint16_t RESERVED7;
} i2c_t;

#define I2C1  ((i2c_t *)I2C1_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* I2C SPE mask */
#define CTLR1_PE_SET   ((uint16_t)0x0001)
#define CTLR1_PE_RESET ((uint16_t)0xFFFE)

/* I2C START mask */
#define CTLR1_START_SET   ((uint16_t)0x0100)
#define CTLR1_START_RESET ((uint16_t)0xFEFF)

/* I2C STOP mask */
#define CTLR1_STOP_SET   ((uint16_t)0x0200)
#define CTLR1_STOP_RESET ((uint16_t)0xFDFF)

/* I2C ACK mask */
#define CTLR1_ACK_SET   ((uint16_t)0x0400)
#define CTLR1_ACK_RESET ((uint16_t)0xFBFF)

/* I2C ENGC mask */
#define CTLR1_ENGC_SET   ((uint16_t)0x0040)
#define CTLR1_ENGC_RESET ((uint16_t)0xFFBF)

/* I2C SWRST mask */
#define CTLR1_SWRST_SET   ((uint16_t)0x8000)
#define CTLR1_SWRST_RESET ((uint16_t)0x7FFF)

/* I2C PEC mask */
#define CTLR1_PEC_SET   ((uint16_t)0x1000)
#define CTLR1_PEC_RESET ((uint16_t)0xEFFF)

/* I2C ENPEC mask */
#define CTLR1_ENPEC_SET   ((uint16_t)0x0020)
#define CTLR1_ENPEC_RESET ((uint16_t)0xFFDF)

/* I2C ENARP mask */
#define CTLR1_ENARP_SET   ((uint16_t)0x0010)
#define CTLR1_ENARP_RESET ((uint16_t)0xFFEF)

/* I2C NOSTRETCH mask */
#define CTLR1_NOSTRETCH_SET   ((uint16_t)0x0080)
#define CTLR1_NOSTRETCH_RESET ((uint16_t)0xFF7F)

/* I2C registers Masks */
// NOTE:Overloaded Definition.
#define I2C_CTLR1_CLEAR_MASK ((uint16_t)0xFBF5)

/* I2C DMAEN mask */
#define CTLR2_DMAEN_SET   ((uint16_t)0x0800)
#define CTLR2_DMAEN_RESET ((uint16_t)0xF7FF)

/* I2C LAST mask */
#define CTLR2_LAST_SET   ((uint16_t)0x1000)
#define CTLR2_LAST_RESET ((uint16_t)0xEFFF)

/* I2C FREQ mask */
#define CTLR2_FREQ_RESET ((uint16_t)0xFFC0)

/* I2C ADD0 mask */
#define OADDR1_ADD0_SET   ((uint16_t)0x0001)
#define OADDR1_ADD0_RESET ((uint16_t)0xFFFE)

/* I2C ENDUAL mask */
#define OADDR2_ENDUAL_SET   ((uint16_t)0x0001)
#define OADDR2_ENDUAL_RESET ((uint16_t)0xFFFE)

/* I2C ADD2 mask */
#define OADDR2_ADD2_RESET ((uint16_t)0xFF01)

/* I2C F/S mask */
#define CKCFGR_FS_SET ((uint16_t)0x8000)

/* I2C CCR mask */
#define CKCFGR_CCR_SET ((uint16_t)0x0FFF)

/* I2C FLAG mask */
// Editor's Note: Overloaded Definition
#define I2C_FLAG_MASK ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define ITEN_MASK ((uint32_t)0x07000000)

/*******************  Bit definition for I2C_CTLR1 register  ********************/
#define I2C_CTLR1_PE        ((uint16_t)0x0001) /* Peripheral Enable */
#define I2C_CTLR1_ENPEC     ((uint16_t)0x0020) /* PEC Enable */
#define I2C_CTLR1_ENGC      ((uint16_t)0x0040) /* General Call Enable */
#define I2C_CTLR1_NOSTRETCH ((uint16_t)0x0080) /* Clock Stretching Disable (Slave mode) */
#define I2C_CTLR1_START     ((uint16_t)0x0100) /* Start Generation */
#define I2C_CTLR1_STOP      ((uint16_t)0x0200) /* Stop Generation */
#define I2C_CTLR1_ACK       ((uint16_t)0x0400) /* Acknowledge Enable */
#define I2C_CTLR1_POS       ((uint16_t)0x0800) /* Acknowledge/PEC Position (for data reception) */
#define I2C_CTLR1_PEC       ((uint16_t)0x1000) /* Packet Error Checking */
#define I2C_CTLR1_SWRST     ((uint16_t)0x8000) /* Software Reset */

/*******************  Bit definition for I2C_CTLR2 register  ********************/
#define I2C_CTLR2_FREQ   ((uint16_t)0x003F) /* FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CTLR2_FREQ_0 ((uint16_t)0x0001) /* Bit 0 */
#define I2C_CTLR2_FREQ_1 ((uint16_t)0x0002) /* Bit 1 */
#define I2C_CTLR2_FREQ_2 ((uint16_t)0x0004) /* Bit 2 */
#define I2C_CTLR2_FREQ_3 ((uint16_t)0x0008) /* Bit 3 */
#define I2C_CTLR2_FREQ_4 ((uint16_t)0x0010) /* Bit 4 */
#define I2C_CTLR2_FREQ_5 ((uint16_t)0x0020) /* Bit 5 */

#define I2C_CTLR2_ITERREN ((uint16_t)0x0100) /* Error Interrupt Enable */
#define I2C_CTLR2_ITEVTEN ((uint16_t)0x0200) /* Event Interrupt Enable */
#define I2C_CTLR2_ITBUFEN ((uint16_t)0x0400) /* Buffer Interrupt Enable */
#define I2C_CTLR2_DMAEN   ((uint16_t)0x0800) /* DMA Requests Enable */
#define I2C_CTLR2_LAST    ((uint16_t)0x1000) /* DMA Last Transfer */

/*******************  Bit definition for I2C_OADDR1 register  *******************/
#define I2C_OADDR1_ADD1_7 ((uint16_t)0x00FE) /* Interface Address */
#define I2C_OADDR1_ADD8_9 ((uint16_t)0x0300) /* Interface Address */

#define I2C_OADDR1_ADD0 ((uint16_t)0x0001) /* Bit 0 */
#define I2C_OADDR1_ADD1 ((uint16_t)0x0002) /* Bit 1 */
#define I2C_OADDR1_ADD2 ((uint16_t)0x0004) /* Bit 2 */
#define I2C_OADDR1_ADD3 ((uint16_t)0x0008) /* Bit 3 */
#define I2C_OADDR1_ADD4 ((uint16_t)0x0010) /* Bit 4 */
#define I2C_OADDR1_ADD5 ((uint16_t)0x0020) /* Bit 5 */
#define I2C_OADDR1_ADD6 ((uint16_t)0x0040) /* Bit 6 */
#define I2C_OADDR1_ADD7 ((uint16_t)0x0080) /* Bit 7 */
#define I2C_OADDR1_ADD8 ((uint16_t)0x0100) /* Bit 8 */
#define I2C_OADDR1_ADD9 ((uint16_t)0x0200) /* Bit 9 */

#define I2C_OADDR1_ADDMODE ((uint16_t)0x8000) /* Addressing Mode (Slave mode) */

/*******************  Bit definition for I2C_OADDR2 register  *******************/
#define I2C_OADDR2_ENDUAL ((uint8_t)0x01) /* Dual addressing mode enable */
#define I2C_OADDR2_ADD2   ((uint8_t)0xFE) /* Interface address */

/********************  Bit definition for I2C_DATAR register  ********************/
#define I2C_DR_DATAR ((uint8_t)0xFF) /* 8-bit Data Register */

/*******************  Bit definition for I2C_STAR1 register  ********************/
#define I2C_STAR1_SB     ((uint16_t)0x0001) /* Start Bit (Master mode) */
#define I2C_STAR1_ADDR   ((uint16_t)0x0002) /* Address sent (master mode)/matched (slave mode) */
#define I2C_STAR1_BTF    ((uint16_t)0x0004) /* Byte Transfer Finished */
#define I2C_STAR1_ADD10  ((uint16_t)0x0008) /* 10-bit header sent (Master mode) */
#define I2C_STAR1_STOPF  ((uint16_t)0x0010) /* Stop detection (Slave mode) */
#define I2C_STAR1_RXNE   ((uint16_t)0x0040) /* Data Register not Empty (receivers) */
#define I2C_STAR1_TXE    ((uint16_t)0x0080) /* Data Register Empty (transmitters) */
#define I2C_STAR1_BERR   ((uint16_t)0x0100) /* Bus Error */
#define I2C_STAR1_ARLO   ((uint16_t)0x0200) /* Arbitration Lost (master mode) */
#define I2C_STAR1_AF     ((uint16_t)0x0400) /* Acknowledge Failure */
#define I2C_STAR1_OVR    ((uint16_t)0x0800) /* Overrun/Underrun */
#define I2C_STAR1_PECERR ((uint16_t)0x1000) /* PEC Error in reception */

/*******************  Bit definition for I2C_STAR2 register  ********************/
#define I2C_STAR2_MSL     ((uint16_t)0x0001) /* Master/Slave */
#define I2C_STAR2_BUSY    ((uint16_t)0x0002) /* Bus Busy */
#define I2C_STAR2_TRA     ((uint16_t)0x0004) /* Transmitter/Receiver */
#define I2C_STAR2_GENCALL ((uint16_t)0x0010) /* General Call Address (Slave mode) */
#define I2C_STAR2_DUALF   ((uint16_t)0x0080) /* Dual Flag (Slave mode) */
#define I2C_STAR2_PEC     ((uint16_t)0xFF00) /* Packet Error Checking Register */

/*******************  Bit definition for I2C_CKCFGR register  ********************/
#define I2C_CKCFGR_CCR  ((uint16_t)0x0FFF) /* Clock Control Register in Fast/Standard mode (Master mode) */
#define I2C_CKCFGR_DUTY ((uint16_t)0x4000) /* Fast Mode Duty Cycle */
#define I2C_CKCFGR_FS   ((uint16_t)0x8000) /* I2C Master Mode Selection */

/* I2C_mode */
#define I2C_MODE_I2C ((uint16_t)0x0000)

/* I2C_duty_cycle_in_fast_mode */
#define I2C_DUTYCYCLE_16_9 ((uint16_t)0x4000) /* I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_DUTYCYCLE_2    ((uint16_t)0xBFFF) /* I2C fast mode Tlow/Thigh = 2 */

/* I2C_acknowledgement */
#define I2C_ACK_ENABLE  ((uint16_t)0x0400)
#define I2C_ACK_DISABLE ((uint16_t)0x0000)

/* I2C_transfer_direction */
#define I2C_DIRECTION_TRANSMITTER ((uint8_t)0x00)
#define I2C_DIRECTION_RECEIVER    ((uint8_t)0x01)

/* I2C_acknowledged_address */
#define I2C_ACKNOWLEDGEDADDRESS_7BIT  ((uint16_t)0x4000)
#define I2C_ACKNOWLEDGEDADDRESS_10BIT ((uint16_t)0xC000)

/* I2C_registers */
#define I2C_REGISTER_CTLR1  ((uint8_t)0x00)
#define I2C_REGISTER_CTLR2  ((uint8_t)0x04)
#define I2C_REGISTER_OADDR1 ((uint8_t)0x08)
#define I2C_REGISTER_OADDR2 ((uint8_t)0x0C)
#define I2C_REGISTER_DATAR  ((uint8_t)0x10)
#define I2C_REGISTER_STAR1  ((uint8_t)0x14)
#define I2C_REGISTER_STAR2  ((uint8_t)0x18)
#define I2C_REGISTER_CKCFGR ((uint8_t)0x1C)

/* I2C_PEC_position */
#define I2C_PECPosition_Next    ((uint16_t)0x0800)
#define I2C_PECPosition_Current ((uint16_t)0xF7FF)

/* I2C_NACK_position */
#define I2C_NACKPosition_Next    ((uint16_t)0x0800)
#define I2C_NACKPosition_Current ((uint16_t)0xF7FF)

/* I2C_interrupts_definition */
#define I2C_IT_BUF ((uint16_t)0x0400)
#define I2C_IT_EVT ((uint16_t)0x0200)
#define I2C_IT_ERR ((uint16_t)0x0100)

/* I2C_interrupts_definition */
#define I2C_IT_PECERR ((uint32_t)0x01001000)
#define I2C_IT_OVR    ((uint32_t)0x01000800)
#define I2C_IT_AF     ((uint32_t)0x01000400)
#define I2C_IT_ARLO   ((uint32_t)0x01000200)
#define I2C_IT_BERR   ((uint32_t)0x01000100)
#define I2C_IT_TXE    ((uint32_t)0x06000080)
#define I2C_IT_RXNE   ((uint32_t)0x06000040)
#define I2C_IT_STOPF  ((uint32_t)0x02000010)
#define I2C_IT_ADD10  ((uint32_t)0x02000008)
#define I2C_IT_BTF    ((uint32_t)0x02000004)
#define I2C_IT_ADDR   ((uint32_t)0x02000002)
#define I2C_IT_SB     ((uint32_t)0x02000001)

/* SR2 register flags  */
#define I2C_FLAG_DUALF   ((uint32_t)0x00800000)
#define I2C_FLAG_GENCALL ((uint32_t)0x00100000)
#define I2C_FLAG_TRA     ((uint32_t)0x00040000)
#define I2C_FLAG_BUSY    ((uint32_t)0x00020000)
#define I2C_FLAG_MSL     ((uint32_t)0x00010000)

/* SR1 register flags */
#define I2C_FLAG_PECERR ((uint32_t)0x10001000)
#define I2C_FLAG_OVR    ((uint32_t)0x10000800)
#define I2C_FLAG_AF     ((uint32_t)0x10000400)
#define I2C_FLAG_ARLO   ((uint32_t)0x10000200)
#define I2C_FLAG_BERR   ((uint32_t)0x10000100)
#define I2C_FLAG_TXE    ((uint32_t)0x10000080)
#define I2C_FLAG_RXNE   ((uint32_t)0x10000040)
#define I2C_FLAG_STOPF  ((uint32_t)0x10000010)
#define I2C_FLAG_ADD10  ((uint32_t)0x10000008)
#define I2C_FLAG_BTF    ((uint32_t)0x10000004)
#define I2C_FLAG_ADDR   ((uint32_t)0x10000002)
#define I2C_FLAG_SB     ((uint32_t)0x10000001)

/****************I2C Master Events (Events grouped in order of communication)********************/

/********************************************************************************************************************
 * @brief  Start communicate
 *
 * After master use I2C_GenerateSTART() function sending the START condition,the master
 * has to wait for event 5(the Start condition has been correctly
 * released on the I2C bus ).
 */
/* EVT5 */
#define I2C_EVENT_MASTER_MODE_SELECT ((uint32_t)0x00030001) /* BUSY, MSL and SB flag */

/********************************************************************************************************************
 * @brief  Address Acknowledge
 *
 * When start condition correctly released on the bus(check EVT5), the
 * master use I2C_Send7bitAddress() function sends the address of the slave(s) with which it will communicate
 * it also determines master as transmitter or Receiver. Then the master has to wait that a slave acknowledges
 * his address. If an acknowledge is sent on the bus, one of the following events will be set:
 *
 *  1) In case of Master Receiver (7-bit addressing): the I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED
 *     event is set.
 *
 *  2) In case of Master Transmitter (7-bit addressing): the I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED
 *     is set
 *
 *  3) In case of 10-Bit addressing mode, the master (after generating the START
 *  and checking on EVT5) use I2C_SendData() function send the header of 10-bit addressing mode.
 *  Then master wait EVT9. EVT9 means that the 10-bit addressing header has been correctly sent
 *  on the bus. Then master should use the function I2C_Send7bitAddress() to send the second part
 *  of the 10-bit address (LSB) . Then master should wait for event 6.
 */

/* EVT6 */
#define I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ((uint32_t)0x00070082) /* BUSY, MSL, ADDR, TXE and TRA flags */
#define I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED    ((uint32_t)0x00030002) /* BUSY, MSL and ADDR flags */
/*EVT9 */
#define I2C_EVENT_MASTER_MODE_ADDRESS10 ((uint32_t)0x00030008) /* BUSY, MSL and ADD10 flags */

/********************************************************************************************************************
 * @brief Communication events
 *
 * If START condition has generated and slave address
 * been acknowledged. then the master has to check one of the following events for
 * communication procedures:
 *
 * 1) Master Receiver mode: The master has to wait on the event EVT7 then use
 *   I2C_ReceiveData() function to read the data received from the slave .
 *
 * 2) Master Transmitter mode: The master use I2C_SendData() function to send data
 *     then to wait on event EVT8 or EVT8_2.
 *    These two events are similar:
 *     - EVT8 means that the data has been written in the data register and is
 *       being shifted out.
 *     - EVT8_2 means that the data has been physically shifted out and output
 *       on the bus.
 *     In most cases, using EVT8 is sufficient for the application.
 *     Using EVT8_2  will leads to a slower communication  speed but will more reliable .
 *     EVT8_2 is also more suitable than EVT8 for testing on the last data transmission
 *
 *  Note:
 *  In case the  user software does not guarantee that this event EVT7 is managed before
 *  the current byte end of transfer, then user may check on I2C_EVENT_MASTER_BYTE_RECEIVED
 *  and I2C_FLAG_BTF flag at the same time .But in this case the communication may be slower.
 */

/* Master Receive mode */
/* EVT7 */
#define I2C_EVENT_MASTER_BYTE_RECEIVED ((uint32_t)0x00030040) /* BUSY, MSL and RXNE flags */

/* Master Transmitter mode*/
/* EVT8 */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING ((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags */
/* EVT8_2 */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTED ((uint32_t)0x00070084) /* TRA, BUSY, MSL, TXE and BTF flags */

/******************I2C Slave Events (Events grouped in order of communication)******************/

/********************************************************************************************************************
 * @brief  Start Communicate events
 *
 * Wait on one of these events at the start of the communication. It means that
 * the I2C peripheral detected a start condition of master device generate on the bus.
 * If the acknowledge feature is enabled through function I2C_AcknowledgeConfig()),The peripheral generates an ACK condition on the bus.
 *
 * a) In normal case (only one address managed by the slave), when the address
 *   sent by the master matches the own address of the peripheral (configured by
 *   I2C_OwnAddress1 field) the I2C_EVENT_SLAVE_XXX_ADDRESS_MATCHED event is set
 *   (where XXX could be TRANSMITTER or RECEIVER).
 *
 * b) In case the address sent by the master matches the second address of the
 *   peripheral (configured by the function I2C_OwnAddress2Config() and enabled
 *   by the function I2C_DualAddressCmd()) the events I2C_EVENT_SLAVE_XXX_SECONDADDRESS_MATCHED
 *   (where XXX could be TRANSMITTER or RECEIVER) are set.
 *
 * c) In case the address sent by the master is General Call (address 0x00) and
 *   if the General Call is enabled for the peripheral (using function I2C_GeneralCallCmd())
 *   the following event is set I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED.
 */

/* EVT1 */
/* a) Case of One Single Address managed by the slave */
#define I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED    ((uint32_t)0x00020002) /* BUSY and ADDR flags */
#define I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED ((uint32_t)0x00060082) /* TRA, BUSY, TXE and ADDR flags */

/* b) Case of Dual address managed by the slave */
#define I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED    ((uint32_t)0x00820000) /* DUALF and BUSY flags */
#define I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED ((uint32_t)0x00860080) /* DUALF, TRA, BUSY and TXE flags */

/* c) Case of General Call enabled for the slave */
#define I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED ((uint32_t)0x00120000) /* GENCALL and BUSY flags */

/********************************************************************************************************************
 * @brief  Communication events
 *
 * Wait on one of these events when EVT1 has already been checked :
 *
 * - Slave Receiver mode:
 *     - EVT2--The device is expecting to receive a data byte .
 *     - EVT4--The device is expecting the end of the communication: master
 *       sends a stop condition and data transmission is stopped.
 *
 * - Slave Transmitter mode:
 *    - EVT3--When a byte has been transmitted by the slave and the Master is expecting
 *      the end of the byte transmission. The two events I2C_EVENT_SLAVE_BYTE_TRANSMITTED and
 *      I2C_EVENT_SLAVE_BYTE_TRANSMITTING are similar. If the user software doesn't guarantee
 *      the EVT3 is managed before the current byte end of transfer The second one can optionally
 *      be used.
 *    - EVT3_2--When the master sends a NACK  to tell slave device that data transmission
 *      shall end . The slave device has to stop sending
 *      data bytes and wait a Stop condition from bus.
 *
 *  Note:
 *  If the  user software does not guarantee that the event 2 is
 *  managed before the current byte end of transfer, User may check on I2C_EVENT_SLAVE_BYTE_RECEIVED
 *  and I2C_FLAG_BTF flag at the same time .
 *  In this case the communication will be slower.
 */

/* Slave Receiver mode*/
/* EVT2 */
#define I2C_EVENT_SLAVE_BYTE_RECEIVED ((uint32_t)0x00020040) /* BUSY and RXNE flags */
/* EVT4  */
#define I2C_EVENT_SLAVE_STOP_DETECTED ((uint32_t)0x00000010) /* STOPF flag */

/* Slave Transmitter mode -----------------------*/
/* EVT3 */
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTED  ((uint32_t)0x00060084) /* TRA, BUSY, TXE and BTF flags */
#define I2C_EVENT_SLAVE_BYTE_TRANSMITTING ((uint32_t)0x00060080) /* TRA, BUSY and TXE flags */
/*EVT3_2 */
#define I2C_EVENT_SLAVE_ACK_FAILURE ((uint32_t)0x00000400) /* AF flag */

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
