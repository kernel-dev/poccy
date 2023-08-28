#ifndef POW_H
#define POW_H

#include <Uefi.h>

#include <Library/UefiLib.h>

UINT64
PowInt64 (
  IN INT32  Value,
  IN INT32  Exponent
  );

#endif /* Pow.h */
