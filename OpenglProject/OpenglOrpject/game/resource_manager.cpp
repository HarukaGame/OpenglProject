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
//---------------------------------------------------------------------------------------
//SearchResourceObject
//---------------------------------------------------------------------------------------
template<class T>
T* CResourceManager::SearchResourceObject(const hash _hash) {
	PRINT("CResourceManager::SearchResourceObject() T not Supported\n");
	return nullptr;
}

template<>
CMesh* CResourceManager::SearchResourceObject(const hash _hash) {
	CList<CMesh*>::iterator iter = s_instance->m_meshList.Begin();
	CList<CMesh*>::iterator end = s_instance->m_meshList.End();
	for (; iter != end; iter++) {
		if ((*iter)->GetHash() == _hash) {
			return (*iter);
		}
	}
	return nullptr;
}

template<>
CShader* CResourceManager::SearchResourceObject(const hash _hash) {
	CList<CShader*>::iterator iter = s_instance->m_shaderList.Begin();
	CList<CShader*>::iterator end = s_instance->m_shaderList.End();
	for (; iter != end; iter++) {
		if ((*iter)->GetHash() == _hash) {
			return (*iter);
		}
	}
	return nullptr;
}

//---------------------------------------------------------------------------------------
//CreateResourceObject
//---------------------------------------------------------------------------------------

template<class T>
T* CResourceManager::CreateResourceObject(const hash _hash) {
	PRINT("CResourceManager::CreateResourceObject() T not Supported\n");
	return nullptr;
}

template<>
CMesh* CResourceManager::CreateResourceObject(const hash _hash) {
	CMesh* ret = CResourceManager::CreateMesh();
	s_instance->m_meshList.PushBack(ret);
	ret->SetHash(_hash);
	return ret;
}

template<>
CShader* CResourceManager::CreateResourceObject(const hash _hash) {
	CShader* ret = CResourceManager::CreateShader();
	s_instance->m_shaderList.PushBack(ret);
	ret->SetHash(_hash);
	return ret;
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
