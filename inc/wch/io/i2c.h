// User-configurable macros (see wchsdk_cfg.h):
//  IO_I2C_TIMEOUT
//  IO_I2C_RX_RING_OVERWRITE  0/1
//   1: Incomming data will overwrite older data in the buffer.
//   0: Incomming data will not be added to the buffer until space is free.

#if IO_I2C

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "wch/hw/afio.h"
#include "wch/hw/i2c.h"
#include "wch/hw/rcc.h"
#include "wch/sys/def.h"
#include "wch/sys/pfic.h"
#include "wch/sys/util.h"

//------------------------------------------------------------------------------

#if !SYS_PFIC
#error "I2C requires SYS_PFIC = 1"
#endif  /* SYS_PFIC */

#if !SYS_UTIL
#error "I2C requires SYS_UTIL = 1"
#endif  /* SYS_UTIL */

//------------------------------------------------------------------------------

#if !IO_I2C_TIMEOUT
#define IO_I2C_TIMEOUT  500
#endif  /* IO_I2C_TIMEOUT */

//------------------------------------------------------------------------------

typedef struct {
  uint8_t* rx_buf;
  uint8_t  rx_size;
  uint8_t* tx_buf;
  uint8_t  tx_size;
} i2c_config_t;

//------------------------------------------------------------------------------

void i2c_init(i2c_config_t* c);

bool i2c_transfer(uint8_t tx, uint8_t* rx);
bool i2c_put(uint8_t byte);
bool i2c_get(uint8_t* out);

//------------------------------------------------------------------------------

static inline uint16_t i2c_scl_to_ccr(uint32_t freq_scl) {
  if (freq_scl <= 100000)  // 100 kHz
    return (SYS_BASE_FREQ / 2 / freq_scl) & I2C_CKCFGR_CCR;
  return ((SYS_BASE_FREQ / 3 / freq_scl) & I2C_CKCFGR_CCR) | I2C_CKCFGR_FS; }

//------------------------------------------------------------------------------

static inline void i2c_enable(void) {
  I2C1->CTLR1 |= CTLR1_PE_SET; }

static inline void i2c_disable(void) {
  I2C1->CTLR1 &= CTLR1_PE_RESET; }

static inline void i2c_power_on(void) {
  RCC->APB1PCENR |= RCC_I2C1EN; }

static inline void i2c_power_off(void) {
  RCC->APB1PCENR &= ~RCC_I2C1EN; }

static inline void i2c_reset(void) {
  RCC->APB1PRSTR |= RCC_I2C2RST;
  RCC->APB1PRSTR &= ~RCC_I2C2RST; }

static inline void i2c_remap(uint32_t pcfr) {
  AFIO->PCFR1 &= ~(AFIO_PCFR1_SWCFG_DISABLE | AFIO_PCFR1_I2C1_HIGH_BIT_REMAP |
      AFIO_PCFR1_I2C1_REMAP);
  AFIO->PCFR1 |= pcfr; }

//------------------------------------------------------------------------------
/*
 static inline bool i2c_wait_start_condition(void) {
  return wait_mask(&I2C1->STAR1, I2C_STAR1_SB, true, IO_I2C_TIMEOUT); }

 static inline bool i2c_wait_byte_transmitted(void) {
  return wait_mask(&I2C1->STAR1, I2C_STAR1_BTF, true, IO_I2C_TIMEOUT); }

 static inline bool i2c_wait_tx_empty(void) {
  return wait_mask(&I2C1->STAR1, I2C_STAR1_TXE, true, IO_I2C_TIMEOUT); }

 static inline bool i2c_wait_rx_full(void) {
  return wait_mask(&I2C1->STAR1, I2C_STAR1_RXNE, true, IO_I2C_TIMEOUT); }

 static inline bool i2c_wait_not_busy(void) {
  return wait_mask(&I2C1->STAR1, I2C_STAR1_BUSY, false, IO_I2C_TIMEOUT); }

 static inline bool i2c_wait_no_error(void) {
  return wait_mask(&I2C1->STAR1, I2C_STAR1_AF | I2C_STAR1_BERR |
                       I2C_STAR1_ARLO, false, IO_I2C_TIMEOUT); }
*/
//------------------------------------------------------------------------------

static inline bool i2c_wait_master_transmitter_mode_selected(void) {
  return wait_mask2(&I2C1->STAR1, &I2C1->STAR2,
      I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED, true, IO_I2C_TIMEOUT); }

static inline bool i2c_wait_master_receiver_mode_selected(void) {
  return wait_mask2(&I2C1->STAR1, &I2C1->STAR2,
      I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED, true, IO_I2C_TIMEOUT); }

static inline bool i2c_send_addr_write7(uint8_t addr) {
  I2C1->DATAR = addr << 1;  // LSB = 0 (write)
  return i2c_wait_master_transmitter_mode_selected(); }

static inline bool i2c_send_addr_read7(uint8_t addr) {
  I2C1->DATAR = (addr << 1) | OADDR1_ADD0_SET;      // LSB = 1 (read)
  return i2c_wait_master_receiver_mode_selected(); }

//------------------------------------------------------------------------------

static inline bool i2c_wait_master_mode_addr10(void) {
  return wait_mask2(&I2C1->STAR1, &I2C1->STAR2,
      I2C_EVENT_MASTER_MODE_ADDRESS10, true, IO_I2C_TIMEOUT); }

bool i2c_send_addr_write10(uint16_t addr);
bool i2c_send_addr_read10(uint16_t addr);

//------------------------------------------------------------------------------

static inline bool i2c_wait_master_mode_select(void) {
  return wait_mask2(&I2C1->STAR1, &I2C1->STAR2,
      I2C_EVENT_MASTER_MODE_SELECT, true, IO_I2C_TIMEOUT); }

static inline bool i2c_start(void) {
  I2C1->CTLR1 |= I2C_CTLR1_START;
  return i2c_wait_master_mode_select(); }

static inline void i2c_stop(void) {
  I2C1->CTLR1 |= I2C_CTLR1_STOP; }

//------------------------------------------------------------------------------
// PFIC

static inline void i2c_enable_event_irq(void) {
  pfic_enable_irq(IRQ_I2C1_EV); }

static inline void i2c_disable_event_irq(void) {
  pfic_disable_irq(IRQ_I2C1_EV); }

//------------------------------------------------------------------------------

static inline void i2c_enable_error_irq(void) {
  pfic_enable_irq(IRQ_I2C1_ER); }

static inline void i2c_disable_error_irq(void) {
  pfic_disable_irq(IRQ_I2C1_ER); }

//------------------------------------------------------------------------------

#endif  /* IO_I2C */
