#include "terminal.h"
#include "types.h"
#include "vga.h"

#include "gdt.h"
#include "idt.h"
#include "apic.h"

extern void kmain(void) {
	VGA_clearScreen();

	GDT_init();
	IDT_init();
	apic_init();


	VGA_printNum64(12345678, 0b11101011, 0, 0);

//	VGA_printStr("hullo2", 0b11101011, 0, 0);

	while(1) { __asm__ volatile ("hlt"); }
	return;
}
