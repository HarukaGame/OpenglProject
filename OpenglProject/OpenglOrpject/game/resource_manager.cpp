#include "resource_manager.h"
#include "Mesh.h"
#include "shader.h"
#include "fileloader.h"
#include "shader_loader.h"
#include "mesh.h"

CResourceManager* CResourceManager::s_instance = nullptr;

bool CResourceManager::CreateInstance()
{
	if (s_instance == nullptr) {
		s_instance = new CResourceManager();
	}
	if (s_instance == nullptr) {
		return false;
	}
	return true;
}

void CResourceManager::Destroy()
{
	if (s_instance != nullptr) {
		delete s_instance;
	}
}

CShader* CResourceManager::CreateShader()
{
	CFileLoader* vertFile = new CFileLoader();
	CFileLoader* fragFile = new CFileLoader();
	vertFile->LoadFile("game/res/basic.vs");
	fragFile->LoadFile("game/res/basic.fs");
	int programID = CShaderLoader::CreateShaderProgram(vertFile->GetBuffer(), vertFile->GetLength(), fragFile->GetBuffer(), fragFile->GetLength());


	CShader* ret = new CShader();
	ret->SetUpUniform(programID);
	return nullptr;
}

CMesh* CResourceManager::CreateMesh()
{
	CMesh* tempMesh = new CMesh();
	tempMesh->InitVertex();
	return tempMesh;
}
