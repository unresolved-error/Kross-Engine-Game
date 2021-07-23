/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#include "FileSystem.h"

#define MANIFEST_FILEPATH "manifest.krs"
#define LINE_DIVIDER "->"

#include "../Manager/ResourceManager.h"

#include "stb_image/stb_image.h"

namespace Kross
{
	std::string FileSystem::GetFileContents(const std::string& filepath)
	{
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;
			std::stringstream contents;

			/* Read the file line by line. */
			while (getline(fileStream, line))
				contents << line << "\n";

			fileStream.close();

			/* Return the file contents. */
			return contents.str();
		}

		else
		{
			fileStream.close();

			/* Return an empty string as it could not open the file. */
			return std::string();
		}
	}

	std::string FileSystem::GetFileContentsSingle(const std::string& filepath, int line)
	{
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string lineString;
			int lineIndex = 0;

			/* Read the file line by line. */
			while (getline(fileStream, lineString) && lineIndex < line)
				lineIndex++;

			fileStream.close();

			/* If the line index wasn't met then return a emtpy string. */
			if (lineIndex < line)
				return std::string();

			/* Return the file contents. */
			return lineString;
		}

		else
		{
			fileStream.close();

			/* Return an empty string as it could not open the file. */
			return std::string();
		}
	}

	std::string FileSystem::OnWriteAtlasData(Atlas* atlas)
	{
		/* Filepaths for everything. */
		std::string atlasFilepath = "Assets/Atlas/0.krs";
		std::string atlasSpriteDataFilepath = "Assets/Atlas/Sprite-Data/0.krs";
		std::string atlasTextureDataFilepath = "Assets/Atlas/Texture-Data/0.krs";
		std::string atlasTextureCountFilepath = "Assets/Atlas/Texture-Data/1.krs";
		std::string atlasRawTextureFilepath = "Resources/Atlas/Atlas.png";

		/* Creates the Directories if needed. */
		OnCreateDirectory("Assets/Atlas/Sprite-Data/");
		OnCreateDirectory("Assets/Atlas/Texture-Data/");

		/* Opens up / Creates the file. Ready for Writing. */
		std::ofstream atlasWriter;
		atlasWriter.open(atlasFilepath);

		/* Write the Data for the Global Atlas Data. */
		atlasWriter << "ATLAS:\n";
		atlasWriter << "TEXTURECOUNTDATA->" << atlasTextureCountFilepath << "->\n";
		atlasWriter << "TEXTURE->" << atlasRawTextureFilepath << "->\n";
		atlasWriter << "SPRITEDATA->" << atlasSpriteDataFilepath << "->\n";
		atlasWriter << "TEXTUREDATA->" << atlasTextureDataFilepath << "->";

		/* Close it to Finalise the File. */
		atlasWriter.close();

		/* Opens up / Creates the Sprite file. */
		std::ofstream atlasSpriteWriter;
		atlasSpriteWriter.open(atlasSpriteDataFilepath);

		/* Write the File Header. */
		atlasSpriteWriter << "ATLAS-SPRITE-DATA:\n";

		/* Go through all of the sprites that were added to the Atlas. */
		for(int i = 0; i < atlas->m_AttachedSprites.size(); i++)
		{
			Sprite* sprite = atlas->m_AttachedSprites[i];
			AtlasSpriteData data = atlas->m_SpriteAtlasUVs[sprite];

			if(i != atlas->m_AttachedSprites.size() - 1)
				atlasSpriteWriter << "DATA->" << sprite->GetName() << "->" << std::to_string(data.m_Offset.x) << "->" << std::to_string(data.m_Offset.y) << "->" << std::to_string(data.m_Ratio.x) << "->" << std::to_string(data.m_Ratio.y) << "->\n";

			else
				atlasSpriteWriter << "DATA->" << sprite->GetName() << "->" << std::to_string(data.m_Offset.x) << "->" << std::to_string(data.m_Offset.y) << "->" << std::to_string(data.m_Ratio.x) << "->" << std::to_string(data.m_Ratio.y) << "->";
		}

		atlasSpriteWriter.close();

		std::ofstream atlasTextureWriter;
		atlasTextureWriter.open(atlasTextureDataFilepath);
		atlasTextureWriter << "ATLAS-TEXTURE-DATA:\n";

		for (int i = 0; i < atlas->m_AttachedTextures.size(); i++)
		{
			Texture* texture = atlas->m_AttachedTextures[i];
			Vector2 offset = atlas->m_TextureOffsets[texture];

			if (i != atlas->m_AttachedTextures.size() - 1)
				atlasTextureWriter << "DATA->" << texture->GetName() << "->" << std::to_string(offset.x) << "->" << std::to_string(offset.y) << "->\n";

			else
				atlasTextureWriter << "DATA->" << texture->GetName() << "->" << std::to_string(offset.x) << "->" << std::to_string(offset.y) << "->";
		}

		atlasTextureWriter.close();

		std::ofstream atlasTextureCountWriter;
		atlasTextureCountWriter.open(atlasTextureCountFilepath);
		atlasTextureCountWriter << "ATLAS-TEXTURE-COUNT-DATA:\n";
		atlasTextureCountWriter << "COUNT->" << std::to_string(atlas->m_AttachedTextures.size()) << "->";

		atlasTextureCountWriter.close();

		return "YEW";
	}

	void FileSystem::OnReadManifestFile()
	{
		/* Display what we are loading. */
		std::cout << "Loading Manifest..." << std::endl;

		/* The Filepath for the Mainfest. */
		std::string filepath = MANIFEST_FILEPATH;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* If the Line size is zero. */
				if (line.empty())
					continue;

				/* Just so It doesn't read "MANIFEST:". */
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
				std::string assetType;
				std::string assetFilepath;
				std::string manifestSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(manifestSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Asset Type. */
					if (varSwitch == 0)
						assetType = line.substr(0, searchPosition);

					/* Grab the Asset Filepath. */
					else
						assetFilepath = line.substr(0, searchPosition);

					line.erase(0, searchPosition + manifestSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}

				/* Determain how it gets loaded in. */

				if (assetType == "SPRITE")
					OnReadSprite(assetFilepath);

				else if (assetType == "TEXTURE")
					OnReadTexture(assetFilepath);

				else if (assetType == "SHADER")
					OnReadShader(assetFilepath);

				else if (assetType == "FONT")
					OnReadFont(assetFilepath);

				else if (assetType == "MATERIAL")
					OnReadMaterial(assetFilepath);

				else if (assetType == "ANIMATION")
					OnReadAnimation(assetFilepath);

				else if (assetType == "AUDIOSOURCE")
					OnReadAudioSource(assetFilepath);

				else if (assetType == "TILEMAP")
					OnReadTileMap(assetFilepath);

				else if(assetType == "TILESET")
					OnReadTileSet(assetFilepath);

				else if (assetType == "ATLAS")
					OnReadAtlas(assetFilepath);
			}

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnReadTexture(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Texture from " << filepath <<"..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string textureFilepath;
		std::string textureName;
		std::string textureType;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

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
				std::string textureProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						textureProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (textureProperty == "NAME")
							textureName = line.substr(0, searchPosition);

						else if (textureProperty == "FILEPATH")
							textureFilepath = line.substr(0, searchPosition);

						else if (textureProperty == "TYPE")
							textureType = line.substr(0, searchPosition);
					}


					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
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
			}

			else
				Texture::OnCreate(textureFilepath, textureName);

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnReadTileMap(const std::string& filepath) 
	{
		/* Display what we are loading. */
		std::cout << "Loading Tile Map from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());
		std::string mapName;
		std::string mapRawDataFilepath;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool hasFirstLine = false;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Special Case where it reads the first line. */
				if (!hasFirstLine)
				{
					hasFirstLine = true;
					continue;
				}

				/* Ignore Comments. */
				if (line.find("//") != std::string::npos)
					continue;

				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string tileMapProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						tileMapProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (tileMapProperty == "NAME")
							mapName = line.substr(0, searchPosition);

						else if (tileMapProperty == "RAWDATA")
							mapRawDataFilepath = line.substr(0, searchPosition);

					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			fileStream.close();
		}

		/* Open Raw Data. */
		fileStream.open(mapRawDataFilepath);

		List<List<int>> dataConverted;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{

				/* Quick Variables. */
				size_t searchPosition = 0;
				List<std::string> data;
				std::string lineSplitter = ",";

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos)
				{
					data.push_back(line.substr(0, searchPosition));

					line.erase(0, searchPosition + lineSplitter.length());
				}
				
				line = line;

				data.push_back(line);

				dataConverted.push_back(List<int>());

				for (int i = 0; i < data.size(); i++)
				{
					/* Comment me please. */
					dataConverted[dataConverted.size() - 1].push_back(std::stoi(data[i]));
				}
			}

			fileStream.close();
		}



		TileMap* tileMap = TileMap::OnCreate(mapName);
		tileMap->SetMapIndexes(dataConverted);
		/* Attach to resource manager. */
		ResourceManager::AttachResource<TileMap>(tileMap);

	}

	void FileSystem::OnReadTileSet(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Tile Set from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());
		std::string tileSetName;
		std::string spriteBaseName;
		std::string spriteSheetWidth;
		std::string spriteSheetHeight;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool hasFirstLine = false;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Special Case where it reads the first line. */
				if (!hasFirstLine)
				{
					hasFirstLine = true;
					continue;
				}

				/* Ignore Comments. */
				if (line.find("//") != std::string::npos)
					continue;

				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string tileSetProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						tileSetProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (tileSetProperty == "NAME")
							tileSetName = line.substr(0, searchPosition);

						else if (tileSetProperty == "SPRITEBASENAME")
							spriteBaseName = line.substr(0, searchPosition);

						else if (tileSetProperty == "SPRITESHEETWIDTH")
							spriteSheetWidth = line.substr(0, searchPosition);

						else if (tileSetProperty == "SPRITESHEETHEIGHT")
							spriteSheetHeight = line.substr(0, searchPosition);


					}


					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			fileStream.close();
		}

		/* Quick Variables. */
		int width = std::stoi(spriteSheetWidth);
		int height = std::stoi(spriteSheetHeight);
		List<Sprite*> sprites;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				sprites.push_back(ResourceManager::GetResource<Sprite>(spriteBaseName + std::to_string(x) + "-" + std::to_string(y)));
			}
		}

		TileSet* tileSet = TileSet::OnCreate(tileSetName);
		tileSet->SetSprites(sprites);

		/* Attach to resource manager. */
		ResourceManager::AttachResource<TileSet>(tileSet);
	}

	void FileSystem::OnReadSprite(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Sprite from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string spriteType;
		std::string spriteTexture;
		std::string spriteName;
		std::string spriteWidth;
		std::string spriteHeight;
		std::string spriteOffsetX;
		std::string spriteOffsetY;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool hasFirstLine = false;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Special Case where it reads the first line. */
				if (!hasFirstLine)
				{
					spriteType = line;
					hasFirstLine = true;
					continue;
				}

				/* Ignore Comments. */
				if (line.find("//") != std::string::npos)
					continue;

				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string spriteProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						spriteProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (spriteProperty == "NAME")
							spriteName = line.substr(0, searchPosition);

						else if (spriteProperty == "TEXTURE")
							spriteTexture = line.substr(0, searchPosition);

						else if (spriteProperty == "WIDTH")
							spriteWidth = line.substr(0, searchPosition);

						else if (spriteProperty == "HEIGHT")
							spriteHeight = line.substr(0, searchPosition);

						else if (spriteProperty == "OFFSETX")
							spriteOffsetX = line.substr(0, searchPosition);

						else if (spriteProperty == "OFFSETY")
							spriteOffsetY = line.substr(0, searchPosition);
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			/* Data Values. */
			Texture* texture =	ResourceManager::GetResource<Texture>(spriteTexture);

			if (spriteType != "SPRITE:")
			{
				int width = std::stoi(spriteWidth);
				int height = std::stoi(spriteHeight);

				if (spriteType == "SINGLESPRITE:")
				{
					Vector2 offset = Vector2(std::stoi(spriteOffsetX), std::stoi(spriteOffsetY));
					Sprite::OnCreate(texture, width, height, offset, spriteName);
				}

				if (spriteType == "SPRITESHEET:")
					Sprite::OnCreate(texture, width, height, spriteName);
			}

			else
				Sprite::OnCreate(texture, spriteName);

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnReadFont(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Font from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string fontName;
		std::string fontTexture;
		std::string fontWidth;
		std::string fontHeight;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Ignore the first line. */
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
				std::string fontProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						fontProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (fontProperty == "NAME")
							fontName = line.substr(0, searchPosition);

						else if (fontProperty == "TEXTURE")
							fontTexture = line.substr(0, searchPosition);

						else if (fontProperty == "WIDTH")
							fontWidth = line.substr(0, searchPosition);

						else if (fontProperty == "HEIGHT")
							fontHeight = line.substr(0, searchPosition);
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			/* Data Values. */
			Texture* texture = ResourceManager::GetResource<Texture>(fontTexture);

			int width = std::stoi(fontWidth);
			int height = std::stoi(fontHeight);

			Font::OnCreate(texture, width, height, fontName);

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnReadShader(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Shader from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string shaderName;
		std::string shaderVertex;
		std::string shaderGeometry;
		std::string shaderFragment;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Ignore the first line. */
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
				std::string shaderProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						shaderProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (shaderProperty == "NAME")
							shaderName = line.substr(0, searchPosition);

						else if (shaderProperty == "VERTEX")
							shaderVertex = line.substr(0, searchPosition);

						else if (shaderProperty == "GEOMETRY")
							shaderGeometry = line.substr(0, searchPosition);

						else if (shaderProperty == "FRAGMENT")
							shaderFragment = line.substr(0, searchPosition);
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}
			Shader* shader = nullptr;

			if (shaderGeometry == "*")
				shader = Shader::OnCreate(shaderVertex, shaderFragment, shaderName);
			else
				shader = Shader::OnCreate(shaderVertex, shaderFragment, shaderGeometry, shaderName);

			ResourceManager::AttachResource<Shader>(shader);

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnReadMaterial(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Material from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string materialName;
		std::string materialDiffuseSprite;
		std::string materialNormalSprite;
		std::string materialSpecularSprite;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Ignore the first line. */
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
				std::string materialProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						materialProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (materialProperty == "NAME")
							materialName = line.substr(0, searchPosition);

						else if (materialProperty == "DIFFUSE")
							materialDiffuseSprite = line.substr(0, searchPosition);

						else if (materialProperty == "NORMAL")
							materialNormalSprite = line.substr(0, searchPosition);

						else if (materialProperty == "SPECULAR")
							materialSpecularSprite = line.substr(0, searchPosition);
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			Material* material = Material::OnCreate(materialName);

			if (materialDiffuseSprite != "*")
				material->p_Diffuse = ResourceManager::GetResource<Sprite>(materialDiffuseSprite);

			else
				material->p_Diffuse = ResourceManager::GetResource<Sprite>("Diffuse");

			if (materialNormalSprite != "*")
				material->p_Normal = ResourceManager::GetResource<Sprite>(materialNormalSprite);

			else
				material->p_Normal = ResourceManager::GetResource<Sprite>("Normal");

			if (materialSpecularSprite != "*")
				material->p_Specular = ResourceManager::GetResource<Sprite>(materialSpecularSprite);

			else
				material->p_Specular = ResourceManager::GetResource<Sprite>("Specular");

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnReadAnimation(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Animation from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string animationName;
		std::string animationDuration;
		List<std::string> animationKeyFrameData;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Ignore the first line. */
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
				std::string animationProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						animationProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (animationProperty == "NAME")
							animationName = line.substr(0, searchPosition);

						else if (animationProperty == "DURATION")
							animationDuration = line.substr(0, searchPosition);

						else if(animationProperty == "KEYFRAME")
							animationKeyFrameData.push_back(line);
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			Animation* animation = Animation::OnCreate(animationName);
			animation->SetDuration(std::stof(animationDuration));

			for (int i = 0; i < animationKeyFrameData.size(); i++)
			{
				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string animationProperty;
				std::string lineSplitter = "->";

				/* Keyframe Data Values. */
				std::string positionX, positionY, rotation, scaleX, scaleY, sprite;

				/* Create the Keyframe. */
				Keyframe* keyframe = KROSS_NEW Keyframe();

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = animationKeyFrameData[i].find(lineSplitter)) != std::string::npos && varSwitch != 6)
				{
					std::string value = animationKeyFrameData[i].substr(0, searchPosition);

					switch (varSwitch)
					{
						case 0:
						{
							if (value != "*")
								positionX = value;

							break;
						}

						case 1:
						{
							if (value != "*")
								positionY = value;

							break;
						}

						case 2:
						{
							if (value != "*")
								rotation = value;

							break;
						}

						case 3:
						{
							if (value != "*")
								scaleX = value;

							break;
						}

						case 4:
						{
							if (value != "*")
								scaleY = value;

							break;
						}

						case 5:
						{
							if (value != "*")
								sprite = value;

							break;
						}
					}

					animationKeyFrameData[i].erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}

				if (positionX != "" && positionY != "")
					keyframe->SetPosition(Vector2(std::stof(positionX), std::stof(positionY)));

				if (rotation != "")
					keyframe->SetRotation(std::stof(rotation));

				if (scaleX != "" && scaleY != "")
					keyframe->SetScale(Vector2(std::stof(scaleX), std::stof(scaleY)));

				if (sprite != "")
					keyframe->SetSprite(ResourceManager::GetResource<Sprite>(sprite));

				/* Add the Keyframe. */
				animation->AttachKeyframe(keyframe);
			}

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnReadAtlas(const std::string& filepath)
	{
		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string atlasTextureCountFilepath;
		std::string atlasTextureFilepath;
		std::string atlasSpriteDataFilepath;
		std::string atlasTextureDataFilepath;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Ignore the first line. */
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
				std::string atlasProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						atlasProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (atlasProperty == "TEXTURECOUNTDATA")
							atlasTextureCountFilepath = line.substr(0, searchPosition);

						else if (atlasProperty == "TEXTURE")
							atlasTextureFilepath = line.substr(0, searchPosition);

						else if (atlasProperty == "SPRITEDATA")
							atlasSpriteDataFilepath = line.substr(0, searchPosition);

						else if (atlasProperty == "TEXTUREDATA")
							atlasTextureDataFilepath = line.substr(0, searchPosition);
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			fileStream.close();

			int textureCount = OnReadAtlasTextureCount(atlasTextureCountFilepath);

			List<Texture*> textures = ResourceManager::GetTextures();
			List<TextureType> ignoreTextures = Atlas::GetIgnoreTextureTypes();

			int actualTextureCount = 0;

			for (int i = 0; i < textures.size(); i++)
			{
				Texture* texture = textures[i];
				bool ignore = false;

				for (int j = 0; j < ignoreTextures.size(); j++)
				{
					if (texture->GetType() == ignoreTextures[j])
					{
						ignore = true;
						break;
					}
				}

				if (ignore)
					continue;

				actualTextureCount++;
			}

			Atlas* atlas;
			if (textureCount != actualTextureCount)
			{
				std::cout << "\nCreating Atlas...\n" << std::endl;
				atlas = Atlas::OnCreate();
				ResourceManager::AttachResource<Atlas>(atlas);

				return;
			}

			std::cout << "\nLoading Atlas...\n" << std::endl;

			atlas = Atlas::OnCreate(false);
			
			OnPopulateAtlasTexture(atlasTextureFilepath, atlas);
			OnPopulateAtlasSpriteData(atlasSpriteDataFilepath, atlas);
			OnPopulateAtlasTextureData(atlasTextureDataFilepath, atlas);

			ResourceManager::AttachResource<Atlas>(atlas);
		}

		else
		{
			fileStream.close();
		}
	}

	int FileSystem::OnReadAtlasTextureCount(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Atlas Texture Count from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string atlasTextureCount;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Ignore the first line. */
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
				std::string atlasTextureCountProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						atlasTextureCountProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (atlasTextureCountProperty == "COUNT")
							atlasTextureCount = line.substr(0, searchPosition);
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			fileStream.close();

			return std::stoi(atlasTextureCount);
		}

		else
		{
			fileStream.close();

			return -1;
		}
	}

	void FileSystem::OnPopulateAtlasSpriteData(const std::string& filepath, Atlas* atlas)
	{
		/* Display what we are loading. */
		std::cout << "Loading Atlas Sprite Data from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());
		
		/* Parameter variables. */
		List<std::string> spriteData;
		
		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;
		
			bool ignoreFirstLine = true;
		
			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Ignore the first line. */
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
				std::string atlasSpriteDataProperty;
				std::string lineSplitter = "->";
		
				int varSwitch = 0;
		
				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						atlasSpriteDataProperty = line.substr(0, searchPosition);
		
					/* Grab the Property Value. */
					else
					{
						if (atlasSpriteDataProperty == "DATA")
							spriteData.push_back(line);
					}
		
					line.erase(0, searchPosition + lineSplitter.length());
		
					/* Up the varaible switch. */
					varSwitch++;
				}
			}
		
			for (int i = 0; i < spriteData.size(); i++)
			{
				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string lineSplitter = "->";
		
				/* Keyframe Data Values. */
				std::string spriteName, offsetX, offsetY, ratioX, ratioY;
		
		
				int varSwitch = 0;
		
				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = spriteData[i].find(lineSplitter)) != std::string::npos && varSwitch != 5)
				{
					std::string value = spriteData[i].substr(0, searchPosition);
		
					switch (varSwitch)
					{
						case 0:
						{
							spriteName = value;
							break;
						}
		
						case 1:
						{
							offsetX = value;
							break;
						}
		
						case 2:
						{
							offsetY = value;
							break;
						}
		
						case 3:
						{
							ratioX = value;
							break;
						}
		
						case 4:
						{
							ratioY = value;
							break;
						}
					}
		
					spriteData[i].erase(0, searchPosition + lineSplitter.length());
		
					/* Up the varaible switch. */
					varSwitch++;
				}

				AtlasSpriteData data;
				data.m_Offset = Vector2(std::stof(offsetX), std::stof(offsetY));
				data.m_Ratio = Vector2(std::stof(ratioX), std::stof(ratioY));

				atlas->AttachSpriteData(ResourceManager::GetResource<Sprite>(spriteName), data);
			}
		
			fileStream.close();
		}
		
		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnPopulateAtlasTextureData(const std::string& filepath, Atlas* atlas)
	{
		/* Display what we are loading. */
		std::cout << "Loading Atlas Texture Data from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		List<std::string> textureData;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Ignore the first line. */
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
				std::string atlasTextureDataProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						atlasTextureDataProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (atlasTextureDataProperty == "DATA")
							textureData.push_back(line);
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			for (int i = 0; i < textureData.size(); i++)
			{
				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string lineSplitter = "->";

				/* Keyframe Data Values. */
				std::string textureName, offsetX, offsetY;


				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = textureData[i].find(lineSplitter)) != std::string::npos && varSwitch != 3)
				{
					std::string value = textureData[i].substr(0, searchPosition);

					switch (varSwitch)
					{
						case 0:
						{
							textureName = value;
							break;
						}

						case 1:
						{
							offsetX = value;
							break;
						}

						case 2:
						{
							offsetY = value;
							break;
						}
					}

					textureData[i].erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}

				Vector2 data;
				data = Vector2(std::stof(offsetX), std::stof(offsetY));

				atlas->AttachTextureOffset(ResourceManager::GetResource<Texture>(textureName), data);
			}

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnPopulateAtlasTexture(const std::string& filepath, Atlas* atlas)
	{
		/* Display what we are loading. */
		std::cout << "Loading Atlas Texture from " << filepath << "..." << std::endl;

		Texture* texture = Texture::OnCreateAtlas();

		int width, height, bpp;
		/* Write the Image to disk. */
		stbi_set_flip_vertically_on_load(0);
		texture->SetPixelData(stbi_load(filepath.c_str(), &width, &height, &bpp, 4));

		/* Set basic Texture Properties. */
		texture->SetName("Atlas");
		texture->SetWidth(width);
		texture->SetHeight(height);
		texture->SetBitsPerPixel(bpp);
		
		/* Finalise the Data. */
		texture->OnFinalise();

		atlas->SetTexture(texture);

	}

	void FileSystem::OnReadAudioSource(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Audio Source from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string audioSourceName;
		std::string audioSourceFilepath;
		std::string audioSourceStream;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Ignore the first line. */
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
				std::string audioSourceProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						audioSourceProperty = line.substr(0, searchPosition);

					/* Grab the Property Value. */
					else
					{
						if (audioSourceProperty == "NAME")
							audioSourceName = line.substr(0, searchPosition);

						else if (audioSourceProperty == "FILEPATH")
							audioSourceFilepath = line.substr(0, searchPosition);

						else if (audioSourceProperty == "STREAM")
							audioSourceStream = line.substr(0, searchPosition);
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}
			
			AudioSource* source = AudioSource::OnCreate(audioSourceFilepath, audioSourceName, std::stoi(audioSourceStream));

			ResourceManager::AttachResource<AudioSource>(source);

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	bool FileSystem::OnCreateDirectory(const std::string& directory)
	{
		/* If the Directory already exists. */
		if (DirectoryExists(directory))
			return true;

		/* If not, Create it. */
		return std::filesystem::create_directory(directory);
	}
}