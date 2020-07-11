#include "mesh.h"
#include "buffer.h"

#include <windows.h>
#include "GL/glew.h"
#include <iostream>

#include "vertexfiles/cube.h"
#include "vertexfiles/quad_index.h"

#include "common_math.h"


static const unsigned int COLUMN_START_POSITION = 0;
static const unsigned int COLUMN_END_POSITION = 2;
static const unsigned int COLUMN_START_NORMAL = 3;
static const unsigned int COLUMN_END_NORMAL = 5;
static const unsigned int COLUMN_START_UV = 6;
static const unsigned int COLUMN_END_UV = 7;
static const unsigned int COLUMN_START_TANGENT = 8;
static const unsigned int COLUMN_END_TANGENT = 10;


void CMesh::InitVertex()
{
    myvertices = PolygonQuadIndex::vertices;
    indeces = PolygonQuadIndex::indeces;
}

bool CMesh::CreateBuffer()
{
    m_pBuffer = new CBuffer();
    if (m_pBuffer == nullptr) {
        return false;
    }
    AddTangent();
    if (m_isIndex == true) {
        m_pBuffer->CreateBufferIndex(this);
    }
    else {
        m_pBuffer->CreateBuffer(this);
    }
    return false;
}

CBuffer* CMesh::GetBuffer() const
{
    return m_pBuffer;
}

void CMesh::AddTangent()
{
    unsigned int tangentElementNum = 3;
    unsigned int newElementNum = elementNum + tangentElementNum;
    unsigned int vertexDataNum = vertexNum * newElementNum;
    float* newVertices = (float*)malloc(vertexDataNum * sizeof(float));

    unsigned int vertexIndex = 0;
    unsigned int sride = 0;
    for (unsigned int i = 0; i < vertexDataNum; i++) {
        vertexIndex = i % newElementNum;
        if (vertexIndex < elementNum) {
            newVertices[i] = myvertices[sride];
            sride++;
        }
    }

    unsigned int posSride = 0;
    unsigned int normallSride = 0;
    unsigned int tangentSride = 0;
    vertexIndex = 0;
    for (unsigned int i = 0; i < vertexNum /3; i++) {
        unsigned int index0 = newElementNum * (i * 3 + 0);
        unsigned int index1 = newElementNum * (i * 3 + 1);
        unsigned int index2 = newElementNum * (i * 3 + 2);
        glm::vec3 pos[3];
        glm::vec2 uv[3];
        pos[0].x = newVertices[index0 + COLUMN_START_POSITION + 0];
        pos[0].y = newVertices[index0 + COLUMN_START_POSITION + 1];
        pos[0].z = newVertices[index0 + COLUMN_START_POSITION + 2];
        pos[1].x = newVertices[index1 + COLUMN_START_POSITION + 0];
        pos[1].y = newVertices[index1 + COLUMN_START_POSITION + 1];
        pos[1].z = newVertices[index1 + COLUMN_START_POSITION + 2];
        pos[2].x = newVertices[index2 + COLUMN_START_POSITION + 0];
        pos[2].y = newVertices[index2 + COLUMN_START_POSITION + 1];
        pos[2].z = newVertices[index2 + COLUMN_START_POSITION + 2];

        uv[0].x = newVertices[index0 + COLUMN_START_UV + 0];
        uv[0].y = newVertices[index0 + COLUMN_START_UV + 1];
        uv[1].x = newVertices[index1 + COLUMN_START_UV + 0];
        uv[1].y = newVertices[index1 + COLUMN_START_UV + 1];
        uv[2].x = newVertices[index2 + COLUMN_START_UV + 0];
        uv[2].y = newVertices[index2 + COLUMN_START_UV + 1];
        glm::vec3 deltaPos1 = pos[1] - pos[0];
        glm::vec3 deltaPos2 = pos[2] - pos[0];
        glm::vec2 deltaUV1 = uv[1] - uv[0];
        glm::vec2 deltaUV2 = uv[2] - uv[0];
        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y);
        newVertices[index0 + COLUMN_START_TANGENT + 0] += tangent.x;
        newVertices[index1 + COLUMN_START_TANGENT + 0] += tangent.x;
        newVertices[index2 + COLUMN_START_TANGENT + 0] += tangent.x;
        newVertices[index0 + COLUMN_START_TANGENT + 1] += tangent.y;
        newVertices[index1 + COLUMN_START_TANGENT + 1] += tangent.y;
        newVertices[index2 + COLUMN_START_TANGENT + 1] += tangent.y;
        newVertices[index0 + COLUMN_START_TANGENT + 2] += tangent.z;
        newVertices[index1 + COLUMN_START_TANGENT + 2] += tangent.z;
        newVertices[index2 + COLUMN_START_TANGENT + 2] += tangent.z;

    }

    m_tangentFrag = true;
    elementNum += tangentElementNum;
    myvertices = newVertices;
}

glm::mat4 CMesh::GetModelMatrix() const
{
    glm::mat4 transMat = GetTransMatrix(m_pos);
    glm::mat4 rotateMat = GetRotateMatrix(m_rot);
    glm::mat4 scaleMat = GetScaleMatrix(m_scale);

    return transMat * rotateMat * scaleMat;
}

void CMesh::Finalize()
{
    if (m_pBuffer != nullptr) {
        m_pBuffer->DeleteBuffer();
        delete m_pBuffer;
    }
    if (m_tangentFrag == true) {
        delete myvertices;
    }
}

glm::mat4 CMesh::GetTransMatrix(glm::vec3 trans)const {
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


glm::mat4 CMesh::GetRotateMatrix(glm::vec3 rotate)const {
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
glm::mat4 CMesh::GetScaleMatrix(glm::vec3 scale)const {
    glm::mat4 scaleMat = {
    scale.x ,0      ,0      ,0,
    0       ,scale.y,0      ,0,
    0       ,0      ,scale.z,0,
    0       ,0      ,0      ,1
    };
    return scaleMat;
}