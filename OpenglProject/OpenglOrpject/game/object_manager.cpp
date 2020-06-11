#include "object_manager.h"
#include "gameobject.h"
#include "resource_manager.h"

void CObjectManager::AllObjectDraw(CRenderer* _renderer)
{
}

CGameObject* CObjectManager::CreateGameObject()
{
	CGameObject* tempObject = new CGameObject();
	CMesh* mesh = CResourceManager::CreateMesh();
	CShader* shader = CResourceManager::CreateShader();
	tempObject->SetMesh(mesh);
	tempObject->SetShader(shader);
	return tempObject;
}
