#pragma once
#ifndef __BITMAP_FORMAT_H__

typedef char c8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;


typedef struct {
	u16 m_bfType;
	u32 m_bfSize;
	u16 m_bfReserved1;
	u16 m_bfReserved2;
	u32 m_bfOffBits;
}BITMAP_HEADER_FILE;

typedef struct {
	u32 m_biSize;
	u32 m_biWidth;
	u32 m_biHeight;
	u16 m_biPlanes;
	u16 m_biBitCount;
	u32 m_biCompression;
	u32 m_biSizeImage;
	u32 m_biXPelsPerMeter;
	u32 m_biYPelsPerMeter;
	u32 m_biClrUsed;
	u32 m_biClrImportant;
}BITMAP_INFORMATION_FILE;

typedef struct {
	BITMAP_HEADER_FILE m_headerFile;
	BITMAP_INFORMATION_FILE m_infoFile;
	c8* date = nullptr;
}BITMAP_FORMAT;

#endif // !__BITMAP_FORMAT_H__
