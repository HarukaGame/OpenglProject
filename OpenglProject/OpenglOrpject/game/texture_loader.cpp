#include "texture_loader.h"
#include "fileloader.h"
#include "bmp_analyzer.h"

bool CTextureLoader::LoadTexture(const char* _filePath)
{
	CFileLoader fileLoader = CFileLoader();
	fileLoader.LoadFile(_filePath);

	BITMAP_FORMAT bitmap;
	bool success = CBmpAnalyzer::AnalyzeBitMap(fileLoader.GetVoidBuffer(), fileLoader.GetLength(), bitmap);
	if (success == true) {
		m_width = bitmap.m_infoFile.m_biWidth;
		m_height = bitmap.m_infoFile.m_biHeight;
		m_elementNum = 3;
		m_pBuffer = (u8*)malloc(m_width * m_height * 3);
		for (int y = 0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {
				//ã‰º”½“]—p•Ï”
				int valueIndex = (y * m_width + x) * 3;
				int bufferIndex = ((m_height - y - 1) * m_width + x) * 3;

				//BGR‚©‚çRGB‚É•ÏŠ·
				m_pBuffer[valueIndex + 0] = bitmap.date[bufferIndex + 2];
				m_pBuffer[valueIndex + 1] = bitmap.date[bufferIndex + 1];
				m_pBuffer[valueIndex + 2] = bitmap.date[bufferIndex + 0];
			}
		}
	}
	CBmpAnalyzer::BitMapRelease(bitmap);
	if (success == true) {
		return true;
	}


	return false;
}

int CTextureLoader::GetHeight() const
{
	return m_height;
}

int CTextureLoader::GetWidth() const
{
	return m_width;
}

int CTextureLoader::GetElementNum() const
{
	return m_elementNum;
}

unsigned char* CTextureLoader::GetBuffer()const
{
	return m_pBuffer;
}

void CTextureLoader::Release()
{
	free(m_pBuffer);
}
