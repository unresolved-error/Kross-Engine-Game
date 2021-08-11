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
        delete p_WaterBatch;
        delete p_TextBatch;
        delete p_SpriteBatch;

        delete p_VertexArray;
        delete p_VertexBuffer;
        delete p_IndexBuffer;

        delete p_VertexBufferLayout;
    }

    BatchRenderer* BatchRenderer::OnCreate(Layer layer)
    {
        /* Quick Variables. */
        Atlas* atlas = ResourceManager::GetAtlas();
        BatchRenderer* renderer = KROSS_NEW BatchRenderer(atlas, layer);

        /* Set what Vertex the Batch will be using. */
        switch (layer)
        {
            case Layer::Fluids:
            {
                renderer->p_VertexBufferLayout->SetLayoutType<WaterVertex>();
                break;
            }

            case Layer::UI:
            {
                renderer->p_VertexBufferLayout->SetLayoutType<TextVertex>();
                break;
            }

            default:
            {
                renderer->p_VertexBufferLayout->SetLayoutType<SpriteVertex>();
                break;
            }
        }

        /* Return the Renderer. */
        return renderer;
    }

    void BatchRenderer::OnDestroy(BatchRenderer* renderer)
    {
        if (renderer)
            delete renderer;
    }

    void BatchRenderer::AttachRenderer(Camera* camera, Renderer* renderer)
    {
        /* The Renderer Type is Sprite Renderer. */
        if (typeid(*renderer) == typeid(SpriteRenderer))
        {
            /* Check if the Batch Packet is Full. */
            if (p_SpriteBatch->Full() == true)
                OnRender();

            /* Attach the Data. */
            p_SpriteBatch->Attach(camera, (SpriteRenderer*)renderer);
        }

        /* The Renderer Type is Text Renderer. */
        else if (typeid(*renderer) == typeid(TextRenderer))
        {
            /* Check if the Batch Packet is Full. */
            if (p_TextBatch->Full() == true)
                OnRender();
                
            /* Attach the Data. */
            p_TextBatch->Attach(camera, (TextRenderer*)renderer);
        }

        /* The Renderer is a Particle Emitter. */
        else if (typeid(*renderer) == typeid(ParticleEmitter))
        {
            /* Check if the Batch Packet is Full. */
            if (p_WaterBatch->Full() == true)
                OnRender();

            /* Attach the Data. */
            p_WaterBatch->Attach(camera, (ParticleEmitter*)renderer);
        }

        /* The Renderer is a Particle Emitter. */
        else if (typeid(*renderer) == typeid(TileMapRenderer))
        {
            /* Check if the Batch Packet is Full. */
            if (p_SpriteBatch->Full() == true)
                OnRender();

            /* Attach the Data. */
            p_SpriteBatch->Attach(camera, (TileMapRenderer*)renderer);
        }

        return;
    }

    void BatchRenderer::OnStart()
    {
        /* Set the Atlas. */
        p_Atlas = ResourceManager::GetAtlas();

        /* Find out What Layer the Renderer is on. Apply the Correct Shader. */
        switch (m_Layer)
        {
            case Layer::Fluids:
            {
                p_Shader = ResourceManager::GetResource<Shader>("WaterShader");

                /* Make sure the Batch Packet Updates its Atlas Pointer. */
                p_WaterBatch->p_Atlas = p_Atlas;

                break;
            }

            case Layer::UI:
            {
                p_Shader = ResourceManager::GetResource<Shader>("TextShader");

                /* Grabs the Default Font First. */
                p_Texture = ResourceManager::GetResource<Font>(0)->GetTexture();

                /* Make sure the Batch Packet Updates its Atlas Pointer. */
                p_TextBatch->p_Atlas = p_Atlas;

                break;
            }

            default:
            {
                p_Shader = ResourceManager::GetResource<Shader>("BatchShader");

                /* Make sure the Batch Packet Updates its Atlas Pointer. */
                p_SpriteBatch->p_Atlas = p_Atlas;

                break;
            }
        }
    }

    void BatchRenderer::OnRender()
    {
        /* Quick Variable. */
        bool shouldAbandon = false;

        /* See if the Batch is Empty. */
        switch (m_Layer)
        {
            case Layer::Fluids:
            {
                /* Check if it is Empty. */
                shouldAbandon = p_WaterBatch->Empty();
                break;
            }

            case Layer::UI:
            {
                /* Check if it is Empty. */
                shouldAbandon = p_TextBatch->Empty();
                break;
            }

            default:
            {
                /* Check if it is Empty. */
                shouldAbandon = p_SpriteBatch->Empty();
                break;
            }
        }

        /* If we need to abandon, do it. */
        if (shouldAbandon)
            return;

        switch (m_Layer)
        {
            case Layer::Fluids:
            {
                /* Set Shader Values. */
                p_Shader->SetUniform("u_HalfSize", 0.03f);
                p_Shader->SetUniform("u_InverseAspect", 1.0f / Application::GetWindow()->GetApsectRatio());
                p_Shader->SetUniform("u_Colour", Colour(0.28f, 0.71f, 0.91f, 1.0f));

                /* Start the Data Transfer. */
                p_VertexArray->Attach();

                /* Set Data.*/
                p_VertexBuffer->AttachVertexData(p_WaterBatch->m_Data.data(), p_WaterBatch->m_Data.size() * sizeof(WaterVertex));
                p_IndexBuffer->AttachIndexData(p_WaterBatch->m_Indicies.data(), p_WaterBatch->m_Indicies.size());

                /* Link both Index Buffer and Vertex Buffer to the Vertex Array. */
                p_IndexBuffer->Attach();
                p_VertexArray->AttachVertexBufferToLayout(*p_VertexBuffer, p_VertexBufferLayout);
                p_VertexArray->Detach();

                /* Render the Batch. */
                p_Shader->Attach();
                p_VertexArray->Attach();
                glDrawElements(GL_POINTS, p_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

                break;
            }

            case Layer::UI:
            {
                /* Attach the Font Texture. */
                p_Texture->Attach();
                p_Shader->SetUniform("u_Texture", p_Texture);

                /* Start the Data Transfer. */
                p_VertexArray->Attach();

                /* Set Data.*/
                p_VertexBuffer->AttachVertexData(p_TextBatch->m_Data.data(), p_TextBatch->m_Data.size() * sizeof(TextVertex));
                p_IndexBuffer->AttachIndexData(p_TextBatch->m_Indicies.data(),p_TextBatch->m_Indicies.size());

                /* Link both Index Buffer and Vertex Buffer to the Vertex Array. */
                p_IndexBuffer->Attach();
                p_VertexArray->AttachVertexBufferToLayout(*p_VertexBuffer, p_VertexBufferLayout);
                p_VertexArray->Detach();

                /* Render the Batch. */
                p_Shader->Attach();
                p_VertexArray->Attach();
                glDrawElements(GL_TRIANGLES, p_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

                break;
            }

            default:
            {
                /* Attach the Texture. */
                p_Atlas->GetTexture()->Attach();
                p_Shader->SetUniform("u_Atlas", p_Atlas->GetTexture());

                /* Start the Data Transfer. */
                p_VertexArray->Attach();
                  
                /* Set Data.*/
                p_VertexBuffer->AttachVertexData(p_SpriteBatch->m_Data.data(), p_SpriteBatch->m_Data.size() * sizeof(SpriteVertex));
                p_IndexBuffer->AttachIndexData(p_SpriteBatch->m_Indicies.data(), p_SpriteBatch->m_Indicies.size());
                
                /* Link both Index Buffer and Vertex Buffer to the Vertex Array. */
                p_IndexBuffer->Attach();
                p_VertexArray->AttachVertexBufferToLayout(*p_VertexBuffer, p_VertexBufferLayout);
                p_VertexArray->Detach();

                /* Render the Batch. */
                p_Shader->Attach();
                p_VertexArray->Attach();
                glDrawElements(GL_TRIANGLES, p_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

                break;
            }
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
        /* Clearing the Batch. */
        switch (m_Layer)
        {
            case Layer::Fluids:
            {
                p_WaterBatch->Clear();
                break;
            }

            case Layer::UI:
            {
                p_TextBatch->Clear();
                break;
            }

            default:
            {
                p_SpriteBatch->Clear();
                break;
            }
        }
    }
}