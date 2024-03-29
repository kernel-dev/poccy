#include "Util/KernRuntimeValues.h"
#include "Graphics/KernGop.h"
#include "Graphics/KernGraphics.h"
#include "Memory/KernMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <stdatomic.h>

VOID
GraphicsSpinlockInit (
  IN GraphicsSpinlock  *Spinlock
  )
{
  atomic_flag_clear (&Spinlock->lock);
}

VOID
GraphicsSpinlockLock (
  IN GraphicsSpinlock  *Spinlock
  )
{
  while (atomic_flag_test_and_set (&Spinlock->lock)) {
    __asm__ volatile ("pause");
  }
}

VOID
GraphicsSpinlockUnlock (
  IN GraphicsSpinlock  *Spinlock
  )
{
  atomic_flag_clear (&Spinlock->lock);
}

VOID
ScreenClearTerminal (
  VOID
  )
{
  //
  //  Fill the entirety of the framebuffer
  //  memory space with black pixels (0x0).
  //
  VolatileKernMemset (
    (UINT32 *)FB->FramebufferBase,
    0x0,
    FB->FramebufferSize
    );
}

VOID
ScreenFillRectangle (
  IN UINT32  X,
  IN UINT32  Y,
  IN UINT32  Width,
  IN UINT32  Height,
  IN UINT32  Color
  )
{
  //
  //  Iterate over every coordinate (X, Y),
  //  in accordance to the specified height-weight,
  //  and fill each corresponding memory space
  //  with the provided BGRA (32-bit) color.
  //
  for (UINT32 Vertical = Y; Vertical < (Y + Height); Vertical++) {
    for (UINT32 Horizontal = X; Horizontal < (X + Width); Horizontal++) {
      ScreenPutPixel (
        Horizontal,
        Vertical,
        Color
        );
    }
  }
}

VOID
ScreenPutPixel (
  IN UINT32  X,
  IN UINT32  Y,
  IN UINT32  Color
  )
{
  GraphicsSpinlockLock (&graphicsSpinlock);

  //
  //  Locate the corresponding memory space
  //  based on the (X, Y) coordinates.
  //
  UINTN  Address = (UINTN)(
    (UINT32)FB->FramebufferBase + (Y * (FB->HorizontalRes * FB->BPP)) + (FB->BPP * X)
    );

  //
  //  Cannot write pixel values to memory that
  //  is not a part of the framebuffer memory space.
  //
  if (Address > (FB->FramebufferBase + FB->FramebufferSize)) {
    return;
  }

  //
  //  Replace contents of the memory block
  //  with the provided BGRA (32-bit) color.
  //
  *((volatile UINTN *)(Address)) = Color;

  GraphicsSpinlockUnlock (&graphicsSpinlock);
}

VOID
ScreenScrollTerminal (
  VOID
  )
{
  UINTN  BytesToMove = FBWidth * (FBHeight - ExtFontHdr.Height);

  VOID  *Source      = (VOID *)(FB->FramebufferBase + FBWidth * ExtFontHdr.Height);
  VOID  *Destination = (VOID *)(FB->FramebufferBase);

  KernMemMove (Destination, Source, BytesToMove);

  Destination = (VOID *)(FB->FramebufferBase + BytesToMove);
  KernMemset (Destination, 0, FBWidth);

  ScreenRow--;
}
