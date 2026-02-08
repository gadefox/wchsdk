#pragma once

#define USE_CLK_SEC      1         // Use clock security system, enabled by default
#define USE_STK_HCLK     0         // Should systick be at 48 MHz (1) or 6MHz (0) on an '003.  Typically set to 0 to divide HCLK by 8.

#define HPE_ENABLE       1         // Enable hardware interrupt stack.  Very good on QingKeV4, i.e. x035, v10x, v20x, v30x, but questionable on 003.
#define USE_PLL          1         // Use built-in 2x PLL

#define USE_HSE          0         // Use External Oscillator
#define HSE_BYPASS       0         // Use HSE Bypass feature (for oscillator input)

#define USE_HSI          1         // Use HSI Internal Oscillator
#define HSI_TRIM         0x10      // Use factory calibration on HSI Trim.

#define SYS_CLK_FREQ     48000000  // Computed Clock in Hz (Default only for 003, other chips have other defaults)

#define USE_TINYVECTOR   0         // If enabled, Does not allow normal interrupts.
#define USE_CONSTRUCTORS 0         // Call functions with __attribute__((constructor)) in SystemInit()

#define DEBUG_HARDFAULT  1         // Log fatal errors with "printf"
#define DEBUG_TIMEOUT    0x100000  // Arbitrary time units, this is around 200ms.
#define UART_BAUD_RATE   115200    // Only used if USE_UARTPRINTF is set.
