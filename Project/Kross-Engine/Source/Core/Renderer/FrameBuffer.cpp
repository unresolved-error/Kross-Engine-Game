/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "FrameBuffer.h"

namespace Kross
{
	FrameBuffer::FrameBuffer(int width, int height)
		: m_FrameBufferID(0), m_WindowFrameTexture(nullptr)
	{
		glGenFramebuffers(1, &m_FrameBufferID);

		/* Create a Texture to write to. */
		m_WindowFrameTexture = Texture::OnCreate(width, height, nullptr, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, "FrameBuffer-WindowTexture");

		Attach();

		/* Set the Texture to write to. Write the screen data. */
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_WindowFrameTexture->GetTextureID(), 0);

		/* If the Frame Buffer doesn't complete itself. */
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			/* Get rid of everything. */
			Texture::OnDestroy(m_WindowFrameTexture);
			glDeleteFramebuffers(1, &m_FrameBufferID);
		}

		Detach();
	}

	FrameBuffer::~FrameBuffer()
	{
		if (m_FrameBufferID != NULL)
			glDeleteFramebuffers(1, &m_FrameBufferID);

		/* Delete the Window Frame Texture. */
		if (m_WindowFrameTexture)
			Texture::OnDestroy(m_WindowFrameTexture);
	}

	void FrameBuffer::Attach()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
	}

	void FrameBuffer::Detach()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}