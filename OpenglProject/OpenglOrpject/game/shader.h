#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

typedef unsigned int GLuint;
enum SHADER_UNIFORM {
	SHADER_UNIFORM_COLOR,
	SHADER_UNIFORM_LIGHT,
	SHADER_UNIFORM_MVP,
	SHADER_UNIFORM_NUM
};

class CShader {
public:
	bool SetUpUniform(int _programID);
private:
	GLuint m_programID = 0;
	int m_uniformList[SHADER_UNIFORM_NUM] = { -1 };
};
#endif // !__SHADER_H__
