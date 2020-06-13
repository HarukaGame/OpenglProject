#include "gameobject.h"

void CGameObject::SetShader(CShader* _shader)
{
	m_pShader = _shader;
}

void CGameObject::SetMesh(CMesh* _mesh)
{
	m_pMesh = _mesh;
}

CShader* CGameObject::GetShader() const
{
	return m_pShader;
}

CMesh* CGameObject::GetMesh() const
{
	return m_pMesh;
}
