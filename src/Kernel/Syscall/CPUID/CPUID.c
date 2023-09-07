#include "Syscall/CPUID/CPUID.h"
#include "Graphics/KernText.h"
#include "Memory/KernMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

BOOLEAN
CheckAPIC (
  )
{
  UINTN  EAX, EDX, UNUSED;

  __cpuid (1, EAX, UNUSED, UNUSED, EDX);

 #ifdef DEBUG_INTERRUPTS
  kprintf ("[DEBUG::INTERRUPTS::APIC]: The APIC is: %s\n", (EDX & CPUID_FEAT_EDX_APIC) != 0 ? "Present" : "NOT AVAILABLE!");
 #endif

  return (EDX & (CPUID_FEAT_EDX_APIC)) != 0;
}

VOID
ProcessBrandString (
  OUT CHAR8  *ProcessorBrand
  )
{
  UINT32  Registers[12];

  __cpuid (0x80000000, Registers[0], Registers[1], Registers[2], Registers[3]);

  if (Registers[0] < 0x80000004) {
    return;
  }

  __cpuid (0x80000002, Registers[0], Registers[1], Registers[2], Registers[3]);
  __cpuid (0x80000003, Registers[4], Registers[5], Registers[6], Registers[7]);
  __cpuid (0x80000004, Registers[8], Registers[9], Registers[10], Registers[11]);

  KernCopyMem (ProcessorBrand, Registers, sizeof (Registers));
}
