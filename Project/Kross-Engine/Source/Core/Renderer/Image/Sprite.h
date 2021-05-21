/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#ifndef BASE_SPRITE_WIDTH_AND_HEIGHT
#define BASE_SPRITE_WIDTH_AND_HEIGHT 64
#endif // Base Sprite Width and Height.

#pragma once

#include "../../Core.h"

#include "Texture.h"
#include "../Geometry.h"

namespace Kross
{
	class KROSS_API Sprite
	{
	private:
		Sprite()
			: p_Texture(nullptr), 
			m_Width(0), 
			m_Height(0), 
			m_UVOffset(Vector2(0.0f,0.0f)),
			m_UVRatio(Vector2(1.0f, 1.0f)),
			m_Name(""),
			m_Geometry(nullptr),
			m_PixelOffset(Vector2(0.0f))
		{
			static int count = 0;
			std::cout << "Creating sprite " << count << std::endl;
			count++;
		};
		~Sprite();

		Texture* p_Texture;
		int m_Width, m_Height;
		
		// (SHADER USE ONLY)
		Vector2 m_UVOffset, m_UVRatio;

		// (FOR THE ATLAS)
		Vector2 m_PixelOffset;

		std::string m_Name;

		Geometry* m_Geometry;

	protected:
		friend class SpriteRenderer;
		friend class Character;
		friend class Atlas;
		friend class Batch;

		// Get the Sprite UV Ratio. (SHADER USE ONLY)
		const Vector2 GetUVRatio() const { return m_UVRatio; };

		// Get the Sprite UV Offset. (SHADER USE ONLY)
		const Vector2 GetUVOffset() const { return m_UVOffset; };

		// Get the Pixel Offset of the Orignial Texture. (ATLAS USE ONLY)
		const Vector2 GetPixelOffset() const { return m_PixelOffset; }

		// Gets the Sprite Geometry.
		Geometry* GetGeometry() const { return m_Geometry; };

		// Sets the Sprite Name.
		void SetName(const std::string& name) { m_Name = name; };

		// Sets the Sprite Width.
		void SetWidth(int width) { m_Width = width; };

		// Sets the Sprite Height.
		void SetHeight(int height) { m_Height = height; };

		// Sets the Sprite Texture.
		void SetTexture(Texture* texture) { p_Texture = texture; };

		// Sets the Pixel Offset. (ATLAS USE ONLY)
		void SetPixelOffset(Vector2 offset) { m_PixelOffset = offset; };

		// Set the Sprite UV Ratio. (SHADER USE ONLY)
		void SetUVRatio(const Vector2 ratio) { m_UVRatio = ratio; };

		// Set the Sprite UV Offset. (SHADER USE ONLY)
		void SetUVOffset(const Vector2 offset) { m_UVOffset = offset; };

		// Sets the Sprite Geometry Data.
		void AttachGeometryData();

		// Renders the Sprite.
		void OnRender();

	public:
		// Creates a Sprite from a Texture.
		static Sprite* OnCreate(Texture* texture, int width, int height, const std::string& name);

		/** 
			Creates a Sprite from a Texture with specific co-ordinates. (USE IF YOU KNOW WHAT YOUR DOING)
			 - texture: The Texture that will be used for the Sprite.
			 - width: Width of the Sprite.
			 - height: Height of the Sprite.
			 - offset: The Offset in PIXELS to the section of the Texture you wish to render. (ORIGIN IS AT TOP LEFT OF TEXTURE)
			 - name: Name of the Sprite.
		*/
		static Sprite* OnCreate(Texture* texture, int width, int height, Vector2 offset, const std::string& name);

		/**
			Creates a Sprite Set from a Texture with a fixed width and height. (FONT USE ONLY)
			 - texture: The Texture that the Font will be using.
			 - width: The Width of the Font Characters.
			 - height: The Height of the Font Characters.
		*/
		static List<Sprite*> OnCreate(Texture* texture, int width, int height);

		// Destroys the Sprite Specified.
		static void OnDestroy(Sprite* sprite);

		// Gets the Sprite Name.
		const std::string GetName() const { return m_Name; };

		// Gets the Sprite Width.
		const int GetWidth() const { return m_Width; };

		// Gets the Sprite Height.
		const int GetHeight() const { return m_Height; };

		// Gets the  Sprite Texture.
		Texture* GetTexture() const { return p_Texture; };

	};
}