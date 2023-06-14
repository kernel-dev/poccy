#ifndef KERN_STRING_H
#define KERN_STRING_H

#include <Uefi.h>

#include <Library/UefiLib.h>

/**
    Gets the length of a string.

    @param[in]  String       The string to get the length of.

    @retval     UINTN        The length of the string.
 **/
UINTN
_KernStrLen (
  IN CHAR8  *String
  );

/**
    Internal method for reversing a string.

    @param[in,out]  Buffer  The string to reverse.

    @retval         CHAR8*  The reversed string.
 **/
VOID
_KernReverseStr (
  IN OUT CHAR8  *Buffer
  );

/**
    Stringifies an integer value.

    @param[in]   Num         The integer to stringify.
    
    @retval      CHAR8*     The stringified integer.
 **/
CHAR8 *
_KernItoa (
  IN  INT64  Num
  );

/**
    Converts a decimal number to a hexadecimal number.

    @param[in]  Num       The decimal number to convert.
    @param[in]  Capitals  Whether or not to use capital letters.

    @retval     CHAR8*   The decimal number in a hexadecimal representation
 **/
CHAR8 *
__DecimalToHex (
  IN  UINTN     Num,
  IN  BOOLEAN   Capitals
  );

#endif /* KernString.h */
