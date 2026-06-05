#include "apic.h"
#include "cpuid.h"

#include "vga.h"

bool x2apic_is_supported() {
	uint32_t eax, ebx, ecx, edx;
	cpuid_count(1, 0, &eax, &ebx, &ecx, &edx);

	VGA_printNum64(ecx, 0b10010101, 24, 8);
	VGA_printNum64(edx, 0b10010101, 24, 10);
	
	return true;
}
