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
  ADC1->CTLR2 = ADC_RSTCAL;
  while (ADC1->CTLR2 & ADC_RSTCAL);

  // Calibrate
  ADC1->CTLR2 = ADC_CAL;
  while (ADC1->CTLR2 & ADC_CAL);

  // Set sampling time for all channels to ADC_SMP_241CYCLES
  ADC1->SAMPTR[0] = ADC_SMP;
  ADC1->SAMPTR[1] = ADC_SMP;

  adc_enable();
}

//------------------------------------------------------------------------------

uint32_t analog_read(uint8_t pin) {
  ADC1->RSQR[2] = pin;

  // Start sw conversion (auto clears)
  ADC1->CTLR2 |= ADC_SWSTART;

  // Wait for conversion complete
  while (!(ADC1->STATR & ADC_EOC));

  // Get result
  return ADC1->RDATAR;
}

//------------------------------------------------------------------------------

#endif /* IO_ADC */
