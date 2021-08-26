/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Serialiser.h"

#include "../Debug.h"

#include "../Renderer/Shader/Shader.h"
#include "../Manager/ResourceManager.h"

#include "../File-IO/Manifest.h"

namespace Kross
{
	template<>
	class KROSS_API Serialiser<Shader>
	{
	public:
		/*!
			Loads in a Shader from the Specified Directory.
		*/
		void Load(const std::string& filepath)
		{
			/* Report and Early out if the Filepath doesn't exist. */
			if (!FileSystem::FilepathExists(filepath))
			{
				Manifest::Logger()->WriteWarning("Creating Shader from File: [" + filepath + "] Failed!");
				Manifest::Logger()->Write("--- Reasons:");

				/* Report the Reason. */
				Manifest::Logger()->Write("----- Kross Shader File is invalid! Filepath: [" + filepath + "]");
				Manifest::Logger()->WriteSpace();

				return;
			}

			/* Open a Filestream. */
			std::fstream fileStream;
			fileStream.open(filepath.c_str());

			if (fileStream.is_open())
			{
				/* Parameter variables. */
				std::string shaderName = "";
				std::string shaderVertex = "";
				std::string shaderGeometry = "";
				std::string shaderFragment = "";

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
					std::string shaderProperty = "";

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = line.find("->")) != std::string::npos)
					{
						/* Grab the Property Type. */
						if (shaderProperty.empty())
							shaderProperty = line.substr(0, searchPosition);

						/* Grab the Property Value. */
						else
						{
							if (shaderProperty == "NAME") /* Extract Name. */
								shaderName = line.substr(0, searchPosition);

							else if (shaderProperty == "VERTEX") /* Extract Vertex Shader Filepath. */
								shaderVertex = line.substr(0, searchPosition);

							else if (shaderProperty == "GEOMETRY") /* Extract Geometry Filepath. */
								shaderGeometry = line.substr(0, searchPosition);

							else if (shaderProperty == "FRAGMENT") /* Extract Fragment Filepath. */
								shaderFragment = line.substr(0, searchPosition);
						}

						/* Remove the Previous Data. */
						line.erase(0, searchPosition + ((std::string)"->").length());
					}
				}

				/* Assume the Shader can be created. */
				bool shouldCreate = true;
				bool startedLog = false;

				/* Report that the Texture Filepath is Missing. */
				if (shaderName.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Shader from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Shader name not read in!");
					shouldCreate = false;
				}

				/* Report that the Texture Name is Missing. */
				if (shaderVertex.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Shader from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Vertex Shader Filepath not read in!");
					shouldCreate = false;
				}

				/* Report that the Texture Name is Missing. */
				if (!shaderVertex.empty() && !FileSystem::FilepathExists(shaderVertex))
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Shader from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Vertex Shader Filepath is invalid! Filepath: [" + shaderVertex + "]");
					shouldCreate = false;
				}

				/* Report that the Texture Type is Missing. */
				if (shaderFragment.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Shader from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Fragment Shader Filepath not read in!");
					shouldCreate = false;
				}

				/* Report that the Texture Type is Missing. */
				if (!shaderFragment.empty() && !FileSystem::FilepathExists(shaderFragment))
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Shader from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Fragment Shader Filepath is invalid! Filepath: [" + shaderFragment + "]");
					shouldCreate = false;
				}

				/* Report that the Texture Type is Missing. */
				if (!shaderGeometry.empty() && !FileSystem::FilepathExists(shaderGeometry))
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Shader from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Geometry Shader Filepath is invalid! Filepath: [" + shaderGeometry + "]");
					shouldCreate = false;
				}

				/* End the Log. */
				if (startedLog)
				{
					Manifest::Logger()->WriteSpace();
					Manifest::SetLoadSuccess(false);
				}

				/* If we can create a Shader then create it. */
				if (shouldCreate)
				{
					/* Create a Initialised Shader. */
					Shader* shader = nullptr;

					/* If no Geometry Shader was Detected, Don't include it in the Creation. */
					if (shaderGeometry.empty())
					{
						shader = Shader::OnCreate(shaderVertex, shaderFragment, shaderName);
					}

					/* If a Geometry Shader was Detected, Include it in the Creation. */
					else
					{
						shader = Shader::OnCreate(shaderVertex, shaderFragment, shaderGeometry, shaderName);
					}

					/* Attach it as a Resource. */
					ResourceManager::AttachResource<Shader>(shader);

					/* Log Success. */
					Manifest::Logger()->WriteLog("Creating Shader from File: [" + filepath + "] Successful!");
				}
			}	
			
			/* Close the Stream. */
			fileStream.close();
		}
	};
}