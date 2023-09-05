#ifndef IDTRTABLE_H
#define IDTRTABLE_H

#include <Uefi.h>
#include <Library/UefiLib.h>

typedef struct {
  UINT16    ISRLow;
  UINT16    KernelCS;
  UINT8     IST;            // Interrupts Stack Offset
  UINT8     AttributesType;
  UINT16    ISRMid;
  UINT32    ISRHigh;
  UINT32    Reserved;
} __attribute__ ((packed)) InterruptDescriptor;

typedef struct {
  UINT16    Limit;
  UINTN     Base;
} __attribute__ ((packed)) IDTRegister;

#endif /* IDTRTable.h */
