#include "shader.h"
#include "GL/glew.h"
#include "debug_print.h"


bool CShader::SetUpUniform()
{
    glUseProgram(m_programID);

    //----------------------------------------------------------
    //uniform�ݒ�
    //----------------------------------------------------------

    m_uniformList[SHADER_UNIFORM_COLOR] = -1;
    m_uniformList[SHADER_UNIFORM_COLOR] = glGetUniformLocation(m_programID, "color");
    if (m_uniformList[SHADER_UNIFORM_COLOR] == -1) {
        PRINT("color uniform�̎擾�Ɏ��s���܂���\n");

    }

    m_uniformList[SHADER_UNIFORM_LIGHT] = -1;

    m_uniformList[SHADER_UNIFORM_LIGHT] = glGetUniformLocation(m_programID, "light");
    if (m_uniformList[SHADER_UNIFORM_LIGHT] == -1) {
        PRINT("light uniform�̎擾�Ɏ��s���܂���\n");

    }

    m_uniformList[SHADER_UNIFORM_MVP] = -1;
    m_uniformList[SHADER_UNIFORM_MVP] = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformList[SHADER_UNIFORM_MVP] == -1) {
        PRINT("MVP uniform�̎擾�Ɏ��s���܂���\n");

    }

    m_uniformList[SHADER_UNIFORM_MODEL_MAT] = -1;
    m_uniformList[SHADER_UNIFORM_MODEL_MAT] = glGetUniformLocation(m_programID, "model_mat");
    if (m_uniformList[SHADER_UNIFORM_MODEL_MAT] == -1) {
        PRINT("model_mat uniform�̎擾�Ɏ��s���܂���\n");

    }

    m_uniformList[SHADER_UNIFORM_TEXTURE] = -1;
    m_uniformList[SHADER_UNIFORM_TEXTURE] = glGetUniformLocation(m_programID, "texture");
    if (m_uniformList[SHADER_UNIFORM_TEXTURE] == -1) {
        PRINT("texture uniform�̎擾�Ɏ��s���܂���\n");
    }

    m_uniformList[SHADER_UNIFORM_NORMAL_MAP] = -1;
    m_uniformList[SHADER_UNIFORM_NORMAL_MAP] = glGetUniformLocation(m_programID, "normal_map");
    if (m_uniformList[SHADER_UNIFORM_NORMAL_MAP] == -1) {
        PRINT("normal_map uniform�̎擾�Ɏ��s���܂���\n");
    }

    m_uniformList[SHADER_UNIFORM_ADD_POSITION] = -1;
    m_uniformList[SHADER_UNIFORM_ADD_POSITION] = glGetUniformLocation(m_programID, "add");
    if (m_uniformList[SHADER_UNIFORM_ADD_POSITION] == -1) {
        PRINT("add uniform�̎擾�Ɏ��s���܂���\n");
    }

    m_uniformList[SHADER_UNIFORM_SCALE] = -1;
    m_uniformList[SHADER_UNIFORM_SCALE] = glGetUniformLocation(m_programID, "scale");
    if (m_uniformList[SHADER_UNIFORM_SCALE] == -1) {
        PRINT("scale uniform�̎擾�Ɏ��s���܂���\n");
    }

    m_uniformList[SHADER_UNIFORM_RATIO] = -1;
    m_uniformList[SHADER_UNIFORM_RATIO] = glGetUniformLocation(m_programID, "ratio");
    if (m_uniformList[SHADER_UNIFORM_RATIO] == -1) {
        PRINT("ratio uniform�̎擾�Ɏ��s���܂���\n");
    }

    m_uniformList[SHADER_UNIFORM_TRANS_SLOPE] = -1;
    m_uniformList[SHADER_UNIFORM_TRANS_SLOPE] = glGetUniformLocation(m_programID, "slope");
    if (m_uniformList[SHADER_UNIFORM_TRANS_SLOPE] == -1) {
        PRINT("slope uniform�̎擾�Ɏ��s���܂���\n");
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
        PRINT("normals attribute�̎擾�Ɏ��s���܂���\n");
    }

    m_attributeList[SHADER_ATTRIBUTE_UV] = glGetAttribLocation(m_programID, "texture_uv");
    if (m_attributeList[SHADER_ATTRIBUTE_UV] == -1) {
        PRINT("texture_uv attribute�̎擾�Ɏ��s���܂���\n");
    }

    m_attributeList[SHADER_ATTRIBUTE_TANGENT] = glGetAttribLocation(m_programID, "tangent");
    if (m_attributeList[SHADER_ATTRIBUTE_TANGENT] == -1) {
        PRINT("tangent attribute�̎擾�Ɏ��s���܂���\n");
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

void CShader::SetTransparent(const bool _value)const
{
    m_transparent = _value;
}

bool CShader::GetTransparent() const
{
    return m_transparent;
}

void CShader::Finalize()
{
    glDeleteShader(m_programID);
}

void CShader::SetRatio(float _ratio) const
{
    if (m_uniformList[SHADER_UNIFORM_RATIO] != -1) {
        glUseProgram(m_programID);
        glUniform1f(m_uniformList[SHADER_UNIFORM_RATIO], _ratio);
        glUseProgram(0);
    }
}

void CShader::SetColor(const glm::vec3 _color)const {
    if (m_uniformList[SHADER_UNIFORM_COLOR] != -1) {
        glUseProgram(m_programID);
        glUniform4f(m_uniformList[SHADER_UNIFORM_COLOR], _color.r, _color.g, _color.b, 1.0f);
        glUseProgram(0);

    }
}

void CShader::SetScale(const glm::vec3 _scale) const
{
    if (m_uniformList[SHADER_UNIFORM_SCALE] != -1) {
        glUseProgram(m_programID);
        glUniform3f(m_uniformList[SHADER_UNIFORM_SCALE], _scale.x,_scale.y,_scale.z);
        glUseProgram(0);
    }
}

void CShader::SetSlope(const float _slope) const
{
    if (m_uniformList[SHADER_UNIFORM_TRANS_SLOPE] != -1) {
        glUseProgram(m_programID);
        glUniform1f(m_uniformList[SHADER_UNIFORM_TRANS_SLOPE],_slope);
        glUseProgram(0);
    }

}
