include ../Makefile.variables

CFLAGS = -O2 -Wall -Wextra -ffreestanding -nostdlib -nostartfiles -m32

SRC_DIR = src

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILDDIR)/%.o, $(SRCS))

ASMOBJ = $(BUILDDIR)/kernel_entry.o

KERNEL_ELF = $(BUILDDIR)/kernel.elf
KERNEL_BIN = $(BUILDDIR)/kernel.bin

all: $(KERNEL_BIN)

$(BUILDDIR)/%.o: $(SRC_DIR)/%.c
	i686-elf-gcc $(CLFAGS) -Isrc -c $< -o $@

$(ASMOBJ): $(SRC_DIR)/kernel_entry.asm
	nasm -f elf32 $< -o $@

$(KERNEL_ELF): $(ASMOBJ) $(OBJS)
	i686-elf-ld -m elf_i386 -T link.ld -o $@ $^

$(KERNEL_BIN): $(KERNEL_ELF)
	i686-elf-objcopy -O binary $< $@

