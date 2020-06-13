#include "object_manager.h"
#include "gameobject.h"
#include "resource_manager.h"
#include "renderer.h"

#include "shader.h"
#include "buffer.h"
#include "mesh.h"

#include "camera.h"

bool CObjectManager::Initilize()
{
	if (CCamera::CreateInstance(800,600) == false) {
		return false;
	}
	return true;
}

void CObjectManager::Finalize()
{
	CCamera::Destroy();
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
	CMesh* mesh = CResourceManager::CreateMesh();
	CShader* shader = CResourceManager::CreateShader();
	tempObject->SetMesh(mesh);
	tempObject->SetShader(shader);
	m_gameObjectList.PushBack(tempObject);
	return tempObject;
}
