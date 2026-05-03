bits 32

global _start
extern kmain

section .text
_start:
	cli
	mov eax, 0x0742        	
	mov [0xB8000], ax

	mov esp, stack_top
	call kmain

	jmp $

.bss
stack_top:
