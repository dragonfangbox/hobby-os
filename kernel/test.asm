bits 32
org 0x10000

mov edi, 0xB8000
mov al, 'A'
mov ah, 0x0F
mov [edi], ax

jmp $
