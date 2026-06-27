#include "pmm.h"

#include "types.h"

// about 16mb of memory
#define BITMAP_SIZE 64

static uint64_t bitmap[BITMAP_SIZE] = {0};

static bool is_free(uint64_t location) {
	return (bitmap[(location / 64)] & (1ULL << (location % 64))) == 0;
}

static void set_page(uint64_t location) {
	bitmap[(location / 64)] |= (1ULL << (location % 64));
}

static void clear_page(uint64_t location) {
	bitmap[(location / 64)] &= ~(1ULL << (location % 64));
}

static uint64_t find_free_page() {
	for (uint64_t i = 1; i < BITMAP_SIZE * 64; i++) {
		if (is_free(i)) { 
			return i;
		}
	}

	return 0; // no free page
}

void pmm_init() {
	// set first megabyte as used so we dont overwrite bios stuff
	for (int i = 0; i < 100; i++) {
		set_page(i);
	}
}

uint64_t pmm_alloc_page() {
	uint64_t page = find_free_page();
	if (page == 0) {
		return 0;
	}

	set_page(page);

	return (page * PAGE_SIZE);
}

void pmm_free_page(void* page) {
	clear_page((uint64_t)page / PAGE_SIZE);
}


