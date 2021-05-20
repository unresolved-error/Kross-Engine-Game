/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "BatchRenderer.h"

namespace Kross
{
    BatchRenderer::~BatchRenderer()
    {
        delete p_Batch;
    }

    BatchRenderer* BatchRenderer::OnCreate()
    {
        Atlas* atlas = ResourceManager::GetAtlas();
        BatchRenderer* renderer = KROSS_NEW BatchRenderer(atlas);

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
            if (!p_Batch->IsFull())
                p_Batch->Attach<SpriteRenderer>((SpriteRenderer*)renderer);

            else
                OnRender();
        }

        else if (typeid(*renderer) == typeid(TextRenderer))
        {
            if (!p_Batch->IsFull())
                p_Batch->Attach<TextRenderer>((TextRenderer*)renderer);

            else
                OnRender();
        }

        else if (typeid(*renderer) == typeid(ParticleEmitter))
        {
            if (!p_Batch->IsFull())
                p_Batch->Attach<ParticleEmitter>((ParticleEmitter*)renderer);

            else
                OnRender();
        }

        return;
    }

    void BatchRenderer::OnRender()
    {
        if (p_Batch->IsEmpty())
            return;

        p_Atlas->GetTexture()->Attach();
        p_Shader->SetUniform("u_Atlas", p_Atlas->GetTexture());

        p_Shader->Attach();
        p_Batch->OnCompile();
        p_Batch->OnRender();

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