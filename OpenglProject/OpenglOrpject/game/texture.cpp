#include "texture.h"
#include "GL/glew.h"
#include <fstream>
#include "debug_print.h"

#define TEXTURE_SIZE (512)


void CTexture::CreateBuffer() {
	glGenTextures(1,&m_textureID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_textureBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void CTexture::SetTextureBuffer(const unsigned char* _textureBuffer, const int _width, const int _height, const int _elementNum)
{
    m_textureBuffer = _textureBuffer;
    m_width = _width;
    m_height = _height;
    m_elementNum = _elementNum;
}

void CTexture::CreateNormalBuffer()
{
    glGenTextures(1, &m_normalID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, m_normalID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_normalBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

}

void CTexture::SetNormalBuffer(const unsigned char* _normalBuffer, const int _width, const int _height, const int _elementNum)
{
    m_normalBuffer = _normalBuffer;
    m_width = _width;
    m_height = _height;
    m_elementNum = _elementNum;

}

void CTexture::Finalize()
{
    glDeleteTextures(1, &m_textureID);
}
