/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Sprite.h"

namespace Kross
{
	Sprite::~Sprite()
	{
		/* For now will be handled inside of a Resource Manager. */
		Texture::OnDestroy(m_Texture);
		delete m_Geometry;

		/* Null out Texture and Geomerty. */
		m_Texture = nullptr;
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

		/* Return the new Sprite. */
		return sprite;
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

		/* Get the Width and Height in World Space. */
		float width = ((float)m_Width / (float)baseSWH) / 2.0f;
		float height = ((float)m_Height / (float)baseSWH) / 2.0f;

		/* Set Render Mode for Geometry. */
		m_Geometry->SetRenderMode(RenderMode::Solid);

		/* Add Vertexes. */
		m_Geometry->AttachVertex(Vertex(Vector2( width,  height), Vector2(1.0f, 1.0f), Colour(1.0f)));
		m_Geometry->AttachVertex(Vertex(Vector2( width, -height), Vector2(1.0f, 0.0f), Colour(1.0f)));
		m_Geometry->AttachVertex(Vertex(Vector2(-width, -height), Vector2(0.0f, 0.0f), Colour(1.0f)));
		m_Geometry->AttachVertex(Vertex(Vector2(-width,  height), Vector2(0.0f, 1.0f), Colour(1.0f)));
	}

	void Sprite::OnRender()
	{
		m_Geometry->OnRenderGeometry();
	}
}