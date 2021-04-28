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

namespace Kross
{
	struct KROSS_API Vertex
	{
	private:
		
	protected:

	public:
		Vertex()
			: m_Position(Vector2(0.0f)), m_UVs(Vector2(0.0f)), m_Colour(Colour(1.0f))
		{};
		Vertex(Vector2 position, Vector2 uvs, Colour colour)
			: m_Position(position), m_UVs(uvs), m_Colour(colour)
		{};

		Vector2 m_Position, m_UVs;
		Colour m_Colour;
	};

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

		int m_MemorySize;
		RenderMode m_RenderMode;

	protected:
		friend class Sprite;

		// Sets the Geometry Name.
		void SetName(const std::string& name) { m_Name = name; };

		// Draws the Geometry.
		void OnRenderGeometry();

	public:
		Geometry()
			: m_Geometry(List<Vertex>()), m_Indicies(List<unsigned int>()), m_Name(""), m_IndexBuffer(new IndexBuffer()), m_VertexArray(new VertexArray()), m_VertexBuffer(new VertexBuffer()), m_MemorySize(0), m_RenderMode(RenderMode::None)
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