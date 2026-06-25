#ifndef MEM_H
#define MEM_H

#include "types.h"

void* kalloc(uint32_t size);
void* kfree(void* mem);

#endif
