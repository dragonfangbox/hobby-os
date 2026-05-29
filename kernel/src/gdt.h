#ifndef GDT_H
#define GDT_H

#include "types.h"

#define GDT_SIZE 6

typedef struct  {
	u16 limit;
	u16 base_low;
	u8 base_mid;
	byte access;
	byte granularity;
	u8 base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct  {

} __attribute__((packed)) gdt_descriptor_t;

void GDT_init();
void GDT_fillEntry(u16 privilege);

#endif
