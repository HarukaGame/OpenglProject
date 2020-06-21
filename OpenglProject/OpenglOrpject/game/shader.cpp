#include "shader.h"
#include "GL/glew.h"
#include "debug_print.h"

bool CShader::SetUpUniform(int _programID)
{
    m_programID = _programID;
    glUseProgram(m_programID);

    //----------------------------------------------------------
    //uniform�ݒ�
    //----------------------------------------------------------

    m_uniformList[SHADER_UNIFORM_COLOR] = -1;
    m_uniformList[SHADER_UNIFORM_COLOR] = glGetUniformLocation(m_programID, "color");
    if (m_uniformList[SHADER_UNIFORM_COLOR] == -1) {
        PRINT("color uniform�̎擾�Ɏ��s���܂���");

    }

    m_uniformList[SHADER_UNIFORM_LIGHT] = -1;

    m_uniformList[SHADER_UNIFORM_LIGHT] = glGetUniformLocation(m_programID, "light");
    if (m_uniformList[SHADER_UNIFORM_LIGHT] == -1) {
        printf("light uniform�̎擾�Ɏ��s���܂���");

    }

    m_uniformList[SHADER_UNIFORM_MVP] = -1;

    m_uniformList[SHADER_UNIFORM_MVP] = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformList[SHADER_UNIFORM_MVP] == -1) {
        printf("MVP uniform�̎擾�Ɏ��s���܂���");

    }

    //----------------------------------------------------------
    //attribute�ݒ�
    //----------------------------------------------------------

    m_attributeList[SHADER_ATTRIBUTE_POSITION] = glGetAttribLocation(m_programID, "position");
    if (m_attributeList[SHADER_ATTRIBUTE_POSITION] == -1) {
        PRINT("position attribute�̎擾�Ɏ��s���܂���\n");
    }
    m_attributeList[SHADER_ATTRIBUTE_NORMAL] = glGetAttribLocation(m_programID, "normals");
    if (m_attributeList[SHADER_ATTRIBUTE_NORMAL] == -1) {
        PRINT("normal attribute�̎擾�Ɏ��s���܂���\n");
    }


    return true;
}

bool CShader::SetUpUniform()
{
    glUseProgram(m_programID);

    //----------------------------------------------------------
    //uniform�ݒ�
    //----------------------------------------------------------

    m_uniformList[SHADER_UNIFORM_COLOR] = -1;
    m_uniformList[SHADER_UNIFORM_COLOR] = glGetUniformLocation(m_programID, "color");
    if (m_uniformList[SHADER_UNIFORM_COLOR] == -1) {
        PRINT("color uniform�̎擾�Ɏ��s���܂���");

    }

    m_uniformList[SHADER_UNIFORM_LIGHT] = -1;

    m_uniformList[SHADER_UNIFORM_LIGHT] = glGetUniformLocation(m_programID, "light");
    if (m_uniformList[SHADER_UNIFORM_LIGHT] == -1) {
        printf("light uniform�̎擾�Ɏ��s���܂���");

    }

    m_uniformList[SHADER_UNIFORM_MVP] = -1;

    m_uniformList[SHADER_UNIFORM_MVP] = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformList[SHADER_UNIFORM_MVP] == -1) {
        printf("MVP uniform�̎擾�Ɏ��s���܂���");

    }

    //----------------------------------------------------------
    //attribute�ݒ�
    //----------------------------------------------------------

    m_attributeList[SHADER_ATTRIBUTE_POSITION] = glGetAttribLocation(m_programID, "position");
    if (m_attributeList[SHADER_ATTRIBUTE_POSITION] == -1) {
        PRINT("position attribute�̎擾�Ɏ��s���܂���\n");
    }
    m_attributeList[SHADER_ATTRIBUTE_NORMAL] = glGetAttribLocation(m_programID, "normals");
    if (m_attributeList[SHADER_ATTRIBUTE_NORMAL] == -1) {
        PRINT("normal attribute�̎擾�Ɏ��s���܂���\n");
    }


    return true;
}

int CShader::GetProgramID()const
{
	return m_programID;
}

int CShader::GetUniform(SHADER_UNIFORM _uniform) const
{
    return m_uniformList[_uniform];
}

int CShader::GetAttribute(SHADER_ATTRIBUTE _attribute) const
{
    return m_attributeList[_attribute];
}

void CShader::CreateShaderProgram(const char* _vertSource, int _vertLength, const char* _fragSource,int _fragLength)
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
    m_programID = glCreateProgram();
    if (m_programID == 0) {
        PRINT("�v���O�����I�u�W�F�N�g�̐����Ɏ��s���܂���");
    }
    glAttachShader(m_programID, vertShaderID);
    glAttachShader(m_programID, fragShaderID);
    GLint attached;
    glGetProgramiv(m_programID, GL_ATTACHED_SHADERS, &attached);
    if (attached == GL_FALSE) {
        PRINT("�V�F�[�_�[�̃A�^�b�`�Ɏ��s���܂���");

    }
    //�����N
    GLint linked;
    glLinkProgram(m_programID);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        PRINT("�V�F�[�_�[�̃����N�Ɏ��s���܂���");

    }

    if (SetUpUniform() == false) {
        PRINT("���j�t�H�[���Z�b�g�A�b�v�Ɏ��s���܂���");
    }
}

void CShader::SetTransparent(const bool _value)
{
    m_transparent = _value;
}

bool CShader::GetTransparent() const
{
    return m_transparent;
}
