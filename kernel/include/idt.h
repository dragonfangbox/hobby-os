#ifndef IDT_H
#define IDT_H

#include "types.h"

#define IDT_SIZE 256

typedef struct {
	uint16_t isr_low;        
	uint16_t code_seg;        
	uint8_t  ist;             
	uint8_t  type_attributes; 
	uint16_t isr_mid;        
	uint32_t isr_high;      
	uint32_t reserved; // zero            
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed)) idtr_t;

void IDT_init(void);
void idt_set_descriptor(uint8_t entry, void* isr, uint8_t flags);

#endif
