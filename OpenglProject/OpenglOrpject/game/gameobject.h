#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class CShader;
class CMesh;

class CGameObject {
public:
	void SetShader(CShader* _shader);
	void SetMesh(CMesh* _mesh);
	CShader* GetShader()const;
	CMesh* GetMesh()const;
	void Finalize();
private:
	CMesh* m_pMesh = nullptr;
	CShader* m_pShader = nullptr;
};
#endif // !__GAMEOBJECT_H__
