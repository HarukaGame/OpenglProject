#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include "resource_base.h"

class CTexture:public CResourceBase {
public:
	void CreateBuffer();
	unsigned int m_buffer = 0;
	unsigned char* m_pData = nullptr;
	int m_width = 0;
	int m_height = 0;
	int m_size = 0;
};
#endif // !__TEXTURE_H__
