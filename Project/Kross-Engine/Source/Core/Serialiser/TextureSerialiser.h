/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Serialiser.h"

#include "../Renderer/Image/Texture.h"
#include "../Manager/ResourceManager.h"

namespace Kross
{
	template<>
	class KROSS_API Serialiser<Texture>
	{
	public:
		static void Serialise(std::string filepath)
		{
			/* Display what we are loading. */
			std::cout << "Loading Texture from " << filepath << "..." << std::endl;

			/* Open a Filestream. */
			std::fstream fileStream;
			fileStream.open(filepath.c_str());

			/* Parameter variables. */
			std::string textureFilepath;
			std::string textureName;
			std::string textureType;

			/* Variables for opening and reading the file. */
			std::string line;

			if (fileStream.is_open())
			{
				bool ignoreFirstLine = true;

				/* Read the file line by line. */
				while (getline(fileStream, line))
				{
					/* Just so It doesn't read "TEXTURE:". */
					if (ignoreFirstLine)
					{
						ignoreFirstLine = false;
						continue;
					}

					/* Ignore Comments. */
					if (line.find("//") != std::string::npos)
						continue;

					/* Quick Variables. */
					size_t searchPosition = 0;
					std::string textureProperty = "";

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = line.find("->")) != std::string::npos)
					{
						/* Grab the Property Type. */
						if (textureProperty.empty())
							textureProperty = line.substr(0, searchPosition);

						/* Grab the Property Value. */
						else
						{
							if (textureProperty == "NAME") /* Extract the Name. */
								textureName = line.substr(0, searchPosition);

							else if (textureProperty == "FILEPATH") /* Extract the Filepath. */
								textureFilepath = line.substr(0, searchPosition);

							else if (textureProperty == "TYPE") /* Extract the Texture Type. */
								textureType = line.substr(0, searchPosition);
						}

						/* Remove the Previous Data. */
						line.erase(0, searchPosition + ((std::string)"->").length());
					}
				}

				if (textureType != "DEFAULT")
				{
					if (textureType == "FONTMAP")
						Texture::OnCreate(textureFilepath, textureName, TextureType::FontMap);

					else if (textureType == "NORMALMAP")
						Texture::OnCreate(textureFilepath, textureName, TextureType::NormalMap);

					else if (textureType == "SPECULARMAP")
						Texture::OnCreate(textureFilepath, textureName, TextureType::SpecularMap);

					else if (textureType == "ENGINE")
						Texture::OnCreate(textureFilepath, textureName, TextureType::Engine);
				}

				else
					Texture::OnCreate(textureFilepath, textureName);
			}

			fileStream.close();
		}
	};
}