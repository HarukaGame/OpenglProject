#pragma once
#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__
#include "my_list.h"
class CMesh;
class CShader;
class CResourceBase;

class CResourceManager {
public:
	static bool CreateInstance();
	static void Destroy();
	static CShader* CreateShader();
	static CMesh* CreateMesh();
	template<class T>static T* CreateResourceObject();
private:
	static CResourceManager* s_instance;
	CList<CMesh*> m_meshList = CList<CMesh*>();
	CList<CShader*>m_shaderList = CList<CShader*>();
};
#endif // !__RESOURCE_MANAGER_H__

