/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Component/Renderer.h"
#include "../../Layer.h"

#include "../FrameBuffer.h"

#include "Batch.h"

namespace Kross
{
    class KROSS_API BatchRenderer
    {
    private:
        BatchRenderer(Atlas* atlas, Layer layer)
            : p_BatchShader(nullptr), p_WaterShader(nullptr), p_Atlas(atlas), p_Batch(KROSS_NEW Batch(atlas)), m_Layer(layer), p_WaterBuffer(KROSS_NEW FrameBuffer())
        {};
        ~BatchRenderer();

        Shader* p_BatchShader;
        Shader* p_WaterShader;
        Atlas* p_Atlas;
        Batch* p_Batch;
        Layer m_Layer;

        FrameBuffer* p_WaterBuffer;

    protected:
        friend class Scene;

        void OnStart() {
            if (m_Layer == Layer::Fluids)
                p_BatchShader = ResourceManager::GetResource<Shader>("WaterShader");

            else
                p_BatchShader = ResourceManager::GetResource<Shader>("BatchShader");

            p_Atlas = ResourceManager::GetAtlas();
            p_Batch->p_Atlas = p_Atlas;
        };
        void OnRender();
        void OnFinish();

        void OnClean();

    public:
        static BatchRenderer* OnCreate(Layer layer);
        static void OnDestroy(BatchRenderer* renderer);

        void AttachRenderer(Renderer* renderer);
    };
}