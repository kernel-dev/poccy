#include "Assert/KernAssert.h"
#include "Util/KernString.h"
#include "Drivers/IO/serial.h"
#include "Drivers/IO/io.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

BOOLEAN
InitSerial (
  VOID
  )
{
  OutB8 (COM1_PORT + 1, 0x00);
  OutB8 (COM1_PORT + 3, 0x80);
  OutB8 (COM1_PORT + 0, 0x03);
  OutB8 (COM1_PORT + 1, 0x00);
  OutB8 (COM1_PORT + 3, 0x03);
  OutB8 (COM1_PORT + 2, 0xC7);
  OutB8 (COM1_PORT + 4, 0x0B);
  OutB8 (COM1_PORT + 4, 0x1E);
  OutB8 (COM1_PORT + 0, 0xAE);

  if (InB8 (COM1_PORT + 0) != 0xAE) {
    return FALSE;
  }

  OutB8 (COM1_PORT + 4, 0x0F);

  return TRUE;
}

UINTN
IsSerialReceived (
  )
{
  return InB8 (COM1_PORT + 5) & 1;
}

UINTN
IsTransmitEmpty (
  )
{
  return InB8 (COM1_PORT + 5) & 0x20;
}

VOID
WriteSerial (
  IN CHAR8  Character
  )
{
  while (IsTransmitEmpty () == 0) {
  }

  OutB8 (COM1_PORT, Character);
}

CHAR8
ReadSerial (
  )
{
  while (IsSerialReceived () == 0) {
  }

  return InB8 (COM1_PORT);
}

VOID
WriteSerialStr (
  IN CHAR8  *String
  )
{
  ASSERT (_KernStrLen (String) != 0);

  CHAR8  *__LocalStrCpy;

  for (__LocalStrCpy = String; *__LocalStrCpy; ++__LocalStrCpy) {
    WriteSerial (*__LocalStrCpy);
  }
}
