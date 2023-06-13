#ifndef KERN_MEM_H
#define KERN_MEM_H

#include "./KernEfiMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

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
    Allocates the requested memory size
    and returns a pointer to the start
    of the allocated buffer.

    @param[in]  Size    The size of the buffer to allocate (in bytes)
 **/
// VOID *
// kmalloc ( IN UINTN Size );

#endif /* KernMem.h */
