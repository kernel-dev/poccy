#include "Interrupts/ApicHandler.h"
#include "Interrupts/MSRegister.h"

#include "Uefi.h"
#include "Library/UefiLib.h"

VOID
CpuSetApicBase (
  UINTN  APIC
  )
{
  UINTN  EAX = (APIC & 0xFFFFF0000) | IA32_APIC_BASE_MSR_ENABLE;
  UINTN  EDX = 0;

 #ifdef __PHYSICAL_MEMORY_EXTENSION__
  EDX = (APIC >> 32) | 0x0F;
 #endif

  CpuSetMSR (IA32_APIC_BASE_MSR, EAX, EDX);
}

UINTN
CpuGetApicBase (
  VOID
  )
{
  UINTN  EAX, EDX;

  CpuGetMSR (IA32_APIC_BASE_MSR, &EAX, &EDX);

 #ifdef __PHYSICAL_MEMORY_EXTENSION__
  return (EAX & 0xFFFFF000) | ((EDX & 0x0F) << 32);
 #else
  return (EAX & 0xFFFFF000);
 #endif
}

UINTN
ReadAPICRegister (
  UINTN  Register
  )
{
  return *((volatile UINTN *)(CpuGetApicBase () + Register));
}

VOID
WriteAPICRegister (
  UINTN  Register,
  UINTN  Value
  )
{
  *((volatile UINTN *)(CpuGetApicBase () + Register)) = Value;
}

VOID
EnableAPIC (
  )
{
  CpuSetApicBase (CpuGetApicBase ());

  WriteAPICRegister (0xF0, ReadAPICRegister (0xF0) | 0x100);
}
