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
  IN UINTN  MSR,
  IN UINTN  *Low,
  IN UINTN  *High
  );

VOID
CpuSetMSR (
  IN UINTN  MSR,
  IN UINTN  Low,
  IN UINTN  High
  );

#endif /* MSRegister.h */
