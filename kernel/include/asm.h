#ifndef ASM_H
#define ASM_H

#include "types.h"

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}


static inline void wrmsr(uint64_t msr, uint64_t value)
{
    uint32_t low = value & 0xFFFFFFFF;
    uint32_t high = value >> 32;
    asm volatile (
        "wrmsr"
        :
        : "c"(msr), "a"(low), "d"(high)
    );
}

static inline uint64_t rdmsr(uint64_t msr)
{
    uint32_t low, high;
    asm volatile (
        "rdmsr"
        : "=a"(low), "=d"(high)
        : "c"(msr)
    );
	return ((uint64_t)high << 32) | low;
}

static inline void load_cr3(void* cr3_val) {
	asm volatile ("mov %0 cr3" :: "r"((uint64_t) cr3_val) : "memory");
}

#endif
