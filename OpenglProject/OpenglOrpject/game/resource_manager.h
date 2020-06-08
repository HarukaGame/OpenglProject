#pragma once
#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

class CMesh;
class CShader;

class CResourceManager {
public:
	CShader* CreateShader();
	CMesh* CreateMesh();
};
#endif // !__RESOURCE_MANAGER_H__
