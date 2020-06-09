#include "shader.h"
#include "GL/glew.h"
#include "debug_print.h"

bool CShader::SetUpUniform(int _programID)
{
    m_programID = _programID;
    glUseProgram(m_programID);

    m_uniformList[SHADER_UNIFORM_COLOR] = glGetUniformLocation(m_programID, "color");
    if (m_uniformList[SHADER_UNIFORM_COLOR] == -1) {
        PRINT("color uniform‚ÌŽæ“¾‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

    }
    m_uniformList[SHADER_UNIFORM_LIGHT] = glGetUniformLocation(m_programID, "light");
    if (m_uniformList[SHADER_UNIFORM_LIGHT] == -1) {
        printf("light uniform‚ÌŽæ“¾‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

    }

    m_uniformList[SHADER_UNIFORM_MVP] = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformList[SHADER_UNIFORM_MVP] == -1) {
        printf("MVP uniform‚ÌŽæ“¾‚ÉŽ¸”s‚µ‚Ü‚µ‚½");

    }




    return m_programID;
}
