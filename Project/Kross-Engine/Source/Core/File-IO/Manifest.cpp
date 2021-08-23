/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Manifest.h"

#include "FileSystem.h"
#include "../Serialiser/Serialiser.h"

namespace Kross
{
	Manifest*	Manifest::m_Instance =		nullptr;

	Manifest::~Manifest()
	{
		delete m_Logger;
	}

	void Manifest::OnCreate()
	{
		if (!m_Instance)
			m_Instance = KROSS_NEW Manifest();
	}
	void Manifest::OnDestroy()
	{
		if (m_Instance)
			delete m_Instance;
	}
	void Manifest::Load(const std::string& filepath)
	{
		/* Report and Early out if the Filepath doesn't exist. */
		if (!FileSystem::FilepathExists(filepath))
		{
			/* Write that it failed to Open the Manifest. */
			m_Instance->m_Logger->WriteError("Manifest Filepath does not Exist!");
			m_Instance->m_Logger->Write("\t Filepath: " + filepath);

			m_Instance->m_Logger->Dump("Kross Manifest Log", "log.txt");

			return;
		}

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* If the Line size is zero. */
				if (line.empty())
					continue;

				/* Ignore Comments. */
				if (line.find("//") != std::string::npos)
					continue;

				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string assetType = "";
				std::string assetFilepath = "";

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find("->")) != std::string::npos)
				{
					/* Grab the Asset Type. */
					if (assetType.empty())
						assetType = line.substr(0, searchPosition);

					/* Grab the Asset Filepath. */
					else
						assetFilepath = line.substr(0, searchPosition);

					line.erase(0, searchPosition + ((std::string)"->").length());
				}

				/* Determain how it gets loaded in. */

				if (assetType == "SPRITE")
				{
					FileSystem::OnReadSprite(assetFilepath);
				}

				else if (assetType == "TEXTURE")
				{
					Serialiser<Texture> serialiser = Serialiser<Texture>();
					serialiser.Load(assetFilepath);
				}

				else if (assetType == "SHADER")
				{
					Serialiser<Shader> serialiser = Serialiser<Shader>();
					serialiser.Load(assetFilepath);
				}

				else if (assetType == "FONT")
					FileSystem::OnReadFont(assetFilepath);

				else if (assetType == "MATERIAL")
					FileSystem::OnReadMaterial(assetFilepath);

				else if (assetType == "ANIMATION")
					FileSystem::OnReadAnimation(assetFilepath);

				else if (assetType == "AUDIOSOURCE")
					FileSystem::OnReadAudioSource(assetFilepath);

				else if (assetType == "TILEMAP")
					FileSystem::OnReadTileMap(assetFilepath);

				else if (assetType == "TILESET")
					FileSystem::OnReadTileSet(assetFilepath);

				else if (assetType == "ATLAS")
					FileSystem::OnReadAtlas(assetFilepath);

				else if (assetType == "PREFAB")
					FileSystem::OnReadPrefab(assetFilepath);

				else if (assetType == "SCENE")
					FileSystem::OnReadScene(assetFilepath);
			}
		}

		/* Close the stream. */
		fileStream.close();

		/* Dump the Logger Report. */
		m_Instance->m_Logger->Dump("Kross Manifest Log", "log.txt");
	}

	void Manifest::Write(const std::string& filepath)
	{
	}
}