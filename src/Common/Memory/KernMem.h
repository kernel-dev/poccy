#ifndef KERN_MEM_H
#define KERN_MEM_H

#include "./KernEfiMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

#define KERN_SIZE_OF_PAGE  4096

#define DIV_ROUNDUP(x, y)       ((x + y - 1) / y)
#define GET_NUM_OF_PAGES(Size)  DIV_ROUNDUP (Size, KERN_SIZE_OF_PAGE)

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
KernMemset (
  IN  VOID   *PTR,
  IN  INTN   Value,
  IN  UINTN  Count
  );

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    This implementation does a volatile write.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
VolatileKernMemset (
  IN  VOID    *PTR,
  IN  INT64   Value,
  IN  UINT64  Count
  );

/**
    Copies the Source buffer
    into the specified destination.

    @param[in]  Destination     The destination to copy the buffer into.
    @param[in]  Source          The source buffer (the data).
    @param[in]  Size            The size of the Source buffer (in bytes).
 **/
VOID *
KernCopyMem (
  IN  VOID    *Destination,
  IN  VOID    *Source,
  IN  UINT64  Size
  );

/**
    Copies the Source buffer
    into the specified destination.

    This implementation does a volatile write.

    @param[in]  Destination     The destination to copy the buffer into.
    @param[in]  Source          The source buffer (the data).
    @param[in]  Size            The size of the Source buffer (in bytes).
 **/
VOID *
KernMemMove (
  IN VOID        *Destination,
  IN CONST VOID  *Source,
  IN UINTN       Count
  );

/**
    Allocates the requested memory size
    and returns a pointer to the start
    of the allocated buffer.

    @param[in]  Size    The size of the buffer to allocate (in bytes)

    @returns    VOID*   The pointer to the start of the allocated buffer.
 **/
VOID *
kmalloc (
  IN UINTN  Size
  );

UINTN
KernMemCmp (
  IN CONST VOID  *First,
  IN CONST VOID  *Second,
  IN UINTN       Bytes
  );

#endif /* KernMem.h */
