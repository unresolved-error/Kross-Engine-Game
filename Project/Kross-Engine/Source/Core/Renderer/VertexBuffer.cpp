/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "VertexBuffer.h"

#include "GL/glew.h"

namespace Kross
{
	VertexBuffer::VertexBuffer() : 
		m_VertexBufferID(0)
	{
		glGenBuffers(1, &m_VertexBufferID);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_VertexBufferID);
	}

	void VertexBuffer::Bind()
	{
		OPENGL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
	}

	void VertexBuffer::UnBind()
	{
		OPENGL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::SetVertexData(const void* data, unsigned int size)
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
}