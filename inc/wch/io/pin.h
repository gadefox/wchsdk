#if IO_PIN

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/gpio.h"
#include "wch/hw/rcc.h"

//------------------------------------------------------------------------------

static inline void pin_init_all(void) {
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_IOPCEN | RCC_IOPDEN; }

static inline void pin_init_bank_a(void) {
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPAEN; }

static inline void pin_init_bank_c(void) {
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPCEN; }

static inline void pin_init_bank_d(void) {
  RCC->APB2PCENR |= RCC_AFIOEN | RCC_IOPDEN; }

//------------------------------------------------------------------------------

static inline void pin_set_mode_a(uint8_t pin, uint8_t mode) {
  GPIOA->CFGLR &= ~GPIO_PIN_MASK(pin);
  GPIOA->CFGLR |= GPIO_PIN_CFG(pin, mode);
}

static inline void pin_set_mode_c(uint8_t pin, uint8_t mode) {
  GPIOC->CFGLR &= ~GPIO_PIN_MASK(pin);
  GPIOC->CFGLR |= GPIO_PIN_CFG(pin, mode);
}

static inline void pin_set_mode_d(uint8_t pin, uint8_t mode) {
  GPIOD->CFGLR &= ~GPIO_PIN_MASK(pin);
  GPIOD->CFGLR |= GPIO_PIN_CFG(pin, mode);
}

//------------------------------------------------------------------------------

static inline bool pin_get_a(uint8_t pin) {
  return (GPIOA->INDR >> pin) & 1; }

static inline bool pin_get_c(uint8_t pin) {
  return (GPIOC->INDR >> pin) & 1; }

static inline bool pin_get_d(uint8_t pin) {
  return (GPIOD->INDR >> pin) & 1; }

//------------------------------------------------------------------------------

static inline void pin_set_a(uint8_t pin) {
  GPIOA->BSHR = 1 << pin; }

static inline void pin_set_c(uint8_t pin) {
  GPIOC->BSHR = 1 << pin; }

static inline void pin_set_d(uint8_t pin) {
  GPIOD->BSHR = 1 << pin; }

//------------------------------------------------------------------------------

static inline void pin_reset_a(uint8_t pin) {
  GPIOA->BSHR = 1 << (pin + 16); }

static inline void pin_reset_c(uint8_t pin) {
  GPIOC->BSHR = 1 << (pin + 16); }

static inline void pin_reset_d(uint8_t pin) {
  GPIOD->BSHR = 1 << (pin + 16); }

//------------------------------------------------------------------------------

#endif  /* IO_PIN */
