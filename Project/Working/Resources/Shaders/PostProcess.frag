#version 460 core

in vec2 uvs;

out vec4 FragColour;

uniform sampler2D u_Texture;

uniform float u_RenderTargetWidth = 1280.0;
uniform float u_RenderTargetHeight = 720.0;

void main()
{
	float pixel_w = 2;
	float pixel_h = 2;

	float dx = pixel_w * (1.0 / u_RenderTargetWidth);
    float dy = pixel_h * (1.0 / u_RenderTargetHeight);
    vec2 coord = vec2(dx * floor(uvs.x / dx),
                      dy * floor(uvs.y / dy));

	vec4 v_Colour = texture(u_Texture, coord); 
	vec4 v_ColourAbove = texture(u_Texture, vec2(coord.x, coord.y - (1.0 / 720.0)));
	vec4 v_ColourBellow = texture(u_Texture, vec2(coord.x, coord.y + (1.0 / 720.0)));

	if(v_Colour.a < 0.025)
	{
		discard;
	}

	vec4 colour = vec4(0.15, 0.08, 0.05, 1.0);
	//vec3 colour = vec3(1.0, 1.0, 1.0);
	if(v_ColourBellow.a >= 0.08)
	{
		// Accepted to be a middle Colour.

		if(v_Colour.b >= 0.3 && v_Colour.b < 0.8)
		{
			colour = vec4(0.56, 0.31, 0.20, 0.8);
		}

		else if(v_Colour.b >= 0.8 && v_Colour.b < 0.9)
		{
			colour = vec4(0.52, 0.28, 0.18, 0.85);
		}

		else if(v_Colour.b >= 0.9 && v_Colour.b < 0.95)
		{
			colour = vec4(0.48, 0.26, 0.17, 0.9);
		}

		else if(v_Colour.b >= 0.95 && v_Colour.b < 1.0)
		{
			colour = vec4(0.44, 0.24, 0.15, 0.95);
		}


	}
	//FragColour = vec4(0.5, coord.y * pixel_h ,coord.x * pixel_h, 1.0);
	// For those that go looking. ^
	FragColour = colour;
}