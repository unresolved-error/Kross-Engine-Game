/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Serialiser.h"

#include "../Debug.h"
#include "../Renderer/Image/Texture.h"

#include "../File-IO/Manifest.h"

namespace Kross
{
	template<>
	class KROSS_API Serialiser<Texture>
	{
	public:
		/*!
			Loads in a Texture from the Specified Directory.
		*/
		void Load(const std::string& filepath)
		{
			/* Report and Early out if the Filepath doesn't exist. */
			if (!FileSystem::FilepathExists(filepath))
			{
				Manifest::Logger()->WriteWarning("Creating Texture from File: [" + filepath + "] Failed!");
				Manifest::Logger()->Write("--- Reasons:");

				/* Report the Reason. */
				Manifest::Logger()->Write("----- Kross Texture File is invalid! Filepath: [" + filepath + "]");
				Manifest::Logger()->WriteSpace();

				return;
			}

			/* Open a Filestream. */
			std::fstream fileStream;
			fileStream.open(filepath.c_str());

			if (fileStream.is_open())
			{
				/* Parameter variables. */
				std::string textureFilepath = "";
				std::string textureName = "";
				std::string textureType = "";

				/* Variables for opening and reading the file. */
				std::string line;

				/* Read the file line by line. */
				while (getline(fileStream, line))
				{
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

				/* Assume the Texture can be created. */
				bool shouldCreate = true;
				bool startedLog = false;

				/* Report that the Texture Filepath is Missing. */
				if (textureFilepath.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Texture from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Texture filepath not read in!");
					shouldCreate = false;
				}

				/* Report that the Texture Name is Missing. */
				if (textureName.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Texture from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Texture name not read in!");
					shouldCreate = false;
				}

				/* Report that the Texture Filepath is Invalid. */
				if (!textureFilepath.empty() && !FileSystem::FilepathExists(textureFilepath))
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Texture from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Texture filepath is invalid! Filepath: [" + textureFilepath + "]");
					shouldCreate = false;
				}

				/* Report that the Texture Type is Missing. */
				if (textureType.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Texture from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Texture type not read in!");
					shouldCreate = false;
				}

				/* End the Log. */
				if (startedLog)
				{
					Manifest::Logger()->WriteSpace();
					Manifest::SetLoadSuccess(false);
				}

				/* If we can create a Texture then create it. */
				if (shouldCreate)
				{
					/* if it isn't a Default Type Texture. */
					if (textureType != "DEFAULT")
					{
						/* Font Map Texture Creation. */
						if (textureType == "FONTMAP")
							Texture::OnCreate(textureFilepath, textureName, TextureType::FontMap);

						/* Normal Map Creation. */
						else if (textureType == "NORMALMAP")
							Texture::OnCreate(textureFilepath, textureName, TextureType::NormalMap);

						/* Specular Map Creation. */
						else if (textureType == "SPECULARMAP")
							Texture::OnCreate(textureFilepath, textureName, TextureType::SpecularMap);

						/* Engine Texture Creation. */
						else if (textureType == "ENGINE")
							Texture::OnCreate(textureFilepath, textureName, TextureType::Engine);
					}

					/* Default Texture Creation. */
					else
						Texture::OnCreate(textureFilepath, textureName);

					/* Log Success. */
					Manifest::Logger()->WriteLog("Creating Texture from File: [" + filepath + "] Successful!");
				}
			}

			/* Close the File Stream. */
			fileStream.close();
		}
	};
}