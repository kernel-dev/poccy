#ifndef KERN_MEMORY_MANAGER_H
#define KERN_MEMORY_MANAGER_H

#include "./KernEfiMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

#define CREATE_BITMAP_FROM_ENTRY(ENTRY, OFFSET)               \
  (ENTRY->PhysicalStart +                                    \
    ((ENTRY->NumberOfPages - OFFSET) * KERN_SIZE_OF_PAGE)    \
    )

#define CALC_SIZE_OF_FRAME(ENTRY) ENTRY->NumberOfPages * KERN_SIZE_OF_PAGE

/**
    Structure defining a physical memory page.
 **/
typedef struct {
  EFI_PHYSICAL_ADDRESS    Address;          // Beginning physical address of this page.
  UINT32                  Size;             // Size of this page.
  VOID                    *Buffer;          // The data this page holds.
  BOOLEAN                 Free;             // Whether or not this page is free to use.
} KERN_PHYSICAL_PAGE;

/**
    Structure defining an internal representation
    of a process's virtual memory space.
 **/
typedef struct {
  KERN_PHYSICAL_PAGE    *Pages;             // An array of mapped physical pages for this VM.
  UINT32                NumOfPages;         // The number of pages allocated for this VM.
  UINT32                SizeOfPage;         // The size of each physical page.
  UINT8                 ProcessId;          // The identification value of the process.
}   InternalVMBlock;

/**
    Internal error codes for
    page faults.
 **/
enum PageFaultReason {
  OutOfMemory,          // Out of memory
  InvalidAccess,        // Process accessed an invalid memory page.
  InternalError         // Something went wrong internally.
};

/**
    Finds the first suitable physical frame
    in the UEFI system memory map
    and allocates the bitmap to that frame.

    @param[in]  MemoryMap     The UEFI system memory map passed
                              by the bootloader.
    @param[in]  __SizeNeeded  The size of the bitmap in bytes.
                              If this is not provided, the size
                              will be calculated first, then
                              the function will be called another
                              time with the size provided.
 **/
VOID
AllocateBitmap (
  IN EFI_KERN_MEMORY_MAP  *MemoryMap,
  IN UINTN                __SizeNeeded OPTIONAL
  );

/**
    Constructs a bitmap representation
    of the system memory.

    @param[in]  MemoryMap   The UEFI system memory map passed
                            by the bootloader.
 **/
VOID
KernCreateMMap (
  IN EFI_KERN_MEMORY_MAP  *MemoryMap
  );

#endif /* KernMemoryManager.h */
