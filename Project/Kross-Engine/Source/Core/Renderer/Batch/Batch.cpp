/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Batch.h"

namespace Kross
{
    Batch::~Batch()
    {
        m_Data.clear();
        m_Indicies.clear();

        p_Atlas = nullptr;

        delete m_IndexBuffer;
        delete m_VertexArray;
        delete m_VertexBuffer;
    }

    void Batch::OnCompile()
    {
        m_VertexArray->Attach();

        /* Set Data.*/
        m_VertexBuffer->AttachVertexData(m_Data.data(), m_Data.size() * sizeof(Vertex));
        m_IndexBuffer->AttachIndexData(m_Indicies.data(), m_Indicies.size());

        /* Link both Index Buffer and Vertex Buffer to the Vertex Array. */
        m_IndexBuffer->Attach();
        m_VertexArray->AttachVertexBufferToLayout(*m_VertexBuffer);
        m_VertexArray->Detach();
    }

    void Batch::OnRender()
    {
        m_VertexArray->Attach();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}