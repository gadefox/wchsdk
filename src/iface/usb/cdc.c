#if IFACE_USB_CDC

#define UART_BUFFER_SIZE 256
#define UART_BR          115200

volatile char usb_tx_buffer[UART_BUFFER_SIZE];
volatile int size_to_send = 0;
volatile int send_index = 0;

static uint8_t rx_buffer[UART_BUFFER_SIZE];
static volatile uint16_t rx_write_pos = 0;
static volatile uint16_t rx_read_pos = 0;

static uint8_t tx_buffer[UART_BUFFER_SIZE];
static volatile uint16_t tx_head = 0;
static volatile uint16_t tx_tail = 0;
static volatile uint8_t tx_active = 0;
static volatile uint16_t tx_last_len = 0;

static void uart_setup(void) {
  // turn on GPIOD, UART1, the sram and DMA1 in RCC
  RCC->APB2PCENR |= RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1 | RCC_AHBPeriph_SRAM | RCC_AHBPeriph_DMA1;
  funPinMode(PD5, GPIO_CFGLR_OUT_10Mhz_AF_PP);                                                  // PD5 is uart TX, push pull alt function
  GPIO_pinMode(GPIOv_from_PORT_PIN(GPIO_port_D, 6), GPIO_pinMode_I_floating, GPIO_Speed_10MHz); // PD6 is uart RX, open drain alt function
  USART1->CTLR1 = USART_WordLength_8b | USART_Parity_No | USART_Mode_Tx | USART_Mode_Rx;        // setup no parity, 8bit, rx/tx uart
  USART1->CTLR2 = USART_StopBits_1;                                                             // 1 stop bit
  USART1->CTLR3 = USART_DMAReq_Tx | USART_DMAReq_Rx;                                            // enable dma requests both ways
  USART1->BRR = (FUNCONF_SYSTEM_CORE_CLOCK + UART_BR / 2) / UART_BR;                            // set uart Baudrate
  USART1->CTLR1 |= CTLR1_UE_Set;                                                                // Uart enable
  // tx dma setup (usb -> uart)
  DMA1_Channel4->CFGR &= ~DMA_CFGR1_EN;                                  // disable dma channel (init)
  DMA1_Channel4->PADDR = (uint32_t)&USART1->DATAR;                       // set addr to uart periph's data
  DMA1_Channel4->CFGR = DMA_CFGR1_MINC | DMA_CFGR1_DIR | DMA_CFGR1_TCIE; // set dir to memory -> periph, transfer compete irq
  // no mem addr/ enable yet, start_tx_dma handles that. TX uses a soft ring buffer, while RX uses the dedicated ring buf mode of the uart.
  NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  // rx dma setup (uart -> usb)
  DMA1_Channel5->CFGR &= ~DMA_CFGR1_EN;            // disable dma channel (init)
  DMA1_Channel5->PADDR = (uint32_t)&USART1->DATAR; // set addr to uart periph's data
  DMA1_Channel5->MADDR = (uint32_t)rx_buffer;      // set memory addr to local array
  DMA1_Channel5->CNTR = UART_BUFFER_SIZE;
  DMA1_Channel5->CFGR = DMA_CFGR1_MINC | DMA_CFGR1_CIRC; // circular buf mode, mem increment
  DMA1_Channel5->CFGR |= DMA_CFGR1_EN;                   // enable the RX dma immediately
  USART1->CTLR1 |= USART_CTLR1_IDLEIE;
  NVIC_EnableIRQ(USART1_IRQn);
}

static void start_tx_dma(void) {
  if (tx_active || tx_head == tx_tail)
    return; // nothing to send or busy
  uint16_t len = (tx_head > tx_tail) ? (tx_head - tx_tail) : (UART_BUFFER_SIZE - tx_tail);
  tx_last_len = len;                                    // save for IRQ
  DMA1_Channel4->CFGR &= ~DMA_CFGR1_EN;                 // disable DMA
  DMA1_Channel4->CNTR = len;                            // set transfer count
  DMA1_Channel4->MADDR = (uint32_t)&tx_buffer[tx_tail]; // set memory addr
  DMA1_Channel4->CFGR |= DMA_CFGR1_EN;                  // enable DMA
  tx_active = 1;                                        // mark active
}

// called when UART TX DMA transfer complete interrupt fires
__attribute__((interrupt)) void DMA1_Channel4_IRQHandler(void) {
  DMA1->INTFCR |= DMA_CTCIF4;                           // clear TC flag
  tx_tail = (tx_tail + tx_last_len) % UART_BUFFER_SIZE; // advance tail
  tx_active = 0;                                        // mark idle
  start_tx_dma();                                       // queue next chunk
}

//------------------------------------------------------------------------------
// called when USB endpoint 2 receives OUT data from host

void usb_handle_user_data(usb_ep *usb_ep, uint8_t ep, uint8_t *data,
                          uint32_t len, usb_t *usb) {
  if (ep != 2 || len == 0)
    return; // only EP2 data
  for (uint32_t i = 0; i < len; i++)
    tx_buf[tx_head = (tx_head + 1) % UART_BUFFER_SIZE] = data[i];  // enqueue
  start_tx_dma();                                                  // start if idle
}

//------------------------------------------------------------------------------
// Called when host requests IN data on USB endpoint 3

void usb_handle_user_in_request(usb_ep_t *usb_ep, uint8_t *scratchpad,
                                uint8_t ep, uint32_t tok, usb_t *usb) {
  int chunk = size_to_send - send_index;
  if (chunk <= 0 || ep != 3) {
    usb_send_empty(tok); // wrong EP
    return;
  }

  if (chunk > 8)
    chunk = 8;

  usb_send_data((uint8_t *)(usb_tx_buf + send_index), chunk, 0, tok);  // send chunk
  send_index += chunk;          // advance index
}

//------------------------------------------------------------------------------

#endif  /* IFACE_USB_CDC */
