#ifndef APICHANDLER_H
#define APICHANDLER_H

#include <Uefi.h>

#include <Library/UefiLib.h>

#define IA32_APIC_BASE_MSR         0x1B
#define IA32_APIC_BASE_MSR_BSP     0x100
#define IA32_APIC_BASE_MSR_ENABLE  0x800

VOID
CpuSetApicBase (
  UINTN  APIC
  );

UINTN
CpuGetApicBase (
  VOID
  );

UINTN
ReadAPICRegister (
  UINTN  Register
  );

VOID
WriteAPICRegister (
  UINTN  Register,
  UINTN  Value
  );

VOID
EnableAPIC (
  VOID
  );

#endif /* ApicHandler.h */
