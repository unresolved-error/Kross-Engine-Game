#version 460 core

out vec4 a_FragColour;

in vec2 o_UVs;
in vec4 o_Colour;

uniform sampler2D u_Atlas;

void main()
{
	vec4 texColour = texture(u_Atlas, vec2(o_UVs.x, (1.0 - o_UVs.y) + (2.0 / 8192)));
	a_FragColour = o_Colour * texColour; 
}