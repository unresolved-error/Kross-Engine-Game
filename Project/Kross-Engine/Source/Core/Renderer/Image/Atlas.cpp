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
	Atlas* Atlas::OnCreate()
	{
		/* Grabs all of the Textures. */
		List<Texture*> textures = ResourceManager::GetTextures();

		/* Create an Empty Atlas. */
		Atlas* atlas = new Atlas();

		/* Create a empty Atlas Texture. */
		Texture* atlasTexture = Texture::OnCreateAtlas();

		/* Variables. */
		const int width = 8192;
		const int height = 8192;

		/* Creating a fresh block of Data for the Texture. */
		unsigned char* data = new unsigned char[width * height * 4];
		memset(data, (unsigned char)0, width * height * 4);

		/* Iterate theough every Texture loaded in. */
		for (int i = 0; i < textures.size(); i++)
		{
			/* Current Texture we are looking at. */
			Texture* texture = textures[i];

			/* Find out where it will sit in the Atlas. */
			int yOffset = 0;
			for (int j = i - 1; j >= 0; j--)
				yOffset += textures[j]->GetHeight();

			/* Record the Texture Offset for proper uv calculations. */
			atlas->m_TextureOffsets[texture] = Vector2(0.0f, yOffset);

			/* Go through the Texture Pixels. */
			for (int y = texture->GetHeight() - 1; y >= 0; y--)
			{
				for (int x = 0; x < texture->GetWidth(); x++)
				{
					/* Grab the Current Pixel. */
					Colour pixelColour = texture->GetPixel(x, y);
					
					/* Write the Pixel Data from bottom to top of the texture. */
					data[(x + (((yOffset + (texture->GetHeight() - y))) * width)) * 4 + 0] = (unsigned char)((int)(pixelColour.r * 255)); /* R. */
					data[(x + (((yOffset + (texture->GetHeight() - y))) * width)) * 4 + 1] = (unsigned char)((int)(pixelColour.g * 255)); /* G. */
					data[(x + (((yOffset + (texture->GetHeight() - y))) * width)) * 4 + 2] = (unsigned char)((int)(pixelColour.b * 255)); /* B. */
					data[(x + (((yOffset + (texture->GetHeight() - y))) * width)) * 4 + 3] = (unsigned char)((int)(pixelColour.a * 255)); /* A. */
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

		for (int i = 0; i < sprites.size(); i++)
		{
			/* UV Ratio Variable. */
			Vector2 ratio = Vector2(0.0f);
			ratio.x = (float)sprites[i]->GetWidth() / (float)atlasTexture->GetWidth();
			ratio.y = (float)sprites[i]->GetHeight() / (float)atlasTexture->GetHeight();

			/* UV Offset Variable. */
			Vector2 offset = Vector2(0.0f);
			offset.x = (float)(atlas->m_TextureOffsets[sprites[i]->GetTexture()].x + sprites[i]->GetPixelOffset().x) / (float)atlasTexture->GetWidth();
			offset.y = (float)(atlasTexture->GetHeight() - sprites[i]->GetHeight() - (int)(atlas->m_TextureOffsets[sprites[i]->GetTexture()].y + sprites[i]->GetPixelOffset().y)) / (float)atlasTexture->GetHeight();

			/* Create a Data Pack. */
			AtlasSpriteData spriteData = AtlasSpriteData(offset, ratio);

			/* Attach this Data. */
			atlas->m_SpriteAtlasUVs[sprites[i]] = spriteData;
		}
		
		/* Returns the new Atlas. */
		return atlas;
	}
}