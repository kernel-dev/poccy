#include "../../Common/Drivers/IO/serial.h"
#include "../../Common/Assert/KernAssert.h"
#include "../../Common/Memory/KernMem.h"
#include "../../Common/Graphics/KernFontParser.h"
#include "../../Common/Graphics/KernGraphics.h"
#include "../../Common/Util/KernString.h"
#include "../../Common/Util/KernRuntimeValues.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

VOID
PSFInit (
  IN  VOID                   *FontFile,
  OUT PSF_FONT_HDR           *Hdr,
  OUT PSF_FONT_HDR_EXTENDED  *ExtHdr     OPTIONAL,
  IN  BOOLEAN                GetExtHdr
  )
{
  ASSERT (FontFile != NULL);
  ASSERT (Hdr != NULL);
  ASSERT (ExtHdr != NULL);

  Hdr = (PSF_FONT_HDR *)FontFile;

  //
  //  Ensure it's a supported version.
  //
  ASSERT (Hdr->Magic == PSF_FONT1_MAGIC);

  if (GetExtHdr == TRUE) {
    ExtHdr->NumOfGlyphs  = (Hdr->Flags & (1 << 0)) == 0 ? 256 : 512;
    ExtHdr->UnicodeTable = (BOOLEAN)(Hdr->Flags & (1 << 1)) != 0;
    ExtHdr->GlyphSeqs    = (BOOLEAN)(Hdr->Flags & (1 << 2)) != 0;
    ExtHdr->Height       = Hdr->Height;
    ExtHdr->Width        = 8;

    FBHeight = FB->VerticalRes * FB->BPP;
    FBWidth  = FB->HorizontalRes * FB->BPP;
  }
}
