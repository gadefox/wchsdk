#if IO_PIN

#pragma once

#include <stdbool.h>

#include "wch/hw/gpio.h"
#include "wch/hw/rcc.h"

#include "wch/sys/def.h"

//------------------------------------------------------------------------------

#define GPIO_PIN(port, pin) (((port) << 3) | (pin))

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
  PC0 = GPIO_PIN(GPIO_PORTC, 0),  /* 16 */
  PC1 = GPIO_PIN(GPIO_PORTC, 1),  /* 17 */
  PC2 = GPIO_PIN(GPIO_PORTC, 2),  /* 18 */
  PC3 = GPIO_PIN(GPIO_PORTC, 3),  /* 19 */
  PC4 = GPIO_PIN(GPIO_PORTC, 4),  /* 20 */
  PC5 = GPIO_PIN(GPIO_PORTC, 5),  /* 21 */
  PC6 = GPIO_PIN(GPIO_PORTC, 6),  /* 22 */
  PC7 = GPIO_PIN(GPIO_PORTC, 7),  /* 23 */

  /* port D */
  PD0 = GPIO_PIN(GPIO_PORTD, 0),  /* 24 */
  PD1 = GPIO_PIN(GPIO_PORTD, 1),  /* 25 */
  PD2 = GPIO_PIN(GPIO_PORTD, 2),  /* 26 */
  PD3 = GPIO_PIN(GPIO_PORTD, 3),  /* 27 */
  PD4 = GPIO_PIN(GPIO_PORTD, 4),  /* 28 */
  PD5 = GPIO_PIN(GPIO_PORTD, 5),  /* 29 */
  PD6 = GPIO_PIN(GPIO_PORTD, 6),  /* 30 */
  PD7 = GPIO_PIN(GPIO_PORTD, 7)   /* 31 */
} gpio_pin_t;

#define PIN_PORT(p)  ((p) >> 3)
#define PIN_NUM(p)   ((p) & 0b111)
#define PIN_BIT(p)   BITS(PIN_NUM(p))

//------------------------------------------------------------------------------

#define PIN_CFG(pin, cfg)  ((cfg) << (PIN_NUM(pin) << 2))
#define PIN_MASK(p)   PIN_CFG(p, 0xF)

// Input modes
#define PIN_IA(p)     PIN_CFG(p, GPIO_ANALOG)
#define PIN_IF(p)     PIN_CFG(p, GPIO_FLOAT)
#define PIN_IP(p)     PIN_CFG(p, GPIO_PUPD)

// Output push-pull
#define PIN_PP2(p)    PIN_CFG(p, GPIO_PP2)
#define PIN_PP10(p)   PIN_CFG(p, GPIO_PP10)
#define PIN_PP30(p)   PIN_CFG(p, GPIO_PP30)

// Output open-drain
#define PIN_OD2(p)    PIN_CFG(p, GPIO_OD2)
#define PIN_OD10(p)   PIN_CFG(p, GPIO_OD10)
#define PIN_OD30(p)   PIN_CFG(p, GPIO_OD30)

// Alternate function push-pull
#define PIN_AOP2(p)   PIN_CFG(p, GPIO_APP2)
#define PIN_AOP10(p)  PIN_CFG(p, GPIO_APP10)
#define PIN_AOP30(p)  PIN_CFG(p, GPIO_APP30)

// Alternate function open-drain
#define PIN_AOD2(p)   PIN_CFG(p, GPIO_AOD2)
#define PIN_AOD10(p)  PIN_CFG(p, GPIO_AOD10)
#define PIN_AOD30(p)  PIN_CFG(p, GPIO_AOD30)

//------------------------------------------------------------------------------
// Power

static inline void port_power_on(uint32_t mask) {
  RCC->APB2PCENR |= mask; }

static inline void port_power_off(uint32_t mask) {
  RCC->APB2PCENR &= ~mask; }

//------------------------------------------------------------------------------

static inline void port_mask_cfg(gpio_port_t* port, uint32_t mask) {
  port->CFGLR &= ~mask; }

static inline void port_write_cfg(gpio_port_t* port, uint32_t cfg) {
  port->CFGLR = cfg; }

static inline void port_set_cfg(gpio_port_t* port, uint32_t cfg) {
  port->CFGLR |= cfg; }

static inline void pin_mode(gpio_pin_t pin, gpio_cfg_t cfg) {
  gpio_port_t* port = &GPIO->ports[PIN_PORT(pin)];
  port_mask_cfg(port, PIN_MASK(pin));
  port_set_cfg(port, PIN_CFG(pin, cfg)); }

//------------------------------------------------------------------------------

static inline uint32_t port_read(gpio_port_t* port) {
  return port->INDR; }

static inline uint32_t pin_read(gpio_pin_t pin) {
  gpio_port_t* port = &GPIO->ports[PIN_PORT(pin)];
  return port_read(port) & PIN_BIT(pin); }

//------------------------------------------------------------------------------

static inline void port_set(gpio_port_t* port, uint32_t mask) {
  port->BSHR |= mask; }

static inline void pin_set(gpio_pin_t pin) {
  gpio_port_t* port = &GPIO->ports[PIN_PORT(pin)];
  port_set(port, PIN_BIT(pin)); }

//------------------------------------------------------------------------------

static inline void port_reset(gpio_port_t* port, uint32_t mask) {
  port->BCR |= mask; }

static inline void pin_reset(gpio_pin_t pin) {
  gpio_port_t* port = &GPIO->ports[PIN_PORT(pin)];
  port_reset(port, PIN_BIT(pin)); }

//------------------------------------------------------------------------------

static inline void pin_write(gpio_pin_t pin, bool set) {
  gpio_port_t* port = &GPIO->ports[PIN_PORT(pin)];
  port_set(port, PIN_BIT(pin) << ((!set) << 4)); }

//------------------------------------------------------------------------------

#endif  /* IO_LINE */
