#include "bmp_analyzer.h"

#define BUFFER(i,j) ((i*)(&j))[0]
#define BIT_COUNT_PER_BYTE (8)
#define BYTE_FILL (0xff)
#define IS_BITMAP (0x4d42)

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


	if (_bitmapFormat.m_headerFile.m_bfType != IS_BITMAP) {
		PRINT("Is not BitMap Format\n");
		return false;
	}
	PRINT("File is BitMap Format\n");

	if (_bitmapFormat.m_infoFile.m_biBitCount == 8 ||
		_bitmapFormat.m_infoFile.m_biBitCount == 4 ||
		_bitmapFormat.m_infoFile.m_biBitCount == 1) {
		SerUpColorPalette(buffer, sride, _length, _bitmapFormat);
	}

	u32 size = _bitmapFormat.m_infoFile.m_biWidth * _bitmapFormat.m_infoFile.m_biHeight * 3;
	_bitmapFormat.date = (u8*)malloc(size);
	if (_bitmapFormat.date == nullptr) {
		PRINT("memory error\n");
	}

	success = false;
	//success = SetUpColorDate(buffer, sride, size, _length, _bitmapFormat.date);
	if (_bitmapFormat.m_infoFile.m_biBitCount == 24) {
		success = SetUpColorData24(buffer, sride, _bitmapFormat);
		if (success == false) {
			PRINT("24bit color data buffer memory over\n");
			return false;
		}

	}
	else if (_bitmapFormat.m_infoFile.m_biBitCount == 8 ||
			 _bitmapFormat.m_infoFile.m_biBitCount == 4 || 
			 _bitmapFormat.m_infoFile.m_biBitCount == 1)
	{
		success = SetUpColorDataByColorPalette(buffer, sride, _bitmapFormat);
		if (success == false) {
			PRINT("%d bit color data buffer memory over\n",_bitmapFormat.m_infoFile.m_biBitCount);
			return false;
		}

	}
	//else if (_bitmapFormat.m_infoFile.m_biBitCount == 4) {
	//	success = SetUpColorDate4(buffer, sride, _bitmapFormat);
	//	if (success == false) {
	//		PRINT("4bit color data buffer memory over\n");
	//		return false;
	//	}
	//}

	////BGR→RGB変換
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
	PRINT("\n\n\n");
	PRINT("--------------------------------------------\n");
	PRINT("BitMap Information start\n");
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
	PRINT("BitMap Information end\n");
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

void CBmpAnalyzer::SerUpColorPalette(const u8* _buffer, u32& _sride, const u32 _length, BITMAP_FORMAT& _bitmapFormat)
{
	u32 start = _sride;
	u32 colorPaletteSize = pow(2, _bitmapFormat.m_infoFile.m_biBitCount);

	for (u32 i = 0; i < colorPaletteSize; i++) {
		_bitmapFormat.m_colorPalette[i].m_rgbBlue = BUFFER(u8, _buffer[_sride]);
		_bitmapFormat.m_colorPalette[i].m_rgbGreen = BUFFER(u8, _buffer[_sride + 1]);
		_bitmapFormat.m_colorPalette[i].m_rgbRed = BUFFER(u8, _buffer[_sride + 2]);
		_bitmapFormat.m_colorPalette[i].m_rgbReserved = BUFFER(u8, _buffer[_sride + 3]);
		_sride += 4;
	}
}


bool CBmpAnalyzer::SetUpColorData24(const u8* _buffer, u32& _sride, const BITMAP_FORMAT _bitmap)
{
	u32 index = _sride;
	u32 height = _bitmap.m_infoFile.m_biHeight;
	u32 width = _bitmap.m_infoFile.m_biWidth;
	u32 size = width * height * 3;
	u32 padding = width % 4;
	u32 sumPadding = padding * height;
	if (_sride + size > _bitmap.m_headerFile.m_bfSize) {
		return false;
	}
	for (u32 y = 0; y < height; y++) {
		sumPadding -= padding;

		for (u32 x = 0; x < width; x++) {
			int valueIndex = (y * width + x) * 3;
			//上下反転用変数
			int bufferIndex = _sride+ sumPadding +((height - y - 1) * width + x) * 3;
			//BGRからRGBに変換
			_bitmap.date[valueIndex + 0] = _buffer[bufferIndex + 2];
			_bitmap.date[valueIndex + 1] = _buffer[bufferIndex + 1];
			_bitmap.date[valueIndex + 2] = _buffer[bufferIndex + 0];
		}
	}
	return true;
}


bool CBmpAnalyzer::SetUpColorDataByColorPalette(const u8* _buffer, u32& _sride, const BITMAP_FORMAT _bitmap)
{
	u32 height = _bitmap.m_infoFile.m_biHeight;
	u32 width = _bitmap.m_infoFile.m_biWidth;
	u32 bitCount = _bitmap.m_infoFile.m_biBitCount;
	u32 colorPerByte = BIT_COUNT_PER_BYTE / bitCount;
	u8 bitMask = BYTE_FILL >> (BIT_COUNT_PER_BYTE - bitCount);

	u32 size = height * width / colorPerByte;

	//バッファサイズ内に収まっているかチェック
	if (_sride + size > _bitmap.m_headerFile.m_bfSize) {
		return false;
	}
	u32 colorNumPer4Byte = colorPerByte * 4;
	u32 padding = (colorNumPer4Byte - width % colorNumPer4Byte) % colorNumPer4Byte;
	//u32 padding = width % (colorPerByte * 4);
	//padding = (colorPerByte * 4) - padding;
	//padding = padding % (colorPerByte * 4);
	u32 sumPadding = padding * height;

	u32 bufferIndex;
	u32 shiftNum;
	for (u32 y = 0; y < height; y++) {
		sumPadding -= padding;
		for (u32 x = 0; x < width; x++) {
			//値を入れるインデックス
			u32 valueIndex = (y * width + x) * 3;
			//上下反転してバッファのインデックスを登録
			bufferIndex = (height - y - 1) * width + x;
			bufferIndex += sumPadding;
			bufferIndex /= colorPerByte;
			bufferIndex += _bitmap.m_headerFile.m_bfOffBits;
			//ビットシフトの数
			shiftNum = ((colorPerByte - 1) -  x % colorPerByte) * bitCount;
			//u32 shiftNum = ((colorPerByte - 1) - (y * width + x) % colorPerByte) * bitCount;
			//カラーパレットのインデックスを取得
			u32 colorIndex = (_buffer[bufferIndex] & (bitMask << shiftNum)) >> shiftNum;

			_bitmap.date[valueIndex + 0] = _bitmap.m_colorPalette[colorIndex].m_rgbRed;
			_bitmap.date[valueIndex + 1] = _bitmap.m_colorPalette[colorIndex].m_rgbGreen;
			_bitmap.date[valueIndex + 2] = _bitmap.m_colorPalette[colorIndex].m_rgbBlue;
		}
		int a = 0;
	}
	_sride += size;
	return true;
}
