#include "application.h"
#include "window.h"
#include "opengl_device.h"

bool CApplication::Initilize(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) {
    m_pwindow = new CWindow();
    m_pwindow->WinInitilize(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    m_pOpenglDevice = new COpenglDevice();
    m_pOpenglDevice->Initilize(m_pwindow->GetHWND());

    return true;
}

void CApplication::Update(MSG* msg) {
    m_pwindow->DispUpdate();
    m_pOpenglDevice->SwapBuffer();
}

void CApplication::Quit() {
    m_pOpenglDevice->Finalize();
    delete m_pOpenglDevice;

    delete m_pwindow;
}