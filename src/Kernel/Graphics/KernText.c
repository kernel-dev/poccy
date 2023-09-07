#include "../../Common/Assert/KernAssert.h"
#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernGraphics.h"
#include "../../Common/Graphics/KernText.h"
#include "../../Common/Graphics/KernFontParser.h"
#include "../../Common/Memory/KernMem.h"
#include "../../Common/Util/KernString.h"
#include "../../Common/Util/KernRuntimeValues.h"

#include <stdarg.h>

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID
kprint (
  IN CHAR8  *Str
  )
{
  ASSERT (Str != NULL);

  UINTN  Len = _KernStrLen (Str);

  ASSERT (Len > 0);

  for (UINTN Index = 0; Index < Len; Index++) {
    PutChar (Str[Index]);
  }
}

//
//  TODO:   Pain.
//
VOID
kprintf (
  IN CONST CHAR8  *Fmt,
  ...
  )
{
  va_list  args;

  va_start (args, format);

  while (*Fmt) {
    if (*Fmt == '%') {
      Fmt++;

      //
      //    Pointer.
      //
      if (*Fmt == 'p') {
        UINTN  *Value = (UINTN *)va_arg (args, VOID *);
        CHAR8  *Str   = __DecimalToHex ((UINTN)Value, TRUE);

        kprint (Str);
      }
      //
      //    Hexadecimal.
      //
      else if ((*Fmt == 'x') || (*Fmt == 'X')) {
        BOOLEAN  Capitals = *Fmt == 'X';

        UINTN  Value = va_arg (args, UINTN);
        CHAR8  *Str  = __DecimalToHex (Value, Capitals);

        kprint (Str);
      }

      //
      //  Character.
      //
      else if (*Fmt == 'c') {
        CHAR8  Character = va_arg (args, CHAR8);

        PutChar (Character);
      }

      //
      //    String.
      //
      else if (*Fmt == 's') {
        CHAR8  *Str = va_arg (args, CHAR8 *);

        if ((Str != NULL) && (*Str != '\0') && (_KernStrLen (Str) > 0)) {
          kprint (Str);
        }
      }
      //
      //    Integer/long.
      //
      else if ((*Fmt == 'd') || (*Fmt == 'l')) {
        //
        //    Regular integer.
        //
        if (*(Fmt + 1) == 'd') {
          CHAR8  *Str = _KernItoa (va_arg (args, INT32));

          kprint (Str);
        }
        //
        //  Long.
        //
        else if (*(Fmt + 1) == 'l') {
          //
          //  Long in an integer representation.
          //
          if (*(Fmt + 2) == 'd') {
            CHAR8  *Str = _KernItoa (va_arg (args, long));

            kprint (Str);
          }
          //
          //    Long-long in an integer representation.
          //
          else if ((*(Fmt + 2) == 'l') && (*(Fmt + 3) == 'd')) {
            CHAR8  *Str = _KernItoa (va_arg (args, long long));

            kprint (Str);
          }
          //
          //    Long represented in hexadecimal.
          //
          else if ((*(Fmt + 2) == 'x') || (*(Fmt + 2) == 'X')) {
            BOOLEAN  Capitals = *(Fmt + 2) == 'X';
            CHAR8    *Str     = __DecimalToHex (va_arg (args, long), Capitals);

            kprint (Str);
          }
          //
          //    Long-long represented in hexadecimal.
          //
          else if ((*(Fmt + 2) == 'l') && ((*(Fmt + 3) == 'x') || (*(Fmt + 3) == 'X'))) {
            BOOLEAN  Capitals = *(Fmt + 3) == 'X';
            CHAR8    *Str     = __DecimalToHex (va_arg (args, long long), Capitals);

            kprint (Str);
          }
        }

        // Skip additional characters (d, ld, lld, llx) in the format specifier
        while (*Fmt && *Fmt != ' ') {
          Fmt++;
        }
      }
    }
    //
    //  Not recognized/supported format.
    //
    else {
      PutChar (*Fmt);
    }

    Fmt++;
  }

  va_end (args);
}

VOID
PutChar (
  IN CHAR8  Char
  )
{
  //
  //  Who knew that the condition for scrolling
  //  would be `VertRes / BitsPerPixel`?
  //
  if (ScreenRow >= (FB->VerticalRes / (FB->BPP * 4))) {
    ScreenScrollTerminal ();
  }

  if (Char == '\n') {
    ScreenCol = 1;
    ScreenRow++;

    return;
  }

  if (Char == '\t') {
 #ifdef PRINT_TABS
    kprint ("    ");

    return;
 #endif
  }

  UINT8  *GlyphStart = ((UINT8 *)FontFile) + sizeof (PSF_FONT_HDR) + (Char * 16);
  UINT8  Glyph[16];

  for (UINTN N = 0; N < 16; N++) {
    Glyph[N] = GlyphStart[N];
  }

  for (UINTN DY = 0; DY < 16; DY++) {
    for (UINTN DX = 0; DX < 8; DX++) {
      UINT32  X = ScreenCol * ExtFontHdr.Width + DX;
      UINT32  Y = ScreenRow * ExtFontHdr.Height + DY;

      UINT32  BitIdx = 7 - DX;
      UINT32  Bit    = (Glyph[DY] >> BitIdx) & 1;

      if (Bit == 1) {
        ScreenPutPixel (X, Y, 0xFFFFFFFF);
      }
    }
  }

  ScreenCol++;

  if (ScreenCol >= FBWidth) {
    ScreenCol = 1;
    ScreenRow++;
  }
}
