/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#pragma once

#include "../Core.h"

#include "../Renderer/Image/Atlas.h"
#include "../Renderer/Shader/Shader.h"
#include "../Renderer/Text/Font.h"
#include "../Renderer/Material.h"
#include "../Animation/Animation.h"
#include "../Audio/AudioSource.h"
#include "../Renderer/Tilemap/TileMap.h"
#include "../Renderer/Tilemap/TileSet.h"
#include "../Object.h"

#include "ShaderManager.h"

namespace Kross
{
	class KROSS_API Script;

	class KROSS_API ResourceManager
	{
	private:
		ResourceManager() :
			m_Geometry		(List<Geometry*>()),
			m_Shaders		(List<Shader*>()),
			m_Sprites		(List<Sprite*>()),
			m_Textures		(List<Texture*>()),
			m_Materials		(List<Material*>()),
			m_Fonts			(List<Font*>()),
			m_Animations	(List<Animation*>()),
			m_AudioSources  (List<AudioSource*>()),
			m_TileMaps		(List<TileMap*>()),
			m_TileSets      (List<TileSet*>()),
			m_Prefabs		(List<Object*>()),
			p_Atlas			(nullptr)
		{};
		~ResourceManager();

		static ResourceManager* s_Instance;

		List<Geometry*> m_Geometry;
		List<Shader*> m_Shaders;
		List<Sprite*> m_Sprites;
		List<Texture*> m_Textures;
		List<Material*> m_Materials;
		List<Font*> m_Fonts;
		List<Animation*> m_Animations;
		List<AudioSource*> m_AudioSources;
		List<TileMap*> m_TileMaps;
		List<TileSet*> m_TileSets;
		List<Object*> m_Prefabs;

		Atlas* p_Atlas;

	public:
		// Creates an Instance of the Manager.
		static void OnCreate();

		// Destroys an Instance of the Manager.
		static void OnDestroy();

		// Base Template Class. (DO NOT USE)
		template<typename Type>
		static Type* GetResource(const std::string& name)
		{
			static_assert(false, "Resource must be a Resource Type!");
		}

		// Base Template Class. (DO NOT USE)
		template<typename Type>
		static Type* GetResource(int index)
		{
			static_assert(false, "Resource must be a Resource Type!");
		}

		// Base Template Class. (DO NOT USE)
		template<typename Type>
		static void AttachResource(Type* resource)
		{
			static_assert(false, "Resource must be a Resource Type!");
		}

		// Base Template Class. (DO NOT USE)
		template<typename Type>
		static void DetachResource(Type* resource)
		{
			static_assert(false, "Resource must be a Resource Type!");
		}

		#pragma region SHADERS

		// Gets Shader by name from Resource Manager.
		template<>
		static Shader* GetResource<Shader>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_Shaders.size(); i++)
			{
				/* If the name of the Shader matches the name requested, return that Shader. */
				if (s_Instance->m_Shaders[i]->GetName() == name)
				{
					Shader* shaderCopy;

					/* Return a copy of the Shader so that whatever is using it can have its own version of it. */
					if(s_Instance->m_Shaders[i]->GetGeometryFilepath() != "")
						shaderCopy = Shader::OnCreate(s_Instance->m_Shaders[i]->GetVertexFilepath(), s_Instance->m_Shaders[i]->GetFragmentFilepath(), s_Instance->m_Shaders[i]->GetGeometryFilepath(), s_Instance->m_Shaders[i]->GetName() + " - Copy");

					else
						shaderCopy = Shader::OnCreate(s_Instance->m_Shaders[i]->GetVertexFilepath(), s_Instance->m_Shaders[i]->GetFragmentFilepath(), s_Instance->m_Shaders[i]->GetName() + " - Copy");

					/* Remove the Shader from the Resource Manager that was just created. */
					DetachResource<Shader>(shaderCopy);

					/* Add Shader to the Shader Manager. */
					ShaderManager::AttachShader(shaderCopy);

					return shaderCopy;
				}
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Shader by name from Resource Manager.
		template<>
		static Shader* GetResource<Shader>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_Shaders.size())
			{
				Shader* shaderCopy;

				/* Return a copy of the Shader so that whatever is using it can have its own version of it. */
				if (s_Instance->m_Shaders[index]->GetGeometryFilepath() != "")
					shaderCopy = Shader::OnCreate(s_Instance->m_Shaders[index]->GetVertexFilepath(), s_Instance->m_Shaders[index]->GetFragmentFilepath(), s_Instance->m_Shaders[index]->GetGeometryFilepath(), s_Instance->m_Shaders[index]->GetName() + " - Copy");

				else
					shaderCopy = Shader::OnCreate(s_Instance->m_Shaders[index]->GetVertexFilepath(), s_Instance->m_Shaders[index]->GetFragmentFilepath(), s_Instance->m_Shaders[index]->GetName() + " - Copy");

				/* Remove the Shader from the Resource Manager that was just created. */
				DetachResource<Shader>(shaderCopy);

				/* Add Shader to the Shader Manager. */
				ShaderManager::AttachShader(shaderCopy);

				return shaderCopy;
			}

			/* If not, return null. */
			return nullptr;
		}

		// Adds Shader to the Resource Manager.
		template<>
		static void AttachResource<Shader>(Shader* shader)
		{
			s_Instance->m_Shaders.push_back(shader);
		}

		// Removes a Shader from the  Resource Manager.
		template<>
		static void DetachResource<Shader>(Shader* shader)
		{
			/* Go through the Shader List. */
			for (int i = 0; i < s_Instance->m_Shaders.size(); i++)
			{
				/* if the Shader is the same as the one specified. Remove it.*/
				if (s_Instance->m_Shaders[i] == shader)
				{
					Shader::OnDestroy(s_Instance->m_Shaders[i]);
					s_Instance->m_Shaders.erase(s_Instance->m_Shaders.begin() + i);
				}
			}
		}

		#pragma endregion

		#pragma region SPRITES

		// Gets Sprite by name from Resource Manager.
		template<>
		static Sprite* GetResource<Sprite>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_Sprites.size(); i++)
			{
				/* If the name of the Sprite matches the name requested, return that Sprite. */
				if (s_Instance->m_Sprites[i]->GetName() == name)
					return s_Instance->m_Sprites[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Sprite by name from Resource Manager.
		template<>
		static Sprite* GetResource<Sprite>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_Sprites.size())
				return s_Instance->m_Sprites[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Sprite to the Resource Manager.
		template<>
		static void AttachResource<Sprite>(Sprite* sprite)
		{
			s_Instance->m_Sprites.push_back(sprite);
		}

		// Removes a Sprite from the  Resource Manager.
		template<>
		static void DetachResource<Sprite>(Sprite* sprite)
		{
			/* Go through the Sprite List. */
			for (int i = 0; i < s_Instance->m_Sprites.size(); i++)
			{
				/* if the Sprte is the  same as the one specified. Remove it.*/
				if (s_Instance->m_Sprites[i] == sprite)
				{
					Sprite::OnDestroy(s_Instance->m_Sprites[i]);
					s_Instance->m_Sprites.erase(s_Instance->m_Sprites.begin() + i);
				}
			}
		}

		#pragma endregion

		#pragma region TEXTURES

		// Gets Texture by name from Resource Manager.
		template<>
		static Texture* GetResource<Texture>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_Textures.size(); i++)
			{
				/* If the name of the Texture matches the name requested, return that Texture. */
				if (s_Instance->m_Textures[i]->GetName() == name)
					return s_Instance->m_Textures[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Texture by name from Resource Manager.
		template<>
		static Texture* GetResource<Texture>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_Textures.size())
				return s_Instance->m_Textures[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Texture to the Resource Manager.
		template<>
		static void AttachResource<Texture>(Texture* texture)
		{
			s_Instance->m_Textures.push_back(texture);
		}

		// Removes a Texture from the  Resource Manager.
		template<>
		static void DetachResource<Texture>(Texture* texture)
		{
			/* Go through the Texture List. */
			for (int i = 0; i < s_Instance->m_Textures.size(); i++)
			{
				/* if the Texture is the same as the one specified. Remove it.*/
				if (s_Instance->m_Textures[i] == texture)
				{
					Texture::OnDestroy(s_Instance->m_Textures[i]);
					s_Instance->m_Textures.erase(s_Instance->m_Textures.begin() + i);
				}
			}
		}

		#pragma endregion

		#pragma region FONTS 

		// Gets Font by name from Resource Manager.
		template<>
		static Font* GetResource<Font>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_Fonts.size(); i++)
			{
				/* If the name of the Font matches the name requested, return that Font. */
				if (s_Instance->m_Fonts[i]->GetName() == name)
					return s_Instance->m_Fonts[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Font by name from Resource Manager.
		template<>
		static Font* GetResource<Font>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_Fonts.size())
				return s_Instance->m_Fonts[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Font to the Resource Manager.
		template<>
		static void AttachResource<Font>(Font* font)
		{
			s_Instance->m_Fonts.push_back(font);
		}

		// Removes a Font from the Resource Manager.
		template<>
		static void DetachResource<Font>(Font* font)
		{
			/* Go through the Font List. */
			for (int i = 0; i < s_Instance->m_Fonts.size(); i++)
			{
				/* if the Font is the same as the one specified. Remove it.*/
				if (s_Instance->m_Fonts[i] == font)
				{
					Font::OnDestroy(s_Instance->m_Fonts[i]);
					s_Instance->m_Fonts.erase(s_Instance->m_Fonts.begin() + i);
				}
			}
		}

		#pragma endregion

		#pragma region MATERIALS

		// Gets Material by name from Resource Manager.
		template<>
		static Material* GetResource<Material>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_Materials.size(); i++)
			{
				/* If the name of the Material matches the name requested, return that Material. */
				if (s_Instance->m_Materials[i]->GetName() == name)
					return s_Instance->m_Materials[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Material by name from Resource Manager.
		template<>
		static Material* GetResource<Material>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_Materials.size())
				return s_Instance->m_Materials[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Material to the Resource Manager.
		template<>
		static void AttachResource<Material>(Material* material)
		{
			s_Instance->m_Materials.push_back(material);
		}

		// Removes a Material from the Resource Manager.
		template<>
		static void DetachResource<Material>(Material* material)
		{
			/* Go through the Material List. */
			for (int i = 0; i < s_Instance->m_Materials.size(); i++)
			{
				/* if the Material is the same as the one specified. Remove it.*/
				if (s_Instance->m_Materials[i] == material)
				{
					Material::OnDestroy(s_Instance->m_Materials[i]);
					s_Instance->m_Materials.erase(s_Instance->m_Materials.begin() + i);
				}
			}
		}

		#pragma endregion

		#pragma region ANIMATIONS

		// Gets Animation by name from Resource Manager.
		template<>
		static Animation* GetResource<Animation>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_Animations.size(); i++)
			{
				/* If the name of the Animation matches the name requested, return that Animation. */
				if (s_Instance->m_Animations[i]->GetName() == name)
					return KROSS_NEW Animation(*s_Instance->m_Animations[i]);
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Animation by name from Resource Manager.
		template<>
		static Animation* GetResource<Animation>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_Animations.size())
				return KROSS_NEW Animation(*s_Instance->m_Animations[index]);

			/* If not, return null. */
			return nullptr;
		}

		// Adds Animation to the Resource Manager.
		template<>
		static void AttachResource<Animation>(Animation* animation)
		{
			s_Instance->m_Animations.push_back(animation);
		}

		// Removes a Animation from the Resource Manager.
		template<>
		static void DetachResource<Animation>(Animation* animation)
		{
			/* Go through the Animation List. */
			for (int i = 0; i < s_Instance->m_Animations.size(); i++)
			{
				/* if the Animation is the same as the one specified. Remove it.*/
				if (s_Instance->m_Animations[i] == animation)
				{
					Animation::OnDestroy(s_Instance->m_Animations[i]);
					s_Instance->m_Animations.erase(s_Instance->m_Animations.begin() + i);
				}
			}
		}

		#pragma endregion

		#pragma region AUDIO SOURCES

		// Gets Audio Source by name from Resource Manager.
		template<>
		static AudioSource* GetResource<AudioSource>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_AudioSources.size(); i++)
			{
				/* If the name of the Audio Source matches the name requested, return that Audio Source. */
				if (s_Instance->m_AudioSources[i]->GetName() == name)
					return s_Instance->m_AudioSources[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Audio Source by name from Resource Manager.
		template<>
		static AudioSource* GetResource<AudioSource>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_AudioSources.size())
				return s_Instance->m_AudioSources[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Audio Source to the Resource Manager.
		template<>
		static void AttachResource<AudioSource>(AudioSource* audioSource)
		{
			s_Instance->m_AudioSources.push_back(audioSource);
		}

		// Removes a Audio Source from the Resource Manager.
		template<>
		static void DetachResource<AudioSource>(AudioSource* audioSource)
		{
			/* Go through the Audio Sources List. */
			for (int i = 0; i < s_Instance->m_AudioSources.size(); i++)
			{
				/* if the Audio Source is the same as the one specified. Remove it.*/
				if (s_Instance->m_AudioSources[i] == audioSource)
				{
					AudioSource::OnDestroy(s_Instance->m_AudioSources[i]);
					s_Instance->m_AudioSources.erase(s_Instance->m_AudioSources.begin() + i);
				}
			}
		}

		#pragma endregion

		#pragma region TILEMAPS

		// Gets TileMap by name from Resource Manager.
		template<>
		static TileMap* GetResource<TileMap>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_TileMaps.size(); i++)
			{
				/* If the name of the Audio Source matches the name requested, return that Audio Source. */
				if (s_Instance->m_TileMaps[i]->GetName() == name)
					return s_Instance->m_TileMaps[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets TileMap by name from Resource Manager.
		template<>
		static TileMap* GetResource<TileMap>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_TileMaps.size())
				return s_Instance->m_TileMaps[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds TileMap to the Resource Manager.
		template<>
		static void AttachResource<TileMap>(TileMap* TileMap)
		{
			s_Instance->m_TileMaps.push_back(TileMap);
		}

		// Removes a TileMap from the Resource Manager.
		template<>
		static void DetachResource<TileMap>(TileMap* TileMap)
		{
			/* Go through the TileMap List. */
			for (int i = 0; i < s_Instance->m_TileMaps.size(); i++)
			{
				/* if the TileMap is the same as the one specified. Remove it.*/
				if (s_Instance->m_TileMaps[i] == TileMap)
				{
					TileMap::OnDestroy(s_Instance->m_TileMaps[i]);
					s_Instance->m_TileMaps.erase(s_Instance->m_TileMaps.begin() + i);
				}
			}
		}

#pragma endregion

		#pragma region TILESETS

		// Gets TileMap by name from Resource Manager.
		template<>
		static TileSet* GetResource<TileSet>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_TileSets.size(); i++)
			{
				/* If the name of the TileSet matches the name requested, return that TileSet. */
				if (s_Instance->m_TileSets[i]->GetName() == name)
					return s_Instance->m_TileSets[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets TileSet by name from Resource Manager.
		template<>
		static TileSet* GetResource<TileSet>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_TileSets.size())
				return s_Instance->m_TileSets[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds TileSet to the Resource Manager.
		template<>
		static void AttachResource<TileSet>(TileSet* TileSet)
		{
			s_Instance->m_TileSets.push_back(TileSet);
		}

		// Removes a TileSet from the Resource Manager.
		template<>
		static void DetachResource<TileSet>(TileSet* TileSet)
		{
			/* Go through the TileSet List. */
			for (int i = 0; i < s_Instance->m_TileSets.size(); i++)
			{
				/* if the TileSet is the same as the one specified. Remove it.*/
				if (s_Instance->m_TileSets[i] == TileSet)
				{
					TileSet::OnDestroy(s_Instance->m_TileSets[i]);
					s_Instance->m_TileSets.erase(s_Instance->m_TileSets.begin() + i);
				}
			}
		}

#pragma endregion

		#pragma region PREFABS

		// Gets Prefab by name from Resource Manager.
		template<>
		static Object* GetResource<Object>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_Prefabs.size(); i++)
			{
				/* If the name of the Prefab matches the name requested, return that Prefab. */
				if (s_Instance->m_Prefabs[i]->GetName() == name)
					return s_Instance->m_Prefabs[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Prefab by name from Resource Manager.
		template<>
		static Object* GetResource<Object>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_Prefabs.size())
				return s_Instance->m_Prefabs[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Prefab to the Resource Manager.
		template<>
		static void AttachResource<Object>(Object* object)
		{
			if(!object->IsPrefab())
				s_Instance->m_Prefabs.push_back(object);
		}

		// Removes a Prefab from the Resource Manager.
		template<>
		static void DetachResource<Object>(Object* object)
		{
			/* Early out if the object is not a Prefab. */
			if (!object->IsPrefab())
				return;

			/* Go through the Prefab List. */
			for (int i = 0; i < s_Instance->m_Prefabs.size(); i++)
			{
				/* if the Prefab is the same as the one specified. Remove it.*/
				if (s_Instance->m_Prefabs[i] == object)
				{
					Object::OnDestroy(s_Instance->m_Prefabs[i]);
					s_Instance->m_Prefabs.erase(s_Instance->m_Prefabs.begin() + i);

					return;
				}
			}
		}

		#pragma endregion

		// Gets the Atlas.
		static Atlas* GetAtlas() { return s_Instance->p_Atlas; };

	/* ------ Protected has been moved down here due to this function overload. ------ */
	protected:
		friend class Sprite;
		friend class Atlas;
		friend class FileSystem;

		friend class Application;

		friend class AssetPreview;
		friend class AssetPanel;

		#pragma region GEOMETRY

		// Gets Geometry by name from Resource Manager.
		template<>
		static Geometry* GetResource<Geometry>(const std::string& name)
		{
			for (int i = 0; i < s_Instance->m_Geometry.size(); i++)
			{
				/* If the name of the Geometry matches the name requested, return that Geometry. */
				if (s_Instance->m_Geometry[i]->GetName() == name)
					return s_Instance->m_Geometry[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Geometry by name from Resource Manager.
		template<>
		static Geometry* GetResource<Geometry>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Instance->m_Geometry.size())
				return s_Instance->m_Geometry[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Geometry to the Resource Manager.
		template<>
		static void AttachResource<Geometry>(Geometry* geometry)
		{
			s_Instance->m_Geometry.push_back(geometry);
		}

		// Removes a Geometry from the  Resource Manager.
		template<>
		static void DetachResource<Geometry>(Geometry* geometry)
		{
			/* Go through the Geometry List. */
			for (int i = 0; i < s_Instance->m_Geometry.size(); i++)
			{
				/* if the Geometry is the same as the one specified. Remove it.*/
				if (s_Instance->m_Geometry[i] == geometry)
				{
					delete s_Instance->m_Geometry[i];
					s_Instance->m_Geometry.erase(s_Instance->m_Geometry.begin() + i);
				}
			}
		}

		#pragma endregion

		// Grabs all of the Textures loaded.
		static List<Texture*> GetTextures() { return s_Instance->m_Textures; };

		// Grabs all of the Sprites Created.
		static List<Sprite*> GetSprites() { return s_Instance->m_Sprites; };

		// Reads the Manifest File.
		static void OnReadManifest();

		// Writes the Mainfest File.
		static void OnWriteManifest();


		// Adds a Atlas to the Resource Manager.
		template<>
		static void AttachResource<Atlas>(Atlas* atlas)
		{
			/* If we already have an Atlas. */
			if (s_Instance->p_Atlas)
				Atlas::OnDestroy(s_Instance->p_Atlas);

			/* Set the New One. */
			s_Instance->p_Atlas = atlas;
		}
	};
}