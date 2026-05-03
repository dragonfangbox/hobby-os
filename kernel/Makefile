.PHONY: all 

all:
	nasm  -f elf32 src/kernel_entry.asm -o build/kernel_entry.o
#	i686-elf-gcc -O2 -Wall -Wextra -ffreestanding -nostdlib -nostartfiles -m32 -c src/main.c -o build/main.o

	i686-elf-ld -m elf_i386 -T link.ld -o build/kernel.elf build/kernel_entry.o

	i686-elf-objcopy -O binary build/kernel.elf build/kernel.bin

