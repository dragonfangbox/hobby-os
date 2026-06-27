#ifndef VMM_H
#define VMM_H

#include "types.h"

void vmm_init();

void* phys_to_virt(uint64_t phys);
void* virt_to_phys(uint64_t virt);

void map_page(void* phys, void* virt, uint64_t flags);
uint64_t* new_page_dir();

uint64_t read_cr3(void);
void write_cr3(uint64_t value);

#endif
