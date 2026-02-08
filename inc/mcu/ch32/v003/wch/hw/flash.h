#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                           FLASH Registers                                  */
/******************************************************************************/

#define FLASH_BASE  (AHBPERIPH_BASE + 0x2000)  /* Flash registers base address */

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define FLASH_ACTLR          0
#define FLASH_KEYR           4
#define FLASH_OBKEYR         8
#define FLASH_STATR          12
#define FLASH_CTLR           16
#define FLASH_ADDR           20
#define FLASH_OBR            28
#define FLASH_WPR            32
#define FLASH_MODEKEYR       36
#define FLASH_BOOT_MODEKEYR  40

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t ACTLR;          /* Control Register          */
  __IO uint32_t KEYR;           /* FPEC Key Register         */
  __IO uint32_t OBKEYR;         /* OBKEY Register            */
  __IO uint32_t STATR;          /* Status Register           */
  __IO uint32_t CTLR;           /* Configuration Register    */
  __IO uint32_t ADDR;           /* Address Register          */
  __IO uint32_t RESERVED;
  __IO uint32_t OBR;            /* Select Word Register      */
  __IO uint32_t WPR;            /* Write Protection Register */
  __IO uint32_t MODEKEYR;       /* Extended Key Register     */
  __IO uint32_t BOOT_MODEKEYR;  /* Unlock BOOT Key Register  */
} flash_t;

#define FLASH  ((flash_t *)FLASH_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* FLASH memory base address (program code and constants) */
#define FLASH_ADDR  ((uint32_t)0x08000000)


/* Flash Access Control Register bits */
#define ACR_LATENCY_MASK ((uint32_t)0x00000038)

/* Flash Control Register bits */
#define CR_PG_SET      ((uint32_t)0x00000001)
#define CR_PG_RESET    ((uint32_t)0xFFFFFFFE)
#define CR_PER_SET     ((uint32_t)0x00000002)
#define CR_PER_RESET   ((uint32_t)0xFFFFFFFD)
#define CR_MER_SET     ((uint32_t)0x00000004)
#define CR_MER_RESET   ((uint32_t)0xFFFFFFFB)
#define CR_OPTPG_SET   ((uint32_t)0x00000010)
#define CR_OPTPG_RESET ((uint32_t)0xFFFFFFEF)
#define CR_OPTER_SET   ((uint32_t)0x00000020)
#define CR_OPTER_RESET ((uint32_t)0xFFFFFFDF)
#define CR_STRT_SET    ((uint32_t)0x00000040)
#define CR_LOCK_SET    ((uint32_t)0x00000080)
#define CR_PAGE_PG     ((uint32_t)0x00010000)
#define CR_PAGE_ER     ((uint32_t)0x00020000)
#define CR_BUF_LOAD    ((uint32_t)0x00040000)
#define CR_BUF_RST     ((uint32_t)0x00080000)

/* FLASH Status Register bits */
#define SR_BSY      ((uint32_t)0x00000001)
#define SR_WRPRTERR ((uint32_t)0x00000010)
#define SR_EOP      ((uint32_t)0x00000020)

/* FLASH Mask */
#define RDPRT_MASK ((uint32_t)0x00000002)
#define WRP0_MASK  ((uint32_t)0x000000FF)
#define WRP1_MASK  ((uint32_t)0x0000FF00)
#define WRP2_MASK  ((uint32_t)0x00FF0000)
#define WRP3_MASK  ((uint32_t)0xFF000000)

/* FLASH Keys */
#define RDP_Key    ((uint16_t)0x00A5)
#define FLASH_KEY1 ((uint32_t)0x45670123)
#define FLASH_KEY2 ((uint32_t)0xCDEF89AB)

/* FLASH BANK address */
#define FLASH_BANK1_END_ADDRESS ((uint32_t)0x807FFFF)

/* Delay definition */
#define ERASE_TIMEOUT   ((uint32_t)0x000B0000)
#define PROGRAM_TIMEOUT ((uint32_t)0x00002000)

/* Flash Program Valid Address */
#define VALID_ADDR_START (FLASH_BASE)
#define VALID_ADDR_END   (FLASH_BASE + 0x4000)

/*******************  Bit definition for FLASH_ACTLR register  ******************/
#define FLASH_ACTLR_LATENCY   ((uint8_t)0x03) /* LATENCY[2:0] bits (Latency) */
#define FLASH_ACTLR_LATENCY_0 ((uint8_t)0x00) /* Bit 0 */
#define FLASH_ACTLR_LATENCY_1 ((uint8_t)0x01) /* Bit 0 */
#define FLASH_ACTLR_LATENCY_2 ((uint8_t)0x02) /* Bit 1 */

/******************  Bit definition for FLASH_KEYR register  ******************/
#define FLASH_KEYR_FKEYR ((uint32_t)0xFFFFFFFF) /* FPEC Key */

/*****************  Bit definition for FLASH_OBKEYR register  ****************/
#define FLASH_OBKEYR_OBKEYR ((uint32_t)0xFFFFFFFF) /* Option Byte Key */

/******************  Bit definition for FLASH_STATR register  *******************/
#define FLASH_STATR_BSY      ((uint32_t)0x00000001) /* Busy */
#define FLASH_STATR_WRPRTERR ((uint32_t)0x00000010) /* Write Protection Error */
#define FLASH_STATR_EOP      ((uint32_t)0x00000020) /* End of operation */
#define FLASH_STATR_MODE     ((uint32_t)0x00004000)
#define FLASH_STATR_LOCK     ((uint32_t)0x00008000)

/*******************  Bit definition for FLASH_CTLR register  *******************/
#define FLASH_CTLR_PG       ((uint32_t)0x00000001) /* Programming */
#define FLASH_CTLR_PER      ((uint32_t)0x00000002) /* Page Erase 1KByte*/
#define FLASH_CTLR_MER      ((uint32_t)0x00000004) /* Mass Erase */
#define FLASH_CTLR_OPTPG    ((uint32_t)0x00000010) /* Option Byte Programming */
#define FLASH_CTLR_OPTER    ((uint32_t)0x00000020) /* Option Byte Erase */
#define FLASH_CTLR_STRT     ((uint32_t)0x00000040) /* Start */
#define FLASH_CTLR_LOCK     ((uint32_t)0x00000080) /* Lock */
#define FLASH_CTLR_OPTWRE   ((uint32_t)0x00000200) /* Option Bytes Write Enable */
#define FLASH_CTLR_ERRIE    ((uint32_t)0x00000400) /* Error Interrupt Enable */
#define FLASH_CTLR_EOPIE    ((uint32_t)0x00001000) /* End of operation interrupt enable */
#define FLASH_CTLR_FLOCK    ((uint32_t)0x00008000)
#define FLASH_CTLR_PAGE_PG  ((uint32_t)0x00010000) /* Page Programming 64Byte */
#define FLASH_CTLR_PAGE_ER  ((uint32_t)0x00020000) /* Page Erase 64Byte */
#define FLASH_CTLR_BUF_LOAD ((uint32_t)0x00040000) /* Buffer Load */
#define FLASH_CTLR_BUF_RST  ((uint32_t)0x00080000) /* Buffer Reset */

/*******************  Bit definition for FLASH_ADDR register  *******************/
#define FLASH_ADDR_FAR ((uint32_t)0xFFFFFFFF) /* Flash Address */

/******************  Bit definition for FLASH_OBR register  *******************/
#define FLASH_OBR_OPTERR ((uint32_t)0x00000001) /* Option Byte Error */
#define FLASH_OBR_RDPRT  ((uint32_t)0x00000002) /* Read protection */

#define FLASH_OBR_USER       ((uint32_t)0x000003FC) /* User Option Bytes */
#define FLASH_OBR_WDG_SW     ((uint32_t)0x00000004) /* WDG_SW */
#define FLASH_OBR_STANDY_RST ((uint32_t)0x00000010)
#define FLASH_OBR_RST_MODE   ((uint32_t)0x00000060) /* RST_MODE */
#define FLASH_OBR_STATR_MODE ((uint32_t)0x00000080)
#define FLASH_OBR_FIX_11     ((uint32_t)0x00000300)

/******************  Bit definition for FLASH_WPR register  ******************/
#define FLASH_WPR_WRP ((uint32_t)0x0000FFFF) /* Write Protect */

/******************  Bit definition for FLASH_RDPR register  *******************/
#define FLASH_RDPR_RDPR  ((uint32_t)0x000000FF) /* Read protection option byte */
#define FLASH_RDPR_nRDPR ((uint32_t)0x0000FF00) /* Read protection complemented option byte */

/******************  Bit definition for FLASH_USER register  ******************/
#define FLASH_USER_USER  ((uint32_t)0x00FF0000) /* User option byte */
#define FLASH_USER_nUSER ((uint32_t)0xFF000000) /* User complemented option byte */

/******************  Bit definition for FLASH_Data0 register  *****************/
#define FLASH_Data0_Data0  ((uint32_t)0x000000FF) /* User data storage option byte */
#define FLASH_Data0_nData0 ((uint32_t)0x0000FF00) /* User data storage complemented option byte */

/******************  Bit definition for FLASH_Data1 register  *****************/
#define FLASH_Data1_Data1  ((uint32_t)0x00FF0000) /* User data storage option byte */
#define FLASH_Data1_nData1 ((uint32_t)0xFF000000) /* User data storage complemented option byte */

/******************  Bit definition for FLASH_WRPR0 register  ******************/
#define FLASH_WRPR0_WRPR0  ((uint32_t)0x000000FF) /* Flash memory write protection option bytes */
#define FLASH_WRPR0_nWRPR0 ((uint32_t)0x0000FF00) /* Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_WRPR1 register  ******************/
#define FLASH_WRPR1_WRPR1  ((uint32_t)0x00FF0000) /* Flash memory write protection option bytes */
#define FLASH_WRPR1_nWRPR1 ((uint32_t)0xFF000000) /* Flash memory write protection complemented option bytes */

/******************  Bit definition for FLASH_MODEKEYR register  ******************/
#define FLASH_MODEKEYR_KEY1 ((uint32_t)0x45670123)
#define FLASH_MODEKEYR_KEY2 ((uint32_t)0xCDEF89AB)

/******************  Bit definition for FLASH__BOOT_MODEKEYR register  ******************/
#define FLASH_BOOT_MODEKEYR_KEY1 ((uint32_t)0x45670123)
#define FLASH_BOOT_MODEKEYR_KEY2 ((uint32_t)0xCDEF89AB)

#ifndef __ASSEMBLER__
/* FLASH Status */
typedef enum {
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT,
  FLASH_OP_RANGE_ERROR = 0xFD,
  FLASH_ALIGN_ERROR = 0xFE,
  FLASH_ADR_RANGE_ERROR = 0xFF,
} flash_status_t;

#endif /* __ASSEMBLER__ */

/* Flash_Latency */
#define FLASH_LATENCY_0 ((uint32_t)0x00000000) /* FLASH Zero Latency cycle */
#define FLASH_LATENCY_1 ((uint32_t)0x00000001) /* FLASH One Latency cycle */
#define FLASH_LATENCY_2 ((uint32_t)0x00000002) /* FLASH Two Latency cycles */

/* Values to be used with CH32V00x devices (1page = 64Byte) */
#define FLASH_WRPROT_PAGES_0TO15    ((uint32_t)0x00000001) /* CH32 Low and Medium density devices: Write protection of page 0 to 15 */
#define FLASH_WRPROT_PAGES_16TO31   ((uint32_t)0x00000002) /* CH32 Low and Medium density devices: Write protection of page 16 to 31 */
#define FLASH_WRPROT_PAGES_32TO47   ((uint32_t)0x00000004) /* CH32 Low and Medium density devices: Write protection of page 32 to 47 */
#define FLASH_WRPROT_PAGES_48TO63   ((uint32_t)0x00000008) /* CH32 Low and Medium density devices: Write protection of page 48 to 63 */
#define FLASH_WRPROT_PAGES_64TO79   ((uint32_t)0x00000010) /* CH32 Low and Medium density devices: Write protection of page 64 to 79 */
#define FLASH_WRPROT_PAGES_80TO95   ((uint32_t)0x00000020) /* CH32 Low and Medium density devices: Write protection of page 80 to 95 */
#define FLASH_WRPROT_PAGES_96TO111  ((uint32_t)0x00000040) /* CH32 Low and Medium density devices: Write protection of page 96 to 111 */
#define FLASH_WRPROT_PAGES_112TO127 ((uint32_t)0x00000080) /* CH32 Low and Medium density devices: Write protection of page 112 to 127 */
#define FLASH_WRPROT_PAGES_128TO143 ((uint32_t)0x00000100) /* CH32 Medium-density devices: Write protection of page 128 to 143 */
#define FLASH_WRPROT_PAGES_144TO159 ((uint32_t)0x00000200) /* CH32 Medium-density devices: Write protection of page 144 to 159 */
#define FLASH_WRPROT_PAGES_160TO175 ((uint32_t)0x00000400) /* CH32 Medium-density devices: Write protection of page 160 to 175 */
#define FLASH_WRPROT_PAGES_176TO191 ((uint32_t)0x00000800) /* CH32 Medium-density devices: Write protection of page 176 to 191 */
#define FLASH_WRPROT_PAGES_192TO207 ((uint32_t)0x00001000) /* CH32 Medium-density devices: Write protection of page 192 to 207 */
#define FLASH_WRPROT_PAGES_208TO223 ((uint32_t)0x00002000) /* CH32 Medium-density devices: Write protection of page 208 to 223 */
#define FLASH_WRPROT_PAGES_224TO239 ((uint32_t)0x00004000) /* CH32 Medium-density devices: Write protection of page 224 to 239 */
#define FLASH_WRPROT_PAGES_240TO255 ((uint32_t)0x00008000) /* CH32 Medium-density devices: Write protection of page 240 to 255 */

#define FLASH_WRPROT_ALLPAGES ((uint32_t)0x0000FFFF) /* Write protection of all Pages */

/* FLASH_Interrupts */
#define FLASH_IT_ERROR       ((uint32_t)0x00000400) /* FPEC error interrupt source */
#define FLASH_IT_EOP         ((uint32_t)0x00001000) /* End of FLASH Operation Interrupt source */
#define FLASH_IT_BANK1_ERROR FLASH_IT_ERROR         /* FPEC BANK1 error interrupt source */
#define FLASH_IT_BANK1_EOP   FLASH_IT_EOP           /* End of FLASH BANK1 Operation Interrupt source */

/* FLASH_Flags */
#define FLASH_FLAG_BSY      ((uint32_t)0x00000001) /* FLASH Busy flag */
#define FLASH_FLAG_EOP      ((uint32_t)0x00000020) /* FLASH End of Operation flag */
#define FLASH_FLAG_WRPRTERR ((uint32_t)0x00000010) /* FLASH Write protected error flag */
#define FLASH_FLAG_OPTERR   ((uint32_t)0x00000001) /* FLASH Option Byte error flag */

#define FLASH_FLAG_BANK1_BSY      FLASH_FLAG_BSY      /* FLASH BANK1 Busy flag*/
#define FLASH_FLAG_BANK1_EOP      FLASH_FLAG_EOP      /* FLASH BANK1 End of Operation flag */
#define FLASH_FLAG_BANK1_WRPRTERR FLASH_FLAG_WRPRTERR /* FLASH BANK1 Write protected error flag */

/* System_Reset_Start_Mode */
#define START_MODE_USER ((uint32_t)0x00000000)
#define START_MODE_BOOT ((uint32_t)0x00004000)

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
