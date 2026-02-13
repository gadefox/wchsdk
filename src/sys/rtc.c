#include "wchsdk_cfg.h"

#if SYS_RTC

#include "wch/hw/irq.h"
#include "wch/mcu/def.h"
#include "wch/mcu/pfic.h"
#include "wch/sys/rtc.h"

//------------------------------------------------------------------------------
// Days before each month, non-leap year

static const uint16_t days_before_month[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

static volatile rtc_time_t time;
static volatile uint8_t interval;
static volatile uint16_t day;

//------------------------------------------------------------------------------

void irq_tim2(void) {
  if (!(TIM2->INTFR & TIM_UIF))
    return;

  TIM2->INTFR &= ~TIM_UIF;

  time.milli += interval;
  if (time.milli < 1000)
    return;

  time.milli = 0;
  if (++time.second < 60)
    return;

  time.second = 0;
  if (++time.minute < 60)
    return;
 
  time.minute = 0;
  if (++time.hour < 24)
    return;

  time.hour = 0;
  day++;
}

//------------------------------------------------------------------------------

void rtc_init(uint8_t ms) {
  interval = ms;

  tim2_power_on();                          // Enable clock for TIM2
  tim2_reset();                             // Reset TIM2
  tim_set_prescaler(TIM2, (MCU_SYS_FREQ / 1000) - 1); // Prescaler: 48 MHz / 48000 = 1 kHz
  tim_set_auto_reload(TIM2, ms - 1);        // Auto-reload: 1000 ticks = 1 s
  tim_set_count(TIM2, 0);                   // Reset counter
  tim_irq_enable_update(TIM2);              // Enable update interrupt

  pfic_enable_irq(IRQ_TIM2);                // Enable IRQ in PFIC
  tim_enable(TIM2);                         // Start timer
}

//------------------------------------------------------------------------------

uint16_t rtc_days_before_month(uint16_t year, uint8_t month) {
  if (month >= 12)
    return 0;

  uint16_t days = days_before_month[month];

  if (month > 1 && rtc_is_leap_year(year))  // March, April, ..
    days++;
  
  return days;
}

//------------------------------------------------------------------------------

uint32_t rtc_days_since_epoch(uint16_t year, uint8_t month) {
  uint16_t years = year - 1970;
  uint32_t days = years * 365;  // Approximation

  days += rtc_leap_days(years);
  days += rtc_days_before_month(year, month);
  return days;
}
//------------------------------------------------------------------------------

uint32_t rtc_seconds_since_epoch(uint16_t year, uint8_t month, uint8_t day,
                                 uint8_t hour, uint8_t minute) {
  uint32_t days = day;
  days += rtc_days_since_epoch(year, month);
  return days * 86400 + hour * 3600 + minute * 60;
}

//------------------------------------------------------------------------------

rtc_time_t rtc_seconds_to_time(uint32_t seconds) {
  rtc_time_t time;
  uint32_t minutes = seconds / 60;
  
  time.second = seconds % 60;
  time.minute = minutes % 60;
  time.hour = (minutes / 60) % 24;
  return time;
}

//------------------------------------------------------------------------------

rtc_date_t rtc_days_to_date(uint32_t days) {
  // Approximate year for 1970–2099; each 4th year is a leap year
  uint16_t years = days / 365;

  // Number of days in full years since 1970 excluding leap days + leap_days
  // → add the extra days from leap years up to the current year
  days -= rtc_leap_days(years) + years * 365;
  years += 1970;

  // If the approximate calculation overshot, correct it
  uint16_t total_days = rtc_is_leap_year(years) ? 366 : 365;
  if (days >= total_days) {
    days -= total_days;
    years++;
  }

  // Find month (0-based)
  uint8_t months = 11; // December
  while (months > 0 && days < days_before_month[months])
    months--;

  // Find day (0-based)
  days -= days_before_month[months];
  if (months > 1 && rtc_is_leap_year(years))
    days--; // adjust after Feb

  rtc_date_t date;
  date.year = years;
  date.month = months;
  date.day = days;
  return date;
}

//------------------------------------------------------------------------------

#endif  /* SYS_RTC */
