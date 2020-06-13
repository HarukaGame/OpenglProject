#pragma once
#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include "my_list.h"

class CGameObject;
class CRenderer;
class CMesh;
class CShader;

class CObjectManager {
public:
	void AllObjectDraw(CRenderer* _renderer);
	CGameObject* CreateGameObject();
private:
	CList<CGameObject*> m_gameObjectList = CList<CGameObject*>();
};
#endif // !__OBJECT_MANAGER_H__
