#include "idt.h"

#include "gdt.h" // for code segment
#include "vga.h"

static idt_entry_t idt[IDT_SIZE];
static idtr_t idtr;

extern void* isr_stub_table[];

extern void exception_handler(uint64_t err_num);
void exception_handler(uint64_t err_num) {

	VGA_clearScreen();
	VGA_printStr("EXCEPTION OCCURED", 0b10110101, (VGAWIDTH / 2) - 12, (VGAHEIGHT / 2) - 1);
	VGA_printNum64(err_num, 0b10110101, (VGAWIDTH / 2), (VGAHEIGHT / 2));

	__asm__ volatile("cli; hlt");
}

void IDT_init(void) {
	idtr.base = (uint64_t)idt;
	idtr.limit = sizeof(idt) - 1;

	for (uint16_t i = 0; i < 32; i++) {
		idt_set_descriptor(i, isr_stub_table[i], 0x8E);
	}

	__asm__ volatile ("lidt %0"
					  :
					  : "m"(idtr)
					  );
}

void idt_set_descriptor(uint8_t entry, void* isr, uint8_t flags) {
	idt[entry].isr_low = (uint64_t)isr & 0xFFFF;
	idt[entry].code_seg = GDT_KERNEL_CODE_SEG;
	idt[entry].ist = 0;
	idt[entry].type_attributes = flags;
	idt[entry].isr_mid = ((uint64_t)isr >> 16) & 0xFFFF;
	idt[entry].isr_high = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
	idt[entry].reserved = 0;
}
