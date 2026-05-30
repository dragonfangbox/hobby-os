#include "terminal.h"
#include "gdt.h"

static gdt_entry_t gdt[GDT_SIZE];
static gdtr_t gdtr;

extern void gdt_reload_segments(void);

void GDT_init() {
	// null descriptor
	gdt[0] = (gdt_entry_t){0};

	GDT_fillEntry(1, 0, true);
	GDT_fillEntry(2, 0, false);
	GDT_fillEntry(3, 3, true);
	GDT_fillEntry(4, 3, false);

	gdtr.limit = sizeof(gdt) - 1;
	gdtr.base = (uint64_t)gdt;

	TERMINAL_putChar('U', 0b10101010);

	__asm__ volatile(
		"lgdt %0"
		:
		: "m"(gdtr)
		: "memory"
	);

	TERMINAL_putChar('G', 0b10101010);

//	gdt_reload_segments();

}

void GDT_fillEntry(uint8_t entry, uint8_t privilege, bool executable) {
	gdt[entry].limit_low = 0xFFFF;
	gdt[entry].base_low = 0x0000;

	gdt[entry].base_mid = 0x00;

	gdt[entry].access = (1 << 7) | ((privilege & 0x3) << 5) | (1 << 4) | (executable << 3) | (0 << 2) | (1 << 1) | (0 << 0);
	gdt[entry].granularity = (1 << 7) | (0 << 6) | (executable << 5) | (0 << 4) | 0x0F;

	gdt[entry].base_high = 0x00;
}

void GDT_fillEntryTSS() {

}
