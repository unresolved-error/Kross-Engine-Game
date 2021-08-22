/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#include "FileSystem.h"


#define MANIFEST_FILEPATH "manifest.krs"
#define LINE_DIVIDER "->"

#include "../Debug.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ScriptRegistry.h"

#include "stb_image/stb_image.h"
#include "../Scene.h"

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
		std::string atlasFilepath = "Assets/Atlas/Atlas.krs";
		std::string atlasSpriteDataFilepath = "Assets/Atlas/Sprite-Data/SpriteData.krs";
		std::string atlasTextureDataFilepath = "Assets/Atlas/Texture-Data/TextureData.krs";
		std::string atlasTextureCountFilepath = "Assets/Atlas/Texture-Data/TextureCountData.krs";
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

				else if (assetType == "TILESET")
					OnReadTileSet(assetFilepath);

				else if (assetType == "ATLAS")
					OnReadAtlas(assetFilepath);

				else if (assetType == "PREFAB")
					OnReadPrefab(assetFilepath);

				else if (assetType == "SCENE")
					OnReadScene(assetFilepath);
			}

			fileStream.close();
		}

		else
		{
			fileStream.close();
		}
	}

	void FileSystem::OnReadScene(const std::string& filepath)
	{
		/* Display what we are loading. */
		std::cout << "Loading Scene from " << filepath << "..." << std::endl;

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		Scene* newScene = Scene::OnCreate("CHANGE ME");
		
		std::string nameOfScene;
		std::string gravity;
		std::string gravityDirX;
		std::string kObjFilepath;


		if (fileStream.is_open()) 
		{
			/* Variables for opening and reading the file. */
			std::string line;

			bool ignoreFirstLine = true;
		
			/* Read the file line by line. */
			while (getline(fileStream, line))
			{
				/* Just so It doesn't read "SCENE:". */
				if (ignoreFirstLine)
				{
					ignoreFirstLine = false;
					continue;
				}

				/* Ignore Comments. */
				if (line.find("//") != std::string::npos) {
					continue;
				}


				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string sceneProperty;
				std::string lineSplitter = "->";

				int varSwitch = 0;
				//while reading this line
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos)
				{
					if (varSwitch == 0)
					{
						sceneProperty = line.substr(0, searchPosition);
					}
					else
					{
						if(sceneProperty == "NAME")
						{
							newScene->SetName(line.substr(0, searchPosition)); 
							//Takes the next property and makes it the scene name and creates the Scene.
						}
						if (sceneProperty == "GRAVITY") 
						{
							switch (varSwitch)
							{
								case 1:
								{
									gravity = line.substr(0, searchPosition);
									break;
								}
								case 2:
								{
									gravityDirX = line.substr(0, searchPosition);
									break;
								}
								case 3:
								{
									Vector2 gravd;
									gravd.x = stof(gravityDirX);
									gravd.y = stof(line.substr(0, searchPosition));
									newScene->SetGravity(stof(gravity),gravd);
									break;
								}
							}
						}
						if (sceneProperty == "OBJECTS")
						{
							kObjFilepath = line.substr(0, searchPosition);
						}
					}

					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
				
			}
			fileStream.close();
		}
		else { fileStream.close(); }

		//NOW LOAD OBJECTS. THIS WILL BE ROUGH.
		std::vector<Object*> readObj = OnReadObjects(kObjFilepath);

		//__debugbreak();

		for (int i = 0; i < readObj.size(); i++)
		{
			
			newScene->AttachObject(readObj[i]);
		}
		
		/* Got I hope this works. */
		SceneManager::AttachScene(newScene);
		SceneManager::SetCurrentScene(0);
	}

	std::vector<Object*> FileSystem::OnReadObjects(const std::string& filepath)
	{
		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string objName;
		std::string objStatic;
		std::string objEnable;
		std::string objLayer;

		std::string transformData;
		std::vector<std::string> animatorData;
		std::vector<std::string> audioPlayerData;
		std::vector<std::string> cameraData;
		std::vector<std::string> rigidbodyData;
		std::vector<std::string> spriteRendererData;
		std::vector<std::string> textRendererData;
		std::vector<std::string> tileMapRendererData;
		std::vector<std::string> particleEmitterData;


		std::vector<Object*> readInObjects;
		Object* currentObject = Object::OnCreate();

		/* If the File Stream is Open. */
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
				std::string objProperty;
				std::string lineSplitter = "->";

				/* Initialise the Variable Switch. */
				int varSwitch = 0;

				if (line == "START->") 
				{
					if(!currentObject)
						currentObject = Object::OnCreate();

					continue;
				}
				else if (line == "END->") 
				{
					/* Set Basic Properties. */
					currentObject->SetName(objName);
					currentObject->SetStatic((bool)std::stoi(objStatic));
					currentObject->SetEnable((bool)std::stoi(objEnable));
					currentObject->SetLayer((Layer)std::stoi(objLayer));
					currentObject->SetPrefab(false);

					/* Go through Animator Data. */
					if (animatorData.size() > 0)
					{
						/* Access all animators on the Object. */
						std::vector<Animator*> animators = currentObject->GetComponents<Animator>();
						for (int i = 0; i < animatorData.size(); i++)
						{
							/* Quick Variables. */
							size_t searchPosition = 0;
							std::string lineSplitter = "->";

							/* For setting the Current animation. */
							bool isFirst = true;

							/* Keep Searching till we reach the end of the Line.*/
							while ((searchPosition = animatorData[i].find(lineSplitter)) != std::string::npos)
							{
								/* Get the Name of the Animation. */
								std::string animationName = animatorData[i].substr(0, searchPosition);

								/* Search for it. */
								Animation* animation = ResourceManager::GetResource<Animation>(animationName);

								/* If the animation exists. */
								if (animation)
								{
									/* Add the Animation to the Animator. */
									animators[i]->AttachAnimation(animation);

									/* For Current Animation Setting. */
									if (isFirst)
									{
										/* If its the First Animation being Searched, Set it a Current. */
										animators[i]->SetCurrentAnimation(0);
										isFirst = false;
									}
								}

								/* If no Animation was Found. */
								else
									Debug::LogWarningLine("Animation: " + animationName + "! Not Found!");

								/* Erase Data that has been used. */
								animatorData[i].erase(0, searchPosition + lineSplitter.length());
							}
						}
					}

					/* Go through the Audio Player Data. */
					if (audioPlayerData.size() > 0)
					{
						/* Grab all of the Audio Players on the Object. */
						std::vector<AudioPlayer*> audioPlayers = currentObject->GetComponents<AudioPlayer>();

						/* Run through the List of Data. */
						for (int i = 0; i < audioPlayerData.size(); i++)
						{
							/* Quick Variables. */
							size_t searchPosition = 0;
							std::string lineSplitter = "->";
							int varSwitch = 0;

							/* Keep Searching till we reach the end of the Line.*/
							while ((searchPosition = audioPlayerData[i].find(lineSplitter)) != std::string::npos)
							{
								/* Grab the Data Value. */
								std::string value = audioPlayerData[i].substr(0, searchPosition);

								/* Run through the Variable Placement Switch. */
								switch (varSwitch)
								{
									/* Audio Source. */
								case 0:
								{
									AudioSource* audioSource = ResourceManager::GetResource<AudioSource>(value);

									/* If the Audio Source searched does exist. */
									if (audioSource)
										audioPlayers[i]->SetAudioSource(audioSource);

									/* If not. */
									else
										Debug::LogWarningLine("Audio Source: " + value + "! Not Found!");

									break;
								}

								/* Loop Setting. */
								case 1:
								{

									audioPlayers[i]->SetLoop((bool)std::stoi(value));
									break;
								}

								/* Play Speed Setting. */
								case 2:
								{
									audioPlayers[i]->SetPlaySpeed(std::stof(value));
									break;
								}

								/* Volume Setting. */
								case 3:
								{
									audioPlayers[i]->SetVolume(std::stof(value));
									break;
								}

								/* Pan Setting. */
								case 4:
								{
									audioPlayers[i]->SetPan(std::stof(value));
									break;
								}
								}

								/* Erase any data that has been used. */
								audioPlayerData[i].erase(0, searchPosition + lineSplitter.length());

								/* Up the Var Switch. */
								varSwitch++;
							}
						}
					}

					/* Go through the Camera Data. */
					if (cameraData.size() > 0)
					{
						/* Grab all of the Cameras on the Object. */
						std::vector<Camera*> cameras = currentObject->GetComponents<Camera>();

						/* Go through all Camera Data. */
						for (int i = 0; i < cameraData.size(); i++)
						{
							/* Quick Variables. */
							size_t searchPosition = 0;
							std::string lineSplitter = "->";
							int varSwitch = 0;

							/* Keep Searching till we reach the end of the Line.*/
							while ((searchPosition = cameraData[i].find(lineSplitter)) != std::string::npos)
							{
								/* Grab the Data Value. */
								std::string value = cameraData[i].substr(0, searchPosition);

								/* Camera Variable Setting. */
								switch (varSwitch)
								{
									/* Camera Size. */
								case 0:
								{
									cameras[i]->SetSize(std::stof(value));
									break;
								}

								/* Camera Near Plane Clipping. */
								case 1:
								{

									cameras[i]->SetNear(std::stof(value));
									break;
								}

								/* Camera Far Plane Clipping. */
								case 2:
								{
									cameras[i]->SetFar(std::stof(value));
									break;
								}
								}

								/* Erase data that is used. */
								cameraData[i].erase(0, searchPosition + lineSplitter.length());

								/* Up the Var Switch. */
								varSwitch++;
							}
						}
					}

					/* Go through Rigidbody Data. */
					if (rigidbodyData.size() > 0)
					{
						/* Grab the Collider on the Object. */
						Collider* collider = currentObject->GetComponent<Collider>();

						/* Go through all of the Rigidbody Data. */
						for (int i = 0; i < rigidbodyData.size(); i++)
						{
							/* Quick Variables. */
							size_t searchPosition = 0;
							std::string lineSplitter = "->";
							int varSwitch = 0;

							/* Keep Searching till we reach the end of the Line.*/
							while ((searchPosition = rigidbodyData[i].find(lineSplitter)) != std::string::npos)
							{
								/* Grab the Data value. */
								std::string value = rigidbodyData[i].substr(0, searchPosition);

								/* Collider Data Setting. */
								switch (varSwitch)
								{
									/* Shape Type Setting. */
								case 0:
								{
									collider->SetShapeType((ShapeType)std::stoi(value));
									break;
								}

								/* Width Setting. */
								case 1:
								{

									collider->SetWidth(std::stof(value));
									break;
								}

								/* Height Setting. */
								case 2:
								{
									collider->SetHeight(std::stof(value));
									break;
								}

								/* Radius Setting. */
								case 3:
								{
									collider->SetRadius(std::stof(value));
									break;
								}

								/* Friction Setting. */
								case 4:
								{

									collider->SetFriction(std::stof(value));
									break;
								}

								/* Mass Setting. */
								case 5:
								{

									collider->SetMass(std::stof(value));
									break;
								}

								/* Static Setting. */
								case 6:
								{

									collider->SetStatic((bool)std::stoi(value));
									break;
								}

								/* Tile Map Collision Check Setting. */
								case 7:
								{
									collider->SetTileMapCollider((bool)std::stoi(value));
									break;
								}

								/* Rotation Lock Setting. */
								case 8:
								{
									collider->SetRotationLock((bool)std::stoi(value));
									break;
								}
								}

								/* Erase any data that we have used. */
								rigidbodyData[i].erase(0, searchPosition + lineSplitter.length());

								/* Up the Var Switch. */
								varSwitch++;
							}
						}
					}

					/* Go through the Sprite Renderer Data. */
					if (spriteRendererData.size() > 0)
					{
						/* Get all Sprite Renderers on this Obejct. */
						std::vector<SpriteRenderer*> renderers = currentObject->GetComponents<SpriteRenderer>();

						/* Go through all of the Data. */
						for (int i = 0; i < spriteRendererData.size(); i++)
						{
							/* Quick Variables. */
							size_t searchPosition = 0;
							std::string lineSplitter = "->";
							int varSwitch = 0;

							/* Colour is Needed through this Process. */
							Colour colour = Colour(1.0f);

							/* Keep Searching till we reach the end of the Line.*/
							while ((searchPosition = spriteRendererData[i].find(lineSplitter)) != std::string::npos)
							{
								/* Grab the Data Value. */
								std::string value = spriteRendererData[i].substr(0, searchPosition);

								/* Sprite Setting Switch. */
								switch (varSwitch)
								{
									/* Material Setting. */
								case 0:
								{
									Material* material = nullptr;
									material = ResourceManager::GetResource<Material>(value);

									/* If we have a material. */
									if (material)
										renderers[i]->SetMaterial(material);

									/* If not Report it. */
									else
										Debug::LogWarningLine("Material: " + value + "! Not Found!");

									break;
								}

								/* Red Value Setting. */
								case 1:
								{

									colour.r = std::stof(value);
									break;
								}

								/* Green Value Setting. */
								case 2:
								{
									colour.g = std::stof(value);
									break;
								}

								/* Blue Value Setting. */
								case 3:
								{
									colour.b = std::stof(value);
									break;
								}

								/* Alpha Value Setting. */
								case 4:
								{

									colour.a = std::stof(value);
									break;
								}

								/* Horizontal Flip Setting. */
								case 5:
								{

									renderers[i]->SetFlipX((bool)std::stoi(value));
									break;
								}

								/* Vertical Flip Setting. */
								case 6:
								{
									renderers[i]->SetFlipY((bool)std::stoi(value));
									break;
								}

								/* Depth Setting. */
								case 7:
								{
									renderers[i]->SetDepth(std::stoi(value));
									break;
								}
								}

								/* Set the Colour Tint. */
								renderers[i]->SetColour(colour);

								/* Erase the data we have used. */
								spriteRendererData[i].erase(0, searchPosition + lineSplitter.length());

								/* Up the Var Switch. */
								varSwitch++;
							}
						}
					}

					/* Go through the Text Rendering Data. */
					if (textRendererData.size() > 0)
					{
						/* Get all of the Text Renderers on the Object. */
						std::vector<TextRenderer*> renderers = currentObject->GetComponents<TextRenderer>();

						/* Run through the Data. */
						for (int i = 0; i < textRendererData.size(); i++)
						{
							/* Quick Variables. */
							size_t searchPosition = 0;
							std::string lineSplitter = "->";
							int varSwitch = 0;

							/* Used thoughout. */
							Colour colour = Colour(1.0f);

							/* Keep Searching till we reach the end of the Line.*/
							while ((searchPosition = textRendererData[i].find(lineSplitter)) != std::string::npos)
							{
								/* Get the Data Value. */
								std::string value = textRendererData[i].substr(0, searchPosition);

								/* Text Renderer Variable Setting. */
								switch (varSwitch)
								{
									/* Text Setting. */
								case 0:
								{
									renderers[i]->SetText(value);
									break;
								}

								/* Font Setting. */
								case 1:
								{
									Font* font = ResourceManager::GetResource<Font>(value);

									/* If we have a font. */
									if (font)
										renderers[i]->SetFont(font);

									/* If not. Report it. */
									else
										Debug::LogWarningLine("Font: " + value + "! Not Found!");

									break;
								}

								/* Text Alignment Setting. */
								case 2:
								{
									renderers[i]->SetTextAlignment((TextAlignment)std::stoi(value));
									break;
								}

								/* Red Value Setting. */
								case 3:
								{

									colour.r = std::stof(value);
									break;
								}

								/* Green Value Setting. */
								case 4:
								{
									colour.g = std::stof(value);
									break;
								}

								/* Blue Value Setting. */
								case 5:
								{
									colour.b = std::stof(value);
									break;
								}

								/* Alpha Value Setting. */
								case 6:
								{
									colour.a = std::stof(value);
									break;
								}

								/* Text Size Setting. */
								case 7:
								{
									renderers[i]->SetTextSize(std::stof(value));
									break;
								}
								}

								/* Set the Text Colour. */
								renderers[i]->SetColour(colour);

								/* Erase the Data just Used. */
								textRendererData[i].erase(0, searchPosition + lineSplitter.length());

								/* Up the Var Switch. */
								varSwitch++;
							}
						}
					}

					/* Go through the Tile Map Renderer Data. */
					if (tileMapRendererData.size() > 0)
					{
						/* Get all Tile Map Renderers on the Object. */
						std::vector<TileMapRenderer*> renderers = currentObject->GetComponents<TileMapRenderer>();

						/* Go through the Data. */
						for (int i = 0; i < tileMapRendererData.size(); i++)
						{
							/* Quick Variables. */
							size_t searchPosition = 0;
							std::string lineSplitter = "->";
							int varSwitch = 0;

							/* Keep Searching till we reach the end of the Line.*/
							while ((searchPosition = tileMapRendererData[i].find(lineSplitter)) != std::string::npos)
							{
								/* Grab the Data Value. */
								std::string value = tileMapRendererData[i].substr(0, searchPosition);

								/* Variable Setting Switch. */
								switch (varSwitch)
								{
									/* Tile Set Setting. */
								case 0:
								{
									TileSet* tileSet = ResourceManager::GetResource<TileSet>(value);

									/* If a Tile Set was Found. */
									if (tileSet)
										renderers[i]->SetTileSet(tileSet);

									/* If not. Report it. */
									else
										Debug::LogWarningLine("Tile Set: " + value + "! Not Found!");

									break;
								}

								/* Tile Map Setting. */
								case 1:
								{
									TileMap* tileMap = ResourceManager::GetResource<TileMap>(value);

									/* If a Tile Map was Found. */
									if (tileMap)
										renderers[i]->SetTileMap(tileMap);

									/* If not. Report it. */
									else
										Debug::LogWarningLine("Tile Map: " + value + "! Not Found!");

									break;
								}
								}

								/* Erase the used up data. */
								tileMapRendererData[i].erase(0, searchPosition + lineSplitter.length());

								/* Up the Var Switch. */
								varSwitch++;
							}
						}
					}

					if (particleEmitterData.size() > 0) 
					{
						/* Get emitterProperties on the Object. */
						ParticleProperties* emitterproperties = currentObject->GetComponent<ParticleProperties>();

						uint16 cBts = 0;
						uint16 mBts = 0;

						/* Run through the Data. */
						for (int i = 0; i < particleEmitterData.size(); i++)
						{
							/* Quick Variables. */
							size_t searchPosition = 0;
							std::string lineSplitter = "->";
							int varSwitch = 0;

							/* Keep Searching till we reach the end of the Line.*/
							while ((searchPosition = particleEmitterData[i].find(lineSplitter)) != std::string::npos)
							{
								/* Get the Data Value. */
								std::string value = particleEmitterData[i].substr(0, searchPosition);

								/*particle Data setting*/
								/*particleFlags->CatagoryBits->MaskBits->Radius*/
								switch (varSwitch)
								{
									/* Particle Flags. */
								case 0:
								{
									uint32 prtFlgs = 0;
									int prtFlagsIntParse = std::stoi(value);
									prtFlgs = static_cast<uint32>(prtFlagsIntParse);
									emitterproperties->AddParticleFlags(prtFlgs);
									break;
								}

								/* CatBits read in. */
								case 1:
								{
									
									int catBtsIntParse = std::stoi(value);
									cBts = static_cast<uint16>(catBtsIntParse);
									break;
								}

								/* MaskBits readIn. */
								case 2:
								{
									int mskBtsIntParse = std::stoi(value);
									mBts = static_cast<uint16>(mskBtsIntParse);
									break;
								}

								/* Radius Setting. */
								case 3:
								{
									float radFlt = std::stof(value);
									emitterproperties->SetRadius(radFlt);
									break;
								}
								case 4:
								{
									int count = std::stoi(value);
									emitterproperties->SetMaxCount(count);
									break;
								}
								}

								emitterproperties->SetColliderFilters(cBts,mBts);
								//edmitterproperties->Sys



								/* Erase the Data just Used. */
								particleEmitterData[i].erase(0, searchPosition + lineSplitter.length());

								/* Up the Var Switch. */
								varSwitch++;
							}
						}

					}

					/* Go through the Transform Data. */
					if (!transformData.empty())
					{
						/* Grab the Transform. */
						Transform2D* transform = currentObject->m_Transform;

						/* Quick Variables. */
						size_t searchPosition = 0;
						std::string lineSplitter = "->";
						int varSwitch = 0;

						/* Keep Searching till we reach the end of the Line.*/
						while ((searchPosition = transformData.find(lineSplitter)) != std::string::npos)
						{
							/* Grab the Data Value. */
							std::string value = transformData.substr(0, searchPosition);

							/* Variable Setting. */
							switch (varSwitch)
							{
								/* X Position Setting. */
							case 0:
							{
								transform->m_Position.x = std::stof(value);
								break;
							}

							/* Y Position Setting. */
							case 1:
							{
								transform->m_Position.y = std::stof(value);
								break;
							}

							/* Rotation Setting. */
							case 2:
							{
								transform->m_Rotation = std::stof(value);
								break;
							}

							/* X Scale Setting. */
							case 3:
							{
								transform->m_Scale.x = std::stof(value);
								break;
							}

							/* Y Scale Setting. */
							case 4:
							{
								transform->m_Scale.y = std::stof(value);
								break;
							}
							}

							/* Remove the Data Used. */
							transformData.erase(0, searchPosition + lineSplitter.length());

							/* Up the Var Switch. */
							varSwitch++;
						}
					}

					animatorData.clear();
					audioPlayerData.clear();
					cameraData.clear();
					rigidbodyData.clear();
					spriteRendererData.clear();
					textRendererData.clear();
					tileMapRendererData.clear();
					particleEmitterData.clear();

					transformData = "";

					readInObjects.push_back(currentObject);
					currentObject = nullptr;
					continue;
				}
				
				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0) {
						objProperty = line.substr(0, searchPosition);
					}

					/* Grab the Property Value. */
					else
					{
						/* Name Property. */
						if (objProperty == "NAME")
							objName = line.substr(0, searchPosition);

						/* Static Property. */
						else if (objProperty == "STATIC")
							objStatic = line.substr(0, searchPosition);

						/* Enable Property. */
						else if (objProperty == "ENABLE")
							objEnable = line.substr(0, searchPosition);

						/* Layer Property. */
						else if (objProperty == "LAYER")
							objLayer = line.substr(0, searchPosition);

						/* Animator Component Property. */
						else if (objProperty == "ANIMATOR")
						{
							currentObject->AttachComponent<Animator>();
							animatorData.push_back(line);
						}

						/* Audio Player Component Property. */
						else if (objProperty == "AUDIO-PLAYER")
						{
							currentObject->AttachComponent<AudioPlayer>();
							audioPlayerData.push_back(line);
						}

						/* Camera Component Property. */
						else if (objProperty == "CAMERA")
						{
							currentObject->AttachComponent<Camera>();
							cameraData.push_back(line);
						}

						/* Rigidbody 2D Component Property. */
						else if (objProperty == "RIGIDBODY2D")
						{
							currentObject->AttachComponent<Rigidbody2D>();
							rigidbodyData.push_back(line);
						}

						/* Sprite Renderer Component Property. */
						else if (objProperty == "SPRITE-RENDERER")
						{
							currentObject->AttachComponent<SpriteRenderer>();
							spriteRendererData.push_back(line);
						}

						/* Text Renderer Component Property. */
						else if (objProperty == "TEXT-RENDERER")
						{
							currentObject->AttachComponent<TextRenderer>();
							textRendererData.push_back(line);
						}

						/* Tile Map Renderer Component Property. */
						else if (objProperty == "TILEMAP-RENDERER")
						{
							currentObject->AttachComponent<TileMapRenderer>();
							tileMapRendererData.push_back(line);
						}

						/* Particle Emitter Component Property. */
						else if (objProperty == "EMITTER") 
						{
							currentObject->AttachComponent<ParticleEmitter>();
							currentObject->AttachComponent<ParticleProperties>();
							particleEmitterData.push_back(line);
						}

						else if (objProperty == "SCRIPT")
						{
							Script* script = ScriptRegistry::GetScript(line.substr(0, line.size() - 2));
							script->m_GameObject = currentObject;
							currentObject->m_Components.push_back(script);
							Debug::LogLine(script->GetName() + " - Script was attached!");
						}

						/* Transform Component Property. */
						else if (objProperty == "TRANSFORM2D")
						{
							transformData = line;
						}

					}

					/* Erase parts of the line to not double up on data search. */
					line.erase(0, searchPosition + lineSplitter.length());

					/* Up the varaible switch. */
					varSwitch++;
				}
			}

			

			

			/* Debugging Checkpoint. */
			std::string debugCheckpoint = "50";

			/* Close the File Stream. */
			fileStream.close();
		}

		/* If the File Stream Failed to open. */
		else
		{
			/* Fully Close the Stream. */
			fileStream.close();
		}

		return readInObjects;
	}

	void FileSystem::OnWriteScene(Scene* sceneToSave)
	{
		std::string sceneFilepath = "Assets/Scenes/" + sceneToSave->GetName() + ".kscn";
		std::string sceneObjFilepath = "Assets/Scenes/" + sceneToSave->GetName() + ".kobj";
		Debug::Log("Saving Scene to " + sceneFilepath);

		std::ofstream fileStream;
		fileStream.open(sceneFilepath.c_str());

		if (fileStream.is_open())
		{
			fileStream << "SCENE:\n";
			fileStream << "NAME->" << sceneToSave->GetName() << "->\n";
			fileStream << "GRAVITY->" << std::to_string(sceneToSave->GetGravityScalar()) << "->"
				<< std::to_string(sceneToSave->GetGravityDirection().x) << "->" 
				<< std::to_string(sceneToSave->GetGravityDirection().y) << "->\n";
			fileStream << "OBJECTS->Assets/Scenes/" << sceneToSave->GetName() << ".kobj->";

			fileStream.close();
		}
		else 
		{
			fileStream.close(); 
		}
		OnWriteObjects(sceneObjFilepath, sceneToSave);

		Debug::Log("SCENE SAVED :D");
	}

	void FileSystem::OnWriteObjects(const std::string& filepath, Scene* scene) 
	{
		
		Debug::LogLine("Saving objects to " + filepath + "...");
		
		std::ofstream fileStream;
		fileStream.open(filepath.c_str());

		if (fileStream.is_open()) {

			fileStream << "OBJECTS:" << "\n\n";

			for (int j = 0; j < scene->m_ActualObjects.size(); j++)
			{
				fileStream << "START->\n";
				fileStream << "NAME->"+ scene->m_ActualObjects[j]->m_Name +"->\n";
				fileStream << "STATIC->" + std::to_string((int)(scene->m_ActualObjects[j]->IsStatic())) + "->\n";
				fileStream << "ENABLE->" + std::to_string((int)(scene->m_ActualObjects[j]->Enabled())) + "->\n";
				fileStream << "LAYER->" + std::to_string((int)(scene->m_ActualObjects[j]->GetLayer())) + "->\n";
				fileStream << "TRANSFORM2D->" + std::to_string(scene->m_ActualObjects[j]->m_Transform->m_Position.x) + "->" +
					std::to_string(scene->m_ActualObjects[j]->m_Transform->m_Position.y) + "->" +
					std::to_string(scene->m_ActualObjects[j]->m_Transform->m_Rotation) + "->" +
					std::to_string(scene->m_ActualObjects[j]->m_Transform->m_Scale.x) + "->" +
					std::to_string(scene->m_ActualObjects[j]->m_Transform->m_Scale.y) + "->" + "\n";
				
				for (int k = 0; k < scene->m_ActualObjects[j]->m_Components.size(); k++)
				{
					Component* comp = scene->m_ActualObjects[j]->m_Components[k];
					//Write each component. Check what it is.
					if (typeid(*comp) == typeid(Animator))
					{
						Animator* anim = (Animator*)comp;
						fileStream << "ANIMATOR->";

						fileStream << anim->GetCurrentAnimation()->GetName() << "->";

						//other animations
						for (int i = 0; i < anim->m_Animations.size(); i++)
						{
							if (anim->m_Animations[i] != anim->GetCurrentAnimation())
							{
								fileStream << anim->m_Animations[i]->GetName() << "->";
							}

						}
						fileStream << "\n";
					}
					else if (typeid(*comp) == typeid(Camera))
					{
						Camera* cam = (Camera*)comp;
						/*
							SIZE->NEAR->FAR
						*/
						fileStream << "CAMERA->";
						fileStream << cam->GetSize() << "->";
						fileStream << cam->GetNear() << "->";
						fileStream << cam->GetFar() << "->";
						fileStream << "\n";
					}
					else if (typeid(*comp) == typeid(AudioPlayer))
					{
						AudioPlayer* aud = (AudioPlayer*)comp;
						fileStream << "AUDIO-PLAYER->";
						fileStream << aud->GetSource()->GetName() << "->";
						fileStream << (int)aud->GetProperties()->GetLoop() << "->";
						fileStream << aud->GetProperties()->GetPlaySpeed() << "->";
						fileStream << aud->GetProperties()->GetVolume() << "->";
						fileStream << aud->GetProperties()->GetPan() << "->";
						fileStream << "\n";
					}
					else if (typeid(*comp) == typeid(Collider))
					{
						Collider* rig = (Collider*)comp;
						fileStream << "RIGIDBODY2D->";
						fileStream << (int)rig->GetShapeType() << "->";
						fileStream << rig->GetWidth() << "->";
						fileStream << rig->GetHeight() << "->";
						fileStream << rig->GetRadius() << "->";
						fileStream << rig->GetFriction() << "->";
						fileStream << rig->GetMass() << "->";
						fileStream << (int)rig->IsStatic() << "->";
						fileStream << (int)rig->IsTileMapCollider() << "->";
						fileStream << (int)rig->IsRotationLocked() << "->";
						fileStream << "\n";
					}
					else if (typeid(*comp) == typeid(SpriteRenderer))
					{
						SpriteRenderer* sprR = (SpriteRenderer*)comp;
						fileStream << "SPRITE-RENDERER->";
						fileStream << sprR->GetMaterial()->GetName() + "->";
						fileStream << sprR->GetColour().r << "->";
						fileStream << sprR->GetColour().g << "->";
						fileStream << sprR->GetColour().b << "->";
						fileStream << sprR->GetColour().a << "->";
						fileStream << (int)sprR->GetFlipX() << "->";
						fileStream << (int)sprR->GetFlipY() << "->";
						fileStream << (int)sprR->GetDepth() << "->";
						fileStream << "\n";
					}
					else if (typeid(*comp) == typeid(TextRenderer))
					{
						TextRenderer* tr = (TextRenderer*)comp;
						/*
							Text->font->alignment->r->g->b->a->size->
						*/

						fileStream << "TEXT-RENDERER->";
						fileStream << tr->GetText() << "->";
						fileStream << tr->GetFont()->GetName() << "->";
						fileStream << (int)tr->GetTextAlignment() << "->";
						fileStream << tr->GetColour().r << "->";
						fileStream << tr->GetColour().g << "->";
						fileStream << tr->GetColour().b << "->";
						fileStream << tr->GetColour().a << "->";
						fileStream << tr->GetTextSize() << "->";
						fileStream << "\n";
					}
					else if (typeid(*comp) == typeid(TileMapRenderer))
					{
						TileMapRenderer* tmr = (TileMapRenderer*)comp;
						/*tileSet -> tileMap*/
						fileStream << "TILEMAP-RENDERER->";
						fileStream << tmr->GetTileSet()->GetName() << "->";
						fileStream << tmr->GetTileMap()->GetName() << "->";
						fileStream << "\n";
					}
					else if (typeid(*comp) == typeid(Transform2D))
					{
					}
					else if (typeid(*comp) == typeid(Rigidbody2D))
					{
						
					}
					else if (typeid(*comp) == typeid(ParticleEmitter))
					{
						/*INTENTIONALLY LEFT BLANK. EMITTERS ARE ##NOT## USED TO WRITE PARTICLE INFORMATION*/
						/*SEE BELOW FOR PARTICLE PROPERTIES.*/
					}
					else if (typeid(*comp) == typeid(ParticleProperties)) 
					{
						ParticleProperties* pep = (ParticleProperties*)comp;
						/*particleFlags->CatagoryBits->MaskBits->Radius*/
						fileStream << "EMITTER->";
						fileStream << pep->GetParticleFlags() << "->";
						fileStream << pep->GetColliderFilters()->categoryBits << "->";
						fileStream << pep->GetColliderFilters()->maskBits << "->";
						fileStream << pep->GetRadius() << "->";
						fileStream << pep->GetMaxCount() << "->\n";

					}
					else
					{
						Script* script = (Script*)scene->m_ActualObjects[j]->m_Components[k];
						fileStream << "SCRIPT->";
						fileStream << script->GetName() << "->\n";
					}
					comp = nullptr;
				}

				fileStream << "END->\n";
				fileStream << "\n";
			}
			fileStream.close();
		}
		else { fileStream.close(); }

		Debug::LogLine("Objects Saved.");
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

				else if (textureType == "ENGINE")
					Texture::OnCreate(textureFilepath, textureName, TextureType::Engine);
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

	void FileSystem::OnReadPrefab(const std::string& filepath)
	{
		/* Display what we are loading. */
		Debug::LogLine("Loading Prefab from " + filepath + "...");

		/* Open a Filestream. */
		std::fstream fileStream;
		fileStream.open(filepath.c_str());

		/* Parameter variables. */
		std::string prefabName;
		std::string prefabStatic;
		std::string prefabEnable;
		std::string prefabLayer;
		
		std::string transformData;
		std::vector<std::string> animatorData;
		std::vector<std::string> audioPlayerData;
		std::vector<std::string> cameraData;
		std::vector<std::string> rigidbodyData;
		std::vector<std::string> spriteRendererData;
		std::vector<std::string> textRendererData;
		std::vector<std::string> tileMapRendererData;
		
		/* If the File Stream is Open. */
		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;
			bool ignoreFirstLine = true;

			/* Create the Object. */
			Object* object = Object::OnCreate();
		
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
				std::string prefabProperty;
				std::string lineSplitter = "->";
		
				/* Initialise the Variable Switch. */
				int varSwitch = 0;
		
				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos && varSwitch != 2)
				{
					/* Grab the Property Type. */
					if (varSwitch == 0)
						prefabProperty = line.substr(0, searchPosition);
		
					/* Grab the Property Value. */
					else
					{
						/* Name Property. */
						if (prefabProperty == "NAME")
							prefabName = line.substr(0, searchPosition);
		
						/* Static Property. */
						else if (prefabProperty == "STATIC")
							prefabStatic = line.substr(0, searchPosition);

						/* Enable Property. */
						else if (prefabProperty == "ENABLE")
							prefabEnable = line.substr(0, searchPosition);

						/* Layer Property. */
						else if (prefabProperty == "LAYER")
							prefabLayer = line.substr(0, searchPosition);

						/* Animator Component Property. */
						else if (prefabProperty == "ANIMATOR")
						{
							object->AttachComponent<Animator>();
							animatorData.push_back(line);
						}

						/* Audio Player Component Property. */
						else if (prefabProperty == "AUDIO-PLAYER")
						{
							object->AttachComponent<AudioPlayer>();
							audioPlayerData.push_back(line);
						}

						/* Camera Component Property. */
						else if (prefabProperty == "CAMERA")
						{
							object->AttachComponent<Camera>();
							cameraData.push_back(line);
						}

						/* Rigidbody 2D Component Property. */
						else if (prefabProperty == "RIGIDBODY2D")
						{
							object->AttachComponent<Rigidbody2D>();
							rigidbodyData.push_back(line);
						}

						/* Sprite Renderer Component Property. */
						else if (prefabProperty == "SPRITE-RENDERER")
						{
							object->AttachComponent<SpriteRenderer>();
							spriteRendererData.push_back(line);
						}

						/* Text Renderer Component Property. */
						else if (prefabProperty == "TEXT-RENDERER")
						{
							object->AttachComponent<TextRenderer>();
							textRendererData.push_back(line);
						}

						/* Tile Map Renderer Component Property. */
						else if (prefabProperty == "TILEMAP-RENDERER")
						{
							object->AttachComponent<TileMapRenderer>();
							tileMapRendererData.push_back(line);
						}

						/* Transform Component Property. */
						else if (prefabProperty == "TRANSFORM2D")
						{
							transformData = line;
						}

					}
		
					/* Erase parts of the line to not double up on data search. */
					line.erase(0, searchPosition + lineSplitter.length());
		
					/* Up the varaible switch. */
					varSwitch++;
				}
			}
		
			/* Set Basic Properties. */
			object->SetName(prefabName);
			object->SetStatic((bool)std::stoi(prefabStatic));
			object->SetEnable((bool)std::stoi(prefabEnable));
			object->SetLayer((Layer)std::stoi(prefabLayer));
			object->SetPrefab(true);

			/* Go through Animator Data. */
			if (animatorData.size() > 0)
			{
				/* Access all animators on the Object. */
				std::vector<Animator*> animators = object->GetComponents<Animator>();
				for (int i = 0; i < animatorData.size(); i++)
				{
					/* Quick Variables. */
					size_t searchPosition = 0;
					std::string lineSplitter = "->";

					/* For setting the Current animation. */
					bool isFirst = true;

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = animatorData[i].find(lineSplitter)) != std::string::npos)
					{
						/* Get the Name of the Animation. */
						std::string animationName = animatorData[i].substr(0, searchPosition);

						/* Search for it. */
						Animation* animation = ResourceManager::GetResource<Animation>(animationName);

						/* If the animation exists. */
						if (animation)
						{
							/* Add the Animation to the Animator. */
							animators[i]->AttachAnimation(animation);

							/* For Current Animation Setting. */
							if (isFirst)
							{
								/* If its the First Animation being Searched, Set it a Current. */
								animators[i]->SetCurrentAnimation(0);
								isFirst = false;
							}
						}

						/* If no Animation was Found. */
						else
							Debug::LogWarningLine("Animation: " + animationName + "! Not Found!");

						/* Erase Data that has been used. */
						animatorData[i].erase(0, searchPosition + lineSplitter.length());
					}
				}
			}

			/* Go through the Audio Player Data. */
			if (audioPlayerData.size() > 0)
			{
				/* Grab all of the Audio Players on the Object. */
				std::vector<AudioPlayer*> audioPlayers = object->GetComponents<AudioPlayer>();

				/* Run through the List of Data. */
				for (int i = 0; i < audioPlayerData.size(); i++)
				{
					/* Quick Variables. */
					size_t searchPosition = 0;
					std::string lineSplitter = "->";
					int varSwitch = 0;

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = audioPlayerData[i].find(lineSplitter)) != std::string::npos)
					{
						/* Grab the Data Value. */
						std::string value = audioPlayerData[i].substr(0, searchPosition);

						/* Run through the Variable Placement Switch. */
						switch (varSwitch)
						{
							/* Audio Source. */
							case 0:
							{
								AudioSource* audioSource = ResourceManager::GetResource<AudioSource>(value);

								/* If the Audio Source searched does exist. */
								if (audioSource)
									audioPlayers[i]->SetAudioSource(audioSource);

								/* If not. */
								else
									Debug::LogWarningLine("Audio Source: " + value + "! Not Found!");

								break;
							}

							/* Loop Setting. */
							case 1:
							{

								audioPlayers[i]->SetLoop((bool)std::stoi(value));
								break;
							}

							/* Play Speed Setting. */
							case 2:
							{
								audioPlayers[i]->SetPlaySpeed(std::stof(value));
								break;
							}

							/* Volume Setting. */
							case 3:
							{
								audioPlayers[i]->SetVolume(std::stof(value));
								break;
							}

							/* Pan Setting. */
							case 4:
							{
								audioPlayers[i]->SetPan(std::stof(value));
								break;
							}
						}

						/* Erase any data that has been used. */
						audioPlayerData[i].erase(0, searchPosition + lineSplitter.length());

						/* Up the Var Switch. */
						varSwitch++;
					}
				}
			}

			/* Go through the Camera Data. */
			if (cameraData.size() > 0)
			{
				/* Grab all of the Cameras on the Object. */
				std::vector<Camera*> cameras = object->GetComponents<Camera>();

				/* Go through all Camera Data. */
				for (int i = 0; i < cameraData.size(); i++)
				{
					/* Quick Variables. */
					size_t searchPosition = 0;
					std::string lineSplitter = "->";
					int varSwitch = 0;

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = cameraData[i].find(lineSplitter)) != std::string::npos)
					{
						/* Grab the Data Value. */
						std::string value = cameraData[i].substr(0, searchPosition);

						/* Camera Variable Setting. */
						switch (varSwitch)
						{
							/* Camera Size. */
							case 0:
							{
								cameras[i]->SetSize(std::stof(value));
								break;
							}

							/* Camera Near Plane Clipping. */
							case 1:
							{

								cameras[i]->SetNear(std::stof(value));
								break;
							}

							/* Camera Far Plane Clipping. */
							case 2:
							{
								cameras[i]->SetFar(std::stof(value));
								break;
							}
						}

						/* Erase data that is used. */
						cameraData[i].erase(0, searchPosition + lineSplitter.length());

						/* Up the Var Switch. */
						varSwitch++;
					}
				}
			}
		
			/* Go through Rigidbody Data. */
			if (rigidbodyData.size() > 0)
			{
				/* Grab the Collider on the Object. */
				Collider* collider = object->GetComponent<Collider>();

				/* Go through all of the Rigidbody Data. */
				for (int i = 0; i < rigidbodyData.size(); i++)
				{
					/* Quick Variables. */
					size_t searchPosition = 0;
					std::string lineSplitter = "->";
					int varSwitch = 0;

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = rigidbodyData[i].find(lineSplitter)) != std::string::npos)
					{
						/* Grab the Data value. */
						std::string value = rigidbodyData[i].substr(0, searchPosition);

						/* Collider Data Setting. */
						switch (varSwitch)
						{
							/* Shape Type Setting. */
							case 0:
							{
								collider->SetShapeType((ShapeType)std::stoi(value));
								break;
							}

							/* Width Setting. */
							case 1:
							{

								collider->SetWidth(std::stof(value));
								break;
							}

							/* Height Setting. */
							case 2:
							{
								collider->SetHeight(std::stof(value));
								break;
							}

							/* Radius Setting. */
							case 3:
							{
								collider->SetRadius(std::stof(value));
								break;
							}

							/* Friction Setting. */
							case 4:
							{

								collider->SetFriction(std::stof(value));
								break;
							}

							/* Static Setting. */
							case 5:
							{

								collider->SetStatic((bool)std::stoi(value));
								break;
							}

							/* Tile Map Collision Check Setting. */
							case 6:
							{
								collider->SetTileMapCollider((bool)std::stoi(value));
								break;
							}

							/* Rotation Lock Setting. */
							case 7:
							{
								collider->SetRotationLock((bool)std::stoi(value));
								break;
							}
						}

						/* Erase any data that we have used. */
						rigidbodyData[i].erase(0, searchPosition + lineSplitter.length());

						/* Up the Var Switch. */
						varSwitch++;
					}
				}
			}

			/* Go through the Sprite Renderer Data. */
			if (spriteRendererData.size() > 0)
			{
				/* Get all Sprite Renderers on this Obejct. */
				std::vector<SpriteRenderer*> renderers = object->GetComponents<SpriteRenderer>();

				/* Go through all of the Data. */
				for (int i = 0; i < spriteRendererData.size(); i++)
				{
					/* Quick Variables. */
					size_t searchPosition = 0;
					std::string lineSplitter = "->";
					int varSwitch = 0;

					/* Colour is Needed through this Process. */
					Colour colour = Colour(1.0f);

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = spriteRendererData[i].find(lineSplitter)) != std::string::npos)
					{
						/* Grab the Data Value. */
						std::string value = spriteRendererData[i].substr(0, searchPosition);

						/* Sprite Setting Switch. */
						switch (varSwitch)
						{
							/* Material Setting. */
							case 0:
							{
								Material* material = nullptr;
								material = ResourceManager::GetResource<Material>(value);

								/* If we have a material. */
								if (material)
									renderers[i]->SetMaterial(material);

								/* If not Report it. */
								else
									Debug::LogWarningLine("Material: " + value + "! Not Found!");

								break;
							}

							/* Red Value Setting. */
							case 1:
							{

								colour.r = std::stof(value);
								break;
							}

							/* Green Value Setting. */
							case 2:
							{
								colour.g = std::stof(value);
								break;
							}

							/* Blue Value Setting. */
							case 3:
							{
								colour.b = std::stof(value);
								break;
							}

							/* Alpha Value Setting. */
							case 4:
							{

								colour.a = std::stof(value);
								break;
							}

							/* Horizontal Flip Setting. */
							case 5:
							{

								renderers[i]->SetFlipX((bool)std::stoi(value));
								break;
							}

							/* Vertical Flip Setting. */
							case 6:
							{
								renderers[i]->SetFlipY((bool)std::stoi(value));
								break;
							}

							/* Depth Setting. */
							case 7:
							{
								renderers[i]->SetDepth(std::stoi(value));
								break;
							}
						}

						/* Set the Colour Tint. */
						renderers[i]->SetColour(colour);

						/* Erase the data we have used. */
						spriteRendererData[i].erase(0, searchPosition + lineSplitter.length());

						/* Up the Var Switch. */
						varSwitch++;
					}
				}
			}

			/* Go through the Text Rendering Data. */
			if (textRendererData.size() > 0)
			{
				/* Get all of the Text Renderers on the Object. */
				std::vector<TextRenderer*> renderers = object->GetComponents<TextRenderer>();

				/* Run through the Data. */
				for (int i = 0; i < textRendererData.size(); i++)
				{
					/* Quick Variables. */
					size_t searchPosition = 0;
					std::string lineSplitter = "->";
					int varSwitch = 0;

					/* Used thoughout. */
					Colour colour = Colour(1.0f);

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = textRendererData[i].find(lineSplitter)) != std::string::npos)
					{
						/* Get the Data Value. */
						std::string value = textRendererData[i].substr(0, searchPosition);

						/* Text Renderer Variable Setting. */
						switch (varSwitch)
						{
							/* Text Setting. */
							case 0:
							{
								renderers[i]->SetText(value);
								break;
							}

							/* Font Setting. */
							case 1:
							{
								Font* font = ResourceManager::GetResource<Font>(value);

								/* If we have a font. */
								if (font)
									renderers[i]->SetFont(font);

								/* If not. Report it. */
								else
									Debug::LogWarningLine("Font: " + value + "! Not Found!");

								break;
							}

							/* Text Alignment Setting. */
							case 2:
							{
								renderers[i]->SetTextAlignment((TextAlignment)std::stoi(value));
								break;
							}

							/* Red Value Setting. */
							case 3:
							{

								colour.r = std::stof(value);
								break;
							}

							/* Green Value Setting. */
							case 4:
							{
								colour.g = std::stof(value);
								break;
							}

							/* Blue Value Setting. */
							case 5:
							{
								colour.b = std::stof(value);
								break;
							}

							/* Alpha Value Setting. */
							case 6:
							{
								colour.a = std::stof(value);
								break;
							}

							/* Text Size Setting. */
							case 7:
							{
								renderers[i]->SetTextSize(std::stof(value));
								break;
							}
						}

						/* Set the Text Colour. */
						renderers[i]->SetColour(colour);

						/* Erase the Data just Used. */
						textRendererData[i].erase(0, searchPosition + lineSplitter.length());

						/* Up the Var Switch. */
						varSwitch++;
					}
				}
			}

			/* Go through the Tile Map Renderer Data. */
			if (tileMapRendererData.size() > 0)
			{
				/* Get all Tile Map Renderers on the Object. */
				std::vector<TileMapRenderer*> renderers = object->GetComponents<TileMapRenderer>();
				
				/* Go through the Data. */
				for (int i = 0; i < tileMapRendererData.size(); i++)
				{
					/* Quick Variables. */
					size_t searchPosition = 0;
					std::string lineSplitter = "->";
					int varSwitch = 0;

					/* Keep Searching till we reach the end of the Line.*/
					while ((searchPosition = tileMapRendererData[i].find(lineSplitter)) != std::string::npos)
					{
						/* Grab the Data Value. */
						std::string value = tileMapRendererData[i].substr(0, searchPosition);

						/* Variable Setting Switch. */
						switch (varSwitch)
						{
							/* Tile Set Setting. */
							case 0:
							{
								TileSet* tileSet = ResourceManager::GetResource<TileSet>(value);

								/* If a Tile Set was Found. */
								if (tileSet)
									renderers[i]->SetTileSet(tileSet);

								/* If not. Report it. */
								else
									Debug::LogWarningLine("Tile Set: " + value + "! Not Found!");

								break;
							}

							/* Tile Map Setting. */
							case 1:
							{
								TileMap* tileMap = ResourceManager::GetResource<TileMap>(value);

								/* If a Tile Map was Found. */
								if (tileMap)
									renderers[i]->SetTileMap(tileMap);

								/* If not. Report it. */
								else
									Debug::LogWarningLine("Tile Map: " + value + "! Not Found!");

								break;
							}
						}

						/* Erase the used up data. */
						tileMapRendererData[i].erase(0, searchPosition + lineSplitter.length());

						/* Up the Var Switch. */
						varSwitch++;
					}
				}
			}

			/* Go through the Transform Data. */
			if (!transformData.empty())
			{
				/* Grab the Transform. */
				Transform2D* transform = object->m_Transform;

				/* Quick Variables. */
				size_t searchPosition = 0;
				std::string lineSplitter = "->";
				int varSwitch = 0;

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = transformData.find(lineSplitter)) != std::string::npos)
				{
					/* Grab the Data Value. */
					std::string value = transformData.substr(0, searchPosition);

					/* Variable Setting. */
					switch (varSwitch)
					{
						/* X Position Setting. */
						case 0:
						{
							transform->m_Position.x = std::stof(value);
							break;
						}

						/* Y Position Setting. */
						case 1:
						{
							transform->m_Position.y = std::stof(value);
							break;
						}

						/* Rotation Setting. */
						case 2:
						{
							transform->m_Rotation = std::stof(value);
							break;
						}

						/* X Scale Setting. */
						case 3:
						{
							transform->m_Scale.x = std::stof(value);
							break;
						}

						/* Y Scale Setting. */
						case 4:
						{
							transform->m_Scale.y = std::stof(value);
							break;
						}
					}

					/* Remove the Data Used. */
					transformData.erase(0, searchPosition + lineSplitter.length());

					/* Up the Var Switch. */
					varSwitch++;
				}
			}

			/* Attach the Prefab. */
			ResourceManager::AttachResource<Object>(object);

			/* Debugging Checkpoint. */
			std::string debugCheckpoint = "50";

			/* Close the File Stream. */
			fileStream.close();
		}

		/* If the File Stream Failed to open. */
		else
		{
			/* Fully Close the Stream. */
			fileStream.close();
		}
	}

	void FileSystem::OnWritePrefab(const Object* prefab)
	{
		OnCreateDirectory("Assets/Prefabs/");

		std::string filepath = ("Assets/Prefabs/" + prefab->GetName() + ".krs");

		/* Display what we are loading. */
		Debug::LogLine("Saving Prefab");


		std::string breakChar("->");

		/* Parameter variables. */
		std::string prefabTitle("PREFAB:");
		std::string prefabName("NAME->" + prefab->GetName() + "->");
		std::string prefabStatic("STATIC->" + std::to_string((int)prefab->IsStatic()) + breakChar);
		std::string prefabEnable("ENABLE->" + std::to_string((int)prefab->Enabled()) + breakChar);
		std::string prefabLayer("LAYER->" + std::to_string((int)prefab->GetLayer()) + breakChar);

		/* Transform is always on an object, and always one. */
		std::string transformData("TRANSFORM2D->");
		transformData += std::to_string(prefab->m_Transform->m_Position.x) + breakChar;
		transformData += std::to_string(prefab->m_Transform->m_Position.y) + breakChar;
		transformData += std::to_string(prefab->m_Transform->m_Rotation) + breakChar;
		transformData += std::to_string(prefab->m_Transform->m_Scale.x) + breakChar;
		transformData += std::to_string(prefab->m_Transform->m_Scale.y) + breakChar;

		/* Open the Filestream. */
		std::ofstream prefabStream;
		prefabStream.open(filepath.c_str());
		prefabStream << prefabTitle + "\n";
		prefabStream << prefabName + "\n";
		prefabStream << prefabStatic + "\n";
		prefabStream << prefabEnable + "\n";
		prefabStream << prefabLayer + "\n";
		prefabStream << transformData + "\n";


		for (int i = 0; i < prefab->m_Components.size(); i++)
		{
			Component* comp = prefab->m_Components[i];
			//Write each component. Check what it is.
			if (typeid(*comp) == typeid(Animator))
			{
				Animator* anim = (Animator*)comp;
				prefabStream << "ANIMATOR->";

				prefabStream << anim->GetCurrentAnimation()->GetName() << "->";

				//other animations
				for (int i = 0; i < anim->m_Animations.size(); i++)
				{
					if (anim->m_Animations[i] != anim->GetCurrentAnimation()) 
					{
						prefabStream << anim->m_Animations[i]->GetName() << "->";
					}

				}

			}
			else if (typeid(*comp) == typeid(Camera))
			{
				Camera* cam = (Camera*)comp;
				/*
					SIZE->NEAR->FAR
				*/
				prefabStream << "CAMERA->";
				prefabStream << cam->GetSize() << "->";
				prefabStream << cam->GetNear() << "->";
				prefabStream << cam->GetFar() << "->";

			}
			else if (typeid(*comp) == typeid(AudioPlayer))
			{
				AudioPlayer* aud = (AudioPlayer*)comp;
				prefabStream << "AUDIO-PLAYER->";
				prefabStream << aud->GetSource()->GetName() << "->";
				prefabStream << (int)aud->GetProperties()->GetLoop() << "->";
				prefabStream << aud->GetProperties()->GetPlaySpeed() << "->";
				prefabStream << aud->GetProperties()->GetVolume() << "->";
				prefabStream << aud->GetProperties()->GetPan() << "->";
			}
			else if (typeid(*comp) == typeid(Collider))
			{
				Collider* rig = (Collider*)comp;
				prefabStream << "RIGIDBODY2D->";
				prefabStream << (int)rig->GetShapeType() << "->";
				prefabStream << rig->GetWidth() << "->";
				prefabStream << rig->GetHeight() << "->";
				prefabStream << rig->GetRadius() << "->";
				prefabStream << rig->GetFriction() << "->";
				prefabStream << (int)rig->IsStatic() << "->";
				prefabStream << (int)rig->IsTileMapCollider() << "->";
				prefabStream << (int)rig->IsRotationLocked() << "->";
			}
			else if (typeid(*comp) == typeid(SpriteRenderer))
			{
				SpriteRenderer* sprR = (SpriteRenderer*)comp;
				prefabStream << "SPRITE-RENDERER->";
				prefabStream << sprR->GetMaterial()->GetName() + "->";
				prefabStream << sprR->GetColour().r << "->";
				prefabStream << sprR->GetColour().g << "->";
				prefabStream << sprR->GetColour().b << "->";
				prefabStream << sprR->GetColour().a << "->";
				prefabStream << (int)sprR->GetFlipX() << "->";
				prefabStream << (int)sprR->GetFlipY() << "->";
				prefabStream << (int)sprR->GetDepth() << "->";
			}
			else if (typeid(*comp) == typeid(TextRenderer))
			{
				TextRenderer* tr = (TextRenderer*)comp;
				/*
					Text->font->alignment->r->g->b->a->size->
				*/

				prefabStream << "TEXT-RENDERER->";
				prefabStream << tr->GetText() << "->";
				prefabStream << tr->GetFont()->GetName() << "->";
				prefabStream << (int)tr->GetTextAlignment() << "->";
				prefabStream << tr->GetColour().r << "->";
				prefabStream << tr->GetColour().g << "->";
				prefabStream << tr->GetColour().b << "->";
				prefabStream << tr->GetColour().a << "->";
				prefabStream << tr->GetTextSize() << "->";

			}
			else if (typeid(*comp) == typeid(TileMapRenderer))
			{
				TileMapRenderer* tmr = (TileMapRenderer*)comp;
				/*tileSet -> tileMap*/
				prefabStream << tmr->GetTileSet()->GetName() << "->";
				prefabStream << tmr->GetTileMap()->GetName() << "->";
			}
			else if (typeid(*comp) == typeid(ParticleEmitter))
			{
				/*INTENTIONALLY LEFT BLANK. EMITTERS ARE ##NOT## USED TO WRITE PARTICLE INFORMATION*/
				/*SEE BELOW FOR PARTICLE PROPERTIES.*/
			}
			else if (typeid(*comp) == typeid(ParticleProperties))
			{
				ParticleProperties* pep = (ParticleProperties*)comp;
				/*particleFlags->CatagoryBits->MaskBits->Radius*/
				prefabStream << "EMITTER->";
				prefabStream << pep->GetParticleFlags() << "->";
				prefabStream << pep->GetColliderFilters()->categoryBits << "->";
				prefabStream << pep->GetColliderFilters()->maskBits << "->";
				prefabStream << pep->GetRadius() << "->\n";

			}

			if (i != prefab->m_Components.size() - 1)
			{
				prefabStream << "\n";
			}

		}

		prefabStream.close();

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

		std::vector<std::vector<int>> dataConverted;

		if (fileStream.is_open())
		{
			/* Variables for opening and reading the file. */
			std::string line;

			/* Read the file line by line. */
			while (getline(fileStream, line))
			{

				/* Quick Variables. */
				size_t searchPosition = 0;
				std::vector<std::string> data;
				std::string lineSplitter = ",";

				/* Keep Searching till we reach the end of the Line.*/
				while ((searchPosition = line.find(lineSplitter)) != std::string::npos)
				{
					data.push_back(line.substr(0, searchPosition));

					line.erase(0, searchPosition + lineSplitter.length());
				}
				
				line = line;

				data.push_back(line);

				dataConverted.push_back(std::vector<int>());

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
		std::vector<Sprite*> sprites;

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
				material->SetDiffuse(ResourceManager::GetResource<Sprite>(materialDiffuseSprite));

			else
				material->SetDiffuse(ResourceManager::GetResource<Sprite>("Diffuse"));

			if (materialNormalSprite != "*")
				material->SetNormal(ResourceManager::GetResource<Sprite>(materialNormalSprite));

			else
				material->SetNormal(ResourceManager::GetResource<Sprite>("Normal"));

			if (materialSpecularSprite != "*")
				material->SetSpecular(ResourceManager::GetResource<Sprite>(materialSpecularSprite));

			else
				material->SetSpecular(ResourceManager::GetResource<Sprite>("Specular"));

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
		std::vector<std::string> animationKeyFrameData;

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

			std::vector<Texture*> textures = ResourceManager::GetTextures();
			std::vector<TextureType> ignoreTextures = Atlas::GetIgnoreTextureTypes();

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
		std::vector<std::string> spriteData;
		
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
		std::vector<std::string> textureData;

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
		texture->Finalise();

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