# WCHSDK

**WCHSDK** is a Software Development Kit for WCH microcontrollers. It provides:
- Peripheral drivers and hardware abstraction layers
- Example projects and templates
- Utilities for easy MCU initialization and peripheral control

Designed to simplify development on WCH MCU platforms and speed up prototyping.
**Note:** This SDK is a refactored fork of the ch32fun library.

## Update Status Overview
|PERIPHERAL    |V003|V00x|V10x|V205|V20x|V30x|X035(643\*)|L103(M103\*)|M030| 641|
|:-------------|:--:|:--:|:--:|:--:|:--:|:--:|:---------:|:----------:|:--:|:--:|
|DPAL Header\* |2.0 | ×  |2.7 | ×  | ×  | ×  | √         |1.5         | ×  |1.3 |
|ADC           |1.9 | ×  |2.1 | ×  | ×  | ×  |1.3        |1.5         | ×  | √  |
|AWU           |N/A |N/A |N/A |N/A |N/A |N/A | √         |N/A         |N/A |N/A |
|BKP           |N/A |N/A |2.1 | ×  | ×  | ×  |N/A        |1.5         |N/A |N/A |
|CAN           |N/A |N/A |N/A | ×  | ×  | ×  |N/A        |1.5         |N/A |N/A |
|CRC           |N/A |N/A |2.1 | ×  | ×  | ×  |N/A        |1.5         |N/A |N/A |
|DAC           |N/A |N/A |N/A |N/A |N/A | ×  |N/A        |N/A         |N/A |N/A |
|DBGMCU        |1.5 | ×  |2.1 | ×  | ×  | ×  | √         |1.5         | ×  |1.2 |
|DMA           | √  | ×  | √  | ×  | ×  | ×  | √         |1.5         | ×  | √  |
|DVP           |N/A |N/A |N/A |N/A |N/A | ×  |N/A        |N/A         |N/A |N/A |
|ETH           |N/A |N/A |N/A |N/A |N/A | ×  |N/A        |N/A         |N/A |N/A |
|EXIT          | √  | ×  |2.4 | ×  | ×  | ×  | √         |1.5         | ×  | √  |
|FLASH         | √  | ×  |2.7 | ×  | ×  | ×  |1.4        |1.5         | ×  |1.1 |
|FSMC          |N/A |N/A |N/A | ×  |N/A | ×  |N/A        |N/A         |N/A |N/A |
|GPIO          |2.0 | ×  |2.7 | ×  | ×  | ×  |1.6        |1.5         | ×  |1.2 |
|I2C           | √  | ×  | √  | ×  | ×  | ×  |1.7        |1.5         | ×  |1.2 |
|IWDG          | √  | ×  | √  | ×  | ×  | ×  | √         |1.5         |N/A |N/A |
|LPTIM         |N/A |N/A |N/A |N/A |N/A |N/A |N/A        |1.5         |N/A |N/A |
|MISC          | √  | ×  |2.4 |N/A | ×  | ×  |1.6        |1.5         |N/A |1.1 |
|OPA           | √  | ×  |N/A | ×  | ×  | ×  |1.3        |1.5         | ×  |N/A |
|PWR           |1.9 | ×  |2.6 | ×  | ×  | ×  |1.7        |1.5         | ×  | √  |
|QSPI          |N/A |N/A |N/A | ×  |N/A |N/A |N/A        |N/A         |N/A |N/A |
|RCC           |1.8 | ×  |2.7 | ×  | ×  | ×  | √         |1.5         | ×  |1.1 |
|RNG           |N/A |N/A |N/A |N/A |N/A | ×  |N/A        |N/A         |N/A |N/A |
|RTC           |N/A |N/A | √  | ×  | ×  | ×  |N/A        |1.5         |N/A |N/A |
|SPI           |1.9 | ×  |2.7 | ×  | ×  | ×  |1.7        |1.5         | ×  |N/A |
|TIM           |1.6 | ×  | √  | ×  | ×  | ×  | √         |1.5         | ×  | √  |
|TKEY          |N/A |N/A |N/A | ×  |N/A |N/A |N/A        |N/A         |N/A |N/A |
|USART         | √  | ×  |2.4 | ×  | ×  | ×  | √         |1.5         | ×  | √  |
|USB           |N/A |N/A | √  | ×  | ×  | ×  |1.8        |1.5         | ×  |N/A |
|USB_HOST      |N/A |N/A | √  |N/A |N/A |N/A |N/A        |N/A         |N/A |N/A |
|USBPD         |N/A |N/A |N/A |N/A |N/A |N/A |1.4        |1.5         | ×  |1.2 |
|WWWDG         | √  | ×  | √  | ×  | ×  | ×  | √         |1.5         | ×  | √  |
|**chxxxhw.h** | √  | ×  | √  | ×  | √  | √  | √         | √          | ×  | √  |
|**minichlink**| √  | ×  | +  | ×  | √  | √  | √  ( √   )| √  ( ×    )| ×  | √  |

* n.m:  Last commit message of the header file in ch32xxx/EVT/EXAM/SRC/Peripheral/inc
* √:    Merged in , version unspecified
* ×:    Not merged / Unchecked
* +:    Work in progress
* N/A:  No header file with this suffix in EVT, does not mean that the feature is not supported

\* X035(643): They are the same except electrical characteristics, LEDPWM, remapping, and ADC channel numbers.\
\* L103(M103): They use the same register map and header files.\
\* DPAL Header: Device Peripheral Access Layer Header File, normally named as ch32xxx.h

# Configuration

Use the following macros:
USE_CLK_SEC         Use clock security system, enabled by default.
USE_STK_HCLK        Should **SysTick** be at 48 MHz (1) or 6MHz (0) on an '003. Typically set to 0 to divide HCLK by 8.
USE_PLL             Use built-in 2x PLL.
USE_HSE             Use External Oscillator.
USE_HSI             Use HSI Internal Oscillator.
USE_TINYVECTOR      If enabled, Does not allow normal interrupts.
USE_CONSTRUCTORS    Call functions with __attribute__((constructor)) in **wch_init** function.

HSE_BYPASS          Use HSE Bypass feature (for oscillator input)
HSI_TRIM            Use factory calibration on HSI Trim.
SYSCLK_FREQ         Computed Clock in Hz.
HPE_ENABLE          Enable hardware interrupt stack.  Very good on QingKeV4, i.e. x035, v10x, v20x, v30x, but questionable on 003.
DEBUG_HARDFAULT     Log fatal errors with "printf". Only used if USE_DEBUG is set.
DEBUG_TIMEOUT       Arbitrary time units, this is around 200ms. Only used if USE_DEBUG is set.
UART_BAUD_RATE      Only used if USE_UART is set.
