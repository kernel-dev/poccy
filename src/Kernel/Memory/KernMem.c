#include "../../Common/Memory/KernMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID *
KernMemset8 (
  IN  VOID   *PTR,
  IN  INT8   Value,
  IN  UINT8  Count
  )
{
  UINT8  *Dest = PTR;

  while (Count--) {
    *Dest++ = Value;
  }

  return PTR;
}

VOID *
KernMemset16 (
  IN  VOID    *PTR,
  IN  INT16   Value,
  IN  UINT16  Count
  )
{
  UINT16  *Dest = PTR;

  while (Count--) {
    *Dest++ = Value;
  }

  return PTR;
}

VOID *
KernMemset32 (
  IN  VOID    *PTR,
  IN  INT32   Value,
  IN  UINT32  Count
  )
{
  UINT32  *Dest = PTR;

  while (Count--) {
    *Dest++ = Value;
  }

  return PTR;
}

VOID *
KernMemset64 (
  IN  VOID    *PTR,
  IN  INT64   Value,
  IN  UINT64  Count
  )
{
  UINT64  *Dest = PTR;

  while (Count--) {
    *Dest++ = Value;
  }

  return PTR;
}

VOID *
VolatileKernMemset8 (
  IN  VOID   *PTR,
  IN  INT8   Value,
  IN  UINT8  Count
  )
{
  volatile UINT8  *Dest = PTR;

  while (Count--) {
    *Dest++ = Value;
  }

  return PTR;
}

VOID *
VolatileKernMemset16 (
  IN  VOID    *PTR,
  IN  INT16   Value,
  IN  UINT16  Count
  )
{
  volatile UINT16  *Dest = PTR;

  while (Count--) {
    *Dest++ = Value;
  }

  return PTR;
}

VOID *
VolatileKernMemset32 (
  IN  VOID    *PTR,
  IN  INT32   Value,
  IN  UINT32  Count
  )
{
  volatile UINT32  *Dest = PTR;

  while (Count--) {
    *Dest++ = Value;
  }

  return PTR;
}

VOID *
VolatileKernMemset64 (
  IN  VOID    *PTR,
  IN  INT64   Value,
  IN  UINT64  Count
  )
{
  volatile UINT64  *Dest = PTR;

  while (Count--) {
    *Dest++ = Value;
  }

  return PTR;
}

VOID
KernCopyMem (
  IN  VOID   *Destination,
  IN  VOID   *Source,
  IN  UINTN  Size
  )
{
  UINTN  *Dest = (UINTN *)Destination;
  UINTN  *Src  = (UINTN *)Source;

  for (UINTN Index = 0; Index < Size; Index++) {
    Dest[Index] = Src[Index];
  }
}

//
//  TODO:   Implement an algorithm for
//          finding a suitable frame for allocation.
//
VOID *
__FindSuitableFrame (
  IN UINTN  Size,
  IN UINTN  NumberOfPages
  )
{
  
}

//
//  TODO:   Implement malloc.
//
VOID *
kmalloc (
  IN UINTN  Size
  )
{
}
