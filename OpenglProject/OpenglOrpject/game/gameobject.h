#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include "hash.h"
#include "glm/matrix.hpp"

class CShader;
class CMesh;
class CTexture;
class CGameObject {
public:
	void SetShader(const CShader* _shader);
	void SetMesh(const CMesh* _mesh);
	void SetTexture(const CTexture* _texture);
	void SetNormalTexture(const CTexture* _normalTexture);
	const CShader* GetShader()const;
	const CMesh* GetMesh()const;
	const CTexture* GetTexture()const;
	const CTexture* GetNormalTexture()const;
	void SetPosition(const float _x,const float _y,const float _z);
	void SetRotate(const float _x, const float _y, const float _z);
	void SetScale(const float _x, const float _y, const float _z);
	void Rotate(const float _x, const float _y, const float _z);
	void Move(const float _x, const float _y, const float _z);
	glm::vec3 GetPosition()const;
	glm::mat4 GetTransMat();

	void SetAddUV(const glm::vec3& _add) { m_addUV = _add; };
	const glm::vec3& GetAddUV()const { return m_addUV; };

	void RotateAxis(glm::vec3 _axis, float _angle);

	void SetHash(const hash _hash);
	hash GetHash()const;
	void Finalize();
	float distance = 0;
private:
	void ReCalculateTrans();

	const CMesh* m_pMesh = nullptr;
	const CShader* m_pShader = nullptr;
	const CTexture* m_pTexture = nullptr;
	const CTexture* m_pNormal = nullptr;
	hash m_hash = 0;

	glm::vec3 m_position = glm::vec3(0, 0, 0);
	glm::vec3 m_rotation = glm::vec3(0, 0, 0);
	glm::vec3 m_scale = glm::vec3(1, 1, 1);
	glm::mat4 m_trans = glm::mat4();
	glm::vec3 m_addUV = glm::vec3(0, 0,0);
	bool m_moved = true;
};
#endif // !__GAMEOBJECT_H__
