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
	CMesh* mesh = CResourceManager::CreateResourceObject<CMesh>(CHash::CRC32("TestMesh"));
	CShader* shader = CResourceManager::CreateResourceObject<CShader>(CHash::CRC32("TestMesh"));
	tempObject->SetMesh(mesh);
	tempObject->SetShader(shader);
	m_gameObjectList.PushBack(tempObject);
	return tempObject;
}
