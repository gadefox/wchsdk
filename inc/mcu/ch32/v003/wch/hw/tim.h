#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                                    TIM                                     */
/******************************************************************************/

#define TIM1_BASE  (APB2PERIPH_BASE + 0x2C00)
#define TIM2_BASE  (APB1PERIPH_BASE + 0x0000)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define TIM_CTLR1      0
#define TIM_CTLR2      4
#define TIM_SMCFGR     8
#define TIM_DMAINTENR  12
#define TIM_INTFR      16
#define TIM_SWEVGR     20
#define TIM_CHCTLR1    24
#define TIM_CHCTLR2    28
#define TIM_CCER       32
#define TIM_CNT        36
#define TIM_PSC        40
#define TIM_ATRLR      44
#define TIM_RPTCR      48
#define TIM_CH1CVR     52
#define TIM_CH2CVR     56
#define TIM_CH3CVR     60
#define TIM_CH4CVR     64
#define TIM_BDTR       68
#define TIM_DMACFGR    72
#define TIM_DMAADR     76

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint16_t CTLR1;      /* Control Register 1                       */
       uint16_t RESERVED0;
  __IO uint16_t CTLR2;      /* Control Register 2                       */
       uint16_t RESERVED1;
  __IO uint16_t SMCFGR;     /* Slave Mode Control Register              */
       uint16_t RESERVED2;
  __IO uint16_t DMAINTENR;  /* DMA/Interrupt Enable Register            */
       uint16_t RESERVED3;
  __IO uint16_t INTFR;      /* Interrupt Status Register                */
       uint16_t RESERVED4;
  __IO uint16_t SWEVGR;     /* Event Generation Register                */
       uint16_t RESERVED5;
  __IO uint16_t CHCTLR1;    /* Compare/Capture Control Register 1       */
       uint16_t RESERVED6;
  __IO uint16_t CHCTLR2;    /* Compare/Capture Control Register 2       */
       uint16_t RESERVED7;
  __IO uint16_t CCER;       /* Compare/Capture Enable Register          */
       uint16_t RESERVED8;
  __IO uint16_t CNT;        /* Counters                                 */
       uint16_t RESERVED9;
  __IO uint16_t PSC;        /* Counting Clock Prescaler                 */
       uint16_t RESERVED10;
  __IO uint16_t ATRLR;      /* Auto-reload value register               */
       uint16_t RESERVED11;
  __IO uint16_t RPTCR;      /* Recurring Count Value Register           */
       uint16_t RESERVED12;
  __IO uint32_t CH1CVR;     /* Compare/Capture Register 1               */
  __IO uint32_t CH2CVR;     /* Compare/Capture Register 2               */
  __IO uint32_t CH3CVR;     /* Compare/Capture Register 3               */
  __IO uint32_t CH4CVR;     /* Compare/Capture Register 4               */
  __IO uint16_t BDTR;       /* Brake and Deadband Registers             */
       uint16_t RESERVED13;
  __IO uint16_t DMACFGR;    /* DMA Control Register                     */
       uint16_t RESERVED14;
  __IO uint16_t DMAADR;     /* DMA Address Register For Continuous Mode */
       uint16_t RESERVED15;
} tim_t;

#define TIM1  ((tim_t *)TIM1_BASE)
#define TIM2  ((tim_t *)TIM2_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* TIM registers bit mask */
#define SMCFGR_ETR_MASK ((uint16_t)0x00FF)
#define CHCTLR_OFFSET   ((uint16_t)0x0018)
#define CCER_CCE_SET    ((uint16_t)0x0001)
#define CCER_CCNE_SET   ((uint16_t)0x0004)

/*******************  Bit definition for TIM_CTLR1 register  ********************/
#define TIM_CEN  ((uint16_t)0x0001) /* Counter enable */
#define TIM_UDIS ((uint16_t)0x0002) /* Update disable */
#define TIM_URS  ((uint16_t)0x0004) /* Update request source */
#define TIM_OPM  ((uint16_t)0x0008) /* One pulse mode */
#define TIM_DIR  ((uint16_t)0x0010) /* Direction */

#define TIM_CMS  ((uint16_t)0x0060) /* CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CMS0 ((uint16_t)0x0020) /* Bit 0 */
#define TIM_CMS1 ((uint16_t)0x0040) /* Bit 1 */

#define TIM_ARPE ((uint16_t)0x0080) /* Auto-reload preload enable */

#define TIM_CTLR1_CKD ((uint16_t)0x0300) /* CKD[1:0] bits (clock division) */
#define TIM_CKD0      ((uint16_t)0x0100) /* Bit 0 */
#define TIM_CKD1      ((uint16_t)0x0200) /* Bit 1 */

/*******************  Bit definition for TIM_CTLR2 register  ********************/
#define TIM_CCPC ((uint16_t)0x0001) /* Capture/Compare Preloaded Control */
#define TIM_CCUS ((uint16_t)0x0004) /* Capture/Compare Control Update Selection */
#define TIM_CCDS ((uint16_t)0x0008) /* Capture/Compare DMA Selection */

#define TIM_MMS  ((uint16_t)0x0070) /* MMS[2:0] bits (Master Mode Selection) */
#define TIM_MMS0 ((uint16_t)0x0010) /* Bit 0 */
#define TIM_MMS1 ((uint16_t)0x0020) /* Bit 1 */
#define TIM_MMS2 ((uint16_t)0x0040) /* Bit 2 */

#define TIM_TI1S  ((uint16_t)0x0080) /* TI1 Selection */
#define TIM_OIS1  ((uint16_t)0x0100) /* Output Idle state 1 (OC1 output) */
#define TIM_OIS1N ((uint16_t)0x0200) /* Output Idle state 1 (OC1N output) */
#define TIM_OIS2  ((uint16_t)0x0400) /* Output Idle state 2 (OC2 output) */
#define TIM_OIS2N ((uint16_t)0x0800) /* Output Idle state 2 (OC2N output) */
#define TIM_OIS3  ((uint16_t)0x1000) /* Output Idle state 3 (OC3 output) */
#define TIM_OIS3N ((uint16_t)0x2000) /* Output Idle state 3 (OC3N output) */
#define TIM_OIS4  ((uint16_t)0x4000) /* Output Idle state 4 (OC4 output) */

/*******************  Bit definition for TIM_SMCFGR register  *******************/
#define TIM_SMS  ((uint16_t)0x0007) /* SMS[2:0] bits (Slave mode selection) */
#define TIM_SMS0 ((uint16_t)0x0001) /* Bit 0 */
#define TIM_SMS1 ((uint16_t)0x0002) /* Bit 1 */
#define TIM_SMS2 ((uint16_t)0x0004) /* Bit 2 */

#define TIM_TS  ((uint16_t)0x0070) /* TS[2:0] bits (Trigger selection) */
#define TIM_TS0 ((uint16_t)0x0010) /* Bit 0 */
#define TIM_TS1 ((uint16_t)0x0020) /* Bit 1 */
#define TIM_TS2 ((uint16_t)0x0040) /* Bit 2 */

#define TIM_MSM ((uint16_t)0x0080) /* Master/slave mode */

#define TIM_ETF  ((uint16_t)0x0F00) /* ETF[3:0] bits (External trigger filter) */
#define TIM_ETF0 ((uint16_t)0x0100) /* Bit 0 */
#define TIM_ETF1 ((uint16_t)0x0200) /* Bit 1 */
#define TIM_ETF2 ((uint16_t)0x0400) /* Bit 2 */
#define TIM_ETF3 ((uint16_t)0x0800) /* Bit 3 */

#define TIM_ETPS  ((uint16_t)0x3000) /* ETPS[1:0] bits (External trigger prescaler) */
#define TIM_ETPS0 ((uint16_t)0x1000) /* Bit 0 */
#define TIM_ETPS1 ((uint16_t)0x2000) /* Bit 1 */

#define TIM_ECE ((uint16_t)0x4000) /* External clock enable */
#define TIM_ETP ((uint16_t)0x8000) /* External trigger polarity */

/*******************  Bit definition for TIM_DMAINTENR register  *******************/
#define TIM_UIE   ((uint16_t)0x0001) /* Update interrupt enable */
#define TIM_CC1IE ((uint16_t)0x0002) /* Capture/Compare 1 interrupt enable */
#define TIM_CC2IE ((uint16_t)0x0004) /* Capture/Compare 2 interrupt enable */
#define TIM_CC3IE ((uint16_t)0x0008) /* Capture/Compare 3 interrupt enable */
#define TIM_CC4IE ((uint16_t)0x0010) /* Capture/Compare 4 interrupt enable */
#define TIM_COMIE ((uint16_t)0x0020) /* COM interrupt enable */
#define TIM_TIE   ((uint16_t)0x0040) /* Trigger interrupt enable */
#define TIM_BIE   ((uint16_t)0x0080) /* Break interrupt enable */
#define TIM_UDE   ((uint16_t)0x0100) /* Update DMA request enable */
#define TIM_CC1DE ((uint16_t)0x0200) /* Capture/Compare 1 DMA request enable */
#define TIM_CC2DE ((uint16_t)0x0400) /* Capture/Compare 2 DMA request enable */
#define TIM_CC3DE ((uint16_t)0x0800) /* Capture/Compare 3 DMA request enable */
#define TIM_CC4DE ((uint16_t)0x1000) /* Capture/Compare 4 DMA request enable */
#define TIM_COMDE ((uint16_t)0x2000) /* COM DMA request enable */
#define TIM_TDE   ((uint16_t)0x4000) /* Trigger DMA request enable */

/********************  Bit definition for TIM_INTFR register  ********************/
#define TIM_UIF   ((uint16_t)0x0001) /* Update interrupt Flag */
#define TIM_CC1IF ((uint16_t)0x0002) /* Capture/Compare 1 interrupt Flag */
#define TIM_CC2IF ((uint16_t)0x0004) /* Capture/Compare 2 interrupt Flag */
#define TIM_CC3IF ((uint16_t)0x0008) /* Capture/Compare 3 interrupt Flag */
#define TIM_CC4IF ((uint16_t)0x0010) /* Capture/Compare 4 interrupt Flag */
#define TIM_COMIF ((uint16_t)0x0020) /* COM interrupt Flag */
#define TIM_TIF   ((uint16_t)0x0040) /* Trigger interrupt Flag */
#define TIM_BIF   ((uint16_t)0x0080) /* Break interrupt Flag */
#define TIM_CC1OF ((uint16_t)0x0200) /* Capture/Compare 1 Overcapture Flag */
#define TIM_CC2OF ((uint16_t)0x0400) /* Capture/Compare 2 Overcapture Flag */
#define TIM_CC3OF ((uint16_t)0x0800) /* Capture/Compare 3 Overcapture Flag */
#define TIM_CC4OF ((uint16_t)0x1000) /* Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_SWEVGR register  ********************/
#define TIM_UG   ((uint16_t)0x0001) /* Update Generation */
#define TIM_CC1G ((uint16_t)0x0002) /* Capture/Compare 1 Generation */
#define TIM_CC2G ((uint16_t)0x0004) /* Capture/Compare 2 Generation */
#define TIM_CC3G ((uint16_t)0x0008) /* Capture/Compare 3 Generation */
#define TIM_CC4G ((uint16_t)0x0010) /* Capture/Compare 4 Generation */
#define TIM_COMG ((uint16_t)0x0020) /* Capture/Compare Control Update Generation */
#define TIM_TG   ((uint16_t)0x0040) /* Trigger Generation */
#define TIM_BG   ((uint16_t)0x0080) /* Break Generation */

/******************  Bit definition for TIM_CHCTLR1 register  *******************/
#define TIM_CC1S  ((uint16_t)0x0003) /* CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CC1S0 ((uint16_t)0x0001) /* Bit 0 */
#define TIM_CC1S1 ((uint16_t)0x0002) /* Bit 1 */

#define TIM_OC1FE ((uint16_t)0x0004) /* Output Compare 1 Fast enable */
#define TIM_OC1PE ((uint16_t)0x0008) /* Output Compare 1 Preload enable */

#define TIM_OC1M  ((uint16_t)0x0070) /* OC1M[2:0] bits (Output Compare 1 Mode) */
#define TIM_OC1M0 ((uint16_t)0x0010) /* Bit 0 */
#define TIM_OC1M1 ((uint16_t)0x0020) /* Bit 1 */
#define TIM_OC1M2 ((uint16_t)0x0040) /* Bit 2 */

#define TIM_OC1CE ((uint16_t)0x0080) /* Output Compare 1Clear Enable */

#define TIM_CC2S  ((uint16_t)0x0300) /* CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CC2S0 ((uint16_t)0x0100) /* Bit 0 */
#define TIM_CC2S1 ((uint16_t)0x0200) /* Bit 1 */

#define TIM_OC2FE ((uint16_t)0x0400) /* Output Compare 2 Fast enable */
#define TIM_OC2PE ((uint16_t)0x0800) /* Output Compare 2 Preload enable */

#define TIM_OC2M  ((uint16_t)0x7000) /* OC2M[2:0] bits (Output Compare 2 Mode) */
#define TIM_OC2M0 ((uint16_t)0x1000) /* Bit 0 */
#define TIM_OC2M1 ((uint16_t)0x2000) /* Bit 1 */
#define TIM_OC2M2 ((uint16_t)0x4000) /* Bit 2 */

#define TIM_OC2CE ((uint16_t)0x8000) /* Output Compare 2 Clear Enable */

#define TIM_IC1PSC  ((uint16_t)0x000C) /* IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_IC1PSC0 ((uint16_t)0x0004) /* Bit 0 */
#define TIM_IC1PSC1 ((uint16_t)0x0008) /* Bit 1 */

#define TIM_IC1F  ((uint16_t)0x00F0) /* IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_IC1F0 ((uint16_t)0x0010) /* Bit 0 */
#define TIM_IC1F1 ((uint16_t)0x0020) /* Bit 1 */
#define TIM_IC1F2 ((uint16_t)0x0040) /* Bit 2 */
#define TIM_IC1F3 ((uint16_t)0x0080) /* Bit 3 */

#define TIM_IC2PSC  ((uint16_t)0x0C00) /* IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_IC2PSC0 ((uint16_t)0x0400) /* Bit 0 */
#define TIM_IC2PSC1 ((uint16_t)0x0800) /* Bit 1 */

#define TIM_IC2F  ((uint16_t)0xF000) /* IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_IC2F0 ((uint16_t)0x1000) /* Bit 0 */
#define TIM_IC2F1 ((uint16_t)0x2000) /* Bit 1 */
#define TIM_IC2F2 ((uint16_t)0x4000) /* Bit 2 */
#define TIM_IC2F3 ((uint16_t)0x8000) /* Bit 3 */

/******************  Bit definition for TIM_CHCTLR2 register  *******************/
#define TIM_CC3S  ((uint16_t)0x0003) /* CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CC3S0 ((uint16_t)0x0001) /* Bit 0 */
#define TIM_CC3S1 ((uint16_t)0x0002) /* Bit 1 */

#define TIM_OC3FE ((uint16_t)0x0004) /* Output Compare 3 Fast enable */
#define TIM_OC3PE ((uint16_t)0x0008) /* Output Compare 3 Preload enable */

#define TIM_OC3M  ((uint16_t)0x0070) /* OC3M[2:0] bits (Output Compare 3 Mode) */
#define TIM_OC3M0 ((uint16_t)0x0010) /* Bit 0 */
#define TIM_OC3M1 ((uint16_t)0x0020) /* Bit 1 */
#define TIM_OC3M2 ((uint16_t)0x0040) /* Bit 2 */

#define TIM_OC3CE ((uint16_t)0x0080) /* Output Compare 3 Clear Enable */

#define TIM_CC4S  ((uint16_t)0x0300) /* CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CC4S0 ((uint16_t)0x0100) /* Bit 0 */
#define TIM_CC4S1 ((uint16_t)0x0200) /* Bit 1 */

#define TIM_OC4FE ((uint16_t)0x0400) /* Output Compare 4 Fast enable */
#define TIM_OC4PE ((uint16_t)0x0800) /* Output Compare 4 Preload enable */

#define TIM_OC4M  ((uint16_t)0x7000) /* OC4M[2:0] bits (Output Compare 4 Mode) */
#define TIM_OC4M0 ((uint16_t)0x1000) /* Bit 0 */
#define TIM_OC4M1 ((uint16_t)0x2000) /* Bit 1 */
#define TIM_OC4M2 ((uint16_t)0x4000) /* Bit 2 */

#define TIM_OC4CE ((uint16_t)0x8000) /* Output Compare 4 Clear Enable */

#define TIM_IC3PSC  ((uint16_t)0x000C) /* IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_IC3PSC0 ((uint16_t)0x0004) /* Bit 0 */
#define TIM_IC3PSC1 ((uint16_t)0x0008) /* Bit 1 */

#define TIM_IC3F  ((uint16_t)0x00F0) /* IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_IC3F0 ((uint16_t)0x0010) /* Bit 0 */
#define TIM_IC3F1 ((uint16_t)0x0020) /* Bit 1 */
#define TIM_IC3F2 ((uint16_t)0x0040) /* Bit 2 */
#define TIM_IC3F3 ((uint16_t)0x0080) /* Bit 3 */

#define TIM_IC4PSC  ((uint16_t)0x0C00) /* IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_IC4PSC0 ((uint16_t)0x0400) /* Bit 0 */
#define TIM_IC4PSC1 ((uint16_t)0x0800) /* Bit 1 */

#define TIM_IC4F  ((uint16_t)0xF000) /* IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_IC4F0 ((uint16_t)0x1000) /* Bit 0 */
#define TIM_IC4F1 ((uint16_t)0x2000) /* Bit 1 */
#define TIM_IC4F2 ((uint16_t)0x4000) /* Bit 2 */
#define TIM_IC4F3 ((uint16_t)0x8000) /* Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define TIM_CC1E  ((uint16_t)0x0001) /* Capture/Compare 1 output enable */
#define TIM_CC1P  ((uint16_t)0x0002) /* Capture/Compare 1 output Polarity */
#define TIM_CC1NE ((uint16_t)0x0004) /* Capture/Compare 1 Complementary output enable */
#define TIM_CC1NP ((uint16_t)0x0008) /* Capture/Compare 1 Complementary output Polarity */
#define TIM_CC2E  ((uint16_t)0x0010) /* Capture/Compare 2 output enable */
#define TIM_CC2P  ((uint16_t)0x0020) /* Capture/Compare 2 output Polarity */
#define TIM_CC2NE ((uint16_t)0x0040) /* Capture/Compare 2 Complementary output enable */
#define TIM_CC2NP ((uint16_t)0x0080) /* Capture/Compare 2 Complementary output Polarity */
#define TIM_CC3E  ((uint16_t)0x0100) /* Capture/Compare 3 output enable */
#define TIM_CC3P  ((uint16_t)0x0200) /* Capture/Compare 3 output Polarity */
#define TIM_CC3NE ((uint16_t)0x0400) /* Capture/Compare 3 Complementary output enable */
#define TIM_CC3NP ((uint16_t)0x0800) /* Capture/Compare 3 Complementary output Polarity */
#define TIM_CC4E  ((uint16_t)0x1000) /* Capture/Compare 4 output enable */
#define TIM_CC4P  ((uint16_t)0x2000) /* Capture/Compare 4 output Polarity */
#define TIM_CC4NP ((uint16_t)0x8000) /* Capture/Compare 4 Complementary output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define TIM_CNT ((uint16_t)0xFFFF) /* Counter Value */

/*******************  Bit definition for TIM_PSC register  ********************/
#define TIM_PSC ((uint16_t)0xFFFF) /* Prescaler Value */

/*******************  Bit definition for TIM_ATRLR register  ********************/
#define TIM_ARR ((uint16_t)0xFFFF) /* actual auto-reload Value */

/*******************  Bit definition for TIM_RPTCR register  ********************/
#define TIM_REP ((uint8_t)0xFF) /* Repetition Counter Value */

/*******************  Bit definition for TIM_CH1CVR register  *******************/
#define TIM_CCR1          ((uint32_t)0x0000FFFF) /* Capture/Compare 1 Value */
#define TIM_CH1CVR_LEVEL1 ((uint32_t)0x00010000) /* The level indication bit corresponding to the captured value */

/*******************  Bit definition for TIM_CH2CVR register  *******************/
#define TIM_CCR2          ((uint32_t)0x0000FFFF) /* Capture/Compare 2 Value */
#define TIM_CH2CVR_LEVEL2 ((uint32_t)0x00010000) /* The level indication bit corresponding to the captured value */

/*******************  Bit definition for TIM_CH3CVR register  *******************/
#define TIM_CCR3          ((uint32_t)0x0000FFFF) /* Capture/Compare 3 Value */
#define TIM_CH3CVR_LEVEL3 ((uint32_t)0x00010000) /* The level indication bit corresponding to the captured value */

/*******************  Bit definition for TIM_CH4CVR register  *******************/
#define TIM_CCR4          ((uint32_t)0x0000FFFF) /* Capture/Compare 4 Value */
#define TIM_CH4CVR_LEVEL4 ((uint32_t)0x00010000) /* The level indication bit corresponding to the captured value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define TIM_DTG  ((uint16_t)0x00FF) /* DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_DTG0 ((uint16_t)0x0001) /* Bit 0 */
#define TIM_DTG1 ((uint16_t)0x0002) /* Bit 1 */
#define TIM_DTG2 ((uint16_t)0x0004) /* Bit 2 */
#define TIM_DTG3 ((uint16_t)0x0008) /* Bit 3 */
#define TIM_DTG4 ((uint16_t)0x0010) /* Bit 4 */
#define TIM_DTG5 ((uint16_t)0x0020) /* Bit 5 */
#define TIM_DTG6 ((uint16_t)0x0040) /* Bit 6 */
#define TIM_DTG7 ((uint16_t)0x0080) /* Bit 7 */

#define TIM_LOCK  ((uint16_t)0x0300) /* LOCK[1:0] bits (Lock Configuration) */
#define TIM_LOCK0 ((uint16_t)0x0100) /* Bit 0 */
#define TIM_LOCK1 ((uint16_t)0x0200) /* Bit 1 */

#define TIM_OSSI ((uint16_t)0x0400) /* Off-State Selection for Idle mode */
#define TIM_OSSR ((uint16_t)0x0800) /* Off-State Selection for Run mode */
#define TIM_BKE  ((uint16_t)0x1000) /* Break enable */
#define TIM_BKP  ((uint16_t)0x2000) /* Break Polarity */
#define TIM_AOE  ((uint16_t)0x4000) /* Automatic Output enable */
#define TIM_MOE  ((uint16_t)0x8000) /* Main Output enable */

/*******************  Bit definition for TIM_DMACFGR register  ********************/
#define TIM_DBA  ((uint16_t)0x001F) /* DBA[4:0] bits (DMA Base Address) */
#define TIM_DBA0 ((uint16_t)0x0001) /* Bit 0 */
#define TIM_DBA1 ((uint16_t)0x0002) /* Bit 1 */
#define TIM_DBA2 ((uint16_t)0x0004) /* Bit 2 */
#define TIM_DBA3 ((uint16_t)0x0008) /* Bit 3 */
#define TIM_DBA4 ((uint16_t)0x0010) /* Bit 4 */

#define TIM_DBL  ((uint16_t)0x1F00) /* DBL[4:0] bits (DMA Burst Length) */
#define TIM_DBL0 ((uint16_t)0x0100) /* Bit 0 */
#define TIM_DBL1 ((uint16_t)0x0200) /* Bit 1 */
#define TIM_DBL2 ((uint16_t)0x0400) /* Bit 2 */
#define TIM_DBL3 ((uint16_t)0x0800) /* Bit 3 */
#define TIM_DBL4 ((uint16_t)0x1000) /* Bit 4 */

/*******************  Bit definition for TIM_DMAADR register  *******************/
#define TIM_DMAR_DMAB ((uint16_t)0xFFFF) /* DMA register for burst accesses */

/* TIM_Output_Compare_and_PWM_modes */
#define TIM_OCMODE_TIMING   ((uint16_t)0x0000)
#define TIM_OCMODE_ACTIVE   ((uint16_t)0x0010)
#define TIM_OCMODE_INACTIVE ((uint16_t)0x0020)
#define TIM_OCMODE_TOGGLE   ((uint16_t)0x0030)
#define TIM_OCMODE_PWM1     ((uint16_t)0x0060)
#define TIM_OCMODE_PWM2     ((uint16_t)0x0070)

/* TIM_One_Pulse_Mode */
#define TIM_OPMODE_SINGLE     ((uint16_t)0x0008)
#define TIM_OPMODE_REPETITIVE ((uint16_t)0x0000)

/* TIM_Channel */
#define TIM_CHANNEL1 ((uint16_t)0x0000)
#define TIM_CHANNEL2 ((uint16_t)0x0004)
#define TIM_CHANNEL3 ((uint16_t)0x0008)
#define TIM_CHANNEL4 ((uint16_t)0x000C)

/* TIM_Clock_Division_CKD */
#define TIM_CKD_DIV1 ((uint16_t)0x0000)
#define TIM_CKD_DIV2 ((uint16_t)0x0100)
#define TIM_CKD_DIV4 ((uint16_t)0x0200)

/* TIM_Counter_Mode */
#define TIM_COUNTER_MODE_UP             ((uint16_t)0x0000)
#define TIM_COUNTER_MODE_DOWN           ((uint16_t)0x0010)
#define TIM_COUNTER_MODE_CENTERALIGNED1 ((uint16_t)0x0020)
#define TIM_COUNTER_MODE_CENTERALIGNED2 ((uint16_t)0x0040)
#define TIM_COUNTER_MODE_CENTERALIGNED3 ((uint16_t)0x0060)

/* TIM_Output_Compare_Polarity */
#define TIM_OCPOLARITY_HIGH ((uint16_t)0x0000)
#define TIM_OCPOLARITY_LOW  ((uint16_t)0x0002)

/* TIM_Output_Compare_N_Polarity */
#define TIM_OCNPOLARITY_HIGH ((uint16_t)0x0000)
#define TIM_OCNPOLARITY_LOW  ((uint16_t)0x0008)

/* TIM_Output_Compare_state */
#define TIM_OUTPUT_STATE_EN  ((uint16_t)0x0001)

/* TIM_Output_Compare_N_state */
#define TIM_OUTPUT_NSTATE_EN  ((uint16_t)0x0004)

/* TIM_Capture_Compare_state */
#define TIM_CCX_EN  ((uint16_t)0x0001)

/* TIM_Capture_Compare_N_state */
#define TIM_CCXN_EN  ((uint16_t)0x0004)

/* Break_Input_enable_disable */
#define TIM_BREAK_EN  ((uint16_t)0x1000)

/* Break_Polarity */
#define TIM_BREAK_POLARITY_LOW  ((uint16_t)0x0000)
#define TIM_BREAK_POLARITY_HIGH ((uint16_t)0x2000)

/* TIM_AOE_Bit_Set_Reset */
#define TIM_AUTOMATI_COUTPUT_EN  ((uint16_t)0x4000)

/* Lock_level */
#define TIM_LOCK_LEVELOFF ((uint16_t)0x0000)
#define TIM_LOCK_LEVEL1   ((uint16_t)0x0100)
#define TIM_LOCK_LEVEL2   ((uint16_t)0x0200)
#define TIM_LOCK_LEVEL3   ((uint16_t)0x0300)

/* OSSI_Off_State_Selection_for_Idle_mode_state */
#define TIM_OSSI_STATE_EN  ((uint16_t)0x0400)

/* OSSR_Off_State_Selection_for_Run_mode_state */
#define TIM_OSSR_STATE_EN  ((uint16_t)0x0800)

/* TIM_Output_Compare_Idle_State */
#define TIM_OCIDLE_STATE_SET   ((uint16_t)0x0100)

/* TIM_Output_Compare_N_Idle_State */
#define TIM_OCNIDLE_STATE_SET   ((uint16_t)0x0200)

/* TIM_Input_Capture_Polarity */
#define TIM_ICPOLARITY_RISING   ((uint16_t)0x0000)
#define TIM_ICPOLARITY_FALLING  ((uint16_t)0x0002)
#define TIM_ICPOLARITY_BOTHEDGE ((uint16_t)0x000A)

/* TIM_Input_Capture_Selection */
#define TIM_ICSELECTION_DIRECTTI ((uint16_t)0x0001)   /* TIM Input 1, 2, 3 or 4 is selected to be \
                                                         connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSELECTION_INDIRECTTI ((uint16_t)0x0002) /* TIM Input 1, 2, 3 or 4 is selected to be \
                                                         connected to IC2, IC1, IC4 or IC3, respectively. */
#define TIM_ICSELECTION_TRC ((uint16_t)0x0003)        /* TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */

/* TIM_Input_Capture_Prescaler */
#define TIM_ICPSC_DIV1 ((uint16_t)0x0000) /* Capture performed each time an edge is detected on the capture input. */
#define TIM_ICPSC_DIV2 ((uint16_t)0x0004) /* Capture performed once every 2 events. */
#define TIM_ICPSC_DIV4 ((uint16_t)0x0008) /* Capture performed once every 4 events. */
#define TIM_ICPSC_DIV8 ((uint16_t)0x000C) /* Capture performed once every 8 events. */

/* TIM_interrupt_sources */
#define TIM_IT_UPDATE  ((uint16_t)0x0001)
#define TIM_IT_CC1     ((uint16_t)0x0002)
#define TIM_IT_CC2     ((uint16_t)0x0004)
#define TIM_IT_CC3     ((uint16_t)0x0008)
#define TIM_IT_CC4     ((uint16_t)0x0010)
#define TIM_IT_COM     ((uint16_t)0x0020)
#define TIM_IT_TRIGGER ((uint16_t)0x0040)
#define TIM_IT_BREAK   ((uint16_t)0x0080)u

/* TIM_DMA_Base_address */
#define TIM_DMABASE_CR1   ((uint16_t)0x0000)
#define TIM_DMABASE_CR2   ((uint16_t)0x0001)
#define TIM_DMABASE_SMCR  ((uint16_t)0x0002)
#define TIM_DMABASE_DIER  ((uint16_t)0x0003)
#define TIM_DMABASE_SR    ((uint16_t)0x0004)
#define TIM_DMABASE_EGR   ((uint16_t)0x0005)
#define TIM_DMABASE_CCMR1 ((uint16_t)0x0006)
#define TIM_DMABASE_CCMR2 ((uint16_t)0x0007)
#define TIM_DMABASE_CCER  ((uint16_t)0x0008)
#define TIM_DMABASE_CNT   ((uint16_t)0x0009)
#define TIM_DMABASE_PSC   ((uint16_t)0x000A)
#define TIM_DMABASE_ARR   ((uint16_t)0x000B)
#define TIM_DMABASE_RCR   ((uint16_t)0x000C)
#define TIM_DMABASE_CCR1  ((uint16_t)0x000D)
#define TIM_DMABASE_CCR2  ((uint16_t)0x000E)
#define TIM_DMABASE_CCR3  ((uint16_t)0x000F)
#define TIM_DMABASE_CCR4  ((uint16_t)0x0010)
#define TIM_DMABASE_BDTR  ((uint16_t)0x0011)
#define TIM_DMABASE_DCR   ((uint16_t)0x0012)

/* TIM_DMA_Burst_Length */
#define TIM_DMABURST_LENGTH_1TRANSFER   ((uint16_t)0x0000)
#define TIM_DMABURST_LENGTH_2TRANSFERS  ((uint16_t)0x0100)
#define TIM_DMABURST_LENGTH_3TRANSFERS  ((uint16_t)0x0200)
#define TIM_DMABURST_LENGTH_4TRANSFERS  ((uint16_t)0x0300)
#define TIM_DMABURST_LENGTH_5TRANSFERS  ((uint16_t)0x0400)
#define TIM_DMABURST_LENGTH_6TRANSFERS  ((uint16_t)0x0500)
#define TIM_DMABURST_LENGTH_7TRANSFERS  ((uint16_t)0x0600)
#define TIM_DMABURST_LENGTH_8TRANSFERS  ((uint16_t)0x0700)
#define TIM_DMABURST_LENGTH_9TRANSFERS  ((uint16_t)0x0800)
#define TIM_DMABURST_LENGTH_10TRANSFERS ((uint16_t)0x0900)
#define TIM_DMABURST_LENGTH_11TRANSFERS ((uint16_t)0x0A00)
#define TIM_DMABURST_LENGTH_12TRANSFERS ((uint16_t)0x0B00)
#define TIM_DMABURST_LENGTH_13TRANSFERS ((uint16_t)0x0C00)
#define TIM_DMABURST_LENGTH_14TRANSFERS ((uint16_t)0x0D00)
#define TIM_DMABURST_LENGTH_15TRANSFERS ((uint16_t)0x0E00)
#define TIM_DMABURST_LENGTH_16TRANSFERS ((uint16_t)0x0F00)
#define TIM_DMABURST_LENGTH_17TRANSFERS ((uint16_t)0x1000)
#define TIM_DMABURST_LENGTH_18TRANSFERS ((uint16_t)0x1100)

/* TIM_DMA_sources */
#define TIM_DMA_UPDATE  ((uint16_t)0x0100)
#define TIM_DMA_CC1     ((uint16_t)0x0200)
#define TIM_DMA_CC2     ((uint16_t)0x0400)
#define TIM_DMA_CC3     ((uint16_t)0x0800)
#define TIM_DMA_CC4     ((uint16_t)0x1000)
#define TIM_DMA_COM     ((uint16_t)0x2000)
#define TIM_DMA_TRIGGER ((uint16_t)0x4000)

/* TIM_External_Trigger_Prescaler */
#define TIM_EXTTRGPSC_OFF  ((uint16_t)0x0000)
#define TIM_EXTTRGPSC_DIV2 ((uint16_t)0x1000)
#define TIM_EXTTRGPSC_DIV4 ((uint16_t)0x2000)
#define TIM_EXTTRGPSC_DIV8 ((uint16_t)0x3000)

/* TIM_Internal_Trigger_Selection */
#define TIM_TS_ITR0    ((uint16_t)0x0000)
#define TIM_TS_ITR1    ((uint16_t)0x0010)
#define TIM_TS_ITR2    ((uint16_t)0x0020)
#define TIM_TS_ITR3    ((uint16_t)0x0030)
#define TIM_TS_TI1F_ED ((uint16_t)0x0040)
#define TIM_TS_TI1FP1  ((uint16_t)0x0050)
#define TIM_TS_TI2FP2  ((uint16_t)0x0060)
#define TIM_TS_ETRF    ((uint16_t)0x0070)

/* TIM_TIx_External_Clock_Source */
#define TIM_TIXEXTERNAL_CLK1SOURCE_TI1   ((uint16_t)0x0050)
#define TIM_TIXEXTERNAL_CLK1SOURCE_TI2   ((uint16_t)0x0060)
#define TIM_TIXEXTERNAL_CLK1SOURCE_TI1ED ((uint16_t)0x0040)

/* TIM_External_Trigger_Polarity */
#define TIM_EXTTRG_POLARITY_INVERTED    ((uint16_t)0x8000)
#define TIM_EXTTRG_POLARITY_NONINVERTED ((uint16_t)0x0000)

/* TIM_Prescaler_Reload_Mode */
#define TIM_PSCRELOAD_MODE_UPDATE    ((uint16_t)0x0000)
#define TIM_PSCRELOAD_MODE_IMMEDIATE ((uint16_t)0x0001)

/* TIM_Forced_Action */
#define TIM_FORCED_ACTION_ACTIVE   ((uint16_t)0x0050)
#define TIM_FORCED_ACTION_INACTIVE ((uint16_t)0x0040)

/* TIM_Encoder_Mode */
#define TIM_ENCODER_MODE_TI1  ((uint16_t)0x0001)
#define TIM_ENCODER_MODE_TI2  ((uint16_t)0x0002)
#define TIM_ENCODER_MODE_TI12 ((uint16_t)0x0003)

/* TIM_Event_Source */
#define TIM_EVENT_SOURCE_UPDATE  ((uint16_t)0x0001)
#define TIM_EVENT_SOURCE_CC1     ((uint16_t)0x0002)
#define TIM_EVENT_SOURCE_CC2     ((uint16_t)0x0004)
#define TIM_EVENT_SOURCE_CC3     ((uint16_t)0x0008)
#define TIM_EVENT_SOURCE_CC4     ((uint16_t)0x0010)
#define TIM_EVENT_SOURCE_COM     ((uint16_t)0x0020)
#define TIM_EVENT_SOURCE_TRIGGER ((uint16_t)0x0040)
#define TIM_EVENT_SOURCE_BREAK   ((uint16_t)0x0080)

/* TIM_Update_Source */
#define TIM_UPDATESOURCE_GLOBAL ((uint16_t)0x0000)  /* Source of update is the counter overflow/underflow \
                                                       or the setting of UG bit, or an update generation  \
                                                       through the slave mode controller. */
#define TIM_UPDATESOURCE_REGULAR ((uint16_t)0x0001) /* Source of update is counter overflow/underflow. */

/* TIM_Output_Compare_Preload_State */
#define TIM_OCPRELOAD_EN  ((uint16_t)0x0008)

/* TIM_Output_Compare_Fast_State */
#define TIM_OCFAST_EN  ((uint16_t)0x0004)

/* TIM_Output_Compare_Clear_State */
#define TIM_OCCLEAR_EN  ((uint16_t)0x0080)

/* TIM_Trigger_Output_Source */
#define TIM_TRGO_SOURCE_RESET  ((uint16_t)0x0000)
#define TIM_TRGO_SOURCE_EN     ((uint16_t)0x0010)
#define TIM_TRGO_SOURCE_UPDATE ((uint16_t)0x0020)
#define TIM_TRGO_SOURCE_OC1    ((uint16_t)0x0030)
#define TIM_TRGO_SOURCE_OC1REF ((uint16_t)0x0040)
#define TIM_TRGO_SOURCE_OC2REF ((uint16_t)0x0050)
#define TIM_TRGO_SOURCE_OC3REF ((uint16_t)0x0060)
#define TIM_TRGO_SOURCE_OC4REF ((uint16_t)0x0070)

/* TIM_Slave_Mode */
#define TIM_SLAVE_MODE_RESET     ((uint16_t)0x0004)
#define TIM_SLAVE_MODE_GATED     ((uint16_t)0x0005)
#define TIM_SLAVE_MODE_TRIGGER   ((uint16_t)0x0006)
#define TIM_SLAVE_MODE_EXTERNAL1 ((uint16_t)0x0007)

/* TIM_Master_Slave_Mode */
#define TIM_MASTERSLAVE_MODE_EN  ((uint16_t)0x0080)

/* TIM_Flags */
#define TIM_FLAG_UPDATE  ((uint16_t)0x0001)
#define TIM_FLAG_CC1     ((uint16_t)0x0002)
#define TIM_FLAG_CC2     ((uint16_t)0x0004)
#define TIM_FLAG_CC3     ((uint16_t)0x0008)
#define TIM_FLAG_CC4     ((uint16_t)0x0010)
#define TIM_FLAG_COM     ((uint16_t)0x0020)
#define TIM_FLAG_TRIGGER ((uint16_t)0x0040)
#define TIM_FLAG_BREAK   ((uint16_t)0x0080)
#define TIM_FLAG_CC1OF   ((uint16_t)0x0200)
#define TIM_FLAG_CC2OF   ((uint16_t)0x0400)
#define TIM_FLAG_CC3OF   ((uint16_t)0x0800)
#define TIM_FLAG_CC4OF   ((uint16_t)0x1000)

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
