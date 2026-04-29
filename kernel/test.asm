bits 32
org 0x10000

mov eax, 0x0741        	
mov [0xB8000], ax

jmp $
