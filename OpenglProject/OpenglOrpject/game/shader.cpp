#include "shader.h"
#include "GL/glew.h"
#include "debug_print.h"

bool CShader::SetUpUniform(int _programID)
{
    m_programID = _programID;
    glUseProgram(m_programID);

    m_uniformList[SHADER_UNIFORM_COLOR] = -1;
    m_uniformList[SHADER_UNIFORM_COLOR] = glGetUniformLocation(m_programID, "color");
    if (m_uniformList[SHADER_UNIFORM_COLOR] == -1) {
        PRINT("color uniform‚ÌŽæ“¾‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

    }

    m_uniformList[SHADER_UNIFORM_LIGHT] = -1;

    m_uniformList[SHADER_UNIFORM_LIGHT] = glGetUniformLocation(m_programID, "light");
    if (m_uniformList[SHADER_UNIFORM_LIGHT] == -1) {
        printf("light uniform‚ÌŽæ“¾‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

    }

    m_uniformList[SHADER_UNIFORM_MVP] = -1;

    m_uniformList[SHADER_UNIFORM_MVP] = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformList[SHADER_UNIFORM_MVP] == -1) {
        printf("MVP uniform‚ÌŽæ“¾‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

    }

    m_attributeList[SHADER_ATTRIBUTE_POSITION] = glGetAttribLocation(m_programID, "position");
    if (m_attributeList[SHADER_ATTRIBUTE_POSITION] == -1) {
        PRINT("position attribute‚ÌŽæ“¾‚ÉŽ¸”s‚µ‚Ü‚µ‚½\n");
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
