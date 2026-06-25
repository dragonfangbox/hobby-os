// [name : # of bits ]
//
// access byte:
//		7						6-5						4 
// [ present : 1 ][ descriptor privilege level : 2 ][ type : 1]
//			3				2				1				0
// [ executable? : 1][ direction : 1][ read/write : 1][ accessible? : 1]
//
// flags:
//			7				6				5			4				3-0
// [ "granularity" : 1][ size : 1][ long mode? : 1][ reserved : 1][ limit[19:16] : 4 ]
//						(^always 0 if long mode)	

#ifndef GDT_H
#define GDT_H

#include "types.h"

#define GDT_SIZE 6
#define GDT_KERNEL_CODE_SEG 0x08
#define GDT_KERNEL_DATA_SEG 0x10
#define GDT_USER_CODE_SEG 0x18
#define GDT_USER_DATA_SEG 0x20

typedef struct  {
	uint16_t limit_low;
	uint16_t base_low;
	
	uint8_t base_mid;

	uint8_t access;
	uint8_t granularity; // 4 flag bits + limit[19:16]
						 
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct  {
} __attribute__((packed)) gdt_tss_t;

typedef struct  {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gdtr_t;

void GDT_init();
void GDT_fillEntry(uint8_t entry, uint8_t privilege, bool executable);

#endif
