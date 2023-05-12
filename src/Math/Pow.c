#include "../Common/Math/Pow.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

#define INT64_MAX   0x7FFFFFFFFFFFFFFF

UINT64
PowInt64 (
    IN INT32   Value,
    IN INT32   Exponent)
{
    //
    //  If the value is 1,
    //  if the value is 0 and exp is 0,
    //  or if the value is 0 and the exp is -1,
    //  then the result is 1.
    //
    if (
        Value == 1 ||
        Exponent == 0
    )
        return 1;

    //
    //  At this point, we've already
    //  made sure that the Exponent != 0
    //
    //  But... if it's lesser than 0,
    //  and the Value is equal to 0,
    //  then the result is undefined.
    //
    //  Because (1 / 0^n) = undefined, n > 0
    //
    if (Value == 0 && Exponent < 0)
        return INT64_MAX - 1;

    //
    //  If the Exponent is positive (but not equal to 0),
    //  and the value is 0, then the result is 0.
    //
    if (Value == 0)
        return 0;

    //
    //  N^1 = N
    //
    if (Exponent == 1)
        return Value;
    
    //
    //  N^(-Y) = 1 / N^Y
    //
    if (Exponent < 0)
        return 1 / (Value * PowInt64 (Value, (Exponent * -1) - 1));

    return Value * PowInt64 (Value, Exponent - 1);
}
