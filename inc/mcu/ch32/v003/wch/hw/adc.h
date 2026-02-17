#pragma once

#include "wch/hw/base.h"
#include "wch/hw/def.h"

/******************************************************************************/
/*                        Analog to Digital Converter                         */
/******************************************************************************/

#define ADC1_BASE  (APB2PERIPH_BASE + 0x2400)

//------------------------------------------------------------------------------

#ifdef __ASSEMBLER__

#define ADC_STATR    0
#define ADC_CTLR1    4
#define ADC_CTLR2    8
#define ADC_SAMPTR1  12
#define ADC_SAMPTR2  16
#define ADC_IOFR1    20
#define ADC_IOFR2    24
#define ADC_IOFR3    28
#define ADC_IOFR4    32
#define ADC_WDHTR    36
#define ADC_WDLTR    40
#define ADC_RSQR1    44
#define ADC_RSQR2    48
#define ADC_RSQR3    52
#define ADC_ISQR     56
#define ADC_IDATAR1  60
#define ADC_IDATAR2  64
#define ADC_IDATAR3  68
#define ADC_IDATAR4  72
#define ADC_RDATAR   76
#define ADC_DLYR     80

#else

//------------------------------------------------------------------------------

typedef struct {
  __IO uint32_t STATR;   /* ADC Status Register                         */
  __IO uint32_t CTLR1;   /* ADC Control Register 1                      */
  __IO uint32_t CTLR2;   /* ADC Control Register 2                      */
  __IO uint32_t SAMPTR1; /* ADC Sample Time Register 1                  */
  __IO uint32_t SAMPTR2; /* ADC Sample Time Register 2                  */
  __IO uint32_t IOFR1;   /* ADC Injected Channel Data Offset Register 1 */
  __IO uint32_t IOFR2;   /* ADC Injected Channel Data Offset Register 2 */
  __IO uint32_t IOFR3;   /* ADC Injected Channel Data Offset Register 3 */
  __IO uint32_t IOFR4;   /* ADC Injected Channel Data Offset Register 4 */
  __IO uint32_t WDHTR;   /* ADC Watchdog High Threshold Register        */
  __IO uint32_t WDLTR;   /* ADC Watchdog Low Threshold Register         */
  __IO uint32_t RSQR1;   /* ADC Regular Sequence Register 1             */
  __IO uint32_t RSQR2;   /* ADC Regular Sequence Register 2             */
  __IO uint32_t RSQR3;   /* ADC Regular Sequence Register 3             */
  __IO uint32_t ISQR;    /* ADC Injected Sequence Register              */
  __IO uint32_t IDATAR1; /* ADC Injected Data Register 1                */
  __IO uint32_t IDATAR2; /* ADC Injected Data Register 2                */
  __IO uint32_t IDATAR3; /* ADC Injected Data Register 3                */
  __IO uint32_t IDATAR4; /* ADC Injected Data Register 4                */
  __IO uint32_t RDATAR;  /* ADC Regular Data Register                   */
  __IO uint32_t DLYR;    /* ADC Delayed Data Register                   */
} adc_t;

#define ADC1  ((adc_t *)ADC1_BASE)

#endif  /* __ASSEMBLER__ */

//------------------------------------------------------------------------------

/* ADC_mode */
#define ADC_MODE_INDEPENDENT ((uint32_t)0x00000000)

/* ADC_external_trigger_sources_for_regular_channels_conversion */
#define ADC_EXTERNAL_TRIGCONV_T1_TRGO     ((uint32_t)0x00000000)
#define ADC_EXTERNAL_TRIGCONV_T1_CC1      ((uint32_t)0x00020000)
#define ADC_EXTERNAL_TRIGCONV_T1_CC2      ((uint32_t)0x00040000)
#define ADC_EXTERNAL_TRIGCONV_T2_TRGO     ((uint32_t)0x00060000)
#define ADC_EXTERNAL_TRIGCONV_T2_CC1      ((uint32_t)0x00080000)
#define ADC_EXTERNAL_TRIGCONV_T2_CC2      ((uint32_t)0x000A0000)
#define ADC_EXTERNAL_TRIGCONV_EXT_PD3_PC2 ((uint32_t)0x000C0000)
#define ADC_EXTERNAL_TRIGCONV_NONE        ((uint32_t)0x000E0000)

/* ADC_data_align */
#define ADC_DATAALIGN_RIGHT ((uint32_t)0x00000000)
#define ADC_DATAALIGN_LEFT  ((uint32_t)0x00000800)

/* ADC_channels */
#define ADC_CHANNEL0 ((uint8_t)0x00)
#define ADC_CHANNEL1 ((uint8_t)0x01)
#define ADC_CHANNEL2 ((uint8_t)0x02)
#define ADC_CHANNEL3 ((uint8_t)0x03)
#define ADC_CHANNEL4 ((uint8_t)0x04)
#define ADC_CHANNEL5 ((uint8_t)0x05)
#define ADC_CHANNEL6 ((uint8_t)0x06)
#define ADC_CHANNEL7 ((uint8_t)0x07)
#define ADC_CHANNEL8 ((uint8_t)0x08)
#define ADC_CHANNEL9 ((uint8_t)0x09)

#define ADC_CHANNEL_VREFINT ((uint8_t)ADC_Channel_8)
#define ADC_CHANNEL_VCALINT ((uint8_t)ADC_Channel_9)

/* ADC_sampling_time */
#define ADC_SAMPLETIME_3CYCLES   ((uint8_t)0x00)
#define ADC_SAMPLETIME_9CYCLES   ((uint8_t)0x01)
#define ADC_SAMPLETIME_15CYCLES  ((uint8_t)0x02)
#define ADC_SAMPLETIME_30CYCLES  ((uint8_t)0x03)
#define ADC_SAMPLETIME_43CYCLES  ((uint8_t)0x04)
#define ADC_SAMPLETIME_57CYCLES  ((uint8_t)0x05)
#define ADC_SAMPLETIME_73CYCLES  ((uint8_t)0x06)
#define ADC_SAMPLETIME_241CYCLES ((uint8_t)0x07)

/* ADC_external_trigger_sources_for_injected_channels_conversion */
#define ADC_EXTERNAL_TRIGINJECCONV_T1_CC3      ((uint32_t)0x00000000)
#define ADC_EXTERNAL_TRIGINJECCONV_T1_CC4      ((uint32_t)0x00001000)
#define ADC_EXTERNAL_TRIGINJECCONV_T2_CC3      ((uint32_t)0x00002000)
#define ADC_EXTERNAL_TRIGINJECCONV_T2_CC4      ((uint32_t)0x00003000)
#define ADC_EXTERNAL_TRIGINJECCONV_EXT_PD1_PA2 ((uint32_t)0x00006000)
#define ADC_EXTERNAL_TRIGINJECCONV_NONE        ((uint32_t)0x00007000)

/* ADC_injected_channel_selection */
#define ADC_INJECTED_CHANNEL1 ((uint8_t)0x14)
#define ADC_INJECTED_CHANNEL2 ((uint8_t)0x18)
#define ADC_INJECTED_CHANNEL3 ((uint8_t)0x1C)
#define ADC_INJECTED_CHANNEL4 ((uint8_t)0x20)

/* ADC_analog_watchdog_selection */
#define ADC_ANALOG_WATCHDOG_SINGLEREGENABLE        ((uint32_t)0x00800200)
#define ADC_ANALOG_WATCHDOG_SINGLEINJECENABLE      ((uint32_t)0x00400200)
#define ADC_ANALOG_WATCHDOG_SINGLEREGORINJECENABLE ((uint32_t)0x00C00200)
#define ADC_ANALOG_WATCHDOG_ALLREGENABLE           ((uint32_t)0x00800000)
#define ADC_ANALOG_WATCHDOG_ALLINJECENABLE         ((uint32_t)0x00400000)
#define ADC_ANALOG_WATCHDOG_ALLREGALLINJECENABLE   ((uint32_t)0x00C00000)
#define ADC_ANALOG_WATCHDOG_NONE                   ((uint32_t)0x00000000)

/* ADC_interrupts_definition */
#define ADC_IT_EOC  ((uint16_t)0x0220)
#define ADC_IT_AWD  ((uint16_t)0x0140)
#define ADC_IT_JEOC ((uint16_t)0x0480)

/* ADC_flags_definition */
#define ADC_FLAG_AWD   ((uint8_t)0x01)
#define ADC_FLAG_EOC   ((uint8_t)0x02)
#define ADC_FLAG_JEOC  ((uint8_t)0x04)
#define ADC_FLAG_JSTRT ((uint8_t)0x08)
#define ADC_FLAG_STRT  ((uint8_t)0x10)

/* ADC_calibration_voltage_definition */
#define ADC_CALVOL_50PERCENT ((uint32_t)0x02000000)
#define ADC_CALVOL_75PERCENT ((uint32_t)0x04000000)

/* ADC_external_trigger_sources_delay_channels_definition */
#define ADC_EXTERNAL_TRIGREGUL_DLY ((uint32_t)0x00000000)
#define ADC_EXTERNAL_TRIGINJEC_DLY ((uint32_t)0x00000200)

/* ADC DISCNUM mask */
#define CTLR1_DISCNUM_RESET ((uint32_t)0xFFFF1FFF)

/* ADC DISCEN mask */
#define CTLR1_DISCEN_SET   ((uint32_t)0x00000800)
#define CTLR1_DISCEN_RESET ((uint32_t)0xFFFFF7FF)

/* ADC JAUTO mask */
#define CTLR1_JAUTO_SET   ((uint32_t)0x00000400)
#define CTLR1_JAUTO_RESET ((uint32_t)0xFFFFFBFF)

/* ADC JDISCEN mask */
#define CTLR1_JDISCEN_SET   ((uint32_t)0x00001000)
#define CTLR1_JDISCEN_RESET ((uint32_t)0xFFFFEFFF)

/* ADC AWDCH mask */
#define CTLR1_AWDCH_RESET ((uint32_t)0xFFFFFFE0)

/* ADC Analog watchdog enable mode mask */
#define CTLR1_AWDMODE_RESET ((uint32_t)0xFF3FFDFF)

/* CTLR1 register Mask */
// NOTE:Overloaded Definition
#define ADC_CTLR1_CLEAR_MASK ((uint32_t)0xFFF0FEFF)

/* ADC ADON mask */
#define CTLR2_ADON_SET   ((uint32_t)0x00000001)
#define CTLR2_ADON_RESET ((uint32_t)0xFFFFFFFE)

/* ADC DMA mask */
#define CTLR2_DMA_SET   ((uint32_t)0x00000100)
#define CTLR2_DMA_RESET ((uint32_t)0xFFFFFEFF)

/* ADC RSTCAL mask */
#define CTLR2_RSTCAL_SET ((uint32_t)0x00000008)

/* ADC CAL mask */
#define CTLR2_CAL_SET ((uint32_t)0x00000004)

/* ADC SWSTART mask */
#define CTLR2_SWSTART_SET ((uint32_t)0x00400000)

/* ADC EXTTRIG mask */
#define CTLR2_EXTTRIG_SET   ((uint32_t)0x00100000)
#define CTLR2_EXTTRIG_RESET ((uint32_t)0xFFEFFFFF)

/* ADC Software start mask */
#define CTLR2_EXTTRIG_SWSTART_SET   ((uint32_t)0x00500000)
#define CTLR2_EXTTRIG_SWSTART_RESET ((uint32_t)0xFFAFFFFF)

/* ADC JEXTSEL mask */
#define CTLR2_JEXTSEL_RESET ((uint32_t)0xFFFF8FFF)

/* ADC JEXTTRIG mask */
#define CTLR2_JEXTTRIG_SET   ((uint32_t)0x00008000)
#define CTLR2_JEXTTRIG_RESET ((uint32_t)0xFFFF7FFF)

/* ADC JSWSTART mask */
#define CTLR2_JSWSTART_SET ((uint32_t)0x00200000)

/* ADC injected software start mask */
#define CTLR2_JEXTTRIG_JSWSTART_SET   ((uint32_t)0x00208000)
#define CTLR2_JEXTTRIG_JSWSTART_RESET ((uint32_t)0xFFDF7FFF)

/* ADC TSPD mask */
#define CTLR2_TSVREFE_SET   ((uint32_t)0x00800000)
#define CTLR2_TSVREFE_RESET ((uint32_t)0xFF7FFFFF)

/* CTLR2 register Mask */
#define CTLR2_CLEAR_MASK ((uint32_t)0xFFF1F7FD)

/* ADC SQx mask */
#define RSQR3_SQ_SET ((uint32_t)0x0000001F)
#define RSQR2_SQ_SET ((uint32_t)0x0000001F)
#define RSQR1_SQ_SET ((uint32_t)0x0000001F)

/* RSQR1 register Mask */
#define RSQR1_CLEAR_MASK ((uint32_t)0xFF0FFFFF)

/* ADC JSQx mask */
#define ISQR_JSQ_SET ((uint32_t)0x0000001F)

/* ADC JL mask */
#define ISQR_JL_SET   ((uint32_t)0x00300000)
#define ISQR_JL_RESET ((uint32_t)0xFFCFFFFF)

/* ADC SMPx mask */
#define SAMPTR1_SMP_SET ((uint32_t)0x00000007)
#define SAMPTR2_SMP_SET ((uint32_t)0x00000007)

/* ADC IDATARx registers offset */
#define IDATAR_OFFSET ((uint8_t)0x28)

/********************  Bit definition for ADC_STATR register *********************/
#define ADC_AWD   ((uint32_t)0x00000001) /* Analog watchdog flag */
#define ADC_EOC   ((uint32_t)0x00000002) /* End of conversion */
#define ADC_JEOC  ((uint32_t)0x00000004) /* Injected channel end of conversion */
#define ADC_JSTRT ((uint32_t)0x00000008) /* Injected channel Start flag */
#define ADC_STRT  ((uint32_t)0x00000010) /* Regular channel Start flag */

/*******************  Bit definition for ADC_CTLR1 register *********************/
#define ADC_AWDCH  ((uint32_t)0x0000001F) /* AWDCH[4:0] bits (Analog watchdog channel select bits) */
#define ADC_AWDCH0 ((uint32_t)0x00000001) /* Bit 0 */
#define ADC_AWDCH1 ((uint32_t)0x00000002) /* Bit 1 */
#define ADC_AWDCH2 ((uint32_t)0x00000004) /* Bit 2 */
#define ADC_AWDCH3 ((uint32_t)0x00000008) /* Bit 3 */
#define ADC_AWDCH4 ((uint32_t)0x00000010) /* Bit 4 */

#define ADC_EOCIE   ((uint32_t)0x00000020) /* Interrupt enable for EOC */
#define ADC_AWDIE   ((uint32_t)0x00000040) /* Analog Watchdog interrupt enable */
#define ADC_JEOCIE  ((uint32_t)0x00000080) /* Interrupt enable for injected channels */
#define ADC_SCAN    ((uint32_t)0x00000100) /* Scan mode */
#define ADC_AWDSGL  ((uint32_t)0x00000200) /* Enable the watchdog on a single channel in scan mode */
#define ADC_JAUTO   ((uint32_t)0x00000400) /* Automatic injected group conversion */
#define ADC_DISCEN  ((uint32_t)0x00000800) /* Discontinuous mode on regular channels */
#define ADC_JDISCEN ((uint32_t)0x00001000) /* Discontinuous mode on injected channels */

#define ADC_DISCNUM  ((uint32_t)0x0000E000) /* DISCNUM[2:0] bits (Discontinuous mode channel count) */
#define ADC_DISCNUM0 ((uint32_t)0x00002000) /* Bit 0 */
#define ADC_DISCNUM1 ((uint32_t)0x00004000) /* Bit 1 */
#define ADC_DISCNUM2 ((uint32_t)0x00008000) /* Bit 2 */

#define ADC_JAWDEN        ((uint32_t)0x00400000) /* Analog watchdog enable on injected channels */
#define ADC_AWDEN         ((uint32_t)0x00800000) /* Analog watchdog enable on regular channels */
#define ADC_CALVOLSELECT  ((uint32_t)0x06000000)
#define ADC_CALVOLSELECT0 ((uint32_t)0x02000000)
#define ADC_CALVOLSELECT1 ((uint32_t)0x04000000)

/*******************  Bit definition for ADC_CTLR2 register *********************/
#define ADC_ADON   ((uint32_t)0x00000001) /* A/D Converter ON / OFF */
#define ADC_CONT   ((uint32_t)0x00000002) /* Continuous Conversion */
#define ADC_CAL    ((uint32_t)0x00000004) /* A/D Calibration */
#define ADC_RSTCAL ((uint32_t)0x00000008) /* Reset Calibration */
#define ADC_DMA    ((uint32_t)0x00000100) /* Direct Memory access mode */
#define ADC_ALIGN  ((uint32_t)0x00000800) /* Data Alignment */

#define ADC_JEXTSEL  ((uint32_t)0x00007000) /* JEXTSEL[2:0] bits (External event select for injected group) */
#define ADC_JEXTSEL0 ((uint32_t)0x00001000) /* Bit 0 */
#define ADC_JEXTSEL1 ((uint32_t)0x00002000) /* Bit 1 */
#define ADC_JEXTSEL2 ((uint32_t)0x00004000) /* Bit 2 */

#define ADC_JEXTTRIG ((uint32_t)0x00008000) /* External Trigger Conversion mode for injected channels */

#define ADC_EXTSEL  ((uint32_t)0x000E0000) /* EXTSEL[2:0] bits (External Event Select for regular group) */
#define ADC_EXTSEL0 ((uint32_t)0x00020000) /* Bit 0 */
#define ADC_EXTSEL1 ((uint32_t)0x00040000) /* Bit 1 */
#define ADC_EXTSEL2 ((uint32_t)0x00080000) /* Bit 2 */

#define ADC_EXTTRIG  ((uint32_t)0x00100000) /* External Trigger Conversion mode for regular channels */
#define ADC_JSWSTART ((uint32_t)0x00200000) /* Start Conversion of injected channels */
#define ADC_SWSTART  ((uint32_t)0x00400000) /* Start Conversion of regular channels */
#define ADC_TSVREFE  ((uint32_t)0x00800000) /* Temperature Sensor and VREFINT Enable */

/******************  Bit definition for ADC_SAMPTR1 register ********************/
#define ADC_SMP10   ((uint32_t)0x00000007) /* SMP10[2:0] bits (Channel 10 Sample time selection) */
#define ADC_SMP10_0 ((uint32_t)0x00000001) /* Bit 0 */
#define ADC_SMP10_1 ((uint32_t)0x00000002) /* Bit 1 */
#define ADC_SMP10_2 ((uint32_t)0x00000004) /* Bit 2 */

#define ADC_SMP11   ((uint32_t)0x00000038) /* SMP11[2:0] bits (Channel 11 Sample time selection) */
#define ADC_SMP11_0 ((uint32_t)0x00000008) /* Bit 0 */
#define ADC_SMP11_1 ((uint32_t)0x00000010) /* Bit 1 */
#define ADC_SMP11_2 ((uint32_t)0x00000020) /* Bit 2 */

#define ADC_SMP12   ((uint32_t)0x000001C0) /* SMP12[2:0] bits (Channel 12 Sample time selection) */
#define ADC_SMP12_0 ((uint32_t)0x00000040) /* Bit 0 */
#define ADC_SMP12_1 ((uint32_t)0x00000080) /* Bit 1 */
#define ADC_SMP12_2 ((uint32_t)0x00000100) /* Bit 2 */

#define ADC_SMP13   ((uint32_t)0x00000E00) /* SMP13[2:0] bits (Channel 13 Sample time selection) */
#define ADC_SMP13_0 ((uint32_t)0x00000200) /* Bit 0 */
#define ADC_SMP13_1 ((uint32_t)0x00000400) /* Bit 1 */
#define ADC_SMP13_2 ((uint32_t)0x00000800) /* Bit 2 */

#define ADC_SMP14   ((uint32_t)0x00007000) /* SMP14[2:0] bits (Channel 14 Sample time selection) */
#define ADC_SMP14_0 ((uint32_t)0x00001000) /* Bit 0 */
#define ADC_SMP14_1 ((uint32_t)0x00002000) /* Bit 1 */
#define ADC_SMP14_2 ((uint32_t)0x00004000) /* Bit 2 */

#define ADC_SMP15   ((uint32_t)0x00038000) /* SMP15[2:0] bits (Channel 15 Sample time selection) */
#define ADC_SMP15_0 ((uint32_t)0x00008000) /* Bit 0 */
#define ADC_SMP15_1 ((uint32_t)0x00010000) /* Bit 1 */
#define ADC_SMP15_2 ((uint32_t)0x00020000) /* Bit 2 */

#define ADC_SMP16   ((uint32_t)0x001C0000) /* SMP16[2:0] bits (Channel 16 Sample time selection) */
#define ADC_SMP16_0 ((uint32_t)0x00040000) /* Bit 0 */
#define ADC_SMP16_1 ((uint32_t)0x00080000) /* Bit 1 */
#define ADC_SMP16_2 ((uint32_t)0x00100000) /* Bit 2 */

#define ADC_SMP17   ((uint32_t)0x00E00000) /* SMP17[2:0] bits (Channel 17 Sample time selection) */
#define ADC_SMP17_0 ((uint32_t)0x00200000) /* Bit 0 */
#define ADC_SMP17_1 ((uint32_t)0x00400000) /* Bit 1 */
#define ADC_SMP17_2 ((uint32_t)0x00800000) /* Bit 2 */

/******************  Bit definition for ADC_SAMPTR2 register ********************/
#define ADC_SMP0   ((uint32_t)0x00000007) /* SMP0[2:0] bits (Channel 0 Sample time selection) */
#define ADC_SMP0_0 ((uint32_t)0x00000001) /* Bit 0 */
#define ADC_SMP0_1 ((uint32_t)0x00000002) /* Bit 1 */
#define ADC_SMP0_2 ((uint32_t)0x00000004) /* Bit 2 */

#define ADC_SMP1   ((uint32_t)0x00000038) /* SMP1[2:0] bits (Channel 1 Sample time selection) */
#define ADC_SMP1_0 ((uint32_t)0x00000008) /* Bit 0 */
#define ADC_SMP1_1 ((uint32_t)0x00000010) /* Bit 1 */
#define ADC_SMP1_2 ((uint32_t)0x00000020) /* Bit 2 */

#define ADC_SMP2   ((uint32_t)0x000001C0) /* SMP2[2:0] bits (Channel 2 Sample time selection) */
#define ADC_SMP2_0 ((uint32_t)0x00000040) /* Bit 0 */
#define ADC_SMP2_1 ((uint32_t)0x00000080) /* Bit 1 */
#define ADC_SMP2_2 ((uint32_t)0x00000100) /* Bit 2 */

#define ADC_SMP3   ((uint32_t)0x00000E00) /* SMP3[2:0] bits (Channel 3 Sample time selection) */
#define ADC_SMP3_0 ((uint32_t)0x00000200) /* Bit 0 */
#define ADC_SMP3_1 ((uint32_t)0x00000400) /* Bit 1 */
#define ADC_SMP3_2 ((uint32_t)0x00000800) /* Bit 2 */

#define ADC_SMP4   ((uint32_t)0x00007000) /* SMP4[2:0] bits (Channel 4 Sample time selection) */
#define ADC_SMP4_0 ((uint32_t)0x00001000) /* Bit 0 */
#define ADC_SMP4_1 ((uint32_t)0x00002000) /* Bit 1 */
#define ADC_SMP4_2 ((uint32_t)0x00004000) /* Bit 2 */

#define ADC_SMP5   ((uint32_t)0x00038000) /* SMP5[2:0] bits (Channel 5 Sample time selection) */
#define ADC_SMP5_0 ((uint32_t)0x00008000) /* Bit 0 */
#define ADC_SMP5_1 ((uint32_t)0x00010000) /* Bit 1 */
#define ADC_SMP5_2 ((uint32_t)0x00020000) /* Bit 2 */

#define ADC_SMP6   ((uint32_t)0x001C0000) /* SMP6[2:0] bits (Channel 6 Sample time selection) */
#define ADC_SMP6_0 ((uint32_t)0x00040000) /* Bit 0 */
#define ADC_SMP6_1 ((uint32_t)0x00080000) /* Bit 1 */
#define ADC_SMP6_2 ((uint32_t)0x00100000) /* Bit 2 */

#define ADC_SMP7   ((uint32_t)0x00E00000)                    /* SMP7[2:0] bits (Channel 7 Sample time selection) */
#define ADC_SMP7_0 ((uint32_t)0x00200000) /* Bit 0 */
#define ADC_SMP7_1 ((uint32_t)0x00400000) /* Bit 1 */
#define ADC_SMP7_2 ((uint32_t)0x00800000) /* Bit 2 */

#define ADC_SMP8   ((uint32_t)0x07000000) /* SMP8[2:0] bits (Channel 8 Sample time selection) */
#define ADC_SMP8_0 ((uint32_t)0x01000000) /* Bit 0 */
#define ADC_SMP8_1 ((uint32_t)0x02000000) /* Bit 1 */
#define ADC_SMP8_2 ((uint32_t)0x04000000) /* Bit 2 */

#define ADC_SMP9   ((uint32_t)0x38000000) /* SMP9[2:0] bits (Channel 9 Sample time selection) */
#define ADC_SMP9_0 ((uint32_t)0x08000000) /* Bit 0 */
#define ADC_SMP9_1 ((uint32_t)0x10000000) /* Bit 1 */
#define ADC_SMP9_2 ((uint32_t)0x20000000) /* Bit 2 */

/******************  Bit definition for ADC_IOFR1 register  *******************/
#define ADC_JOFFSET1 ((uint32_t)0x000002FF) /* Data offset for injected channel 1 */

/******************  Bit definition for ADC_IOFR2 register  *******************/
#define ADC_JOFFSET2 ((uint32_t)0x000002FF) /* Data offset for injected channel 2 */

/******************  Bit definition for ADC_IOFR3 register  *******************/
#define ADC_JOFFSET3 ((uint32_t)0x000002FF) /* Data offset for injected channel 3 */

/******************  Bit definition for ADC_IOFR4 register  *******************/
#define ADC_JOFFSET4 ((uint32_t)0x000002FF) /* Data offset for injected channel 4 */

/*******************  Bit definition for ADC_WDHTR register *********************/
#define ADC_HT ((uint32_t)0x000002FF) /* Analog watchdog high threshold */

/*******************  Bit definition for ADC_WDLTR register *********************/
#define ADC_LT ((uint32_t)0x000002FF) /* Analog watchdog low threshold */

/*******************  Bit definition for ADC_RSQR1 register *******************/
#define ADC_SQ13   ((uint32_t)0x0000001F) /* SQ13[4:0] bits (13th conversion in regular sequence) */
#define ADC_SQ13_0 ((uint32_t)0x00000001) /* Bit 0 */
#define ADC_SQ13_1 ((uint32_t)0x00000002) /* Bit 1 */
#define ADC_SQ13_2 ((uint32_t)0x00000004) /* Bit 2 */
#define ADC_SQ13_3 ((uint32_t)0x00000008) /* Bit 3 */
#define ADC_SQ13_4 ((uint32_t)0x00000010) /* Bit 4 */

#define ADC_SQ14   ((uint32_t)0x000003E0) /* SQ14[4:0] bits (14th conversion in regular sequence) */
#define ADC_SQ14_0 ((uint32_t)0x00000020) /* Bit 0 */
#define ADC_SQ14_1 ((uint32_t)0x00000040) /* Bit 1 */
#define ADC_SQ14_2 ((uint32_t)0x00000080) /* Bit 2 */
#define ADC_SQ14_3 ((uint32_t)0x00000100) /* Bit 3 */
#define ADC_SQ14_4 ((uint32_t)0x00000200) /* Bit 4 */

#define ADC_SQ15   ((uint32_t)0x00007C00) /* SQ15[4:0] bits (15th conversion in regular sequence) */
#define ADC_SQ15_0 ((uint32_t)0x00000400) /* Bit 0 */
#define ADC_SQ15_1 ((uint32_t)0x00000800) /* Bit 1 */
#define ADC_SQ15_2 ((uint32_t)0x00001000) /* Bit 2 */
#define ADC_SQ15_3 ((uint32_t)0x00002000) /* Bit 3 */
#define ADC_SQ15_4 ((uint32_t)0x00004000) /* Bit 4 */

#define ADC_SQ16   ((uint32_t)0x000F8000) /* SQ16[4:0] bits (16th conversion in regular sequence) */
#define ADC_SQ16_0 ((uint32_t)0x00008000) /* Bit 0 */
#define ADC_SQ16_1 ((uint32_t)0x00010000) /* Bit 1 */
#define ADC_SQ16_2 ((uint32_t)0x00020000) /* Bit 2 */
#define ADC_SQ16_3 ((uint32_t)0x00040000) /* Bit 3 */
#define ADC_SQ16_4 ((uint32_t)0x00080000) /* Bit 4 */

#define ADC_L  ((uint32_t)0x00F00000) /* L[3:0] bits (Regular channel sequence length) */
#define ADC_L0 ((uint32_t)0x00100000) /* Bit 0 */
#define ADC_L1 ((uint32_t)0x00200000) /* Bit 1 */
#define ADC_L2 ((uint32_t)0x00400000) /* Bit 2 */
#define ADC_L3 ((uint32_t)0x00800000) /* Bit 3 */

/*******************  Bit definition for ADC_RSQR2 register *******************/
#define ADC_SQ7  ((uint32_t)0x0000001F) /* SQ7[4:0] bits (7th conversion in regular sequence) */
#define ADC_SQ7_0 ((uint32_t)0x00000001) /* Bit 0 */
#define ADC_SQ7_1 ((uint32_t)0x00000002) /* Bit 1 */
#define ADC_SQ7_2 ((uint32_t)0x00000004) /* Bit 2 */
#define ADC_SQ7_3 ((uint32_t)0x00000008) /* Bit 3 */
#define ADC_SQ7_4 ((uint32_t)0x00000010) /* Bit 4 */

#define ADC_SQ8   ((uint32_t)0x000003E0) /* SQ8[4:0] bits (8th conversion in regular sequence) */
#define ADC_SQ8_0 ((uint32_t)0x00000020) /* Bit 0 */
#define ADC_SQ8_1 ((uint32_t)0x00000040) /* Bit 1 */
#define ADC_SQ8_2 ((uint32_t)0x00000080) /* Bit 2 */
#define ADC_SQ8_3 ((uint32_t)0x00000100) /* Bit 3 */
#define ADC_SQ8_4 ((uint32_t)0x00000200) /* Bit 4 */

#define ADC_SQ9   ((uint32_t)0x00007C00) /* SQ9[4:0] bits (9th conversion in regular sequence) */
#define ADC_SQ9_0 ((uint32_t)0x00000400) /* Bit 0 */
#define ADC_SQ9_1 ((uint32_t)0x00000800) /* Bit 1 */
#define ADC_SQ9_2 ((uint32_t)0x00001000) /* Bit 2 */
#define ADC_SQ9_3 ((uint32_t)0x00002000) /* Bit 3 */
#define ADC_SQ9_4 ((uint32_t)0x00004000) /* Bit 4 */

#define ADC_SQ10   ((uint32_t)0x000F8000) /* SQ10[4:0] bits (10th conversion in regular sequence) */
#define ADC_SQ10_0 ((uint32_t)0x00008000) /* Bit 0 */
#define ADC_SQ10_1 ((uint32_t)0x00010000) /* Bit 1 */
#define ADC_SQ10_2 ((uint32_t)0x00020000) /* Bit 2 */
#define ADC_SQ10_3 ((uint32_t)0x00040000) /* Bit 3 */
#define ADC_SQ10_4 ((uint32_t)0x00080000) /* Bit 4 */

#define ADC_SQ11   ((uint32_t)0x01F00000) /* SQ11[4:0] bits (11th conversion in regular sequence) */
#define ADC_SQ11_0 ((uint32_t)0x00100000) /* Bit 0 */
#define ADC_SQ11_1 ((uint32_t)0x00200000) /* Bit 1 */
#define ADC_SQ11_2 ((uint32_t)0x00400000) /* Bit 2 */
#define ADC_SQ11_3 ((uint32_t)0x00800000) /* Bit 3 */
#define ADC_SQ11_4 ((uint32_t)0x01000000) /* Bit 4 */

#define ADC_SQ12   ((uint32_t)0x3E000000) /* SQ12[4:0] bits (12th conversion in regular sequence) */
#define ADC_SQ12_0 ((uint32_t)0x02000000) /* Bit 0 */
#define ADC_SQ12_1 ((uint32_t)0x04000000) /* Bit 1 */
#define ADC_SQ12_2 ((uint32_t)0x08000000) /* Bit 2 */
#define ADC_SQ12_3 ((uint32_t)0x10000000) /* Bit 3 */
#define ADC_SQ12_4 ((uint32_t)0x20000000) /* Bit 4 */

/*******************  Bit definition for ADC_RSQR3 register *******************/
#define ADC_SQ1   ((uint32_t)0x0000001F) /* SQ1[4:0] bits (1st conversion in regular sequence) */
#define ADC_SQ1_0 ((uint32_t)0x00000001) /* Bit 0 */
#define ADC_SQ1_1 ((uint32_t)0x00000002) /* Bit 1 */
#define ADC_SQ1_2 ((uint32_t)0x00000004) /* Bit 2 */
#define ADC_SQ1_3 ((uint32_t)0x00000008) /* Bit 3 */
#define ADC_SQ1_4 ((uint32_t)0x00000010) /* Bit 4 */

#define ADC_SQ2   ((uint32_t)0x000003E0) /* SQ2[4:0] bits (2nd conversion in regular sequence) */
#define ADC_SQ2_0 ((uint32_t)0x00000020) /* Bit 0 */
#define ADC_SQ2_1 ((uint32_t)0x00000040) /* Bit 1 */
#define ADC_SQ2_2 ((uint32_t)0x00000080) /* Bit 2 */
#define ADC_SQ2_3 ((uint32_t)0x00000100) /* Bit 3 */
#define ADC_SQ2_4 ((uint32_t)0x00000200) /* Bit 4 */

#define ADC_SQ3   ((uint32_t)0x00007C00) /* SQ3[4:0] bits (3rd conversion in regular sequence) */
#define ADC_SQ3_0 ((uint32_t)0x00000400) /* Bit 0 */
#define ADC_SQ3_1 ((uint32_t)0x00000800) /* Bit 1 */
#define ADC_SQ3_2 ((uint32_t)0x00001000) /* Bit 2 */
#define ADC_SQ3_3 ((uint32_t)0x00002000) /* Bit 3 */
#define ADC_SQ3_4 ((uint32_t)0x00004000) /* Bit 4 */

#define ADC_SQ4   ((uint32_t)0x000F8000) /* SQ4[4:0] bits (4th conversion in regular sequence) */
#define ADC_SQ4_0 ((uint32_t)0x00008000) /* Bit 0 */
#define ADC_SQ4_1 ((uint32_t)0x00010000) /* Bit 1 */
#define ADC_SQ4_2 ((uint32_t)0x00020000) /* Bit 2 */
#define ADC_SQ4_3 ((uint32_t)0x00040000) /* Bit 3 */
#define ADC_SQ4_4 ((uint32_t)0x00080000) /* Bit 4 */

#define ADC_SQ5   ((uint32_t)0x01F00000) /* SQ5[4:0] bits (5th conversion in regular sequence) */
#define ADC_SQ5_0 ((uint32_t)0x00100000) /* Bit 0 */
#define ADC_SQ5_1 ((uint32_t)0x00200000) /* Bit 1 */
#define ADC_SQ5_2 ((uint32_t)0x00400000) /* Bit 2 */
#define ADC_SQ5_3 ((uint32_t)0x00800000) /* Bit 3 */
#define ADC_SQ5_4 ((uint32_t)0x01000000) /* Bit 4 */

#define ADC_SQ6   ((uint32_t)0x3E000000) /* SQ6[4:0] bits (6th conversion in regular sequence) */
#define ADC_SQ6_0 ((uint32_t)0x02000000) /* Bit 0 */
#define ADC_SQ6_1 ((uint32_t)0x04000000) /* Bit 1 */
#define ADC_SQ6_2 ((uint32_t)0x08000000) /* Bit 2 */
#define ADC_SQ6_3 ((uint32_t)0x10000000) /* Bit 3 */
#define ADC_SQ6_4 ((uint32_t)0x20000000) /* Bit 4 */

/*******************  Bit definition for ADC_ISQR register  *******************/
#define ADC_JSQ1   ((uint32_t)0x0000001F) /* JSQ1[4:0] bits (1st conversion in injected sequence) */
#define ADC_JSQ1_0 ((uint32_t)0x00000001) /* Bit 0 */
#define ADC_JSQ1_1 ((uint32_t)0x00000002) /* Bit 1 */
#define ADC_JSQ1_2 ((uint32_t)0x00000004) /* Bit 2 */
#define ADC_JSQ1_3 ((uint32_t)0x00000008) /* Bit 3 */
#define ADC_JSQ1_4 ((uint32_t)0x00000010) /* Bit 4 */

#define ADC_JSQ2   ((uint32_t)0x000003E0) /* JSQ2[4:0] bits (2nd conversion in injected sequence) */
#define ADC_JSQ2_0 ((uint32_t)0x00000020) /* Bit 0 */
#define ADC_JSQ2_1 ((uint32_t)0x00000040) /* Bit 1 */
#define ADC_JSQ2_2 ((uint32_t)0x00000080) /* Bit 2 */
#define ADC_JSQ2_3 ((uint32_t)0x00000100) /* Bit 3 */
#define ADC_JSQ2_4 ((uint32_t)0x00000200) /* Bit 4 */

#define ADC_JSQ3   ((uint32_t)0x00007C00) /* JSQ3[4:0] bits (3rd conversion in injected sequence) */
#define ADC_JSQ3_0 ((uint32_t)0x00000400) /* Bit 0 */
#define ADC_JSQ3_1 ((uint32_t)0x00000800) /* Bit 1 */
#define ADC_JSQ3_2 ((uint32_t)0x00001000) /* Bit 2 */
#define ADC_JSQ3_3 ((uint32_t)0x00002000) /* Bit 3 */
#define ADC_JSQ3_4 ((uint32_t)0x00004000) /* Bit 4 */

#define ADC_JSQ4   ((uint32_t)0x000F8000) /* JSQ4[4:0] bits (4th conversion in injected sequence) */
#define ADC_JSQ4_0 ((uint32_t)0x00008000) /* Bit 0 */
#define ADC_JSQ4_1 ((uint32_t)0x00010000) /* Bit 1 */
#define ADC_JSQ4_2 ((uint32_t)0x00020000) /* Bit 2 */
#define ADC_JSQ4_3 ((uint32_t)0x00040000) /* Bit 3 */
#define ADC_JSQ4_4 ((uint32_t)0x00080000) /* Bit 4 */

#define ADC_JL  ((uint32_t)0x00300000) /* JL[1:0] bits (Injected Sequence length) */
#define ADC_JL0 ((uint32_t)0x00100000) /* Bit 0 */
#define ADC_JL1 ((uint32_t)0x00200000) /* Bit 1 */

/********************  Bit definition for ADC_RDATAR register *********************/
#define ADC_RDATAR_DATA     ((uint32_t)0x0000FFFF) /* Regular data */
#define ADC_RDATAR_ADC2DATA ((uint32_t)0xFFFF0000) /* ADC2 data */

/********************  Bit definition for ADC_DLYR register *********************/
#define ADC_DLYR_DLYVLU ((uint32_t)0x000001FF)
#define ADC_DLYR_DLYSRC ((uint32_t)0x00000200)

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
