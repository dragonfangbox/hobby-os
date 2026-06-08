#include "apic.h"

#include "cpuid.h"
#include "asm.h"

#include "vga.h"

#define IA32_APIC_BASE_ADDR_MASK 0xFFFFFF000ULL

static uint64_t apicBaseAddr;

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

}

static uint64_t apic_get_base_addr() {
	return rdmsr(0x1B) & IA32_APIC_BASE_ADDR_MASK;
}

void apic_init() {
	if (!apic_is_supported()) {
		VGA_printStr("apic not supported???", 0b10110100, 20, 20);
		return;
	}

	apicBaseAddr = apic_get_base_addr();

	VGA_printNum64(apicBaseAddr, 0b10110100, 20, 20);
	
}
