#include "../../Common/Assert/KernAssert.h"
#include "../../Common/Util/KernString.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

//
//  The following function has been taken from
//  Apple's open source repository.
//
//  https://opensource.apple.com/source/groff/groff-40/groff/src/libs/libgroff/itoa.c.auto.html
//

#define MAX_DIGITS  20  /* Enough for UINT64 and INT64 */
#define MAX_BUF     sizeof(unsigned long long)

UINTN
_KernStrLen (
  IN CHAR8  *String
  )
{
  ASSERT (String != NULL);

  if (String[0] == '\0') {
    return 0;
  }

  CONST CHAR8  *S;

  for (S = String; *S; ++S) {
  }

  return (S - String);
}

VOID
_KernReverseStr (
  IN OUT CHAR8  *Buffer
  )
{
  UINTN  Length = _KernStrLen (Buffer);

  ASSERT (Length > 1);

  UINTN  Beg = 0;
  UINTN  End = Length - 1;

  for (UINTN Index = 0; Index < (Length / 2); Index++, Beg++, End--) {
    CHAR8  First = Buffer[Beg];
    CHAR8  Last  = Buffer[End];

    Buffer[Beg] = Last;
    Buffer[End] = First;
  }
}

CHAR8 *
_KernItoa (
  IN  INT64  Num
  )
{
  STATIC CHAR8  Buffer[MAX_DIGITS + 2];

  CHAR8  *Ptr = Buffer + MAX_DIGITS + 1;

  do {
    *--Ptr = '0' + (Num % 10);

    Num /= 10;
  } while (Num != 0);

  return Ptr;
}

CHAR8 *
__DecimalToHex (
  IN  UINTN    Num,
  IN  BOOLEAN  Capitals
  )
{
  ASSERT (Num >= 0);

  if (Num == 0) {
    return "0";
  }

  STATIC CHAR8  Buffer[MAX_BUF];

  register CHAR8  *Ptr = (Buffer + MAX_BUF - 1);

  *--Ptr = '\0';

  do {
    *--Ptr = "0123456789abcdef0123456789ABCDEF"[(Num % 16) + (Capitals ? 16 : 0)];

    Num /= 16;
  } while (Num != 0);

  *--Ptr = 'x';
  *--Ptr = '0';

  return Ptr;
}

UINTN
_KernStrCmp (
  IN CONST CHAR8  *First,
  IN CONST CHAR8  *Second,
  IN UINTN        Chars
  )
{
  while (Chars--) {
    if (*First != *Second) {
      return (UINTN)((*First) - (*Second));
    }

    if (*First == '\0') {
      break;
    }

    First++;
    Second++;
  }

  return 0;
}
