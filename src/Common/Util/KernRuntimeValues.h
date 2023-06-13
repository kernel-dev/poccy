#ifndef KERN_RUNTIME_VALUES_H
#define KERN_RUNTIME_VALUES_H

#include "../../Common/Graphics/KernFontParser.h"
#include "../../Common/Graphics/KernText.h"
#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernGraphics.h"
#include "../../Common/Memory/KernMemoryManager.h"

#include <Uefi.h>

#include <Library/UefiLib.h>

//
//  Screen row.
//
extern UINT32  ScreenRow;

//
//  Screen column.
//
extern UINT32  ScreenCol;

//
//  KERN_FRAMEBUFFER pointer.
//
extern KERN_FRAMEBUFFER  *FB;

//
//  PSF font header.
//
extern PSF_FONT_HDR  FontHdr;

//
//  Extended PSF font header.
//
extern PSF_FONT_HDR_EXTENDED  ExtFontHdr;

//
//  Contents of the current PSF file.
//
extern VOID  *FontFile;

//
//  Size of the 4-KiB page bitmap.
//
extern UINTN  BitmapSize;

//
//  A bitmap of 4-KiB aligned usable memory.
//
//  Includes memory that is already in-use
//  by a process in the kernel, as well.
//
extern UINT8  Bitmap[2048];

#endif /* KernRuntimeValues.h */
