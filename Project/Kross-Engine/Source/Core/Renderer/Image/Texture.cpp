/*
	Author: Deklyn Palmer.
	Editors:
		- Deklyn Palmer.
*/

#include "Texture.h"

#include "stb_image/stb_image.h"

#include "GL/glew.h"

namespace Kross
{
	Texture::Texture()
		: m_TextureID(0), m_Slot(0), m_Width(0), m_Height(0), m_BPP(0), m_PixelData(nullptr), m_Name(""), m_Filepath("")
	{
		glGenTextures(1, &m_TextureID);
	}

	Texture::~Texture()
	{
		if(m_TextureID != NULL)
			glDeleteTextures(1, &m_TextureID);

		if (m_PixelData)
			stbi_image_free(m_PixelData);
	}

	void Texture::Attach()
	{
		glEnable(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::Detach()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture* Texture::OnCreate(const std::string& filepath, const std::string& name)
	{
		/* Flips the image vertically on load. */
		stbi_set_flip_vertically_on_load(1);

		/* Local variables for image data. */
		int width, height, bpp;

		/* Creation of Texture. */
		Texture* texture = new Texture();
		texture->SetName(name);
		texture->SetFilepath(filepath);

		/* Core Texture data. */
		texture->SetPixelData(stbi_load(filepath.c_str(), &width, &height, &bpp, 4));
		texture->SetWidth(width);
		texture->SetHeight(height);
		texture->SetBitsPerPixel(bpp);

		/* Seeing if the Texture was created properly. */
		if (texture->GetTextureID() != NULL)
		{
			texture->Attach();

			/* Making the Texture pixel perfect. */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			/* Setting it to repeat. */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			/* Set the data. */
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->GetPixelData());

			texture->Detach();

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
		Texture* texture = new Texture();
		texture->SetName(name);

		/* Core Texture data. */
		texture->SetPixelData(data);
		texture->SetWidth(width);
		texture->SetHeight(height);

		/* Seeing if the Texture was created properly. */
		if (texture->GetTextureID() != NULL)
		{
			texture->Attach();

			/* Making the Texture pixel perfect. */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			/* Set the data. */
			glTexImage2D(GL_TEXTURE_2D, 0, internal, texture->GetWidth(), texture->GetHeight(), 0, format, type, texture->GetPixelData());

			texture->Detach();

			/* Return the created texture. */
			return texture;
		}

		/* Couldn't create the Texture. */
		delete texture;
		return nullptr;
	}

	void Texture::OnDestroy(Texture* texture)
	{
		/* Safe programming, not really needed but good to have. */
		if(texture)
			texture->~Texture();
	}
}