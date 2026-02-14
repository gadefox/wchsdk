#if SYS_EXTI

#pragma once

#include "wch/hw/afio.h"
#include "wch/hw/exti.h"
#include "wch/hw/irq.h"
#include "wch/hw/rcc.h"
#include "wch/sys/pfic.h"

//------------------------------------------------------------------------------

#if !SYS_PFIC
#error "EXTI requires SYS_PFIC = 1"
#endif  /* SYS_PFIC */

//------------------------------------------------------------------------------
// Power

static inline void exti_power_on(void) {
  RCC->APB2PCENR |= RCC_AFIOEN; }

static inline void exti_power_off(void) {
  RCC->APB2PCENR &= ~RCC_AFIOEN; }

//------------------------------------------------------------------------------
// Line config

static inline void exti_enable(uint32_t mask) {
  EXTI->INTENR |= mask; }

static inline void exti_disable(uint32_t mask) {
  EXTI->INTENR &= ~mask; }

static inline void exti_rising_on(uint32_t mask) {
  EXTI->RTENR |= mask; }

static inline void exti_rising_off(uint32_t mask) {
  EXTI->RTENR &= ~mask; }

static inline void exti_falling_on(uint32_t mask) {
  EXTI->FTENR |= mask; }

static inline void exti_falling_off(uint32_t mask) {
  EXTI->FTENR &= ~mask; }

//------------------------------------------------------------------------------
// Pending

static inline uint32_t exti_pending(uint32_t mask) {
  return EXTI->INTFR & mask; }

static inline void exti_clear(uint32_t mask) {
  EXTI->INTFR = mask; }   // write 1 to clear

//------------------------------------------------------------------------------
// Port mapping

#define EXTI_CFG(line, port)  ((port) << ((line) << 1))
#define EXTI_MASK(l)  EXTI_CFG(l, 0b11)

#define EXTI_PORTA(l)  EXTI_CFG(l, EXTI_GPIOA)
#define EXTI_PORTC(l)  EXTI_CFG(l, EXTI_GPIOC)
#define EXTI_PORTD(l)  EXTI_CFG(l, EXTI_GPIOD)

static inline void exti_clear_map(uint32_t mask) {
  AFIO->EXTICR &= ~mask; }

static inline void exti_set_map(uint32_t cfg) {
  AFIO->EXTICR |= cfg; }

static inline void exti_map(uint32_t cfg, uint32_t mask) {
  exti_clear_map(mask);
  exti_set_map(cfg); }

//------------------------------------------------------------------------------
// SW Trigger

static inline void exti_sw_trigger(uint32_t mask) {
  EXTI->SWIEVR |= mask; }

//------------------------------------------------------------------------------
// PFIC

static inline void exti_enable_irq(void) {
  pfic_enable_irq(IRQ_EXTI7_0); }

static inline void exti_disable_irq(void) {
  pfic_disable_irq(IRQ_EXTI7_0); }

//------------------------------------------------------------------------------

#endif  /* SYS_EXTI */
