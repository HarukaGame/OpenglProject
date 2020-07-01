#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include "resource_base.h"

enum IMAGE_FORMAT {
	IMAGE_FORMAT_NONE,
	IMAGE_FORMAT_RGB,
	IMAGE_FORMAT_RGBA,
};

class CTexture:public CResourceBase {
public:
	void CreateBuffer();
	void SetTextureBuffer(const unsigned char* _textureBuffer,const int _width,const int _height,const int _elementNum);
	void Finalize()override;
	unsigned int m_buffer = 0;
	unsigned char* m_pData = nullptr;
	IMAGE_FORMAT m_imageFormat = IMAGE_FORMAT_NONE;
	int m_width = 0;
	int m_height = 0;
	int m_elementNum = 0;
	int m_size = 0;
	const unsigned char* m_textureBuffer;
};
#endif // !__TEXTURE_H__
