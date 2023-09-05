%macro isr_stub 1
isr_stub_%1:
    call ExceptionHandler
    iretq
%endmacro

section .text
extern ExceptionHandler
global isr_stub_table

; Define ISR stubs
isr_no_err_stub_0: isr_stub 0
isr_no_err_stub_1: isr_stub 1
isr_no_err_stub_2: isr_stub 2
isr_no_err_stub_3: isr_stub 3
isr_no_err_stub_4: isr_stub 4
isr_no_err_stub_5: isr_stub 5
isr_no_err_stub_6: isr_stub 6
isr_no_err_stub_7: isr_stub 7
isr_err_stub_8: isr_stub 8
isr_no_err_stub_9: isr_stub 9
isr_err_stub_10: isr_stub 10
isr_err_stub_11: isr_stub 11
isr_err_stub_12: isr_stub 12
isr_err_stub_13: isr_stub 13
isr_err_stub_14: isr_stub 14
isr_no_err_stub_15: isr_stub 15
isr_no_err_stub_16: isr_stub 16
isr_err_stub_17: isr_stub 17
isr_no_err_stub_18: isr_stub 18
isr_no_err_stub_19: isr_stub 19
isr_no_err_stub_20: isr_stub 20
isr_no_err_stub_21: isr_stub 21
isr_no_err_stub_22: isr_stub 22
isr_no_err_stub_23: isr_stub 23
isr_no_err_stub_24: isr_stub 24
isr_no_err_stub_25: isr_stub 25
isr_no_err_stub_26: isr_stub 26
isr_no_err_stub_27: isr_stub 27
isr_no_err_stub_28: isr_stub 28
isr_no_err_stub_29: isr_stub 29
isr_err_stub_30: isr_stub 30
isr_no_err_stub_31: isr_stub 31

; Define ISR stub table
section .data
isr_stub_table:
    dq isr_stub_0
    dq isr_stub_1
    dq isr_stub_2
    dq isr_stub_3
    dq isr_stub_4
    dq isr_stub_5
    dq isr_stub_6
    dq isr_stub_7
    dq isr_stub_8
    dq isr_stub_9
    dq isr_stub_10
    dq isr_stub_11
    dq isr_stub_12
    dq isr_stub_13
    dq isr_stub_14
    dq isr_stub_15
    dq isr_stub_16
    dq isr_stub_17
    dq isr_stub_18
    dq isr_stub_19
    dq isr_stub_20
    dq isr_stub_21
    dq isr_stub_22
    dq isr_stub_23
    dq isr_stub_24
    dq isr_stub_25
    dq isr_stub_26
    dq isr_stub_27
    dq isr_stub_28
    dq isr_stub_29
    dq isr_stub_30
    dq isr_stub_31
