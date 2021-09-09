#version 460 core


layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float u_HalfSize;	//The 'radius' of the quad.
uniform float u_InverseAspect;

out vec2 o_VertUVs;
out vec4 o_VertColour;
out vec2 o_VertVelocity;

in vec4 i_DropletColour[];
in vec2 i_DropletVelocity[];

void main()
{	
	gl_Position = gl_in[0].gl_Position - vec4(u_HalfSize * u_InverseAspect, -u_HalfSize, 0, 0);
	o_VertUVs = vec2(1.0, 0.0);
	o_VertColour = i_DropletColour[0];
	o_VertVelocity = i_DropletVelocity[0];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position - vec4(-u_HalfSize * u_InverseAspect, -u_HalfSize, 0, 0);
	o_VertUVs = vec2(0.0, 0.0);
	o_VertColour = i_DropletColour[0];
	o_VertVelocity = i_DropletVelocity[0];
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position - vec4(u_HalfSize * u_InverseAspect, u_HalfSize, 0, 0);
	o_VertUVs = vec2(1.0, 1.0);
	o_VertColour = i_DropletColour[0];
	o_VertVelocity = i_DropletVelocity[0];
	EmitVertex();

	gl_Position = gl_in[0].gl_Position - vec4(-u_HalfSize * u_InverseAspect, u_HalfSize, 0, 0);
	o_VertUVs = vec2(0.0, 1.0);
	o_VertColour = i_DropletColour[0];
	o_VertVelocity = i_DropletVelocity[0];
	EmitVertex();
	
	EndPrimitive();
}