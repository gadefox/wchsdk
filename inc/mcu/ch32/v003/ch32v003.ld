ENTRY(isr_entry)

MEMORY {
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 16K
  RAM   (xrw): ORIGIN = 0x20000000, LENGTH = 2K
}

SECTIONS {
  .init : {
    _sinit = .;
    . = ALIGN(4);
    KEEP(*(SORT_NONE(.init)))
    . = ALIGN(4);
    _einit = .;
  } >FLASH

  .text : {
    . = ALIGN(4);
    *(.text)
    *(.text.*)
    *(.rodata)
    *(.rodata*)
    *(.gnu.linkonce.t.*)
    . = ALIGN(4);
  } >FLASH

  .fini : {
    KEEP(*(SORT_NONE(.fini)))
    . = ALIGN(4);
  } >FLASH

  PROVIDE(_etext = .);

  .preinit_array : {
    PROVIDE_HIDDEN(__preinit_array_start = .);
    KEEP(*(.preinit_array))
    PROVIDE_HIDDEN(__preinit_array_end = .);
  } >FLASH

  .init_array : {
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)))
    KEEP(*(.init_array))
    PROVIDE_HIDDEN(__init_array_end = .);
  } >FLASH

  .fini_array : {
    PROVIDE_HIDDEN(__fini_array_start = .);
    KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array.*)))
    KEEP(*(.fini_array))
    PROVIDE_HIDDEN(__fini_array_end = .);
  } >FLASH

  .dalign : {
    . = ALIGN(4);
    PROVIDE(_data_vma = .);
  } >RAM AT>FLASH

  .dlalign :  {
    . = ALIGN(4);
    PROVIDE(_data_lma = .);
  } >FLASH

  .data : {
    . = ALIGN(4);
    __global_pointer$ = . + 0x3fc;
    *(.data .data.*)
    *(.sdata .sdata.*)
    . = ALIGN(4);
    PROVIDE(_edata = .);
  } >RAM AT>FLASH

  .bss : {
    . = ALIGN(4);
    PROVIDE(_sbss = .);
    *(.sbss*)
    *(.bss*)
    *(COMMON*)
    . = ALIGN(4);
    PROVIDE(_ebss = .);
  } >RAM

  PROVIDE(_end = _ebss);
  PROVIDE(end = .);
  PROVIDE(_eusrstack = ORIGIN(RAM) + LENGTH(RAM));

  /DISCARD/ : {
    *(.note*)
    *(.eh_frame*)
    *(.comment*)
  }
}
