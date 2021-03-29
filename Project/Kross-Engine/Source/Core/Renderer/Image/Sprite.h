/*
	Author: Deklyn Palmer.
	Editors:
		- Deklyn Palmer.
*/

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
			:m_Texture(nullptr), m_Width(0), m_Height(0), m_UVOffset(Vector2(0.0f,0.0f)), m_UVRatio(Vector2(1.0f, 1.0f)), m_Name(""), m_Geometry(new Geometry())
		{};
		~Sprite();

		Texture* m_Texture;
		int m_Width, m_Height;
		
		// (SHADER USE ONLY)
		Vector2 m_UVOffset, m_UVRatio;

		std::string m_Name;

		Geometry* m_Geometry;

	protected:
		friend class Application;

		// Get the Sprite UV Ratio. (SHADER USE ONLY)
		const Vector2 GetUVRatio() const { return m_UVRatio; };

		// Get the Sprite UV Offset. (SHADER USE ONLY)
		const Vector2 GetUVOffset() const { return m_UVOffset; };

		// Sets the Sprite Name.
		void SetName(const std::string& name) { m_Name = name; };

		// Sets the Sprite Width.
		void SetWidth(int width) { m_Width = width; };

		// Sets the Sprite Height.
		void SetHeight(int height) { m_Height = height; };

		// Sets the Sprite Texture.
		void SetTexture(Texture* texture) { m_Texture = texture; };

		// Sets the Sprite Geometry Data.
		void AttachGeometryData();

		// Renders the Sprite.
		void OnRender();

	public:
		// Creates a Sprite from a Texture.
		static Sprite* OnCreate(Texture* texture, int width, int height, const std::string& name);

		// Destroys the Sprite Specified.
		static void OnDestroy(Sprite* sprite);

		// Gets the Sprite Name.
		const std::string GetName() const { return m_Name; };

		// Gets the Sprite Width.
		const int GetWidth() const { return m_Width; };

		// Gets the Sprite Height.
		const int GetHeight() const { return m_Height; };

	};
}