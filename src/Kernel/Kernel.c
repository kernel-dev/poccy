#include "../Common/Acpi/KernEfiAcpi.h"
#include "../Common/Assert/KernAssert.h"
#include "../Common/Memory/KernEfiMem.h"
#include "../Common/Memory/KernMem.h"
#include "../Common/Memory/KernMemoryManager.h"
#include "../Common/Graphics/KernGop.h"
#include "../Common/Graphics/KernGraphics.h"
#include "../Common/Graphics/KernFontParser.h"
#include "../Common/Util/KernRuntimeValues.h"

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

// CHAR8 *itoa(UINTN value, CHAR8 *result, UINTN base) {
//     // check that the base if valid
//     if (base < 2 || base > 36) { *result = '\0'; return result; }

//     CHAR8 *ptr = result, *ptr1 = result, tmp_char;
//     UINTN tmp_value;

//     do {
//         tmp_value = value;
//         value /= base;
//         *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
//     } while ( value );

//     // Apply negative sign
//     if (tmp_value < 0) *ptr++ = '-';
//     *ptr-- = '\0';
//     while(ptr1 < ptr) {
//         tmp_char = *ptr;
//         *ptr--= *ptr1;
//         *ptr1++ = tmp_char;
//     }
//     return result;
// }

// VOID DecToHex (UINTN Number, CHAR8 **Result)
// {
//     UINTN Index = 0;

//     while (Number != 0)
//     {
//         UINTN Temp = 0;

//         Temp = Number % 16;

//         if (Temp < 10)
//             (*Result)[Index] = Temp + 48;

//         else
//             (*Result)[Index] = Temp + 55;

//         Index++;
//         Number /= 16;
//     }
// }

// Entry point for kernel
VOID
KernMain (
    IN EFI_RUNTIME_SERVICES                         *RT,
    IN EFI_KERN_MEMORY_MAP                          *MemoryMap,
    IN ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE  **Dsdt,
    IN KERN_FRAMEBUFFER                             *Framebuffer,
    IN VOID                                         *TerminalFont)
{
    FB = Framebuffer;
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
        TRUE);

    //
    //  Test print.
    //
    kprint ("Hello, kernelOS!\n");

    //
    //  Create an internal Bitmap
    //  representation of system memory.
    //
    // KernCreateMMap (MemoryMap);

    // for (UINTN Index = 0; Index < BitmapSize; Index++)
    // {
        // CHAR8 Address[20];

        // DecToHex (Index * MemoryMap->DescriptorSize, &Address);

        // kprint(Address);
        // kprint(": ");
        // kprint(Bitmap[Index].Free == 1 ? "Free" : "Unavailable");
    // }

    //
    //  Should never reach here.
    //  Will be removed later.
    //
    while (TRUE);
}   
