#include "vmm.h"

#include "types.h"
#include "pmm.h"
#include "string.h"

#include "vga.h"

#define PAGE_PRESENT (1 << 0)
#define PAGE_WRITE (1 << 1)
#define PAGE_USER (1 << 2) // user or supervisor

#define PAGE_ADDR_MASK 0x000FFFFFFFFFF000ULL

#define PML4_INDEX(x) (((x) >> 39) & 0x1FF)
#define PDPT_INDEX(x) (((x) >> 30) & 0x1FF)
#define PD_INDEX(x)   (((x) >> 21) & 0x1FF)
#define PT_INDEX(x)   (((x) >> 12) & 0x1FF)
#define PAGE_OFFSET(x) ((x) & 0xFFF)

static uint64_t* current_pml4;

inline uint64_t read_cr3(void) {
    uint64_t value;
    asm volatile (
        "mov %%cr3, %0"
        : "=r"(value)
    );
    return value;
}

inline void write_cr3(uint64_t phys) {
    asm volatile (
        "mov %0, %%cr3"
        :
        : "r"(phys)
        : "memory"
    );
}

void* phys_to_virt(uint64_t phys) {
	return (void*)phys;
}

void* virt_to_phys(uint64_t virt) {
	return (void*)virt;
}

// TODO: invalidate page after clearing a mapping
void map_page(void* phys, void* virt, uint64_t flags) {
	uint64_t table_flags = PAGE_PRESENT | PAGE_WRITE;

	if (flags & PAGE_USER) {
		table_flags |= PAGE_USER;
	}

	uint64_t* pml4 = current_pml4;
	uint16_t pml4_i = PML4_INDEX((uint64_t)virt);

	uint64_t* pdpt;
	if (!(pml4[pml4_i] & PAGE_PRESENT)) {
		uint64_t pdpt_phys = pmm_alloc_page();
		pdpt = phys_to_virt(pdpt_phys);

		memset(pdpt, 0, PAGE_SIZE);

		pml4[pml4_i] = pdpt_phys | table_flags;
	}

	pdpt = phys_to_virt((pml4[pml4_i] & PAGE_ADDR_MASK));
	uint16_t pdpt_i = PDPT_INDEX((uint64_t)virt);

	uint64_t* pd;
	if (!(pdpt[pdpt_i] & PAGE_PRESENT)) {
		uint64_t pd_phys = pmm_alloc_page();
		pd = phys_to_virt(pd_phys);

		memset(pd, 0, PAGE_SIZE);

		pdpt[pdpt_i] = pd_phys | table_flags;
	}

	pd = phys_to_virt(pdpt[pdpt_i] & PAGE_ADDR_MASK);
	uint16_t pd_i = PD_INDEX((uint64_t)virt);

	uint64_t* pt;
	if (!(pd[pd_i] & PAGE_PRESENT)) {
		uint64_t pt_phys = pmm_alloc_page();
		pt = phys_to_virt(pt_phys);

		memset(pt, 0, PAGE_SIZE);

		pd[pd_i] = pt_phys | table_flags;
	}

	pt = phys_to_virt(pd[pd_i] & PAGE_ADDR_MASK);
	uint16_t pt_i = PT_INDEX((uint64_t)virt);

	pt[pt_i] = ((uint64_t) phys & PAGE_ADDR_MASK) | flags | PAGE_PRESENT;
}

void vmm_init() {
	uint64_t pml4_phys = pmm_alloc_page();
	uint64_t* pml4 = phys_to_virt(pml4_phys);

	memset(pml4, 0, PAGE_SIZE);

	current_pml4 = pml4;

	for (uint64_t i = 0; i < 0x200000; i += 0x1000) {
		map_page((void*)i, (void*)i, PAGE_WRITE);
	}

	// new stack position
	uint64_t stack_phys = pmm_alloc_page();
	uint64_t stack_virt = 0x7000000;
	map_page((void*)stack_phys, (void*)stack_virt, PAGE_WRITE);

	write_cr3(pml4_phys);

	asm volatile (
			"mov %0, %%rsp" 
			:
			: "r"(stack_virt + 0x1000) 
			: "memory"
	);	
}
