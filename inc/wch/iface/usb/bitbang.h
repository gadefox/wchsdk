// If you want to use custom functions for the level 2 stack, then say
// USB_BB_CUSTOM_C
// This is mostly useful on things like bootloaders.
//
// Here are your options:
//  #define USB_BB_ADD_EXTI_HANDLER         asm
//  #define USB_BB_ADD_EXTI_MASK            <num>
//  #define USB_BB_CONTROL_OUT              0/1
//  #define USB_BB_DEBUG                    0/1
//  #define USB_BB_DEBUG_TIMING             0/1
//  #define USB_BB_HANDLE_IN_REQUEST        0/1
//  #define USB_BB_HANDLE_USER_DATA         0/1
//  #define USB_BB_HANDLE_TOKEN             0/1
//  #define USB_BB_HID_FEATURES             0/1
//  #define USB_BB_OPTIMIZE_FLASH           0/1
//  #define USB_BB_OTHER_CONTROL            0/1
//  #define USB_BB_REBOOT_REPORT            0/1
//  #define USB_BB_TERMINAL                 0/1
//
//  #define USB_BB_PORT                     A/B/C/D
//  #define USB_BB_PIN_DM                   <gpio>
//  #define USB_BB_PIN_DP                   <gpio>
//  #define USB_BB_PIN_DPU                  <gpio>

#if IFACE_USB_BB

#pragma once

#include <stdint.h>

//------------------------------------------------------------------------------

#if !USE_SYSTICK_HCLK
#error "USB bit-bang requires USE_SYSTICK_HCLK = 1"
#endif  /* USE_SYSTICK_HCLK */

// Reboot:
//  hid_device * hd = hid_open( 0x1209, 0xd003, 0 );
//  uint8_t bufferX[7] = { 0xfd, 0x12, 0x34, 0xaa, 0xbb, 0xcc, 0xdd };
//  r = hid_send_feature_report( hd, bufferX, sizeof(bufferX) );

#ifndef USB_BB_REBOOT_REPORT
#define USB_BB_REBOOT_REPORT  1
#endif  /* USB_BB_REBOOT_REPORT */

#ifndef USB_BB_PORT
#define USB_BB_PORT  D
#endif  /* USB_BB_PORT */

//------------------------------------------------------------------------------
// This can be undone once support for fast-c.lbu / c.sbu is made available.

#ifdef USB_BB_OPTIMIZE_FLASH
typedef uint32_t usb_bb8;
typedef uint32_t usb_bb16;
#else
typedef uint8_t  usb_bb8;
typedef uint16_t usb_bb16;
#endif  /* USB_BB_OPTIMIZE_FLASH */

//------------------------------------------------------------------------------

typedef struct {
  usb_bb8  count;      // ack count / in count
  usb_bb8  toggle_in;  // DATA0 or DATA1?
  usb_bb8  toggle_out; // Out PC->US
  usb_bb8  custom;     // Anything nonzero will incur the custom call.
  usb_bb16 max_len;
  usb_bb16 reserved1;
  uint32_t reserved2;
  uint8_t  *opaque;    // For user.
} usb_endpoint_t;

// Make the size of this a power of 2, otherwise it will be slow to access.
#ifdef USB_BB_OPTIMIZE_FLASH
_Static_assert(sizeof(usb_endpoint_t) == 32, "usb_endpoint must be pow2 sized");
#else
_Static_assert(sizeof(usb_endpoint_t) == 16, "usb_endpoint must be pow2 sized");
#endif  /* USB_BB_OPTIMIZE_FLASH */

//------------------------------------------------------------------------------

typedef struct {
  usb_bb8        current_endpoint;  // Can this be combined with setup_request?
  usb_bb8        my_address;        // Will be 0 until set up.
  usb_bb8        setup_request;     // 0 for non-setup request, 1 after setup token, is allowed to be 2 for control-out if USB_BB_SUPPORT_CONTROL_OUT is set.
#if USB_BB_REBOOT_REPORT
  usb_bb8        reboot_armed;      // If in a 0xFD set feature report.
#else
  usb_bb8        reserved;
#endif  /* USB_BB_REBOOT_REPORT */
  uint32_t       last_se0_cyccount;
  int32_t        delta_se0_cyccount;
  uint32_t       se0_windup;
  usb_endpoint_t eps[USB_BB_ENDPOINTS];
} usb_bb_t;

typedef struct __attribute__((packed)) {
  uint16_t wRequestTypeLSBRequestMSB;
  uint32_t lValueLSBIndexMSB;
  uint16_t wLength;
} usb_urb_t;

//------------------------------------------------------------------------------
// usb_handle_interrupt_in is OBLIGATED to call usb_send_data or usb_send_empty.
// Enable with USB_BB_HANDLE_IN_REQUEST=1
void usb_bb_handle_user_in_request(usb_endpoint_t *e, uint8_t *scratchpad,
    int endp, uint32_t sendtok, usb_bb_t *ist);

//------------------------------------------------------------------------------
// Enable with USB_BB_HID_FEATURES=1
void usb_bb_handle_hid_set_report_start(usb_endpoint_t *e, int reqlen, uint32_t lValueLSBIndexMSB);
void usb_bb_handle_hid_get_report_start(usb_endpoint_t *e, int reqlen, uint32_t lValueLSBIndexMSB);

//------------------------------------------------------------------------------
// Enable with USB_BB_OTHER_CONTROL=1
void usb_bb_handle_other_control_message(usb_endpoint_t *e, usb_urb_t *s, usb_bb_t *ist);

//------------------------------------------------------------------------------
// Received data from the host which is not an internal control message, i.e.
// this could be going to an endpoint or be data coming in for an unidentified
// control message.
// Enable with USB_BB_HANDLE_USER_DATA=1
void usb_bb_handle_user_data(usb_endpoint_t *e, int current_endpoint, uint8_t *data, int len, usb_bb_t *ist);

//------------------------------------------------------------------------------
// Note: This checks addr & endp to make sure they are valid.
void usb_bb_pid_handle_setup(uint32_t addr, uint8_t *data, uint32_t endp, uint32_t unused, usb_bb_t *ist);
void usb_bb_pid_handle_in(uint32_t addr, uint8_t *data, uint32_t endp, uint32_t unused, usb_bb_t *ist);
void usb_bb_pid_handle_out(uint32_t addr, uint8_t *data, uint32_t endp, uint32_t unused, usb_bb_t *ist);
void usb_bb_pid_handle_data(uint32_t this_token, uint8_t *data, uint32_t which_data, uint32_t length, usb_bb_t *ist);
void usb_bb_pid_handle_ack(uint32_t dummy, uint8_t *data, uint32_t dummy2, uint32_t dummy3, usb_bb_t *ist);

//------------------------------------------------------------------------------
// poly_function = 0 to include CRC.
// poly_function = 2 to exclude CRC.
// This function is provided in assembly
void usb_bb_send_data(const void *data, uint32_t length, uint32_t poly_function, uint32_t token);
void usb_bb_send_empty(uint32_t token);

//------------------------------------------------------------------------------

void usb_bb_setup(void);

//------------------------------------------------------------------------------

#if USB_BB_DEBUG
void usb_bb_log_event(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
uint32_t *usb_bb_get_event(void);
#else
#define usb_bb_log_event(a, b, c, d)
#define usb_bb_get_event() 0
#endif  /* USB_BB_DEBUG */

//------------------------------------------------------------------------------

extern usb_bb_t usb_bb_data;
extern uint32_t *usb_bb_always0;

//------------------------------------------------------------------------------

#endif  /* IFACE_USB_BB */
