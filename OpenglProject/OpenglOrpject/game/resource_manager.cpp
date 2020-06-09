#include "resource_manager.h"
#include "Mesh.h"
#include "shader.h"
#include "fileloader.h"
#include "shader_loader.h"

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
	return nullptr;
}
