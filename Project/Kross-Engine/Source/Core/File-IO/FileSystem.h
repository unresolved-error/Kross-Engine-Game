/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#pragma once

#include "../Core.h"

namespace Kross
{
	class KROSS_API FileSystem
	{
	private:
		FileSystem() {};
		~FileSystem() {};
	protected:
		friend class ResourceManager;

		// Writes the Asset Engine Manifest File.
		static void OnWriteManifestFile();

		// Writes a Texture.
		static void OnWritesTexture(const std::string& filepath);

		// Writes a TileMap
		static void OnWritesTileMap(const std::string& filepath);

		// Writes a TileSet
		static void OnWritesTileSet(const std::string& filepath);

		// Writes a Sprite.
		static void OnWritesSprite(const std::string& filepath);

		// Writes a Shader.
		static void OnWritesShader(const std::string& filepath);

		// Writes a Shader.
		static void OnWritesFont(const std::string& filepath);

		// Writes a Material.
		static void OnWritesMaterial(const std::string& filepath);

		// Writes a Animation.
		static void OnWritesAnimation(const std::string& filepath);

		// Writes a Audio Source.
		static void OnWritesAudioSource(const std::string& filepath);

		// Reads the Asset Engine Manifest File.
		static void OnReadManifestFile();

		// Reads in a Texture.
		static void OnReadTexture(const std::string& filepath);

		// Reads in a TileMap
		static void OnReadTileMap(const std::string& filepath);

		// Reads in a TileSet
		static void OnReadTileSet(const std::string& filepath);

		// Reads in a Sprite.
		static void OnReadSprite(const std::string& filepath);

		// Reads in a Shader.
		static void OnReadShader(const std::string& filepath);

		// Reads in a Shader.
		static void OnReadFont(const std::string& filepath);

		// Reads in a Material.
		static void OnReadMaterial(const std::string& filepath);

		// Reads in a Animation.
		static void OnReadAnimation(const std::string& filepath);

		// Reads in a Audio Source.
		static void OnReadAudioSource(const std::string& filepath);

	public:
		// Obtains the file contents in a string. (LAID OUT AS REPRESENTED IN FILE)
		static std::string GetFileContents(const std::string& filepath);

		// Obtains the file contents in a string. (ONLY ONE LINE FROM THE FILE)
		static std::string GetFileContentsSingle(const std::string& filepath, int line);
	};
}