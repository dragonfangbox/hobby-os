include ../Makefile.variables

CFLAGS = -O0 -g -Wall -Wextra -mcmodel=kernel -fno-exceptions -fno-unwind-tables \
		 -fno-asynchronous-unwind-tables -ffreestanding -nostdlib -nostartfiles -m64 

CFLAGS += -Iinclude/

ASFLAGS = -f elf64

SRCDIR = src/

KERNEL_ELF := build/kernel.elf
KERNEL_BIN := build/kernel.bin

SRCS := 
include src/kernel/Makefile
include src/drivers/Makefile
include src/arch/x86_64/Makefile
include src/mem/Makefile

OBJS := $(SRCS:src/%.c=build/%.o)
OBJS := $(OBJS:src/%.s=build/%.o)

$(info SRCS = $(SRCS))
$(info OBJS = $(OBJS))

all: $(KERNEL_BIN)

$(BUILDDIR)%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)%.o: $(SRCDIR)/%.s 	
	@mkdir -p $(dir $@)
	nasm $(ASFLAGS) $< -o $@

$(KERNEL_ELF): $(OBJS)
	$(LD) -m elf_x86_64 -T link.ld -o $@ $^

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCPY) -O binary $< $@

clean:
	rm -rf build
	
$(BUILDDIR):
	mkdir -p $@

print:
	@echo SRCS=$(SRCS)
	@echo OBJS=$(OBJS)
	@echo ASMSRCS=$(ASMSRCS)
	@echo ASMOBJS=$(ASMOBJS)
