#pragma once
#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

class CObjectManager;


class CSceneBase {
public:
	virtual bool Initilize(CObjectManager* _objectManager) = 0;
	virtual void Update() = 0;
	virtual void Finalize() = 0;
protected:
	CObjectManager* m_pObjectManager = nullptr;

};

#endif // !__SCENE_BASE_H__
