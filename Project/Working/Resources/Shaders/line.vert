#version 460 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Colour;

out vec3 o_Colour;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	o_Colour = a_Colour;
	gl_Position = u_Projection * u_View * vec4(a_Position, 0, 1);
}