/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Image/Texture.h"

namespace Kross
{
	class KROSS_API FrameBuffer
	{
	private:
		unsigned int m_FrameBufferID;
		unsigned int m_AttachmentID;
		Texture* m_WindowFrameTexture;

	protected:

	public:
		FrameBuffer() : 
			m_FrameBufferID			(0),
			m_AttachmentID			(0),
			m_WindowFrameTexture	(nullptr)
		{};
		FrameBuffer(int width, int height, unsigned int attachmentID = 0);
		~FrameBuffer();

		// Binds the Frame Buffer.
		void Attach();

		// Un Binds all Frame Buffers.
		static void Detach();

		// Gets the Frame Buffer generated Texture.
		Texture* GetFrameTexture() const { return m_WindowFrameTexture; };
	};
}