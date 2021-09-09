#version 460 core


layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_Velocity;
layout(location = 2) in vec4 a_Colour;

uniform mat4 u_Projection;
uniform mat4 u_View;

out vec4 DropletColour;
out vec2 DropletVelocity;

void main()
{
	DropletColour = a_Colour;
	DropletVelocity = a_Velocity;
	gl_Position = u_Projection * u_View * vec4(a_Position, 0, 1);
}