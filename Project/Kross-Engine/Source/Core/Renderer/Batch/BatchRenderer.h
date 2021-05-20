/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Component/Renderer.h"

#include "Batch.h"

namespace Kross
{
    class KROSS_API BatchRenderer
    {
    private:
        BatchRenderer(Atlas* atlas) : 
            p_Atlas     (atlas), 
            p_Batch     (KROSS_NEW Batch(atlas)),
            p_Shader    (ResourceManager::GetResource<Shader>("BatchShader"))
        {};
        ~BatchRenderer();

        Shader* p_Shader;
        Atlas* p_Atlas;
        Batch* p_Batch;

    protected:
        friend class Scene;

        void OnStart() {
            p_Atlas = ResourceManager::GetAtlas();
            p_Batch->p_Atlas = p_Atlas;
        };
        void OnRender();
        void OnFinish();

        void OnClean();

    public:
        static BatchRenderer* OnCreate();
        static void OnDestroy(BatchRenderer* renderer);

        void AttachRenderer(Renderer* renderer);
    };
}