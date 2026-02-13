#include "wchsdk_cfg.h"

#if IO_I2C

#include "wch/util/ring.h"
#include "wch/sys/pfic.h"
#include "wch/io/i2c.h"
#include "wch/io/util.h"

#if !SYS_PFIC
#error "I2C requires SYS_PFIC = 1"
#endif  /* SYS_PFIC */

#if !UTIL_RING
#error "I2C requires UTIL_RING = 1"
#endif  /* UTIL_RING */

#if !IO_UTIL
#error "I2C requires IO_UTIL = 1"
#endif  /* IO_UTIL */

//------------------------------------------------------------------------------
// I2C Ring Buffers

static ring_t rx_ring;
static ring_t tx_ring;

//------------------------------------------------------------------------------
// I2C IRQ Handler

__attribute__((interrupt))
void irq_i2c1_ev(void) {
  uint16_t statr = I2C1->STAR1;

  /* RX: Data received */
  if (statr & I2C_STAR1_RXNE) {
    uint8_t recv = (uint8_t)I2C1->DATAR;

#if IO_I2C_RX_RING_OVERWRITE
    if (ring_is_full(&rx_ring)) {
      uint8_t dummy;
      ring_get(&rx_ring, &dummy);
    }
#endif  /* IO_I2C_RX_RING_OVERWRITE */
    ring_put(&rx_ring, recv);
  }

  /* TX: Transmit buffer empty */
  if (statr & I2C_STAR1_TXE) {
    uint8_t data;
    if (ring_get(&tx_ring, &data))
      I2C1->DATAR = data;
    else
      I2C1->CTLR2 &= ~I2C_CTLR2_ITBUFEN;  // disable buffer interrupt
  }

  /* Error handling */
  if (statr & (I2C_STAR1_BERR | I2C_STAR1_ARLO | I2C_STAR1_AF)) {
    volatile uint8_t dummy;
    dummy = I2C1->DATAR;
    dummy = I2C1->STAR1;
  }
}

//------------------------------------------------------------------------------

void i2c_init(i2c_config_t* c) {
  ring_init(&rx_ring, c->rx_buf, c->rx_size);
  ring_init(&tx_ring, c->tx_buf, c->tx_size);

  i2c_power_on();
  i2c_reset();

//  I2C1->CTLR1 = freq_to_prescaler(c->freq_hz) | c->direction;

  pfic_enable_irq(IRQ_I2C1_EV);
}

//------------------------------------------------------------------------------
// Transfer functions

bool i2c_transfer(uint8_t tx, uint8_t *rx) {
  if (!i2c_put(tx))
      return false;

  while (!i2c_get(rx));
  return true;
}

bool i2c_put(uint8_t byte) {
  if (!ring_put(&tx_ring, byte))
      return false;

  I2C1->CTLR2 |= I2C_CTLR2_ITBUFEN;  // enable buffer interrupt
  return true;
}

bool i2c_get(uint8_t *out) {
  return ring_get(&rx_ring, out);
}

//------------------------------------------------------------------------------

bool i2c_send_addr_write10(uint16_t addr) {
  // First byte: 11110[A9][A8]0
  I2C1->DATAR = 0xF0 | ((addr >> 7) & 0x06);
  if (!i2c_wait_master_mode_addr10())
    return false;
 
  // Second byte: A7-A0
  I2C1->DATAR = addr & 0xFF;  
  return i2c_wait_master_transmitter_mode_selected();
}

//------------------------------------------------------------------------------

bool i2c_send_addr_read10(uint16_t addr) {
  // First byte: 11110[A9][A8]1
  I2C1->DATAR = 0xF0 | ((addr >> 7) & 0x06) | OADDR1_ADD0_SET;
  if (!i2c_wait_master_mode_addr10())
    return false;

  // Second byte: A7-A0
  I2C1->DATAR = addr & 0xFF;  
  return i2c_wait_master_receiver_mode_selected();
}

//------------------------------------------------------------------------------

#endif // IO_I2C
