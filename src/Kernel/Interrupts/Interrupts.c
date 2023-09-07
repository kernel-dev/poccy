#include "Interrupts/Interrupts.h"
#include "Interrupts/IDTRTable.h"

#include <Uefi.h>

__attribute__ ((aligned (0x10))) STATIC InterruptDescriptor IDTs[256];
STATIC IDTRegister  RegisterIDT;
BOOLEAN             Vectors[32];

VOID
IDTSetDescriptor (
  IN UINT8  Vector,
  IN VOID   *InterruptService,
  IN UINT8  Flags
  )
{
  InterruptDescriptor  *Descriptor = &IDTs[Vector];

  Descriptor->ISRLow         = (UINTN)InterruptService & 0xFFFF;
  Descriptor->KernelCS       = 0x9A;
  Descriptor->IST            = 0;
  Descriptor->AttributesType = Flags;
  Descriptor->ISRMid         = ((UINTN)InterruptService >> 16) & 0xFFFF;
  Descriptor->ISRHigh        = ((UINTN)InterruptService >> 32) & 0xFFFFFFFF;
  Descriptor->Reserved       = 0;
}

VOID
InitIDT (
  VOID
  )
{
  RegisterIDT.Base  = (UINTN)&IDTs[0];
  RegisterIDT.Limit = (UINT16)sizeof (InterruptDescriptor) * 255;

  for (UINT8 Vector = 0; Vector < 32; Vector++) {
    IDTSetDescriptor (Vector, isr_stub_table[Vector], 0x8E);

    Vectors[Vector] = TRUE;
  }

  __asm__ volatile ("lidt %0" :: "m"(RegisterIDT));
  __asm__ volatile ("sti");
}

VOID
ExceptionHandler (
  VOID
  )
{
  __asm__ volatile ("cli; hlt");
}
