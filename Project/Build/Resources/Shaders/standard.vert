#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_UVs;
layout(location = 2) in vec4 a_Colour;

out vec2 o_UVs;
out vec4 o_Colour;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

uniform vec2 u_UVRatio = vec2(1.0, 1.0);
uniform vec2 u_UVOffset = vec2(0.0, 0.0);

uniform bool u_FlipX = false;
uniform bool u_FlipY = false;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 0.0, 1.0);

	o_UVs.x = (u_FlipX) ? ((1.0 - a_UVs.x) * u_UVRatio.x) + u_UVOffset.x : (a_UVs.x * u_UVRatio.x) + u_UVOffset.x;
	o_UVs.y = (u_FlipY) ? ((1.0 - a_UVs.y) * u_UVRatio.y) + u_UVOffset.y : (a_UVs.y * u_UVRatio.y) + u_UVOffset.y;

    o_Colour = a_Colour;
}