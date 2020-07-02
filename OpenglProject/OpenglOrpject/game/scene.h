#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include "scene_base.h"

class CObjectManager;
class CShader;
class CMesh;
class CTexture;

#include "hash.h"
class CScene :public CSceneBase{
public:
	bool Initilize()override { return true; };
	void Finalize()override;

	void SetObjectManager(CObjectManager* _objectManager) { m_pObjectManager = _objectManager; };
	void Update();

	const CMesh* SearchOrCreateMesh(const hash _hash);
	const CShader* SearchOrCreateShader(const hash _hash);
	const CTexture* SearchOrCreateTexture(const hash _hash);
private:
	CObjectManager* m_pObjectManager = nullptr;
	float m_trans = 1.0f;
};

#endif // !__SCENE_H__
