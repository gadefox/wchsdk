#include "wchsdk_cfg.h"

#if IO_SPI

#include "wch/util/ring.h"
#include "wch/io/spi.h"
#include "wch/io/util.h"

//------------------------------------------------------------------------------

#if !UTIL_RING
#error "SPI requires UTIL_RING = 1"
#endif  /* UTIL_RING */

#if !IO_UTIL
#error "SPI requires IO_UTIL = 1"
#endif  /* IO_UTIL */

//------------------------------------------------------------------------------
// SPI Ring Buffer

static ring_t rx_ring;
static ring_t tx_ring;

//------------------------------------------------------------------------------

  __attribute__((interrupt))
void irq_spi1(void) {
  uint16_t statr = SPI1->STATR;

  /* RX: Data received */
  if (statr & SPI_RXNE) {
    uint8_t recv = (uint8_t)SPI1->DATAR;

#if IO_SPI_RX_RING_OVERWRITE
    // Overwrite mode: if full, advance tail
    if (ring_is_full(&rx_ring)) {
      uint8_t dummy;
      ring_get(&rx_ring, &dummy);  // Discard oldest byte
    }
#endif  /* IO_SPI_RX_RING_OVERWRITE */

    // Try to put data into ring buffer
    ring_put(&rx_ring, recv);
  }

  /* TX: Transmit buffer empty */
  if (statr & SPI_TXE) {
    uint8_t data;
    if (ring_get(&tx_ring, &data)) {
      // Send next byte
      SPI1->DATAR = data;
    } else {
      // No more data to send, disable TXE interrupt
      SPI1->CTLR2 &= ~SPI_TXEIE;
    }
  }

  /* Error handling */
  if (statr & SPI_OVR) {
    volatile uint8_t dummy;
    dummy = SPI1->DATAR;
    dummy = SPI1->STATR;
  }
}

//------------------------------------------------------------------------------

void spi_init(spi_config_t* c) {
  // Initialize the RX / TX ring buffers
  ring_init(&rx_ring, c->rx_buf, c->rx_size);
  ring_init(&tx_ring, c->tx_buf, c->tx_size);

  // Enable SPI1 Clock
  spi_power_on();

  // NSS hardware control mode; pull NSS high; MCU is master
  SPI1->CTLR1 |= SPI_MSTR | SPI_SSI;
  SPI1->CTLR2 |= SPI_SSOE;

  // Set prescaler; NSS hardware control mode; pull NSS high; MCU is master
  uint8_t prescaler = freq_to_prescaler(c->freq, SPI_BR_DIV256);
  SPI1->CTLR1 |= prescaler;

  // Set data direction and configure data pins
  SPI1->CTLR1 |= c->direction;

  // Enable the SPI RXNE Interrupt
  spi_enable_irq();
}

//------------------------------------------------------------------------------

bool spi_transfer(uint8_t tx, uint8_t *rx) {
  if (!spi_put(tx))
    return false;

  while (!spi_get(rx));
  return true;
}

//------------------------------------------------------------------------------
// Write one byte to TX ring buffer

bool spi_put(uint8_t byte) {
  if (!ring_put(&tx_ring, byte))
    return false;

  // Enable TXE interrupt to start sending
  SPI1->CTLR2 |= SPI_TXEIE;
  return true;
}

//------------------------------------------------------------------------------
// Read one byte from RX ring buffer

bool spi_get(uint8_t *out) {
  return ring_get(&rx_ring, out);
}

//------------------------------------------------------------------------------

#endif // IO_SPI
