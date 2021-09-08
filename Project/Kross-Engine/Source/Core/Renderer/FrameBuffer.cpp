/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "FrameBuffer.h"

namespace Kross
{
	FrameBuffer::FrameBuffer() :
		m_FrameBufferID			(0),
		m_AttachmentID			(0),
		m_FrameBufferTexture	(nullptr)
	{}

	FrameBuffer::FrameBuffer(int width, int height, unsigned int attachmentID)	:
		m_FrameBufferID			(0),
		m_AttachmentID			(attachmentID),
		m_FrameBufferTexture	(nullptr)
	{
		glGenFramebuffers(1, &m_FrameBufferID);

		/* Create a Texture to write to. */
		m_FrameBufferTexture = Texture::OnCreate(width, height, nullptr, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, "FrameBuffer-WindowTexture");

		Bind();

		/* Set the Texture to write to. Write the screen data. */
		OPENGL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachmentID, m_FrameBufferTexture->GetTextureID(), 0));

		/* If the Frame Buffer doesn't complete itself. */
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			/* Get rid of everything. */
			Texture::OnDestroy(m_FrameBufferTexture);
			glDeleteFramebuffers(1, &m_FrameBufferID);
		}

		UnBind();
	}

	FrameBuffer::~FrameBuffer()
	{
		if (m_FrameBufferID != NULL)
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
		}

		/* Delete the Window Frame Texture. */
		if (m_FrameBufferTexture)
		{
			Texture::OnDestroy(m_FrameBufferTexture);
		}
	}

	void FrameBuffer::Bind()
	{
		OPENGL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID));
	}

	void FrameBuffer::UnBind()
	{
		OPENGL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void FrameBuffer::ClearBuffer()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}