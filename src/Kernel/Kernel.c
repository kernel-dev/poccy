#include "Acpi/KernEfiAcpi.h"
#include "Assert/KernAssert.h"
#include "Memory/KernMem.h"
#include "Util/KernString.h"
#include "Drivers/PS2/PS2KeyboardDriver.h"
#include "Interrupts/ApicHandler.h"
#include "Interrupts/GDT.h"

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
  //    Initialize the GDT and IDT.
  //
  InitializeDescriptorTables ();

  //
  //  Enable the APIC if possible.
  //
  EnableAPIC ();

  //
  //  Test print.
  //
  kprint ("Hello, kernelOS!\n");

  House  *my_house = kmalloc (sizeof (House));

  if (my_house != NULL) {
    my_house->Name  = "My House";
    my_house->Owner = "Me2";

    for (UINT32 Index = 0; Index < 5; Index++) {
      kprint ("House of name: ");
      kprint (my_house->Name);
      kprint (" is owned by yours truly, ");
      kprint (my_house->Owner);
      kprint ("\n");
    }
  } else {
 #ifdef DEBUG_MEMORY
    kprint ("[DEBUG::MEMORY::MALLOC]: Failed to allocate memory for 'House' struct!\n");
 #endif
  }

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
