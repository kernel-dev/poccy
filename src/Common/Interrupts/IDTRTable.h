#ifndef IDTRTABLE_H
#define IDTRTABLE_H

#include <Uefi.h>
#include <Library/UefiLib.h>

struct InterruptDescriptor {
  UINT16    Offset1;
  UINT16    Selector;
  UINT8     IST;            // Interrupts Stack Offset
  UINT8     AttributesType;
  UINT16    Offset2;
  UINT32    Offset3;
  UINT32    Reserved;
};

#endif /* IDTRTable.h */
