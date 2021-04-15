/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Geometry.h"

#include "GL/glew.h"

namespace Kross
{
	Geometry::~Geometry()
	{
		/* Clean up external data. */
		delete m_IndexBuffer;
		delete m_VertexArray;
		delete m_VertexBuffer;
	}

	void Geometry::OnRenderGeometry()
	{
		/* Early out if no RenderMode has been given. */
		if (m_RenderMode == RenderMode::None)
			return;

		m_VertexArray->Attach();

		/* Render the Geometry based on the Render Mode. */
		if (m_RenderMode == RenderMode::Solid)
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

		else if (m_RenderMode == RenderMode::Wireframe)
			glDrawElements(GL_LINES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

		else if (m_RenderMode == RenderMode::Line)
			glDrawElements(GL_LINE_STRIP, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Geometry::AttachVertex(Vertex vertex)
	{
		/* Size Variable. */
		int indiciesSize = m_Indicies.size();

		/* First Element. */
		if (indiciesSize == 0)
			m_Indicies.push_back(indiciesSize);

		/* First Six Elements. */
		else if (indiciesSize <= 3)
		{
			/* Next Two Elements. */
			if (indiciesSize % 3 != 0)
				m_Indicies.push_back(indiciesSize);

			/* The the wrapper to make them loop and connect. */
			else
			{
				m_Indicies.push_back(indiciesSize - 1);
				m_Indicies.push_back(indiciesSize);
				m_Indicies.push_back(indiciesSize - 3);
			}
		}

		/* Add the Vertex. */
		m_Geometry.push_back(vertex);

		/* Update the Index Buffer, Vertex Buffer and Vertex Array. */
		m_VertexArray->Attach();

		/* Set Data.*/
		m_VertexBuffer->AttachVertexData(m_Geometry.data(), m_Geometry.size() * sizeof(Vertex));
		m_IndexBuffer->AttachIndexData(m_Indicies.data(), m_Indicies.size());

		/* Link both Index Buffer and Vertex Buffer to the Vertex Array. */
		m_IndexBuffer->Attach();
		m_VertexArray->AttachVertexBufferToLayout(*m_VertexBuffer);

		m_VertexArray->Detach();
	}
}