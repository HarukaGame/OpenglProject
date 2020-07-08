#include "buffer.h"
#include "mesh.h"

int CBuffer::GetProgramID() const
{
	return m_buffer;
}

void CBuffer::CreateBuffer(const CMesh* _mesh)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, _mesh->GetVertexNum() * _mesh->GetElementNum() * sizeof(GLfloat), &_mesh->myvertices[0], GL_STATIC_DRAW);

	m_vertexNum = _mesh->GetVertexNum();
}

void CBuffer::CreateBufferIndex(const CMesh* _mesh)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, 32 * 4 * sizeof(GLfloat), _mesh->myvertices, GL_STATIC_DRAW);
}

int CBuffer::GetVertexNum() const
{
	return m_vertexNum;
}

void CBuffer::DeleteBuffer()
{
	glDeleteBuffers(1, &m_buffer);
}
