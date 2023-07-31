#include "../../Common/Memory/KernMem.h"
#include "../../Common/Util/KernRuntimeValues.h"
#include "../../Common/Util/KernString.h"

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
    while (((UINTN)Src & (sizeof (long) - 1)) != 0) {
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
pages_search_success:
      break;
    }

    for (UINTN Bit = 0; Bit < 8; Bit++) {
      if (CurrCntgFreePages) {
        goto pages_search_success;
      }

      UINTN  Value = *Frame;

      if (((Value >> Bit) & 1) == 1) {
        if (Index < 0x10000) {
          continue;
        }

 #ifdef DEBUG_MEMORY
        kprint ("[DEBUG::MEMORY::kmalloc()]: PAGE AT ADDRESS ");
        kprint (__DecimalToHex ((UINTN)Frame * 4096, TRUE));
        kprint (" IS AVAILABLE FOR USAGE!\n");
 #endif

        if (Start == NULL) {
          Start = (VOID *)((UINTN)Frame * 0x1000);
        }

        CurrCntgFreePages++;
      } else {
 #ifdef DEBUG_MEMORY
        kprint ("[DEBUG::MEMORY::kmalloc()]: ");
        kprint (_KernItoa (CurrCntgFreePages));
        kprint ("-ITH PAGE IS TAKEN (AT ADDRESS ");
        kprint (__DecimalToHex ((UINTN)Frame * 0x1000, TRUE));
        kprint (") GOING NEXT BIT OVER...\n");
 #endif

        CurrCntgFreePages = 0;
        Start             = NULL;
      }
    }
  }

  //
  //  Zero the memory.
  //
  KernMemset (
    Start,
    0x00,
    NumberOfPages * KERN_SIZE_OF_PAGE
    );

  for (UINTN Bit = 0; Bit < NumberOfPages; Bit++) {
    UINTN  Index = (UINTN)Start / 4096;

    Bitmap[Index] &= ~(1 << (Bit % 8));
  }

  return Start;
}
