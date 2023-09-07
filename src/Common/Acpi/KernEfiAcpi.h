#ifndef KERNEFIACPI_H
#define KERNEFIACPI_H

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>

/**
    Structure for a typical SDT (System Description Table)
    header, according to the ACPI 6.5 specification.
 **/
typedef struct {
  CHAR8     Signature[4];
  UINT32    Length;
  UINT8     Revision;
  UINT8     Checksum;
  CHAR8     OemId[6];
  CHAR8     OemTableId[8];
  UINT32    OemRevision;
  CHAR8     CreatorId[4];
  UINT32    CreatorRevision;
} __attribute__ ((packed)) SDT_HEADER;

typedef struct {
  CHAR8     Signature[4];       // 'X' 'S' 'D' 'T'
  UINT32    Length;
  UINT8     Revision;
  UINT8     Checksum;
  CHAR8     OEMID[6];
  CHAR8     OEMTableID[8];
  UINT32    OEMRevision;
  CHAR8     CreatorID[4];
  UINT32    CreatorRevision;
  UINT64    Entries[];          // 8*n, n = Length - sizeof(SDT_HEADER)
} __attribute__ ((packed)) ACPI_XSDT;

/**
    Structure for the DSDT (Differentiated System Description Table),
    according to the ACPI 6.5 specification.
 **/
typedef struct {
  SDT_HEADER    Sdt;
  UINT64        BytecodeCount;
} ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE;

/**
    Attempts to locate the FADT by
    traversing the entries inside of XSDT.

    @param[in]      Xsdt            The XSDT.
    @param[out]     Fadt            The FADT to locate.

    @retval         EFI_SUCCESS     FADT was successfully found in the XSDT.
    @retval         EFI_ERROR       Something went wrong during the traversal.
    @retval         EFI_NOT_FOUND   The FADT could not be located. Maybe it's an ACPI 1.0 system?
                                    In which case, use the RSDT instead.
 **/
EFI_STATUS
EfiLocateFadtFromXsdt (
  IN  EFI_ACPI_DESCRIPTION_HEADER  *Xsdt,
  OUT EFI_ACPI_COMMON_HEADER       **Fadt
  );

/**
    Obtains all necessary tables... (using the RSDP initially)
    - RSDT (ACPI 1.0);
    - XSDT (ACPI 2.0+);
    - FADT;
    - DSDT

    @param[out]     Rsdp            The RSDP to locate.
    @param[out]     Rsdt            The RSDT to locate.
    @param[out]     Xsdt            The XSDT to locate.
    @param[out]     Fadt            The FADT to locate.

    @retval         EFI_SUCCESS     All necessary tables have been found
    @retval         EFI_ERROR       Something went wrong during the discovery process.
    @retval         EFI_NOT_FOUND   RSDP was not found. Something is definitely wrong.
 **/
EFI_STATUS
EfiGetTables (
  OUT EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER  **Rsdp,
  OUT EFI_ACPI_DESCRIPTION_HEADER                   **Rsdt,
  OUT EFI_ACPI_DESCRIPTION_HEADER                   **Xsdt,
  OUT EFI_ACPI_2_0_FIXED_ACPI_DESCRIPTION_TABLE     **Fadt,
  OUT ACPI_DIFFERENTIATED_SYSTEM_DESCRIPTOR_TABLE   **Dsdt
  );

#endif /* KernEfiAcpi.h */
