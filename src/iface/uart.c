#include "wchsdk_cfg.h"

#if IFACE_UART

#include "wch/hw/afio.h"
#include "wch/hw/rcc.h"
#include "wch/hw/uart.h"
#include "wch/mcu/pfic.h"
#include "wch/core/ring.h"
#include "wch/iface/uart.h"

//------------------------------------------------------------------------------

#if !MCU_PFIC
#error "UART requires MCU_PFIC = 1"
#endif  /* SYS_RING */

#if !CORE_RING
#error "UART requires CORE_RING = 1"
#endif  /* CORE_RING */

//------------------------------------------------------------------------------
// UART Ring Buffer

static ring_t rx_ring;
static ring_t tx_ring;

//------------------------------------------------------------------------------
// UART Receiver Interrupt handler - Puts the data received into the Ring Buffer

__attribute__((interrupt))
void irq_usart1(void) {
  uint16_t statr = USART1->STATR;

  // RX: Check if data received
  if (statr & USART_STATR_RXNE) {
    // Read from the DATAR Register to reset the flag
    uint8_t recv = (uint8_t)USART1->DATAR;

#if IFACE_UART_RX_RING_OVERWRITE
    // Overwrite mode: if full, advance tail
    if (ring_is_full(&rx_ring)) {
      uint8_t dummy;
      ring_get(&rx_ring, &dummy);  // Discard oldest byte
    }
#endif  /* IFACE_UART_RX_RING_OVERWRITE */

    // Try to put data into ring buffer
    ring_put(&rx_ring, recv);
  }

  // TX: Check if transmitter empty
  if (statr & USART_STATR_TXE) {
    uint8_t data;
    if (ring_get(&tx_ring, &data)) {
      // Send next byte
      USART1->DATAR = data;
     } else {
      // No more data to send, disable TXE interrupt
      USART1->CTLR1 &= ~USART_CTLR1_TXEIE;
    }
  }
}

//------------------------------------------------------------------------------

void uart_init(uart_config_t* c) {
  // Initialize the RX / TX ring buffers
  ring_init(&rx_ring, c->rx_buf, c->rx_size);
  ring_init(&tx_ring, c->tx_buf, c->tx_size);

  // Enable UART1 Clock
  uart_power_on();
  uart_reset();

  // Set the Baudrate, assuming 48KHz
  USART1->BRR = UART_BAUD_TO_BRR(c->baud);

  // Enable the UART RXNE Interrupt
  pfic_enable_irq(IRQ_USART1);

  // Set CTLR registers
  USART1->CTLR1 = USART_WORDLENGTH_8B | USART_PARITY_NO | USART_MODE_TX |
                  USART_MODE_RX;
  USART1->CTLR2 = USART_STOPBITS_1;
  USART1->CTLR3 = USART_DMAREQ_TX | USART_DMAREQ_RX;
}

//------------------------------------------------------------------------------

void uart_print(const char *s) {
  while (*s) {
    uart_put(*s);
    s++;
  }
}

//------------------------------------------------------------------------------
// Write one byte to TX ring buffer

bool uart_put(uint8_t byte) {
  if (!ring_put(&tx_ring, byte))
    return false;

  // Enable TXE interrupt to start sending
  USART1->CTLR1 |= USART_CTLR1_TXEIE;
  return true;
}

//------------------------------------------------------------------------------
// Read one byte from RX ring buffer

bool uart_get(uint8_t *out) {
  return ring_get(&rx_ring, out);
}

//------------------------------------------------------------------------------

#endif  /* IFACE_UART */
