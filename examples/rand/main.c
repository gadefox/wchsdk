#include "wchsdk_cfg.h"
#include "wch/util/rand.h"
#include "wch/sys/init.h"

int main(void) {
  sys_init();
  rand_seed(0x12345678);

  // Print 4 Random Numbers: 3443170572, 2761041505, 3238759778, 3045866432
  for (int i = 0; i < 4; i++) {
    uint32_t rand = rand_new();
//    printf("Random Number %u: %lu\n", i, rand);
  }

  return 0;
}
