gdt_32_start:
    dq 0x0                  ; Null descriptor (required)

gdt_32_code:
    dw 0xFFFF               ; Limit
    dw 0x0                  ; Base low
    db 0x0                  ; Base mid
    db 10011010b            ; Access byte (code segment)
    db 11001111b            ; Granularity and flags
    db 0x0                  ; Base high

gdt_32_data:
    dw 0xFFFF               ; Limit
    dw 0x0
    db 0x0
    db 10010010b            ; Access byte (data segment)
    db 11001111b
    db 0x0

gdt_32_end:

gdt_32_descriptor:
    dw gdt_32_end - gdt_32_start - 1 ; GDT size - 1
    dd gdt_32_start               ; GDT base address

CODE_SEG_32 equ gdt_32_code - gdt_32_start
DATA_SEG_32 equ gdt_32_data - gdt_32_start

	
