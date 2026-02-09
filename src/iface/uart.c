#include "wchsdk_cfg.h"

#if IFACE_UART

//#include "wch/hw/afio.h"
//#include "wch/hw/rcc.h"
//#include "wch/hw/uart.h"
//#include "wch/mcu/pfic.h"
//#include "wch/core/ring.h"
//#include "wch/iface/uart.h"

//------------------------------------------------------------------------------

#if !MCU_PFIC
#error "UART requires MCU_PFIC = 1"
#endif  /* MCU_PFIC */

#if !CORE_RING
#error "UART requires CORE_RING = 1"
#endif  /* CORE_RING */

//------------------------------------------------------------------------------

#define DMA_IRQ  IRQ_DMA1_CHANNEL6
#define DMA_TX   DMA1_CHANNEL6
#define DMA_RX   DMA1_CHANNEL7

//------------------------------------------------------------------------------

static uint8_t *usb_buf;
static uint8_t usb_size, usb_index;
static ring_t tx_ring, rx_ring;
static uint8_t tx_last_len;
static bool tx_active;

//------------------------------------------------------------------------------
// Called when UART RX IDLE line interrupt fires indicating new data ready

__attribute__((interrupt))
void irq_usart1(void) {
  if (!(USART1->STATR & USART_STATR_IDLE))
    return;

  (void)USART1->STATR;  // Clear flags
  (void)USART1->DATAR;

  rx_ring.head = (rx_ring.size - DMA_RX->CNTR) % rx_ring.size;
  if (ring_is_empty(&rx_ring))
    return;

  uint8_t linear = ring_linear_count(&rx_ring);
  uint8_t *tail = ring_tail_ptr(&rx_ring);
  memcpy(usb_buf, tail, linear);

  uint8_t count = ring_count(&rx_ring);
  if (count != linear)
    memcpy(usb_buf + linear, rx_ring.buf, count - linear);

  rx_ring.tail = rx_ring.head;  // Consume data
  usb_size = count;
  usb_index = 0;
}

/*
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
/*
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
*/

//------------------------------------------------------------------------------
// Called when UART TX DMA transfer complete interrupt fires

__attribute__((interrupt))
void irq_dma1_channel6(void) {
  dma_clear_tc(DMA_CTCIF6);
  tx_ring.tail = (tx_ring.tail + tx_last_len) % rx_ring.size;
  tx_active = false;
  uart_reload_dma();
}

//------------------------------------------------------------------------------

void uart_reload_dma(void) {
  if (tx_active || ring_is_empty(&tx_ring))
    return;     // nothing to send or busy

  uint8_t* tail = ring_tail_ptr(&tx_ring);
  uint8_t linear = ring_linear_count(&tx_ring);
  dma_reload(DMA_TX, tail, linear);

  tx_last_len = linear;
  tx_active = true;
}

//------------------------------------------------------------------------------

void uart_init(uart_config_t* c) {
  // Initialize the RX / TX ring buffers
  ring_init(&rx_ring, c->rx_buf, c->rx_size);
  ring_init(&tx_ring, c->tx_buf, c->tx_size);

  // Turn on UART1 and DMA
  dma_power_on();
  uart_power_on();

  // TX DMA setup (USB -> UART)
  dma_init_mem2periph(DMA_TX, DMA_IRQ, &USART1->DATAR);
  
  // RX DMA setup (UART -> USB)
  dma_init_periph2mem(DMA_RX, &USART1->DATAR, rx_ring.buf, rx_ring.size);

  // Set CTLR registers
  USART1->CTLR1 = USART_WORDLENGTH_8B | USART_PARITY_NO | USART_MODE_TX |
                  USART_MODE_RX;                     // 8bit, no parity, rx/tx uart
  USART1->CTLR2 = USART_STOPBITS_1;                  // 1 stop bit
  USART1->CTLR3 = USART_DMAREQ_TX | USART_DMAREQ_RX; // enable dma requests both ways

  // Set the Baudrate, assuming 48KHz
  uart_set_baud(c->baud);
  uart_enable();

  // Enable the UART RXNE Interrupt
  pfic_enable_irq(IRQ_USART1);
}

//------------------------------------------------------------------------------

void uart_print(const char *s) {
  while (*s) {
    uart_put(*s);
    s++;
  }
}

//------------------------------------------------------------------------------

void uart_printnl(const char *s) {
  uart_print(s);
  uart_put('\r');
  uart_put('\n');
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
