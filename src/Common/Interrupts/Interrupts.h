#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <Uefi.h>

__attribute__ ((noreturn)) VOID
ExceptionHandler (
  VOID
  );

extern VOID  *isr_stub_table[];

VOID
IDTSetDescriptor (
  IN UINT8  Vector,
  IN VOID   *InterruptService,
  IN UINT8  Flags
  );

VOID
InitIDT (
  VOID
  );

#endif /* Interrupts.h */
