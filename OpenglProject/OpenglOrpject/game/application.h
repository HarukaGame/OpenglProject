#pragma once

#include <Windows.h>

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

class CWindow;
class COpenglDevice;
class CRenderer;
class CMesh;
//class MSG;

class CApplication {
public:
	bool Initilize(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow);

    void Update(MSG* msg);

	void Quit();
private:
    CWindow* m_pwindow;
    COpenglDevice* m_pOpenglDevice  = nullptr;
    CRenderer* m_prenderer = nullptr;

    CMesh* testMesh = nullptr;
};


#endif // !__APPLICATION_H__
