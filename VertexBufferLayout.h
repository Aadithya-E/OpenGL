#pragma once
#include <vector>
#include <glew.h>
struct Element
{
	GLuint count;
	GLuint type;
	GLuint sizeoftype;
	GLboolean normalised;
	Element(GLuint c, GLuint t, GLuint s, GLboolean n)
	{
		count = c;
		type = t;
		sizeoftype = s;
		normalised = n;
	}

};

class VertexBufferLayout
{
private:
	std::vector<Element> m_Elements;
	GLuint stride = 0;
public:
	VertexBufferLayout();
	
	template<typename T>
	void Push(GLuint count, GLboolean normalised)
	{
		static_assert(false);		
	}

	template<>
	void Push<GLfloat>(GLuint count, GLboolean normalised)
	{
		m_Elements.push_back(Element(count, GL_FLOAT, 4, normalised));
		stride += count * 4;
	}

	template<>
	void Push<GLuint>(GLuint count, GLboolean normalised)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_INT, 4, normalised });
		stride += count * 4;
	}
	
	/*void Push<GLubyte>(GLuint count, GLboolean normalised)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_BYTE, sizeof(unsigned char), normalised });
		stride += 1;
	}*/

	std::vector<Element> GetElements()
	{
		return m_Elements;
	}

	GLuint GetStride()
	{
		return stride;
	}
};

