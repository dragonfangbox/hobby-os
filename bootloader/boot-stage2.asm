org 0x8000
bits 16

start:
	mov [bootDriveNumber], dl

	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x9000

	.load_kernel:

		mov si, DAP 
		mov ah, 0x42
		mov dl, [bootDriveNumber]
		int 0x13

	.enter_protected:
		.enable_a20:
			in al, 0x92
			or al, 2
			out 0x92, al

		mov ah, 0x0E
		mov al, 'X'
		int 0x10

		cli
		lgdt [gdt_descriptor]

		; enables protected mode
		mov eax, cr0
		or eax, 0x1
		mov cr0, eax

		jmp CODE_SEG:init_pm

bits 32
init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, 0x9000

;	mov eax, 0x0741        	
;	mov [0xB8000], ax

	jmp CODE_SEG:0x10000
	

bootDriveNumber: db 0

align 16
DAP:
	db 0x10
	db 0x00
blockcount:	dw KERNEL_SECTORS
	dw 0
	dw 0x1000
	; 0x1000:0x0000
	dq 5 ; which sector to start at

%include "gdt.asm"
;pad to 2048 bytes (4 sectors)
times (2048 - ($ - $$)) db 0
