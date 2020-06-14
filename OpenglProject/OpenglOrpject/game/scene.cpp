#include "scene.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "debug_print.h"
#include "gameobject.h"

#include "mesh.h"
#include "resource_manager.h"
#include "object_manager.h"

bool CScene::Initilize(CObjectManager* _objectManager)
{
	m_pObjectManager = _objectManager;
	if (m_pObjectManager == nullptr) {
		PRINT("CScene::Initilize _objectManager is nullptr\n");
		return false;
	}
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
	if (Input::GetKeyDown('I')) {
		m_pObjectManager->DeleteObject(CHash::CRC32("TestCube"));
		int a = 0;

	}
	if (Input::GetKeyDown('O')) {
		m_pObjectManager->CreateGameObject(CHash::CRC32("TestCube"));
		int a = 0;

	}
}
