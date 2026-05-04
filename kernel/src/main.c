#include "vga.h"

extern void kmain(void) {
	VGA_clearScreen();
	VGA_printStr("Hello, world!", 0b00000101, 0, 0);

	while(1) { __asm__ volatile ("hlt"); }
	return;
}
