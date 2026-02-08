// User-configurable macros (see wchsdk_cfg.h):
//  IO_ADC_PREDIV: { RCC_ADCPRE_DIVxx }

#if IO_ADC

#pragma once

#include <stdint.h>
#include "wch/hw/adc.h"
#include "wch/hw/rcc.h"

//------------------------------------------------------------------------------

// Initialize the ADC calibrate it and set some sane defaults.
void adc_init(void);

// Read an analog input (not a GPIO pin number)
uint32_t adc_read(uint8_t pin);

//------------------------------------------------------------------------------
 
static inline void adc_enable(void) {
  ADC1->CTLR1 |= ADC_ADON | ADC_EXTSEL; }

static inline void adc_disable(void) {
  ADC1->CTLR1 &= ~ADC_ADON; }

static inline void adc_power_on(void) {
  RCC->APB2PCENR |= RCC_ADC2EN; }

static inline void adc_power_off(void) {
  RCC->APB2PCENR &= ~RCC_ADC2EN; }

static inline void adc_reset(void) { 
  RCC->APB2PRSTR |= RCC_ADC2RST;
  RCC->APB2PRSTR &= ~RCC_ADC2RST; }

//------------------------------------------------------------------------------

#endif  /* IO_ADC */
