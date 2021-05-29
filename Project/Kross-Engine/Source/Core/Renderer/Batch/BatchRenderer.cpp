/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "BatchRenderer.h"
#include "../../Application.h"

namespace Kross
{
    BatchRenderer::~BatchRenderer()
    {
        delete p_Batch;
        delete p_WaterBuffer;
    }

    BatchRenderer* BatchRenderer::OnCreate(Layer layer)
    {
        Atlas* atlas = ResourceManager::GetAtlas();
        BatchRenderer* renderer = KROSS_NEW BatchRenderer(atlas, layer);

        return renderer;
    }

    void BatchRenderer::OnDestroy(BatchRenderer* renderer)
    {
        if (renderer)
            delete renderer;
    }

    void BatchRenderer::AttachRenderer(Renderer* renderer)
    {
        if (typeid(*renderer) == typeid(SpriteRenderer))
        {
            if (p_Batch->IsFull())
                OnRender();

            p_Batch->Attach<SpriteRenderer>((SpriteRenderer*)renderer);
        }

        else if (typeid(*renderer) == typeid(TextRenderer))
        {
            if (p_Batch->IsFull())
                OnRender();
                
            p_Batch->Attach<TextRenderer>((TextRenderer*)renderer);
        }

        else if (typeid(*renderer) == typeid(ParticleEmitter))
        {
            if (p_Batch->IsFull())
                OnRender();

            p_Batch->Attach<ParticleEmitter>((ParticleEmitter*)renderer);
        }

        return;
    }

    void BatchRenderer::OnRender()
    {
        if (p_Batch->IsEmpty())
            return;

        if (m_Layer != Layer::Fluids)
        {
            p_Atlas->GetTexture()->Attach();
            p_BatchShader->SetUniform("u_Atlas", p_Atlas->GetTexture());
            p_BatchShader->Attach();
            p_Batch->OnCompile();
            p_Batch->m_VertexArray->AttachVertexBufferToLayout(*p_Batch->m_VertexBuffer);

            p_Batch->OnRender();
        }
        else
        {
           // p_WaterBuffer->Attach();
            p_BatchShader->SetUniform("u_HalfSize", 0.03f);
            p_BatchShader->SetUniform("u_InverseAspect", 1.0f / Application::GetWindow()->GetApsectRatio());
            p_BatchShader->SetUniform("u_Colour", Colour(0.28f, 0.71f, 0.91f, 1.0f));
            p_BatchShader->Attach();
            p_Batch->OnCompile();

            p_Batch->m_VertexArray->AttachVertexBufferToLayout(*p_Batch->m_VertexBuffer);

            p_Batch->m_VertexArray->Attach();
            glDrawElements(GL_POINTS, p_Batch->m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr); // not to screen.

            //p_WaterBuffer->Detach();

            //p_metaballShader->SetUniform("u_Texture", p_WaterBuffer->GetFrameTexture());




            //further junk here to metaball;

//            take further junk to future metaball:


        }

        Texture::Detach();

        OnClean();
    }

    void BatchRenderer::OnFinish()
    {
        OnRender();
    }

    void BatchRenderer::OnClean()
    {
        delete p_Batch;

        p_Batch = KROSS_NEW Batch(p_Atlas);
    }
}