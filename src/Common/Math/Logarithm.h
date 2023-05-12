#ifndef LOGARITHM_H
#define LOGARITHM_H

#include <Uefi.h>

#include <Library/UefiLib.h>

/**
    Finds the base-10 logarithm of some value.

    @param[in]  Value       The result of the exponentiation.

    @retval     UINT64      The exponent.
 **/
UINT64
Base10Log (
    IN  UINT32  Value
);

/**
    Implementation of a typical logarithm
    function.

    @param[in]  Base        The base.
    @param[in]  Value       The result of the exponentiation.

    @retval     UINT64      The exponent.
 **/
UINT64
LogarithmFindExponent (
    IN UINT32   Base,
    IN UINT32   Value
);

/**
    Finds the base of a logarithm
    expression. logn(16) = 2

    `n' here would be 4.

    @param[in]  Value       The result of the exponentiation.
    @param[in]  Exponent    The exponent.

    @retval     UINT64      The base.
 **/
UINT64
LogarithmFindBase (
    IN UINT32   Value,
    IN UINT32   Exponent
);

/**
    Finds the result of a logarithm
    expression.

    @param[in]  Base        The base of this logarithm expression.
    @param[in]  Exponent    The exponent.

    @retval     UINT64      The result.
 **/
UINT64
LogarithmFindResult (
    IN UINT32   Base,
    IN UINT32   Exponent
);



#endif /* Logarithm.h */
