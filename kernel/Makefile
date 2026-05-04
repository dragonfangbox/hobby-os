CFLAGS = -O2 -Wall -Wextra -ffreestanding -nostdlib -nostartfiles -m32

SRC_DIR = src
BUILD_DIR = build

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(SRCS))

ASMOBJ = $(BUILD_DIR)/kernel_entry.o

KERNEL_ELF = $(BUILD_DIR)/kernel.elf
KERNEL_BIN = $(BUILD_DIR)/kernel.bin

all: $(KERNEL_BIN)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	i686-elf-gcc $(CLFAGS) -Isrc -c $< -o $@

$(ASMOBJ): $(SRC_DIR)/kernel_entry.asm
	nasm -f elf32 $< -o $@

$(KERNEL_ELF): $(ASMOBJ) $(OBJS)
	i686-elf-ld -m elf_i386 -T link.ld -o $@ $^

$(KERNEL_BIN): $(KERNEL_ELF)
	i686-elf-objcopy -O binary $< $@

