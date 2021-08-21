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

	void VertexArray::Bind()
	{
		OPENGL_CHECK(glBindVertexArray(m_VertexArrayID));
	}

	void VertexArray::UnBind()
	{
		OPENGL_CHECK(glBindVertexArray(0));
	}

	void VertexArray::AttachVertexBufferToLayout(VertexBuffer& vertexBuffer, VertexBufferLayout* layout)
	{
		Bind();
		vertexBuffer.Bind();

		/* ---- Configure Layout. ---- */

		/* Go through all Attributes. */
		for (int i = 0; i < layout->GetAttributeCount(); i++)
		{
			/* Quick Variable. */
			VertexAttribute attribute = layout->GetAttribute(i);

			/* Set Attribute Parameters. */
			OPENGL_CHECK(glEnableVertexAttribArray(attribute.m_PointerID));
			OPENGL_CHECK(glVertexAttribPointer(attribute.m_PointerID, attribute.m_Count, attribute.m_Type, attribute.m_Normalised, attribute.m_Stride, (const void*)attribute.m_Offset));
		}

		/* --------------------------- */
	}
}