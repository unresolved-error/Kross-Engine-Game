#version 460 core

out vec4 a_FragColour;

in vec2 o_UVs;
in vec4 o_Colour;

uniform sampler2D u_Texture;
uniform vec4 u_Colour = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
	vec4 texColour = texture(u_Texture, o_UVs);
	a_FragColour = (o_Colour * u_Colour) * texColour; 
}