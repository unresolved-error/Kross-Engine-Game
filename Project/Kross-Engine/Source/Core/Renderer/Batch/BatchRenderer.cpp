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
        delete m_WaterBatch;
        delete m_TextBatch;
        delete m_SpriteBatch;

        delete m_VertexArray;
        delete m_VertexBuffer;
        delete m_IndexBuffer;

        delete m_VertexBufferLayout;

        delete m_PostProcessVertexArray;
        delete m_PostProcessVertexBuffer;
        delete m_PostProcessIndexBuffer;

        delete m_PostProcessVertexBufferLayout;

        if (m_FrameBuffer)
            delete m_FrameBuffer;
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
                Window* window = Application::GetWindow();

                renderer->m_VertexBufferLayout->SetLayoutType<WaterVertex>();
                renderer->m_FrameBuffer = KROSS_NEW FrameBuffer(window->GetWidth(), window->GetHeight());
                break;
            }
            case Layer::UI:
            {
                renderer->m_VertexBufferLayout->SetLayoutType<TextVertex>();
                break;
            }
            default:
            {
                renderer->m_VertexBufferLayout->SetLayoutType<SpriteVertex>();
                break;
            }
        }

        /* Return the Renderer. */
        return renderer;
    }

    void BatchRenderer::OnDestroy(BatchRenderer* renderer)
    {
        if (renderer)
        {
            delete renderer;
        }
    }

    void BatchRenderer::AttachRenderer(Camera* camera, Renderer* renderer)
    {
        /* The Renderer Type is Sprite Renderer. */
        if (typeid(*renderer) == typeid(SpriteRenderer))
        {
            /* Check if the Batch Packet is Full. */
            if (m_SpriteBatch->Full() == true)
            {
                OnRender();
            }

            /* Attach the Data. */
            m_SpriteBatch->Attach(camera, (SpriteRenderer*)renderer);
        }
        /* The Renderer Type is Text Renderer. */
        else if (typeid(*renderer) == typeid(TextRenderer))
        {
            /* Check if the Batch Packet is Full. */
            if (m_TextBatch->Full() == true)
            {
                OnRender();
            }

            /* Attach the Data. */
            m_TextBatch->Attach(camera, (TextRenderer*)renderer);
        }
        /* The Renderer is a Particle Emitter. */
        else if (typeid(*renderer) == typeid(ParticleEmitter))
        {
            /* Check if the Batch Packet is Full. */
            if (m_WaterBatch->Full() == true)
            {
                OnRender();
            }

            /* Attach the Data. */
            m_WaterBatch->Attach(camera, (ParticleEmitter*)renderer);
        }
        /* The Renderer is a Particle Emitter. */
        else if (typeid(*renderer) == typeid(TileMapRenderer))
        {
            /* Check if the Batch Packet is Full. */
            if (m_SpriteBatch->Full() == true)
            {
                OnRender();
            }

            /* Attach the Data. */
            m_SpriteBatch->Attach(camera, (TileMapRenderer*)renderer);
        }

        return;
    }

    void BatchRenderer::OnStart()
    {
        /* Set the Atlas. */
        m_Atlas = ResourceManager::GetAtlas();

        /* Find out What Layer the Renderer is on. Apply the Correct Shader. */
        switch (m_Layer)
        {
            case Layer::Fluids:
            {
                m_Shader = ResourceManager::GetResource<Shader>("WaterShader");
                m_PostProcessShader = ResourceManager::GetResource<Shader>("WaterPostProcess");

                /* Make sure the Batch Packet Updates its Atlas Pointer. */
                m_WaterBatch->m_Atlas = m_Atlas;

                break;
            }
            case Layer::UI:
            {
                m_Shader = ResourceManager::GetResource<Shader>("TextShader");

                /* Grabs the Default Font First. */
                m_Texture = ResourceManager::GetResource<Font>(0)->GetTexture();

                /* Make sure the Batch Packet Updates its Atlas Pointer. */
                m_TextBatch->m_Atlas = m_Atlas;

                break;
            }
            default:
            {
                m_Shader = ResourceManager::GetResource<Shader>("BatchShader");

                /* Make sure the Batch Packet Updates its Atlas Pointer. */
                m_SpriteBatch->m_Atlas = m_Atlas;

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
                shouldAbandon = m_WaterBatch->Empty();
                break;
            }
            case Layer::UI:
            {
                /* Check if it is Empty. */
                shouldAbandon = m_TextBatch->Empty();
                break;
            }
            default:
            {
                /* Check if it is Empty. */
                shouldAbandon = m_SpriteBatch->Empty();
                break;
            }
        }

        /* If we need to abandon, do it. */
        if (shouldAbandon)
        {
            return;
        }

        switch (m_Layer)
        {
            case Layer::Fluids:
            {
                Window* window = Application::GetWindow();

               

                if (!window->Minimised())
                {
                    if (window->GetWidth() == NULL || window->GetHeight() == NULL)
                    {
                        return;
                    }

                    Texture* frameBufferTexture = m_FrameBuffer->GetTexture();

                    if (frameBufferTexture->GetWidth() != window->GetWidth() ||
                        frameBufferTexture->GetHeight() != window->GetHeight())
                    {
                        delete m_FrameBuffer;
                        m_FrameBuffer = KROSS_NEW FrameBuffer(window->GetWidth(), window->GetHeight());
                    }
                    
                    frameBufferTexture = m_FrameBuffer->GetTexture();

                    m_FrameBuffer->Bind();
                    m_FrameBuffer->ClearBuffer();

                    /* Set Shader Values. */
                    m_Shader->SetUniform("u_HalfSize", 0.015f);
                    m_Shader->SetUniform("u_InverseAspect", 1.0f / Application::GetWindow()->GetApsectRatio());
                    m_Shader->SetUniform("u_Colour", Colour(0.28f, 0.71f, 0.91f, 1.0f));

                    /* Start the Data Transfer. */
                    m_VertexArray->Bind();

                    /* Set Data.*/
                    m_VertexBuffer->SetVertexData(m_WaterBatch->m_Data.data(), m_WaterBatch->m_Data.size() * sizeof(WaterVertex));
                    m_IndexBuffer->SetIndexData(m_WaterBatch->m_Indicies.data(), m_WaterBatch->m_Indicies.size());

                    /* Link both Index Buffer and Vertex Buffer to the Vertex Array. */
                    m_IndexBuffer->Bind();
                    m_VertexArray->AttachVertexBufferToLayout(*m_VertexBuffer, m_VertexBufferLayout);
                    VertexArray::UnBind();

                    /* Render the Batch. */
                    m_Shader->Bind();
                    m_VertexArray->Bind();
                    glDrawElements(GL_POINTS, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

                    /* Detahc the Frame Buffer because we are finished with it. */
                    FrameBuffer::UnBind();

                    /* Start the Data Transfer. */
                    m_VertexArray->Bind();

                    /* Full Screen Quad */
                    std::vector<WaterVertex> data;
                    data.push_back(WaterVertex(Vector2(-1.0f, 1.0f), Vector2(0.0f), Colour(1.0f)));
                    data.push_back(WaterVertex(Vector2(1.0f, 1.0f), Vector2(1.0f, 0.0f), Colour(1.0f)));
                    data.push_back(WaterVertex(Vector2(-1.0f, -1.0f), Vector2(0.0f, 1.0f), Colour(1.0f)));
                    data.push_back(WaterVertex(Vector2(1.0f, -1.0f), Vector2(1.0f), Colour(1.0f)));

                    /* Proper Indexing. */
                    std::vector<unsigned int> indicies;
                    indicies = { 0, 1, 2, 1, 3, 2 }; /* May need to be changed. */

                    /* Set Data.*/
                    m_VertexBuffer->SetVertexData(data.data(), data.size() * sizeof(WaterVertex));
                    m_IndexBuffer->SetIndexData(indicies.data(), indicies.size());

                    /* Link both Index Buffer and Vertex Buffer to the Vertex Array. */
                    m_IndexBuffer->Bind();
                    m_VertexArray->AttachVertexBufferToLayout(*m_VertexBuffer, m_VertexBufferLayout);
                    VertexArray::UnBind();

                    /* Bind the Frame Buffer Texture. */
                    m_FrameBuffer->GetTexture()->Bind();

                    /* Pass the Texture to the Post Process Shader. */
                    m_PostProcessShader->SetUniform("u_Texture", frameBufferTexture);

                    m_PostProcessShader->SetUniform("u_RenderTargetWidth", frameBufferTexture->GetWidth());
                    m_PostProcessShader->SetUniform("u_RenderTargetHeight", frameBufferTexture->GetHeight());

                    /* Draw the Final Image. */
                    m_PostProcessShader->Bind();
                    m_VertexArray->Bind();
                    glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

                    Texture::UnBind();
                }

                break;
            }
            case Layer::UI:
            {
                /* Attach the Font Texture. */
                m_Texture->Bind();
                m_Shader->SetUniform("u_Texture", m_Texture);

                /* Start the Data Transfer. */
                m_VertexArray->Bind();

                /* Set Data.*/
                m_VertexBuffer->SetVertexData(m_TextBatch->m_Data.data(), m_TextBatch->m_Data.size() * sizeof(TextVertex));
                m_IndexBuffer->SetIndexData(m_TextBatch->m_Indicies.data(),m_TextBatch->m_Indicies.size());

                /* Link both Index Buffer and Vertex Buffer to the Vertex Array. */
                m_IndexBuffer->Bind();
                m_VertexArray->AttachVertexBufferToLayout(*m_VertexBuffer, m_VertexBufferLayout);
                m_VertexArray->UnBind();

                /* Render the Batch. */
                m_Shader->Bind();
                m_VertexArray->Bind();
                glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

                break;
            }
            default:
            {
                /* Attach the Texture. */
                m_Atlas->GetTexture()->Bind();
                m_Shader->SetUniform("u_Atlas", m_Atlas->GetTexture());

                /* Start the Data Transfer. */
                m_VertexArray->Bind();
                  
                /* Set Data.*/
                m_VertexBuffer->SetVertexData(m_SpriteBatch->m_Data.data(), m_SpriteBatch->m_Data.size() * sizeof(SpriteVertex));
                m_IndexBuffer->SetIndexData(m_SpriteBatch->m_Indicies.data(), m_SpriteBatch->m_Indicies.size());
                
                /* Link both Index Buffer and Vertex Buffer to the Vertex Array. */
                m_IndexBuffer->Bind();
                m_VertexArray->AttachVertexBufferToLayout(*m_VertexBuffer, m_VertexBufferLayout);
                m_VertexArray->UnBind();

                /* Render the Batch. */
                m_Shader->Bind();
                m_VertexArray->Bind();
                glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

                break;
            }
        }

        Texture::UnBind();

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
                m_WaterBatch->Clear();
                break;
            }
            case Layer::UI:
            {
                m_TextBatch->Clear();
                break;
            }
            default:
            {
                m_SpriteBatch->Clear();
                break;
            }
        }
    }
}