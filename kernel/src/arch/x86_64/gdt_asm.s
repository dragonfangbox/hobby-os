global gdt_reload_segments

section .text

gdt_reload_segments:
	push 0x08
	lea rax, [rel .reload_CS]
	push rax
	retfq

	.reload_CS:
	mov ax, 0x10
	mov fs, ax
	mov gs, ax
	ret
