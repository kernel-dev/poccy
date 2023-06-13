#include "../../Common/Memory/KernMem.h"
#include "../../Common/Memory/KernEfiMem.h"
#include "../../Common/Memory/KernMemoryManager.h"
#include "../../Common/Assert/KernAssert.h"
#include "../../Common/Util/KernRuntimeValues.h"
#include "../../Common/Util/KernString.h"
#include "../../Common/Drivers/IO/serial.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

//
//  FIXME:  Not all physical frames are mapped???
//
VOID
KernCreateMMap (
  IN EFI_KERN_MEMORY_MAP  *MemoryMap
  )
{
  ASSERT (MemoryMap != NULL);
  ASSERT (MemoryMap->MemoryMap != NULL);

  EFI_MEMORY_DESCRIPTOR  *CurrDesc = MemoryMap->MemoryMap;
  UINT8                  Bit = 0;

  do {
    if (CurrDesc->Type == EfiConventionalMemory) {
      for (UINTN Index = 0; Index < CurrDesc->NumberOfPages; Index++) {
        if (Bit == 8) {
          Bit = 0;
        }

        Bitmap[BitmapSize] |= (1 << Bit);
        Bit++;
      }
    }

    Bitmap[BitmapSize] = 0x00;

    BitmapSize++;

    CurrDesc = (EFI_MEMORY_DESCRIPTOR *)NEXT_MEMORY_DESCRIPTOR (
                                          CurrDesc,
                                          MemoryMap->DescriptorSize
                                          );
  } while (
    CurrDesc->PhysicalStart < (MemoryMap->MemoryMap + MemoryMap->MemoryMapSize)->PhysicalStart &&
    CurrDesc->PhysicalStart < MEMORY_UPPER_BOUNDARY
  );
}
