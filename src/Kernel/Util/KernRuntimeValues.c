#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernFontParser.h"
#include "../../Common/Util/KernRuntimeValues.h"
#include "../../Common/Memory/KernMemoryManager.h"

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <stdatomic.h>

//
//  Framebuffer related values
//
UINT32            ScreenRow         = 1;
UINT32            ScreenCol         = 1;
UINT32            FBWidth           = 0;
UINT32            FBHeight          = 0;
KERN_FRAMEBUFFER  *FB               = NULL;
atomic_flag       VideoMemoryLocked = ATOMIC_FLAG_INIT;

//
//  Font related values
//
PSF_FONT_HDR           FontHdr;
PSF_FONT_HDR_EXTENDED  ExtFontHdr;
VOID                   *FontFile = NULL;

//
//  Bitmap related values
//
UINTN  BitmapSize = 0;
UINT8  *Bitmap    = NULL;
