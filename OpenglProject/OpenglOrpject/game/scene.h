#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include "my_list.h"
#include "scene_base.h"

class CObjectManager;
class CGameObject;
class CShader;
class CMesh;
class CTexture;
class CTextObject;

#include "hash.h"
class CScene :public CSceneBase{
public:
	bool Initilize()override;
	void Finalize()override;

	void SetObjectManager(CObjectManager* _objectManager) { m_pObjectManager = _objectManager; };
	void Update();

	const CMesh* SearchOrCreateMesh(const hash _hash);
	const CShader* SearchOrCreateShader(const hash _hash);
	const CTexture* SearchOrCreateTexture(const hash _hash);
	const CTexture* SearchOrCreateTexture(const hash _textureHash, const hash _normalHashs);;
private:
	CObjectManager* m_pObjectManager = nullptr;
	float m_trans = 1.0f;
	CGameObject* m_cube = nullptr;
	CList<CTextObject*> m_textObjectList = CList<CTextObject*>();
};

#endif // !__SCENE_H__
