#include "../../Common/Util/KernUtil.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

//
//  TODO: Implement IRQ handling so
//        we can use the PIC for timers.
//

// UINT64
// __get_tickrate (
//   VOID
//   )
// {
//   UINT32  High, Low;

//   __asm__ __volatile__ (
//     "rdtsc"
//     : "=a"(Low),
//       "=d"(High)
//   );

//   return ((UINT64)High << 32) | Low;
// }

// VOID
// KernSleep (
//   UINTN  Milliseconds
//   )
// {
//   UINTN  ETicks = 0;

//   ETicks = __get_tickrate () + Milliseconds;

//   while (ETicks > __get_tickrate ()) {
//     __asm__ __volatile__ ("hlt");
//   }
// }
