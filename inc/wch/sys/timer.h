#if SYS_TIMER

#pragma once

#include <stdint.h>

#include "wch/hw/rcc.h"
#include "wch/hw/tim.h"

//------------------------------------------------------------------------------
// Power

static inline void tim1_power_on(void) {
  RCC->APB2PCENR |= RCC_TIM1EN; }

static inline void tim1_reset(void) {
  RCC->APB2PRSTR |= RCC_TIM1RST;
  RCC->APB2PRSTR &= ~RCC_TIM1RST; }

//------------------------------------------------------------------------------

static inline void tim2_power_on(void) {
  RCC->APB1PCENR |= RCC_TIM2EN; }

static inline void tim2_reset(void) {
  RCC->APB1PRSTR |= RCC_TIM2RST;
  RCC->APB1PRSTR &= ~RCC_TIM2RST; }

//------------------------------------------------------------------------------
// Basic control

static inline void tim_enable(tim_t *tim) {
  tim->CTLR1 |= TIM_CEN; }

static inline void tim_disable(tim_t *tim) {
  tim->CTLR1 &= ~TIM_CEN; }

static inline void tim_update_event(tim_t *tim) {
  tim->SWEVGR |= TIM_UG; }

//------------------------------------------------------------------------------
// Counter

static inline void tim_set_prescaler(tim_t *tim, uint16_t psc) {
  tim->PSC = psc; }

static inline void tim_set_auto_reload(tim_t* tim, uint16_t arr) {
  tim->ATRLR = arr; }

static inline void tim_set_count(tim_t *tim, uint16_t count) {
  tim->CNT = cnt; }

static inline uint16_t tim_get_count(tim_t *tim) {
  return tim->CNT; }

//------------------------------------------------------------------------------
// Mode

static inline void tim_upcount(tim_t *tim) {
  tim->CTLR1 &= ~TIM_DIR; }

static inline void tim_downcount(tim_t *tim) {
  tim->CTLR1 |= TIM_DIR; }

static inline void tim_one_pulse(tim_t *tim) {
  tim->CTLR1 |= TIM_OPM; }

static inline void tim_continuous(tim_t *tim) {
  tim->CTLR1 &= ~TIM_OPM; }

//------------------------------------------------------------------------------
// Interrupt

static inline void tim_irq_enable_update(tim_t *tim) {
  tim->DMAINTENR |= TIM_UIE; }

static inline void tim_irq_disable_update(tim_t *tim) {
  tim->DMAINTENR &= ~TIM_UIE; }

static inline void tim_clear_update_flag(tim_t *tim) {
  tim->INTFR &= ~TIM_UIF; }

static inline uint8_t tim_update_flag(tim_t * tim) {
  return (tim->INTFR & TIM_UIF) != 0; }

//------------------------------------------------------------------------------
// PWM

static inline void tim_pwm_ch1_enable(tim_t *tim) {
  tim->CCER |= TIM_CC1E; }

static inline void tim_pwm_ch1_disable(tim_t *tim) {
  tim->CCER &= ~TIM_CC1E; }

static inline void tim_pwm_ch1_set_duty(tim_t *tim, uint16_t duty) {
  tim->CH1CVR = duty; }

//------------------------------------------------------------------------------

#endif  /* SYS_TIMER */
