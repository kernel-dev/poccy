#ifndef KERN_ASSERT_H
#define KERN_ASSERT_H

#include "../Drivers/IO/serial.h"
#include "../Util/KernRuntimeValues.h"
#include "../Graphics/KernText.h"

#define STR_EXPR(expr)  #expr
#define ASSERT(expr) \
    if (!(expr)) \
    { \
        kprint ("["); \
        kprint (__FILE__); \
        kprint ("] ASSERT ( "); \
        kprint (STR_EXPR(expr)); \
        kprint (" )"); \
        kprint (" == "); \
        kprint (expr ? "1\n" : "0\n"); \
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
