#include "wchsdk_cfg.h"

#if IO_ADC

#include "wch/io/adc.h"

//------------------------------------------------------------------------------

#ifndef IO_ADC_PREDIV
#define IO_ADC_PREDIV  RCC_ADCPRE_DIV2
#endif  /* IO_ADC_PREDIV */

//------------------------------------------------------------------------------

void adc_init(void) {
  adc_power_on();

  // Reset ADC
  adc_reset(); 

  // Clear out the bis in case they were set
  RCC->CFGR0 &= ~RCC_ADCPRE;
  RCC->CFGR0 |= IO_ADC_PREDIV;

  // Reset calibration
  ADC1->CTLR2 = CTLR2_RSTCAL_SET;
  while (ADC1->CTLR2 & CTLR2_RSTCAL_SET);

  // Calibrate
  ADC1->CTLR2 = CTLR2_CAL_SET;
  while (ADC1->CTLR2 & CTLR2_CAL_SET);

  // Set sampling time for all channels to 15 (A good middleground) ADC_SMP0_1.
  ADC1->SAMPTR1 = ADC_SMP10 | ADC_SMP11 | ADC_SMP12 | ADC_SMP13 |
                  ADC_SMP14 | ADC_SMP15 | ADC_SMP16 | ADC_SMP17;
  ADC1->SAMPTR2 = ADC_SMP0 | ADC_SMP1 | ADC_SMP2 | ADC_SMP3 | ADC_SMP4 |
                  ADC_SMP5 | ADC_SMP6 | ADC_SMP7 | ADC_SMP8 | ADC_SMP9;
  adc_enable();
}

//------------------------------------------------------------------------------

uint32_t analog_read(uint8_t pin) {
  ADC1->RSQR3 = pin;

  // Start sw conversion (auto clears)
  ADC1->CTLR2 |= ADC_SWSTART;

  // Wait for conversion complete
  while (!(ADC1->STATR & ADC_EOC));

  // Get result
  return ADC1->RDATAR;
}

//------------------------------------------------------------------------------

#endif /* IO_ADC */
