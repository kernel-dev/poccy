section .text
global DisableInterrupts
global EnableInterrupts

DisableInterrupts:
    cli

    ret

EnableInterrupts:
    sti

    ret