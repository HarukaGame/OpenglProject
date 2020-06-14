#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

class CObjectManager;
class CScene {
public:
	bool Initilize(CObjectManager* _objectManager);
	void Update();
private:
	CObjectManager* m_pObjectManager = nullptr;
};

#endif // !__SCENE_H__
