#ifndef KERN_MEM_H
#define KERN_MEM_H

#include "./KernEfiMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

#define KERN_SIZE_OF_PAGE  4096
#define DIV_ROUNDUP(x, y)  ((x + y - 1) / y)

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
KernMemset8 (
  IN  VOID   *PTR,
  IN  INT8   Value,
  IN  UINT8  Count
  );

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
KernMemset16 (
  IN  VOID    *PTR,
  IN  INT16   Value,
  IN  UINT16  Count
  );

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
KernMemset32 (
  IN  VOID    *PTR,
  IN  INT32   Value,
  IN  UINT32  Count
  );

/**
    Fills the provided memory blocks
    with the provided Value for Count bytes.

    @param[in]  PTR     The pointer to the base address of the location.
    @param[in]  Value   The value to fill the memory block with.
    @param[in]  Count   The size of Value in bytes.

    @retval     VOID*   The modified pointer.
 **/
VOID *
KernMemset64 (
  IN  VOID    *PTR,
  IN  INT64   Value,
  IN  UINT64  Count
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
VolatileKernMemset8 (
  IN  VOID   *PTR,
  IN  INT8   Value,
  IN  UINT8  Count
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
VolatileKernMemset16 (
  IN  VOID    *PTR,
  IN  INT16   Value,
  IN  UINT16  Count
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
VolatileKernMemset32 (
  IN  VOID    *PTR,
  IN  INT32   Value,
  IN  UINT32  Count
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
VolatileKernMemset64 (
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
VOID
KernCopyMem (
  IN  VOID    *Destination,
  IN  VOID    *Source,
  IN  UINT64  Size
  );

/**
    Finds a matching frame for the requested size
    of data to be stored.

    @param[in]  Size            The size requested.
    @param[in]  NumberOfPages   The number of pages to allocate.

    @returns    VOID*           The pointer to the start of the frame.
 **/
VOID *
__FindSuitableFrame (
  IN  UINTN  Size,
  IN  UINTN  NumberOfPages
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

#endif /* KernMem.h */
