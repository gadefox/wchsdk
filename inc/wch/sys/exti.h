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

#define EXTI_PORTA  GPIO_PORTSOURCE_GPIOA
#define EXTI_PORTC  GPIO_PORTSOURCE_GPIOC
#define EXTI_PORTD  GPIO_PORTSOURCE_GPIOD

#define EXTI_LINE(n)  (1 << (n))

//------------------------------------------------------------------------------
// Power

static inline void exti_power_on(void) {
  RCC->APB2PCENR |= RCC_AFIOEN; }

static inline void exti_power_off(void) {
  RCC->APB2PCENR &= ~RCC_AFIOEN; }

//------------------------------------------------------------------------------
// Line config

static inline void exti_unmask(uint32_t mask) {
  EXTI->INTENR |= mask; }

static inline void exti_mask(uint32_t mask) {
  EXTI->INTENR &= ~mask; }

static inline void exti_enable_rising(uint32_t mask) {
  EXTI->RTENR |= mask; }

static inline void exti_enable_falling(uint32_t mask) {
  EXTI->FTENR |= mask; }

static inline void exti_disable_rising(uint32_t mask) {
  EXTI->RTENR &= ~mask; }

static inline void exti_disable_falling(uint32_t mask) {
  EXTI->FTENR &= ~mask; }

//------------------------------------------------------------------------------
// Pending

static inline uint32_t exti_pending(uint32_t mask) {
  return EXTI->INTFR & mask; }

static inline void exti_clear(uint32_t mask) {
  EXTI->INTFR = mask; }   // write 1 to clear

//------------------------------------------------------------------------------
// Port mapping

static inline void exti_map_port(uint8_t line, uint8_t port) {
  uint8_t shift = line << 1;
  AFIO->EXTICR &= ~(0b11 << shift);
  AFIO->EXTICR |= port << shift; }

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
