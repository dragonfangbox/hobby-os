include ../Makefile.variables

CFLAGS = -O2 -Wall -Wextra -mcmodel=kernel -fno-exceptions -fno-unwind-tables \
		 -fno-asynchronous-unwind-tables -ffreestanding -nostdlib -nostartfiles -m64 \

SRC_DIR = src

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILDDIR)/%.o, $(SRCS))

ASMOBJ = $(BUILDDIR)/kernel_entry.o

KERNEL_ELF = $(BUILDDIR)/kernel.elf
KERNEL_BIN = $(BUILDDIR)/kernel.bin

all: $(KERNEL_BIN)

$(BUILDDIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

$(ASMOBJ): $(SRC_DIR)/kernel_entry.asm
	nasm -f elf64 $< -o $@

$(KERNEL_ELF): $(ASMOBJ) $(OBJS)
	$(LD) -m elf_x86_64 -T link.ld -o $@ $^

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCPY) -O binary $< $@

