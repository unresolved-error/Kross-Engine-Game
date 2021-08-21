/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Image/Texture.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

namespace Kross
{
	class KROSS_API FrameBuffer
	{
	private:
		unsigned int m_FrameBufferID;
		unsigned int m_AttachmentID;

		Texture* m_FrameBufferTexture;

	protected:

	public:
		FrameBuffer();
		FrameBuffer(int width, int height, unsigned int attachmentID = 0);
		~FrameBuffer();

		// Binds the Frame Buffer.
		void Bind();

		// Un Binds all Frame Buffers.
		static void UnBind();

		// Gets the Frame Buffer generated Texture.
		Texture* GetTexture() const { return m_FrameBufferTexture; };
	};
}