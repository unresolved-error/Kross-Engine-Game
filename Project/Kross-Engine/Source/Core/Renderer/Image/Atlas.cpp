/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Atlas.h"

#include "stb_image/stb_image_write.h"

#include "../../Manager/ResourceManager.h"

namespace Kross
{
	Atlas::~Atlas()
	{
		Texture::OnDestroy(p_AtlasTexture);

		for (int i = 0; i < m_AttachedTextures.size(); i++)
			m_AttachedTextures[i] = nullptr;

		for (int i = 0; i < m_AttachedSprites.size(); i++)
			m_AttachedSprites[i] = nullptr;
	}

	Atlas* Atlas::OnCreate(bool createNew)
	{
		/* Create an Empty Atlas. */
		Atlas* atlas = KROSS_ALLOCATION_REPORT(Atlas());

		/* If we don't need to create a fresh one. */
		if (!createNew)
			return atlas;

		/* Grabs all of the Textures. */
		List<Texture*> textures = ResourceManager::GetTextures();

		/* Create a empty Atlas Texture. */
		Texture* atlasTexture = Texture::OnCreateAtlas();

		/* Variables. */
		const int width = 4096;
		const int height = 4096;

		/* Creating a fresh block of Data for the Texture. */
		unsigned char* data = KROSS_ALLOCATION_REPORT(unsigned char[width * height * 4]);
		memset(data, (unsigned char)0, width * height * 4);

		/* Iterate theough every Texture loaded in. */
		for (int i = 0; i < textures.size(); i++)
		{
			/* Current Texture we are looking at. */
			Texture* texture = textures[i];

			/* If we need to ignore, go to the next texture in the list. */
			if (atlas->ShouldIgnoreTexture(texture))
				continue;
		
			/* Find out where it will sit in the Atlas. */
			int yOffset = 0;
			for (int j = i - 1; j >= 0; j--)
			{
				/* If this  is  a texture that should not be Ignored. */
				if (!atlas->ShouldIgnoreTexture(textures[j]))
					yOffset += textures[j]->GetHeight(); /* Collectively add the Height. */
			}
		
			/* Record the Texture Offset for proper uv calculations. */
			atlas->AttachTextureOffset(texture, Vector2(0.0f, yOffset));
		
			/* Quick Variable. */
			int textureHeight = texture->GetHeight();
			int textureWidth = texture->GetWidth();

			/* Go through the Texture Pixels. */
			for (int y = textureHeight - 1; y >= 0; y--)
			{
				for (int x = 0; x < textureWidth; x++)
				{
					/* Grab the Current Pixel. */
					Colour pixelColour = texture->GetPixel(x, y);
					
					/* Write the Pixel Data from bottom to top of the texture. */
					data[(x + (((yOffset + (textureHeight - y))) * width)) * 4 + 0] = (unsigned char)((int)(pixelColour.r * 255)); /* R. */
					data[(x + (((yOffset + (textureHeight - y))) * width)) * 4 + 1] = (unsigned char)((int)(pixelColour.g * 255)); /* G. */
					data[(x + (((yOffset + (textureHeight - y))) * width)) * 4 + 2] = (unsigned char)((int)(pixelColour.b * 255)); /* B. */
					data[(x + (((yOffset + (textureHeight - y))) * width)) * 4 + 3] = (unsigned char)((int)(pixelColour.a * 255)); /* A. */
				}
			}
		}

		/* Write the Image to disk. */
		stbi_flip_vertically_on_write(0);
		stbi_write_png("Resources/Atlas/Atlas.png", width, height, 4, &data[0], 4 * width);

		/* set basic Texture Properties. */
		atlasTexture->SetName("Atlas");
		atlasTexture->SetWidth(width);
		atlasTexture->SetHeight(height);

		/* Set the Pixel Data. */
		atlasTexture->SetPixelData(data);

		/* Finalise the Data. */
		atlasTexture->OnFinalise();

		/* Set the Texture Atlas. */
		atlas->SetTexture(atlasTexture);

		/* Gather Created Sprites. */
		List<Sprite*> sprites = ResourceManager::GetSprites();

		/* Go through all of the Sprites. */
		for (int i = 0; i < sprites.size(); i++)
		{
			/* Quick Variable for the Texture. */
			Texture* spriteTexture = sprites[i]->GetTexture();

			/* If the Texture that this sprite origniated from is ignored don't add it to the sprite data. */
			if (atlas->ShouldIgnoreTexture(spriteTexture))
				continue;

			/* Quick Variables. */
			Vector2 spriteTextureOffset = atlas->GetTextureOffset(spriteTexture);
			Vector2 spritePixelOffset = sprites[i]->GetPixelOffset();

			int spriteWidth = sprites[i]->GetWidth();
			int spriteHeight = sprites[i]->GetHeight();


			/* UV Ratio Variable. */
			Vector2 ratio = Vector2(0.0f);
			ratio.x = (float)spriteWidth / (float)width;
			ratio.y = (float)spriteHeight / (float)height;

			/* UV Offset Variable. */
			Vector2 offset = Vector2(0.0f);
			offset.x = (float)(spriteTextureOffset.x + spritePixelOffset.x) / (float)width;
			offset.y = (float)(height - spriteHeight - (int)(spriteTextureOffset.y + spritePixelOffset.y)) / (float)height;

			/* Create a Data Pack. */
			AtlasSpriteData spriteData = AtlasSpriteData(offset, ratio);

			/* Attach this Data. */
			atlas->AttachSpriteData(sprites[i], spriteData);
		}
		
		/* Returns the new Atlas. */
		return atlas;
	}

	void Atlas::OnDestroy(Atlas* atlas)
	{
		/* Safe programming. Not really needed, but good to have. */
		if (atlas)
			delete atlas;
	}

	List<TextureType> Atlas::GetIgnoreTextureTypes()
	{
		List<TextureType> types = List<TextureType>();

		types.push_back(TextureType::FontMap);
		types.push_back(TextureType::PerlinMap);
		types.push_back(TextureType::Engine);

		return types;
	}

	void Atlas::AttachSpriteData(Sprite* sprite, AtlasSpriteData data)
	{
		m_SpriteAtlasUVs.emplace(sprite, data);
		m_AttachedSprites.push_back(sprite);
	}

	void Atlas::AttachTextureOffset(Texture* texture, Vector2 offset)
	{
		m_TextureOffsets.emplace(texture, offset);
		m_AttachedTextures.push_back(texture);
	}

	bool Atlas::ShouldIgnoreTexture(Texture* texture)
	{
		/* Get the Type of Texture it is. */
		TextureType type = texture->GetType();

		/* Check if it is a Texture that should ignored. */
		for (int i = 0; i < m_IgnoreTextureTypes.size(); i++)
		{
			/* If the Texture is one of the Ignored Types. */
			if (m_IgnoreTextureTypes[i] == type)
			{
				/* We should ignore it. */
				return true;
			}
		}

		/* Return false if no Type was matched. */
		return false;
	}
}