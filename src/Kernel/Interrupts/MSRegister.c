//
// Created by Mladen Golo on 27. 8. 2023..
//

#include "Interrupts/MSRegister.h"
#include "Syscall/CPUID/CPUID.h"

#include <cpuid.h>
#include <Uefi.h>

#include <Library/UefiLib.h>

BOOLEAN
CpuHasMSR (
) {
    static UINTN EAX, EDX, UNUSED;

    __cpuid (1, EAX, UNUSED, UNUSED, EDX);

    return EDX & CPUID_FEAT_EDX_MSR;
}

VOID
CpuGetMSR (
        UINTN  MSR,
        UINTN  *Low,
        UINTN  *High
) {
    asm volatile ("rdmsr" : "=a"(Low), "=d"(High) : "c"(MSR));
}


VOID
CpuSetMSR (
        UINTN  MSR,
        UINTN  Low,
        UINTN  High
) {
    asm volatile ("wrmsr" :: "a"(Low), "d"(High), "c"(MSR));
}