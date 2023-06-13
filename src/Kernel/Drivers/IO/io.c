#include "../../../Common/Drivers/IO/io.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID
OutB8 (
  IN UINT16  Port,
  IN UINT8   Value
  )
{
  asm volatile (
      "outb %0, %1" : : "a"(Value), "Nd"(Port) : "memory"
  );
}

UINT8
InB8 (
  IN UINT16  Port
  )
{
  UINT8  Ret;

  asm volatile ( "inb %1, %0"
                 : "=a"(Ret)
                 : "Nd"(Port)
                 : "memory");

  return Ret;
}
