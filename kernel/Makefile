.PHONY: all 

all:
	$(eval KERNEL_SIZE := $(shell stat -c%s kernel.bin))
	$(eval KERNEL_SECTORS := $(shell echo $$(( ($(KERNEL_SIZE) + 511) / 512 ))))

	nasm -DKERNEL_SECTORS=$(KERNEL_SECTORS) -f bin -o kernel.bin test.asm
	mv kernel.bin ../kernel.bin
