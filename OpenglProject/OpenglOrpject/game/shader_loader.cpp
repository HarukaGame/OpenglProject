#include "shader_loader.h"
#include "GL/glew.h"
#include "debug_print.h"

int CShaderLoader::CreateShaderProgram(const char* _vertSource, int _vertLength, const char* _fragSource, int _fragLength)
{
    //�o�[�e�b�N�X�V�F�[�_�[�R���p�C��
    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertShaderID, 1, &_vertSource, &_vertLength);
    glCompileShader(vertShaderID);

    GLint success = 0;
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        PRINT("�o�[�e�b�N�X�V�F�[�_�[�̃R���p�C���Ɏ��s���܂���");
    }

    //�t���O�����g�V�F�[�_�[�̃R���p�C��
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderID, 1, &_fragSource, &_fragLength);
    glCompileShader(fragShaderID);

    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &_fragLength);
    if (success == GL_FALSE) {
        PRINT("�t���O�����g�V�F�[�_�[�̃R���p�C���Ɏ��s���܂���");

    }

    //�v���O�����I�u�W�F�N�g�̍쐬
    GLuint programID = glCreateProgram();
    if (programID == 0) {
        PRINT("�v���O�����I�u�W�F�N�g�̐����Ɏ��s���܂���");
    }
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);
    GLint attached;
    glGetProgramiv(programID, GL_ATTACHED_SHADERS, &attached);
    if (attached == GL_FALSE) {
        PRINT("�V�F�[�_�[�̃A�^�b�`�Ɏ��s���܂���");

    }
    //�����N
    GLint linked;
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        PRINT("�V�F�[�_�[�̃����N�Ɏ��s���܂���");

    }

    return programID;
}
