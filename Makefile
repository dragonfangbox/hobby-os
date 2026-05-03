SECTOR := 512

.PHONY: assemble image test build run

build:
	@echo compiling kernel...
	$(MAKE) -C kernel
	@echo assembling bootloader...
	make assemble 
	@echo creating os image...
	make image


assemble:
	$(eval KERNEL_SIZE := $(shell stat -c%s kernel/build/kernel.bin))
	$(eval KERNEL_SECTORS := $(shell echo $$(( ($(KERNEL_SIZE) + 511) / 512 ))))

	@echo KERNEL_SIZE: $(KERNEL_SIZE)
	@echo KERNEL_SECTORS: $(KERNEL_SECTORS)

	@echo assembling stage 1...
	nasm bootloader/boot.asm -f bin -I bootloader -o boot.bin

	@echo assembling stage 2...
	nasm -DKERNEL_SECTORS=$(KERNEL_SECTORS) bootloader/boot-stage2.asm -f bin -I bootloader -o boot-stage2.bin

image:
	$(eval KERNEL_SIZE := $(shell stat -c%s kernel.bin))
	$(eval KERNEL_SECTORS := $(shell echo $$(( ($(KERNEL_SIZE) + 511) / 512 ))))
	$(eval TOTAL_SECTORS := $(shell echo $$(( 5 + $(KERNEL_SECTORS) ))))

	@dd if=/dev/zero of=os.img bs=$(SECTOR) count=$(TOTAL_SECTORS)

	@dd if=boot.bin of=os.img bs=$(SECTOR) conv=notrunc seek=0

	@dd if=boot-stage2.bin of=os.img bs=$(SECTOR) conv=notrunc seek=1

	@dd if=kernel/build/kernel.bin of=os.img bs=$(SECTOR) conv=notrunc seek=5

test:
	qemu-system-i386 -drive file=os.img,format=raw -no-reboot --no-shutdown -d int,cpu_reset -serial stdio

run:
	make build
	@echo running...
	make test
