#if IO_PIN

#pragma once

#include <stdbool.h>

#include "wch/hw/gpio.h"
#include "wch/hw/rcc.h"

#include "wch/sys/def.h"

//------------------------------------------------------------------------------

#define GPIO_PIN(port, pin) ((uint8_t)(((port) << 4) | ((pin) & 0xF)))

typedef enum {
  /* port A */
  PA0 = GPIO_PIN(GPIO_PORTA, 0),  /* 0 */
  PA1 = GPIO_PIN(GPIO_PORTA, 1),  /* 1 */
  PA2 = GPIO_PIN(GPIO_PORTA, 2),  /* 2 */
  PA3 = GPIO_PIN(GPIO_PORTA, 3),  /* 3 */
  PA4 = GPIO_PIN(GPIO_PORTA, 4),  /* 4 */
  PA5 = GPIO_PIN(GPIO_PORTA, 5),  /* 5 */
  PA6 = GPIO_PIN(GPIO_PORTA, 6),  /* 6 */
  PA7 = GPIO_PIN(GPIO_PORTA, 7),  /* 7 */

  /* port C */
  PC0 = GPIO_PIN(GPIO_PORTC, 0),  /* 32 */
  PC1 = GPIO_PIN(GPIO_PORTC, 1),  /* 33 */
  PC2 = GPIO_PIN(GPIO_PORTC, 2),  /* 34 */
  PC3 = GPIO_PIN(GPIO_PORTC, 3),  /* 35 */
  PC4 = GPIO_PIN(GPIO_PORTC, 4),  /* 36 */
  PC5 = GPIO_PIN(GPIO_PORTC, 5),  /* 37 */
  PC6 = GPIO_PIN(GPIO_PORTC, 6),  /* 38 */
  PC7 = GPIO_PIN(GPIO_PORTC, 7),  /* 39 */

  /* port D */
  PD0 = GPIO_PIN(GPIO_PORTD, 0),  /* 48 */
  PD1 = GPIO_PIN(GPIO_PORTD, 1),  /* 49 */
  PD2 = GPIO_PIN(GPIO_PORTD, 2),  /* 50 */
  PD3 = GPIO_PIN(GPIO_PORTD, 3),  /* 51 */
  PD4 = GPIO_PIN(GPIO_PORTD, 4),  /* 52 */
  PD5 = GPIO_PIN(GPIO_PORTD, 5),  /* 53 */
  PD6 = GPIO_PIN(GPIO_PORTD, 6),  /* 54 */
  PD7 = GPIO_PIN(GPIO_PORTD, 7)   /* 55 */
} gpio_pin_t;

#define PIN_PORT(p)  ((gpio_port_id_t)((p) >> 4))
#define PIN_NUM(p)   ((p) & 0xF)
#define PIN_BIT(p)   BITS(PIN_NUM(p))

//------------------------------------------------------------------------------

#define PIN_CFG(pin, cfg)  ((cfg) << (PIN_NUM(pin) << 2))
#define PIN_MASK(p)  PIN_CFG(p, 0xF)

// Input modes
#define PIN_IA(p)  PIN_CFG(p, GPIO_ANALOG)
#define PIN_IF(p)  PIN_CFG(p, GPIO_FLOAT)
#define PIN_IP(p)  PIN_CFG(p, GPIO_PUPD)

// Output push-pull
#define PIN_PP2(p)   PIN_CFG(p, GPIO_PP2)
#define PIN_PP10(p)  PIN_CFG(p, GPIO_PP10)
#define PIN_PP30(p)  PIN_CFG(p, GPIO_PP30)

// Output open-drain
#define PIN_OD2(p)   PIN_CFG(p, GPIO_OD2)
#define PIN_OD10(p)  PIN_CFG(p, GPIO_OD10)
#define PIN_OD30(p)  PIN_CFG(p, GPIO_OD30)

// Alternate function push-pull
#define PIN_AP2(p)   PIN_CFG(p, GPIO_APP2)
#define PIN_AP10(p)  PIN_CFG(p, GPIO_APP10)
#define PIN_AP30(p)  PIN_CFG(p, GPIO_APP30)

// Alternate function open-drain
#define PIN_AD2(p)   PIN_CFG(p, GPIO_AOD2)
#define PIN_AD10(p)  PIN_CFG(p, GPIO_AOD10)
#define PIN_AwD30(p)  PIN_CFG(p, GPIO_AOD30)

//------------------------------------------------------------------------------
// Power

static inline void port_power_on(uint32_t mask) {
  RCC->APB2PCENR |= mask; }

static inline void port_power_off(uint32_t mask) {
  RCC->APB2PCENR &= ~mask; }

//------------------------------------------------------------------------------

static inline void port_mask_cfg(gpio_port_t* port, uint32_t mask) {
  port->CFGLR &= ~mask; }

static inline void port_set_cfg(gpio_port_t* port, uint32_t cfg) {
  port->CFGLR |= cfg; }

static inline void pin_set_mode(gpio_pin_t pin, gpio_cfg_t cfg) {
  gpio_port_t* port = &GPIO->ports[PIN_PORT(pin)];
  port_mask_cfg(port, PIN_MASK(pin));
  port_set_cfg(port, PIN_CFG(pin, cfg)); }

//------------------------------------------------------------------------------

static inline uint32_t port_get(gpio_port_t* port) {
  return port->INDR; }

static inline uint32_t pin_get(gpio_pin_t pin) {
  gpio_port_t* port = &GPIO->ports[PIN_PORT(pin)];
  uint32_t indr = port_get(port);
  return indr & PIN_BIT(pin); }

//------------------------------------------------------------------------------

static inline void port_set(gpio_port_t* port, uint32_t mask) {
  port->BSHR = mask; }

static inline void pin_set(gpio_pin_t pin) {
  gpio_port_t* port = &GPIO->ports[PIN_PORT(pin)];
  port_set(port, PIN_BIT(pin)); }

//------------------------------------------------------------------------------

static inline void port_reset(gpio_port_t* port, uint32_t mask) {
  port->BCR = mask; }

static inline void pin_reset(gpio_pin_t pin) {
  gpio_port_t* port = &GPIO->ports[PIN_PORT(pin)];
  port_reset(port, PIN_BIT(pin)); }

//------------------------------------------------------------------------------

#endif  /* IO_LINE */
