ENTRY(_start)

SECTIONS
{
	. = 0x10000;
	
	.text : ALIGN(4K) {
		*(.text.start)
		*(.text)
		*(.text*)
	}

	.rodata : ALIGN(4K) {
		*(.rodata)
		*(.rodata*)
	}

	.data : ALIGN(4K) {
		*(.data)
		*(.data*)
	}

	.bss : ALIGN(4K) {
		*(.bss)
		*(.bss*)
		*(COMMON)
	}

    kernel_start = ADDR(.text);
    kernel_end = .;
}
