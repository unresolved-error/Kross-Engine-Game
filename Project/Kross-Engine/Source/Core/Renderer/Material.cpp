/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Material.h"
#include "../Manager/ResourceManager.h"

namespace Kross
{
	Material::~Material()
	{
		m_Diffuse = nullptr;
		m_Normal = nullptr;
		m_Specular = nullptr;
	}

	Material* Material::OnCreate(const std::string& name)
	{
		/* Creates a New Material. */
		Material* material = new Material();

		/* Set the Name of the Material. */
		material->SetName(name);

		/* Attach the Material to the Resource Manager. */
		ResourceManager::AttachResource<Material>(material);

		/* Return the new Material. */
		return material;
	}

	void Material::OnDestroy(Material* material)
	{
		/* Safe programming, not needed but good to have. */
		if (material)
		{
			delete material;
		}
	}
}