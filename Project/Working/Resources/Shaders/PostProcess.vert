#version 460 core

layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 UVs;
layout (location = 2) in vec4 Colour;

out vec2 uvs;

void main()
{
	uvs = vec2(UVs.x, 1.0 - UVs.y);
	gl_Position = vec4(Position, 0, 1);
}