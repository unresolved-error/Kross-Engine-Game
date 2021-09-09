#version 460 core

out vec4 FragColour;

in vec3 o_Colour;

void main()
{
	FragColour = vec4(o_Colour, 1);
}