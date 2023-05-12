#ifndef IO_H
#define IO_H

#include <Uefi.h>

#include <Library/UefiLib.h>

/**
    Sends the 1-byte value to
    the specified I/O port.

    @param[in]  Port    The port to send the data to.
    @param[in]  Value   The value to send.
 **/
VOID
OutB8 (
    IN UINT16  Port,
    IN UINT8   Value
);

/**
    Sends the 2-byte value to
    the specified I/O port.

    @param[in]  Port    The port to send the data to.
    @param[in]  Value   The value to send.
 **/
VOID
OutB16 (
    IN UINT16  Port,
    IN UINT16  Value
);

/**
    Sends the 4-byte value to
    the specified I/O port.

    @param[in]  Port    The port to send the data to.
    @param[in]  Value   The value to send.
 **/
VOID
OutB32 (
    IN UINT16  Port,
    IN UINT32  Value
);

/**
    Receives a 1-byte value from
    the specified I/O port.

    @param[in]  Port    The port to receive the data from.

    @retval     UINT8   The read 1-byte value.
 **/
UINT8
InB8 ( IN UINT16 Port );


/**
    Receives a 2-byte value from
    the specified I/O port.

    @param[in]  Port    The port to receive the data from.

    @retval     UINT16  The read 2-byte value.
 **/
UINT16
InB16 ( IN UINT16 Port );

/**
    Receives a 4-byte value from
    the specified I/O port.

    @param[in]  Port    The port to receive the data from.

    @retval     UINT32  The read 4-byte value.
 **/
UINT32
InB32 ( IN UINT16 Port );

/**
    Waits for a very, very small
    amount of time. (1-4µs)
 **/
VOID
IoWait (VOID);

/**
    Returns a boolean indicating
    whether or not interrupts have been enabled.

    @retval     BOOLEAN     Whether or not interrupts are enabled.
 **/
BOOLEAN
IRQsEnabled (VOID);



/**
    Initializes the keyboard handler.
 **/
VOID
HandlerInitKeyboard (VOID);

#endif /* io.h */
