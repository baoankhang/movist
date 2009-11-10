/*
 * ColorConversions.h
 * Created by Alexander Strange on 1/10/07.
 *
 * This file is part of Perian.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */


#include <Carbon/Carbon.h>
#ifdef __BIG_ENDIAN__
    #include <ffmpeg/avcodec.h>
#else
    #include <libavcodec/avcodec.h>
#endif

#if defined(__i386__) && !defined(__llvm__)
#define FASTCALL __attribute__((fastcall))
#else
#define FASTCALL
#endif

typedef void ColorConversionFunc(AVFrame *inPicture, UInt8 *outBaseAddr, int outRowBytes, unsigned outWidth, unsigned outHeight) FASTCALL;
typedef ColorConversionFunc *ColorConversionFuncPtr;
typedef void ColorClearFunc(UInt8 *outBaseAddr, int outRowBytes, unsigned outWidth, unsigned outHeight) FASTCALL;
typedef ColorClearFunc *ColorClearFuncPtr;

typedef struct ColorConversionFuncs {
	ColorConversionFuncPtr convert;
	ColorClearFuncPtr      clear;
} ColorConversionFuncs;

extern OSType ColorConversionDstForPixFmt(enum PixelFormat ffPixFmt);
extern int ColorConversionFindFor(ColorConversionFuncs *funcs, enum PixelFormat ffPixFmt, AVFrame *ffPicture, OSType qtPixFmt);