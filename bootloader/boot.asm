; KERNEL_SECTORS is defined at compile time as the size of the kernel in LBA sectors 
; the img file is in the format [ BOOT ][ STAGE 2 ][    KERNEL     ]
;						   1 sector ^  n sectors ^			 ^
;													  KERNEL_SECTORS sectors

org 0x7C00
bits 16

start:
	jmp 0:main
	nop

main:
	.setup:
		cli	
		xor ax, ax
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		mov ss, ax
		mov sp, 0x9000
		sti

		mov [bootDriveNumber], dl

		call clear_screen

		mov si, helloMsg
		call print_string

	.load_stage2:

		; check if bios has extended int 13h
		mov ah, 0x41
		mov bx, 0x55aa
		mov dl, [bootDriveNumber]
		int 0x13
		jc short .extended_error;

		; now load stage 2
		.retry:
		mov si, DAP 
		mov ah, 0x42
		mov dl, [bootDriveNumber]
		int 0x13
		jc short .read_error

		; jumps to second stage
		mov dl, [bootDriveNumber]
		jmp 0x0000:0x8000

.read_error:
	mov si, readErr
	call print_string
	jmp .retry

.extended_error:
	mov si, extendErr
	call print_string
	jmp $
	
%include "util-inl.asm"

helloMsg: db "Hello from stage 1!", 0
readErr: db "failed to read from disk... retrying...", 0
extendErr: db "int 13h extended not supported, your cooked", 0

bootDriveNumber: db 0

align 16
DAP:
	db 0x10
	db 0x00
blockcount:	dw 4 
	dw 0x8000
	dw 0
	; 0x8000:0x0000
	dq 1 ; which sector to start at

times (510 - ($ - $$)) db 0 
db 0x55, 0xaa
