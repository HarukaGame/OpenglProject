#pragma once
#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__
#include "my_list.h"
#include "hash.h"

class CSceneBase;
class CObjectManager;

enum SCENE_STATE {
	SCENE_INITILIZE,
	SCENE_RESET,
	SCENE_UPDATE,
	SCENE_FINALIZE
};

class CSceneManager {
public:
	static CSceneManager& GetInstance();
	void LoadScene(hash _sceneID);
	bool Initilize(CObjectManager* _objectManager);
	void Update();
	void Finalize();
	const CSceneBase* SearchScene(const hash _id);
private:
	CSceneManager(){};
	~CSceneManager() {};
	CSceneManager(const CSceneManager&) = delete;
	CSceneManager(CSceneManager&&) = delete;
	CSceneManager& operator=(const CSceneManager&) = delete;
	CSceneManager& operator=(CSceneManager&&) = delete;

	void ResetScene();
	void FinalizeAllScene();

	static CSceneManager s_instance;
	CList<CSceneBase*> m_pCurrentSceneList = CList<CSceneBase*>();
	CList<CSceneBase*> m_pLoadedSceneList = CList<CSceneBase*>();

	CObjectManager* m_objectManager = nullptr;

	SCENE_STATE m_currentState = SCENE_INITILIZE;
};

#endif // !__SCENE_MANAGER_H__
