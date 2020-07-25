#pragma once
#ifndef __TEXT_OBJECT_H__
#define __TEXT_OBJECT_H__

#include "my_list.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class CObjectManager;
class CGameObject;
class CMesh;
class CShader;
class CTexture;

class CCharObject {
public:
	bool SetUp(CObjectManager* _objectManager, const CMesh* _mesh, const CShader* _shader, const CTexture* _texture);
	void SetChar(const char _char);
	void SetScale(const float _x, const float _y);
	void SetScale(const float _scale);
	void SetPosition(const glm::vec3& _pos);
	void Finalize();
private:
	CObjectManager* m_objectManager = nullptr;
	CGameObject* m_gameObject = nullptr;
	const CShader* m_shader = nullptr;
	char m_char = ' ';
};

class CTextObject {
public:
	bool SetUp(CObjectManager* _objectManager, const CMesh* _mesh, const CShader* _shader, const CTexture* _texture);
	void SetText(const char* _text,const glm::vec2& _pos,const glm::vec2& _scale);
	void SetPosition(const glm::vec3& _pos);
	void Finalize();
private:
	unsigned int m_textNum = 0;
	char* m_text = nullptr;
	bool m_setUped = false;
	glm::vec3 m_centerPos = glm::vec3(0, 0, 0);
	CObjectManager* m_objectManager = nullptr;
	const CMesh* m_mesh = nullptr;
	const CShader* m_shader = nullptr;
	const CTexture* m_texture = nullptr;
	CList<CCharObject*> m_charList = CList<CCharObject*>();
};

#endif // !__TEXT_OBJECT_H__
