ENTRY(ivt_entry)
__stack_size = 256;

MEMORY {
  /* Actually at 0x1FFFF000 but the system maps it to 0x00000000 */
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 16K
  RAM   (xrw): ORIGIN = 0x20000000, LENGTH = 2K
}

SECTIONS {
  .init : {
    . = ALIGN(4);
    KEEP(*(SORT_NONE(.init)))
    *(.init.isr)
    . = ALIGN(4);
  } >FLASH

  .text : {
    . = ALIGN(4);
    *(.text .text.*)
    *(.rodata .rodata*)
    . = ALIGN(4);
  } >FLASH

  .data : {
    . = ALIGN(4);
    *(.data.isr)
    PROVIDE(_data_vma = .);
    PROVIDE(_data_lma = LOADADDR(.data));
    *(.data .data.*)
    . = ALIGN(8);
    PROVIDE(__global_pointer$ = . + 0x400);
    *(.sdata .sdata.*)
    *(.srodata*)
    . = ALIGN(4);
    PROVIDE(_edata = .);
  } >RAM AT>FLASH

  .bss : {
    . = ALIGN(4);
    PROVIDE(_sbss = .);
    *(.sbss* .bss* COMMON)
    . = ALIGN(4);
    PROVIDE(_ebss = .);
  } >RAM

  .stack ORIGIN(RAM) + LENGTH(RAM) - __stack_size : {
    PROVIDE(_heap_end = .);
    PROVIDE(_susrstack = .);
    . = . + __stack_size;
    PROVIDE(_eusrstack = .);
  } >RAM
}
