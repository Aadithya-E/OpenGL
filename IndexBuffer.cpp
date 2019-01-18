#include "IndexBuffer.h"

#include<glew.h>

IndexBuffer::IndexBuffer(GLuint* data, GLuint count, GLuint usage)
{
	glGenBuffers(1, &m_renderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, usage);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_renderID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
