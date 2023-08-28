#ifndef KERN_SERIAL_H
#define KERN_SERIAL_H

#include "io.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

#define COM1_PORT  0x3F8

/**
 * Initializes the COM1 serial port.
 *
 * @return BOOLEAN  Whether or not Serial I/O has been initialized.
 */
BOOLEAN
InitSerial (
  VOID
  );

/**
 * Checks if the COM1 port data has been received.
 *
 * @return  UINTN   An integer value determining whether
 *                  or not the port's already received.
 */
UINTN
IsSerialReceived (
  VOID
  );

/**
 * Checks if the transmit is empty.
 *
 * @return UINTN Whether or not the transmit is empty.
 */
UINTN
IsTransmitEmpty (
  VOID
  );

/**
 * Reads data sent through the COM1 port.
 *
 * @return  CHAR8   The data read from COM1 port.
 */
CHAR8
ReadSerial (
  VOID
  );

/**
 * Writes a character to COM1.
 *
 * @param Character The character to write to COM1.
 * @return VOID
 */
VOID
WriteSerial (
  IN CHAR8  Character
  );

/**
 * Writes a string to COM1.
 *
 * @param String The string to write to COM1.
 * @return VOID
 */
VOID
WriteSerialStr (
  IN CHAR8  *String
  );

#endif /* serial.h */
