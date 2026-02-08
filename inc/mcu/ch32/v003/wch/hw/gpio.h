#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                      General Purpose Function I/O                          */
/******************************************************************************/

//------------------------------------------------------------------------------

#define GPIOA_BASE  (APB2PERIPH_BASE + 0x0800)
#define GPIOC_BASE  (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE  (APB2PERIPH_BASE + 0x1400)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define GPIO_CFGLR  0
#define GPIO_CFGHR  4
#define GPIO_INDR   8
#define GPIO_OUTDR  12
#define GPIO_BSHR   16
#define GPIO_BCR    20
#define GPIO_LCKR   24

#else

//------------------------------------------------------------------------------

/* Configuration Mode enumeration */
typedef enum {
  GPIO_MODE_AIN         = 0x0,
  GPIO_MODE_IN_FLOATING = 0x04,
  GPIO_MODE_IPD         = 0x28,
  GPIO_MODE_IPU         = 0x48,
  GPIO_MODE_OUT_OD      = 0x14,
  GPIO_MODE_OUT_PP      = 0x10,
  GPIO_MODE_AF_OD       = 0x1C,
  GPIO_MODE_AF_PP       = 0x18
} gpio_mode_t;

typedef enum {
  GPIO_CFGLR_IN_ANALOG    = 0,
  GPIO_CFGLR_IN_FLOAT     = 4,
  GPIO_CFGLR_IN_PUPD      = 8,

  GPIO_CFGLR_OUT_10_PP    = 1,
  GPIO_CFGLR_OUT_2_PP     = 2,
  GPIO_CFGLR_OUT_50_PP    = 3,
  GPIO_CFGLR_OUT_30_PP    = 3,

  GPIO_CFGLR_OUT_10_OD    = 5,
  GPIO_CFGLR_OUT_2_OD     = 6,
  GPIO_CFGLR_OUT_50_OD    = 7,
  GPIO_CFGLR_OUT_30_OD    = 7,

  GPIO_CFGLR_OUT_10_AF_PP = 9,
  GPIO_CFGLR_OUT_2_AF_PP  = 10,
  GPIO_CFGLR_OUT_50_AF_PP = 11,
  GPIO_CFGLR_OUT_30_AF_PP = 11,
  
  GPIO_CFGLR_OUT_10_AF_OD = 13,
  GPIO_CFGLR_OUT_2_AF_OD  = 14,
  GPIO_CFGLR_OUT_50_AF_OD = 15,
  GPIO_CFGLR_OUT_30_AF_OD = 15,
} gpio_cfglr_pin_mode_t;

//------------------------------------------------------------------------------

#define GPIO_PIN_CFG(p, c)  ((c) << ((p) * 4))
#define GPIO_PIN_MASK(p)    GPIO_PIN_CFG(p, 0xF)

// Input modes
#define GPIO_PIN_IN_ANALOG(p)     GPIO_PIN_CFG(p, GPIO_CFGLR_IN_ANALOG)
#define GPIO_PIN_IN_FLOAT(p)      GPIO_PIN_CFG(p, GPIO_CFGLR_IN_FLOAT)
#define GPIO_PIN_IN_PUPD(p)       GPIO_PIN_CFG(p, GPIO_CFGLR_IN_PUPD)

// Output push-pull
#define GPIO_PIN_OUT_10_PP(p)     GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_10_PP)
#define GPIO_PIN_OUT_2_PP(p)      GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_2_PP)
#define GPIO_PIN_OUT_50_PP(p)     GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_50_PP)
#define GPIO_PIN_OUT_30_PP(p)     GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_30_PP)

// Output open-drain
#define GPIO_PIN_OUT_10_OD(p)     GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_10_OD)
#define GPIO_PIN_OUT_2_OD(p)      GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_2_OD)
#define GPIO_PIN_OUT_50_OD(p)     GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_50_OD)
#define GPIO_PIN_OUT_30_OD(p)     GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_30_OD)

// Alternate function push-pull
#define GPIO_PIN_OUT_10_AF_PP(p)  GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_10_AF_PP)
#define GPIO_PIN_OUT_2_AF_PP(p)   GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_2_AF_PP)
#define GPIO_PIN_OUT_50_AF_PP(p)  GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_50_AF_PP)
#define GPIO_PIN_OUT_30_AF_PP(p)  GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_30_AF_PP)

// Alternate function open-drain
#define GPIO_PIN_OUT_10_AF_OD(p)  GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_10_AF_OD)
#define GPIO_PIN_OUT_2_AF_OD(p)   GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_2_AF_OD)
#define GPIO_PIN_OUT_50_AF_OD(p)  GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_50_AF_OD)
#define GPIO_PIN_OUT_30_AF_OD(p)  GPIO_PIN_CFG(p, GPIO_CFGLR_OUT_30_AF_OD)

//------------------------------------------------------------------------------

typedef union {
  uint32_t __FULL;
  struct {
    gpio_cfglr_pin_mode_t PIN0 : 4;
    gpio_cfglr_pin_mode_t PIN1 : 4;
    gpio_cfglr_pin_mode_t PIN2 : 4;
    gpio_cfglr_pin_mode_t PIN3 : 4;
    gpio_cfglr_pin_mode_t PIN4 : 4;
    gpio_cfglr_pin_mode_t PIN5 : 4;
    gpio_cfglr_pin_mode_t PIN6 : 4;
    gpio_cfglr_pin_mode_t PIN7 : 4;
  };
} gpio_cfglr_t;

typedef union {
  uint32_t __FULL;
  const struct {
    uint32_t IDR0 : 1;
    uint32_t IDR1 : 1;
    uint32_t IDR2 : 1;
    uint32_t IDR3 : 1;
    uint32_t IDR4 : 1;
    uint32_t IDR5 : 1;
    uint32_t IDR6 : 1;
    uint32_t IDR7 : 1;
    uint32_t : 24;
  };
} gpio_indr_t;

typedef union {
  uint32_t __FULL;
  struct {
    uint32_t ODR0 : 1;
    uint32_t ODR1 : 1;
    uint32_t ODR2 : 1;
    uint32_t ODR3 : 1;
    uint32_t ODR4 : 1;
    uint32_t ODR5 : 1;
    uint32_t ODR6 : 1;
    uint32_t ODR7 : 1;
    uint32_t : 24;
  };
} gpio_outdr_t;

typedef union {
  uint32_t __FULL;
  struct {
    uint32_t BS0 : 1;
    uint32_t BS1 : 1;
    uint32_t BS2 : 1;
    uint32_t BS3 : 1;
    uint32_t BS4 : 1;
    uint32_t BS5 : 1;
    uint32_t BS6 : 1;
    uint32_t BS7 : 1;
    uint32_t : 8;
    uint32_t BR0 : 1;
    uint32_t BR1 : 1;
    uint32_t BR2 : 1;
    uint32_t BR3 : 1;
    uint32_t BR4 : 1;
    uint32_t BR5 : 1;
    uint32_t BR6 : 1;
    uint32_t BR7 : 1;
    uint32_t : 8;
  };
} gpio_bshr_t;

typedef union {
  uint32_t __FULL;
  struct {
    uint32_t BR0 : 1;
    uint32_t BR1 : 1;
    uint32_t BR2 : 1;
    uint32_t BR3 : 1;
    uint32_t BR4 : 1;
    uint32_t BR5 : 1;
    uint32_t BR6 : 1;
    uint32_t BR7 : 1;
    uint32_t : 24;
  };
} gpio_bcr_t;

typedef union {
  uint32_t __FULL;
  struct {
    uint32_t LCK0 : 1;
    uint32_t LCK1 : 1;
    uint32_t LCK2 : 1;
    uint32_t LCK3 : 1;
    uint32_t LCK4 : 1;
    uint32_t LCK5 : 1;
    uint32_t LCK6 : 1;
    uint32_t LCK7 : 1;
    uint32_t LCKK : 1;
    uint32_t : 23;
  };
} gpio_lckr_t;

typedef struct {
  __IO uint32_t CFGLR; /* Port Configuration Register Low  */
  __IO uint32_t CFGHR; /* Port Configuration Register High */
  __I  uint32_t INDR;  /* Port Input Data Register         */
  __IO uint32_t OUTDR; /* Port Output Data Register        */
  __IO uint32_t BSHR;  /* Port Set/Reset Register          */
  __IO uint32_t BCR;   /* Port Reset Register              */
  __IO uint32_t LCKR;  /* Port Configuration Lock Register */
} gpio_t;

#define GPIOA  ((gpio_t *)GPIOA_BASE)
#define GPIOC  ((gpio_t *)GPIOC_BASE)
#define GPIOD  ((gpio_t *)GPIOD_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* MASK */
#define LSB_MASK             ((uint16_t)0xFFFF)
#define DBGAFR_POSITION_MASK ((uint32_t)0x000F0000)
#define DBGAFR_SDI_MASK      ((uint32_t)0xF8FFFFFF)
#define DBGAFR_LOCATION_MASK ((uint32_t)0x00200000)
#define DBGAFR_NUMBITS_MASK  ((uint32_t)0x00100000)

/*******************  Bit definition for GPIO_CFGLR register  *******************/
#define GPIO_CFGLR_MODE ((uint32_t)0x33333333) /* Port x mode bits */

#define GPIO_CFGLR_MODE0   ((uint32_t)0x00000003) /* MODE0[1:0] bits (Port x mode bits, pin 0) */
#define GPIO_CFGLR_MODE0_0 ((uint32_t)0x00000001) /* Bit 0 */
#define GPIO_CFGLR_MODE0_1 ((uint32_t)0x00000002) /* Bit 1 */

#define GPIO_CFGLR_MODE1   ((uint32_t)0x00000030) /* MODE1[1:0] bits (Port x mode bits, pin 1) */
#define GPIO_CFGLR_MODE1_0 ((uint32_t)0x00000010) /* Bit 0 */
#define GPIO_CFGLR_MODE1_1 ((uint32_t)0x00000020) /* Bit 1 */

#define GPIO_CFGLR_MODE2   ((uint32_t)0x00000300) /* MODE2[1:0] bits (Port x mode bits, pin 2) */
#define GPIO_CFGLR_MODE2_0 ((uint32_t)0x00000100) /* Bit 0 */
#define GPIO_CFGLR_MODE2_1 ((uint32_t)0x00000200) /* Bit 1 */

#define GPIO_CFGLR_MODE3   ((uint32_t)0x00003000) /* MODE3[1:0] bits (Port x mode bits, pin 3) */
#define GPIO_CFGLR_MODE3_0 ((uint32_t)0x00001000) /* Bit 0 */
#define GPIO_CFGLR_MODE3_1 ((uint32_t)0x00002000) /* Bit 1 */

#define GPIO_CFGLR_MODE4   ((uint32_t)0x00030000) /* MODE4[1:0] bits (Port x mode bits, pin 4) */
#define GPIO_CFGLR_MODE4_0 ((uint32_t)0x00010000) /* Bit 0 */
#define GPIO_CFGLR_MODE4_1 ((uint32_t)0x00020000) /* Bit 1 */

#define GPIO_CFGLR_MODE5   ((uint32_t)0x00300000) /* MODE5[1:0] bits (Port x mode bits, pin 5) */
#define GPIO_CFGLR_MODE5_0 ((uint32_t)0x00100000) /* Bit 0 */
#define GPIO_CFGLR_MODE5_1 ((uint32_t)0x00200000) /* Bit 1 */

#define GPIO_CFGLR_MODE6   ((uint32_t)0x03000000) /* MODE6[1:0] bits (Port x mode bits, pin 6) */
#define GPIO_CFGLR_MODE6_0 ((uint32_t)0x01000000) /* Bit 0 */
#define GPIO_CFGLR_MODE6_1 ((uint32_t)0x02000000) /* Bit 1 */

#define GPIO_CFGLR_MODE7   ((uint32_t)0x30000000) /* MODE7[1:0] bits (Port x mode bits, pin 7) */
#define GPIO_CFGLR_MODE7_0 ((uint32_t)0x10000000) /* Bit 0 */
#define GPIO_CFGLR_MODE7_1 ((uint32_t)0x20000000) /* Bit 1 */

#define GPIO_CFGLR_CNF ((uint32_t)0xCCCCCCCC) /* Port x configuration bits */

#define GPIO_CFGLR_CNF0   ((uint32_t)0x0000000C) /* CNF0[1:0] bits (Port x configuration bits, pin 0) */
#define GPIO_CFGLR_CNF0_0 ((uint32_t)0x00000004) /* Bit 0 */
#define GPIO_CFGLR_CNF0_1 ((uint32_t)0x00000008) /* Bit 1 */

#define GPIO_CFGLR_CNF1   ((uint32_t)0x000000C0) /* CNF1[1:0] bits (Port x configuration bits, pin 1) */
#define GPIO_CFGLR_CNF1_0 ((uint32_t)0x00000040) /* Bit 0 */
#define GPIO_CFGLR_CNF1_1 ((uint32_t)0x00000080) /* Bit 1 */

#define GPIO_CFGLR_CNF2   ((uint32_t)0x00000C00) /* CNF2[1:0] bits (Port x configuration bits, pin 2) */
#define GPIO_CFGLR_CNF2_0 ((uint32_t)0x00000400) /* Bit 0 */
#define GPIO_CFGLR_CNF2_1 ((uint32_t)0x00000800) /* Bit 1 */

#define GPIO_CFGLR_CNF3   ((uint32_t)0x0000C000) /* CNF3[1:0] bits (Port x configuration bits, pin 3) */
#define GPIO_CFGLR_CNF3_0 ((uint32_t)0x00004000) /* Bit 0 */
#define GPIO_CFGLR_CNF3_1 ((uint32_t)0x00008000) /* Bit 1 */

#define GPIO_CFGLR_CNF4   ((uint32_t)0x000C0000) /* CNF4[1:0] bits (Port x configuration bits, pin 4) */
#define GPIO_CFGLR_CNF4_0 ((uint32_t)0x00040000) /* Bit 0 */
#define GPIO_CFGLR_CNF4_1 ((uint32_t)0x00080000) /* Bit 1 */

#define GPIO_CFGLR_CNF5   ((uint32_t)0x00C00000) /* CNF5[1:0] bits (Port x configuration bits, pin 5) */
#define GPIO_CFGLR_CNF5_0 ((uint32_t)0x00400000) /* Bit 0 */
#define GPIO_CFGLR_CNF5_1 ((uint32_t)0x00800000) /* Bit 1 */

#define GPIO_CFGLR_CNF6   ((uint32_t)0x0C000000) /* CNF6[1:0] bits (Port x configuration bits, pin 6) */
#define GPIO_CFGLR_CNF6_0 ((uint32_t)0x04000000) /* Bit 0 */
#define GPIO_CFGLR_CNF6_1 ((uint32_t)0x08000000) /* Bit 1 */

#define GPIO_CFGLR_CNF7   ((uint32_t)0xC0000000) /* CNF7[1:0] bits (Port x configuration bits, pin 7) */
#define GPIO_CFGLR_CNF7_0 ((uint32_t)0x40000000) /* Bit 0 */
#define GPIO_CFGLR_CNF7_1 ((uint32_t)0x80000000) /* Bit 1 */

/*******************  Bit definition for GPIO_INDR register  *******************/
#define GPIO_INDR_IDR0 ((uint32_t)0x00000001) /* Port input data, bit 0 */
#define GPIO_INDR_IDR1 ((uint32_t)0x00000002) /* Port input data, bit 1 */
#define GPIO_INDR_IDR2 ((uint32_t)0x00000004) /* Port input data, bit 2 */
#define GPIO_INDR_IDR3 ((uint32_t)0x00000008) /* Port input data, bit 3 */
#define GPIO_INDR_IDR4 ((uint32_t)0x00000010) /* Port input data, bit 4 */
#define GPIO_INDR_IDR5 ((uint32_t)0x00000020) /* Port input data, bit 5 */
#define GPIO_INDR_IDR6 ((uint32_t)0x00000040) /* Port input data, bit 6 */
#define GPIO_INDR_IDR7 ((uint32_t)0x00000080) /* Port input data, bit 7 */

/*******************  Bit definition for GPIO_OUTDR register  *******************/
#define GPIO_OUTDR_ODR0 ((uint32_t)0x00000001) /* Port output data, bit 0 */
#define GPIO_OUTDR_ODR1 ((uint32_t)0x00000002) /* Port output data, bit 1 */
#define GPIO_OUTDR_ODR2 ((uint32_t)0x00000004) /* Port output data, bit 2 */
#define GPIO_OUTDR_ODR3 ((uint32_t)0x00000008) /* Port output data, bit 3 */
#define GPIO_OUTDR_ODR4 ((uint32_t)0x00000010) /* Port output data, bit 4 */
#define GPIO_OUTDR_ODR5 ((uint32_t)0x00000020) /* Port output data, bit 5 */
#define GPIO_OUTDR_ODR6 ((uint32_t)0x00000040) /* Port output data, bit 6 */
#define GPIO_OUTDR_ODR7 ((uint32_t)0x00000080) /* Port output data, bit 7 */

/******************  Bit definition for GPIO_BSHR register  *******************/
#define GPIO_BSHR_BS0 ((uint32_t)0x00000001) /* Port x Set bit 0 */
#define GPIO_BSHR_BS1 ((uint32_t)0x00000002) /* Port x Set bit 1 */
#define GPIO_BSHR_BS2 ((uint32_t)0x00000004) /* Port x Set bit 2 */
#define GPIO_BSHR_BS3 ((uint32_t)0x00000008) /* Port x Set bit 3 */
#define GPIO_BSHR_BS4 ((uint32_t)0x00000010) /* Port x Set bit 4 */
#define GPIO_BSHR_BS5 ((uint32_t)0x00000020) /* Port x Set bit 5 */
#define GPIO_BSHR_BS6 ((uint32_t)0x00000040) /* Port x Set bit 6 */
#define GPIO_BSHR_BS7 ((uint32_t)0x00000080) /* Port x Set bit 7 */

#define GPIO_BSHR_BR0 ((uint32_t)0x00010000) /* Port x Reset bit 0 */
#define GPIO_BSHR_BR1 ((uint32_t)0x00020000) /* Port x Reset bit 1 */
#define GPIO_BSHR_BR2 ((uint32_t)0x00040000) /* Port x Reset bit 2 */
#define GPIO_BSHR_BR3 ((uint32_t)0x00080000) /* Port x Reset bit 3 */
#define GPIO_BSHR_BR4 ((uint32_t)0x00100000) /* Port x Reset bit 4 */
#define GPIO_BSHR_BR5 ((uint32_t)0x00200000) /* Port x Reset bit 5 */
#define GPIO_BSHR_BR6 ((uint32_t)0x00400000) /* Port x Reset bit 6 */
#define GPIO_BSHR_BR7 ((uint32_t)0x00800000) /* Port x Reset bit 7 */

/*******************  Bit definition for GPIO_BCR register  *******************/
#define GPIO_BCR_BR0 ((uint32_t)0x00000001) /* Port x Reset bit 0 */
#define GPIO_BCR_BR1 ((uint32_t)0x00000002) /* Port x Reset bit 1 */
#define GPIO_BCR_BR2 ((uint32_t)0x00000004) /* Port x Reset bit 2 */
#define GPIO_BCR_BR3 ((uint32_t)0x00000008) /* Port x Reset bit 3 */
#define GPIO_BCR_BR4 ((uint32_t)0x00000010) /* Port x Reset bit 4 */
#define GPIO_BCR_BR5 ((uint32_t)0x00000020) /* Port x Reset bit 5 */
#define GPIO_BCR_BR6 ((uint32_t)0x00000040) /* Port x Reset bit 6 */
#define GPIO_BCR_BR7 ((uint32_t)0x00000080) /* Port x Reset bit 7 */

/******************  Bit definition for GPIO_LCKR register  *******************/
#define GPIO_LCK0 ((uint32_t)0x00000001) /* Port x Lock bit 0 */
#define GPIO_LCK1 ((uint32_t)0x00000002) /* Port x Lock bit 1 */
#define GPIO_LCK2 ((uint32_t)0x00000004) /* Port x Lock bit 2 */
#define GPIO_LCK3 ((uint32_t)0x00000008) /* Port x Lock bit 3 */
#define GPIO_LCK4 ((uint32_t)0x00000010) /* Port x Lock bit 4 */
#define GPIO_LCK5 ((uint32_t)0x00000020) /* Port x Lock bit 5 */
#define GPIO_LCK6 ((uint32_t)0x00000040) /* Port x Lock bit 6 */
#define GPIO_LCK7 ((uint32_t)0x00000080) /* Port x Lock bit 7 */
#define GPIO_LCKK ((uint32_t)0x00010000) /* Lock key */

/* GPIO_pins_define */
#define GPIO_PIN_0   ((uint16_t)0x0001) /* Pin 0 selected */
#define GPIO_PIN_1   ((uint16_t)0x0002) /* Pin 1 selected */
#define GPIO_PIN_2   ((uint16_t)0x0004) /* Pin 2 selected */
#define GPIO_PIN_3   ((uint16_t)0x0008) /* Pin 3 selected */
#define GPIO_PIN_4   ((uint16_t)0x0010) /* Pin 4 selected */
#define GPIO_PIN_5   ((uint16_t)0x0020) /* Pin 5 selected */
#define GPIO_PIN_6   ((uint16_t)0x0040) /* Pin 6 selected */
#define GPIO_PIN_7   ((uint16_t)0x0080) /* Pin 7 selected */
#define GPIO_PIN_ALL ((uint16_t)0xFFFF) /* All pins selected */

/* GPIO_Remap_define */

#define GPIO_REMAP_SPI1           ((uint32_t)0x00000001) /* SPI1 Alternate Function mapping */
#define GPIO_PARTIALREMAP_I2C1    ((uint32_t)0x10000002) /* I2C1 Partial Alternate Function mapping */
#define GPIO_FULLREMAP_I2C1       ((uint32_t)0x10400002) /* I2C1 Full Alternate Function mapping */
#define GPIO_PARTIALREMAP1_USART1 ((uint32_t)0x80000004) /* USART1 Partial1 Alternate Function mapping */
#define GPIO_PARTIALREMAP2_USART1 ((uint32_t)0x80200000) /* USART1 Partial2 Alternate Function mapping */
#define GPIO_FULLREMAP_USART1     ((uint32_t)0x80200004) /* USART1 Full Alternate Function mapping */
#define GPIO_PARTIALREMAP1_TIM1   ((uint32_t)0x00160040) /* TIM1 Partial1 Alternate Function mapping */
#define GPIO_PARTIALREMAP2_TIM1   ((uint32_t)0x00160080) /* TIM1 Partial2 Alternate Function mapping */
#define GPIO_FULLREMAP_TIM1       ((uint32_t)0x001600C0) /* TIM1 Full Alternate Function mapping */
#define GPIO_PARTIALREMAP1_TIM2   ((uint32_t)0x00180100) /* TIM2 Partial1 Alternate Function mapping */
#define GPIO_PARTIALREMAP2_TIM2   ((uint32_t)0x00180200) /* TIM2 Partial2 Alternate Function mapping */
#define GPIO_FULLREMAP_TIM2       ((uint32_t)0x00180300) /* TIM2 Full Alternate Function mapping */
#define GPIO_REMAP_PA1_2          ((uint32_t)0x00008000) /* PA1 and PA2 Alternate Function mapping */
#define GPIO_REMAP_ADC1_ETRGINJ   ((uint32_t)0x00200002) /* ADC1 External Trigger Injected Conversion remapping */
#define GPIO_REMAP_ADC1_ETRGREG   ((uint32_t)0x00200004) /* ADC1 External Trigger Regular Conversion remapping */
#define GPIO_REMAP_LSI_CAL        ((uint32_t)0x00200080) /* LSI calibration Alternate Function mapping */
#define GPIO_REMAP_SDI_DISABLE    ((uint32_t)0x00300400) /* SDI Disabled */

/* GPIO_Port_Sources */
#define GPIO_PORTSOURCE_GPIOA ((uint8_t)0x00)
#define GPIO_PORTSOURCE_GPIOC ((uint8_t)0x02)
#define GPIO_PORTSOURCE_GPIOD ((uint8_t)0x03)

/* GPIO_Pin_sources */
#define GPIO_PINSOURCE0 ((uint8_t)0x00)
#define GPIO_PINSOURCE1 ((uint8_t)0x01)
#define GPIO_PINSOURCE2 ((uint8_t)0x02)
#define GPIO_PINSOURCE3 ((uint8_t)0x03)
#define GPIO_PINSOURCE4 ((uint8_t)0x04)
#define GPIO_PINSOURCE5 ((uint8_t)0x05)
#define GPIO_PINSOURCE6 ((uint8_t)0x06)
#define GPIO_PINSOURCE7 ((uint8_t)0x07)

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
