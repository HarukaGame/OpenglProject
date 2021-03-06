#include "scene.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "debug_print.h"
#include "gameobject.h"

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "texture_loader.h"
#include "resource_manager.h"
#include "vertexfiles/cube.h"
#include "vertexfiles/quad.h"
#include "vertexfiles/ui.h"
#include "vertexfiles/quad_index.h"
#include "vertexfiles/font_mesh.h"
#include "fileloader.h"
#include "object_manager.h"

#include <random>
#include "bmp_analyzer.h"


#include "scene_manager.h"

#include "text_object.h"

#include <math.h>


bool CScene::Initilize()
{
	m_cube = m_pObjectManager->CreateGameObject(CHash::CRC32("TestCube"));
	const CMesh* mesh = SearchOrCreateMesh(CHash::CRC32("CubeMesh"));
	const CShader* shader = SearchOrCreateShader(CHash::CRC32("TextureShader"));
	const CTexture* texture = SearchOrCreateTexture(CHash::CRC32("BlockTexture"), CHash::CRC32("BlockNormalTexture"));

	m_cube->SetMesh(mesh);
	m_cube->SetShader(shader);
	m_cube->SetTexture(texture);
	m_cube->SetPosition(0,0,0);

	CGameObject* secondCube = m_pObjectManager->CreateGameObject(CHash::CRC32("SecondCube"));
	secondCube->SetMesh(SearchOrCreateMesh(CHash::CRC32("CubeMesh")));
	const CShader* secondShader = SearchOrCreateShader(CHash::CRC32("BasicShader"));
	secondCube->SetShader(secondShader);
	secondShader->SetColor(glm::vec3(1, 1, 1));
	secondCube->SetPosition(2, 0, 0);

	CTextObject* textObject = new CTextObject();

	const CMesh* fontMesh = SearchOrCreateMesh(CHash::CRC32("FontMesh"));
	const CShader* fontShader = SearchOrCreateShader(CHash::CRC32("FontShader"));
	const CTexture* fontTexture = SearchOrCreateTexture(CHash::CRC32("FontTexture"));

	textObject->SetUp(m_pObjectManager, fontMesh, fontShader, fontTexture);
	textObject->SetText("ABC",glm::vec2(1,1),glm::vec2(1,1));

	m_textObjectList.PushFront(textObject);

	

	return true;
}

void CScene::Finalize()
{
	CList<CTextObject*>::iterator iter = m_textObjectList.Begin();
	CList<CTextObject*>::iterator end = m_textObjectList.End();
	for (; iter != end; iter++) {
		(*iter)->Finalize();
		delete (*iter);
	}
	m_textObjectList.Clear();
	m_textObjectList.Clear();
	m_textObjectList.~CList();

	m_pObjectManager->AllObjectDelete();
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


#ifdef _DEBUG
	const float rotetaSpeed = 0.05f;
	const float moveSpeed = 0.1f;

	if (Input::GetKey(VK_SHIFT)&&Input::GetKey('I')) {
		m_cube->Rotate(-rotetaSpeed, 0.0f, 0.0f);
	}
	if (Input::GetKey(VK_SHIFT) && Input::GetKey('K')) {
		m_cube->Rotate(rotetaSpeed, 0.0f, 0.0f);
	}
	if (Input::GetKey(VK_SHIFT) && Input::GetKey('J')) {
		m_cube->Rotate(0.0f, -rotetaSpeed, 0.0f);
	}
	if (Input::GetKey(VK_SHIFT) && Input::GetKey('L')) {
		m_cube->Rotate(0.0f, rotetaSpeed, 0.0f);
	}


	if (Input::GetKey(VK_CONTROL)&&Input::GetKey('I')) {
		m_cube->Move(0,moveSpeed,0);
	}
	if (Input::GetKey(VK_CONTROL) && Input::GetKey('K')) {
		m_cube->Move(0,-moveSpeed,0);
	}
	if (Input::GetKey(VK_CONTROL) && Input::GetKey('J')) {
		m_cube->Move(-moveSpeed,0,0);
	}
	if (Input::GetKey(VK_CONTROL) && Input::GetKey('L')) {
		m_cube->Move(moveSpeed,0,0);
	}
	if (Input::GetKey(VK_CONTROL) && Input::GetKey('U')) {
		m_cube->Move(0,0,moveSpeed);
	}
	if (Input::GetKey(VK_CONTROL) && Input::GetKey('O')) {
		m_cube->Move(0, 0, -moveSpeed);
	}

	if (Input::GetKey(VK_SPACE)) {
		m_cube->RotateAxis(glm::vec3(1, 0, 1), 1);
	}


	if (Input::GetKey('6')) {
		m_trans -= 0.01f;
		if (m_trans < 0.0) { m_trans = 0.0f; }
		else if (m_trans > 1.0f) { m_trans = 1.0f; }
	}
	if (Input::GetKey('7')) {
		m_trans += 0.01f;
		if (m_trans < 0.0) { m_trans = 0.0f; }
		else if (m_trans > 1.0f) { m_trans = 1.0f; }

	}

	const CShader* shader= CResourceManager::SearchResourceObject<CShader>(CHash::CRC32("TransShader"));
	if (shader != nullptr) {
		shader->SetRatio(m_trans);
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
	else if (_hash == CHash::CRC32("UIMesh")) {
		mesh->myvertices = PolygonUI::verticex;
		mesh->m_normals = PolygonUI::normals;
		mesh->vertexNum = PolygonUI::vertexNum;
		mesh->elementNum = PolygonUI::elementNum;
	}
	else if (_hash == CHash::CRC32("FontMesh")) {
		mesh->myvertices = FontMesh::verticex;
		mesh->m_normals = FontMesh::normals;
		mesh->vertexNum = FontMesh::vertexNum;
		mesh->elementNum = FontMesh::elementNum;
	}
	else if (_hash == CHash::CRC32("IndexMesh")) {
		mesh->myvertices = PolygonQuadIndex::vertices;
		mesh->indeces = PolygonQuadIndex::indeces;
		mesh->vertexNum = PolygonQuadIndex::verticesNum;
		mesh->elementNum = PolygonQuadIndex::elementNum;
		mesh->m_isIndex = true;
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
	else if (_hash == CHash::CRC32("UIShader")) {
		vertFilePath = "game/ShaderFiles/UIShader.vs";
		fragFilePath = "game/ShaderFiles/UIShader.fs";
	}
	else if (_hash == CHash::CRC32("FontShader")) {
		vertFilePath = "game/ShaderFiles/font.vs";
		fragFilePath = "game/ShaderFiles/font.fs";
	}
	else if (_hash == CHash::CRC32("TransShader")) {
		vertFilePath = "game/ShaderFiles/transition.vs";
		fragFilePath = "game/ShaderFiles/transition.fs";
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

	CFileLoader fileloader = CFileLoader();
	if (_hash == CHash::CRC32("Test24Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow24_511.bmp");
	}
	else if (_hash == CHash::CRC32("Test8Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow8.bmp");
	}
	else if (_hash == CHash::CRC32("Test4Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow4.bmp");
	}
	else if (_hash == CHash::CRC32("Test2Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow2_513.bmp");
	}
	else if (_hash == CHash::CRC32("TransTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/rule1080p/114.bmp");
	}
	else if (_hash == CHash::CRC32("BlockTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/block.bmp");
	}
	else if (_hash == CHash::CRC32("BlockNormalTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/block_normal.bmp");
	}
	else if (_hash == CHash::CRC32("FontTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/moji.bmp");
	}

	CTextureConverter textureConverter = CTextureConverter();
	textureConverter.ConvertTexture(fileloader.GetVoidBuffer(), fileloader.GetLength());
	CTexture* texture = CResourceManager::CreateResourceObject<CTexture>(_hash);
	texture->SetTextureBuffer(textureConverter.GetBuffer(), textureConverter.GetWidth(), textureConverter.GetHeight(), textureConverter.GetElementNum());
	texture->CreateBuffer();
	textureConverter.Release();
	fileloader.Release();

	if (texture == nullptr) {
		return nullptr;
	}
	texture->RefCountUp();
	return texture;
}

const CTexture* CScene::SearchOrCreateTexture(const hash _textureHash, const hash _normalHashs)
{
	const CTexture* cTexture = CResourceManager::SearchResourceObject<CTexture>(_textureHash);
	if (cTexture != nullptr) {
		cTexture->RefCountUp();
		return cTexture;
	}

	CFileLoader fileloader = CFileLoader();
	if (_textureHash == CHash::CRC32("Test24Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow24_511.bmp");
	}
	else if (_textureHash == CHash::CRC32("Test8Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow8.bmp");
	}
	else if (_textureHash == CHash::CRC32("Test4Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow4.bmp");
	}
	else if (_textureHash == CHash::CRC32("Test2Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow2_513.bmp");
	}
	else if (_textureHash == CHash::CRC32("TransTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/rule1080p/114.bmp");
	}
	else if (_textureHash == CHash::CRC32("BlockTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/block.bmp");
	}
	else if (_textureHash == CHash::CRC32("BlockNormalTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/block_normal.bmp");
	}
	CTextureConverter textureConverter = CTextureConverter();
	textureConverter.ConvertTexture(fileloader.GetVoidBuffer(), fileloader.GetLength());
	CTexture* texture = CResourceManager::CreateResourceObject<CTexture>(_textureHash);
	texture->SetTextureBuffer(textureConverter.GetBuffer(), textureConverter.GetWidth(), textureConverter.GetHeight(), textureConverter.GetElementNum());
	texture->CreateBuffer();
	textureConverter.Release();
	fileloader.Release();


	if (_normalHashs == CHash::CRC32("Test24Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow24_511.bmp");
	}
	else if (_normalHashs == CHash::CRC32("Test8Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow8.bmp");
	}
	else if (_normalHashs == CHash::CRC32("Test4Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow4.bmp");
	}
	else if (_normalHashs == CHash::CRC32("Test2Texture")) {
		fileloader.LoadFile("game/res/bmpfiles/rainbow2_513.bmp");
	}
	else if (_normalHashs == CHash::CRC32("TransTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/rule1080p/114.bmp");
	}
	else if (_normalHashs == CHash::CRC32("BlockTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/block.bmp");
	}
	else if (_normalHashs == CHash::CRC32("BlockNormalTexture")) {
		fileloader.LoadFile("game/res/bmpfiles/block_normal.bmp");
	}
	textureConverter.ConvertTexture(fileloader.GetVoidBuffer(), fileloader.GetLength());
	texture->SetNormalBuffer(textureConverter.GetBuffer(), textureConverter.GetWidth(), textureConverter.GetHeight(), textureConverter.GetElementNum());
	texture->CreateNormalBuffer();
	textureConverter.Release();
	fileloader.Release();

	if (texture == nullptr) {
		return nullptr;
	}
	texture->RefCountUp();
	return texture;
}
