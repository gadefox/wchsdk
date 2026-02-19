ifndef WCHSDK_MCU
$(error WCHSDK_MCU is not set.)
endif

WCHSDK_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
WCHSDK_INC := $(WCHSDK_DIR)inc/mcu/$(WCHSDK_MCU)

ifeq ("$(wildcard $(WCHSDK_INC))","")
$(error Directory '$(WCHSDK_INC)' does not exist!)
endif

WCHSDK_LDSCRIPT := $(WCHSDK_INC)/$(subst /,,$(WCHSDK_MCU)).ld
$(info $(WCHSDK_LDSCRIPT))
WCHSDK_SRCS := $(shell find $(WCHSDK_DIR)src -name '*.c')
WCHSDK_ASMS := $(shell find $(WCHSDK_DIR)src -name '*.S')
WCHSDK_INC := -I$(WCHSDK_INC) -I$(WCHSDK_DIR)inc -I/usr/include/newlib

CC := riscv64-unknown-elf-gcc
CXX := riscv64-unknown-elf-g++
OBJCOPY := riscv64-unknown-elf-objcopy
OBJDUMP := riscv64-unknown-elf-objdump

CFLAGS := -Wall -march=rv32ec -mabi=ilp32e -static-libgcc -nostdlib \
		  -ffunction-sections -fdata-sections -msmall-data-limit=8
LDFLAGS := -lgcc -Wl,--gc-sections -Wl,--print-memory-usage

SRCS += $(WCHSDK_SRCS)
ASMS += $(WCHSDK_ASMS)
INC += $(WCHSDK_INC)
