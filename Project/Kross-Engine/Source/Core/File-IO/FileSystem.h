/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#pragma once

#include "../Core.h"

#include "../Manager/ResourceManager.h"
#include "../Scene.h"

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
		friend class MainMenu;
		friend class SceneManager;

		// Temp.
		friend class Manifest;

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

		//Reads the scene in.
		static Scene* OnReadScene(const std::string& filepath);
		//Reads in the objects in a scene. Important that this is not called by anyone but "OnReadScene"
		static std::vector<Object*> OnReadObjects(const std::string& filepath);

		//SAVES Scene
		static void OnWriteScene(Scene* sceneToSave);
		//Saves the objects in the ".kobj". Important that this is not called by anything but OnWriteScene()
		static void OnWriteObjects(const std::string& filepath, Scene* scene);

		// Reads in a Prefab.
		static void OnReadPrefab(const std::string& filepath);

		// Reads in a TileMap
		static void OnReadTileMap(const std::string& filepath);

		// Reads in a Sprite.
		static void OnReadSprite(const std::string& filepath);

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

		

	public:
		// Obtains the file contents in a string. (LAID OUT AS REPRESENTED IN FILE)
		static std::string GetFileContents(const std::string& filepath);

		// Obtains the file contents in a string. (ONLY ONE LINE FROM THE FILE)
		static std::string GetFileContentsSingle(const std::string& filepath, int line);

		// Checks whether a relative Directory Exists.
		static bool DirectoryExists(const std::string& directory) { return std::filesystem::is_directory(directory); };

		// Creates the Directory Specified and returns the success of the Creation.
		static bool OnCreateDirectory(const std::string& directory);

		/*!
			Checks if the Filepath specified exists.
		*/
		static bool FilepathExists(const std::string& filepath);
	};
}