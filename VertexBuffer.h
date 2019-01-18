#pragma once
#include<glew.h>

class VertexBuffer
{
private:
	GLuint m_renderID;
public:
	VertexBuffer( void* data, GLuint size, GLuint usage);
	~VertexBuffer();
	void Bind();
	void Unbind();

};

