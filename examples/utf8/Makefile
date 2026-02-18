TARGET := utf8
WCHSDK_MCU := ch32/v003
include wchsdk/makefile

OUTDIR := out
SRCS += $(wildcard *.c)
INC += -I.

SRCOBJS := $(patsubst %.c,$(OUTDIR)/%.o,$(SRCS))
ASMOBJS := $(patsubst %.S,$(OUTDIR)/%_s.o,$(ASMS))
OBJS := $(SRCOBJS) $(ASMOBJS)

CFLAGS += -g -Os $(INC)
LDFLAGS += -T $(WCHSDK_LDSCRIPT) -Wl,-Map=$(OUTDIR)/$(TARGET).map

.PHONY: all build clean

all: build

$(OUTDIR)/%.o: %.c | $(OUTDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/%_s.o: %.S | $(OUTDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/$(TARGET).bin: $(OBJS) | $(OUTDIR)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(OUTDIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $(OUTDIR)/$(TARGET).elf $(OUTDIR)/$(TARGET).bin
	$(OBJCOPY) -O ihex $(OUTDIR)/$(TARGET).elf $(OUTDIR)/$(TARGET).hex
	$(OBJDUMP) -S $(OUTDIR)/$(TARGET).elf > $(OUTDIR)/$(TARGET).lst

$(OUTDIR):
	mkdir -p $(OUTDIR)

build: $(OUTDIR)/$(TARGET).bin

clean:
	rm -rf $(OUTDIR)
