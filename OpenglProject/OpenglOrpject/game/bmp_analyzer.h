#pragma once
#ifndef __BMP_ANALYZER_H__
#define __BMP_ANALYZER_H__
#include "debug_print.h"
#include "bitmap_format.h"



class CBmpAnalyzer {
public:
	static bool AnalyzeBitMap(const void* _buffer, const u32 _length, BITMAP_FORMAT& _bitmapFormat);
	static void ShowBitMapInfo(const BITMAP_FORMAT& _bitmap);
	static void ShowBitMapColorData(const BITMAP_FORMAT& _bitmap);
	static void BitMapRelease(BITMAP_FORMAT& _bitmapFormat);
private:
	static bool SetUpValue16(const u8* _buffer, u32& sride, const u32 _length, u16& value);
	static bool SetUpValue32(const u8* _buffer, u32& sride, const u32 _length, u32& value);
	static bool SetUpColorDate(const u8* _buffer, u32& sride, const u32 size, const u32 _length,u8* value);
	static bool SetUpColorDate(const u8* _buffer, u32& sride, const u32 _length, const u32 _width, const u32 _height, u8* _value);
};
#endif // !__BMP_ANALYZER_H__
