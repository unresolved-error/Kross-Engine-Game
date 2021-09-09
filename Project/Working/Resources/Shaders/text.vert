#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_UVs;
layout(location = 2) in vec4 a_Colour;

out vec2 o_UVs;
out vec4 o_Colour;

uniform mat4 u_Projection;
uniform mat4 u_View;

uniform bool u_InWorldSpace = true;

void main()
{
    /* If in world space draw as if it were and Object, if not draw straight to screen space. */
    gl_Position = (u_InWorldSpace) ? u_Projection * u_View * vec4(a_Position, 0.0, 1.0) : u_Projection * vec4(a_Position, 0.0, 1.0);

	o_UVs.x = a_UVs.x;
	o_UVs.y = a_UVs.y;

    o_Colour = a_Colour;
}