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

  kprint ("[GDTDescriptor::Before]: BaseAddress: ");
  kprint (__DecimalToHex ((UINTN)&Gdt, TRUE));
  kprint ("\n");

  GDTDescriptor  Descriptor = {
    .Limit       = sizeof (GDT) - 1,
    .BaseAddress = (UINTN)&Gdt
  };

  //
  //    I don't know how this could
  //    possibly happen.
  //
  if (Descriptor.Limit != (sizeof (GDT) - 1)) {
    kprint ("[GDT]: Limit is misaligned!\n");

    return;
  }

  FlushGDT (&Descriptor);

  GDTDescriptor  Saved;

  asm volatile ("sgdt %0" : "=m" (Saved));

  GDT  *Entry = (GDT *)Saved.BaseAddress;

  kprint ("[GDTEntry]: KernelCode: \n");
  kprint ("\tLimitLow: ");
  kprint (__DecimalToHex (Entry->KernelCode.LimitLow, TRUE));
  kprint (" | BaseLow: ");
  kprint (__DecimalToHex (Entry->KernelCode.BaseLow, TRUE));
  kprint (" | BaseMiddle: ");
  kprint (__DecimalToHex (Entry->KernelCode.BaseMiddle, TRUE));
  kprint (" | Access: ");
  kprint (__DecimalToHex (Entry->KernelCode.Access, TRUE));
  kprint (" | Granularity: ");
  kprint (__DecimalToHex (Entry->KernelCode.Granularity, TRUE));
  kprint (" | BaseHigh: ");
  kprint (__DecimalToHex (Entry->KernelCode.BaseHigh, TRUE));
  kprint ("\n");

  kprint ("[GDTEntry]: KernelData: \n");
  kprint ("\tLimitLow: ");
  kprint (__DecimalToHex (Entry->KernelData.LimitLow, TRUE));
  kprint (" | BaseLow: ");
  kprint (__DecimalToHex (Entry->KernelData.BaseLow, TRUE));
  kprint (" | BaseMiddle: ");
  kprint (__DecimalToHex (Entry->KernelData.BaseMiddle, TRUE));
  kprint (" | Access: ");
  kprint (__DecimalToHex (Entry->KernelData.Access, TRUE));
  kprint (" | Granularity: ");
  kprint (__DecimalToHex (Entry->KernelData.Granularity, TRUE));
  kprint (" | BaseHigh: ");
  kprint (__DecimalToHex (Entry->KernelData.BaseHigh, TRUE));
  kprint ("\n");

  kprint ("[GDTEntry]: UserCode: \n");
  kprint ("\tLimitLow: ");
  kprint (__DecimalToHex (Entry->UserCode.LimitLow, TRUE));
  kprint (" | BaseLow: ");
  kprint (__DecimalToHex (Entry->UserCode.BaseLow, TRUE));
  kprint (" | BaseMiddle: ");
  kprint (__DecimalToHex (Entry->UserCode.BaseMiddle, TRUE));
  kprint (" | Access: ");
  kprint (__DecimalToHex (Entry->UserCode.Access, TRUE));
  kprint (" | Granularity: ");
  kprint (__DecimalToHex (Entry->UserCode.Granularity, TRUE));
  kprint (" | BaseHigh: ");
  kprint (__DecimalToHex (Entry->UserCode.BaseHigh, TRUE));
  kprint ("\n");

  kprint ("[GDTEntry]: UserData: \n");
  kprint ("\tLimitLow: ");
  kprint (__DecimalToHex (Entry->UserData.LimitLow, TRUE));
  kprint (" | BaseLow: ");
  kprint (__DecimalToHex (Entry->UserData.BaseLow, TRUE));
  kprint (" | BaseMiddle: ");
  kprint (__DecimalToHex (Entry->UserData.BaseMiddle, TRUE));
  kprint (" | Access: ");
  kprint (__DecimalToHex (Entry->UserData.Access, TRUE));
  kprint (" | Granularity: ");
  kprint (__DecimalToHex (Entry->UserData.Granularity, TRUE));
  kprint (" | BaseHigh: ");
  kprint (__DecimalToHex (Entry->UserData.BaseHigh, TRUE));
  kprint ("\n");
}
