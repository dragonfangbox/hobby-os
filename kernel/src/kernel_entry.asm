; the problem is in the linking this asm file and the kernel main file. idk whats wrong

bits 32

global _start

section .text
_start:
	cli
	mov eax, 0x0742        	
	mov [0xB8000], ax

	jmp $

.bss

