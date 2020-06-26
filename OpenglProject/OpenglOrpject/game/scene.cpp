#include "scene.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "debug_print.h"
#include "gameobject.h"

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "resource_manager.h"
#include "vertexfiles/cube.h"
#include "vertexfiles/quad.h"
#include "fileloader.h"
#include "object_manager.h"

#include <random>
#include "bmp_analyzer.h"

bool CScene::Initilize(CObjectManager* _objectManager)
{
	m_pObjectManager = _objectManager;
	if (m_pObjectManager == nullptr) {
		PRINT("CScene::Initilize _objectManager is nullptr\n");
		return false;
	}

	//BITMAP_FORMAT bitmap;
	//CFileLoader fileloader = CFileLoader();
	//fileloader.LoadFile("game/res/bmpfiles/test.bmp");
	//CBmpAnalyzer::AnalyzeBitMap(fileloader.GetVoidBuffer(), fileloader.GetLength(), bitmap);
	//CBmpAnalyzer::ShowBitMapInfo(bitmap);
	//fileloader.Release();

	return true;
}

void CScene::Update()
{
	if (Input::GetKey('A')) {
		CCamera::GetInstance()->Rotate(0, -3.0f);
	}
	if (Input::GetKey('D')) {
		CCamera::GetInstance()->Rotate(0, 3.0f);
	}
	if (Input::GetKey('W')) {
		CCamera::GetInstance()->Rotate(3.0f, 0);
	}
	if (Input::GetKey('S')) {
		CCamera::GetInstance()->Rotate(-3.0f, 0);
	}
	if (Input::GetKey('Q')) {
		CCamera::GetInstance()->Zoom(0.1f);
	}
	if (Input::GetKey('E')) {
		CCamera::GetInstance()->Zoom(-0.1f);
	}

	if (Input::GetKey(VK_UP)) {
		CLight::GetInstance()->Rotate(2.0f,0);
	}
	if (Input::GetKey(VK_DOWN)) {
		CLight::GetInstance()->Rotate(-2.0f,0);
	}
	if (Input::GetKey(VK_RIGHT)) {
		CLight::GetInstance()->Rotate(0,2.0f);
	}
	if (Input::GetKey(VK_LEFT)) {
		CLight::GetInstance()->Rotate(0,-2.0f);
	}

	if (Input::GetKeyDown('U')) {
		CGameObject* temp = m_pObjectManager->SearchGameObject(CHash::CRC32("TestCube"));
		int a = 0;
	}
	if (Input::GetKey('3')) {
		m_pObjectManager->DeleteObject(CHash::CRC32("TestCube"));
	}
	//if (Input::GetKeyDown('1')) {
	//	for (int i = 0; i < 10; i++) {
	//		float range = 10.0f;
	//		float x = fmod(rand() / 100.0f, range) - range / 2.0f;
	//		float y = fmod(rand() / 100.0f, range) - range / 2.0f;
	//		float z = fmod(rand() / 100.0f, range) - range / 2.0f;
	//		CGameObject* tempObject =  m_pObjectManager->CreateGameObject(CHash::CRC32("TestCube"));
	//		const CMesh* mesh = SearchOrCreateMesh(CHash::CRC32("CubeMesh"));
	//		const CShader* shader = SearchOrCreateShader(CHash::CRC32("TransparentShader"));
	//		tempObject->SetMesh(mesh);
	//		tempObject->SetShader(shader);
	//		tempObject->SetPosition(x, y, z);

	//	}


	//}
	if (Input::GetKeyDown('2')) {
		for (int i = 0; i < 10; i++) {
			float range = 10.0f;
			float x = fmod(rand() / 100.0f, range) - range / 2.0f;
			float y = fmod(rand() / 100.0f, range) - range / 2.0f;
			float z = fmod(rand() / 100.0f, range) - range / 2.0f;
			CGameObject* tempObject =  m_pObjectManager->CreateGameObject(CHash::CRC32("TestCube"));
			const CMesh* mesh = SearchOrCreateMesh(CHash::CRC32("QuadMesh"));
			const CShader* shader = SearchOrCreateShader(CHash::CRC32("TextureShader"));
			const CTexture* texture = SearchOrCreateTexture(CHash::CRC32("TestTexture"));
			//const CShader* shader = SearchOrCreateShader(CHash::CRC32("BasicShader"));
			tempObject->SetMesh(mesh);
			tempObject->SetShader(shader);
			tempObject->SetTexture(texture);
			tempObject->SetPosition(x, y, z);

		}


	}

#ifdef _DEBUG
	if (Input::GetKeyDown('4')) {
		m_pObjectManager->DebugShow();
	}

#endif // _DEBUG

}





const CMesh* CScene::SearchOrCreateMesh(const hash _hash)
{
	const CMesh* cMesh = CResourceManager::SearchResourceObject<CMesh>(_hash);
	if (cMesh != nullptr) {
		cMesh->RefCountUp();
		return cMesh;
	}

	CMesh* mesh = CResourceManager::CreateResourceObject<CMesh>(_hash);
	if (mesh == nullptr) {
		return nullptr;
	}
	mesh->RefCountUp();
	if (_hash == CHash::CRC32("CubeMesh")) {
		mesh->myvertices = PolygonCube::verticex;
		mesh->m_normals = PolygonCube::normals;
		mesh->vertexNum = PolygonCube::vertexNum;
		mesh->elementNum = PolygonCube::elementNum;
	}
	else if (_hash == CHash::CRC32("QuadMesh")) {
		mesh->myvertices = PolygonQuad::verticex;
		mesh->m_normals = PolygonQuad::normals;
		mesh->vertexNum = PolygonQuad::vertexNum;
		mesh->elementNum = PolygonQuad::elementNum;
	}
	else {
		return nullptr;
	}

	mesh->CreateBuffer();
	return mesh;
}

const CShader* CScene::SearchOrCreateShader(const hash _hash)
{
	const CShader* cShader = CResourceManager::SearchResourceObject<CShader>(_hash);
	if (cShader != nullptr) {
		cShader->RefCountUp();
		return cShader;
	}

	CShader* shader = CResourceManager::CreateResourceObject<CShader>(_hash);
	if (shader == nullptr) {
		return nullptr;
	}
	shader->RefCountUp();
	
	const char* vertFilePath = "";
	const char* fragFilePath = "";
	if (_hash == CHash::CRC32("BasicShader")) {
		vertFilePath = "game/ShaderFiles/basic.vs";
		fragFilePath = "game/ShaderFiles/basic.fs";
	}
	else if (_hash == CHash::CRC32("TransparentShader")) {
		vertFilePath = "game/ShaderFiles/Transparent.vs";
		fragFilePath = "game/ShaderFiles/Transparent.fs";
		shader->SetTransparent(true);
	}
	else if (_hash == CHash::CRC32("TextureShader")) {
		vertFilePath = "game/ShaderFiles/texture.vs";
		fragFilePath = "game/ShaderFiles/texture.fs";
	}
	else {
		return nullptr;
	}

	CFileLoader vertFile = CFileLoader();
	CFileLoader fragFile = CFileLoader();
	vertFile.LoadFile(vertFilePath);
	fragFile.LoadFile(fragFilePath);
	shader->CreateShaderProgram(vertFile.GetBuffer(), vertFile.GetLength(), fragFile.GetBuffer(), fragFile.GetLength());
	vertFile.Release();
	fragFile.Release();

	return shader;
}

const CTexture* CScene::SearchOrCreateTexture(const hash _hash)
{
	const CTexture* cTexture = CResourceManager::SearchResourceObject<CTexture>(_hash);
	if (cTexture != nullptr) {
		cTexture->RefCountUp();
		return cTexture;
	}

	CTexture* texture = CResourceManager::CreateResourceObject<CTexture>(_hash);
	if (texture == nullptr) {
		return nullptr;
	}
	texture->RefCountUp();

	texture->CreateBuffer();

	return texture;
}
