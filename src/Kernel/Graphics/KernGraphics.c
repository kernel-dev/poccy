#include "../../Common/Util/KernRuntimeValues.h"
#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernGraphics.h"
#include "../../Common/Memory/KernMem.h"

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <stdatomic.h>

VOID
VideoMemoryLockAcquire (
  atomic_flag  *Lock
  )
{
  while (atomic_flag_test_and_set_explicit (Lock, memory_order_acquire)) {
    __asm__ __volatile__ ("pause");
  }
}

VOID
VideoMemoryLockRelease (
  atomic_flag  *Lock
  )
{
  atomic_flag_clear_explicit (Lock, memory_order_release);
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
  VideoMemoryLockAcquire (&VideoMemoryLocked);

  //
  //  Locate the corresponding memory space
  //  based on the (X, Y) coordinates.
  //
  UINT64  Address = (UINT64)(
                             (UINT32)FB->FramebufferBase + (Y * (FB->HorizontalRes* FB->BPP)) + (FB->BPP * X)
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
  *((volatile UINT64 *)(Address)) = Color;

  VideoMemoryLockRelease (&VideoMemoryLocked);
}

VOID
ScreenScrollTerminal (
  VOID
  )
{
  UINTN  LineWidth  = FB->HorizontalRes * FB->BPP;
  UINTN  LineHeight = FB->VerticalRes * FB->BPP;

  for (UINTN Y = 0; Y < FBHeight; Y++) {
    KernMemMove (
      (VOID *)(FB->FramebufferBase + (Y * FBWidth)),
      (VOID *)(FB->FramebufferBase + ((Y + ExtFontHdr.Height) * FBWidth)),
      FBWidth
      );
  }
}
