/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "Core.h"

namespace Kross
{
	class KROSS_API FileSystem
	{
	private:
		FileSystem() {};
		~FileSystem() {};
	protected:
		friend class ResourceManager;

		// Loads the Asset Engine Manifest File.
		static void OnLoadManifestFile();

		// Loads in a Texture.
		static void OnLoadTexture(const std::string& filepath);

		// Loads in a Sprite.
		static void OnLoadSprite(const std::string& filepath);

		// Loads in a Shader.
		static void OnLoadShader(const std::string& filepath);

		// Loads in a Shader.
		static void OnLoadFont(const std::string& filepath);

		// Loads in a Material.
		static void OnLoadMaterial(const std::string& filepath);

		// Loads in a Animation.
		static void OnLoadAnimation(const std::string& filepath);

	public:
		// Obtains the file contents in a string. (LAID OUT AS REPRESENTED IN FILE)
		static std::string GetFileContents(const std::string& filepath);

		// Obtains the file contents in a string. (ONLY ONE LINE FROM THE FILE)
		static std::string GetFileContentsSingle(const std::string& filepath, int line);
	};
}