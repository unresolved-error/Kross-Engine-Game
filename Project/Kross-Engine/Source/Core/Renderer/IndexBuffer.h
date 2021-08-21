/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

namespace Kross
{
	class KROSS_API IndexBuffer
	{
	private:
		unsigned int m_IndexBufferID;
		unsigned int m_Count;

	protected:
		// Gets the ID of the Index Buffer.
		unsigned int GetIndexBufferID() const { return m_IndexBufferID; };

	public:
		IndexBuffer();
		~IndexBuffer();

		// Binds the Index Buffer.
		void Bind();

		// Un Binds the Index Buffer.
		static void UnBind();

		// Gets the number of Indexes inside of the index data.
		unsigned int GetCount() const { return m_Count; };

		// Adds data to the Index Buffer.
		void SetIndexData(const void* data, unsigned int count);
	};
}