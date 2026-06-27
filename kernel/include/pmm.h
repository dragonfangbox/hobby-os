#ifndef PMM_H 
#define PMM_H 

#include "types.h"

// page directory = a table that points to another page directory
// page table = a table that points to frames
//
// PML4 > page dir
//   PDPR > page dir
//		PD > page dir
//		  PT > page table

#define PAGE_SIZE 4096

void pmm_init();

uint64_t pmm_alloc_page();
void pmm_free_page(void* page);

#endif
