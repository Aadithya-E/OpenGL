#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

using namespace std;


struct ParseReturn
{
	string vertex;
	string fragment;
};

static ParseReturn ParseShader(string loc)
{
	ifstream stream(loc);
	
	enum ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ShaderType type = ShaderType::NONE;
	stringstream ss[2];

	string line;
	while (getline(stream, line))
	{
		if (line.find("#shader") != string::npos)
		{
			if (line.find("vertex") != string::npos)
			{
				type = VERTEX;
			}
			else if (line.find("fragment") != string::npos)
			{
				type = FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << endl;
		}
	}
	ParseReturn r;
	r.vertex = ss[0].str();
	r.fragment = ss[1].str();
	return r;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		cout << "Error!" << endl;
	}

	float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	ParseReturn r = ParseShader("Red.shader");
	 const char* VertexShader = r.vertex.c_str();
	 const char* FragmentShader = r.fragment.c_str();
	//cout << VertexShader << endl;
	//cout << FragmentShader << endl;

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//
	glShaderSource(vs, 1, &VertexShader, nullptr);
	glShaderSource(fs, 1, &FragmentShader, nullptr);
	glCompileShader(vs);
	glCompileShader(fs);
	GLuint program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
	glLinkProgram(program);
	glUseProgram(program);

	GLuint uloc = glGetUniformLocation(program, "u_Color");
	glUniform4f(uloc, 0, 0, 1, 1);

	VertexArray vao;
	VertexBufferLayout vbl;
	vbl.Push<float>(2, GL_FALSE);
	VertexBuffer vb(positions, sizeof(positions), GL_STATIC_DRAW);
	vb.Bind();
	//vao.AddBuffer(vb, vbl);
	//vao.Bind();
	unsigned int vao_t;
	glGenVertexArrays(1, &vao_t);
	glBindVertexArray(vao_t);
	

	IndexBuffer ib(indices, 6, GL_STATIC_DRAW); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);


	float increment = 0.01f;
	float red = 0.0f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		
		if (red <= 0)
			increment = 0.01f;
		if (red >= 1)
			increment = -0.01f;
		red += increment;
		glUseProgram(program);
		glUniform4f(uloc, red, 0, 0.5f, 1);
		ib.Bind();
		vao.Bind();
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indices);//problem

		/* Swap front and back buffers */
		glfwSwapBuffers(window);


		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}