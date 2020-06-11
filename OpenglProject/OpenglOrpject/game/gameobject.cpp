#include "gameobject.h"

void CGameObject::SetShader(const CShader* _shader)
{
	m_pShader = _shader;
}

void CGameObject::SetMesh(const CMesh* _mesh)
{
	m_pMesh = _mesh;
}

const CShader* CGameObject::GetShader() const
{
	return m_pShader;
}

const CMesh* CGameObject::GetMesh() const
{
	return m_pMesh;
}
