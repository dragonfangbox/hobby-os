include ../Makefile.variables

CFLAGS = -O0 -g -Wall -Wextra -mcmodel=kernel -fno-exceptions -fno-unwind-tables \
		 -fno-asynchronous-unwind-tables -ffreestanding -nostdlib -nostartfiles -m64 

ASFLAGS = -f elf64

SRC_DIR = src

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILDDIR)/%.o, $(SRCS))

ASMSRCS := $(wildcard src/*.s)
ASMOBJS := $(patsubst $(SRC_DIR)/%.s,$(BUILDDIR)/%.o, $(ASMSRCS))

KERNEL_ELF = $(BUILDDIR)/kernel.elf
KERNEL_BIN = $(BUILDDIR)/kernel.bin

all: $(KERNEL_BIN)

$(BUILDDIR)/%.o: $(SRC_DIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

$(BUILDDIR)/%.o: $(SRC_DIR)/%.s | $(BUILDDIR)
	nasm $(ASFLAGS) $< -o $@

$(KERNEL_ELF): $(ASMOBJS) $(OBJS)
	$(LD) -m elf_x86_64 -T link.ld -o $@ $^

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCPY) -O binary $< $@

clean:
	rm -r build
	
$(BUILDDIR):
	mkdir -p $@

print:
	@echo SRCS=$(SRCS)
	@echo OBJS=$(OBJS)
	@echo ASMSRCS=$(ASMSRCS)
	@echo ASMOBJS=$(ASMOBJS)
