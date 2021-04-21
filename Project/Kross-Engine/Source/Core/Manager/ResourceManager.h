/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Renderer/Image/Sprite.h"
#include "../Renderer/Image/Texture.h"
#include "../Renderer/Shader/Shader.h"
#include "../Renderer/Text/Font.h"

#include "ShaderManager.h"

namespace Kross
{
	class KROSS_API ResourceManager
	{
	private:
		ResourceManager() {};
		~ResourceManager();

		static ResourceManager* s_Instance;

		static List<Geometry*> s_Geometry;
		static List<Shader*> s_Shaders;
		static List<Sprite*> s_Sprites;
		static List<Texture*> s_Textures;
		static List<Font*> s_Fonts;

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

		/* ----- SHADERS ----- */

		// Gets Shader by name from Resource Manager.
		template<>
		static Shader* GetResource<Shader>(const std::string& name)
		{
			for (int i = 0; i < s_Shaders.size(); i++)
			{
				/* If the name of the Shader matches the name requested, return that Shader. */
				if (s_Shaders[i]->GetName() == name)
				{
					/* Return a copy of the Shader so that whatever is using it can have its own version of it. */
					Shader* shaderCopy = Shader::OnCreate(s_Shaders[i]->GetVertexFilepath(), s_Shaders[i]->GetFragmentFilepath(), s_Shaders[i]->GetName() + " - Copy");

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
			if (index >= 0 && index < s_Shaders.size())
			{
				/* Return a copy of the Shader so that whatever is using it can have its own version of it. */
				Shader* shaderCopy = Shader::OnCreate(s_Shaders[index]->GetVertexFilepath(), s_Shaders[index]->GetFragmentFilepath(), s_Shaders[index]->GetName());

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
			s_Shaders.push_back(shader);
		}

		// Removes a Shader from the  Resource Manager.
		template<>
		static void DetachResource<Shader>(Shader* shader)
		{
			/* Go through the Shader List. */
			for (int i = 0; i < s_Shaders.size(); i++)
			{
				/* if the Shader is the same as the one specified. Remove it.*/
				if (s_Shaders[i] == shader)
				{
					Shader::OnDestroy(s_Shaders[i]);
					s_Shaders.erase(s_Shaders.begin() + i);
				}
			}
		}

		/* ------------------- */

		/* ----- SPRITES ----- */

		// Gets Sprite by name from Resource Manager.
		template<>
		static Sprite* GetResource<Sprite>(const std::string& name)
		{
			for (int i = 0; i < s_Sprites.size(); i++)
			{
				/* If the name of the Sprite matches the name requested, return that Sprite. */
				if (s_Sprites[i]->GetName() == name)
					return s_Sprites[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Sprite by name from Resource Manager.
		template<>
		static Sprite* GetResource<Sprite>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Sprites.size())
				return s_Sprites[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Sprite to the Resource Manager.
		template<>
		static void AttachResource<Sprite>(Sprite* sprite)
		{
			s_Sprites.push_back(sprite);
		}

		// Removes a Sprite from the  Resource Manager.
		template<>
		static void DetachResource<Sprite>(Sprite* sprite)
		{
			/* Go through the Sprite List. */
			for (int i = 0; i < s_Sprites.size(); i++)
			{
				/* if the Sprte is the  same as the one specified. Remove it.*/
				if (s_Sprites[i] == sprite)
				{
					Sprite::OnDestroy(s_Sprites[i]);
					s_Sprites.erase(s_Sprites.begin() + i);
				}
			}
		}

		/* ------------------- */

		/* ----- TEXTURES ----- */

		// Gets Texture by name from Resource Manager.
		template<>
		static Texture* GetResource<Texture>(const std::string& name)
		{
			for (int i = 0; i < s_Textures.size(); i++)
			{
				/* If the name of the Texture matches the name requested, return that Texture. */
				if (s_Textures[i]->GetName() == name)
					return s_Textures[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Texture by name from Resource Manager.
		template<>
		static Texture* GetResource<Texture>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Textures.size())
				return s_Textures[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Texture to the Resource Manager.
		template<>
		static void AttachResource<Texture>(Texture* texture)
		{
			s_Textures.push_back(texture);
		}

		// Removes a Texture from the  Resource Manager.
		template<>
		static void DetachResource<Texture>(Texture* texture)
		{
			/* Go through the Texture List. */
			for (int i = 0; i < s_Textures.size(); i++)
			{
				/* if the Texture is the same as the one specified. Remove it.*/
				if (s_Textures[i] == texture)
				{
					Texture::OnDestroy(s_Textures[i]);
					s_Textures.erase(s_Textures.begin() + i);
				}
			}
		}

		/* -------------------- */

		/* ------- FONTS ------ */

		// Gets Font by name from Resource Manager.
		template<>
		static Font* GetResource<Font>(const std::string& name)
		{
			for (int i = 0; i < s_Fonts.size(); i++)
			{
				/* If the name of the Font matches the name requested, return that Font. */
				if (s_Fonts[i]->GetName() == name)
					return s_Fonts[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Font by name from Resource Manager.
		template<>
		static Font* GetResource<Font>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Fonts.size())
				return s_Fonts[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Font to the Resource Manager.
		template<>
		static void AttachResource<Font>(Font* font)
		{
			s_Fonts.push_back(font);
		}

		// Removes a Font from the  Resource Manager.
		template<>
		static void DetachResource<Font>(Font* font)
		{
			/* Go through the Font List. */
			for (int i = 0; i < s_Fonts.size(); i++)
			{
				/* if the Font is the same as the one specified. Remove it.*/
				if (s_Fonts[i] == font)
				{
					Font::OnDestroy(s_Fonts[i]);
					s_Fonts.erase(s_Fonts.begin() + i);
				}
			}
		}

		/* -------------------- */

	/* ------ Protected has been moved down here due to this function overload. ------ */
	protected:
		friend class Sprite;

		/* ----- GEOMETRY ----- */

		// Gets Geometry by name from Resource Manager.
		template<>
		static Geometry* GetResource<Geometry>(const std::string& name)
		{
			for (int i = 0; i < s_Geometry.size(); i++)
			{
				/* If the name of the Geometry matches the name requested, return that Geometry. */
				if (s_Geometry[i]->GetName() == name)
					return s_Geometry[i];
			}

			/* If nothing was found. */
			return nullptr;
		}

		// Gets Geometry by name from Resource Manager.
		template<>
		static Geometry* GetResource<Geometry>(int index)
		{
			/* If the Index is in the bounds of the List. */
			if (index >= 0 && index < s_Geometry.size())
				return s_Geometry[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Geometry to the Resource Manager.
		template<>
		static void AttachResource<Geometry>(Geometry* geometry)
		{
			s_Geometry.push_back(geometry);
		}

		// Removes a Geometry from the  Resource Manager.
		template<>
		static void DetachResource<Geometry>(Geometry* geometry)
		{
			/* Go through the Geometry List. */
			for (int i = 0; i < s_Geometry.size(); i++)
			{
				/* if the Geometry is the same as the one specified. Remove it.*/
				if (s_Geometry[i] == geometry)
				{
					delete s_Geometry[i];
					s_Geometry.erase(s_Geometry.begin() + i);
				}
			}
		}

		/* -------------------- */
	};
}