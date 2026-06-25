// pause this until paging gets setup. the memory address of the apic base 
// addr and io apic base addr are not mapped

#include "apic.h"

#include "types.h"
#include "cpuid.h"
#include "asm.h"
#include "vga.h"

#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1

#define APIC_MSR_BASE 0x1B
#define APIC_BASE_ADDR_MASK 0xFFFFFF000ULL
#define APIC_ENABLE_BIT (1 << 11)

#define APIC_LVT_TIMER 0x320

static uint32_t apicBaseAddr;

static bool apic_is_supported() {
	uint32_t eax, ebx, ecx, edx;
	cpuid_count(1, 0, &eax, &ebx, &ecx, &edx);
	
	if ((edx & bit_APIC) == 0) { return false; }
	
	return true;
}

static bool x2apic_is_supported() {
	uint32_t eax, ebx, ecx, edx;
	cpuid_count(1, 0, &eax, &ebx, &ecx, &edx);
	
	if ((ecx & bit_X2APIC) == 0) { return false; }
	
	return true;
}

static void disable_pic() {
    outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);
}

static void enable_apic() {
	uint64_t baseMsr = rdmsr(APIC_MSR_BASE);
	baseMsr |= APIC_ENABLE_BIT;
	wrmsr(APIC_MSR_BASE, baseMsr);
}

static inline uint64_t apic_get_base_addr() {
	return rdmsr(APIC_MSR_BASE) & APIC_BASE_ADDR_MASK;
}

static inline void apic_set_reg(uint32_t offset, uint32_t val) {
	*(volatile uint32_t*)((uintptr_t)apicBaseAddr + offset) = val;
}

static inline uint32_t apic_get_reg(uint32_t offset) {
    return *(volatile uint32_t*)((uintptr_t)apicBaseAddr + offset);
}

static void apic_enable_timer() {
	uint32_t timer = apic_get_reg(APIC_LVT_TIMER);
//	VGA_printNum64(timer, 0b10110100, 20, 20);
}

void apic_init() {
	if (!apic_is_supported()) {
		VGA_printStr("apic not supported???", 0b10110100, 20, 20);
		return;
	}

	disable_pic();

	apicBaseAddr = apic_get_base_addr();
	VGA_printNum64(apicBaseAddr, 0b10110100, 20, 20);

	enable_apic();
	//apic_enable_timer();
}
