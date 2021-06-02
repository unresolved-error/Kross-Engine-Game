/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Component/Renderer.h"

#include "../Shader/Shader.h"

#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"

#include "../VertexBufferLayout.h"

#include "Batch.h"

#include "../FrameBuffer.h"
#include "../../Layer.h"

namespace Kross
{
    //template<typename Type> class Batch;

    class KROSS_API BatchRenderer
    {
    private:
        BatchRenderer(Atlas* atlas, Layer layer) : 
            p_Shader                (nullptr), 
            p_PostProcessShader     (nullptr), 

            p_VertexArray           (KROSS_NEW VertexArray()),
            p_VertexBuffer          (KROSS_NEW VertexBuffer()),
            p_IndexBuffer           (KROSS_NEW IndexBuffer()),

            p_VertexBufferLayout    (KROSS_NEW VertexBufferLayout()),
            p_Atlas                 (atlas), 
            p_Texture               (nullptr), 

            p_WaterBatch            (KROSS_NEW Batch<WaterVertex>(atlas)),
            p_TextBatch             (KROSS_NEW Batch<TextVertex>(atlas)),
            p_SpriteBatch           (KROSS_NEW Batch<SpriteVertex>(atlas)),

            m_Layer                 (layer)
        {};
        ~BatchRenderer();

        Shader* p_Shader;
        Shader* p_PostProcessShader;

        VertexArray* p_VertexArray;
        VertexBuffer* p_VertexBuffer;
        IndexBuffer* p_IndexBuffer;

        VertexBufferLayout* p_VertexBufferLayout;

        // Use Atlas for Standard Drawing.
        Atlas* p_Atlas;

        // Use Texture for Special Cases like Text Renderering..
        Texture* p_Texture;
        
        /* Batch Type to allow the Renderer to switch which one it uses. */
        Batch<WaterVertex>* p_WaterBatch;
        Batch<TextVertex>* p_TextBatch;
        Batch<SpriteVertex>* p_SpriteBatch;

        Layer m_Layer;

    protected:
        friend class Scene;

        void OnStart();
        void OnRender();
        void OnFinish();

        void OnClean();

    public:
        static BatchRenderer* OnCreate(Layer layer);
        static void OnDestroy(BatchRenderer* renderer);

        void AttachRenderer(Renderer* renderer);
    };
}