#pragma once
#include <glew.h>
class IndexBuffer
{
private:
	GLuint m_renderID;
	GLuint m_Count;
public:
	IndexBuffer( GLuint* data, GLuint count, GLuint usage);
	~IndexBuffer();
	void Bind();
	void Unbind();

};

