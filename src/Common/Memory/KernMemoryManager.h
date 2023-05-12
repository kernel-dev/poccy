#ifndef KERN_MEMORY_MANAGER_H
#define KERN_MEMORY_MANAGER_H

#include "./KernEfiMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

//
//  Obtains the previous memory descriptor.
//
#define PREVIOUS_MEMORY_DESCRIPTOR(MEMORY, SIZE) ( \
    (EFI_MEMORY_DESCRIPTOR *)( \
        (UINT8 *)(MEMORY) - (SIZE) \
    ) \
)

/**
    A bitmap of system memory,
    where each region is marked
    as free or unavailable.
 **/
typedef struct {
    BOOLEAN Free: 1;
} MEMORY_BITMAP;

/**
    Structure defining a physical memory page.
 **/
typedef struct {
    EFI_PHYSICAL_ADDRESS    Address;        // Beginning physical address of this page.
    UINT32                  Size;           // Size of this page.
    VOID                    *Buffer;        // The data this page holds.
    BOOLEAN                 Free;           // Whether or not this page is free to use.
} KERN_PHYSICAL_PAGE;

/**
    Structure defining an internal representation
    of a process's virtual memory space.
 **/
typedef struct {
    KERN_PHYSICAL_PAGE      *Pages;         // An array of mapped physical pages for this VM.
    UINT32                  NumOfPages;     // The number of pages allocated for this VM.
    UINT32                  SizeOfPage;     // The size of each physical page.
    UINT8                   ProcessId;      // The identification value of the process.
}   InternalVMBlock;

/**
    Internal error codes for
    page faults.
 **/
enum PageFaultReason {
    OutOfMemory,        // Out of memory
    InvalidAccess,      // Process accessed an invalid memory page.
    InternalError       // Something went wrong internally.
};

#endif /* KernMemoryManager.h */
