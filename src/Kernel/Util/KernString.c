#include "../../Common/Assert/KernAssert.h"
#include "../../Common/Util/KernString.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

UINTN
_KernStrLen ( IN CHAR8 *String )
{
    ASSERT  (String[0] != '\0');

    const CHAR8 *S;

    for (S = String; *S; ++S);

    return (S - String);
}

// VOID
// _KernReverseStr ( IN OUT CHAR8 **Buffer )
// {
//     UINTN Length = _KernStrLen (*Buffer);

//     ASSERT (Length > 1);

//     UINTN Beg = 0;
//     UINTN End = Length - 1;

//     for (UINTN Index = 0; Index < (Length / 2); Beg++, End--)
//     {
//         CHAR8 First = (*Buffer)[Beg];
//         CHAR8 Last  = (*Buffer)[End];

//         (*Buffer)[Beg] = Last;
//         (*Buffer)[End] = First;
//     }
// }


// UINTN
// _KernItoa ( 
//     IN  INT64    Num,
//     IN  UINT64   Base,
//     OUT CHAR8    *Buffer)
// {
//     if (Base < 2 || Base > 32)
//         return _KernStrLen (Buffer);

//     UINT64 Absolute = Num * (Num < 0 ? -1 : 1);

//     UINTN Index = 0;

//     while (Absolute)
//     {
//         UINTN Remainder = Absolute % Base;

//         if (Remainder >= 10)
//             Buffer[Index++] = 65 + (Remainder - 10);
        
//         else
//             Buffer[Index++] = 48 + Remainder;

//         Absolute /= Base;
//     }

//     if (Index == 0)
//         Buffer[Index++] = '0';

//     if (Num < 0 && Base == 10)
//         Buffer[Index++] = '-';

//     Buffer[Index] = '\0';

//     // reverse string here

//     return _KernStrLen (Buffer);
// }
