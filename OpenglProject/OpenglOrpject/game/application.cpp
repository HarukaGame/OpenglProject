#include "application.h"
#include "window.h"
#include "opengl_device.h"
#include "renderer.h"
#include "object_manager.h"
#include "resource_manager.h"
#include "scene_manager.h"
#include "scene.h"
#include "input.h"
#include "mesh.h"
#include "hash.h"
#include "camera.h"

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
    CResourceManager::CreateInstance();

    m_pObjectManager = new CObjectManager();
    m_pObjectManager->Initilize();


    //m_pScene = new CScene();
    //m_pScene->SetObjectManager(m_pObjectManager);


    CSceneManager::GetInstance().Initilize(m_pObjectManager);
    CSceneManager::GetInstance().LoadScene(CHash::CRC32("MainScene"));
    return true;
}

void CApplication::Update(MSG* msg) {
    //m_prenderer->SetShaderMesh(testMesh, "shader.vert", "shader.frag");
    Input::StackInput();

    //m_pScene->Update();
    CSceneManager::GetInstance().Update();

    m_prenderer->StartDisplay();

    m_pObjectManager->ZSort(CCamera::GetInstance()->GetPosition());
    m_pObjectManager->AllObjectDraw(m_prenderer);
    //m_prenderer->MeshDraw(testMesh);

    m_pOpenglDevice->SwapBuffer();
    Input::ReleaseInput();
}

void CApplication::Quit() {
    CSceneManager::GetInstance().Finalize();

    m_pOpenglDevice->Finalize();
    m_pObjectManager->Finalize();
    m_prenderer->Release();
    delete m_pOpenglDevice;
    //delete m_pScene;
    delete m_pObjectManager;
    delete m_prenderer;
    CResourceManager::Finalize();
    CResourceManager::Destroy();
    Input::DestroyInstance();
    m_pwindow->Finalize();
    delete m_pwindow;
    int a = 0;
}