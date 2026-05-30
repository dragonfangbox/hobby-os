print_string:
		mov al, [si]
		cmp al, 0
		je .done
		
		mov ah, 0x0e
		int 0x10

		inc si
		jmp print_string

	.done:
		mov al, 10
		int 0x10
		mov al, 13
		int 0x10
		ret

clear_screen:
	.clear: 
		mov ax, 0x0700
		mov bx, 0x07
		xor cx, cx
		mov dx, 0x184f
		int 0x10

	.move_cursor:
		mov ax, 0x02
		xor dx, dx
		xor bh, bh
		int 0x10
	
	ret
