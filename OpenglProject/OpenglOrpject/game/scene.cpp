#include "scene.h"
#include "camera.h"
#include "light.h"
#include "input.h"
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
}
