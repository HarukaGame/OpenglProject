#include "bmp_analyzer.h"

#define BUFFER(i,j) ((i*)(&j))[0]

bool CBmpAnalyzer::AnalyzeBitMap(const void* _buffer, const u32 _length, BITMAP_FORMAT& _bitmapFormat)
{
	const u8* buffer = (u8*)(_buffer);
	u32 sride = 0;
	bool success = true;
	success &= SetUpValue16(buffer, sride, _length, _bitmapFormat.m_headerFile.m_bfType);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_headerFile.m_bfSize);
	success &= SetUpValue16(buffer, sride, _length, _bitmapFormat.m_headerFile.m_bfReserved1);
	success &= SetUpValue16(buffer, sride, _length, _bitmapFormat.m_headerFile.m_bfReserved2);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_headerFile.m_bfOffBits);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biSize);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biWidth);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biHeight);
	success &= SetUpValue16(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biPlanes);
	success &= SetUpValue16(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biBitCount);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biCompression);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biSizeImage);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biXPelsPerMeter);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biYPelsPerMeter);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biClrUsed);
	success &= SetUpValue32(buffer, sride, _length, _bitmapFormat.m_infoFile.m_biClrImportant);

	if (success == false) {
		PRINT("buffer memory over\n");
		return false;
	}


	if (_bitmapFormat.m_headerFile.m_bfType != 0x4d42) {
		PRINT("Is not BitMap Format\n");
		return false;
	}
	PRINT("File is BitMap Format\n");

	if (_bitmapFormat.m_infoFile.m_biBitCount != 24) {
		PRINT("BitMapCount is not 24\n");
		return false;
	}
	PRINT("BitMapCount is 24\n");
	u32 size = _bitmapFormat.m_infoFile.m_biWidth * _bitmapFormat.m_infoFile.m_biHeight * 3;
	_bitmapFormat.date = (c8*)malloc(size);
	if (_bitmapFormat.date == nullptr) {
		PRINT("memory error\n");
	}

	SetUpColorDate(buffer, sride, size, _length, _bitmapFormat.date);
	if (success == false) {
		PRINT("buffer memory over\n");
		return false;
	}
	//BGRÅ®RGBïœä∑
	char temp;
	for (int i = 0; i < size; i+=3) {
		temp = (_bitmapFormat.date)[i];
		(_bitmapFormat.date)[i] = (_bitmapFormat.date)[i + 2];
		(_bitmapFormat.date)[i + 2] = temp;

	}

	PRINT("BitMap analyze success\n");
	return true;
}

void CBmpAnalyzer::ShowBitMapInfo(const BITMAP_FORMAT& _bitmap)
{
	PRINT("\n\nBitMap Information\n");
	PRINT("--------------------------------------------\n");
	PRINT2("Type            %04x\n", _bitmap.m_headerFile.m_bfType);
	PRINT2("FileSize        %d\n", _bitmap.m_headerFile.m_bfSize);
	PRINT2("Reserved1       %d\n", _bitmap.m_headerFile.m_bfReserved1);
	PRINT2("Reserved2       %d\n", _bitmap.m_headerFile.m_bfReserved2);
	PRINT2("OffsetBit       %04x\n", _bitmap.m_headerFile.m_bfOffBits);

	PRINT2("HeaderSize      %d\n", _bitmap.m_infoFile.m_biSize);
	PRINT2("Width           %d\n", _bitmap.m_infoFile.m_biWidth);
	PRINT2("Height          %d\n", _bitmap.m_infoFile.m_biHeight);
	PRINT2("Planes          %d\n", _bitmap.m_infoFile.m_biPlanes);
	PRINT2("BitCount        %d\n", _bitmap.m_infoFile.m_biBitCount);
	PRINT2("Compression     %d\n", _bitmap.m_infoFile.m_biCompression);
	PRINT2("SizeImage       %d\n", _bitmap.m_infoFile.m_biSizeImage);
	PRINT2("XPixelPerMeter  %d\n", _bitmap.m_infoFile.m_biXPelsPerMeter);
	PRINT2("YPixelPerMeter  %d\n", _bitmap.m_infoFile.m_biYPelsPerMeter);
	PRINT2("ColorUsed       %d\n", _bitmap.m_infoFile.m_biClrUsed);
	PRINT2("ColorImportant  %d\n", _bitmap.m_infoFile.m_biClrImportant);
	PRINT("--------------------------------------------\n");
}

bool CBmpAnalyzer::SetUpValue16(const u8* _buffer, u32& sride, const u32 _length, u16& value)
{
	u32 index = sride;
	sride += sizeof(u16);
	if (sride >= _length) {
		return false;
	}
	value = BUFFER(u16, _buffer[index]);
	return true;
}

bool CBmpAnalyzer::SetUpValue32(const u8* _buffer, u32& sride, const u32 _length, u32& value)
{
	u32 index = sride;
	sride += sizeof(u32);
	if (sride >= _length) {
		return false;
	}
	value = BUFFER(u32, _buffer[index]);
	return true;
}

bool CBmpAnalyzer::SetUpColorDate(const u8* _buffer, u32& sride,const u32 size, const u32 _length, c8* value)
{
	u32 index = sride;
	sride += size;
	if (sride >= _length) {
		return false;
	}
	value = (c8*)_buffer[index];
	return true;
}
