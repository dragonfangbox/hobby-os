unsigned short* vgaBuffer = (unsigned short*)0xb8000;

#define WIDTH 80
#define HEIGHT 25

void VGA_clearScreen() {
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		vgaBuffer[i] = (unsigned short)(0 << 8) | 0x20;
	}
}

void VGA_printChar(char c, unsigned char attrib, unsigned int x, unsigned int y) {
	
}

extern void kmain(void) {
	VGA_clearScreen();

	while (1);

	return;
}
