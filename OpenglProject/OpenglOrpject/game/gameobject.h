#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class CShader;
class CMesh;

class CGameObject {
public:
	void SetShader(const CShader* _shader);
	void SetMesh(const CMesh* _mesh);
	const CShader* GetShader()const;
	const CMesh* GetMesh()const;
private:
	const CMesh* m_pMesh = nullptr;
	const CShader* m_pShader = nullptr;
};
#endif // !__GAMEOBJECT_H__
