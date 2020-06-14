#include "resource_manager.h"
#include "Mesh.h"
#include "shader.h"
#include "fileloader.h"
#include "shader_loader.h"
#include "mesh.h"
#include "buffer.h"
#include "debug_print.h"

CResourceManager* CResourceManager::s_instance = nullptr;
//template CMesh* CResourceManager::CreateResourceObject();
//template CShader* CResourceManager::CreateResourceObject();

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

template<class T>
T* CResourceManager::CreateResourceObject() {
	PRINT("CResourceManager::CreateResourceObject() T not Supported\n");
	return T();
}

template<>
CMesh* CResourceManager::CreateResourceObject() {
	return CResourceManager::CreateMesh();
}

template<>
CShader* CResourceManager::CreateResourceObject() {
	return CResourceManager::CreateShader();
}


CShader* CResourceManager::CreateShader()
{
	CFileLoader* vertFile = new CFileLoader();
	CFileLoader* fragFile = new CFileLoader();
	vertFile->LoadFile("game/ShaderFiles/basic.vs");
	fragFile->LoadFile("game/ShaderFiles/basic.fs");
	int programID = CShaderLoader::CreateShaderProgram(vertFile->GetBuffer(), vertFile->GetLength(), fragFile->GetBuffer(), fragFile->GetLength());


	CShader* ret = new CShader();
	ret->SetUpUniform(programID);
	return ret;
}

CMesh* CResourceManager::CreateMesh()
{
	CMesh* tempMesh = new CMesh();
	tempMesh->InitVertex();
	tempMesh->CreateBuffer();
	return tempMesh;
}
