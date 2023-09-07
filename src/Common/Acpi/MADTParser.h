#ifndef MADTPARSER_H
#define MADTPARSER_H

#include "KernEfiAcpi.h"

#include <Uefi.h>

#define PCAT_COMPAT  (1 << 0)

typedef struct {
  UINT8     LocalAPICIDs[256];
  UINT8     NumberOfCores;
  UINT64    LocalAPICPointer;
  UINT64    IOAPICPointer;
} __attribute__ ((packed)) MADTData;

typedef struct {
  CHAR8     Signature[4]; // 'A' 'P' 'I' 'C' Signature
  UINT32    Length;
  UINT8     Revision;
  UINT8     Checksum;     // Table must sum up to zero.
  CHAR8     OEMID[4];
  CHAR8     OEMTableID[8];
  UINT32    OEMRevision;
  CHAR8     CreatorID[4];
  UINT32    CreatorRevision;
  UINT32    LocalAPICAddr;
  UINT32    APICFlags;      // I don't know why it's 32 bits. We only need the first bit. Rest are reserved.
  UINT8     Entries[];
} __attribute__ ((packed)) MADT;

MADTData *
DetectCores (
  IN EFI_ACPI_DESCRIPTION_HEADER  *Xsdt
  );

#endif /* MADTParser.h */
