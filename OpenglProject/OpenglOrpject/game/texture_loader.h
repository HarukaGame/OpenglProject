#pragma once
#ifndef __TEXTURE_LOADER_H__
#define __TEXTURE_LOADER_H__

enum TEXTURE_FORMAT {
	TEXTURE_FORMAT_NONE,
	TEXTURE_FORMAT_BITMAP,
};


class CTextureConverter {
public:
	bool LoadTexture(const char* _filePath);
	bool ConvertTexture(const void* _buffer, const unsigned int _length);
	unsigned char* GetBuffer()const;
	int GetHeight()const;
	int GetWidth()const;
	int GetElementNum()const;
	void Release();
private:
	unsigned char* m_pBuffer = nullptr;
	int m_width = 0;
	int m_height = 0;
	int m_elementNum = 0;
	int m_size = 0;
	TEXTURE_FORMAT m_textureFormat ;
};
#endif // !__TEXTURE_LOADER_H__
