#include "../Common/Math/Logarithm.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

UINT64
Base10Log (
  IN UINT32  Value
  )
{
  if (Value == 0) {
    return __UINT64_MAX__ - 1;
  }
}

UINT64
LogarithmGetExponent (
  IN UINT32  Base,
  IN UINT32  Value
  )
{
}
