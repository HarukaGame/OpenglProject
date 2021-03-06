﻿#include "renderer.h"
#include "Mesh.h"
#include "shader.h"
#include "texture.h"
#include "buffer.h"
#include "camera.h"
#include "light.h"
#include "debug_print.h"

#include "GL/glew.h"
#include <cmath>

#include "fileloader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <math.h>
#include "input.h"

#include "ray_cast.h"

#include "common_math.h"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

float test = -1;

static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1,VERTEX = 0,FRAGMENT = 1 
    };

    std::string line;

    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}

bool CRenderer::Initialize(HWND _hwnd) {
    m_hwnd = _hwnd;

    //if (GLSetUp(_hwnd) == false) {
    //    printf("GLのセットアップに失敗しました");
    //    return false;
    //}

    return true;

}

void CRenderer::StartDisplay() {

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glDepthRange(-1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glClearDepth(0.0f);
    glEnable(GL_CULL_FACE);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f);
}

void CRenderer::MeshDraw(CBuffer* _buffer,const CShader* _shader,const CTexture* _texture,glm::mat4& modelMat,const glm::vec3& _addUV) {
    if (_buffer == nullptr) {
        PRINT("CRenderer::MeshDraw _buffer is nullptr\n");
        return;
    }
    glBindBuffer(GL_ARRAY_BUFFER, _buffer->GetProgramID());

    if (_shader == nullptr) {
        PRINT("CRenderer::MeshDraw _shader is nullptr\n");
        return;
    }

    glUseProgram(_shader->GetProgramID());
    //glUseProgram(_buffer->GetProgramID());

    //_mesh->SetColor(0, 1, 1, 1);
    glm::vec3 lightDir = CLight::GetInstance()->GetDirection();
    SetLight(_shader, lightDir.x, lightDir.y, lightDir.z);
    if (_shader->GetTransparent() == true) {
        glEnable(GL_BLEND);
        //SetColor(_shader, 0, 1, 1, 0.5);
    }
    else {
        //SetColor(_shader, 1, 0, 0, 1);
    }

    if (_texture != nullptr) {
        SetTexture(_shader, _texture);
        SetNormalTexture(_shader, _texture);
    }
    //_mesh->SetLight(1, 2, 3);

    test += 0.1f;

    //ビュー行列の取得
    glm::mat4 view = CCamera::GetInstance()->GetViewMatrix();
    //プロジェクション行列の取得
    glm::mat4 pro = CCamera::GetInstance()->GetProjectionMatrix();

    //ビューポート行列の取得
    glm::mat4 viewportMat = GetViewPortMatrix((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);

    

    //MVP行列の計算
    glm::mat4 mvp = pro * view * modelMat;


    glUniform3f(_shader->GetUniform(SHADER_UNIFORM_ADD_POSITION), modelMat[3][0], modelMat[3][1], -1);
    glUniform3f(_shader->GetUniform(SHADER_UNIFORM_SCALE), modelMat[0][0], modelMat[1][1], modelMat[2][2]);
    glUniform2f(_shader->GetUniform(SHADER_UNIFORM_UV), _addUV.x, _addUV.y);

    //行列のUniform設定
    glUniformMatrix4fv(_shader->GetUniform(SHADER_UNIFORM_MVP), 1, GL_FALSE, &mvp[0][0]);

    glm::mat3 model3 = glm::mat3();
    model3[0][0] = modelMat[0][0];
    model3[0][1] = modelMat[0][1];
    model3[0][2] = modelMat[0][2];
    model3[1][0] = modelMat[1][0];
    model3[1][1] = modelMat[1][1];
    model3[1][2] = modelMat[1][2];
    model3[2][0] = modelMat[2][0];
    model3[2][1] = modelMat[2][1];
    model3[2][2] = modelMat[2][2];

    model3 =  glm::transpose(model3);

    glUniformMatrix3fv(_shader->GetUniform(SHADER_UNIFORM_MODEL_MAT), 1, GL_FALSE, &model3[0][0]);

    int a = sizeof(GLfloat) * 6;
    //PRINT("%d\n",a);
    //Attribure設定
    glEnableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_POSITION));
    glVertexAttribPointer(_shader->GetAttribute(SHADER_ATTRIBUTE_POSITION), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, 0);
    glEnableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_NORMAL));
    glVertexAttribPointer(_shader->GetAttribute(SHADER_ATTRIBUTE_NORMAL), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat)*3));
    glEnableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_UV));
    glVertexAttribPointer(_shader->GetAttribute(SHADER_ATTRIBUTE_UV), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 6));
    glEnableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_TANGENT));
    glVertexAttribPointer(_shader->GetAttribute(SHADER_ATTRIBUTE_TANGENT), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 8));

    if (_texture != nullptr) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture->m_textureID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _texture->m_normalID);
        glActiveTexture(GL_TEXTURE0);

    }

    glDrawArrays(GL_TRIANGLES, 0, _buffer->GetVertexNum());

    glDisableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_POSITION));
    glDisableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_NORMAL));
    glDisableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_UV));

    glUseProgram(0);

    glDisable(GL_BLEND);
}

void CRenderer::MeshDrawIndex(CBuffer* _buffer, const CShader* _shader, const CTexture* _texture, glm::mat4& modelMat, const unsigned int _indexCount,const unsigned int* indeces)
{
    if (_buffer == nullptr) {
        PRINT("CRenderer::MeshDraw _buffer is nullptr\n");
        return;
    }
    glBindBuffer(GL_ARRAY_BUFFER, _buffer->GetProgramID());

    if (_shader == nullptr) {
        PRINT("CRenderer::MeshDraw _shader is nullptr\n");
        return;
    }

    glUseProgram(_shader->GetProgramID());
    //glUseProgram(_buffer->GetProgramID());

    //_mesh->SetColor(0, 1, 1, 1);
    glm::vec3 lightDir = CLight::GetInstance()->GetDirection();
    SetLight(_shader, lightDir.x, lightDir.y, lightDir.z);
    if (_shader->GetTransparent() == true) {
        glEnable(GL_BLEND);
        //SetColor(_shader, 0, 1, 1, 0.5);
    }
    else {
        //SetColor(_shader, 1, 0, 0, 1);
    }

    if (_texture != nullptr) {
        SetTexture(_shader, _texture);
        SetNormalTexture(_shader, _texture);
    }
    //_mesh->SetLight(1, 2, 3);

    test += 0.1f;

    //ビュー行列の取得
    glm::mat4 view = CCamera::GetInstance()->GetViewMatrix();
    //プロジェクション行列の取得
    glm::mat4 pro = CCamera::GetInstance()->GetProjectionMatrix();

    //ビューポート行列の取得
    glm::mat4 viewportMat = GetViewPortMatrix((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);



    //MVP行列の計算
    glm::mat4 mvp = pro * view * modelMat;


    glUniform3f(_shader->GetUniform(SHADER_UNIFORM_ADD_POSITION), modelMat[3][0], modelMat[3][1], -1);
    //行列のUniform設定
    glUniformMatrix4fv(_shader->GetUniform(SHADER_UNIFORM_MVP), 1, GL_FALSE, &mvp[0][0]);


    int a = sizeof(GLfloat) * 6;
    //PRINT("%d\n",a);
    //Attribure設定
    glEnableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_POSITION));
    glVertexAttribPointer(_shader->GetAttribute(SHADER_ATTRIBUTE_POSITION), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);
    glEnableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_NORMAL));
    glVertexAttribPointer(_shader->GetAttribute(SHADER_ATTRIBUTE_NORMAL), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_UV));
    glVertexAttribPointer(_shader->GetAttribute(SHADER_ATTRIBUTE_UV), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 6));

    if (_texture != nullptr) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture->m_textureID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _texture->m_normalID);
        glActiveTexture(GL_TEXTURE0);

    }

    glDrawElements(GL_TRIANGLE_STRIP, _indexCount, GL_UNSIGNED_INT, indeces);

    glDisableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_POSITION));
    glDisableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_NORMAL));
    glDisableVertexAttribArray(_shader->GetAttribute(SHADER_ATTRIBUTE_UV));

    glUseProgram(0);

    glDisable(GL_BLEND);

}



void CRenderer::Release() {

    //GLRelease();
}


void CRenderer::SetLight(const CShader* _shader,const float _x, const float _y, const float _z)
{
    float length = sqrtf(_x * _x + _y * _y + _z * _z);
    glUniform3f(_shader->GetUniform(SHADER_UNIFORM_LIGHT), _x / length, _y / length, _z / length);
}

void CRenderer::SetColor(const CShader* _shader, const float _r, const float _g, const float _b, const float _a)
{
    glUniform4f(_shader->GetUniform(SHADER_UNIFORM_COLOR), _r, _g, _b, _a);
}

void CRenderer::SetTexture(const CShader* _shader, const CTexture* _texture)
{
    glUniform1i(_shader->GetUniform(SHADER_UNIFORM_TEXTURE), 0);
}

void CRenderer::SetNormalTexture(const CShader* _shader, const CTexture* _normal)
{
    glUniform1i(_shader->GetUniform(SHADER_UNIFORM_NORMAL_MAP), 1);

}



void CRenderer::GLRelease() {
    // 後処理
    // カレントコンテキストを無効にする
    wglMakeCurrent(NULL, NULL);

    // カレントコンテキストを削除
    wglDeleteContext(m_glrc);

    // デバイスコンテキスト解放
    ReleaseDC(m_hwnd, m_hdc);
}

glm::mat4 CRenderer::GetTransMatrix(glm::vec3 trans) {
    //glm::mat4 transMat = {
    //1,0,0,trans.x,
    //0,1,0,trans.y,
    //0,0,1,trans.z,
    //0,0,0,1
    //};
    glm::mat4 transMat = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    trans.x,trans.y,trans.z,1
    };
    return transMat;
}
glm::mat4 CRenderer::GetRotateMatrix(glm::vec3 rotate) {
    rotate.x = deg_to_rad(rotate.x);
    rotate.y = deg_to_rad(rotate.y);
    rotate.z = deg_to_rad(rotate.z);
    glm::mat4 rotateX = {
    1,      0,      0,      0,
    0,      cos(rotate.x), -sin(rotate.x),0,
    0,      sin(rotate.x), cos(rotate.x), 0,
    0,      0,      0,      1
    };

    glm::mat4 rotateY = {
        cos(rotate.y), 0,      -sin(rotate.y),0,
        0,      1,      0 ,     0,
        sin(rotate.y), 0,      cos(rotate.y), 0,
        0,      0,      0,      1
    };

    glm::mat4 rotateZ = {
        cos(rotate.z), -sin(rotate.z),0,      0,
        sin(rotate.z), cos(rotate.z), 0,      0,
        0,      0,      1,      0,
        0,      0,      0,      1
    };
    glm::mat4 rotateMat = rotateX * rotateY * rotateZ;
    return rotateMat;
}
glm::mat4 CRenderer::GetScaleMatrix(glm::vec3 scale) {
    glm::mat4 scaleMat = {
    scale.x ,0      ,0      ,0,
    0       ,scale.y,0      ,0,
    0       ,0      ,scale.z,0,
    0       ,0      ,0      ,1
    };
    return scaleMat;
}


glm::mat4 CRenderer::GetModelMatirix(glm::vec3 trans, glm::vec3 rotate, glm::vec3 scale) {
    glm::mat4 transMat = GetTransMatrix(trans);
    glm::mat4 rotateMat = GetRotateMatrix(rotate);
    glm::mat4 scaleMat = GetScaleMatrix(scale);

    return transMat * rotateMat * scaleMat;
}


glm::mat4 CRenderer::GetViewMatirix(glm::vec3 camera, glm::vec3 target, glm::vec3 up, bool inverseZ) {
    glm::vec3 cX = { 0.0,    0.0,    0.0 };
    glm::vec3 cY = { 0.0,    0.0,    0.0 };
    glm::vec3 cZ = { 0.0,    0.0,    0.0 };

    //カメラZ軸の設定
    cZ = glm::normalize(camera - target);

    //カメラX軸の設定
    cX = glm::normalize(glm::cross(up, cZ));

    //カメラY軸の設定
    cY = glm::normalize(glm::cross(cZ,cX));


    //Z軸が手前にあるなら
    if (inverseZ == true) {
        cZ = -cZ;
    }
    float moveX = glm::dot(camera, cX);
    float moveY = glm::dot(camera, cY);
    float moveZ = glm::dot(camera, cZ);
    //float moveX = cZ.x;
    //float moveY = cZ.y;
    //float moveZ = cZ.z;

    //glm::mat4 ret = {
    //    cX.x    ,cY.x   ,cZ.x   ,0,
    //    cX.y    ,cY.y   ,cZ.y   ,0,
    //    cX.z    ,cY.z   ,cZ.z   ,0,
    //   -moveX       ,-moveY     ,-moveZ      ,1
    //};
    glm::mat4 ret = {
        cX.x    ,cX.y   ,cX.z   ,-moveX,
        cY.x    ,cY.y   ,cY.z   ,-moveY,
        cZ.x    ,cZ.y   ,cZ.z   ,-moveZ,
        0       ,0      ,0      ,1
    };
    //glm::mat4 ret = {
    //    cX.x    ,cY.x   ,cZ.x   ,-moveX,
    //    cX.y    ,cY.y   ,cZ.y   ,-moveY,
    //    cX.z    ,cY.z   ,cZ.z   ,-moveZ,
    //    0       ,0      ,0      ,1
    //};

    return ret;
}

glm::mat4 CRenderer::GetViewMatirix(glm::vec3 trans, glm::vec3 rotate) {
    
    return    GetRotateMatrix(-rotate)*GetTransMatrix(-trans);
}

glm::mat4 CRenderer::GetProjectionMatrix(float _angle, float _aspect, float _far, float _near) {
    float zoomY = 1 / tanf(deg_to_rad(_angle)/2.0f);
    float zoomX = zoomY / _aspect;

    glm::mat4 ret = {
        zoomX,0,0,0,
        0,zoomY,0,0,
        0,0,(_far+_near) / (_far - _near),-1,
        0,0,-2.0f*_far * _near / (_far - _near),0
    };
    ret = glm::transpose(ret);
    return ret;
}

glm::mat4 CRenderer::GetViewPortMatrix(float _width, float _height)
{
    glm::mat4 ret = {
        _width/2.0f,    //size change
        0,
        0,
        0,

        0,
        -_height/2.0f,  //size change
        0,
        0,

        0,
        0,
        1,
        0,

        _width/2.0f,    //transform
        _height/2.0f,   //transform
        0,
        1
    };
    return ret;
}
