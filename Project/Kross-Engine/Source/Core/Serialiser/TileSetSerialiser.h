/*
 *  Author: Chris Deitch.
 *  Editors:
 *		- Chris Deitch.
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Serialiser.h"

#include "../File-IO/Manifest.h"
#include "../File-IO/FileSystem.h"

namespace Kross
{
	template<>
	class KROSS_API Serialiser<TileSet>
	{
	public:
		void Load(const std::string& filepath)
		{
			/* Report and Early out if the Filepath doesn't exist. */
			if (!FileSystem::FilepathExists(filepath))
			{
				Manifest::Logger()->WriteWarning("Creating Tile Set from File: [" + filepath + "] Failed!");
				Manifest::Logger()->Write("--- Reasons:");

				/* Report the Reason. */
				Manifest::Logger()->Write("----- Kross Tile Set File is invalid! Filepath: [" + filepath + "]");
				Manifest::Logger()->WriteSpace();

				return;
			}

			/* Open a Filestream. */
			std::fstream fileStream;
			fileStream.open(filepath.c_str());

			if (fileStream.is_open())
			{
				/* Parameter Variables. */
				std::string tileSetName = "";
				std::string spriteBaseName = "";
				std::string spriteSheetWidth = "";
				std::string spriteSheetHeight = "";

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
					std::string tileSetProperty = "";

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = line.find("->")) != std::string::npos)
					{
						/* Grab the Property Type. */
						if (tileSetProperty.empty())
							tileSetProperty = line.substr(0, searchPosition);

						/* Grab the Property Value. */
						else
						{
							if (tileSetProperty == "NAME") /* Extract the Name. */
								tileSetName = line.substr(0, searchPosition);

							else if (tileSetProperty == "SPRITEBASENAME") /* Extract the Base Name of the Sprite. */
								spriteBaseName = line.substr(0, searchPosition);

							else if (tileSetProperty == "SPRITESHEETWIDTH") /* Extract the Width in cells of the Sprtie Sheet. */
								spriteSheetWidth = line.substr(0, searchPosition);

							else if (tileSetProperty == "SPRITESHEETHEIGHT") /* Extract the Height in cells of the Sprtie Sheet. */
								spriteSheetHeight = line.substr(0, searchPosition);
						}

						/* Erase the Used Data. */
						line.erase(0, searchPosition + ((std::string)"->").length());
					}
				}

				/* Assume the Tile Set can be created. */
				bool shouldCreate = true;
				bool startedLog = false;

				/* Report that the Tile Set Name is Missing. */
				if (tileSetName.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Tile Set from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Tile Set Name not read in!");
					shouldCreate = false;
				}

				/* Report that the Tile Set Sprite Base Name is Missing. */
				if (spriteBaseName.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Tile Set from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Tile Set Sprite base Name not read in!");
					shouldCreate = false;
				}

				/* Report that the Tile Set Sprite Sheet Width is Missing. */
				if (spriteSheetWidth.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Tile Set from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Tile Set Sprite Sheet Width not read in!");
					shouldCreate = false;
				}

				/* Report that the Tile Set Sprite Sheet Height is Missing. */
				if (spriteSheetHeight.empty())
				{
					/* Start the Log if it hasn't yet. */
					if (!startedLog)
					{
						/* Report the Failure. */
						Manifest::Logger()->WriteWarning("Creating Tile Set from File: [" + filepath + "] Failed!");
						Manifest::Logger()->Write("--- Reasons:");
						startedLog = true;
					}

					/* Report the Reason. */
					Manifest::Logger()->Write("----- Tile Set Sprite Sheet Height not read in!");
					shouldCreate = false;
				}

				/* Storage of Sprites. */
				std::vector<Sprite*> sprites;

				/* This is the First parse to the Creation. */
				if (shouldCreate)
				{
					/* Quick Variables. */
					int width = std::stoi(spriteSheetWidth);
					int height = std::stoi(spriteSheetHeight);

					/* Go through the Sprite Sheet. */
					for (int y = 0; y < height; y++)
					{
						for (int x = 0; x < width; x++)
						{
							/* Sprtie Name.*/
							std::string spriteName = spriteBaseName + std::to_string(x) + "-" + std::to_string(y);

							/* Sprite. */
							Sprite* sprite = ResourceManager::GetResource<Sprite>(spriteName);

							/* If no Sprite was returned. */
							if (!sprite)
							{

								/* Start the Log if it hasn't yet. */
								if (!startedLog)
								{
									/* Report the Failure. */
									Manifest::Logger()->WriteWarning("Creating Tile Set from File: [" + filepath + "] Failed!");
									Manifest::Logger()->Write("--- Reasons:");
									startedLog = true;
								}

								/* Report the Reason. */
								Manifest::Logger()->Write("----- Tile Set Sprite with name [" + spriteName + "] returned null!");
							
								shouldCreate = false;
							}

							/* add the Sprite if it did. */
							else
							{
								sprites.push_back(sprite);
							}
						}
					}
				}

				/* If it failed the first parse. */
				else
				{
					Manifest::Logger()->WriteSpace();
					Manifest::Logger()->Write("----- Failed First Parse! Did not try to add Sprite References!");
				}

				/* End the Log. */
				if (startedLog)
				{
					Manifest::Logger()->WriteSpace();
					Manifest::SetLoadSuccess(false);
				}

				/* Second Parse of the Tile Set. */
				if (shouldCreate)
				{
					/* Create the Tile Set. */
					TileSet* tileSet = TileSet::OnCreate(tileSetName);
					tileSet->SetSprites(sprites);

					/* Attach to resource manager. */
					ResourceManager::AttachResource<TileSet>(tileSet);

					/* Log Success. */
					Manifest::Logger()->WriteLog("Creating Tile Set from File: [" + filepath + "] Successful!");
				}
			}

			/* Close the File Stream. */
			fileStream.close();
		}
	};
}