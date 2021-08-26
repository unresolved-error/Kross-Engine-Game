/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "Sprite.h"
#include "TextureType.h"

#include "../../Debug.h"

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
			m_AtlasTexture			(nullptr),
			m_IgnoreTextureTypes	(std::vector<TextureType>()),
			m_TextureOffsets		(std::unordered_map<Texture*, Vector2>()),
			m_AttachedTextures		(std::vector<Texture*>()),
			m_SpriteAtlasUVs		(std::unordered_map<Sprite*, AtlasSpriteData>()),
			m_AttachedSprites		(std::vector<Sprite*>())
		{
			/* Add the Ignore Types. */
			m_IgnoreTextureTypes.push_back(TextureType::FontMap);
			m_IgnoreTextureTypes.push_back(TextureType::PerlinMap);
			m_IgnoreTextureTypes.push_back(TextureType::Engine);

			Debug::LogLine("Created Atlas!");
			/* NOTE! if you update this update the function GetIgnoreTextureTypes() ! */
		};
		~Atlas();

		Texture* m_AtlasTexture;
		
		// Identifies what types to ignore when adding textures to the Atlas. (THIS NEEDS TO BE SET MANUALLY)
		std::vector<TextureType> m_IgnoreTextureTypes;

		std::unordered_map<Texture*, Vector2> m_TextureOffsets;
		std::vector<Texture*> m_AttachedTextures;

		std::unordered_map<Sprite*, AtlasSpriteData> m_SpriteAtlasUVs;
		std::vector<Sprite*> m_AttachedSprites;

	protected:
		friend class BatchRenderer;
		friend class FileSystem;

		static std::vector<TextureType> GetIgnoreTextureTypes();

		// Sets the Texture.
		void SetTexture(Texture* texture) { m_AtlasTexture = texture; };

		// Gets the Texture.
		Texture* GetTexture() const { return m_AtlasTexture; };

		// Adds Sprite Data.
		void AttachSpriteData(Sprite* sprite, AtlasSpriteData data);

		// Adds the Texture Offset on the Atlas.
		void AttachTextureOffset(Texture* texture, Vector2 offset);

		// Check if the Texture should be Ignored.
		bool ShouldIgnoreTexture(Texture* texture);

		// Gets the Texture Offset.
		Vector2 GetTextureOffset(Texture* texture) { return m_TextureOffsets[texture]; };

	public:
		// Creates a Atlas from all existing textures.
		static Atlas* OnCreate(bool createNew = true);

		// Destroys the Atlas specified.
		static void OnDestroy(Atlas* atlas);

		// Gets the data for where abouts the Sprite sits on the Atlas.
		AtlasSpriteData GetSpriteData(Sprite* sprite) { return m_SpriteAtlasUVs[sprite]; };
	};
}