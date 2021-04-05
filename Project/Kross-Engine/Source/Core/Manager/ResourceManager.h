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

	protected:
		friend class Sprite;

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
			if(index >= 0 && index < s_Geometry.size())
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

		/* -------------------- */

	public:
		// Creates an Instance of the Manager.
		static void OnCreate();

		// Destroys an Instance of the Manager.

		static void OnDestroy();
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
					Shader* shaderCopy = Shader::OnCreate(s_Shaders[i]->GetVertexFilepath(), s_Shaders[i]->GetFragmentFilepath(), s_Shaders[i]->GetName());
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
				return s_Shaders[index];

			/* If not, return null. */
			return nullptr;
		}

		// Adds Shader to the Resource Manager.
		template<>
		static void AttachResource<Shader>(Shader* shader)
		{
			s_Shaders.push_back(shader);
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

		/* -------------------- */

	};
}