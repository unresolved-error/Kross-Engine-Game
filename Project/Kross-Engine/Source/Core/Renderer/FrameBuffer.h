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
		Texture* m_WindowFrameTexture;

	protected:

	public:
		FrameBuffer() : 
			m_FrameBufferID			(0),
			m_WindowFrameTexture	(nullptr)
		{};
		FrameBuffer(int width, int height);
		~FrameBuffer();

		// Binds the Frame Buffer.
		void Attach();

		// Un Binds all Frame Buffers.
		static void Detach();

		// Gets the Frame Buffer generated Texture.
		Texture* GetFrameTexture() const { return m_WindowFrameTexture; };
	};
}