#include "vga.h"

static volatile uint16_t* vgaBuffer = (uint16_t*)0xb8000;

void VGA_clearScreen() {
	for (int i = 0; i < VGAWIDTH * VGAHEIGHT; i++) {
		vgaBuffer[i] = (0 << 8) | 0x20;
	}
}

void VGA_printChar(char c, uint8_t attrib, uint16_t x, uint16_t y) {
	vgaBuffer[y * VGAWIDTH + x] = (attrib << 8) | c;
}

void VGA_printStr(const char* s, uint8_t attrib, uint16_t x, uint16_t y) {
	uint32_t count = 0;
	while(s[count] != '\0') {
		vgaBuffer[y * VGAWIDTH + x + count] = (attrib << 8) | s[count];
		count++;
	}
}

void VGA_printNum64(uint64_t num, uint8_t attrib, uint16_t x, uint16_t y) {
	char buf[21];
	uint32_t i = 0;

	if (num == 0) {
		buf[i++] = '\0';
	} else {
		while (num > 0) {
			buf[i++] = '0' + (num % 10);
			num /= 10;
		}
	}

	for (int32_t j = i - 1; j >= 0; j--) {
		// x + i - 1 - j makes it so it prints just like printstr
		VGA_printChar(buf[j], attrib, (x + i - 1) - j, y);
	}

}
