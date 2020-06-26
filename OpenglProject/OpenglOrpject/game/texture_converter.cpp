#include "texture_converter.h"

const void CTextureConverter::ConvertBitMapToTexture(const BITMAP_FORMAT& _bitmap, CTexture& _texture)
{
	int width = _bitmap.m_infoFile.m_biWidth;
	int height = _bitmap.m_infoFile.m_biHeight;
	int size = width * height * 3;
	for (int i = 0; i < size; i++) {
		_texture.m_pData[i] = _bitmap.date[i];
	}

}
