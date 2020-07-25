#include "text_object.h"

#include "hash.h"
#include "gameobject.h"
#include "object_manager.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

bool CCharObject::SetUp(CObjectManager* _objectManager, const CMesh* _mesh, const CShader* _shader, const CTexture* _texture)
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
	m_gameObject = _objectManager->CreateGameObject();
	_shader->SetTransparent(true);

	m_gameObject->SetMesh(_mesh);
	m_gameObject->SetShader(_shader);
	m_gameObject->SetTexture(_texture);


	m_shader = _shader;
	m_objectManager = _objectManager;

	return true;
}

void CCharObject::SetChar(const char _char)
{
	if (m_shader == nullptr) {
		return;
	}
	m_char = _char;
	float x = (1.0f / 16.0f) * (m_char & 0x0f);
	float y = (1.0f / 8.0f) * (m_char >> 4);
	m_gameObject->SetAddUV(glm::vec3(x, y, 0));
	//m_shader->SetUV(glm::vec2(x, y));
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

void CCharObject::SetPosition(const glm::vec3& _pos)
{
	m_gameObject->SetPosition(_pos.x,_pos.y,_pos.z);
}

void CCharObject::Finalize()
{
	if (m_objectManager == nullptr) {
		return;
	}

	m_objectManager->DeleteObject(m_gameObject->GetHash());
}

bool CTextObject::SetUp(CObjectManager* _objectManager, const CMesh* _mesh, const CShader* _shader, const CTexture* _texture)
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

	m_objectManager = _objectManager;
	m_mesh = _mesh;
	m_shader = _shader;
	m_texture = _texture;
	return true;
}

void CTextObject::SetText(const char* _text, const glm::vec2& _pos, const glm::vec2& _scale)
{
	if (_text == nullptr) {
		return;
	}
	unsigned int charCounter = 0;
	while (_text[charCounter] != '\0') {
		charCounter++;
	}

	while (m_charList.Length() != charCounter) {
		if (m_charList.Length() > charCounter) {
			CCharObject* tempChar = (*m_charList.Begin());
			tempChar->Finalize();
			delete tempChar;
			m_charList.PopFront();
		}
		else {
			CCharObject* newChar = new CCharObject();
			newChar->SetUp(m_objectManager, m_mesh, m_shader, m_texture);
			m_charList.PushFront(newChar);
		}
	}

	CList<CCharObject*>::iterator iter = m_charList.Begin();
	CList<CCharObject*>::iterator end = m_charList.End();
	unsigned int tempCounter = 0;
	for (; iter != end; iter++) {
		(*iter)->SetChar(_text[tempCounter]);
		(*iter)->SetScale(1.0f);
		(*iter)->SetPosition(m_centerPos + glm::vec3(1, 0, 0) * 1.0f * (float)tempCounter);
		tempCounter++;
	}

}

void CTextObject::SetPosition(const glm::vec3& _pos)
{
}

void CTextObject::Finalize()
{
	CList<CCharObject*>::iterator iter = m_charList.Begin();
	CList<CCharObject*>::iterator end = m_charList.End();
	for (; iter != end; iter++) {
		(*iter)->Finalize();
		delete (*iter);
	}
	m_charList.Clear();
}
