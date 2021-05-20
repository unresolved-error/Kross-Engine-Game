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

	void VertexArray::AttachVertexBufferToLayout(VertexBuffer& vertexBuffer)
	{
		Attach();
		vertexBuffer.Attach();

		/* ---- Configure Layout. ---- */

		/* Position Layout. */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::m_Position));

		/* UVs Layout. */
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::m_UVs));

		/* Colour Layout. */
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::m_Colour));

		/* --------------------------- */
	}
}