#ifndef GDT_H
#define GDT_H

#include <Uefi.h>

/**
 * The GDT entry.
 */
typedef struct {
  UINT16    LimitLow;
  UINT16    BaseLow;
  UINT8     BaseMiddle;
  UINT8     Access;
  UINT8     Granularity;
  UINT8     BaseHigh;
} __attribute__ ((packed)) GDTEntry;

/**
 * The GDT descriptor.
 */

typedef struct {
  UINT16    Limit;
  UINT32    BaseAddress;
} __attribute__ ((packed)) GDTDescriptor;

typedef struct {
  GDTEntry    Null;
  GDTEntry    KernelCode;
  GDTEntry    KernelData;
  GDTEntry    UserCode;
  GDTEntry    UserData;
} __attribute__ ((packed)) GDT;

extern VOID
FlushGDT (
  IN GDTDescriptor  *Entry
  );

extern VOID
DisableInterrupts (
  VOID
  );

extern VOID
EnableInterrupts (
  VOID
  );

VOID
InitializeDescriptorTables (
  VOID
  );

STATIC VOID
InitializeGDT (
  VOID
  );

#endif /* GDT.h */
