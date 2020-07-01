#pragma once
#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__
#include "hash.h"

class CObjectManager;


class CSceneBase {
public:
	virtual bool Initilize() = 0;
	virtual void Update() = 0;
	virtual void Finalize() = 0;

	void SetID(const hash _id) { m_sceneID = _id; };
	hash GetID()const { return m_sceneID; };
protected:
	hash m_sceneID = hash();
};

#endif // !__SCENE_BASE_H__
