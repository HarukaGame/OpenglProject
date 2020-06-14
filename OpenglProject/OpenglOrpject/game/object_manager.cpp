#include "object_manager.h"
#include "gameobject.h"
#include "resource_manager.h"
#include "renderer.h"

#include "shader.h"
#include "buffer.h"
#include "mesh.h"

#include "camera.h"
#include "light.h"

#include "hash.h"

bool CObjectManager::Initilize()
{
	if (CCamera::CreateInstance(800,600) == false) {
		return false;
	}

	CCamera::GetInstance()->SetTargetPosition(glm::vec3(0, 0, 0));

	if (CLight::CreateInstance() == false) {
		return false;
	}

	CLight::GetInstance()->SetRotate(0, 0);
	return true;
}

void CObjectManager::Finalize()
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	while (m_gameObjectList.Empty() == false) {
		(*iter)->Finalize();
		delete (*iter);
		m_gameObjectList.PopFront();
		iter = m_gameObjectList.Begin();
	}

	CCamera::Destroy();
	CLight::Destory();
}

void CObjectManager::AllObjectDraw(CRenderer* _renderer)
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	for (; iter != m_gameObjectList.End(); iter++) {
		CShader* shader = (*iter)->GetShader();
		CBuffer* buffer = (*iter)->GetMesh()->GetBuffer();
		glm::mat4 model = (*iter)->GetMesh()->GetModelMatrix();
		_renderer->MeshDraw(buffer,shader,model);
	}
}

CGameObject* CObjectManager::CreateGameObject()
{
	CGameObject* tempObject = new CGameObject();
	CMesh* mesh = CResourceManager::SearchOrCreateResourceObject<CMesh>(CHash::CRC32("TestMesh"));
	CShader* shader = CResourceManager::SearchOrCreateResourceObject<CShader>(CHash::CRC32("TestShader"));
	tempObject->SetMesh(mesh);
	tempObject->SetShader(shader);
	m_gameObjectList.PushBack(tempObject);
	return tempObject;
}

CGameObject* CObjectManager::CreateGameObject(const hash _hash)
{
	CGameObject* temp = CreateGameObject();
	temp->SetHash(_hash);
	return temp;
}

CGameObject* CObjectManager::SearchGameObject(const hash _hash)
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	return SearchGameObject(_hash, iter);
}

CGameObject* CObjectManager::SearchGameObject(const hash _hash, CList<CGameObject*>::iterator& _iter)
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	CList<CGameObject*>::iterator end = m_gameObjectList.End();
	for (; iter != end; iter++) {
		if ((*iter)->GetHash() == _hash) {
			_iter = iter;
			return (*iter);
		}
	}
	return nullptr;
}

void CObjectManager::DeleteObject(const hash _hash)
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	CGameObject* temp = SearchGameObject(_hash, iter);
	if (temp == nullptr) {
		return;
	}
	temp->Finalize();
	delete temp;
	m_gameObjectList.Pop(iter);
}
