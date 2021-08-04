/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "TextureType.h"

#include "GL/glew.h"

namespace Kross
{
	// Used EXPLICITLY for the creation of a Perlin Noise Texture.
	enum class KROSS_API PerlinNormaliseMode
	{
		Local,
		Global,
	};

	class KROSS_API Texture
	{
	private:
		// Used for the creation of Perlin Noise.
		struct KROSS_API Pixel
		{
			unsigned char r, g, b, a;
		};

		Texture();
		~Texture();

		unsigned int m_TextureID;
		unsigned int m_Slot;

		int m_Width, m_Height;

		/**	
			Bits per Pixel.
			 - Never really used. Only for the creation of Textures.
		*/
		int m_BPP;

		unsigned char* p_PixelData;

		std::string m_Name, m_Filepath;

		TextureType m_Type;

	protected:
		friend class FrameBuffer;
		friend class Atlas;
		friend class FileSystem;

		/* Creates a Blank Texture. (ATLAS) */
		static Texture* OnCreateAtlas();

		// Gets the Texture PixelData.
		inline unsigned char* GetPixelData() const { return p_PixelData; };

		// Sets the Texture Name.
		void SetName(const std::string& name) { m_Name = name; };

		// Sets the Texture Width.
		void SetWidth(int width) { m_Width = width; };

		// Sets the Texture Height.
		void SetHeight(int height) { m_Height = height; };

		// Sets the Texture Filepath.
		void SetFilepath(const std::string& filepath) { m_Filepath = filepath; };

		// Sets the Texture Bits per Pixel.
		void SetBitsPerPixel(int bpp) {m_BPP = bpp; };

		// Sets the Texture Pixel Data.
		void SetPixelData(unsigned char* data) { p_PixelData = data; };

		// Sets the Texture Type.
		void SetType(TextureType type) { m_Type = type; };

		// Gets a Colour of the Pixel at a given co-ordinate.
		Colour GetPixel(int x, int y);

		// Sets the Pixel Colour at a given co-ordinate.
		void SetPixel(int x, int y, Colour colour);

		// Creates a Canvas for the Data to be placed in. (ATLAS)
		void OnCreateImageCanvas(int width, int height, int bpp = 4);

		// Finalises the Data for the Graphics Card. (ATLAS)
		void OnFinalise();
		
	public:
		// Binds the Texture to the Texture Slot.
		void Attach();
		
		// Un Binds all Textures.
		static void Detach();

		// Gets the Texture ID. (USE RARELY)
		inline const unsigned int GetTextureID() const { return m_TextureID; };

		// Gets the Texture Name.
		const std::string GetName() const { return m_Name; };

		// Gets the Texture Width.
		inline const int GetWidth() const { return m_Width; };

		// Gets the texture Height.
		inline const int GetHeight() const { return m_Height; };

		// Gets the Texture Slot.
		const unsigned int GetSlot() const { return m_Slot; };

		// Gets the Texture Type.
		TextureType GetType() const { return m_Type; };

		// Sets the Texture Slot.
		void SetSlot(unsigned int slot = 0) { m_Slot = slot; };

		// Creates a Texture through file location.
		static Texture* OnCreate(const std::string& filepath, const std::string& name, TextureType type = TextureType::TextureMap);

		/** 
			Creates a Texture based on custom parameters. (PERLIN NOISE)
			 - width: Sets the Width of the Texture.
			 - height: Sets the Height of the Texture.
			 - seed: The seed used to generate perlin noise.
			 - scale: Sets the Scale of the perlin noise. (LOWER = LARGER, LARGER = SMALLER)
			 - octaves: Number of Layers.
			 - persistance: (BROKEN)
			 - lacunarity: How important later values are weighted.
			 - offset: Offsets the perlin noise generation.
			 - mode: (BROKEN)
			 - name: Name of the Texture.
		*/
		static Texture* OnCreate(int width, int height, int seed, float scale, int octaves, float persistance, float lacunarity, Vector2 offset, PerlinNormaliseMode mode, const std::string& name);

		/**
			Creates a Texture based on custom parameters. (FRAMEBUFFER USE ONLY)
			 - width: Sets the Width of the Texture.
			 - height: Sets the Height of the Texture.
			 - data: Sets the Data of the Texture.
			 - internal: Sets the Internal Format that the Texture will be using.
			 - format: The actuall Format of the Texture.
			 - type: Determains how the data will be read when passed in.
			 - name: Sets the Name of the texture.
		*/
		static Texture* OnCreate(int width, int height, unsigned char* data, int internal, int format, GLenum type, const std::string& name);

		// Destroys the Texture specified.
		static void OnDestroy(Texture* texture);
	};
}