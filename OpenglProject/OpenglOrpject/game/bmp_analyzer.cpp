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
	_bitmapFormat.date = (u8*)malloc(size);
	if (_bitmapFormat.date == nullptr) {
		PRINT("memory error\n");
	}

	for (u32 i = 0; i < 100; i++) {
		//PRINT("%u\n",*BUFFER(u16, buffer[i]));
	}
	PRINT("-----------------------------------------------------------------------\n");
	//success = SetUpColorDate(buffer, sride, size, _length, _bitmapFormat.date);
	success = SetUpColorDate(buffer, sride, _length,_bitmapFormat.m_infoFile.m_biWidth,_bitmapFormat.m_infoFile.m_biHeight, _bitmapFormat.date);
	if (success == false) {
		PRINT("color data buffer memory over\n");
		return false;
	}
	////BGR��RGB�ϊ�
	//char temp;
	//for (int i = 0; i < size; i+=3) {
	//	temp = (_bitmapFormat.date)[i];
	//	(_bitmapFormat.date)[i] = (_bitmapFormat.date)[i + 2];
	//	(_bitmapFormat.date)[i + 2] = temp;

	//}

	PRINT("BitMap analyze success\n");
	return true;
}

void CBmpAnalyzer::ShowBitMapInfo(const BITMAP_FORMAT& _bitmap)
{
	PRINT("\n\nBitMap Information\n");
	PRINT("--------------------------------------------\n");
	PRINT("Type            %04x\n", _bitmap.m_headerFile.m_bfType);
	PRINT("FileSize        %d\n", _bitmap.m_headerFile.m_bfSize);
	PRINT("Reserved1       %d\n", _bitmap.m_headerFile.m_bfReserved1);
	PRINT("Reserved2       %d\n", _bitmap.m_headerFile.m_bfReserved2);
	PRINT("OffsetBit       %d\n", _bitmap.m_headerFile.m_bfOffBits);

	PRINT("HeaderSize      %d\n", _bitmap.m_infoFile.m_biSize);
	PRINT("Width           %d\n", _bitmap.m_infoFile.m_biWidth);
	PRINT("Height          %d\n", _bitmap.m_infoFile.m_biHeight);
	PRINT("Planes          %d\n", _bitmap.m_infoFile.m_biPlanes);
	PRINT("BitCount        %d\n", _bitmap.m_infoFile.m_biBitCount);
	PRINT("Compression     %d\n", _bitmap.m_infoFile.m_biCompression);
	PRINT("SizeImage       %d\n", _bitmap.m_infoFile.m_biSizeImage);
	PRINT("XPixelPerMeter  %d\n", _bitmap.m_infoFile.m_biXPelsPerMeter);
	PRINT("YPixelPerMeter  %d\n", _bitmap.m_infoFile.m_biYPelsPerMeter);
	PRINT("ColorUsed       %d\n", _bitmap.m_infoFile.m_biClrUsed);
	PRINT("ColorImportant  %d\n", _bitmap.m_infoFile.m_biClrImportant);
	PRINT("--------------------------------------------\n");
}

void CBmpAnalyzer::ShowBitMapColorData(const BITMAP_FORMAT& _bitmap)
{
	u32 size = _bitmap.m_infoFile.m_biWidth * _bitmap.m_infoFile.m_biHeight;
	for (u32 i = 0; i < size; i++) {
		PRINT("R:%d  G:%d  B:%d\n", _bitmap.date[i*3], _bitmap.date[i*3+1], _bitmap.date[i*3+2]);
	}
}

void CBmpAnalyzer::BitMapRelease(BITMAP_FORMAT& _bitmapFormat)
{
	 free(_bitmapFormat.date);
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

bool CBmpAnalyzer::SetUpColorDate(const u8* _buffer, u32& sride,const u32 size, const u32 _length,u8* value)
{
	u32 index = sride;
	sride += size;
	if (sride > _length) {
		return false;
	}
	for (int i = 0; i + index < _length; i++) {
		value[i] = _buffer[_length - i];
		//value[i] =BUFFER(u8, _buffer[i + index]) ;
	}
	return true;
}

bool CBmpAnalyzer::SetUpColorDate(const u8* _buffer, u32& sride, const u32 _length, const u32 _width, const u32 _height, u8* _value)
{
	u32 index = sride;
	u32 size = _width * _height * 3;
	if (sride + size > _length) {
		return false;
	}
	for (u32 y = 0; y < _height; y++) {
		for (u32 x = 0; x < _width; x++) {
			int valueIndex = (y * _width + x) * 3;

			_value[valueIndex + 0] = _buffer[sride + valueIndex + 0];
			_value[valueIndex + 1] = _buffer[sride + valueIndex + 1];
			_value[valueIndex + 2] = _buffer[sride + valueIndex + 2];
		}
	}
	return true;
}
