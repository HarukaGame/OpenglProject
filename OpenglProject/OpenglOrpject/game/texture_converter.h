#pragma once
#ifndef __TEXTURE_CONVERTER_H__
#define __TEXTURE_CONVERTER_H__

#include "texture_format.h"
#include "bitmap_format.h"

class CTextureConverter {
public:
	static const void ConvertBitMapToTexture(const BITMAP_FORMAT& _bitmap,TEXTURE_IMAGE& _texture);
};

#endif // !__TEXTURE_CONVERTER_H__
