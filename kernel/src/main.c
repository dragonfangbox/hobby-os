#include "terminal.h"
#include "types.h"
#include "vga.h"

extern void kmain(void) {
	VGA_clearScreen();

	for (u16 i = 0; i < 256; i++) {
		TERMINAL_putChar('x', i);
	}

	while(1) { __asm__ volatile ("hlt"); }
	return;
}
