#pragma once

#include "../Core.h"

#include "Serialiser.h"

#include "../File-IO/Manifest.h"
#include "../File-IO/FileSystem.h"

namespace Kross
{
	template<>
	class KROSS_API Serialiser<AudioSource>
	{
	public:
		void Load(const std::string& filepath)
		{
			/* Report and Early out if the Filepath doesn't exist. */
			if (!FileSystem::FilepathExists(filepath))
			{
				Manifest::Logger()->WriteWarning("Creating Audio Source from File: [" + filepath + "] Failed!");
				Manifest::Logger()->Write("--- Reasons:");

				/* Report the Reason. */
				Manifest::Logger()->Write("----- Kross Audio Source File is invalid! Filepath: [" + filepath + "]");
				Manifest::Logger()->WriteSpace();

				return;
			}

			/* Open a Filestream. */
			std::fstream fileStream;
			fileStream.open(filepath.c_str());

			if (fileStream.is_open())
			{
				/* Parameter variables. */
				std::string audioSourceName = "";
				std::string audioSourceFilepath = "";
				std::string audioSourceStream = "";

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
					std::string audioSourceProperty = "";

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = line.find("->")) != std::string::npos)
					{
						/* Grab the Property Type. */
						if (audioSourceProperty.empty())
							audioSourceProperty = line.substr(0, searchPosition);

						/* Grab the Property Value. */
						else
						{
							if (audioSourceProperty == "NAME") /* Extract the Name. */
								audioSourceName = line.substr(0, searchPosition);

							else if (audioSourceProperty == "FILEPATH") /* Extract the Filepath. */
								audioSourceFilepath = line.substr(0, searchPosition);

							else if (audioSourceProperty == "STREAM") /* Extract the Stream Value. */
								audioSourceStream = line.substr(0, searchPosition);
						}

						/* Erase Used Data. */
						line.erase(0, searchPosition + ((std::string)"->").length());
					}
				}

				/* Assume the Audio Source can be created. */
				bool shouldCreate = true;
				bool startedLog = false;

				/* Report that the Audio Source Name is Missing. */
				if (audioSourceName.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Audio Source from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Audio Source Name not read in!");
					shouldCreate = false;
				}

				/* Report that the Audio Source Filepath is Missing. */
				if (audioSourceFilepath.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Audio Source from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Audio Filepath not read in!");
					shouldCreate = false;
				}

				/* Report that the Audio Source Stream is Missing. */
				if (audioSourceStream.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Audio Source from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Audio Source Stream Value not read in!");
					shouldCreate = false;
				}

				/* Report that the Texture Filepath is Invalid. */
				if (!audioSourceFilepath.empty() && !FileSystem::FilepathExists(audioSourceFilepath))
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
					Manifest::Logger()->Write("----- Texture filepath is invalid! Filepath: [" + audioSourceFilepath + "]");
					shouldCreate = false;
				}

				/* End the Log. */
				if (startedLog)
				{
					Manifest::Logger()->WriteSpace();
					Manifest::SetLoadSuccess(false);
				}

				/* If we can create the Audio Source. */
				if (shouldCreate)
				{
					/* Create the Audio Source and Attach it to the Resource Manager. */
					AudioSource* source = AudioSource::OnCreate(audioSourceFilepath, audioSourceName, std::stoi(audioSourceStream));
					ResourceManager::AttachResource<AudioSource>(source);

					/* Log Success. */
					Manifest::Logger()->WriteLog("Creating Audio Source from File: [" + filepath + "] Successful!");
				}
			}

			fileStream.close();
		}
	};
}