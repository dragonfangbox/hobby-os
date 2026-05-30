global _start
extern kmain

section .text.start
bits 64
_start:
	cli

	mov word [abs 0xB8000], 0x0741

	mov rsp, stack_top
	call kmain

	jmp $

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
