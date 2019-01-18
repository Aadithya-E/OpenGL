#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	GLuint m_RenderID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer vb, VertexBufferLayout layout);

	void Bind();
	void Unbind();
};

