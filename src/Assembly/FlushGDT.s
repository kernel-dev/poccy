section .text
global FlushGDT

FlushGDT:
    lgdt [rcx]

    ret

__flush:
    ret