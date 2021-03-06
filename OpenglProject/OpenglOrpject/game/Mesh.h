﻿#pragma once
#ifndef __MESH_H__
#define __MESH_H__
typedef unsigned int GLuint;
typedef int GLint;
typedef float GLfloat;

#include "glm/glm.hpp"
#include "resource_base.h"


class CRenderer;
class CBuffer;
class CMesh:public CResourceBase {
	friend class CRenderer;
public:
	//GLuint CreateShaderProgram(GLuint programID);
	//GLint CreateVAO();

	void InitVertex();

	//void SetColor(float r, float g, float b, float a);
	//void SetLight(float x, float y, float z);
	bool CreateBuffer();
	CBuffer* GetBuffer()const;
	GLuint GetVertexNum()const { return vertexNum; }
	GLuint GetElementNum()const { return elementNum; }
	void AddTangent();
	glm::mat4 GetModelMatrix()const;
	void Finalize()override;

	const float* myvertices;
	const float* m_normals;
	const unsigned int* indeces;

	GLuint vertexNum = 0;
	GLuint elementNum = 0;
	GLuint indexNum = 0;

	glm::vec3 m_pos = glm::vec3(0, 0, 0);
	glm::vec3 m_rot = glm::vec3(0, 0, 0);
	glm::vec3 m_scale = glm::vec3(1, 1, 1);

	bool m_isIndex = false;
	bool m_tangentFrag = false;
private:

	glm::mat4 GetTransMatrix(glm::vec3 trans)const;
	glm::mat4 GetRotateMatrix(glm::vec3 rotate)const;
	glm::mat4 GetScaleMatrix(glm::vec3 scale)const;

	CBuffer* m_pBuffer = nullptr;

	//float myvertices[18] = {
	//-0.5f , -0.5f ,0.0f, // Bottom left corner
	//-0.5f ,  0.5f ,0.0f, // Top left corner
	// 0.5f ,  0.5f ,0.0f, // Top Right corner    
	// 0.5f , -0.5f, 0.0f, // Bottom right corner
	//-0.5f , -0.5f, 0.0f, // Bottom left corner
	// 0.5f ,  0.5f, 0.0f, // Top Right corner 
	//};

	//GLuint m_programID = 0;

	//GLint m_uniformColor = -1;
	//GLint m_uniformModelMat = -1;
	//GLint m_uniformLight = -1;

	//GLuint m_vaoID = -1;
	//GLuint m_vboID = -1;
	//GLuint m_normalID = -1;
};

#endif