#include "../Common/Acpi/KernEfiAcpi.h"
#include "../Common/Assert/KernAssert.h"
#include "../Common/Memory/KernEfiMem.h"
#include "../Common/Memory/KernMem.h"
#include "../Common/Memory/KernMemoryManager.h"
#include "../Common/Graphics/KernGop.h"
#include "../Common/Graphics/KernGraphics.h"
#include "../Common/Graphics/KernFontParser.h"
#include "../Common/Util/KernRuntimeValues.h"
#include "../Common/Util/KernString.h"
#include "../Common/Drivers/IO/io.h"
#include "../Common/Drivers/IO/serial.h"

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

// Entry point for kernel
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
  //  Test print.
  //
  kprint ("Hello, kernelOS!\n");

  kprint ("Constructing bitmap memory map...\n");

  //
  //  Create an internal Bitmap
  //  representation of system memory.
  //
  KernCreateMMap (MemoryMap);

  UINTN  Increment = 0;

  for (UINTN Index = 0; Index < BitmapSize; Index++) {
    for (UINTN Bit = 0; Bit < 8; Bit++) {
      CHAR8  *Address = _KernItoa (
                          (UINTN)(MemoryMap->MemoryMap->PhysicalStart + ((Index + Increment) * 4096))
                          );

      WriteSerialStr ("0x");
      WriteSerialStr (Address);
      WriteSerialStr (" : ");
      WriteSerialStr (((Bitmap[Index] >> Bit) & 1) == 1 ? "Free\n" : "Unavailable\n");

      Increment++;
    }
  }

  //
  //  Should never reach here.
  //  Will be removed later.
  //
  for ( ; ;) {
    __asm__ ("hlt");
  }
}
