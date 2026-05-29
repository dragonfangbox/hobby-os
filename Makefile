include Makefile.variables

.PHONY: image test build run

run: build test

build:
	@echo compiling kernel...
	$(MAKE) -C kernel
	@echo assembling bootloader...
	$(MAKE) -C bootloader 
	@echo creating os image...
	make image

image:
	$(eval KERNEL_SIZE := $(shell wc -c < $(KERNELBUILD)kernel.bin | xargs))
	$(eval KERNEL_SECTORS := $(shell echo $$(( ($(KERNEL_SIZE) + 511) / 512 ))))
	$(eval TOTAL_SECTORS := $(shell echo $$(( 5 + $(KERNEL_SECTORS) ))))

	dd if=/dev/zero of=os.img bs=$(SECTOR) count=$(TOTAL_SECTORS)

	dd if=$(BOOTLOADERBUILD)boot.bin of=os.img bs=$(SECTOR) conv=notrunc seek=0

	dd if=$(BOOTLOADERBUILD)boot-stage2.bin of=os.img bs=$(SECTOR) conv=notrunc seek=1

	dd if=$(KERNELBUILD)kernel.bin of=os.img bs=$(SECTOR) conv=notrunc seek=5

test:
	@echo running...
	qemu-system-x86_64 -drive file=os.img,format=raw -no-reboot --no-shutdown -d int,cpu_reset

clean:
	rm -r $(BOOTLOADERBUILD)
	mkdir $(BOOTLOADERBUILD)

	rm -r $(KERNELBUILD)
	mkdir $(KERNELBUILD)
