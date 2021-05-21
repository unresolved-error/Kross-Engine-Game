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
#define MAX_BATCH_SIZE 64

namespace Kross
{
    class KROSS_API Batch
    {
    private:
        List<Vertex> m_Data;
        List<unsigned int> m_Indicies;

        Atlas* p_Atlas;

        IndexBuffer* m_IndexBuffer;
        VertexArray* m_VertexArray;
        VertexBuffer* m_VertexBuffer;

        unsigned int m_MaxBatchSize;
        unsigned int m_BatchSize;

    protected:
        friend class BatchRenderer;

        void OnCompile();

        void OnRender();

    public:
        Batch(Atlas* atlas)
            : m_Data(List<Vertex>()), m_Indicies(List<unsigned int>()), p_Atlas(atlas), m_IndexBuffer(KROSS_NEW IndexBuffer()), m_VertexArray(KROSS_NEW VertexArray()), m_VertexBuffer(KROSS_NEW VertexBuffer()), m_MaxBatchSize(MAX_BATCH_SIZE), m_BatchSize(0)
        {};

        ~Batch();

        template<typename Type>
        void Attach(Type* renderer)
        {
            static_assert(false, "Type must be convertable to Type Renderer.");
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

            m_BatchSize++;
        }

        template<>
        void Attach<TextRenderer>(TextRenderer* renderer)
        {
            List<Character*> characters = renderer->m_Text.m_TextCharacters;
            List<Sprite*> sprites;

            for (int i = 0; i < characters.size(); i++)
                sprites.push_back(characters[i]->GetSprite());

            List<List<Vector2>> spritesUVs;
            List<AtlasSpriteData> atlasSpriteData;
            for (int i = 0; i < sprites.size(); i++)
                atlasSpriteData.push_back(p_Atlas->GetSpriteData(sprites[i]));

            for (int i = 0; i < sprites.size(); i++)
            {
                spritesUVs.push_back(List<Vector2>(4));
                spritesUVs[i][0].x = (1.0f * atlasSpriteData[i].m_Ratio.x) + atlasSpriteData[i].m_Offset.x;
                spritesUVs[i][1].x = (1.0f * atlasSpriteData[i].m_Ratio.x) + atlasSpriteData[i].m_Offset.x;
                spritesUVs[i][2].x = (0.0f * atlasSpriteData[i].m_Ratio.x) + atlasSpriteData[i].m_Offset.x;
                spritesUVs[i][3].x = (0.0f * atlasSpriteData[i].m_Ratio.x) + atlasSpriteData[i].m_Offset.x;

                spritesUVs[i][0].y = (1.0f * atlasSpriteData[i].m_Ratio.y) + atlasSpriteData[i].m_Offset.y;
                spritesUVs[i][1].y = (0.0f * atlasSpriteData[i].m_Ratio.y) + atlasSpriteData[i].m_Offset.y;
                spritesUVs[i][2].y = (0.0f * atlasSpriteData[i].m_Ratio.y) + atlasSpriteData[i].m_Offset.y;
                spritesUVs[i][3].y = (1.0f * atlasSpriteData[i].m_Ratio.y) + atlasSpriteData[i].m_Offset.y;

                Matrix4 model;
                Matrix4 modelPosition = glm::translate(Matrix4(1.0f), Vector3(characters[i]->m_Position, 0.0f));
                Matrix4 modelRotation = glm::rotate(Matrix4(1.0f), glm::radians(0.0f), Vector3(0.0f, 0.0f, 1.0f)); /* Set this to Zero as text isn't rotating... */
                Matrix4 modelScale = glm::scale(Matrix4(1.0f), Vector3(characters[i]->m_Scale, 0.0f));							  /* Atleast not now anyway. */

                /* Update the Model. */
                model = modelPosition * modelRotation * modelScale;

                List<Vertex> geometryVertexes = sprites[i]->GetGeometry()->m_Geometry;

                Vertex topRight = Vertex(model * Vector4(geometryVertexes[0].m_Position, 0.0f, 1.0f),
                    spritesUVs[i][0],
                    renderer->GetColour());
                Vertex bottomRight = Vertex(model * Vector4(geometryVertexes[1].m_Position, 0.0f, 1.0f),
                    spritesUVs[i][1],
                    renderer->GetColour());
                Vertex bottomLeft = Vertex(model * Vector4(geometryVertexes[2].m_Position, 0.0f, 1.0f),
                    spritesUVs[i][2],
                    renderer->GetColour());
                Vertex topLeft = Vertex(model * Vector4(geometryVertexes[3].m_Position, 0.0f, 1.0f),
                    spritesUVs[i][3],
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

            m_BatchSize += sprites.size();
        }

        template<>
        void Attach<ParticleEmitter>(ParticleEmitter* emitter)
        {
            b2Vec2* positions = emitter->GetParticleSystem()->GetPositionBuffer();
            b2Vec2* velocities = emitter->GetParticleSystem()->GetVelocityBuffer();
            int particleCount = emitter->GetParticleSystem()->GetParticleCount();

            for (int i = 0; i < particleCount; i++)
            {
                Colour waterColour = Colour(0.28f, 0.71f, 0.91f, 1.0f);

                Vertex waterDrop = Vertex(Vector2(positions[i].x, positions[i].y),
                    Vector2(velocities[i].x, velocities[i].y),
                    waterColour);

                int vertexCount = m_Data.size();

                m_Indicies.push_back(vertexCount);

                m_Data.push_back(waterDrop);
            }

            m_BatchSize += particleCount;
        }

        bool IsFull() const { return (m_BatchSize >= m_MaxBatchSize); }

        bool IsEmpty() const { return (m_Data.size() == 0); }
        
    };
}