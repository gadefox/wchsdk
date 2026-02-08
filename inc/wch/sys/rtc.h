#if SYS_RTC

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/rcc.h"
#include "wch/hw/tim.h"

//------------------------------------------------------------------------------

typedef struct {
  uint16_t year;
  uint8_t  month;     // 0 = January
  uint8_t  day;       // 0 = first day of month
} rtc_date_t;

typedef struct {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t milli;
} rtc_time_t;

//------------------------------------------------------------------------------

void rtc_init(uint8_t ms);

//------------------------------------------------------------------------------

uint16_t rtc_days_before_month(uint16_t year, uint8_t month);
uint32_t rtc_days_since_epoch(uint16_t year, uint8_t month);
uint32_t rtc_seconds_since_epoch(uint16_t year, uint8_t month, uint8_t day,
                                 uint8_t hour, uint8_t minute);

//------------------------------------------------------------------------------

rtc_time_t rtc_seconds_to_time(uint32_t seconds);
rtc_date_t rtc_days_to_date(uint32_t days);

//------------------------------------------------------------------------------
// This function is valid only for years 1970 through 2099

static inline bool rtc_is_leap_year(uint16_t year) {
   return (year & 3) == 0; }

static inline uint8_t rtc_leap_days(uint16_t year) {
   return (year + 1) >> 2; }

//------------------------------------------------------------------------------

static inline void rtc_enable(void) {
  TIM2->CTLR1 = TIM_CEN; }

static inline void rtc_disable(void) {
  TIM2->CTLR1 &= ~TIM_CEN; }

static inline void rtc_power_on(void) {
  RCC->APB1PCENR |= RCC_APB1PERIPH_TIM2; }

static inline void rtc_power_off(void) {
  RCC->APB1PCENR &= ~RCC_APB1PERIPH_TIM2; }

static inline void rtc_reset(void) {
  RCC->APB1PRSTR |= RCC_APB1PERIPH_TIM2;
  RCC->APB1PRSTR &= ~RCC_APB1PERIPH_TIM2; }

//------------------------------------------------------------------------------

#endif // SYS_RTC
