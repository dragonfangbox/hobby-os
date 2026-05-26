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

		.enable_protected:
			cli
			lgdt [gdt_32_descriptor]

			; enables protected mode
			mov eax, cr0
			or eax, 0x1
			mov cr0, eax

			; long jump to 32 bit code
			jmp CODE_SEG_32:protected_mode

bits 32
protected_mode:
	mov ax, DATA_SEG_32
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, 0x9000

;	jmp CODE_SEG_32:0x10000

	.init_long_mode:
		mov eax, 0x0741        	
		mov [0xB8000], ax

		mov edi, PML4T_ADDR
		mov cr3, edi

		mov eax, 0x0742        	
		mov [0xB8000], ax

		xor eax, eax
		mov ecx, PAGE_TABLE_SIZE
		rep stosd

		mov eax, 0x0743        	
		mov [0xB8000], ax


		; 1 = present bit
		; 2 = readable bit
		mov edi,  PML4T_ADDR
		mov dword [edi], PDPT_ADDR & PT_ADDR_MASK | 1 | 2

		mov edi, PDPT_ADDR
		mov dword [edi], PDT_ADDR & PT_ADDR_MASK | 1 | 2

		mov edi, PDT_ADDR 
		mov dword [edi], PT_ADDR & PT_ADDR_MASK | 1 | 2

		mov edi, PT_ADDR
		mov ebx, 1 | 2
		mov ecx, 512

		.set_entry:
			mov dword [edi], ebx
			add ebx, 0x1000
			add edi, 8
			loop .set_entry

		mov eax, cr4
		or eax, CR4_PAE_ENABLE
		mov cr4, eax

		mov ecx, EFER_MSR
		rdmsr
		or eax, EFER_LM_ENABLE
		wrmsr

		mov eax, 0x0753        	
		mov [0xB8000], ax

		mov eax, cr0
		or eax,	CR0_PG_ENABLE | CR0_PM_ENABLE
		mov cr0, eax

		lgdt [gdt_64_descriptor]

		jmp CODE_SEG_64:.long_mode

bits 64
DEFAULT REL

.long_mode:
	cli
	mov ax, DATA_SEG_64 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov [abs 0xB8000], 0x0741
	
	jmp $

bootDriveNumber: db 0

align 16
DAP:
	db 0x10
	db 0x00
	dw KERNEL_SECTORS
	dw 0
	dw 0x1000
	dq 5 ; which sector to start at

%include "gdt32.asm"
%include "gdt64.asm"

PML4T_ADDR equ 0x1000
PDPT_ADDR equ 0x2000
PDT_ADDR equ 0x3000
PT_ADDR equ 0x4000

PT_ADDR_MASK equ 0xffffffffff000

PAGE_TABLE_SIZE equ 4096

CR4_PAE_ENABLE equ 1 << 5

CR0_PM_ENABLE equ 1 << 0
CR0_PG_ENABLE equ 1 << 31

EFER_MSR equ 0xC0000080
EFER_LM_ENABLE equ 1 << 8
;pad to 2048 bytes (4 sectors)
times (2048 - ($ - $$)) db 0
