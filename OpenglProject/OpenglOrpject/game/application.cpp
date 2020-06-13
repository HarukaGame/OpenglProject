#include "application.h"
#include "window.h"
#include "opengl_device.h"
#include "renderer.h"
#include "object_manager.h"
#include "resource_manager.h"
#include "mesh.h"

bool CApplication::Initilize(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) {
    m_pwindow = new CWindow();
    m_pwindow->WinInitilize(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    m_pOpenglDevice = new COpenglDevice();
    m_pOpenglDevice->Initilize(m_pwindow->GetHWND());

    m_prenderer = new CRenderer();
    if (m_prenderer == nullptr) {
        return false;
    }
    bool success = m_prenderer->Initialize(m_pwindow->GetHWND());
    if (success == false) {
        delete m_prenderer;
        return false;
    }

    m_pObjectManager = new CObjectManager();
    m_pObjectManager->Initilize();
    m_pObjectManager->CreateGameObject();
    //m_pObjectManager->CreateGameObject();

    CResourceManager::CreateInstance();

    //testMesh = new CMesh();
    //testMesh->InitVertex();

    return true;
}

void CApplication::Update(MSG* msg) {
    //m_prenderer->SetShaderMesh(testMesh, "shader.vert", "shader.frag");

    m_prenderer->StartDisplay();
    m_pObjectManager->AllObjectDraw(m_prenderer);
    //m_prenderer->MeshDraw(testMesh);

    m_pOpenglDevice->SwapBuffer();
}

void CApplication::Quit() {

    m_pOpenglDevice->Finalize();
    m_pObjectManager->Finalize();
    delete m_pOpenglDevice;

    delete m_pwindow;
    delete m_pObjectManager;

    CResourceManager::Destroy();
}