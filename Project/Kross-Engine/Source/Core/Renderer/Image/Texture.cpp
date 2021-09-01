/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Texture.h"

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"

#include "../../Manager/ResourceManager.h"

#include "../../Math/Random.h"

#include "fnl/FastNoiseLite.h"

#include "GL/glew.h"

namespace Kross
{
	Texture::Texture() : 
		m_TextureID	(0), 
		m_Slot		(0),
		m_Width		(0),
		m_Height	(0),
		m_BPP		(0), 
		m_Name		(""), 
		m_Filepath	(""),
		m_PixelData	(nullptr),
		m_Type		(TextureType::TextureMap)
	{
		glGenTextures(1, &m_TextureID);
	}

	Texture::~Texture()
	{
		if(m_TextureID != NULL)
			glDeleteTextures(1, &m_TextureID);

		if (m_PixelData)
		{
			delete[] m_PixelData;
		}
	}

	Colour Texture::GetPixel(int x, int y)
	{
		/* Create an Empty Colour. */
		Colour colour = Colour(1.0f);

		if (x < 0 || x >= m_Width)
			return colour;

		else if (y < 0 || y >= m_Height)
			return colour;

		/* Set the Colour data from the Pixel. */
		colour.r = (float)((int)m_PixelData[(x + (y * m_Width)) * 4 + 0]) / 255.0f;
		colour.g = (float)((int)m_PixelData[(x + (y * m_Width)) * 4 + 1]) / 255.0f;
		colour.b = (float)((int)m_PixelData[(x + (y * m_Width)) * 4 + 2]) / 255.0f;
		colour.a = (float)((int)m_PixelData[(x + (y * m_Width)) * 4 + 3]) / 255.0f;

		/* Return the Colour. */
		return colour;
	}

	void Texture::SetPixel(int x, int y, Colour colour)
	{
		/* If the x and y are outside of the bounds of the Texture return. */
		if (x < 0 || x >= m_Width)
			return;

		else if (y < 0 || y >= m_Height)
			return;

		/* If not, set the Pixel Data. */
		m_PixelData[(x + (y * m_Width)) * 4 + 0] = (unsigned char)((int)(colour.r * 255));
		m_PixelData[(x + (y * m_Width)) * 4 + 1] = (unsigned char)((int)(colour.g * 255));
		m_PixelData[(x + (y * m_Width)) * 4 + 2] = (unsigned char)((int)(colour.b * 255));
		m_PixelData[(x + (y * m_Width)) * 4 + 3] = (unsigned char)((int)(colour.a * 255));
	}

	void Texture::OnCreateImageCanvas(int width, int height, int bpp)
	{
		m_Width = width;
		m_Height = height;
		m_BPP = bpp;

		if (m_PixelData)
			delete[] m_PixelData;

		m_PixelData = KROSS_NEW unsigned char(width * height * bpp);
	}

	void Texture::Finalise()
	{
		/* Seeing if the Texture was created properly. */
		if (GetTextureID() != NULL)
		{
			Bind();

			/* Making the Texture pixel perfect. */
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

			/* Setting it to repeat. */
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			/* Set the data. */
			OPENGL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, GetWidth(), GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, GetPixelData()));

			UnBind();
		}

		/* If not, report that it wasn't. */
		else
			std::cout << "Texture wasn't able to be finalised!" << std::endl;
	}

	void Texture::Bind()
	{
		/* Something is broken. This may be needed else where. */
		//if (glIsEnabled(GL_TEXTURE_2D) == GL_FALSE)
		//{
		//	OPENGL_CHECK(glEnable(GL_TEXTURE_2D));
		//}

		/* Bind the Texture. */
		OPENGL_CHECK(glActiveTexture(GL_TEXTURE0 + m_Slot));
		OPENGL_CHECK(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	}

	void Texture::UnBind()
	{
		OPENGL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
	}

	Texture* Texture::OnCreate(const std::string& filepath, const std::string& name, TextureType type)
	{
		/* Flips the image vertically on load. */
		stbi_set_flip_vertically_on_load(1);

		/* Local variables for image data. */
		int width, height, bpp;

		/* Creation of Texture. */
		Texture* texture = KROSS_NEW Texture();
		texture->SetName(name);
		texture->SetFilepath(filepath);
		texture->SetType(type);

		/* Core Texture data. */
		texture->SetPixelData(stbi_load(filepath.c_str(), &width, &height, &bpp, 4));
		texture->SetWidth(width);
		texture->SetHeight(height);
		texture->SetBitsPerPixel(bpp);

		/* Seeing if the Texture was created properly. */
		if (texture->GetTextureID() != NULL)
		{
			texture->Bind();

			/* Making the Texture pixel perfect. */
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

			/* Setting it to repeat. */
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			/* Set the data. */
			OPENGL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->GetPixelData()));

			texture->UnBind();

			/* Add it to the  Resource Manager. */
			ResourceManager::AttachResource<Texture>(texture);

			/* Return the created texture. */
			return texture;
		}

		/* Couldn't create the Texture. */
		delete texture;
		return nullptr;
	}

	Texture* Texture::OnCreate(int width, int height, int seed, float scale, int octaves, float persistance, float lacunarity, Vector2 offset, PerlinNormaliseMode mode, const std::string& name)
	{
		/* Creation of Texture. */
		Texture* texture = KROSS_NEW Texture();
		texture->SetName(name);
		texture->SetType(TextureType::PerlinMap);

		/* Core Texture data. */
		texture->SetWidth(width); 
		texture->SetHeight(height);

		/* ----- Fast Noise Settings ----- */
		FastNoiseLite noise;
		noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
		noise.SetSeed(seed);
		noise.SetFrequency(scale / 1000.0f);

		noise.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);
		noise.SetFractalOctaves((float)octaves);
		noise.SetFractalLacunarity(lacunarity);
		noise.SetFractalGain(0.5f);
		noise.SetFractalWeightedStrength(0.0f);
		noise.SetFractalPingPongStrength(2.0f);

		noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_EuclideanSq);
		noise.SetCellularJitter(1.0f);

		noise.SetDomainWarpType(FastNoiseLite::DomainWarpType::DomainWarpType_OpenSimplex2);
		noise.SetDomainWarpAmp(30.0f);
		/* ------------------------------- */

		/* Create new Texture Data. */
		unsigned char* data = KROSS_NEW unsigned char[width * height * 4];

		/* Go through Texture Pixels. */
		for(int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				float noiseSample = noise.GetNoise((float)x + offset.x, float(y) + offset.y);
				float actualNoiseSample = ((1.0f + noiseSample) / 2.0f >= 0.5f) ? 1.0f : 0.0f;
				//float actualNoiseSample = (1.0f + noiseSample) / 2.0f;

				/* Set Pixel Data. */
				data[(x + (y * width)) * 4 + 0] = (unsigned char)((int)(actualNoiseSample * 255)); /* R. */
				data[(x + (y * width)) * 4 + 1] = (unsigned char)((int)(actualNoiseSample * 255)); /* G. */
				data[(x + (y * width)) * 4 + 2] = (unsigned char)((int)(actualNoiseSample * 255)); /* B. */
				data[(x + (y * width)) * 4 + 3] = UCHAR_MAX;									   /* A. */
			}

		/* Set Texture data. */
		texture->SetPixelData(data);

		/* Seeing if the Texture was created properly. */
		if (texture->GetTextureID() != NULL)
		{
			texture->Bind();

			/* Making the Texture pixel perfect. */
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

			/* Setting it to repeat. */
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			/* Set the data. */
			OPENGL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->GetPixelData()));

			texture->UnBind();

			/* Add it to the Resource Manager. */
			ResourceManager::AttachResource<Texture>(texture);

			/* Return the created texture. */
			return texture;
		}

		/* Couldn't create the Texture. */
		delete texture;
		return nullptr;
	}

	Texture* Texture::OnCreate(int width, int height, unsigned char* data, int internal, int format, GLenum type, const std::string& name)
	{
		/* Creation of Texture. */
		Texture* texture = KROSS_NEW Texture();
		texture->SetName(name);
		texture->SetType(TextureType::TextureMap);

		/* Core Texture data. */
		texture->SetPixelData(data);
		texture->SetWidth(width);
		texture->SetHeight(height);

		/* Seeing if the Texture was created properly. */
		if (texture->GetTextureID() != NULL)
		{
			texture->Bind();

			/* Making the Texture pixel perfect. */
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

			/* Setting it to repeat. */
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			OPENGL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			/* Set the data. */
			OPENGL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internal, texture->GetWidth(), texture->GetHeight(), 0, format, type, texture->GetPixelData()));

			texture->UnBind();

			/* Return the created texture. */
			return texture;
		}

		/* Couldn't create the Texture. */
		delete texture;
		return nullptr;
	}

	Texture* Texture::OnCreateAtlas()
	{
		/* return a blank Texture for the Atlas to mess around with. */
		return KROSS_NEW Texture();
	}

	void Texture::OnDestroy(Texture* texture)
	{
		/* Safe programming, not really needed but good to have. */
		if(texture)
			delete texture;
	}
}