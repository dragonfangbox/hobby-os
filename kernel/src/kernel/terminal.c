#include "terminal.h"
#include "vga.h"

static int cursorPos[2] = {0};

void TERMINAL_putChar(char c, uint8_t attrib) {
	VGA_printChar(c, attrib, cursorPos[0], cursorPos[1]);

	cursorPos[0]++;

	if (cursorPos[0] % VGAWIDTH == 0) {
		cursorPos[0] = 0;
		cursorPos[1]++;
	}
}
