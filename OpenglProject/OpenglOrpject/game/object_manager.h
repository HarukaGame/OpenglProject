#pragma once
#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include "my_list.h"

class CGameObject;
class CRenderer;

class CObjectManager {
public:
	void AllObjectDraw(CRenderer* _renderer);
private:
	CList<CGameObject*> m_gameObjectList;
};
#endif // !__OBJECT_MANAGER_H__
