/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "IndexBuffer.h"

#include "GL/glew.h"

namespace Kross
{
	IndexBuffer::IndexBuffer() :
		m_IndexBufferID	(0),
		m_Count			(0)
	{
		glGenBuffers(1, &m_IndexBufferID);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_IndexBufferID);
	}

	void IndexBuffer::Attach()
	{
		OPENGL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID));
	}

	void IndexBuffer::Detach()
	{
		OPENGL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void IndexBuffer::AttachIndexData(const void* data, unsigned int count)
	{
		m_Count = count;

		Attach();
		OPENGL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}
}