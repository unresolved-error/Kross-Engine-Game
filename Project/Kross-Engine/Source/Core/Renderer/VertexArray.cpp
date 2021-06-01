/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "VertexArray.h"

#include "Geometry.h"

#include "GL/glew.h"

namespace Kross
{
	VertexArray::VertexArray() :
		m_VertexArrayID(0)
	{
		glGenVertexArrays(1, &m_VertexArrayID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void VertexArray::Attach()
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void VertexArray::Detach()
	{
		glBindVertexArray(0);
	}

	void VertexArray::AttachVertexBufferToLayout(VertexBuffer& vertexBuffer, VertexBufferLayout* layout)
	{
		Attach();
		vertexBuffer.Attach();

		/* ---- Configure Layout. ---- */

		/* Go through all Attributes. */
		for (int i = 0; i < layout->GetAttributeCount(); i++)
		{
			/* Quick Variable. */
			VertexAttribute attribute = layout->GetAttribute(i);

			/* Set Attribute Parameters. */
			glEnableVertexAttribArray(attribute.m_PointerID);
			glVertexAttribPointer(attribute.m_PointerID, attribute.m_Count, attribute.m_Type, attribute.m_Normalised, attribute.m_Stride, (const void*)attribute.m_Offset);
		}

		/* --------------------------- */

		///* Position Layout. */
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::m_Position));
		//
		///* Texture UVs Layout. */
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::m_TextureUVs));
		//
		///* Normal UVs Layout. */
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::m_NormalUVs));
		//
		///* Specular UVs Layout. */
		//glEnableVertexAttribArray(3);
		//glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::m_SpecularUVs));
		//
		///* World Normal Layout. */
		//glEnableVertexAttribArray(4);
		//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::m_WorldNormal));
		//
		///* Colour Layout. */
		//glEnableVertexAttribArray(5);
		//glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::m_Colour));

		
	}
}