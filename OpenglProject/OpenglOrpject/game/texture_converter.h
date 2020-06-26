#pragma once
#ifndef __TEXTURE_CONVERTER_H__
#define __TEXTURE_CONVERTER_H__

#include "texture.h"
#include "bitmap_format.h"

class Ctexture;

class CTextureConverter {
public:
	static const void ConvertBitMapToTexture(const BITMAP_FORMAT& _bitmap,CTexture& _texture);
};

#endif // !__TEXTURE_CONVERTER_H__
