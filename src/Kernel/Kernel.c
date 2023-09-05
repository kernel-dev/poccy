#include "Acpi/KernEfiAcpi.h"
#include "Assert/KernAssert.h"
#include "Memory/KernMem.h"
#include "Util/KernString.h"
#include "Drivers/PS2/PS2KeyboardDriver.h"
#include "Interrupts/ApicHandler.h"
#include "Interrupts/GDT.h"
#include "Interrupts/Interrupts.h"
#include "Syscall/CPUID/CPUID.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

typedef struct {
  CHAR8    *Name;
  CHAR8    *Owner;
} House;

//
//  Kernel EP
//
VOID
EfiMain (
  IN EFI_RUNTIME_SERVICES                         *RT,
  IN EFI_KERN_MEMORY_MAP                          *MemoryMap,
  IN ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE  **Dsdt,
  IN KERN_FRAMEBUFFER                             *Framebuffer,
  IN VOID                                         *TerminalFont
  )
{
  FB       = Framebuffer;
  FontFile = TerminalFont;

  //
  //  Clear the screen.
  //
  ScreenClearTerminal ();

  //
  //  Initialize font data
  //
  PSFInit (
    TerminalFont,
    &FontHdr,
    &ExtFontHdr,
    TRUE
    );

  //
  //  Initialize serial I/O.
  //
  InitSerial ();

  //
  //  Create an internal Bitmap
  //  representation of system memory.
  //
  KernCreateMMap (MemoryMap);

  //
  //    Initialize the GDT.
  //
  InitializeDescriptorTables ();

  //
  //    Initialize the IDT.
  //
  InitIDT ();

  //
  //  Enable the APIC if possible.
  //
  EnableAPIC ();

  //
  //  Test print.
  //
  kprintf ("Hello, kernelOS!\n");

  CHAR8  *ProcessorBrand = kmalloc (sizeof (UINTN) * 12 + 1);

  ProcessBrandString (ProcessorBrand);

  kprintf ("[DEBUG::CPUID::BRAND_STRING]: PROCESSOR BRAND STRING: %s\n", ProcessorBrand);

  CHAR8  Key;

  while ((Key = ReadSerial ())) {
    if ((UINTN)Key == 13) {
      kprint ("\n");
      continue;
    }

    PutChar (Key);
  }

  //
  //  Should never reach here.
  //  Will be removed later.
  //
  for ( ;;) {
    __asm__ ("hlt");
  }
}
