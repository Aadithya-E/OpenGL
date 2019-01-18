#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;

void main()
{
	gl_Position = pos;
}

#shader fragment
#version 330 core

uniform vec4 u_Color;

void main()
{
	gl_FragColor = u_Color;
}