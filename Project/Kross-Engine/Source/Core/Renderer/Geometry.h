/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Math/Math.h"

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Vertex/Vertex.h"

namespace Kross
{
	// This is used inside of Geomtry, to determain the way it is drawn.
	enum class KROSS_API RenderMode
	{
		None,
		Solid,
		Wireframe,
		Line,
	};

	class KROSS_API Geometry
	{
	private:
		List<Vertex> m_Geometry;
		List<unsigned int> m_Indicies;

		std::string m_Name;

		IndexBuffer* m_IndexBuffer;
		VertexArray* m_VertexArray;
		VertexBuffer* m_VertexBuffer;

		RenderMode m_RenderMode;
		int m_MemorySize;

	protected:
		friend class Sprite;
		friend class Batch;

		// Sets the Geometry Name.
		void SetName(const std::string& name) { m_Name = name; };

		// Draws the Geometry.
		void OnRenderGeometry();

	public:
		Geometry() :
			m_IndexBuffer	(KROSS_NEW IndexBuffer()), 
			m_VertexArray	(KROSS_NEW VertexArray()), 
			m_VertexBuffer	(KROSS_NEW VertexBuffer()), 
			m_RenderMode	(RenderMode::None),
			m_Indicies		(List<unsigned int>()), 
			m_Geometry		(List<Vertex>()), 
			m_Name			(""), 
			m_MemorySize	(0)
		{};
		~Geometry();

		// Adds a Vertex to the Geometry Data.
		void AttachVertex(Vertex vertex);

		// Sets the Geometry Render Mode.
		void SetRenderMode(RenderMode mode) { m_RenderMode = mode; };

		// Gets the Geometry Name.
		const std::string GetName() const { return m_Name; };
	};
}