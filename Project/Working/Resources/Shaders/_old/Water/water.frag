#version 460 core

in vec4 o_VertColour;
in vec2 o_VertUVs;

//layout(location = 0) out vec4 o_OutputColour;
out vec4 o_OutputColour;

uniform vec4 u_Colour;

void main()
{	
	float distanceFromCentre = clamp(length(o_VertUVs - vec2(0.5, 0.5)) * 2.0, 0.0, 1.0);

	float intermediateVal = distanceFromCentre + 1.0;
	
	float intensity = 1.0 / (intermediateVal * intermediateVal) - 0.25;	//Note: Function peaks at 0.75 at centre of particle.\

	intensity = (intensity > .7) ? 1 : ((intensity > .5) ? .5 : ((intensity > .1) ? .25 : 0));


	o_OutputColour = vec4(u_Colour.xyz, intensity);
	//o_OutputColour = vec4(1, 1, /*distanceFromCentre < 0.1 ? 1.0 :*/ 1.0, 1);
}