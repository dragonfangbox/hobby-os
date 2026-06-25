#include "paging.h"

#define INVALID_PAGE UINT64_MAX

#define PAGE_PRESENT (1 << 0)
#define PAGE_WRITE (1 << 1)
#define PAGE_USER (1 << 2) // user or supervisor

// about 16mb of memory
#define BITMAP_SIZE 8

static uint64_t bitmap[BITMAP_SIZE] = {0};

static bool is_free(uint64_t location) {
	return bitmap[(location / 64)] & (1ULL << (location % 64));
}

static void set_page(uint64_t location) {
	bitmap[(location / 64)] |= (1ULL << (location % 64));
}

static void clear_page(uint64_t location) {
	bitmap[(location / 64)] &= ~(1ULL << (location % 64));
}

static uint64_t find_free_page() {
	for (uint64_t i = 0; i < BITMAP_SIZE * 64; i++) {
		if (is_free(i)) { return i; };
	}

	return 0;
}

void pmm_init() {
	set_page(0); // lets us use 0 as an error code
}

void* pmm_alloc_page() {
	uint64_t page = find_free_page();
	if (page == 0) {
		return 0;
	}

	set_page(page);

	return (void*)(page * PAGE_SIZE);
}

void pmm_free_page(void* page) {
	clear_page((uint64_t)page / PAGE_SIZE);
}


