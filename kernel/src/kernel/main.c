#include "terminal.h"
#include "vga.h"

#include "gdt.h"
#include "idt.h"
#include "pmm.h"
#include "vmm.h"
#include "apic.h"

// kernel is located at physical addr 0x10000
extern void kmain(void) {
	VGA_clearScreen();

	GDT_init();
	IDT_init();

	pmm_init();
	vmm_init();

	apic_init();


	while(1) { __asm__ volatile ("hlt"); }
	return;
}
