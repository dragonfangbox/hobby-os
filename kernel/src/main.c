#include "terminal.h"
#include "types.h"
#include "vga.h"

#include "gdt.h"
#include "idt.h"

extern void kmain(void) {
	VGA_clearScreen();
	VGA_printStr("hullo", 0b11101011, 0, 0);

	GDT_init();
	IDT_init();

	VGA_printStr("hullo2", 0b11101011, 0, 0);

	while(1) { __asm__ volatile ("hlt"); }
	return;
}
