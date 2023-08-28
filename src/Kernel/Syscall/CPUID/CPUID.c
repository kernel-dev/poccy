#include "Syscall/CPUID/CPUID.h"
#include "Graphics/KernText.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

BOOLEAN
CheckAPIC (
  )
{
  UINTN  EAX, EDX, UNUSED;

  __cpuid (1, EAX, UNUSED, UNUSED, EDX);

 #ifdef DEBUG_INTERRUPTS
  kprint ("[KERNEL::DEBUG_INTERRUPTS]: The APIC is: ");
  kprint ((EAX & CPUID_FEAT_EDX_APIC) == 1 ? "Present" : "NOT AVAILABLE!");
 #endif
  return EAX & CPUID_FEAT_EDX_APIC;
}
