/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Sprite.h"

#include "../../Manager/ResourceManager.h"

namespace Kross
{
	Sprite::~Sprite()
	{
		/* Null out Texture and Geomerty. */
		p_Texture = nullptr;
		m_Geometry = nullptr;
	}

	Sprite* Sprite::OnCreate(Texture* texture, int width, int height, const std::string& name)
	{
		/* Sprite Creation. */
		Sprite* sprite = new Sprite();
		sprite->SetName(name);
		sprite->SetWidth(width);
		sprite->SetHeight(height);
		sprite->SetTexture(texture);

		/* Set UV Data. (DEFAULT FULL RESOLUTION) */
		sprite->SetUVRatio(Vector2(1.0f));
		sprite->SetUVOffset(Vector2(0.0f));

		/* Add all of the Geometry Data needed. */
		sprite->AttachGeometryData();

		/* Attach the Sprite to the Resource Manager. */
		ResourceManager::AttachResource<Sprite>(sprite);

		/* Return the new Sprite. */
		return sprite;
	}

	Sprite* Sprite::OnCreate(Texture* texture, int width, int height, Vector2 offset, const std::string& name)
	{
		/* Sprite Creation. */
		Sprite* sprite = new Sprite();
		sprite->SetName(name);
		sprite->SetWidth(width);
		sprite->SetHeight(height);
		sprite->SetTexture(texture);

		/* UV Ratio Variable. */
		Vector2 ratio = Vector2(0.0f);
		ratio.x = (float)width / (float)texture->GetWidth();
		ratio.y = (float)height / (float)texture->GetHeight();

		/* Set UV Ratio Data. */
		sprite->SetUVRatio(Vector2((float)ratio.x, (float)ratio.y));

		/* UV Offset Variable. */
		offset.x = (float)offset.x / (float)texture->GetWidth();
		offset.y = (float)(texture->GetHeight() - height - (int)offset.y) / (float)texture->GetHeight();

		/* Set UV Offset Data. */
		sprite->SetUVOffset(Vector2((float)offset.x, (float)offset.y));

		/* Add all of the Geometry Data needed. */
		sprite->AttachGeometryData();

		/* Attach the Sprite to the Resource Manager. */
		ResourceManager::AttachResource<Sprite>(sprite);

		/* Return the new Sprite. */
		return sprite;
	}

	List<Sprite*> Sprite::OnCreate(Texture* texture, int width, int height)
	{
		/* Create the List. */
		List<Sprite*> spriteList = List<Sprite*>();

		/* Get the Max Number of Sprites Up and Down. */
		int maxHorizontalSprites = texture->GetWidth() / width;
		int maxVerticalSprites = texture->GetHeight() / height;

		unsigned int charIndex = 0;

		/* Create the Sprites. */
		for(int y = 0; y < maxVerticalSprites; y++)
			for (int x = 0; x < maxHorizontalSprites; x++)
			{
				/* Sprite Creation. */
				Sprite* sprite = new Sprite();
				std::string name = std::to_string((unsigned char)(charIndex));

				sprite->SetName(name);
				sprite->SetWidth(width);
				sprite->SetHeight(height);
				sprite->SetTexture(texture);

				/* UV Ratio Variable. */
				Vector2 ratio = Vector2(0.0f);
				ratio.x = (float)width / (float)texture->GetWidth();
				ratio.y = (float)height / (float)texture->GetHeight();

				/* Set UV Ratio Data. */
				sprite->SetUVRatio(Vector2((float)ratio.x, (float)ratio.y));

				/* UV Offset Variable. */
				Vector2 offset = Vector2(0.0f);
				offset.x = (float)(x * width) / (float)texture->GetWidth();
				offset.y = (float)(texture->GetHeight() - height - (int)(y * width)) / (float)texture->GetHeight();

				/* Set UV Offset Data. */
				sprite->SetUVOffset(Vector2((float)offset.x, (float)offset.y));

				/* Add all of the Geometry Data needed. */
				sprite->AttachGeometryData();

				/* Add it to the List. */
				spriteList.push_back(sprite);
			}

		/* Once Finished return the list. */
		return spriteList;
	}

	void Sprite::OnDestroy(Sprite* sprite)
	{
		/* Safe programming, not really needed but good to have. */
		if (sprite)
			delete sprite;
	}

	void Sprite::AttachGeometryData()
	{
		/* Base Sprite Width and Height. */
		const int baseSWH = 128;

		/* Get the name of the Geometry. */
		std::string name = std::to_string(m_Width) + "x" + std::to_string(m_Height);

		/* Search for pre existsing Geometry with these dimentions. */
		Geometry* geometry = ResourceManager::GetResource<Geometry>(name);

		/* If Geometry exists already of these dimentions then use it. */
		if (geometry)
		{
			m_Geometry = geometry;
			return;
		}

		/* Otherwise create it. */

		/* Set the name of the Geometry. */
		m_Geometry->SetName(name);

		/* Set Render Mode for Geometry. */
		m_Geometry->SetRenderMode(RenderMode::Solid);

		/* Get the Width and Height in World Space. */
		float width = ((float)m_Width / (float)baseSWH) / 2.0f;
		float height = ((float)m_Height / (float)baseSWH) / 2.0f;

		/* Add Vertexes. */
		m_Geometry->AttachVertex(Vertex(Vector2( width,  height), Vector2(1.0f, 1.0f), Colour(1.0f)));
		m_Geometry->AttachVertex(Vertex(Vector2( width, -height), Vector2(1.0f, 0.0f), Colour(1.0f)));
		m_Geometry->AttachVertex(Vertex(Vector2(-width, -height), Vector2(0.0f, 0.0f), Colour(1.0f)));
		m_Geometry->AttachVertex(Vertex(Vector2(-width,  height), Vector2(0.0f, 1.0f), Colour(1.0f)));

		/* Attach new Geometry to the global resources. */
		ResourceManager::AttachResource<Geometry>(m_Geometry);
	}

	void Sprite::OnRender()
	{
		m_Geometry->OnRenderGeometry();
	}
}