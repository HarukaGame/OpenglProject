#include "scene_manager.h"
#include "scene_base.h"
#include "scene.h"
#include "debug_print.h"

CSceneManager CSceneManager::s_instance;

CSceneManager& CSceneManager::GetInstance()
{
	return s_instance;
}
void CSceneManager::LoadScene(hash _sceneID)
{
	CSceneBase* sceneBase = nullptr;
	if (_sceneID == CHash::CRC32("MainScene")) {
		CScene* newScene = new CScene();
		newScene->Initilize();
		newScene->SetID(_sceneID);
		newScene->SetObjectManager(m_objectManager);
		sceneBase = newScene;
	}
	else {
		return;
	}
	m_pLoadedSceneList.PushBack(sceneBase);
	m_currentState = SCENE_RESET;
}
bool CSceneManager::Initilize(CObjectManager* _objectManager)
{
	if (_objectManager == nullptr) {
		PRINT("CSceneManager::Initilize _objectManager is nullptr\n");
		return false;
	}
	m_objectManager = _objectManager;
	return true;
}

void CSceneManager::Update() {
	if (m_currentState == SCENE_INITILIZE) {
		m_currentState = SCENE_UPDATE;
	}
	else if (m_currentState == SCENE_RESET) {
		ResetScene();
		m_currentState = SCENE_UPDATE;
	}
	else if (m_currentState == SCENE_UPDATE) {
		CList<CSceneBase*>::iterator iter = m_pCurrentSceneList.Begin();
		CList<CSceneBase*>::iterator end = m_pCurrentSceneList.End();
		for (; iter != end; iter++) {
			(*iter)->Update();
		}
	}
	else if (m_currentState == SCENE_FINALIZE) {

	}

}

void CSceneManager::Finalize()
{
	FinalizeAllScene();
}

const CSceneBase* CSceneManager::SearchScene(const hash _id)
{
	CList<CSceneBase*>::iterator iter = m_pCurrentSceneList.Begin();
	CList<CSceneBase*>::iterator end = m_pCurrentSceneList.End();
	for (; iter != end; iter++) {
		if ((*iter) == nullptr) {
			continue;
		}
		if (_id == (*iter)->GetID()) {
			return (*iter);
		}
	}
	return nullptr;
}

void CSceneManager::ResetScene()
{
	FinalizeAllScene();
	CList<CSceneBase*>::iterator iter = m_pLoadedSceneList.Begin();
	CList<CSceneBase*>::iterator end = m_pLoadedSceneList.End();
	for (; iter != end; iter++) {
		m_pCurrentSceneList.PushBack(*iter);
	}
	m_pLoadedSceneList.Clear();
}

void CSceneManager::FinalizeAllScene()
{
	CList<CSceneBase*>::iterator iter = m_pCurrentSceneList.Begin();
	CList<CSceneBase*>::iterator end = m_pCurrentSceneList.End();
	for (; iter != end; iter++) {
		(*iter)->Finalize();
		delete (*iter);
	}
	m_pCurrentSceneList.Clear();
}
