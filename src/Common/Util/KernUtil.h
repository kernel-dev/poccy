#ifndef KERN_UTIL_H
#define KERN_UTIL_H

#include <Uefi.h>

#include <Library/UefiLib.h>

UINT64
__get_tickrate (
  VOID
  );

/**
    "Sleep" for the specified amount of time in milliseconds.

    @param[in] Milliseconds  The number of milliseconds to sleep.
 **/
VOID
KernSleep (
  UINTN  Milliseconds
  );

#endif /* KernUtil.h */
