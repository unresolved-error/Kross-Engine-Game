/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#pragma once

#include "../Core.h"

#include "../Manager/ResourceManager.h"

namespace Kross
{
	class KROSS_API FileSystem
	{
	private:
		FileSystem() {};
		~FileSystem() {};
	protected:
		friend class ResourceManager;
		friend class ObjectEditor;

		// Writes the Asset Engine Manifest File.
		static void OnWriteManifestFile();

		static void OnWritePrefab(const Object* prefab);

		// Writes a Texture.
		static void OnWriteTexture(const std::string& filepath);

		// Writes a TileMap
		static void OnWriteTileMap(const std::string& filepath);

		// Writes a TileSet
		static void OnWriteTileSet(const std::string& filepath);

		// Writes a Sprite.
		static void OnWriteSprite(const std::string& filepath);

		// Writes a Shader.
		static void OnWriteShader(const std::string& filepath);

		// Writes a Shader.
		static void OnWriteFont(const std::string& filepath);

		// Writes a Material.
		static void OnWriteMaterial(const std::string& filepath);

		// Writes a Animation.
		static void OnWriteAnimation(const std::string& filepath);

		// Writes a Audio Source.
		static void OnWriteAudioSource(const std::string& filepath);

		// Writes the Atlas.
		static std::string OnWriteAtlasData(Atlas* atlas);

		// Reads the Asset Engine Manifest File.
		static void OnReadManifestFile();

		//Reads the scene in.
		static void OnReadScene(const std::string& filepath);
		static List<Object*> OnReadObjects(const std::string& filepath);
			
		// Reads in a Texture.
		static void OnReadTexture(const std::string& filepath);

		// Reads in a Prefab.
		static void OnReadPrefab(const std::string& filepath);

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

		// Reads in the Atlas.
		static void OnReadAtlas(const std::string& filepath);

		// Reads in the Atlas Texture Count.
		static int OnReadAtlasTextureCount(const std::string& filepath);

		// Reads in the Atlas Sprite Data and Applies it to the Atlas.
		static void OnPopulateAtlasSpriteData(const std::string& filepath, Atlas* atlas);

		// Reads in the Atlas Texture Data and Applies it to the Atlas.
		static void OnPopulateAtlasTextureData(const std::string& filepath, Atlas* atlas);

		// Reads in the Atlas Texture and Applies it to the Atlas.
		static void OnPopulateAtlasTexture(const std::string& filepath, Atlas* atlas);

		// Reads in a Audio Source.
		static void OnReadAudioSource(const std::string& filepath);

		// Creates the Directory Specified and returns the success of the Creation.
		static bool OnCreateDirectory(const std::string& directory);

	public:
		// Obtains the file contents in a string. (LAID OUT AS REPRESENTED IN FILE)
		static std::string GetFileContents(const std::string& filepath);

		// Obtains the file contents in a string. (ONLY ONE LINE FROM THE FILE)
		static std::string GetFileContentsSingle(const std::string& filepath, int line);

		// Checks whether a relative Directory Exists.
		static bool DirectoryExists(const std::string& directory) { return std::filesystem::is_directory(directory); };
	};
}