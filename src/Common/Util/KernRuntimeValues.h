#ifndef KERN_RUNTIME_VALUES_H
#define KERN_RUNTIME_VALUES_H

#include "../../Common/Graphics/KernFontParser.h"
#include "../../Common/Graphics/KernText.h"
#include "../../Common/Graphics/KernGop.h"
#include "../../Common/Graphics/KernGraphics.h"
#include "../../Common/Memory/KernMemoryManager.h"

#include <Uefi.h>

#include <Library/UefiLib.h>
#include <stdatomic.h>

//
//  Screen row.
//
extern UINT32  ScreenRow;

//
//  Screen column.
//
extern UINT32  ScreenCol;

//
//  Framebuffer line width.
//
extern UINT32  FBWidth;

//
//  Framebuffer line height.
//
extern UINT32  FBHeight;

//
//  Whether or not a process
//  is writing to the framebuffer memory space.
//
extern atomic_flag  VideoMemoryLocked;

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
//  Total amount of entries (bytes)
//  in the bitmap.
//
extern UINTN  BitmapSize;

//
//  A bitmap representation of
//  the system memory.
//
extern UINT8  *Bitmap;

#endif /* KernRuntimeValues.h */
