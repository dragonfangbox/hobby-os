gdt_64_start:
    dq 0x0000000000000000      ; Null descriptor

gdt_64_code:
    dw 0xFFFF                  ; Limit low
    dw 0x0000                  ; Base low
    db 0x00                    ; Base mid
    db 10011010b               ; Access byte
    db 10101111b               ; Flags + limit high
    db 0x00                    ; Base high

gdt_64_data:
    dw 0xFFFF                  ; Limit low
    dw 0x0000                  ; Base low
    db 0x00                    ; Base mid
    db 10010010b               ; Access byte
    db 11001111b               ; Flags + limit high
    db 0x00                    ; Base high

gdt_64_end:

gdt_64_descriptor:
    dw gdt_64_end - gdt_64_start - 1
    dd gdt_64_start

CODE_SEG_64 equ gdt_64_code - gdt_64_start
DATA_SEG_64 equ gdt_64_data - gdt_64_start
