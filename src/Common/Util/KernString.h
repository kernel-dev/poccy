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
_KernStrLen ( IN CHAR8 *String );

/**
    Internal method for reversing a string.

    @param[in,out]  Buffer  The string to reverse.

    @retval         CHAR8*  The reversed string.
 **/
VOID
_KernReverseStr ( IN OUT CHAR8 **Buffer );

/**
    Stringifies an integer value.

    @param[in]   Num         The integer to stringify.
    @param[in]   Base        The base of the integer.
    @param[out]  Buffer      The buffer to allocate into.

    @retval      UINTN       The length of the string.
 **/
UINTN
_KernItoa (
    IN  INT64    Num,
    IN  UINT64   Base,
    OUT CHAR8    **Buffer
);

#endif /* KernString.h */
