#include "Interrupts/ApicHandler.h"
#include "Interrupts/MSRegister.h"
#include "Syscall/CPUID/CPUID.h"

#include "Uefi.h"
#include "Library/UefiLib.h"
#include "Graphics/KernText.h"

VOID
CpuSetApicBase (
  IN UINTN  APIC
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
  IN UINTN  Register
  )
{
  return *((volatile UINTN *)(CpuGetApicBase () + Register));
}

VOID
WriteAPICRegister (
  IN UINTN  Register,
  IN UINTN  Value
  )
{
  *((volatile UINTN *)(CpuGetApicBase () + Register)) = Value;
}

VOID
EnableAPIC (
  )
{
  if (CheckAPIC () == FALSE) {
    kprintf ("[APIC]: APIC is unavailable! Halting system...\n");

    for ( ;;) {
      __asm__ ("cli; hlt");
    }
  }

  CpuSetApicBase (CpuGetApicBase ());

  WriteAPICRegister (0xF0, ReadAPICRegister (0xF0) | 0x100);
}
