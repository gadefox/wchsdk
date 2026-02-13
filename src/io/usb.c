#if IO_USB

#include "wch/hw/dbg.h"
#include "wch/hw/gpio.h"
#include "wch/hw/rcc.h"
#include "wch/hw/tim.h"
#include "wch/io/usb.h"

//------------------------------------------------------------------------------

#define USB_GPIO  EXP(GPIO, USB_PORT)

//------------------------------------------------------------------------------

static usb_t usb_data;
static uint32_t *usb_always0;

//------------------------------------------------------------------------------

#if IO_USB_DBG

#define NUMUEVENTS  32

static uint32_t events[NUMUEVENTS * 4];
static volatile uint8_t eventhead, eventtail;

//------------------------------------------------------------------------------

void usb_log_event(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
  int event = eventhead;
  uint32_t *e = &events[event * 4];
  e[0] = a;
  e[1] = b;
  e[2] = c;
  e[3] = d;
  eventhead = (event + 1) & (NUMUEVENTS - 1);
}

//------------------------------------------------------------------------------

uint32_t *usb_get_event(void) {
  int event = eventtail;
  if (eventhead == event)
    return 0;
  eventtail = (event + 1) & (NUMUEVENTS - 1);
  return &events[event * 4];
}

#endif  /* IO_USB_DBG */

//------------------------------------------------------------------------------

void usb_ini(void) {
  usb_data.se0_windup = 0;

  // Enable GPIOs
  RCC->APB2PCENR |= EXP(RCC_APB2PERIPH_GPIO, USB_PORT) | RCC_APB2PERIPH_AFIO;

#if IO_USB_DEBUG_TIMING
  RCC->APB2PCENR |= RCC_IOPCEN | RCC_TIM1EN;

  // PC4 is MCO (for watching timing)
  GPIOC->CFGLR = GPIO_PIN_OUT_50_PP(0) | GPIO_PIN_OUT_50_PP(2) |
                 GPIO_PIN_OUT_50_AF_PP(3) | GPIO_PIN_OUT_50_AF_PP(4) |
                 GPIO_CFGLR_MODE4_0 | GPIO_CFGLR_MODE4_1 | GPIO_CFGLR_CNF4_1;
  RCC->CFGR0 &= ~RCC_CFGR0_MCO;
  RCC->CFGR0 |= RCC_CFGR0_MCO_SYSCLK;

  // Initialize timer
  TIM1->PSC = 0;                             // PWM is used for debug timing.<Left>
  TIM1->ATRLR = 0xFFFF;                      // Auto Reload - sets period
  TIM1->SWEVGR |= TIM_UG;                    // Reload immediately
  TIM1->CCER |= TIM_CC3E | TIM_CC3NP;        // Enable CH4 output, positive pol
  TIM1->CHCTLR2 |= TIM_OC3M_2 | TIM_OC3M_1;  // CH2 Mode is output, PWM1 (CC1S = 00, OC1M = 110)
  TIM1->CH3CVR = 2;                          // Set the Capture Compare Register value to 50% initially
  TIM1->BDTR |= TIM_MOE;                     // Enable TIM1 outputs
  TIM1->CTLR1 |= TIM_CEN;                    // Enable TIM1
#endif  /* IO_USB_DEBUG_TIMING */

  // GPIO Setup
  USB_GPIO->CFGLR &= ~(GPIO_PIN_MASK(USB_USB_PIN_DP) |
#ifdef USB_PIN_DPU
                       GPIO_PIN_MASK(USB_PIN_DPU) |
#endif  /* USB_PIN_DPU */
                       GPIO_PIN_MASK(USB_USB_PIN_DM));

  USB_GPIO->CFGLR |= GPIO_CFGLR_IN_PUPD(USB_USB_PIN_DP) |
#ifdef USB_PIN_DPU
                     GPIO_PIN_OUT_50_PP(USB_PIN_DPU) |
#endif /* USB_PIN_DPU */
                     GPIO_CFGLR_IN_PUPD(USB_USB_PIN_DP);

  // Configure USB_PIN_DM (D-) as an interrupt on falling edge.
  AFIO->EXTICR = EXP(GPIO_PORTSOURCEGPIO, USB_PORT) << (USB_PIN_DM * 2);  // Configure EXTI interrupt for USB_PIN_DM
  EXTI->INTENR = 1 << USB_PIN_DM;                                            // Enable EXTI interrupt
  EXTI->FTENR = 1 << USB_PIN_DM;                                             // Enable falling edge trigger for USB_PIN_DM (D-)

#ifdef USB_PIN_DPU
  // This drives USB_PIN_DPU (D- Pull-Up) high, which will tell the host that we are going on-bus.
  USB_GPIO->BSHR = 1 << USB_PIN_DPU;
#endif  /* USB_PIN_DPU */

  // enable interrupt
  pfic_enable_irq(IRQ_EXTI7_0);
}

void usb_pid_handle_in(uint32_t addr, uint8_t *data, uint32_t endp, uint32_t unused, usb_t *ist) {
  usb_endpoint_t *e = &ist->eps[endp];
  int sendtok = e->toggle_in ? 0b01001011 : 0b11000011;
  ist->current_endpoint = endp;

#if IO_USB_REBOOT_REPORT
  if (ist->reboot_armed == 2) {
    usb_send_empty(sendtok);

    // Initiate boot into bootloader
    FLASH->BOOT_MODEKEYR = FLASH_KEY1;
    FLASH->BOOT_MODEKEYR = FLASH_KEY2;
    FLASH->STATR = FLASH_STATR_MODE;  // FLASH_STATR_MODE is zero, so, boot bootloader code. Unset for user code.
    FLASH->CTLR = CR_LOCK_Set;
    RCC->RSTSCKR |= RSTSCKR_RMVF_SET;
    PFIC->SCTLR = PFIC_SCTLR_SYSRESET;
  }
#endif  /* IO_USB_REBOOT_REPORT */

#if IO_USB_HANDLE_IN_REQUEST
  if (e->custom || endp) {
    // Can reuse data-stack as scratchpad.
    uint8_t *sendnow = __builtin_assume_aligned(data, 4);
    usb_handle_user_in_request(e, sendnow, endp, sendtok, ist);
    return;
  }
#endif  /* IO_USB_HANDLE_IN_REQUEST */

// Handle IN (sending data back to PC)
  // Do this down here.
  // We do this because we are required to have an in-endpoint.  We don't
  // have to do anything with it, though.
#if IO_USB_TERMINAL
  uint8_t data0 = (uint8_t)DBG->DMDATA0;
  if (data0 == e->opaque) {
    usb_send_data(data0, ENDPOINT0_SIZE, 0, sendtok);
    DBG->DMDATA0 = 0;
    DBG->DMDATA1 = 0;
    e->opaque = 0;
    return;
  }
#endif  /* IO_USB_TERMINAL */

  uint8_t *tsend = e->opaque;
  int offset = (e->count) << 3;
 
  int tosend = (int)e->max_len - offset;
  if (tosend > ENDPOINT0_SIZE)
    tosend = ENDPOINT0_SIZE;
  sendnow = tsend + offset;
  if (tosend <= 0)
    usb_send_empty(sendtok);
  else
    usb_send_data(sendnow, tosend, 0, sendtok);
}

//------------------------------------------------------------------------------

void usb_pid_handle_out(uint32_t addr, uint8_t *data, uint32_t endp, uint32_t unused, usb_t *ist) {
  ist->current_endpoint = endp;

  // We need to handle this here because we could have an interrupt in the middle of a control or big transfer.
  // This will correctly swap back the endpoint.
}

//------------------------------------------------------------------------------

void usb_pid_handle_data(uint32_t this_token, uint8_t *data, uint32_t which_data, uint32_t length, usb_t *ist) {
  // Received data from host.
  int epno = ist->current_endpoint;
  usb_endpoint_t *e = &ist->eps[epno];

  length -= 3;
  uint8_t *data_in = __builtin_assume_aligned(data, 4);

  // Already received this packet.
  if (e->toggle_out != which_data)
    goto just_ack;

  e->toggle_out = !e->toggle_out;

#if IO_USB_HANDLE_USER_DATA || IO_USB_REBOOT_REPORT || IO_USB_TERMINAL
  if (epno || (!ist->setup_request && length > 3)) {
#if IO_USB_REBOOT_REPORT
    if (ist->reboot_armed) {
      uint32_t *base = __builtin_assume_aligned(data_in, 4);
      if (epno == 0 && base[0] == 0xAA3412FD &&
          (base[1] & 0x00FFFFFF) == 0x00DDCCBB) {
        e->count = 7;
        ist->reboot_armed = 2;
        goto just_ack;
      }
     
      ist->reboot_armed = 0;
    }
#endif  /* IO_USB_REBOOT_REPORT */

#if IO_USB_TERMINAL
    if (epno == 0 && data_in[0] == 0xfd) {
      uint32_t *base = __builtin_assume_aligned(data_in, 4);

      DBG->DMDATA0 = base[0];
      DBG->DMDATA1 = base[1];
      DBG->DMDATA0 &= ~(0xFF);

      for (int i = 1; i < 8; i++) {
        if (data_in[i] == 0) {
          DBG->DMDATA0 |= i + 3;
          break;
        }
      }

      goto just_ack;
    }
#endif  /* IO_USB_TERMINAL */

#if IO_USB_HANDLE_USER_DATA
    usb_handle_user_data(e, epno, data_in, length, ist);
#endif  /* IO_USB_HANDLE_USER_DATA */

#if IO_USB_HANDLE_TOKEN
    return;
#endif  /* IO_USB_HANDLE_TOKEN */
  } else
#endif  /* IO_USB_HANDLE_USER_DATA || IO_USB_REBOOT_REPORT || IO_USB_TERMINAL */

  if (ist->setup_request) {
    // For receiving CONTROL-OUT messages into RAM.
    // NOTE: MUST be ALIGNED to 4, and be allocated round_up( payload, 8 ) + 4
    //  opaque points to [length received, but uninitialized before complete][data...]

#if IO_USB_CONTROL_OUT
    if (ist->setup_request == 2) {
      // This mode is where we record control-in data into a pointer and mark it as
      int offset = e->count << 3;
      uint32_t *base = __builtin_assume_aligned(e->opaque, 4);
      uint32_t *dout = __builtin_assume_aligned(((uint8_t *)base) + offset + 4, 4);
      uint32_t *din = __builtin_assume_aligned(data_in, 4);

      if (offset < e->max_len) {
        dout[0] = din[0];
        dout[1] = din[1];
        e->count++;
        if (offset + 8 >= e->max_len)
          base[0] = e->max_len;
      }
      goto just_ack;
    }
#endif  /* IO_USB_CONTROL_OUT */

    usb_urb_t *s = __builtin_assume_aligned((usb_urb_t *)(data_in), 4);
    uint32_t wvi = s->lValueLSBIndexMSB;
    uint32_t wLength = s->wLength;

    // Send just a data packet.
    e->count = 0;
    e->opaque = 0;
    e->custom = 0;
    e->max_len = 0;
    ist->setup_request = 0;

    // int bRequest = s->wRequestTypeLSBRequestMSB >> 8;

    // We shift down because we don't care if USB_RECIP_INTERFACE is set or not.
    // Otherwise we have to write extra code to handle each case if it's set or
    // not set, but in general, there's never a situation where we really care.
    uint32_t reqShl = s->wRequestTypeLSBRequestMSB >> 1;
//    usb_log_event(0, s->wRequestTypeLSBRequestMSB, wvi, s->wLength);

    if (reqShl == (0x0921 >> 1)) {
      // Class request (Will be writing)  This is hid_send_feature_report
#if IO_USB_REBOOT_REPORT
      if (wvi == 0x000003FD)
        ist->reboot_armed = 1;
#endif  /* IO_USB_REBOOT_REPORT */

#if IO_USB_HID_FEATURES
      usb_handle_hid_set_report_start(e, wLength, wvi);
#endif  /* IO_USB_HID_FEATURES */
    } else
#if IO_USB_HID_FEATURES || IO_USB_TERMINAL
    if (reqShl == (0x01a1 >> 1)) {
      // Class read request.
      // The host wants to read back from us. hid_get_feature_report
#if IO_USB_HID_FEATURESS
      usb_handle_hid_get_report_start(e, wLength, wvi);
#endif  /* IO_USB_HID_FEATURESS */

#if IO_USB_USB_TERMINAL
      if ((wvi & 0xFF) == 0xFD) {
        e->opaque = 0;  // If it's 0xFD feature discard anything that could be set in usb_handle_hid_get_report_start
        e->max_len = 1; // If 0 - terminal is sent to the stratosphere
        if (!DBG->DMSTATUS) {
          if ((DBG->DMDATA0 & 0x80)) {
            e->opaque = (uint8_t *)DBG->DMDATA0;
            e->max_len = (DBG->DMDATA0 & 0xF) - 4;
            // e->max_len = 8;
          } else if ((DBG->DMDATA0 & 0xC0) == 0xC0)
            DBG->DMDATA0 = 0;
        } else
          attempt_unlock(2);
      }
#endif  /* IO_USB_USB_TERMINAL */
    } else
#endif  /* IO_USB_HID_FEATURESS */
    if (reqShl == (0x0680 >> 1)) { // GET_DESCRIPTOR = 6 (msb)
      for (int i = 0; i < DESCRIPTOR_LIST_ENTRIES; i++) {
        const struct descriptor_list_struct *dl = &descriptor_list[i];
        if (dl->lIndexValue == wvi) {
          e->opaque = (uint8_t *)dl->addr;
          uint16_t swLen = wLength;
          uint16_t elLen = dl->length;
          e->max_len = (swLen < elLen) ? swLen : elLen;
        }
      }
#if IO_USB_DBG
      if (!e->max_len)
        usb_log_event(1234, dl->lIndexValue, dl->length, 0);
#endif  /* IO_USB_DBG */
    } else if (reqShl == (0x0500 >> 1)) // SET_ADDRESS = 0x05
      ist->my_address = wvi;

    // You could handle SET_CONFIGURATION == 0x0900 here if you wanted.
    // Can also handle GET_CONFIGURATION == 0x0880 to which we send back { 0x00 }, or the interface number.  (But no one does this).
    // You could handle SET_INTERFACE == 0x1101 here if you wanted.
    //  or
    // USB_REQ_GET_INTERFACE to which we would send 0x00, or the interface #
    else {
#if IO_USB_OTHER_CONTROL
      usb_handle_other_control_message(e, s, ist);
#endif  /* IO_USB_OTHER_CONTROL */
    }
  }
just_ack:
  // Got the right data.  Acknowledge.
  usb_send_data(0, 0, 2, 0xD2); // Send ACK
}

//------------------------------------------------------------------------------

#if !IO_USB_OPTIMIZE_FLASH

void usb_pid_handle_ack(uint32_t dummy, uint8_t *data, uint32_t dummy1, uint32_t dummy2, usb_t *ist) {
  usb_endpoint_t *e = &ist->eps[ist->current_endpoint];
  e->toggle_in = !e->toggle_in;
  e->count++;
}

//------------------------------------------------------------------------------
// Received a setup for a specific endpoint.

void usb_pid_handle_setup(uint32_t addr, uint8_t *data, uint32_t endp, uint32_t unused, usb_t *ist) {
  usb_endpoint_t *e = &ist->eps[endp];
  ist->current_endpoint = endp;
  ist->setup_request = 1;
  e->toggle_in = 1;
  e->toggle_out = 0;
  e->count = 0;
  e->opaque = 0;
}

#endif /* IO_USB_OPTIMIZE_FLASH */

//------------------------------------------------------------------------------

#endif /* IO_USB */
