#include "texture_converter.h"

const void CTextureConverter::ConvertBitMapToTexture(const BITMAP_FORMAT& _bitmap, TEXTURE_IMAGE& _texture)
{
	int width = _bitmap.m_infoFile.m_biWidth;
	int height = _bitmap.m_infoFile.m_biHeight;
	int size = width * height * 3;
	for (int i = 0; i < size; i++) {
		_texture.m_pData[i] = _bitmap.date[i];
		_texture.m_pData[i+1] = _bitmap.date[i+1];
		_texture.m_pData[i+2] = _bitmap.date[i+2];
		_texture.m_pData[i+3] = _bitmap.date[i+3];
	}

}
