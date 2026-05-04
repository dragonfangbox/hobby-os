#include "vga.h"

extern void kmain(void) {
	VGA_clearScreen();

	VGA_printChar('X', 0b00000101, 0, 0);
	VGA_printChar('X', 0b00000101, 0, 1);
	VGA_printChar('X', 0b00000101, 0, 2);

	while(1) { __asm__ volatile ("hlt"); }
	return;
}
