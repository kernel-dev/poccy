#include "Memory/KernMem.h"
#include "Memory/KernMemoryManager.h"
#include "Assert/KernAssert.h"
#include "Util/KernString.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID
AllocateBitmap (
  IN EFI_KERN_MEMORY_MAP  *MemoryMap,
  IN UINTN                SizeNeeded OPTIONAL
  )
{
  EFI_MEMORY_DESCRIPTOR  *Desc           = MemoryMap->MemoryMap;
  BOOLEAN                SizeUnspecified = SizeNeeded == 0;

  while (
    (UINTN)Desc < ((UINTN)MemoryMap->MemoryMap + MemoryMap->MemoryMapSize) &&
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

    if (CALC_SIZE_OF_FRAME (Desc) >= SizeNeeded) {
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
 #ifdef DEBUG_MEMORY
    kprintf ("[DEBUG::MEMORY::CREATE_MMAP]: FAILED TO ALLOCATE BITMAP!\n");
 #endif

    return;
  }

  for (
    EFI_MEMORY_DESCRIPTOR *Entry = MemoryMap->MemoryMap;
    (UINTN)Entry < (UINTN)MemoryMap->MemoryMap + MemoryMap->MemoryMapSize &&
    (UINTN)Entry->PhysicalStart < 2147483648;
    Entry = NEXT_MEMORY_DESCRIPTOR (Entry, MemoryMap->DescriptorSize)
    )
  {
 #ifdef DEBUG_MEMORY
    kprintf (
      "[DEBUG::MEMORY::CREATE_MMAP]: FRAME RANGE: %X - %X",
      Entry->PhysicalStart,
      (Entry->PhysicalStart + (Entry->NumberOfPages * KERN_SIZE_OF_PAGE))
      );
 #endif

    if (Entry->PhysicalStart == (UINTN)Bitmap) {
 #ifdef DEBUG_MEMORY
      kprintf (" [[  IS BITMAP FRAME  ]]!!!\n");
 #endif

      continue;
    }

    if (
      (Entry->Type == EfiConventionalMemory) ||
      (Entry->Type == EfiLoaderCode) ||
      (Entry->Type == EfiLoaderData) ||
      (Entry->Type == EfiBootServicesData) ||
      (Entry->Type == EfiBootServicesCode)
      )
    {
 #ifdef DEBUG_MEMORY
      kprintf (" [[  IS FREE  ]]!\n");
 #endif

      //
      //  Just in case some vendors decide
      //  to have a fucking blast writing the firmware
      //  and don't organise the memory map
      //  by their physical addresses.
      //
      UINTN  Offset = Entry->PhysicalStart * (1 / KERN_SIZE_OF_PAGE);

      for (
        UINTN Index = Entry->PhysicalStart;
        Index < Entry->PhysicalStart + Entry->NumberOfPages * KERN_SIZE_OF_PAGE;
        Index += KERN_SIZE_OF_PAGE
        )
      {
        UINTN  ByteFree = Index / KERN_SIZE_OF_PAGE / 8;
        UINTN  Bit      = (Index / KERN_SIZE_OF_PAGE) % 8;

        Bitmap[ByteFree + Offset] |= (1 << Bit);
      }
    } else {
 #ifdef DEBUG_MEMORY
      kprintf (" [[  IS UNAVAILABLE  ]]!!!\n");
 #endif
    }
  }
}
