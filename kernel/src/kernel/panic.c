#include "panic.h"

#include "vga.h"
#include "types.h"

void kpanic(const char* msg) {
	for (uint32_t x = 0; x < VGAWIDTH; x++) {
		for (uint32_t y = 0; y < VGAHEIGHT; y++) {
			VGA_printChar(' ', VGA_RED_BG | VGA_RED_FG, x, y);
		}
	}

	VGA_printStr(msg, VGA_RED_BG | VGA_BLACK_FG, (VGAWIDTH / 2) - 6, VGAHEIGHT / 2);

	asm volatile ("hlt");
}
