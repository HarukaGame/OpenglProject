#pragma once
#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

class CMesh;
class CShader;

class CResourceManager {
public:
	static bool CreateInstance();
	static void Destroy();
	static CShader* CreateShader();
	static CMesh* CreateMesh();
private:
	static CResourceManager* s_instance;
};
#endif // !__RESOURCE_MANAGER_H__
