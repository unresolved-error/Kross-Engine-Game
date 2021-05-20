/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */
 /*
  *  Author: Deklyn Palmer.
  *  Editors:
  *      - Deklyn Palmer.
  */

#pragma once

#include "../../Core.h"

#include "../Vertex/Vertex.h"
#include "../Image/Atlas.h"

#include "../../Component/Renderer.h"

// How many Rendering Quads can be passed in by default.
#define MAX_BATCH_SIZE 32

namespace Kross
{
    class KROSS_API Batch
    {
    private:
        List<Vertex> m_Data;
        List<unsigned int> m_Indicies;

        Atlas* p_Atlas;

        unsigned int m_MaxBatchSize;
        unsigned int m_BatchSize;
    protected:

    public:
        Batch(Atlas* atlas)
            : m_Data(List<Vertex>()), m_Indicies(List<unsigned int>()), p_Atlas(atlas), m_MaxBatchSize(MAX_BATCH_SIZE), m_BatchSize(0)
        {};

        template<typename Type>
        void Attach(Type* renderer)
        {
            static_assert(std::is_convertible<Type*, Renderer*>::value, "Type must be convertable to Type Renderer.");
        }

        template<>
        void Attach<SpriteRenderer>(SpriteRenderer* renderer)
        {
            Sprite* sprite = renderer->GetSprite();
            Matrix4 model = renderer->GetObject()->GetTransform()->GetModelMatrix();
            AtlasSpriteData spriteData = p_Atlas->GetSpriteData(sprite);

            List<Vertex> geometryVertexes = sprite->GetGeometry()->m_Geometry;
            List<Vector2> uvs = List<Vector2>(4);

            if (renderer->GetFlipX()) 
            {
                uvs[0].x = ((1.0f - 1.0f) * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
                uvs[1].x = ((1.0f - 1.0f) * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
                uvs[2].x = ((1.0f - 0.0f) * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
                uvs[3].x = ((1.0f - 0.0f) * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
            }

            else
            {
                uvs[0].x = (1.0f * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
                uvs[1].x = (1.0f * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
                uvs[2].x = (0.0f * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
                uvs[3].x = (0.0f * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
            }

            if (renderer->GetFlipY())
            {
                uvs[0].y = ((1.0f - 1.0f) * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
                uvs[1].y = ((1.0f - 0.0f) * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
                uvs[2].y = ((1.0f - 0.0f) * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
                uvs[3].y = ((1.0f - 1.0f) * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
            }

            else
            {
                uvs[0].y = (1.0f * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
                uvs[1].y = (0.0f * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
                uvs[2].y = (0.0f * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
                uvs[3].y = (1.0f * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
            }

            Vertex topRight =       Vertex(model * Vector4(geometryVertexes[0].m_Position, 0.0f, 1.0f), 
                                            uvs[0],
                                            renderer->GetColour());
            Vertex bottomRight =    Vertex(model * Vector4(geometryVertexes[1].m_Position, 0.0f, 1.0f), 
                                            uvs[1], 
                                            renderer->GetColour());
            Vertex bottomLeft =     Vertex(model * Vector4(geometryVertexes[2].m_Position, 0.0f, 1.0f), 
                                            uvs[2], 
                                            renderer->GetColour());
            Vertex topLeft =        Vertex(model * Vector4(geometryVertexes[3].m_Position, 0.0f, 1.0f), 
                                            uvs[3], 
                                            renderer->GetColour());

            int vertexCount = m_Data.size();
            
            m_Indicies.push_back(0 + vertexCount);
            m_Indicies.push_back(1 + vertexCount);
            m_Indicies.push_back(2 + vertexCount);
            m_Indicies.push_back(2 + vertexCount);
            m_Indicies.push_back(3 + vertexCount);
            m_Indicies.push_back(0 + vertexCount);
            
            m_Data.push_back(topRight);
            m_Data.push_back(bottomRight);
            m_Data.push_back(bottomLeft);
            m_Data.push_back(topLeft);
        }
    };
}