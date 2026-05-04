#include "vga.h"

#define WIDTH 80
#define HEIGHT 25

static volatile unsigned short* vgaBuffer = (unsigned short*)0xb8000;

void VGA_clearScreen() {
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		vgaBuffer[i] = (0 << 8) | 0x20;
	}
}

void VGA_printChar(char c, unsigned char attrib, unsigned int x, unsigned int y) {
	vgaBuffer[y * WIDTH + x] = (attrib << 8) | c;
}

void VGA_printStr(const char* s, unsigned char attrib, unsigned int x, unsigned int y) {
	unsigned int count = 0;
	while(s[count] != '\0') {
		vgaBuffer[y * WIDTH + x + count] = (attrib << 8) | s[count];
		count++;
	}
}
