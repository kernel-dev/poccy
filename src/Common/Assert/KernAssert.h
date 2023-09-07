#ifndef KERN_ASSERT_H
#define KERN_ASSERT_H

#include "Drivers/IO/serial.h"
#include "Util/KernRuntimeValues.h"
#include "Graphics/KernText.h"

#define STR_EXPR(expr)  #expr
#define ASSERT(expr) \
    if (!(expr)) \
    { \
        kprintf(     \
            "[%s]: ASSERT (%s) == %s\n", \
            __FILE__,\
            STR_EXPR(expr),              \
            expr ? "1" : "0"        \
            ); \
        WriteSerialStr ("["); \
        WriteSerialStr (__FILE__); \
        WriteSerialStr ("] ASSERT ( "); \
        WriteSerialStr (STR_EXPR(expr)); \
        WriteSerialStr (" )"); \
        WriteSerialStr (" == "); \
        WriteSerialStr (expr ? "1\n" : "0\n"); \
        for ( ; ;) { __asm__("hlt"); } \
    }

#endif /* KernAssert.h */
