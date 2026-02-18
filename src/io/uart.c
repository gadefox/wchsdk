#include "wchsdk_cfg.h"

#if IO_UART

#include "wch/hw/dma.h"
#include "wch/hw/uart.h"
#include "wch/util/mem.h"
#include "wch/util/ring.h"
#include "wch/io/dma.h"
#include "wch/io/uart.h"

//------------------------------------------------------------------------------

#if !SYS_PFIC
#error "UART requires SYS_PFIC = 1"
#endif  /* SYS_PFIC */

#if !UTIL_RING
#error "UART requires UTIL_RING = 1"
#endif  /* UTIL_RING */

//------------------------------------------------------------------------------
// rx_ring: `head` is just a snapshot of the current position.
// The actual head pointer is maintained by the DMA hardware.

static ring_t rx_ring;
static ring_t tx_ring;

#ifdef IO_UART_USB_CDC
static uint8_t *usb_buf;
static uint8_t usb_size, usb_index;

static uint8_t tx_last_len;
static bool tx_active;
#endif  /* IO_UART_USB_CDC */

//------------------------------------------------------------------------------
// Write one byte to TX ring buffer

bool uart_tx_put(uint8_t byte) {
  if (!ring_put(&tx_ring, byte))
    return false;

  uart_enable_txe();  // Enable TXE interrupt to start sending
  return true;
}

//------------------------------------------------------------------------------
// Read one byte from RX ring buffer

inline bool uart_rx_get(uint8_t *out) {
  return ring_get(&rx_ring, out); }

//------------------------------------------------------------------------------

inline uint8_t uart_rx_snapshot(void) {
  return ring_snapshot(&rx_ring, DMA1_CHANNEL7->CNTR); }

//------------------------------------------------------------------------------
// Called when UART RX IDLE line interrupt fires indicating new data ready

__attribute__((interrupt))
void irq_uart1(void) {
#ifdef IO_UART_USB_CDC

  if (!(UART1->STATR & UART_STATR_IDLE))
    return;

  (void)UART1->STATR;  // Clear flags
  (void)UART1->DATAR;

  // Update head according to DMA count, get number of new bytes
  uint8_t new_bytes = uart_rx_snapshot();
  if (new_bytes == 0)
    return;

  uint8_t linear = ring_linear_count(&rx_ring);
  uint8_t *tail = ring_tail_ptr(&rx_ring);
  memcpy(usb_buf, tail, linear);

  if (new_bytes != linear)
    memcpy(usb_buf + linear, rx_ring.buf, new_bytes - linear);

  rx_ring.tail = rx_ring.head;  // Consume data
  usb_size = new_bytes;
  usb_index = 0;

#else

  // TX: Check if transmitter empty
  if (!uart_is_tx_empty())
    return;

  uint8_t data;
  if (ring_get(&tx_ring, &data))
    UART1->DATAR = data;  // Send next byte
  else
    uart_disable_txe();

#endif  /* IO_UART_USB_CDC */
}

//------------------------------------------------------------------------------

#ifdef IO_UART_USB_CDC

static void uart_reload_dma(void) {
  if (ring_is_empty(&tx_ring)) {
    tx_active = false;  // nothing to send or busy
    return;
  }

  uint8_t* tail = ring_tail_ptr(&tx_ring);
  uint8_t linear = ring_linear_count(&tx_ring);
  dma_reload(DMA1_CHANNEL6, tail, linear);

  tx_last_len = linear;
  tx_active = true;
}

//------------------------------------------------------------------------------
// Called when UART TX DMA transfer complete interrupt fires

__attribute__((interrupt))
void irq_dma1_channel6(void) {
  dma_clear_tc(DMA_CTCIF6);
  ring_shift_tail(&tx_ring, tx_last_len);
  uart_reload_dma();
}

#endif  /* IO_UART_USB_CDC */

//------------------------------------------------------------------------------

void uart_init(uart_config_t* c) {
  // Initialize the RX / TX ring buffers
  ring_init(&rx_ring, c->rx_buf, c->buf_size);
  ring_init(&tx_ring, c->tx_buf, c->buf_size);

#if IO_UART_USB_CDC
  usb_buf = c->usb_buf;
#endif  /* IO_UART_USB_CDC */

  // Turn on UART1 and DMA
  dma_power_on();
  uart_power_on();

#ifdef IO_UART_USB_CDC
  // TX DMA setup (USB -> UART)
  dma_init_mem2periph(DMA1_CHANNEL6, IRQ_DMA1_CHANNEL6, (void*)&UART1->DATAR);
#endif  /* IOE_UART_USB_CDC */
  
  // RX DMA setup (UART -> USB)
  dma_init_periph2mem(DMA1_CHANNEL7, (void*)&UART1->DATAR, rx_ring.buf, rx_ring.size);

  // Set CTLR registers
  UART1->CTLR1 = UART_WORDLENGTH_8B | UART_PARITY_NO | UART_MODE_TX |
                 UART_MODE_RX;                     // 8bit, no parity, rx/tx uart
  UART1->CTLR2 = UART_STOPBITS1;                   // 1 stop bit
  UART1->CTLR3 = UART_DMAREQ_TX | UART_DMAREQ_RX; // enable dma requests both ways

  // Set the Baudrate, assuming 48KHz
  uart_set_baud(c->baud);
  uart_enable();

#if IO_UART_USB_CDC
  uart_enable_idle_irq();
#endif  /* IO_UART_USB_CDC */

  // Enable the UART interrupt
  uart_enable_irq();
}

//------------------------------------------------------------------------------

void uart_print(const char *s) {
  while (*s) {
    uart_tx_put(*s);
    s++;
  }
}

//------------------------------------------------------------------------------

void uart_printnl(const char *s) {
  uart_print(s);
  uart_tx_put('\r');
  uart_tx_put('\n');
}

//------------------------------------------------------------------------------

#endif  /* IO_UART */
