#include "../../Common/Memory/KernMem.h"
#include "../../Common/Util/KernRuntimeValues.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID *
KernMemset (
  IN  VOID   *PTR,
  IN  INTN   Value,
  IN  UINTN  Count
  )
{
  /* CHAR16 is defined as unsigned long */
  CHAR16  *Dest = PTR;

  while (--Count) {
    /* BOOLEAN is defined as unsigned char */
    *Dest++ = (BOOLEAN)Value;
  }

  return PTR;
}

VOID *
VolatileKernMemset (
  IN  VOID    *PTR,
  IN  INT64   Value,
  IN  UINT64  Count
  )
{
  /* CHAR16 is defined as unsigned long */
  volatile CHAR16  *Dest = PTR;

  while (--Count) {
    /* Boolean is defined as unsigned char */
    *Dest++ = (BOOLEAN)Value;
  }

  return PTR;
}

//
//  Thanks, random SO users and Théo for
//  linking this to me.
//
//  This is a fast memcpy implementation.
//
//  Source: https://stackoverflow.com/a/51559967
//
VOID *
KernCopyMem (
  IN  VOID   *Destination,
  IN  VOID   *Source,
  IN  UINTN  Size
  )
{
  UINT8  *Dest = (UINT8 *)Destination;
  UINT8  *Src  = (UINT8 CONST *)Source;

  if (
      (Size >= sizeof (long) * 2) &&
      (((UINTN)Src & (sizeof (long) - 1)) == ((UINTN)Dest & (sizeof (long) - 1)))
      )
  {
    while ((UINTN)Src & (sizeof (long) - 1) != 0) {
      *Dest++ = *Src++;

      Size--;
    }

    long        *AlignedDest = (long *)Dest;
    long const  *AlignedSrc  = (long const *)Src;

    while (Size >= sizeof (long) * 4) {
      AlignedDest[0] = AlignedSrc[0];
      AlignedDest[1] = AlignedSrc[1];
      AlignedDest[2] = AlignedSrc[2];
      AlignedDest[3] = AlignedSrc[3];

      AlignedSrc  += 4;
      AlignedDest += 4;

      Size -= sizeof (long) * 4;
    }

    while (Size >= sizeof (long)) {
      *AlignedDest++ = *AlignedSrc++;

      Size -= sizeof (long);
    }

    Dest = (UINT8 *)AlignedDest;
    Src  = (UINT8 CONST *)AlignedSrc;
  }

  while (Size--) {
    *Dest++ = *Src++;
  }

  return Dest;
}

VOID *
KernMemMove (
  IN VOID        *Destination,
  IN CONST VOID  *Source,
  IN UINTN       Count
  )
{
  if (Destination < Source) {
    return KernCopyMem (Destination, (VOID *)Source, Count);
  }

  CHAR16        *DestPtr = (CHAR16 *)Destination + Count;
  CONST CHAR16  *SrcPtr  = (CHAR16 *)Source + Count;

  while (--Count) {
    *--DestPtr = *--SrcPtr;
  }

  return Destination;
}

VOID *
kmalloc (
  IN UINTN  Size
  )
{
  VOID   *Start            = NULL;
  UINTN  NumberOfPages     = GET_NUM_OF_PAGES (Size);
  UINTN  CurrCntgFreePages = 0;

  for (UINTN Index = 0; Index < BitmapSize; Index++) {
    UINT8  *Frame = Bitmap + Index;

    if (CurrCntgFreePages == NumberOfPages) {
      break;
    }

    if ((*Frame) == 0xFF) {
      if (Start == NULL) {
        Start = Frame;
      }

      CurrCntgFreePages++;
    } else {
      Start             = NULL;
      CurrCntgFreePages = 0;
    }
  }

  return Start;
}
