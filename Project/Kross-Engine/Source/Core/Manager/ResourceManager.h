/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Renderer/Image/Atlas.h"
#include "../Renderer/Shader/Shader.h"
#include "../Renderer/Text/Font.h"
#include "../Renderer/Material.h"

#include "ShaderManager.h"

namespace Kross
{
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
				/* If the name of the Font matches the name requested, return that Font. */
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

		// Gets the Atlas.
		static Atlas* GetAtlas() { return s_Instance->p_Atlas; };

	/* ------ Protected has been moved down here due to this function overload. ------ */
	protected:
		friend class Sprite;
		friend class Atlas;

		friend class Application;

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

		// Adds a Atlas to the Resource Manager.
		template<>
		static void AttachResource<Atlas>(Atlas* atlas)
		{
			/* If we already have an Atlas. */
			//if (s_Atlas)
			//	Atlas::OnDestroy(s_Atlas); // NOT WORKING!

			/* Set the New One. */
			s_Instance->p_Atlas = atlas;
		}
	};
}