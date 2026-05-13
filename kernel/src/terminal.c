#include "terminal.h"
#include "vga.h"

static int cursorPos[2] = {0};

void TERMINAL_putChar(char c, unsigned char attrib) {
	VGA_printChar(c, attrib, cursorPos[0], cursorPos[1]);

	cursorPos[0]++;
}
