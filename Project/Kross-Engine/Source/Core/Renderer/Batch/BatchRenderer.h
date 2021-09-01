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
            m_Shader                            (nullptr),
            m_PostProcessShader                 (nullptr),

            m_FrameBuffer                       (nullptr),

            m_VertexArray                       (KROSS_NEW VertexArray()),
            m_VertexBuffer                      (KROSS_NEW VertexBuffer()),
            m_IndexBuffer                       (KROSS_NEW IndexBuffer()),

            m_VertexBufferLayout                (KROSS_NEW VertexBufferLayout()),

            m_PostProcessVertexArray            (KROSS_NEW VertexArray()),
            m_PostProcessVertexBuffer           (KROSS_NEW VertexBuffer()),
            m_PostProcessIndexBuffer            (KROSS_NEW IndexBuffer()),

            m_PostProcessVertexBufferLayout     (KROSS_NEW VertexBufferLayout()),

            m_Atlas                             (atlas), 
            m_Texture                           (nullptr), 

            m_SpriteBatch                       (KROSS_NEW Batch<SpriteVertex>(atlas)),
            m_TextBatch                         (KROSS_NEW Batch<TextVertex>(atlas)),
            m_WaterBatch                        (KROSS_NEW Batch<WaterVertex>(atlas)),

            m_Layer                             (layer)
        {};
        ~BatchRenderer();

        Shader* m_Shader;
        Shader* m_PostProcessShader;

        FrameBuffer* m_FrameBuffer;

        VertexArray* m_VertexArray;
        VertexBuffer* m_VertexBuffer;
        IndexBuffer* m_IndexBuffer;

        VertexBufferLayout* m_VertexBufferLayout;

        VertexArray* m_PostProcessVertexArray;
        VertexBuffer* m_PostProcessVertexBuffer;
        IndexBuffer* m_PostProcessIndexBuffer;

        VertexBufferLayout* m_PostProcessVertexBufferLayout;

        // Use Atlas for Standard Drawing.
        Atlas* m_Atlas;

        // Use Texture for Special Cases like Text Renderering..
        Texture* m_Texture;
        
        /* Batch Type to allow the Renderer to switch which one it uses. */

        Batch<SpriteVertex>* m_SpriteBatch;
        Batch<TextVertex>* m_TextBatch;
        Batch<WaterVertex>* m_WaterBatch;

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

        void AttachRenderer(Camera* camera, Renderer* renderer);
    };
}