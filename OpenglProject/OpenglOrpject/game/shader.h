#pragma once
#ifndef __SHADER_H__
#define __SHADER_H__

#include "resource_base.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

typedef unsigned int GLuint;
enum SHADER_UNIFORM {
	SHADER_UNIFORM_COLOR,
	SHADER_UNIFORM_LIGHT,
	SHADER_UNIFORM_MVP,
	SHADER_UNIFORM_MODEL_MAT,
	SHADER_UNIFORM_TEXTURE,
	SHADER_UNIFORM_NORMAL_MAP,
	SHADER_UNIFORM_ADD_POSITION,
	SHADER_UNIFORM_SCALE,
	SHADER_UNIFORM_RATIO,
	SHADER_UNIFORM_TRANS_SLOPE,
	SHADER_UNIFORM_UV,
	SHADER_UNIFORM_NUM
};

enum SHADER_ATTRIBUTE {
	SHADER_ATTRIBUTE_POSITION,
	SHADER_ATTRIBUTE_NORMAL,
	SHADER_ATTRIBUTE_UV,
	SHADER_ATTRIBUTE_TANGENT,
	SHADER_ATTRIBUTE_NUM
};

class CShader:public CResourceBase {
public:
	bool SetUpUniform();
	int GetProgramID()const;
	int GetUniform(SHADER_UNIFORM _uniform)const;
	int GetAttribute(SHADER_ATTRIBUTE _attribute)const;
	void CreateShaderProgram(const char* _vertSource,int _vertLength, const char* _fragSource, int _fragLength);

	void SetTransparent(const bool _value)const;
	bool GetTransparent()const;
	void Finalize()override;
	void SetRatio(float _ratio)const;
	void SetColor(const glm::vec3 _color)const;
	void SetScale(const glm::vec3 _scale)const;
	void SetSlope(const float _slope)const;
	void SetUV(const glm::vec2& _uv)const;
private:
	mutable bool m_transparent = false;
	GLuint m_programID = 0;
	int m_uniformList[SHADER_UNIFORM_NUM] = { -1 };
	int m_attributeList[SHADER_ATTRIBUTE_NUM] = { -1 };
};
#endif // !__SHADER_H__
