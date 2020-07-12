#include "gameobject.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "common_math.h"
#include "resource_manager.h"
using namespace GLM_MATH_NAMESPACE;


void CGameObject::SetShader(const CShader* _shader)
{
	m_pShader = _shader;
}

void CGameObject::SetMesh(const CMesh* _mesh)
{
	m_pMesh = _mesh;
}

void CGameObject::SetTexture(const CTexture* _texture)
{
	m_pTexture = _texture;
}

void CGameObject::SetNormalTexture(const CTexture* _normalTexture)
{
	m_pNormal = _normalTexture;
}

const CShader* CGameObject::GetShader() const
{
	return m_pShader;
}

const CMesh* CGameObject::GetMesh() const
{
	return m_pMesh;
}

const CTexture* CGameObject::GetTexture() const
{
	return m_pTexture;
}

const CTexture* CGameObject::GetNormalTexture() const
{
	return m_pNormal;
}

void CGameObject::SetPosition(const float _x, const float _y, const float _z)
{
	m_position = glm::vec3(_x, _y, _z);
	ReCalculateTrans();
}

void CGameObject::SetRotate(const float _x, const float _y, const float _z)
{
	m_rotation = glm::vec3(_x, _y, _z);
	ReCalculateTrans();
}

void CGameObject::SetScale(const float _x, const float _y, const float _z)
{
	m_scale = glm::vec3(_x, _y, _z);
	ReCalculateTrans();
}

void CGameObject::Rotate(const float _x, const float _y, const float _z)
{
	m_trans = m_trans * GlmMath::Rotate(glm::vec3(_x,_y, _z));
}

void CGameObject::Move(const float _x, const float _y, const float _z)
{
	m_trans = GlmMath::Trans(glm::vec3(_x, _y, _z)) * m_trans;
}

glm::vec3 CGameObject::GetPosition() const
{
	return glm::vec3(m_trans[0][3], m_trans[1][3], m_trans[2][3]);
	//return m_position;;
}

glm::mat4 CGameObject::GetTransMat()
{
	//if (m_moved == true) {
	//	ReCalculateTrans();
	//}
	return m_trans;
}

void CGameObject::RotateAxis(glm::vec3 _axis, float _angle)
{
	glm::vec3 tempAxis = glm::vec3(0,1,0);
		
	if (glm::length(_axis) != 0) {
		tempAxis = glm::normalize(_axis);
	}
	float x = _axis.x;
	float y = _axis.y;
	float z = _axis.z;
	float ang = deg_to_rad(_angle);
	float COS = cosf(ang);
	float SIN = sinf(ang);
	float COSA = 1 - COS;
	glm::mat4 rot = glm::mat4();
	rot[0][0] = COS + x * x * COSA;
	rot[0][1] = x * y * COSA - z * SIN;
	rot[0][2] = z * x * COSA + y * SIN;

	rot[1][0] = x * y * COSA + z * SIN;
	rot[1][1] = COS + y * y * COSA;
	rot[1][2] = y * z * COSA - x * SIN;

	rot[2][0] = z * x * COSA - y * SIN;
	rot[2][1] = y * z * COSA + x * SIN;
	rot[2][2] = COS + z * z * COSA;

	rot[0][3] = 0;
	rot[1][3] = 0;
	rot[2][3] = 0;
	rot[3][0] = 0;
	rot[3][1] = 0;
	rot[3][2] = 0;
	rot[3][3] = 1;


	m_trans = rot * m_trans;
	//m_position = rot * m_position;

	//glm::mat3 tempModel = glm::mat3();
	//tempModel[0] = m_trans[0];
	//tempModel[1] = m_trans[1];
	//tempModel[2] = m_trans[2];
	//tempModel[0][0] = 1;
	//tempModel[1][1] = 1;
	//tempModel[2][2] = 1;
	//tempModel = glm::transpose(tempModel);

	//m_rotation.x += dot(tempModel * glm::vec3(1, 0, 0), tempAxis) * ang;
	//m_rotation.y += dot(tempModel * glm::vec3(0, 1, 0), tempAxis) * ang;
	//m_rotation.z += dot(tempModel * glm::vec3(0, 0, 1), tempAxis) * ang;

	//printf("%f\n", m_rotation.x);

	//m_moved = true;

}

void CGameObject::SetHash(const hash _hash)
{
	m_hash = _hash;
}

hash CGameObject::GetHash() const
{
	return m_hash;
}

void CGameObject::Finalize()
{
	if (m_pMesh != nullptr) {
		m_pMesh->RefCountDown();
		if (m_pMesh->RefCountZero()) {
			CResourceManager::DeleteMeshResource(m_pMesh);
		}
	}

	if (m_pShader != nullptr) {
		m_pShader->RefCountDown();
		if (m_pShader->RefCountZero()) {
			CResourceManager::DeleteShaderResource(m_pShader);
		}
	}
	if (m_pTexture != nullptr) {
		m_pTexture->RefCountDown();
		if (m_pTexture->RefCountZero()) {
			CResourceManager::DeleteTextureResource(m_pTexture);
		}
	}
}

void CGameObject::ReCalculateTrans()
{
	m_trans = GlmMath::Trans(m_position) * GlmMath::Rotate(m_rotation) * GlmMath::Scale(m_scale);
}
