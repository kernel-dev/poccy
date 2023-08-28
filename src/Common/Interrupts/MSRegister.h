#ifndef MSREGISTER_H
#define MSREGISTER_H

#include <Uefi.h>

#include <Library/UefiLib.h>

BOOLEAN
CpuHasMSR (
  VOID
  );

VOID
CpuGetMSR (
  UINTN  MSR,
  UINTN  *Low,
  UINTN  *High
  );

VOID
CpuSetMSR (
  UINTN  MSR,
  UINTN  Low,
  UINTN  High
  );

#endif /* MSRegister.h */
