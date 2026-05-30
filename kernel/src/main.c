#include "terminal.h"
#include "types.h"
#include "vga.h"

#include "gdt.h"

extern void kmain(void) {
	GDT_init();

	VGA_clearScreen();

	for (u16 i = 0; i < 256; i++) {
		TERMINAL_putChar('x', i);
	}

	while(1) { __asm__ volatile ("hlt"); }
	return;
}
