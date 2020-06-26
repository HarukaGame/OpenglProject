#include "texture.h"
#include "GL/glew.h"
#include <fstream>

#define TEXTURE_SIZE (512)

void CTexture::CreateBuffer() {
	glGenTextures(1,&m_buffer);

    std::ifstream fstr("game/res/bmpfiles/test.bmp", std::ios::binary);
    const size_t fileSize = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
    fstr.seekg(0, fstr.beg);
    char* textureBuffer = new char[fileSize];
    fstr.read(textureBuffer, fileSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, m_buffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_SIZE, TEXTURE_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, textureBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    delete[] textureBuffer;
    glBindTexture(GL_TEXTURE_2D, 0);
}