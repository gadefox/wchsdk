#include "wchsdk_cfg.h"
#include "wch/util/mem.h"
#include "wch/sys/init.h"

#include "wch/hw/adc.h"
#include "wch/hw/afio.h"
#include "wch/hw/dbg.h"
#include "wch/hw/def.h"
#include "wch/hw/dma.h"
#include "wch/hw/exten.h"
#include "wch/hw/exti.h"
#include "wch/hw/flash.h"
#include "wch/hw/gpio.h"
#include "wch/hw/i2c.h"
#include "wch/hw/irq.h"
#include "wch/hw/iwdg.h"
#include "wch/hw/opb.h"
#include "wch/hw/pfic.h"
#include "wch/hw/pwr.h"
#include "wch/hw/rcc.h"
#include "wch/hw/spi.h"
#include "wch/hw/stk.h"
#include "wch/hw/tim.h"
#include "wch/hw/uart.h"
#include "wch/hw/vendor.h"
#include "wch/hw/wwdg.h"
#include "wch/hw/xw.h"

int main(void) {
  sys_init();

  return 0;
}
