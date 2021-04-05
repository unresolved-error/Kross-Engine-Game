/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "VertexBuffer.h"

namespace Kross
{
	class KROSS_API VertexArray
	{
	private:
		unsigned int m_VertexArrayID;

	protected:
		// Gets the ID of the Vertex Array.
		unsigned int GetVertexArrayID() const { return m_VertexArrayID; };

	public:
		VertexArray();
		~VertexArray();

		// Binds the Vertex Array for using.
		void Attach();

		// Un Binds the current VertexArray. 
		static void Detach();

		// Configures a VertexBuffer to a layout.
		void AttachVertexBufferToLayout(VertexBuffer& vertexBuffer);
	};
}