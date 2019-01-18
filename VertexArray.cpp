#include "VertexArray.h"
#include <vector>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RenderID);

}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RenderID);
}

void VertexArray::AddBuffer(VertexBuffer vb, VertexBufferLayout layout)
{
	vb.Bind();
	Bind();

	std::vector<Element> elements = layout.GetElements();
	GLuint offset = (GLuint)0;

	for (int i = 0; i < elements.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalised, layout.GetStride(), ( void*)offset);
		offset += elements[i].sizeoftype * elements[i].count;
	}
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RenderID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
