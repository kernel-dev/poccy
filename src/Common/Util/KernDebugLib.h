#ifndef KERN_DEBUG_LIB_H
#define KERN_DEBUG_LIB_H

//
//  The ENABLE_DEBUG_MODE macro is defined for
//  debug binaries of kernelOS.
//
#ifdef ENABLE_DEBUG_MODE

    #define DEBUG_MEMORY_ERR
    #define DEBUG_FRAMEBUFFER
    #define DEBUG_CTX_SWITCH

#endif /* ENABLE_DEBUG_MODE */

#endif /* KernDebugLib.h */
