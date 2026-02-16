#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                          Reset and Clock Control                           */
/******************************************************************************/

#define RCC_BASE  (AHBPERIPH_BASE + 0x1000)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define RCC_CTLR       0
#define RCC_CFGR0      4
#define RCC_INTR       8
#define RCC_APB2PRSTR  12
#define RCC_APB1PRSTR  16
#define RCC_AHBPCENR   20
#define RCC_APB2PCENR  24
#define RCC_APB1PCENR  28
#define RCC_RSTSCKR    36

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t CTLR;       /* Clock Control Register                */
  __IO uint32_t CFGR0;      /* Clock Configuration Register 0        */
  __IO uint32_t INTR;       /* Clock Interrupt Register              */
  __IO uint32_t APB2PRSTR;  /* APB2 Peripheral Reset Register        */
  __IO uint32_t APB1PRSTR;  /* APB1 Peripheral Reset Register        */
  __IO uint32_t AHBPCENR;   /* AHB Peripheral Clock Enable Register  */
  __IO uint32_t APB2PCENR;  /* APB2 Peripheral Clock Enable Register */
  __IO uint32_t APB1PCENR;  /* APB1 Peripheral Clock Enable Register */
  __IO uint32_t RESERVED0;
  __IO uint32_t RSTSCKR;    /* Control/Status Register               */
} rcc_t;

#define RCC  ((rcc_t *)RCC_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* CTLR register bit mask */
#define CTLR_HSEBYP_RESET ((uint32_t)0xFFFBFFFF)
#define CTLR_HSEBYP_SET   ((uint32_t)0x00040000)
#define CTLR_HSEON_RESET  ((uint32_t)0xFFFEFFFF)
#define CTLR_HSEON_SET    ((uint32_t)0x00010000)
#define CTLR_HSITRIM_MASK ((uint32_t)0xFFFFFF07)

#define CFGR0_PLL_MASK          ((uint32_t)0xFFC0FFFF)
#define CFGR0_PLLMULL_MASK      ((uint32_t)0x003C0000)
#define CFGR0_PLLSRC_MASK       ((uint32_t)0x00010000)
#define CFGR0_PLLXTPRE_MASK     ((uint32_t)0x00020000)
#define CFGR0_SWS_MASK          ((uint32_t)0x0000000C)
#define CFGR0_SW_MASK           ((uint32_t)0xFFFFFFFC)
#define CFGR0_HPRE_RESET_MASK   ((uint32_t)0xFFFFFF0F)
#define CFGR0_HPRE_SET_MASK     ((uint32_t)0x000000F0)
#define CFGR0_PPRE1_RESET_MASK  ((uint32_t)0xFFFFF8FF)
#define CFGR0_PPRE1_SET_MASK    ((uint32_t)0x00000700)
#define CFGR0_PPRE2_RESET_MASK  ((uint32_t)0xFFFFC7FF)
#define CFGR0_PPRE2_SET_MASK    ((uint32_t)0x00003800)
#define CFGR0_ADCPRE_RESET_MASK ((uint32_t)0xFFFF07FF)
#define CFGR0_ADCPRE_SET_MASK   ((uint32_t)0x0000F800)

/* RSTSCKR register bit mask */
#define RSTSCKR_RMVF_SET ((uint32_t)0x01000000)

/* RCC Flag Mask */
// Editor's Note: Overloaded Definition
#define RCC_FLAG_MASK ((uint8_t)0x1F)

/* INTR register byte 2 (Bits[15:8]) base address */
#define INTR_BYTE2_ADDRESS ((uint32_t)0x40021009)

/* INTR register byte 3 (Bits[23:16]) base address */
#define INTR_BYTE3_ADDRESS ((uint32_t)0x4002100A)

/* CFGR0 register byte 4 (Bits[31:24]) base address */
#define CFGR0_BYTE4_ADDRESS ((uint32_t)0x40021007)

/* BDCTLR register base address */
#define BDCTLR_ADDRESS (PERIPH_BASE + BDCTLR_OFFSET)

/********************  Bit definition for RCC_CTLR register  ********************/
#define RCC_HSION   ((uint32_t)0x00000001) /* Internal High Speed clock enable */
#define RCC_HSIRDY  ((uint32_t)0x00000002) /* Internal High Speed clock ready flag */
#define RCC_HSITRIM ((uint32_t)0x000000F8) /* Internal High Speed clock trimming */
#define RCC_HSICAL  ((uint32_t)0x0000FF00) /* Internal High Speed clock Calibration */
#define RCC_HSEON   ((uint32_t)0x00010000) /* External High Speed clock enable */
#define RCC_HSERDY  ((uint32_t)0x00020000) /* External High Speed clock ready flag */
#define RCC_HSEBYP  ((uint32_t)0x00040000) /* External High Speed clock Bypass */
#define RCC_CSSON   ((uint32_t)0x00080000) /* Clock Security System enable */
#define RCC_PLLON   ((uint32_t)0x01000000) /* PLL enable */
#define RCC_PLLRDY  ((uint32_t)0x02000000) /* PLL clock ready flag */

/*******************  Bit definition for RCC_CFGR0 register  *******************/
#define RCC_SW   ((uint32_t)0x00000003) /* SW[1:0] bits (System clock Switch) */
#define RCC_SW_0 ((uint32_t)0x00000001) /* Bit 0 */
#define RCC_SW_1 ((uint32_t)0x00000002) /* Bit 1 */

#define RCC_SW_HSI ((uint32_t)0x00000000) /* HSI selected as system clock */
#define RCC_SW_HSE ((uint32_t)0x00000001) /* HSE selected as system clock */
#define RCC_SW_PLL ((uint32_t)0x00000002) /* PLL selected as system clock */

#define RCC_SWS   ((uint32_t)0x0000000C) /* SWS[1:0] bits (System Clock Switch Status) */
#define RCC_SWS_0 ((uint32_t)0x00000004) /* Bit 0 */
#define RCC_SWS_1 ((uint32_t)0x00000008) /* Bit 1 */

#define RCC_SWS_HSI ((uint32_t)0x00000000) /* HSI oscillator used as system clock */
#define RCC_SWS_HSE ((uint32_t)0x00000004) /* HSE oscillator used as system clock */
#define RCC_SWS_PLL ((uint32_t)0x00000008) /* PLL used as system clock */

#define RCC_HPRE   ((uint32_t)0x000000F0) /* HPRE[3:0] bits (AHB prescaler) */
#define RCC_HPRE_0 ((uint32_t)0x00000010) /* Bit 0 */
#define RCC_HPRE_1 ((uint32_t)0x00000020) /* Bit 1 */
#define RCC_HPRE_2 ((uint32_t)0x00000040) /* Bit 2 */
#define RCC_HPRE_3 ((uint32_t)0x00000080) /* Bit 3 */

#define RCC_HPRE_DIV1   ((uint32_t)0x00000000) /* SYSCLK not divided */
#define RCC_HPRE_DIV2   ((uint32_t)0x00000010) /* SYSCLK divided by 2 */
#define RCC_HPRE_DIV3   ((uint32_t)0x00000020) /* SYSCLK divided by 3 */
#define RCC_HPRE_DIV4   ((uint32_t)0x00000030) /* SYSCLK divided by 4 */
#define RCC_HPRE_DIV5   ((uint32_t)0x00000040) /* SYSCLK divided by 5 */
#define RCC_HPRE_DIV6   ((uint32_t)0x00000050) /* SYSCLK divided by 6 */
#define RCC_HPRE_DIV7   ((uint32_t)0x00000060) /* SYSCLK divided by 7 */
#define RCC_HPRE_DIV8   ((uint32_t)0x00000070) /* SYSCLK divided by 8 */
#define RCC_HPRE_DIV16  ((uint32_t)0x000000B0) /* SYSCLK divided by 16 */
#define RCC_HPRE_DIV32  ((uint32_t)0x000000C0) /* SYSCLK divided by 32 */
#define RCC_HPRE_DIV64  ((uint32_t)0x000000D0) /* SYSCLK divided by 64 */
#define RCC_HPRE_DIV128 ((uint32_t)0x000000E0) /* SYSCLK divided by 128 */
#define RCC_HPRE_DIV256 ((uint32_t)0x000000F0) /* SYSCLK divided by 256 */

#define RCC_ADCPRE   ((uint32_t)0x0000F800) /* ADCPRE[4:0] bits (ADC prescaler) */
#define RCC_ADCPRE_0 ((uint32_t)0x00000800) /* Bit 0 */
#define RCC_ADCPRE_1 ((uint32_t)0x00001000) /* Bit 1 */
#define RCC_ADCPRE_2 ((uint32_t)0x00002000)
#define RCC_ADCPRE_3 ((uint32_t)0x00004000)
#define RCC_ADCPRE_4 ((uint32_t)0x00008000)

#define RCC_ADCPRE_DIV2 ((uint32_t)0x00000000) /* HBCLK divided by 2 */
/* includes                                                0x00000800,
                                                           0x00001000,
                                                           0x00001800 */
#define RCC_ADCPRE_DIV4_1  ((uint32_t)0x00002000) /* HBCLK divided by 4 */
#define RCC_ADCPRE_DIV8_2  ((uint32_t)0x00002800) /* HBCLK divided by 8 */
#define RCC_ADCPRE_DIV16_2 ((uint32_t)0x00003000) /* HBCLK divided by 16 */
#define RCC_ADCPRE_DIV32_2 ((uint32_t)0x00003800) /* HBCLK divided by 32 */
#define RCC_ADCPRE_DIV4    ((uint32_t)0x00004000) /* HBCLK divided by 4 */
/* includes                                                0x00004800,
                                                           0x00005000,
                                                           0x00005800 */
#define RCC_ADCPRE_DIV8_1  ((uint32_t)0x00006000) /* HBCLK divided by 8 */
#define RCC_ADCPRE_DIV16_1 ((uint32_t)0x00006800) /* HBCLK divided by 16 */
#define RCC_ADCPRE_DIV32_1 ((uint32_t)0x00007000) /* HBCLK divided by 32 */
#define RCC_ADCPRE_DIV64_1 ((uint32_t)0x00007800) /* HBCLK divided by 64 */
#define RCC_ADCPRE_DIV6    ((uint32_t)0x00008000) /* HBCLK divided by 6 */
/* includes                                                0x00008800,
                                                           0x00009000,
                                                           0x00009800 */
#define RCC_ADCPRE_DIV12 ((uint32_t)0x0000A000) /* HBCLK divided by 12 */
#define RCC_ADCPRE_DIV24 ((uint32_t)0x0000A800) /* HBCLK divided by 24 */
#define RCC_ADCPRE_DIV48 ((uint32_t)0x0000B000) /* HBCLK divided by 48 */
#define RCC_ADCPRE_DIV96 ((uint32_t)0x0000B800) /* HBCLK divided by 96 */
#define RCC_ADCPRE_DIV8  ((uint32_t)0x0000C000) /* HBCLK divided by 8 */
/* includes                                                0x0000C800,
                                                           0x0000D000,
                                                           0x0000D800 */
#define RCC_ADCPRE_DIV16  ((uint32_t)0x0000E000) /* HBCLK divided by 16 */
#define RCC_ADCPRE_DIV32  ((uint32_t)0x0000E800) /* HBCLK divided by 32 */
#define RCC_ADCPRE_DIV64  ((uint32_t)0x0000F000) /* HBCLK divided by 64 */
#define RCC_ADCPRE_DIV128 ((uint32_t)0x0000F800) /* HBCLK divided by 128 */

#define RCC_PLLSRC          ((uint32_t)0x00010000) /* PLL entry clock source */
#define RCC_PLLSRC_HSI_MUL2 ((uint32_t)0x00000000) /* HSI clock*2 selected as PLL entry clock source */
#define RCC_PLLSRC_HSE_MUL2 ((uint32_t)0x00010000) /* HSE clock*2 selected as PLL entry clock source */

#define RCC_CFGR0_MCO ((uint32_t)0x07000000) /* MCO[2:0] bits (Microcontroller Clock Output) */
#define RCC_MCO_0     ((uint32_t)0x01000000) /* Bit 0 */
#define RCC_MCO_1     ((uint32_t)0x02000000) /* Bit 1 */
#define RCC_MCO_2     ((uint32_t)0x04000000) /* Bit 2 */

#define RCC_MCO_NOCLOCK      ((uint32_t)0x00000000) /* No clock */
#define RCC_CFGR0_MCO_SYSCLK ((uint32_t)0x04000000) /* System clock selected as MCO source */
#define RCC_CFGR0_MCO_HSI    ((uint32_t)0x05000000) /* HSI clock selected as MCO source */
#define RCC_CFGR0_MCO_HSE    ((uint32_t)0x06000000) /* HSE clock selected as MCO source  */
#define RCC_CFGR0_MCO_PLL    ((uint32_t)0x07000000) /* PLL clock divided by 2 selected as MCO source */

/*******************  Bit definition for RCC_INTR register  ********************/
#define RCC_LSIRDYF  ((uint32_t)0x00000001) /* LSI Ready Interrupt flag */
#define RCC_HSIRDYF  ((uint32_t)0x00000004) /* HSI Ready Interrupt flag */
#define RCC_HSERDYF  ((uint32_t)0x00000008) /* HSE Ready Interrupt flag */
#define RCC_PLLRDYF  ((uint32_t)0x00000010) /* PLL Ready Interrupt flag */
#define RCC_CSSF     ((uint32_t)0x00000080) /* Clock Security System Interrupt flag */
#define RCC_LSIRDYIE ((uint32_t)0x00000100) /* LSI Ready Interrupt Enable */
#define RCC_HSIRDYIE ((uint32_t)0x00000400) /* HSI Ready Interrupt Enable */
#define RCC_HSERDYIE ((uint32_t)0x00000800) /* HSE Ready Interrupt Enable */
#define RCC_PLLRDYIE ((uint32_t)0x00001000) /* PLL Ready Interrupt Enable */
#define RCC_LSIRDYC  ((uint32_t)0x00010000) /* LSI Ready Interrupt Clear */
#define RCC_HSIRDYC  ((uint32_t)0x00040000) /* HSI Ready Interrupt Clear */
#define RCC_HSERDYC  ((uint32_t)0x00080000) /* HSE Ready Interrupt Clear */
#define RCC_PLLRDYC  ((uint32_t)0x00100000) /* PLL Ready Interrupt Clear */
#define RCC_CSSC     ((uint32_t)0x00800000) /* Clock Security System Interrupt Clear */

/*****************  Bit definition for RCC_APB2PRSTR register  *****************/
#define RCC_AFIORST ((uint32_t)0x00000001) /* Alternate Function I/O reset */
#define RCC_IOPARST ((uint32_t)0x00000004) /* I/O port A reset */
#define RCC_IOPBRST ((uint32_t)0x00000008) /* I/O port B reset */
#define RCC_IOPCRST ((uint32_t)0x00000010) /* I/O port C reset */
#define RCC_IOPDRST ((uint32_t)0x00000020) /* I/O port D reset */
#define RCC_ADC1RST ((uint32_t)0x00000200) /* ADC 1 interface reset */

#define RCC_ADC2RST ((uint32_t)0x00000400) /* ADC 2 interface reset */

#define RCC_TIM1RST   ((uint32_t)0x00000800) /* TIM1 Timer reset */
#define RCC_SPI1RST   ((uint32_t)0x00001000) /* SPI 1 reset */
#define RCC_USART1RST ((uint32_t)0x00004000) /* USART1 reset */

#define RCC_IOPERST ((uint32_t)0x00000040) /* I/O port E reset */

/*****************  Bit definition for RCC_APB1PRSTR register  *****************/
#define RCC_TIM2RST   ((uint32_t)0x00000001) /* Timer 2 reset */
#define RCC_TIM3RST   ((uint32_t)0x00000002) /* Timer 3 reset */
#define RCC_WWDGRST   ((uint32_t)0x00000800) /* Window Watchdog reset */
#define RCC_USART2RST ((uint32_t)0x00020000) /* USART 2 reset */
#define RCC_I2C1RST   ((uint32_t)0x00200000) /* I2C 1 reset */

#define RCC_CAN1RST ((uint32_t)0x02000000) /* CAN1 reset */

#define RCC_BKPRST ((uint32_t)0x08000000) /* Backup interface reset */
#define RCC_PWRRST ((uint32_t)0x10000000) /* Power interface reset */

#define RCC_TIM4RST   ((uint32_t)0x00000004) /* Timer 4 reset */
#define RCC_SPI2RST   ((uint32_t)0x00004000) /* SPI 2 reset */
#define RCC_USART3RST ((uint32_t)0x00040000) /* USART 3 reset */
#define RCC_I2C2RST   ((uint32_t)0x00400000) /* I2C 2 reset */

#define RCC_USBRST ((uint32_t)0x00800000) /* USB Device reset */

/******************  Bit definition for RCC_AHBPCENR register  ******************/
#define RCC_DMA1EN  ((uint32_t)0x0001) /* DMA1 clock enable */
#define RCC_SRAMEN  ((uint32_t)0x0004) /* SRAM interface clock enable */
#define RCC_FLITFEN ((uint32_t)0x0010) /* FLITF clock enable */
#define RCC_CRCEN   ((uint32_t)0x0040) /* CRC clock enable */
#define RCC_USBHD   ((uint32_t)0x1000)
#define RCC_USBFS   ((uint32_t)0x1000)
#define RCC_USBPD   ((uint32_t)0x20000)

/******************  Bit definition for RCC_APB2PCENR register  *****************/
#define RCC_AFIOEN ((uint32_t)0x00000001) /* Alternate Function I/O clock enable */
#define RCC_IOPAEN ((uint32_t)0x00000004) /* I/O port A clock enable */
#define RCC_IOPBEN ((uint32_t)0x00000008) /* I/O port B clock enable */
#define RCC_IOPCEN ((uint32_t)0x00000010) /* I/O port C clock enable */
#define RCC_IOPDEN ((uint32_t)0x00000020) /* I/O port D clock enable */
#define RCC_ADC1EN ((uint32_t)0x00000200) /* ADC 1 interface clock enable */

#define RCC_ADC2EN ((uint32_t)0x00000400) /* ADC 2 interface clock enable */

#define RCC_TIM1EN   ((uint32_t)0x00000800) /* TIM1 Timer clock enable */
#define RCC_SPI1EN   ((uint32_t)0x00001000) /* SPI 1 clock enable */
#define RCC_USART1EN ((uint32_t)0x00004000) /* USART1 clock enable */

/*****************  Bit definition for RCC_APB1PCENR register  ******************/
#define RCC_TIM2EN   ((uint32_t)0x00000001) /* Timer 2 clock enabled*/
#define RCC_TIM3EN   ((uint32_t)0x00000002) /* Timer 3 clock enable */
#define RCC_WWDGEN   ((uint32_t)0x00000800) /* Window Watchdog clock enable */
#define RCC_USART2EN ((uint32_t)0x00020000) /* USART 2 clock enable */
#define RCC_I2C1EN   ((uint32_t)0x00200000) /* I2C 1 clock enable */

#define RCC_BKPEN ((uint32_t)0x08000000) /* Backup interface clock enable */
#define RCC_PWREN ((uint32_t)0x10000000) /* Power interface clock enable */

#define RCC_USBEN ((uint32_t)0x00800000) /* USB Device clock enable */

/*******************  Bit definition for RCC_RSTSCKR register  ********************/
#define RCC_LSION    ((uint32_t)0x00000001) /* Internal Low Speed oscillator enable */
#define RCC_LSIRDY   ((uint32_t)0x00000002) /* Internal Low Speed oscillator Ready */
#define RCC_RMVF     ((uint32_t)0x01000000) /* Remove reset flag */
#define RCC_PINRSTF  ((uint32_t)0x04000000) /* PIN reset flag */
#define RCC_PORRSTF  ((uint32_t)0x08000000) /* POR/PDR reset flag */
#define RCC_SFTRSTF  ((uint32_t)0x10000000) /* Software Reset flag */
#define RCC_IWDGRSTF ((uint32_t)0x20000000) /* Independent Watchdog reset flag */
#define RCC_WWDGRSTF ((uint32_t)0x40000000) /* Window watchdog reset flag */
#define RCC_LPWRRSTF ((uint32_t)0x80000000) /* Low-Power reset flag */

/******************  Bit definition for RCC_AHBRSTR register  *****************/

/* HSE_configuration */
#define RCC_HSE_OFF    ((uint32_t)0x00000000)
#define RCC_HSE_ON     ((uint32_t)0x00010000)
#define RCC_HSE_BYPASS ((uint32_t)0x00040000)

/* PLL_entry_clock_source */
#define RCC_PLLSource_HSI_MUL2 ((uint32_t)0x00000000)
#define RCC_PLLSource_HSE_MUL2 ((uint32_t)0x00030000)

/* System_clock_source */
#define RCC_SYSCLKSOURCE_HSI    ((uint32_t)0x00000000)
#define RCC_SYSCLKSOURCE_HSE    ((uint32_t)0x00000001)
#define RCC_SYSCLKSOURCE_PLLCLK ((uint32_t)0x00000002)

/* AHB_clock_source */
#define RCC_SYSCLK_DIV1   ((uint32_t)0x00000000)
#define RCC_SYSCLK_DIV2   ((uint32_t)0x00000010)
#define RCC_SYSCLK_DIV3   ((uint32_t)0x00000020)
#define RCC_SYSCLK_DIV4   ((uint32_t)0x00000030)
#define RCC_SYSCLK_DIV5   ((uint32_t)0x00000040)
#define RCC_SYSCLK_DIV6   ((uint32_t)0x00000050)
#define RCC_SYSCLK_DIV7   ((uint32_t)0x00000060)
#define RCC_SYSCLK_DIV8   ((uint32_t)0x00000070)
#define RCC_SYSCLK_DIV16  ((uint32_t)0x000000B0)
#define RCC_SYSCLK_DIV32  ((uint32_t)0x000000C0)
#define RCC_SYSCLK_DIV64  ((uint32_t)0x000000D0)
#define RCC_SYSCLK_DIV128 ((uint32_t)0x000000E0)
#define RCC_SYSCLK_DIV256 ((uint32_t)0x000000F0)

/* RCC_Interrupt_source */
#define RCC_IT_LSIRDY ((uint8_t)0x01)
#define RCC_IT_HSIRDY ((uint8_t)0x04)
#define RCC_IT_HSERDY ((uint8_t)0x08)
#define RCC_IT_PLLRDY ((uint8_t)0x10)
#define RCC_IT_CSS    ((uint8_t)0x80)

/* ADC_clock_source */
#define RCC_PCLK2_DIV2   ((uint32_t)0x00000000)
#define RCC_PCLK2_DIV4   ((uint32_t)0x00004000)
#define RCC_PCLK2_DIV6   ((uint32_t)0x00008000)
#define RCC_PCLK2_DIV8   ((uint32_t)0x0000C000)
#define RCC_PCLK2_DIV12  ((uint32_t)0x0000A000)
#define RCC_PCLK2_DIV16  ((uint32_t)0x0000E000)
#define RCC_PCLK2_DIV24  ((uint32_t)0x0000A800)
#define RCC_PCLK2_DIV32  ((uint32_t)0x0000E800)
#define RCC_PCLK2_DIV48  ((uint32_t)0x0000B000)
#define RCC_PCLK2_DIV64  ((uint32_t)0x0000F000)
#define RCC_PCLK2_DIV96  ((uint32_t)0x0000B800)
#define RCC_PCLK2_DIV128 ((uint32_t)0x0000F800)

/* AHB_peripheral */
#define RCC_AHBPERIPH_DMA1 ((uint32_t)0x00000001)
#define RCC_AHBPERIPH_SRAM ((uint32_t)0x00000004)

/* APB2_peripheral */
#define RCC_APB2PERIPH_AFIO   ((uint32_t)0x00000001)
#define RCC_APB2PERIPH_GPIOA  ((uint32_t)0x00000004)
#define RCC_APB2PERIPH_GPIOC  ((uint32_t)0x00000010)
#define RCC_APB2PERIPH_GPIOD  ((uint32_t)0x00000020)
#define RCC_APB2PERIPH_ADC1   ((uint32_t)0x00000200)
#define RCC_APB2PERIPH_TIM1   ((uint32_t)0x00000800)
#define RCC_APB2PERIPH_SPI1   ((uint32_t)0x00001000)
#define RCC_APB2PERIPH_USART1 ((uint32_t)0x00004000)

/* APB1_peripheral */
#define RCC_APB1PERIPH_TIM2 ((uint32_t)0x00000001)
#define RCC_APB1PERIPH_WWDG ((uint32_t)0x00000800)
#define RCC_APB1PERIPH_I2C1 ((uint32_t)0x00200000)
#define RCC_APB1PERIPH_PWR  ((uint32_t)0x10000000)

/* Clock_source_to_output_on_MCO_pin */
#define RCC_MCO_NoClock ((uint8_t)0x00)
#define RCC_MCO_SYSCLK  ((uint8_t)0x04)
#define RCC_MCO_HSI     ((uint8_t)0x05)
#define RCC_MCO_HSE     ((uint8_t)0x06)
#define RCC_MCO_PLLCLK  ((uint8_t)0x07)

/* RCC_Flag */
#define RCC_FLAG_HSIRDY  ((uint8_t)0x21)
#define RCC_FLAG_HSERDY  ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY  ((uint8_t)0x39)
#define RCC_FLAG_LSIRDY  ((uint8_t)0x61)
#define RCC_FLAG_PINRST  ((uint8_t)0x7A)
#define RCC_FLAG_PORRST  ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST  ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST ((uint8_t)0x7F)

/* SysTick_clock_source */
#define SYSTICK_CLKSOURCE_HCLK_DIV8 ((uint32_t)0xFFFFFFFB)
#define SYSTICK_CLKSOURCE_HCLK      ((uint32_t)0x00000004)

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
