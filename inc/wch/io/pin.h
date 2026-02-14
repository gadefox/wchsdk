#if IO_PIN

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wch/hw/afio.h"
#include "wch/hw/gpio.h"
#include "wch/hw/rcc.h"
#include "wch/sys/def.h"

//------------------------------------------------------------------------------

#define PIN_CFG(pin, cfg)  ((cfg) << ((pin) << 2))
#define PIN_MASK(pin)      PIN_CFG(pin, 0xF)

// Input modes
#define PIN_IA(p)  PIN_CFG(p, GPIO_CFGLR_IN_ANALOG)
#define PIN_IF(p)  PIN_CFG(p, GPIO_CFGLR_IN_FLOAT)
#define PIN_IP(p)  PIN_CFG(p, GPIO_CFGLR_IN_PUPD)

// Output push-pull
#define PIN_OP2(p)   PIN_CFG(p, GPIO_CFGLR_OUT_2_PP)
#define PIN_OP10(p)  PIN_CFG(p, GPIO_CFGLR_OUT_10_PP)
#define PIN_OP30(p)  PIN_CFG(p, GPIO_CFGLR_OUT_30_PP)
#define PIN_OP50(p)  PIN_CFG(p, GPIO_CFGLR_OUT_50_PP)

// Output open-drain
#define PIN_OD2(p)   PIN_CFG(p, GPIO_CFGLR_OUT_2_OD)
#define PIN_OD10(p)  PIN_CFG(p, GPIO_CFGLR_OUT_10_OD)
#define PIN_OD30(p)  PIN_CFG(p, GPIO_CFGLR_OUT_30_OD)
#define PIN_OD50(p)  PIN_CFG(p, GPIO_CFGLR_OUT_50_OD)

// Alternate function push-pull
#define PIN_AP2(p)   PIN_CFG(p, GPIO_CFGLR_OUT_2_AF_PP)
#define PIN_AP10(p)  PIN_CFG(p, GPIO_CFGLR_OUT_10_AF_PP)
#define PIN_AP30(p)  PIN_CFG(p, GPIO_CFGLR_OUT_30_AF_PP)
#define PIN_AP50(p)  PIN_CFG(p, GPIO_CFGLR_OUT_50_AF_PP)

// Alternate function open-drain
#define PIN_AD2(p)   PIN_CFG(p, GPIO_CFGLR_OUT_2_AF_OD)
#define PIN_AD10(p)  PIN_CFG(p, GPIO_CFGLR_OUT_10_AF_OD)
#define PIN_AD30(p)  PIN_CFG(p, GPIO_CFGLR_OUT_30_AF_OD)
#define PIN_AD50(p)  PIN_CFG(p, GPIO_CFGLR_OUT_50_AF_OD)

//------------------------------------------------------------------------------
// Power

#define PORTA  RCC_IOPAEN
#define PORTC  RCC_IOPCEN
#define PORTD  RCC_IOPDEN

static inline void port_power_on(uint32_t mask) {
  RCC->APB2PCENR |= mask | RCC_AFIOEN; }

static inline void port_power_off(uint32_t mask) {
  RCC->APB2PCENR &= ~mask; }

//------------------------------------------------------------------------------

static inline void port_clear_cfg(gpio_t* port, uint32_t mask) {
  port->CFGLR &= ~mask; }

static inline void port_set_cfg(gpio_t* port, uint32_t cfg) {
  port->CFGLR |= cfg; }

static inline void port_cfg(gpio_t* port, uint32_t cfg, uint32_t mask) {
  port_clear_cfg(port, mask);
  port_set_cfg(port, cfg); }

//------------------------------------------------------------------------------


static inline uint32_t port_get(gpio_t* port) {
  return port->INDR; }

static inline bool pin_get(gpio_t* port, uint8_t pin) {
  return BITR(port->INDR, pin); }

//------------------------------------------------------------------------------

static inline void port_set(gpio_t* port, uint32_t mask) {
  port->BSHR = mask; }

static inline void pin_set(gpio_t* port, uint8_t pin) {
  port->BSHR = BITS(pin); }

//------------------------------------------------------------------------------

static inline void port_reset(gpio_t* port, uint32_t mask) {
  port->BCR = mask; }

static inline void pin_reset(gpio_t* port, uint8_t pin) {
  port->BCR = BITS(pin); }

//------------------------------------------------------------------------------

#endif  /* IO_LINE */
