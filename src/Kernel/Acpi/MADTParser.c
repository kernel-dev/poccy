#include "Acpi/MADTParser.h"
#include "Acpi/KernEfiAcpi.h"
#include "Assert/KernAssert.h"
#include "Drivers/IO/serial.h"
#include "Graphics/KernText.h"
#include "Memory/KernMem.h"
#include "Util/KernString.h"

#include <Uefi.h>

//
//  FIXME:  For some reason, the MADT parsing
//          is either broken, or the XSDT parsing
//          is broken. The `Size` field of each
//          MADT entry is always equal to 0.
//
MADTData *DetectCores(IN EFI_ACPI_DESCRIPTION_HEADER *Xsdt) {
  MADTData *MadtData = kmalloc(sizeof(MadtData));

  kprintf("Xsdt Address: %p\n", Xsdt);

  kprintf("Xsdt OemID: %c%c%c%c%c%c\n", Xsdt->OemId[0], Xsdt->OemId[1],
          Xsdt->OemId[2], Xsdt->OemId[3], Xsdt->OemId[4], Xsdt->OemId[5]);

  kprintf("Xsdt Revision: %x\n", Xsdt->Revision);

  unsigned char sum = 0;

  for (int i = 0; i < Xsdt->Length; i++) {
    sum += ((char *)Xsdt)[i];
  }

  kprintf("Xsdt Checksum: %x\n", sum);

  kprintf("Xsdt Length: %x\n", Xsdt->Length);

  for (UINT32 Index = 0; Index < (Xsdt->Length - 0x2C) / sizeof(UINT64);
       ++Index) {
    UINT8 *Table = (UINT8 *)((ACPI_XSDT *)Xsdt)->Entries[Index];

    if (Table == NULL) {
      continue;
    }

    char sigStr[5];

    KernCopyMem(sigStr, Table, 4);

    sigStr[4] = 0;

    kprintf("Signature = %s\n", sigStr);

    if (KernMemCmp(sigStr, "APIC", 4) == 0) {
      kprintf("[DEBUG::INTERRUPTS::MADT]: Found MADT (address: %p, offset to "
              "entries: %p) -> Signature: %s\n\n",
              Table, (Table + 0x2A), sigStr);

      UINT64 Length = ((EFI_ACPI_DESCRIPTION_HEADER *)Table)->Length;

      kprintf("[DEBUG::ACPI::MADT]: MADT Length: %x\n", Length);

      UINT8 *Entry = (UINT8 *)(Table + 0x2A);
      while (Entry < (Table + Length)) {
        if (MadtData->NumberOfCores > 32) {
          break;
        }

        switch (*Entry) {
        case 0:
          MadtData->LocalAPICIDs[MadtData->NumberOfCores++] = *(Entry + 3);
          break;

        case 1:
          MadtData->IOAPICPointer = (UINT64) * (Entry + 4);
          break;

        default:
          break;
        }

        Entry += *(Entry + 1);
      }

      break;
    }
  }

  kprintf("[DEBUG::INTERRUPTS::MADT]: MadtData:\n\tNumber of cores: %x | IO "
          "APIC Pointer: %p | Local APIC Pointer: %p\n",
          MadtData->NumberOfCores, MadtData->IOAPICPointer,
          MadtData->LocalAPICPointer);

  if (MadtData->NumberOfCores == 0) {
    return NULL;
  }

  return MadtData;
}
