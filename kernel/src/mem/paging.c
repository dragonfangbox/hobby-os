#include "paging.h"

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
