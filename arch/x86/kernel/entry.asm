[BITS 32]

SECTION .mboot
global start
start:
	jmp stublet
	
ALIGN 4
mboot:
	MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO ; | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end
    
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    
SECTION .text
ALIGN 4
stublet:
	mov esp, default_stack_pointer
	call cpu_init
	extern multiboot_init
    push ebx
    call multiboot_init
    add esp, 4
    extern main
    call main
    jmp $
    
global cpu_init
cpu_init:
	mov eax, cr0
	and eax, 0x1ffffffb
	or eax, 0x22
    mov cr0, eax
    xor eax, eax
    mov cr3, eax
    mov eax, cr4
    and eax, 0xfffbf9ff
    mov cr4, eax
    ret
    
SECTION .data
    resb 8192               ; This reserves 8KBytes of memory here
default_stack_pointer:

SECTION .note.GNU-stack noalloc noexec nowrite progbits
	
