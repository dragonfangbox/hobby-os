include ../Makefile.variables

.PHONY: assemble


assemble: | $(BUILDDIR)
	$(eval KERNEL_SIZE := $(shell wc -c <  ../$(KERNELBUILD)kernel.bin | xargs))
	$(eval KERNEL_SECTORS := $(shell echo $$(( ($(KERNEL_SIZE) + 511) / $(SECTOR) ))))

	@echo KERNEL_SIZE: $(KERNEL_SIZE)
	@echo KERNEL_SECTORS: $(KERNEL_SECTORS)

	@echo assembling stage 1...
	nasm boot.s -f bin -I bootloader -o $(BUILDDIR)boot.bin

	@echo assembling stage 2...
	nasm -DKERNEL_SECTORS=$(KERNEL_SECTORS) boot-stage2.s -f bin -I bootloader -o $(BUILDDIR)boot-stage2.bin

clean:
	rm -r $(BUILDDIR)

$(BUILDDIR):
	mkdir -p $@
