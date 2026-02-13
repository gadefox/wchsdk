#if IO_PIN

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/afio.h"
#include "wch/hw/gpio.h"
#include "wch/hw/rcc.h"

//------------------------------------------------------------------------------

static inline void pin_init_all(void) {
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_IOPCEN | RCC_IOPDEN; }

static inline void pin_a_init(void) {
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN; }

static inline void pin_c_init(void) {
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPCEN; }

static inline void pin_d_init(void) {
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPDEN; }

//------------------------------------------------------------------------------

static inline void pin_a_mode(uint8_t pin, uint8_t mode) {
  GPIOA->CFGLR &= ~GPIO_PIN_MASK(pin);
  GPIOA->CFGLR |= GPIO_PIN_CFG(pin, mode);
}

static inline void pin_c_mode(uint8_t pin, uint8_t mode) {
  GPIOC->CFGLR &= ~GPIO_PIN_MASK(pin);
  GPIOC->CFGLR |= GPIO_PIN_CFG(pin, mode);
}

static inline void pin_d_mode(uint8_t pin, uint8_t mode) {
  GPIOD->CFGLR &= ~GPIO_PIN_MASK(pin);
  GPIOD->CFGLR |= GPIO_PIN_CFG(pin, mode);
}

//------------------------------------------------------------------------------

static inline bool pin_a_get(uint8_t pin) {
  return (GPIOA->INDR >> pin) & 1; }

static inline bool pin_c_get(uint8_t pin) {
  return (GPIOC->INDR >> pin) & 1; }

static inline bool pin_d_get(uint8_t pin) {
  return (GPIOD->INDR >> pin) & 1; }

//------------------------------------------------------------------------------

static inline void pin_a_set(uint8_t pin) {
  GPIOA->BSHR = 1 << pin; }

static inline void pin_c_set(uint8_t pin) {
  GPIOC->BSHR = 1 << pin; }

static inline void pin_d_set(uint8_t pin) {
  GPIOD->BSHR = 1 << pin; }

//------------------------------------------------------------------------------

static inline void pin_a_reset(uint8_t pin) {
  GPIOA->BSHR = 1 << (pin + 16); }

static inline void pin_c_reset(uint8_t pin) {
  GPIOC->BSHR = 1 << (pin + 16); }

static inline void pin_d_reset(uint8_t pin) {
  GPIOD->BSHR = 1 << (pin + 16); }

//------------------------------------------------------------------------------

#define pin_a_exti_cfg(pin)  pin_exti_cfg(GPIO_PORTSOURCE_GPIOA, pin)
#define pin_c_exti_cfg(pin)  pin_exti_cfg(GPIO_PORTSOURCE_GPIOC, pin)
#define pin_d_exti_cfg(pin)  pin_exti_cfg(GPIO_PORTSOURCE_GPIOD, pin)

static inline void pin_exti_cfg(uint8_t source, uint8_t pin) {
  uint8_t mask = pin << 1;
  AFIO->EXTICR &= ~(0b11 << mask);
  AFIO->EXTICR |= source << mask; }

//------------------------------------------------------------------------------

#endif  /* IO_PIN */
