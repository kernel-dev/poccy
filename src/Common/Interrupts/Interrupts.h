#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <Uefi.h>

typedef struct {
  UINT32 Reserved1;
  UINT32 Low_RSP0;
  UINT32 High_RSP0;
  UINT32 Low_RSP1;
  UINT32 High_RSP1;
  UINT32 Low_RSP2;
  UINT32 High_RSP2;
  UINT32 Reserved2;
  UINT32 Reserved3;
  UINT32 Low_IST1;
  UINT32 High_IST1;
  UINT32 Low_IST2;
  UINT32 High_IST2;
  UINT32 Low_IST3;
  UINT32 High_IST3;
  UINT32 Low_IST4;
  UINT32 High_IST4;
  UINT32 Low_IST5;
  UINT32 High_IST5;
  UINT32 Low_IST6;
  UINT32 High_IST6;
  UINT32 Low_IST7;
  UINT32 High_IST7;
  UINT32 Reserved4;
  UINT32 Reserved5;
  UINT16 Reserved6;
  UINT16 IOPB;
} TaskSegmentDescriptor;

__attribute__((noreturn)) VOID ExceptionHandler(VOID);

extern VOID *isr_stub_table[];

VOID IDTSetDescriptor(IN UINT8 Vector, IN VOID *InterruptService,
                      IN UINT8 Flags);

VOID InitIDT(VOID);

#endif /* Interrupts.h */
