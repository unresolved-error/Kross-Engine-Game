#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_UVs;
layout(location = 2) in vec2 a_NUVs;
layout(location = 3) in vec2 a_SUVs;
layout(location = 4) in vec3 a_WorldNormal;
layout(location = 5) in vec4 a_Colour;

out vec2 o_UVs;
out vec4 o_Colour;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position = u_Projection * u_View * vec4(a_Position, 0.0, 1.0);

	o_UVs = a_UVs;
    o_Colour = a_Colour;
}