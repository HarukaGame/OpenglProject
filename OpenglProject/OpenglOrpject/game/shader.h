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

enum SHADER_ATTRIBUTE {
	SHADER_ATTRIBUTE_POSITION,
	SHADER_ATTRIBUTE_NUM
};

class CShader {
public:
	bool SetUpUniform(int _programID);
	int GetProgramID()const;
	int GetUniform(SHADER_UNIFORM _uniform)const;
	int GetAttribute(SHADER_ATTRIBUTE _attribute)const;
private:
	GLuint m_programID = 0;
	int m_uniformList[SHADER_UNIFORM_NUM] = { -1 };
	int m_attributeList[SHADER_ATTRIBUTE_NUM] = { -1 };
};
#endif // !__SHADER_H__
