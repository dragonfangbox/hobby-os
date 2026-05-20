#include "vga.h"

static volatile unsigned short* vgaBuffer = (unsigned short*)0xb8000;

void VGA_clearScreen() {
	for (int i = 0; i < VGAWIDTH * VGAHEIGHT; i++) {
		vgaBuffer[i] = (0 << 8) | 0x20;
	}
}

void VGA_printChar(char c, byte attrib, u16 x, u16 y) {
	vgaBuffer[y * VGAWIDTH + x] = (attrib << 8) | c;
}

void VGA_printStr(const char* s, byte attrib, u16 x, u16 y) {
	unsigned int count = 0;
	while(s[count] != '\0') {
		vgaBuffer[y * VGAWIDTH + x + count] = (attrib << 8) | s[count];
		count++;
	}
}
