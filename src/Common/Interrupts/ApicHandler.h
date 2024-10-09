#ifndef APICHANDLER_H
#define APICHANDLER_H

#include <Uefi.h>

#include <Library/UefiLib.h>

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100
#define IA32_APIC_BASE_MSR_ENABLE 0x800

VOID CpuSetApicBase(
    IN UINTN APIC);

UINTN
CpuGetApicBase(
    VOID);

UINTN
ReadAPICRegister(
    IN UINTN Register);

VOID WriteAPICRegister(
    IN UINTN Register,
    IN UINTN Value);

VOID
    EnableAPIC(
        VOID);

VOID SendEOI(UINT8 IRQ);

#endif /* ApicHandler.h */
