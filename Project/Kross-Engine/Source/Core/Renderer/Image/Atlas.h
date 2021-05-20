/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "Sprite.h"

namespace Kross
{
	struct KROSS_API AtlasSpriteData
	{
		AtlasSpriteData()
			: m_Offset(Vector2(-1.0f)), m_Ratio(Vector2(-1.0f))
		{};

		AtlasSpriteData(Vector2 offset, Vector2 ratio)
			: m_Offset(offset), m_Ratio(ratio)
		{};

		Vector2 m_Offset;
		Vector2 m_Ratio;
	};

	class KROSS_API Atlas
	{
	private:
		Atlas()
			: p_AtlasTexture(nullptr), m_TextureOffsets(std::unordered_map<Texture*, Vector2>()), m_SpriteAtlasUVs(std::unordered_map<Sprite*, AtlasSpriteData>())
		{};
		~Atlas();

		Texture* p_AtlasTexture;

		std::unordered_map<Texture*, Vector2> m_TextureOffsets;
		std::unordered_map<Sprite*, AtlasSpriteData> m_SpriteAtlasUVs;

	protected:
		friend class BatchRenderer;

		// Sets the Texture.
		void SetTexture(Texture* texture) { p_AtlasTexture = texture; };

		// Gets the Texture.
		Texture* GetTexture() const { return p_AtlasTexture; };

	public:
		// Creates a Atlas from all existing textures.
		static Atlas* OnCreate();

		// Destroys the Atlas specified.
		static void OnDestroy(Atlas* atlas);

		// Gets the data for where abouts the Sprite sits on the Atlas.
		AtlasSpriteData GetSpriteData(Sprite* sprite) { return m_SpriteAtlasUVs[sprite]; };
	};
}