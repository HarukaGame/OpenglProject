#pragma once
#ifndef __TEXT_OBJECT_H__
#define __TEXT_OBJECT_H__

class CObjectManager;
class CGameObject;
class CMesh;
class CShader;
class CTexture;

class CCharObject {
public:
	bool SetUp(const char _char, CObjectManager* _objectManager, const CMesh* _mesh, const CShader* _shader, const CTexture* _texture);
	void SetChar(const char _char);
	void SetScale(const float _x, const float _y);
	void SetScale(const float _scale);
private:
	CGameObject* m_gameObject = nullptr;
	const CShader* m_shader = nullptr;
	char m_char = ' ';
};

#endif // !__TEXT_OBJECT_H__
