#include "opengl_device.h"
#include "GL/glew.h"
#include "debug_print.h"

bool COpenglDevice::Initilize(HWND _hwnd)
{
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
        PFD_TYPE_RGBA,                                              //The kind of framebuffer. RGBA or palette.
        32,                                                         //Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                                                         //Number of bits for the depthbuffer
        8,                                                          //Number of bits for the stencilbuffer
        0,                                                          //Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    m_hdc = GetDC(_hwnd);
    int format = ChoosePixelFormat(m_hdc, &pfd);
    if (format == 0) {
        PRINT("�s�N�Z���t�H�[�}�b�g�̑I���Ɏ��s���܂���");

        return false; // �Y������s�N�Z���t�H�[�}�b�g������
    }

    // OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
    if (!SetPixelFormat(m_hdc, format, &pfd)) {
        PRINT("�s�N�Z���t�H�[�}�b�g�̃Z�b�g�Ɏ��s���܂���");

        return false; // DC�փt�H�[�}�b�g��ݒ肷��̂Ɏ��s
    }

    // OpenGL context���쐬
    m_glrc = wglCreateContext(m_hdc);

    // �쐬���ꂽ�R���e�L�X�g���J�����g�i���ݎg�p���̃R���e�L�X�g�j���H
    if (!wglMakeCurrent(m_hdc, m_glrc)) {
        PRINT("�J�����g�R���e�L�X�g");

        return false; // �����������Ȃ��݂����c
    }

    if (glewInit() != GLEW_OK) {
        PRINT("GL�̏������Ɏ��s���܂���");

        return false;
    }
    return true;

}

void COpenglDevice::SwapBuffer()
{
    SwapBuffers(m_hdc);

}

void COpenglDevice::Finalize()
{
    // �㏈��
// �J�����g�R���e�L�X�g�𖳌��ɂ���
    wglMakeCurrent(NULL, NULL);

    // �J�����g�R���e�L�X�g���폜
    wglDeleteContext(m_glrc);

    // �f�o�C�X�R���e�L�X�g���
    ReleaseDC(m_hwnd, m_hdc);
}
