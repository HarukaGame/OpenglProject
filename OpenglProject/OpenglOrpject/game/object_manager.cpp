#include "object_manager.h"
#include "gameobject.h"
#include "resource_manager.h"
#include "renderer.h"

#include "shader.h"
#include "buffer.h"
#include "mesh.h"

#include "camera.h"
#include "light.h"

#include "hash.h"

#include "debug_print.h"

bool CObjectManager::Initilize()
{
	if (CCamera::CreateInstance(800, 600) == false) {
		return false;
	}

	CCamera::GetInstance()->SetTargetPosition(glm::vec3(0, 0, 0));

	if (CLight::CreateInstance() == false) {
		return false;
	}

	CLight::GetInstance()->SetRotate(0, 0);
	return true;
}

void CObjectManager::Finalize()
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	while (m_gameObjectList.Empty() == false) {
		DeleteObject((*iter)->GetHash());
		iter = m_gameObjectList.Begin();
	}

	CCamera::Destroy();
	CLight::Destory();
}

void CObjectManager::AllObjectDraw(CRenderer* _renderer)
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	for (; iter != m_gameObjectList.End(); iter++) {
		const CShader* shader = (*iter)->GetShader();
		if ((*iter)->GetMesh() == nullptr) {
			PRINT("CObjectManager::AllObjectDraw GetMesh() is nullptr\n");
			continue;
		}
		CBuffer* buffer = (*iter)->GetMesh()->GetBuffer();
		glm::mat4 model = (*iter)->GetTransMat();
		_renderer->MeshDraw(buffer, shader, model);
	}
}

CGameObject* CObjectManager::CreateGameObject()
{
	CGameObject* tempObject = new CGameObject();
	//CMesh* mesh = CResourceManager::SearchOrCreateResourceObject<CMesh>(CHash::CRC32("TestMesh"));
	//CShader* shader = CResourceManager::SearchOrCreateResourceObject<CShader>(CHash::CRC32("TestShader"));
	//tempObject->SetMesh(mesh);
	//tempObject->SetShader(shader);
	m_gameObjectList.PushBack(tempObject);
	return tempObject;
}

CGameObject* CObjectManager::CreateGameObject(const hash _hash)
{
	CGameObject* temp = CreateGameObject();
	temp->SetHash(_hash);
	return temp;
}

CGameObject* CObjectManager::SearchGameObject(const hash _hash)
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	return SearchGameObject(_hash, iter);
}

CGameObject* CObjectManager::SearchGameObject(const hash _hash, CList<CGameObject*>::iterator& _iter)
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	CList<CGameObject*>::iterator end = m_gameObjectList.End();
	for (; iter != end; iter++) {
		if ((*iter)->GetHash() == _hash) {
			_iter = iter;
			return (*iter);
		}
	}
	return nullptr;
}

void CObjectManager::ZSort(const glm::vec3& _cameraPos)
{
	//���X�g�T�C�Y��2�ȏ�̂Ƃ��̂ݎ��s
	if (m_gameObjectList.Length() < 2) {
		return;
	}

	//��{�ƂȂ�C�e���[�^�[
	CList<CGameObject*>::iterator baseIter = m_gameObjectList.Begin();
	//End�C�e���[�^�[
	CList<CGameObject*>::iterator end = m_gameObjectList.End();

	//�I�u�W�F�N�g���ꂼ��ɃJ�����Ƃ̋�����o�^
	for (; baseIter != end; baseIter++) {
		(*baseIter)->distance = glm::length((*baseIter)->GetPosition() - _cameraPos);
	}

	//�X�^�[�g�̃C�e���[�^�[
	CList<CGameObject*>::iterator begin = m_gameObjectList.Begin();
	baseIter = m_gameObjectList.End() - 1;

	//2�Ԗڂ̍��ڂ���@���ׂ�
	baseIter = end -2;
	//�}���\�[�g�ő}���ꏊ�����߂�C�e���[�^
	CList<CGameObject*>::iterator insert = end - 2;
	for (; baseIter != begin-1; baseIter--) {
		if ((*baseIter)->GetShader() == nullptr) {
			continue;
		}
		if ((*baseIter)->GetShader()->GetTransparent() == false) {
			continue;
		}
		////[i-1]�Ԗ� >= [i]�ԖڂȂ烋�[�v�𑱂���
		//if ((*baseIter)->distance > (*(baseIter+1))->distance){
		//	continue;
		//}

		//[i - 1]�Ԗ� < [i]�ԖڂƂȂ��Ă�����
		//�}���ꏊ��T������A���̂Ƃ�baseIter�͈ړ�������ׂ����ڂƂȂ�
		insert = baseIter+1;
		for (; insert != end; insert++) {
			if ((*insert)->GetShader()->GetTransparent() == false){
				continue;
			}
			if ((*baseIter)->distance > (*insert)->distance) {
				break;
			}
		}

		//�T�������}���ꏊ��baseIter������
		m_gameObjectList.Insert((*baseIter),insert-1);

		//baseIter�̍��ڂ�Pop�����baseIter��next���Q�Ƃł��Ȃ��Ȃ�̂ŁA
		//baseIter--�ŉ����Ă���AbaseIter+1��Pop���AbaseIter��next���Q�Ƃł���悤�ɕۂ�
		baseIter++;
		m_gameObjectList.Pop(baseIter-1);

		//���X�g�̈�ԏ��߂�����ւ���Ă���\��������̂ŁA�X�V����
		end = m_gameObjectList.End();
		begin = m_gameObjectList.Begin();
	}
}

void CObjectManager::DeleteObject(const hash _hash)
{
	CList<CGameObject*>::iterator iter = m_gameObjectList.Begin();
	CGameObject* temp = SearchGameObject(_hash, iter);
	if (temp == nullptr) {
		return;
	}
	
	temp->Finalize();
	delete temp;
	m_gameObjectList.Pop(iter);
}

void CObjectManager::DebugShow()
{
	PRINT("----------------------------------------------------\n");
	CList<CGameObject*>::iterator printIter = m_gameObjectList.Begin();
	CList<CGameObject*>::iterator printEnd = m_gameObjectList.End();
	for (; printIter != printEnd; printIter++) {
		PRINT2("gameobject[%f]		", (*printIter)->distance);
		if ((*printIter)->GetShader()->GetTransparent() == true) {
			PRINT("true\n");
		}
		else {
			PRINT("false\n");
		}
	}
	PRINT("----------------------------------------------------\n");
}
