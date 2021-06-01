/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "BatchRenderer.h"
#include "../../Application.h"

#include "Batch.h"

namespace Kross
{
    BatchRenderer::~BatchRenderer()
    {
        delete p_Batch;

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
                renderer->p_Batch = KROSS_NEW Batch<WaterVertex>(atlas);
                renderer->p_VertexBufferLayout->SetLayoutType<WaterVertex>();
                break;
            }

            case Layer::UI:
            {
                renderer->p_Batch = KROSS_NEW Batch<TextVertex>(atlas);
                renderer->p_VertexBufferLayout->SetLayoutType<TextVertex>();
                break;
            }

            default:
            {
                renderer->p_Batch = KROSS_NEW Batch<SpriteVertex>(atlas);
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

    void BatchRenderer::AttachRenderer(Renderer* renderer)
    {
        /* The Renderer Type is Sprite Renderer. */
        if (typeid(*renderer) == typeid(SpriteRenderer))
        {
            /* Pull the Batch Instance from the Void. */
            Batch<SpriteVertex>* batch = (Batch<SpriteVertex>*)p_Batch;

            /* Check if the Batch Packet is Full. */
            if (batch->GetFullStatus() == true)
                OnRender();

            /* Attach the Data. */
            batch->Attach((SpriteRenderer*)renderer);
        }

        /* The Renderer Type is Text Renderer. */
        else if (typeid(*renderer) == typeid(TextRenderer))
        {
            /* Pull the Batch Instance from the Void. */
            Batch<TextVertex>* batch = (Batch<TextVertex>*)p_Batch;

            /* Check if the Batch Packet is Full. */
            if (batch->GetFullStatus() == true)
                OnRender();
                
            /* Attach the Data. */
            batch->Attach((TextRenderer*)renderer);
        }

        /* The Renderer is a Particle Emitter. */
        else if (typeid(*renderer) == typeid(ParticleEmitter))
        {
            /* Pull the Batch Instance from the Void. */
            Batch<WaterVertex>* batch = (Batch<WaterVertex>*)p_Batch;

            /* Check if the Batch Packet is Full. */
            if (batch->GetFullStatus() == true)
                OnRender();

            /* Attach the Data. */
            batch->Attach((ParticleEmitter*)renderer);
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
                Batch<WaterVertex>* batch = (Batch<WaterVertex>*)p_Batch; 
                batch->p_Atlas = p_Atlas;

                break;
            }

            case Layer::UI:
            {
                p_Shader = ResourceManager::GetResource<Shader>("TextShader");

                /* Grabs the Default Font First. */
                p_Texture = ResourceManager::GetResource<Font>(0)->GetTexture();

                /* Make sure the Batch Packet Updates its Atlas Pointer. */
                Batch<TextVertex>* batch = (Batch<TextVertex>*)p_Batch;
                batch->p_Atlas = p_Atlas;

                break;
            }

            default:
            {
                p_Shader = ResourceManager::GetResource<Shader>("BatchShader");

                /* Make sure the Batch Packet Updates its Atlas Pointer. */
                Batch<SpriteVertex>* batch = (Batch<SpriteVertex>*)p_Batch;
                batch->p_Atlas = p_Atlas;

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
                /* Grab the Batch Packet from the Void. */
                Batch<WaterVertex>* batch = (Batch<WaterVertex>*)p_Batch;

                /* Check if it is Empty. */
                shouldAbandon = batch->GetEmptyStatus();
                break;
            }

            case Layer::UI:
            {
                /* Grab the Batch Packet from the Void. */
                Batch<TextVertex>* batch = (Batch<TextVertex>*)p_Batch;

                /* Check if it is Empty. */
                shouldAbandon = batch->GetEmptyStatus();
                break;
            }

            default:
            {
                /* Grab the Batch Packet from the Void. */
                Batch<SpriteVertex>* batch = (Batch<SpriteVertex>*)p_Batch;

                /* Check if it is Empty. */
                shouldAbandon = batch->GetEmptyStatus();
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
                /* Grab the Batch Packet from the Void. */
                Batch<WaterVertex>* batch = (Batch<WaterVertex>*)p_Batch;

                p_Shader->SetUniform("u_HalfSize", 0.03f);
                p_Shader->SetUniform("u_InverseAspect", 1.0f / Application::GetWindow()->GetApsectRatio());
                p_Shader->SetUniform("u_Colour", Colour(0.28f, 0.71f, 0.91f, 1.0f));

                /* Start the Data Transfer. */
                p_VertexArray->Attach();

                /* Set Data.*/
                p_VertexBuffer->AttachVertexData(batch->m_Data.data(), batch->m_Data.size() * sizeof(WaterVertex));
                p_IndexBuffer->AttachIndexData(batch->m_Indicies.data(), batch->m_Indicies.size());

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
                /* Grab the Batch Packet from the Void. */
                Batch<TextVertex>* batch = (Batch<TextVertex>*)p_Batch;

                /* Attach the Font Texture. */
                p_Texture->Attach();
                p_Shader->SetUniform("u_Texture", p_Texture);

                /* Start the Data Transfer. */
                p_VertexArray->Attach();

                /* Set Data.*/
                p_VertexBuffer->AttachVertexData(batch->m_Data.data(), batch->m_Data.size() * sizeof(TextVertex));
                p_IndexBuffer->AttachIndexData(batch->m_Indicies.data(), batch->m_Indicies.size());

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
                /* Grab the Batch Packet from the Void. */
                Batch<SpriteVertex>* batch = (Batch<SpriteVertex>*)p_Batch;

                /* Attach the Texture. */
                p_Atlas->GetTexture()->Attach();
                p_Shader->SetUniform("u_Atlas", p_Atlas->GetTexture());

                /* Start the Data Transfer. */
                p_VertexArray->Attach();
                  
                /* Set Data.*/
                p_VertexBuffer->AttachVertexData(batch->m_Data.data(), batch->m_Data.size() * sizeof(SpriteVertex));
                p_IndexBuffer->AttachIndexData(batch->m_Indicies.data(), batch->m_Indicies.size());
                
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
        if (m_Layer != Layer::Fluids)
        {
            //p_Atlas->GetTexture()->Attach();
            //p_BatchShader->SetUniform("u_Atlas", p_Atlas->GetTexture());
            //p_BatchShader->Attach();
            //p_Batch->OnCompile();
            //p_Batch->m_VertexArray->AttachVertexBufferToLayout(*p_Batch->m_VertexBuffer);
            //
            //p_Batch->OnRender();
        }
        else
        {
            // p_WaterBuffer->Attach();
            //p_BatchShader->SetUniform("u_HalfSize", 0.03f);
            //p_BatchShader->SetUniform("u_InverseAspect", 1.0f / Application::GetWindow()->GetApsectRatio());
            //p_BatchShader->SetUniform("u_Colour", Colour(0.28f, 0.71f, 0.91f, 1.0f));
            //p_BatchShader->Attach();
            //p_Batch->OnCompile();
            //
            //p_Batch->m_VertexArray->AttachVertexBufferToLayout(*p_Batch->m_VertexBuffer);
            //
            //p_Batch->m_VertexArray->Attach();
            //glDrawElements(GL_POINTS, p_Batch->m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr); // not to screen.

            //p_WaterBuffer->Detach();

            //p_metaballShader->SetUniform("u_Texture", p_WaterBuffer->GetFrameTexture());
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
        if (p_Batch)
        {
            switch (m_Layer)
            {
                case Layer::Fluids:
                {
                    /* Grab the Batch Packet from the Void. */
                    Batch<WaterVertex>* batch = (Batch<WaterVertex>*)p_Batch;

                    /* Delete it. */
                    delete batch;
                    break;
                }

                case Layer::UI:
                {
                    /* Grab the Batch Packet from the Void. */
                    Batch<TextVertex>* batch = (Batch<TextVertex>*)p_Batch;

                    /* Delete it. */
                    delete batch;
                    break;
                }

                default:
                {
                    /* Grab the Batch Packet from the Void. */
                    Batch<SpriteVertex>* batch = (Batch<SpriteVertex>*)p_Batch;

                    /* Delete it. */
                    delete batch;
                    break;
                }
            }

            /* Null out Batch. */
            p_Batch = nullptr;
        }

        switch (m_Layer)
        {
        case Layer::Fluids:
        {
            p_Batch = KROSS_NEW Batch<WaterVertex>(p_Atlas);
            break;
        }

        case Layer::UI:
        {
            p_Batch = KROSS_NEW Batch<TextVertex>(p_Atlas);
            break;
        }

        default:
        {
            p_Batch = KROSS_NEW Batch<SpriteVertex>(p_Atlas);
            break;
        }
        }
    }
}