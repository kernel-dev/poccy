#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernFontParser.h"
#include "../../Common/Util/KernRuntimeValues.h"
#include "../../Common/Memory/KernMemoryManager.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

//
//  Framebuffer related values
//
UINT32                   ScreenRow          = 1;
UINT32                   ScreenCol          = 1;
KERN_FRAMEBUFFER         *FB                = NULL;

//
//  Font related values
//
PSF_FONT_HDR             FontHdr;
PSF_FONT_HDR_EXTENDED    ExtFontHdr;
VOID                     *FontFile          = NULL;

//
//  Bitmap related values
//
UINTN                    BitmapSize         = 0;
MEMORY_BITMAP            *Bitmap            = NULL;
