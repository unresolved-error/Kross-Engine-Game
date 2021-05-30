/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

/* !----- NOTICE -----! */
/* 
	Make sure all Vertex 
	Types are here and 
	Included as well as 
	functionally added!
*/

#include "Vertex/SpriteVertex.h"
#include "Vertex/TextVertex.h"
#include "Vertex/WaterVertex.h"

/* !------------------! */

#include "GL/glew.h"

namespace Kross
{
	struct KROSS_API VertexAttribute
	{
		VertexAttribute(short pointerID, short count, int type, int normalised, unsigned int stride, unsigned int offset) :
			m_PointerID		(pointerID),
			m_Count			(count),
			m_Type			(type),
			m_Normalised	(normalised),
			m_Stride		(stride),
			m_Offset		(offset)
		{};

		int m_PointerID, m_Count, m_Type, m_Normalised;
		unsigned int m_Stride;
		unsigned int m_Offset;
	};

	class KROSS_API VertexBufferLayout
	{
	private:
		List<VertexAttribute> m_Attributes;

	protected:

	public:
		// Base Template. (DO NOT USE)
		template<typename Type>
		void SetLayoutType()
		{
			static_assert(false, "Vertex Buffer Layout Type Passed Invalid!");
		}

		// Sets the Layout to be of type Sprite Vertex.
		template<>
		void SetLayoutType<SpriteVertex>()
		{
			/* Pre Allocate 6 for adding the Attributes. */
			m_Attributes = List<VertexAttribute>(6);

			/* Position Layout. */
			m_Attributes[0] = VertexAttribute(0, 2, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(SpriteVertex), (unsigned int)offsetof(SpriteVertex, SpriteVertex::m_Position));

			/* Texture UVs Layout. */
			m_Attributes[1] = VertexAttribute(1, 2, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(SpriteVertex), (unsigned int)offsetof(SpriteVertex, SpriteVertex::m_TextureUVs));

			/* Normal UVs Layout. */
			m_Attributes[2] = VertexAttribute(2, 2, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(SpriteVertex), (unsigned int)offsetof(SpriteVertex, SpriteVertex::m_NormalUVs));

			/* Specular UVs Layout. */
			m_Attributes[3] = VertexAttribute(3, 2, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(SpriteVertex), (unsigned int)offsetof(SpriteVertex, SpriteVertex::m_SpecularUVs));

			/* World Normal Layout. */
			m_Attributes[4] = VertexAttribute(4, 3, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(SpriteVertex), (unsigned int)offsetof(SpriteVertex, SpriteVertex::m_WorldNormal));

			/* Colour Layout. */
			m_Attributes[5] = VertexAttribute(5, 4, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(SpriteVertex), (unsigned int)offsetof(SpriteVertex, SpriteVertex::m_Colour));
		}

		// Sets the Layout to be of type Text Vertex.
		template<>
		void SetLayoutType<TextVertex>()
		{
			/* Pre Allocate 3 for adding the Attributes. */
			m_Attributes = List<VertexAttribute>(3);

			/* Position Layout. */
			m_Attributes[0] = VertexAttribute(0, 2, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(TextVertex), (unsigned int)offsetof(TextVertex, TextVertex::m_Position));

			/* UVs Layout. */
			m_Attributes[1] = VertexAttribute(1, 2, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(TextVertex), (unsigned int)offsetof(TextVertex, TextVertex::m_UVs));

			/* Colour Layout. */
			m_Attributes[2] = VertexAttribute(2, 4, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(TextVertex), (unsigned int)offsetof(TextVertex, TextVertex::m_Colour));
		}

		// Sets the Layout to be of type Water Vertex.
		template<>
		void SetLayoutType<WaterVertex>()
		{
			/* Pre Allocate 3 for adding the Attributes. */
			m_Attributes = List<VertexAttribute>(3);

			/* Position Layout. */
			m_Attributes[0] = VertexAttribute(0, 2, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(WaterVertex), (unsigned int)offsetof(WaterVertex, WaterVertex::m_Position));

			/* UVs Layout. */
			m_Attributes[1] = VertexAttribute(1, 2, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(WaterVertex), (unsigned int)offsetof(WaterVertex, WaterVertex::m_Velocity));

			/* Colour Layout. */
			m_Attributes[2] = VertexAttribute(2, 4, GL_FLOAT, GL_FALSE, (unsigned int)sizeof(WaterVertex), (unsigned int)offsetof(WaterVertex, WaterVertex::m_Colour));
		}
	};
}