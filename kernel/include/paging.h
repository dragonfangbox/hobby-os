#ifndef PAGING_H
#define PAGING_H

// page directory = a table that points to another page directory
// page table = a table that points to frames
//
// PML4 > page dir
//   PDPR > page dir
//		PD > page dir
//		  PT > page table

#include "types.h"

#define PAGE_SIZE 4096

#endif
