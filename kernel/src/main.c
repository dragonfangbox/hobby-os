extern void kmain(void) {
	
	unsigned char* vgaBuffer = (unsigned char*)0xb8000;

	*vgaBuffer = (unsigned char)'Z';

	while (1);

	return;
}
