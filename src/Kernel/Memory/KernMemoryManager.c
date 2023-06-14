#include "../../Common/Memory/KernMem.h"
#include "../../Common/Memory/KernEfiMem.h"
#include "../../Common/Memory/KernMemoryManager.h"
#include "../../Common/Assert/KernAssert.h"
#include "../../Common/Util/KernRuntimeValues.h"
#include "../../Common/Util/KernString.h"
#include "../../Common/Drivers/IO/serial.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID
AllocateBitmap (
  IN EFI_KERN_MEMORY_MAP  *MemoryMap,
  IN UINTN                __SizeNeeded OPTIONAL
  )
{
  EFI_MEMORY_DESCRIPTOR  *Desc           = MemoryMap->MemoryMap;
  BOOLEAN                SizeUnspecified = __SizeNeeded == 0;

  while (
         (UINTN)Desc < ((UINTN)MemoryMap->MemoryMap + MemoryMap->MemoryMapSize) &&
         Desc->PhysicalStart < MEMORY_UPPER_BOUNDARY &&
         Desc->PhysicalStart < 2147483648
         )
  {
    if (SizeUnspecified) {
      BitmapSize += DIV_ROUNDUP (Desc->NumberOfPages, 8);
    }

    Desc = (EFI_MEMORY_DESCRIPTOR *)NEXT_MEMORY_DESCRIPTOR (
                                      Desc,
                                      MemoryMap->DescriptorSize
                                      );

    if (SizeUnspecified) {
      continue;
    }

    if (
        (Desc->Type != EfiConventionalMemory) &&
        (Desc->Type != EfiLoaderCode) &&
        (Desc->Type != EfiLoaderData) &&
        (Desc->Type != EfiBootServicesData)
        )
    {
      continue;
    }

    if (CALC_SIZE_OF_FRAME (Desc) >= __SizeNeeded) {
      Bitmap = (UINT8 *)Desc->PhysicalStart;
      break;
    }
  }

  if (SizeUnspecified) {
    return AllocateBitmap (MemoryMap, BitmapSize);
  }
}

VOID
KernCreateMMap (
  IN EFI_KERN_MEMORY_MAP  *MemoryMap
  )
{
  ASSERT (MemoryMap != NULL);
  ASSERT (MemoryMap->MemoryMap != NULL);

  EFI_MEMORY_DESCRIPTOR  *Entry = MemoryMap->MemoryMap;

  AllocateBitmap (MemoryMap, 0);

  if (Bitmap == NULL) {
    kprint ("[DEBUG::KernMemoryManager]: FAILED TO ALLOCATE BITMAP!\n");

    return;
  }

  kprint ("Start address of bitmap: ");
  kprint (__DecimalToHex ((UINTN)Bitmap, TRUE));
  kprint ("\n");

  while (
         (UINTN)Entry < ((UINTN)MemoryMap->MemoryMap + MemoryMap->MemoryMapSize) &&
         Entry->PhysicalStart < MEMORY_UPPER_BOUNDARY &&
         Entry->PhysicalStart < 2147483648
         )
  {
    if (
        (Entry->Type == EfiConventionalMemory) ||
        (Entry->Type == EfiLoaderCode) ||
        (Entry->Type == EfiLoaderData) ||
        (Entry->Type == EfiBootServicesData) ||
        (Entry->Type == EfiBootServicesCode)
        )
    {
      if (Entry->PhysicalStart == (UINTN)Bitmap) {
        goto exit_bitmap_set;
      }

      UINTN  __Size      = DIV_ROUNDUP (Entry->NumberOfPages, 8);
      UINTN  BitmapPages = DIV_ROUNDUP (BitmapSize, 4096);

      //
      //  Just in case some vendors decide
      //  to have a fucking blast writing the firmware
      //  and don't organise the memory map
      //  by their physical addresses.
      //
      UINTN  Offset      = Entry->PhysicalStart / KERN_SIZE_OF_PAGE;

      for (UINTN i = 0; i < __Size; i++) {
        *(Bitmap + Offset) = 0xFF;
      }

      Index += __Size;
    }

exit_bitmap_set:
    Entry = (EFI_MEMORY_DESCRIPTOR *)NEXT_MEMORY_DESCRIPTOR (Entry, MemoryMap->DescriptorSize);
  }
}
