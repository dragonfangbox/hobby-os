bits 64

global _start
extern kmain

section .text
_start:
	cli

	mov eax, 0x0745        	
	mov [0xB8000], ax

	mov esp, stack_top
	call kmain

	jmp $

.bss:
resb 16386
stack_top:
