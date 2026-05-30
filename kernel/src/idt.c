#include "idt.h"

static idt_entry_t idt[IDT_SIZE];
static idtr_t idtr;

void idt_set_gate(uint8_t entry, uint16_t selector) {
	
}
