#include "text_object.h"

#include "hash.h"
#include "gameobject.h"
#include "object_manager.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

bool CCharObject::SetUp(const char _char,CObjectManager* _objectManager, const CMesh* _mesh, const CShader* _shader, const CTexture* _texture)
{
	if (_shader == nullptr) {
		return false;
	}
	if (_objectManager == nullptr) {
		return false;
	}
	if (_mesh == nullptr) {
		return false;
	}
	if (_texture == nullptr) {
		return false;
	}
	m_gameObject = _objectManager->CreateGameObject(CHash::CRC32("CharObject"));
	_shader->SetTransparent(true);

	m_gameObject->SetMesh(_mesh);
	m_gameObject->SetShader(_shader);
	m_gameObject->SetTexture(_texture);


	m_shader = _shader;

	SetChar(_char);
	return false;
}

void CCharObject::SetChar(const char _char)
{
	if (m_shader == nullptr) {
		return;
	}
	m_char = _char;
	float x = (1.0f / 16.0f) * (m_char & 0x0f);
	float y = (1.0f / 8.0f) * (m_char >> 4);
	m_shader->SetUV(glm::vec2(x, y));
}

void CCharObject::SetScale(const float _x, const float _y)
{
	if (m_gameObject == nullptr) {
		return;
	}
	m_gameObject->SetScale(_x, _y, 1.0f);
}

void CCharObject::SetScale(const float _scale)
{
	if (m_gameObject == nullptr) {
		return;
	}
	m_gameObject->SetScale(_scale, _scale, 1.0f);
}
