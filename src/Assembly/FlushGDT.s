section .text
global FlushGDT

FlushGDT:
    mov di, [rcx]
    mov rsi, [rcx+2]
    lgdt [rcx]

    ret

__flush:
    ret