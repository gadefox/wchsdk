#pragma once

#include "wch/hw/def.h"

/******************************************************************************/
/*                           FLASH Registers                                  */
/******************************************************************************/

#define FLASH_BASE  (AHBPERIPH_BASE + 0x2000)  /* Flash registers base address */

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define FLASH_ACTLR     0
#define FLASH_KEYR      4
#define FLASH_OBKEYR    8
#define FLASH_STATR     12
#define FLASH_CTLR      16
#define FLASH_ADDR      20
#define FLASH_OBR       28
#define FLASH_WPR       32
#define FLASH_MODEKEYR  36
#define FLASH_BOOTKEYR  40

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t ACTLR;          /* Control Register          */
  __IO uint32_t KEYR;           /* FPEC Key Register         */
  __IO uint32_t OBKEYR;         /* OBKEY Register            */
  __IO uint32_t STATR;          /* Status Register           */
  __IO uint32_t CTLR;           /* Configuration Register    */
  __IO uint32_t ADDR;           /* Address Register          */
       uint32_t RESERVED;
  __IO uint32_t OBR;            /* Select Word Register      */
  __IO uint32_t WPR;            /* Write Protection Register */
  __IO uint32_t MODEKEYR;       /* Extended Key Register     */
  __IO uint32_t BOOTKEYR;       /* Unlock BOOT Key Register  */
} flash_t;

#define FLASH  ((flash_t *)FLASH_BASE)

/* FLASH Status */
typedef enum {
  FLASH_BUSY          = 1,
  FLASH_PG_ERR        = 2,
  FLASH_WRP_ERR       = 3,
  FLASH_COMPLETE      = 4,
  FLASH_TIMEOUT       = 5,
  FLASH_OP_RANGE_ERR  = 0xFD,
  FLASH_ALIGN_ERR     = 0xFE,
  FLASH_ADR_RANGE_ERR = 0xFF,
} flash_status_t;

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* Delay definition */
#define ERASE_TIMEOUT 0x000B0000
#define WRITE_TIMEOUT 0x00002000

/* FLASH memory base address (program code and constants) */
#define FLASH_ADDR  0x08000000
#define FLASH_SIZE  0x4000

#define FLASH_BOOT_ADDR  0x1FFFF000
#define FLASH_BOOT_SIZE  0x0780

/* FLASH Keys */
#define FLASH_KEY1 0x45670123
#define FLASH_KEY2 0xCDEF89AB

/* FLASH_Interrupts */
#define FLASH_IT_ERR  0x00000400 /* FPEC error interrupt source */
#define FLASH_IT_EOP  0x00001000 /* End of FLASH Operation Interrupt source */

/*******************  Bit definition for FLASH_ACTLR register  ******************/
#define FLASH_LATENCY     0x03 /* LATENCY[2:0] bits (Latency) */
#define FLASH_LATENCY0    0x00 /* Zero Latency cycle */
#define FLASH_LATENCY1    0x01 /* One Latency cycle */

/******************  Bit definition for FLASH_STATR register  *******************/
#define FLASH_STATR_BSY      0x00000001 /* Busy */
#define FLASH_STATR_WRPRTERR 0x00000010 /* Write Protection Error */
#define FLASH_STATR_EOP      0x00000020 /* End of operation */
#define FLASH_STATR_BOOTMODE 0x00004000 /* After software reset, you can switch to the BOOT area */
#define FLASH_STATR_LOCK     0x00008000 /* Locked, cannot perform a write operation to the BOOTMODE field */

/*******************  Bit definition for FLASH_CTLR register  *******************/
#define FLASH_PG       0x00000001 /* Programming */
#define FLASH_PER      0x00000002 /* Page Erase 1KByte*/
#define FLASH_MER      0x00000004 /* Mass Erase */
#define FLASH_OPTPG    0x00000010 /* Option Byte Programming */
#define FLASH_OPTER    0x00000020 /* Option Byte Erase */
#define FLASH_STRT     0x00000040 /* Start */
#define FLASH_LOCK     0x00000080 /* Lock */
#define FLASH_OPTWRE   0x00000200 /* Option Bytes Write Enable */
#define FLASH_ERRIE    0x00000400 /* Error Interrupt Enable */
#define FLASH_EOPIE    0x00001000 /* End of operation interrupt enable */
#define FLASH_FLOCK    0x00008000
#define FLASH_PAGE_PG  0x00010000 /* Page Programming 64Byte */
#define FLASH_PAGE_ER  0x00020000 /* Page Erase 64Byte */
#define FLASH_BUF_LOAD 0x00040000 /* Buffer Load */
#define FLASH_BUF_RST  0x00080000 /* Buffer Reset */

/******************  Bit definition for FLASH_OBR register  *******************/
#define FLASH_OPTERR      0x00000001 /* Option Byte Error */
#define FLASH_RDPRT       0x00000002 /* Read protection */

#define FLASH_WDG_SW      0x00000004 /* Software IWDG selected */
#define FLASH_STANDY_RST  0x00000010
#define FLASH_BOOT_MODE   0x00000080

#define FLASH_RST         0x00000060 /* 2 bits; RST_MODE */
#define FLASH_RST_DT128US 0x00000000 /* Reset IO enable (PD7) and  Ignore delay time 128us */
#define FLASH_RST_DT1MS   0x00000020 /* Reset IO enable (PD7) and  Ignore delay time 1ms */
#define FLASH_RST_DT12MS  0x00000040 /* Reset IO enable (PD7) and  Ignore delay time 12ms */

#define FLASH_USER        0x000003FC /* 8 bits; User Option Bytes */
#define FLASH_DATA0       0x0003FC00 /* 8 bits */
#define FLASH_DATA1       0x03FC0000 /* 8 bits */

/******************  Bit definition for FLASH_WPR register  ******************/
#define FLASH_PAGES_0TO15    0x00000001 /* CH32 Low and Medium density devices: Write protection of page 0 to 15 */
#define FLASH_PAGES_16TO31   0x00000002 /* CH32 Low and Medium density devices: Write protection of page 16 to 31 */
#define FLASH_PAGES_32TO47   0x00000004 /* CH32 Low and Medium density devices: Write protection of page 32 to 47 */
#define FLASH_PAGES_48TO63   0x00000008 /* CH32 Low and Medium density devices: Write protection of page 48 to 63 */
#define FLASH_PAGES_64TO79   0x00000010 /* CH32 Low and Medium density devices: Write protection of page 64 to 79 */
#define FLASH_PAGES_80TO95   0x00000020 /* CH32 Low and Medium density devices: Write protection of page 80 to 95 */
#define FLASH_PAGES_96TO111  0x00000040 /* CH32 Low and Medium density devices: Write protection of page 96 to 111 */
#define FLASH_PAGES_112TO127 0x00000080 /* CH32 Low and Medium density devices: Write protection of page 112 to 127 */
#define FLASH_PAGES_128TO143 0x00000100 /* CH32 Medium-density devices: Write protection of page 128 to 143 */
#define FLASH_PAGES_144TO159 0x00000200 /* CH32 Medium-density devices: Write protection of page 144 to 159 */
#define FLASH_PAGES_160TO175 0x00000400 /* CH32 Medium-density devices: Write protection of page 160 to 175 */
#define FLASH_PAGES_176TO191 0x00000800 /* CH32 Medium-density devices: Write protection of page 176 to 191 */
#define FLASH_PAGES_192TO207 0x00001000 /* CH32 Medium-density devices: Write protection of page 192 to 207 */
#define FLASH_PAGES_208TO223 0x00002000 /* CH32 Medium-density devices: Write protection of page 208 to 223 */
#define FLASH_PAGES_224TO239 0x00004000 /* CH32 Medium-density devices: Write protection of page 224 to 239 */
#define FLASH_PAGES_240TO255 0x00008000 /* CH32 Medium-density devices: Write protection of page 240 to 255 */
#define FLASH_PAGES_ALL      0x0000FFFF /* Write protection of all Pages */

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
