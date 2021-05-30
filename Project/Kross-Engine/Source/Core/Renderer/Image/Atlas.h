/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "Sprite.h"
#include "TextureType.h"

namespace Kross
{
	struct KROSS_API AtlasSpriteData
	{
		AtlasSpriteData() :
			m_Offset	(Vector2(-1.0f)), 
			m_Ratio		(Vector2(-1.0f))
		{};

		AtlasSpriteData(Vector2 offset, Vector2 ratio) : 
			m_Offset	(offset), 
			m_Ratio		(ratio)
		{};

		Vector2 m_Offset;
		Vector2 m_Ratio;
	};

	class KROSS_API Atlas
	{
	private:
		Atlas() : 
			p_AtlasTexture			(nullptr),
			m_IgnoreTextureTypes	(List<TextureType>()),
			m_TextureOffsets		(std::unordered_map<Texture*, Vector2>()),
			m_SpriteAtlasUVs		(std::unordered_map<Sprite*, AtlasSpriteData>())
		{
			/* Add the Ignore Types. */
			m_IgnoreTextureTypes.push_back(TextureType::FontMap);
			m_IgnoreTextureTypes.push_back(TextureType::PerlinMap);
		};
		~Atlas();

		Texture* p_AtlasTexture;

		// Identifies what types to ignore when adding textures to the Atlas. (THIS NEEDS TO BE SET MANUALLY)
		List<TextureType> m_IgnoreTextureTypes;

		std::unordered_map<Texture*, Vector2> m_TextureOffsets;
		std::unordered_map<Sprite*, AtlasSpriteData> m_SpriteAtlasUVs;

	protected:
		friend class BatchRenderer;

		// Sets the Texture.
		void SetTexture(Texture* texture) { p_AtlasTexture = texture; };

		// Sets Sprite Data.
		void SetSpriteData(Sprite* sprite, AtlasSpriteData data) { m_SpriteAtlasUVs[sprite] = data; };

		// Sets the Texture Offset on the Atlas.
		void SetTextureOffset(Texture* texture, Vector2 offset) { m_TextureOffsets[texture] = offset; };

		// Check if the Texture should be Ignored.
		bool ShouldIgnoreTexture(Texture* texture);

		// Gets the Texture.
		Texture* GetTexture() const { return p_AtlasTexture; };

		// Gets the Texture Offset.
		Vector2 GetTextureOffset(Texture* texture) { return m_TextureOffsets[texture]; };

	public:
		// Creates a Atlas from all existing textures.
		static Atlas* OnCreate();

		// Destroys the Atlas specified.
		static void OnDestroy(Atlas* atlas);

		// Gets the data for where abouts the Sprite sits on the Atlas.
		AtlasSpriteData GetSpriteData(Sprite* sprite) { return m_SpriteAtlasUVs[sprite]; };
	};
}