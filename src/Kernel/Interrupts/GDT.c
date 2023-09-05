#include "Interrupts/GDT.h"
#include "Graphics/KernText.h"
#include "Util/KernString.h"
#include "Memory/KernMem.h"
#include "Graphics/KernGraphics.h"

#include <Uefi.h>

__attribute__ ((aligned (64))) GDT Gdt = {
  .Null       = { 0, 0, 0, 0,    0,    0 },
  .KernelCode = { 0, 0, 0, 0x9A, 0xA0, 0 },
  .KernelData = { 0, 0, 0, 0x92, 0xC0, 0 },
  .UserCode   = { 0, 0, 0, 0xFA, 0xA0, 0 },
  .UserData   = { 0, 0, 0, 0xF2, 0xC0, 0 }
};

VOID
InitializeDescriptorTables (
  VOID
  )
{
  InitializeGDT ();
}

static VOID
InitializeGDT (
  )
{
  DisableInterrupts ();

  kprintf ("[GDTDescriptor::Before]: BaseAddress: %p\n", &Gdt);

  GDTDescriptor  Descriptor = {
    .Limit       = sizeof (GDT) - 1,
    .BaseAddress = (UINTN)&Gdt
  };

  //
  //    I don't know how this could
  //    possibly happen.
  //
  if (Descriptor.Limit != (sizeof (GDT) - 1)) {
    kprintf ("[GDT]: Limit is misaligned!\n");

    return;
  }

  FlushGDT (&Descriptor);

  GDTDescriptor  Saved;

  asm volatile ("sgdt %0" : "=m" (Saved));

  GDT  *Entry = (GDT *)Saved.BaseAddress;

  kprintf (
    "[GDTEntry]: KernelCode:\n\tLimitLow: %X | BaseLow: %X | BaseMiddle: %X | Access: %X | Granularity: %X | BaseHigh: %X\n\n",
    Entry->KernelCode.LimitLow,
    Entry->KernelCode.BaseLow,
    Entry->KernelCode.BaseMiddle,
    Entry->KernelCode.Access,
    Entry->KernelCode.Granularity,
    Entry->KernelCode.BaseHigh
    );

  kprintf (
    "[GDTEntry]: KernelData:\n\tLimitLow: %X | BaseLow: %X | BaseMiddle: %X | Access: %X | Granularity: %X | BaseHigh: %X\n\n",
    Entry->KernelData.LimitLow,
    Entry->KernelData.BaseLow,
    Entry->KernelData.BaseMiddle,
    Entry->KernelData.Access,
    Entry->KernelData.Granularity,
    Entry->KernelData.BaseHigh
    );

  kprintf (
    "[GDTEntry]: KernelCode:\n\tLimitLow: %X | BaseLow: %X | BaseMiddle: %X | Access: %X | Granularity: %X | BaseHigh: %X\n\n",
    Entry->UserCode.LimitLow,
    Entry->UserCode.BaseLow,
    Entry->UserCode.BaseMiddle,
    Entry->UserCode.Access,
    Entry->UserCode.Granularity,
    Entry->UserCode.BaseHigh
    );

  kprintf (
    "[GDTEntry]: KernelCode:\n\tLimitLow: %X | BaseLow: %X | BaseMiddle: %X | Access: %X | Granularity: %X | BaseHigh: %X\n\n",
    Entry->UserData.LimitLow,
    Entry->UserData.BaseLow,
    Entry->UserData.BaseMiddle,
    Entry->UserData.Access,
    Entry->UserData.Granularity,
    Entry->UserData.BaseHigh
    );
}
