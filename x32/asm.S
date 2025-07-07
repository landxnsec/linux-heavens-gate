    .intel_syntax noprefix
    .section .text
    .global _call_64_from_32
    .global _do_syscall

    .code32

_call_64_from_32:

    push ebx
    mov ebx, [esp+8]
    push ebp
    push esp
    push edi
    push esi

    
    call 0x33:_do_syscall

    pop esi
    pop edi
    pop esp
    pop ebp
    pop ebx
    ret

    .code64

_do_syscall:
    mov   eax, [rbx]       
    mov   edi, [rbx+0x8]   
    mov   esi, [rbx+0x10]  
    mov   edx, [rbx+0x18]  
    mov   r10d, [rbx+0x20]
    mov   r8d,  [rbx+0x28]  
    mov   r9d,  [rbx+0x30]  
    syscall
    mov   [rbx+0x38], rax
    retf

