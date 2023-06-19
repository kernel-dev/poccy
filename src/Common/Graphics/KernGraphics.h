#ifndef KERN_GRAPHICS_H
#define KERN_GRAPHICS_H

#include "KernGop.h"

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <stdatomic.h>

/**
    Locks the framebuffer memory space
    spinlock.
 **/
VOID
VideoMemoryLockAcquire (
  atomic_flag  *Lock
  );

/**
    Unlocks the framebuffer memory space
    spinlock.
 **/
VOID
VideoMemoryLockRelease (
  atomic_flag  *Lock
  );

/**
    Overwrites the entire framebuffer memory
    space with black pixels — [clears the screen].
 **/
VOID
ScreenClearTerminal (
  VOID
  );

/**
    Fills a rectangle (on the screen)
    beginning at the (X, Y) coordinates,
    and expanding according to the
    Height-Width values.

    @param[in]  X       The starting X coordinate.
    @param[in]  Y       The starting Y coordinate.
    @param[in]  Width   The length to expand across the X axis
    @param[in]  Height  The length to expand across the Y axis
    @param[in]  Color   The BGRA value of the wanted pixel.
 **/
VOID
ScreenFillRectangle (
  IN UINT32  X,
  IN UINT32  Y,
  IN UINT32  Width,
  IN UINT32  Height,
  IN UINT32  Color
  );

/**
    Places a pixel at the specified
    FB memory space corresponding to the
    specified (X, Y) coordinates.

    @param[in]  X       The X coordinate.
    @param[in]  Y       The Y coordinate.
    @param[in]  Color   The BGRA value of the wanted pixel.
 **/
VOID
ScreenPutPixel (
  IN UINT32  X,
  IN UINT32  Y,
  IN UINT32  Color
  );

/**
    Scrolls the terminal by one row.
 **/
VOID
ScreenScrollTerminal (
  VOID
  );

#endif /* KernGraphics.h */
