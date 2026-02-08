// User-configurable macros (see wchsdk_cfg.h):
//  #define IFACE_USB_ADD_EXTI_HANDLER   asm
//  #define IFACE_USB_ADD_EXTI_MASK      <num>
//  #define IFACE_USB_CONTROL_OUT        0/1
//  #define IFACE_USB_DBG                0/1
//  #define IFACE_USB_DBG_TIMING         0/1
//  #define IFACE_USB_HANDLE_IN_REQUEST  0/1
//  #define IFACE_USB_HANDLE_USER_DATA   0/1
//  #define IFACE_USB_HANDLE_TOKEN       0/1
//  #define IFACE_USB_HID_FEATURES       0/1
//  #define IFACE_USB_OPTIMIZE_FLASH     0/1
//  #define IFACE_USB_OTHER_CONTROL      0/1
//  #define IFACE_USB_REBOOT_REPORT      0/1
//  #define IFACE_USB_TERMINAL           0/1
//  #define IFACE_USB_PORT               A/B/C/D
//  #define IFACE_USB_PIN_DM             <gpio>
//  #define IFACE_USB_PIN_DP             <gpio>
//  #define IFACE_USB_PIN_DPU            <gpio>

#if IFACE_USB

#pragma once

#include <stdint.h>

//------------------------------------------------------------------------------

#if !MCU_STK_HCLK
#error "USB bit-bang requires MCU_STK_HCLK = 1"
#endif  /* USE_SYSTICK_HCLK */

//------------------------------------------------------------------------------
// Reboot:
//  hid_device * hd = hid_open( 0x1209, 0xd003, 0 );
//  uint8_t bufferX[7] = { 0xfd, 0x12, 0x34, 0xaa, 0xbb, 0xcc, 0xdd };
//  r = hid_send_feature_report( hd, bufferX, sizeof(bufferX) );

#ifndef IFACE_USB_REBOOT_REPORT
#define IFACE_USB_REBOOT_REPORT  1
#endif  /* IFACE_USB_REBOOT_REPORT */

#ifndef IFACE_USB_PORT
#define IFACE_USB_PORT  D
#endif  /* IFACE_USB_PORT */

#ifndef USB_EP_MAX
#define USB_EP_MAX  8  // Fixed for USB 1.1, Low Speed.
#endif  /* USB_EP_MAX */

//------------------------------------------------------------------------------
// This can be undone once support for fast-c.lbu / c.sbu is made available.

#ifdef IFACE_USB_OPTIMIZE_FLASH
typedef uint32_t usb8_t;
typedef uint32_t usb16_t;
#else
typedef uint8_t  usb8_t;
typedef uint16_t usb16_t;
#endif  /* IFACE_USB_OPTIMIZE_FLASH */

//------------------------------------------------------------------------------

typedef struct {
  usb8_t   count;      // ack count / in count
  usb8_t   toggle_in;  // DATA0 or DATA1?
  usb8_t   toggle_out; // Out PC->US
  usb8_t   custom;     // Anything nonzero will incur the custom call.
  usb16_t  max_len;
  usb16_t  reserved1;
  uint32_t reserved2;
  uint8_t  *opaque;    // For user.
} usb_endpoint_t;

// Make the size of this a power of 2, otherwise it will be slow to access.
#ifdef IFACE_USB_OPTIMIZE_FLASH
_Static_assert(sizeof(usb_endpoint_t) == 32, "usb_endpoint must be pow2 sized");
#else
_Static_assert(sizeof(usb_endpoint_t) == 16, "usb_endpoint must be pow2 sized");
#endif  /* IFACE_USB_OPTIMIZE_FLASH */

//------------------------------------------------------------------------------

typedef struct {
  usb8_t         current_endpoint;  // Can this be combined with setup_request?
  usb8_t         my_address;        // Will be 0 until set up.
  usb8_t         setup_request;     // 0 for non-setup request, 1 after setup token, is allowed to be 2 for control-out if USB_SUPPORT_CONTROL_OUT is set.
#if IFACE_USB_REBOOT_REPORT
  usb8_t         reboot_armed;      // If in a 0xFD set feature report.
#else
  usb8_t         reserved;
#endif  /* IFACE_USB_REBOOT_REPORT */
  uint32_t       last_se0_cyccount;
  int32_t        delta_se0_cyccount;
  uint32_t       se0_windup;
  usb_endpoint_t eps[USB_EP_MAX];
} usb_t;

typedef struct __attribute__((packed)) {
  uint16_t wRequestTypeLSBRequestMSB;
  uint32_t lValueLSBIndexMSB;
  uint16_t wLength;
} usb_urb_t;

//------------------------------------------------------------------------------
// usb_handle_interrupt_in is OBLIGATED to call usb_send_data or usb_send_empty.
// Enable with IFACE_USB_HANDLE_IN_REQUEST=1
void usb_handle_user_in_request(usb_endpoint_t *e, uint8_t *scratchpad,
    int endp, uint32_t sendtok, usb_t *ist);

//------------------------------------------------------------------------------
// Enable with IFACE_USB_HID_FEATURES=1
void usb_handle_hid_set_report_start(usb_endpoint_t *e, int reqlen, uint32_t lValueLSBIndexMSB);
void usb_handle_hid_get_report_start(usb_endpoint_t *e, int reqlen, uint32_t lValueLSBIndexMSB);

//------------------------------------------------------------------------------
// Enable with IFACE_USB_OTHER_CONTROL=1
void usb_handle_other_control_message(usb_endpoint_t *e, usb_urb_t *s, usb_t *ist);

//------------------------------------------------------------------------------
// Received data from the host which is not an internal control message, i.e.
// this could be going to an endpoint or be data coming in for an unidentified
// control message.
// Enable with IFACE_USB_HANDLE_USER_DATA=1
void usb_handle_user_data(usb_endpoint_t *e, int current_endpoint, uint8_t *data, int len, usb_t *ist);

//------------------------------------------------------------------------------
// Note: This checks addr & endp to make sure they are valid.
void usb_pid_handle_setup(uint32_t addr, uint8_t *data, uint32_t endp, uint32_t unused, usb_t *ist);
void usb_pid_handle_in(uint32_t addr, uint8_t *data, uint32_t endp, uint32_t unused, usb_t *ist);
void usb_pid_handle_out(uint32_t addr, uint8_t *data, uint32_t endp, uint32_t unused, usb_t *ist);
void usb_pid_handle_data(uint32_t this_token, uint8_t *data, uint32_t which_data, uint32_t length, usb_t *ist);
void usb_pid_handle_ack(uint32_t dummy, uint8_t *data, uint32_t dummy2, uint32_t dummy3, usb_t *ist);

//------------------------------------------------------------------------------
// poly_function = 0 to include CRC.
// poly_function = 2 to exclude CRC.
// This function is provided in assembly
void usb_send_data(const void *data, uint32_t length, uint32_t poly_function, uint32_t token);
void usb_send_empty(uint32_t token);

//------------------------------------------------------------------------------

void usb_init(void);

//------------------------------------------------------------------------------

#if IFACE_USB_DBG
void usb_log_event(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
uint32_t *usb_get_event(void);
#else
#define usb_log_event(a, b, c, d)
#define usb_get_event() 0
#endif  /* IFACE_USB_DBG */

//------------------------------------------------------------------------------

extern usb_t usb_data;
extern uint32_t *usb_always0;

//------------------------------------------------------------------------------

#endif  /* IFACE_USB */
