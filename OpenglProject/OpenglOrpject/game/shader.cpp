#include "shader.h"
#include "GL/glew.h"
#include "debug_print.h"


bool CShader::SetUpUniform()
{
    glUseProgram(m_programID);

    //----------------------------------------------------------
    //uniform設定
    //----------------------------------------------------------

    m_uniformList[SHADER_UNIFORM_COLOR] = -1;
    m_uniformList[SHADER_UNIFORM_COLOR] = glGetUniformLocation(m_programID, "color");
    if (m_uniformList[SHADER_UNIFORM_COLOR] == -1) {
        PRINT("color uniformの取得に失敗しました\n");

    }

    m_uniformList[SHADER_UNIFORM_LIGHT] = -1;

    m_uniformList[SHADER_UNIFORM_LIGHT] = glGetUniformLocation(m_programID, "light");
    if (m_uniformList[SHADER_UNIFORM_LIGHT] == -1) {
        PRINT("light uniformの取得に失敗しました\n");

    }

    m_uniformList[SHADER_UNIFORM_MVP] = -1;
    m_uniformList[SHADER_UNIFORM_MVP] = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformList[SHADER_UNIFORM_MVP] == -1) {
        PRINT("MVP uniformの取得に失敗しました\n");

    }

    m_uniformList[SHADER_UNIFORM_MODEL_MAT] = -1;
    m_uniformList[SHADER_UNIFORM_MODEL_MAT] = glGetUniformLocation(m_programID, "model_mat");
    if (m_uniformList[SHADER_UNIFORM_MODEL_MAT] == -1) {
        PRINT("model_mat uniformの取得に失敗しました\n");

    }

    m_uniformList[SHADER_UNIFORM_TEXTURE] = -1;
    m_uniformList[SHADER_UNIFORM_TEXTURE] = glGetUniformLocation(m_programID, "texture");
    if (m_uniformList[SHADER_UNIFORM_TEXTURE] == -1) {
        PRINT("texture uniformの取得に失敗しました\n");
    }

    m_uniformList[SHADER_UNIFORM_NORMAL_MAP] = -1;
    m_uniformList[SHADER_UNIFORM_NORMAL_MAP] = glGetUniformLocation(m_programID, "normal_map");
    if (m_uniformList[SHADER_UNIFORM_NORMAL_MAP] == -1) {
        PRINT("normal_map uniformの取得に失敗しました\n");
    }

    m_uniformList[SHADER_UNIFORM_ADD_POSITION] = -1;
    m_uniformList[SHADER_UNIFORM_ADD_POSITION] = glGetUniformLocation(m_programID, "add");
    if (m_uniformList[SHADER_UNIFORM_ADD_POSITION] == -1) {
        PRINT("add uniformの取得に失敗しました\n");
    }

    m_uniformList[SHADER_UNIFORM_SCALE] = -1;
    m_uniformList[SHADER_UNIFORM_SCALE] = glGetUniformLocation(m_programID, "scale");
    if (m_uniformList[SHADER_UNIFORM_SCALE] == -1) {
        PRINT("scale uniformの取得に失敗しました\n");
    }

    m_uniformList[SHADER_UNIFORM_RATIO] = -1;
    m_uniformList[SHADER_UNIFORM_RATIO] = glGetUniformLocation(m_programID, "ratio");
    if (m_uniformList[SHADER_UNIFORM_RATIO] == -1) {
        PRINT("ratio uniformの取得に失敗しました\n");
    }

    m_uniformList[SHADER_UNIFORM_TRANS_SLOPE] = -1;
    m_uniformList[SHADER_UNIFORM_TRANS_SLOPE] = glGetUniformLocation(m_programID, "slope");
    if (m_uniformList[SHADER_UNIFORM_TRANS_SLOPE] == -1) {
        PRINT("slope uniformの取得に失敗しました\n");
    }


    //----------------------------------------------------------
    //attribute設定
    //----------------------------------------------------------

    m_attributeList[SHADER_ATTRIBUTE_POSITION] = glGetAttribLocation(m_programID, "position");
    if (m_attributeList[SHADER_ATTRIBUTE_POSITION] == -1) {
        PRINT("position attributeの取得に失敗しました\n");
    }
    m_attributeList[SHADER_ATTRIBUTE_NORMAL] = glGetAttribLocation(m_programID, "normals");
    if (m_attributeList[SHADER_ATTRIBUTE_NORMAL] == -1) {
        PRINT("normals attributeの取得に失敗しました\n");
    }

    m_attributeList[SHADER_ATTRIBUTE_UV] = glGetAttribLocation(m_programID, "texture_uv");
    if (m_attributeList[SHADER_ATTRIBUTE_UV] == -1) {
        PRINT("texture_uv attributeの取得に失敗しました\n");
    }

    m_attributeList[SHADER_ATTRIBUTE_TANGENT] = glGetAttribLocation(m_programID, "tangent");
    if (m_attributeList[SHADER_ATTRIBUTE_TANGENT] == -1) {
        PRINT("tangent attributeの取得に失敗しました\n");
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
    //バーテックスシェーダーコンパイル
    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertShaderID, 1, &_vertSource, &_vertLength);
    glCompileShader(vertShaderID);

    GLint success = 0;
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        PRINT("バーテックスシェーダーのコンパイルに失敗しました");
    }

    //フラグメントシェーダーのコンパイル
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderID, 1, &_fragSource, &_fragLength);
    glCompileShader(fragShaderID);

    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &_fragLength);
    if (success == GL_FALSE) {
        PRINT("フラグメントシェーダーのコンパイルに失敗しました");

    }

    //プログラムオブジェクトの作成
    m_programID = glCreateProgram();
    if (m_programID == 0) {
        PRINT("プログラムオブジェクトの生成に失敗しました");
    }
    glAttachShader(m_programID, vertShaderID);
    glAttachShader(m_programID, fragShaderID);
    GLint attached;
    glGetProgramiv(m_programID, GL_ATTACHED_SHADERS, &attached);
    if (attached == GL_FALSE) {
        PRINT("シェーダーのアタッチに失敗しました");

    }
    //リンク
    GLint linked;
    glLinkProgram(m_programID);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        PRINT("シェーダーのリンクに失敗しました");

    }

    if (SetUpUniform() == false) {
        PRINT("ユニフォームセットアップに失敗しました");
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
