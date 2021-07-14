 /*
  *  Author: Deklyn Palmer.
  *  Editors:
  *      - Deklyn Palmer.
  */

#pragma once

#include "../../Core.h"

#include "../Image/Atlas.h"
#include "../Vertex/Vertex.h"
#include "../../Component/Renderer.h"

// How much Geometry can be passed in by default.
#define MAX_BATCH_SIZE 512

namespace Kross
{
    template<typename Type>
    class KROSS_API Batch
    {
    private:
        List<Type> m_Data;
        List<unsigned int> m_Indicies;

        Atlas* p_Atlas;

        unsigned int m_MaxBatchSize;
        unsigned int m_BatchSize;

    protected:
        friend class BatchRenderer;

        // Gets how much Geometry has been passed into the Batch.
        const int GetSize() const { return m_BatchSize; };

        // Gets the Size in Bytes of the Data.
        unsigned int GetDataSize() const { return (unsigned int)(m_Data.size() * sizeof(Type)); };

        // Gets the First Element in the Data Array.
        const void* GetDataElement() const { return m_Data.data(); };

        // Gets the Count of the Index Data.
        unsigned int GetIndexCount() const { return m_Indicies.size(); };

        // Gets the First Element in the Index Array.
        const void* GetIndexElement() const { return m_Indicies.data(); };

    public:
        Batch(Atlas* atlas) : 
            m_Data              (List<Type>()), 
            m_Indicies          (List<unsigned int>()), 
            p_Atlas             (atlas), 
            m_MaxBatchSize      (MAX_BATCH_SIZE), 
            m_BatchSize         (0)
        {
            /* Check if the type passed through is a Child of Vertex. */
            static_assert(std::is_convertible<Type, Vertex>::value, "Type must be of Vertex!");
        };

        ~Batch()
        {
            /* Clean up the Data. */
            m_Data.clear();
            m_Indicies.clear();

            /* Null out the Atlas. */
            p_Atlas = nullptr;
        };

        // Add Sprite Renderer Data to the Batch.
        void Attach(SpriteRenderer* renderer)
        {
            /* Check if we have the Right Vertex Type First. */
            static_assert(std::is_convertible<Type, SpriteVertex>::value, "Type must be of Sprite Vertex!");

            /* Get all Material Sprites. */
            Sprite* diffuseSprite = renderer->GetDiffuseMap();
            Sprite* normalSprite = renderer->GetNormalMap();
            Sprite* specularSprite = renderer->GetSpecularMap();

            /* Quick Variables. */
            Transform2D* transform = renderer->GetLinkObject()->GetTransform();

            /* Update the Model. */
            Matrix4 model = Matrix4(1.0f);

            /* Update the Translation, Rotation and Scale Marixes. */
            Matrix4 translation = glm::translate(Matrix4(1.0f), Vector3(transform->m_Position, 0.0f));
            Matrix4 rotation = glm::rotate(Matrix4(1.0f), glm::radians(transform->m_Rotation), Vector3(0.0f, 0.0f, 1.0f));
            Matrix4 scale = glm::scale(Matrix4(1.0f), Vector3(transform->m_Scale, 0.0f));

            model = translation * rotation * scale;

            /* Get all the Sprite Data needed. */
            AtlasSpriteData diffuseData = p_Atlas->GetSpriteData(diffuseSprite);
            AtlasSpriteData normalData = p_Atlas->GetSpriteData(normalSprite);
            AtlasSpriteData specularData = p_Atlas->GetSpriteData(specularSprite);

            /* Get Diffuse Sprite Geometry. */
            Geometry* geometry = diffuseSprite->GetGeometry();

            /* Get UVs for all Sprites. */
            List<Vector2> uvs = List<Vector2>(12);
            /*
                0 - 3 Diffuse UVs.
                4 - 7 Normal UVs.
                8 - 11 Specular UVs.
            */

            if (renderer->GetFlipX()) 
            {
                /* Diffuse UVs. */
                uvs[0].x = ((1.0f - 1.0f) * diffuseData.m_Ratio.x) + diffuseData.m_Offset.x;
                uvs[1].x = ((1.0f - 1.0f) * diffuseData.m_Ratio.x) + diffuseData.m_Offset.x;
                uvs[2].x = ((1.0f - 0.0f) * diffuseData.m_Ratio.x) + diffuseData.m_Offset.x;
                uvs[3].x = ((1.0f - 0.0f) * diffuseData.m_Ratio.x) + diffuseData.m_Offset.x;

                /* Normal UVs. */
                uvs[4].x = ((1.0f - 1.0f) * normalData.m_Ratio.x) + normalData.m_Offset.x;
                uvs[5].x = ((1.0f - 1.0f) * normalData.m_Ratio.x) + normalData.m_Offset.x;
                uvs[6].x = ((1.0f - 0.0f) * normalData.m_Ratio.x) + normalData.m_Offset.x;
                uvs[7].x = ((1.0f - 0.0f) * normalData.m_Ratio.x) + normalData.m_Offset.x;

                /* Specular UVs. */
                uvs[8].x = ((1.0f - 1.0f) * specularData.m_Ratio.x) + specularData.m_Offset.x;
                uvs[9].x = ((1.0f - 1.0f) * specularData.m_Ratio.x) + specularData.m_Offset.x;
                uvs[10].x = ((1.0f - 0.0f) * specularData.m_Ratio.x) + specularData.m_Offset.x;
                uvs[11].x = ((1.0f - 0.0f) * specularData.m_Ratio.x) + specularData.m_Offset.x;
            }
            
            else
            {
                /* Diffuse UVs. */
                uvs[0].x = (1.0f * diffuseData.m_Ratio.x) + diffuseData.m_Offset.x;
                uvs[1].x = (1.0f * diffuseData.m_Ratio.x) + diffuseData.m_Offset.x;
                uvs[2].x = (0.0f * diffuseData.m_Ratio.x) + diffuseData.m_Offset.x;
                uvs[3].x = (0.0f * diffuseData.m_Ratio.x) + diffuseData.m_Offset.x;

                /* Normal UVs. */
                uvs[4].x = (1.0f * normalData.m_Ratio.x) + normalData.m_Offset.x;
                uvs[5].x = (1.0f * normalData.m_Ratio.x) + normalData.m_Offset.x;
                uvs[6].x = (0.0f * normalData.m_Ratio.x) + normalData.m_Offset.x;
                uvs[7].x = (0.0f * normalData.m_Ratio.x) + normalData.m_Offset.x;

                /* Specular UVs. */
                uvs[8].x = (1.0f * specularData.m_Ratio.x) + specularData.m_Offset.x;
                uvs[9].x = (1.0f * specularData.m_Ratio.x) + specularData.m_Offset.x;
                uvs[10].x = (0.0f * specularData.m_Ratio.x) + specularData.m_Offset.x;
                uvs[11].x = (0.0f * specularData.m_Ratio.x) + specularData.m_Offset.x;
            }
            
            if (renderer->GetFlipY())
            {
                /* Diffuse UVs. */
                uvs[0].y = ((1.0f - 1.0f) * diffuseData.m_Ratio.y) + diffuseData.m_Offset.y;
                uvs[1].y = ((1.0f - 0.0f) * diffuseData.m_Ratio.y) + diffuseData.m_Offset.y;
                uvs[2].y = ((1.0f - 0.0f) * diffuseData.m_Ratio.y) + diffuseData.m_Offset.y;
                uvs[3].y = ((1.0f - 1.0f) * diffuseData.m_Ratio.y) + diffuseData.m_Offset.y;

                /* Normal UVs. */
                uvs[4].y = ((1.0f - 1.0f) * normalData.m_Ratio.y) + normalData.m_Offset.y;
                uvs[5].y = ((1.0f - 0.0f) * normalData.m_Ratio.y) + normalData.m_Offset.y;
                uvs[6].y = ((1.0f - 0.0f) * normalData.m_Ratio.y) + normalData.m_Offset.y;
                uvs[7].y = ((1.0f - 1.0f) * normalData.m_Ratio.y) + normalData.m_Offset.y;

                /* Specular UVs. */
                uvs[8].y = ((1.0f - 1.0f) * specularData.m_Ratio.y) + specularData.m_Offset.y;
                uvs[9].y = ((1.0f - 0.0f) * specularData.m_Ratio.y) + specularData.m_Offset.y;
                uvs[10].y = ((1.0f - 0.0f) * specularData.m_Ratio.y) + specularData.m_Offset.y;
                uvs[11].y = ((1.0f - 1.0f) * specularData.m_Ratio.y) + specularData.m_Offset.y;
            }
            
            else
            {
                /* Diffuse UVs. */
                uvs[0].y = (1.0f * diffuseData.m_Ratio.y) + diffuseData.m_Offset.y;
                uvs[1].y = (0.0f * diffuseData.m_Ratio.y) + diffuseData.m_Offset.y;
                uvs[2].y = (0.0f * diffuseData.m_Ratio.y) + diffuseData.m_Offset.y;
                uvs[3].y = (1.0f * diffuseData.m_Ratio.y) + diffuseData.m_Offset.y;

                /* Normal UVs. */
                uvs[4].y = (1.0f * normalData.m_Ratio.y) + normalData.m_Offset.y;
                uvs[5].y = (0.0f * normalData.m_Ratio.y) + normalData.m_Offset.y;
                uvs[6].y = (0.0f * normalData.m_Ratio.y) + normalData.m_Offset.y;
                uvs[7].y = (1.0f * normalData.m_Ratio.y) + normalData.m_Offset.y;

                /* Specular UVs. */
                uvs[8].y = (1.0f * specularData.m_Ratio.y) + specularData.m_Offset.y;
                uvs[9].y = (0.0f * specularData.m_Ratio.y) + specularData.m_Offset.y;
                uvs[10].y = (0.0f * specularData.m_Ratio.y) + specularData.m_Offset.y;
                uvs[11].y = (1.0f * specularData.m_Ratio.y) + specularData.m_Offset.y;
            }

            /* Quick Variables. */
            float halfWidth = geometry->GetSize().x / 2.0f;
            float halfHeight = geometry->GetSize().y / 2.0f;

            /* Vertex Data. */
            SpriteVertex topRight =     SpriteVertex(model * Vector4(halfWidth, halfHeight, 0.0f, 1.0f),
                                            uvs[0],
                                            uvs[4],
                                            uvs[8],
                                            Vector3(0.0f, 0.0f, 1.0f),
                                            renderer->GetColour());
            SpriteVertex bottomRight =  SpriteVertex(model * Vector4(halfWidth, -halfHeight, 0.0f, 1.0f),
                                            uvs[1], 
                                            uvs[5],
                                            uvs[9],
                                            Vector3(0.0f, 0.0f, 1.0f),
                                            renderer->GetColour());
            SpriteVertex bottomLeft =   SpriteVertex(model * Vector4(-halfWidth, -halfHeight, 0.0f, 1.0f),
                                            uvs[2], 
                                            uvs[6],
                                            uvs[10],
                                            Vector3(0.0f, 0.0f, 1.0f),
                                            renderer->GetColour());
            SpriteVertex topLeft =      SpriteVertex(model * Vector4(-halfWidth, halfHeight, 0.0f, 1.0f),
                                            uvs[3], 
                                            uvs[7],
                                            uvs[11],
                                            Vector3(0.0f, 0.0f, 1.0f),
                                            renderer->GetColour());
            
            /* Grab the Current Vertex Count. */
            int vertexCount = m_Data.size();
            
            /* Attach the Indicies. */
            m_Indicies.push_back(0 + vertexCount);
            m_Indicies.push_back(1 + vertexCount);
            m_Indicies.push_back(2 + vertexCount);
            m_Indicies.push_back(2 + vertexCount);
            m_Indicies.push_back(3 + vertexCount);
            m_Indicies.push_back(0 + vertexCount);
            
            /* Attach the Vertex Data. */
            m_Data.push_back(topRight);
            m_Data.push_back(bottomRight);
            m_Data.push_back(bottomLeft);
            m_Data.push_back(topLeft);
            
            /* Update the Size. */
            m_BatchSize++;
        }

        // Add Tile Map Renderer Data to the Batch.
        void Attach(TileMapRenderer* renderer)
        {
            /* Check if we have the Right Vertex Type First. */
            static_assert(std::is_convertible<Type, SpriteVertex>::value, "Type must be of Sprite Vertex!");

            /* Quick Variables. */
            Transform2D* transform = renderer->GetLinkObject()->GetTransform();

            for (int i = 0; i < renderer->m_Tiles.size(); i++)
            {
                Tile* currentTile = renderer->m_Tiles[i];
                /* Update the Model. */
                Matrix4 model = Matrix4(1.0f);

                /* Update the Translation, Rotation and Scale Marixes. */
                Matrix4 translation = glm::translate(Matrix4(1.0f), Vector3(transform->m_Position + currentTile->m_Offset, 0.0f));
                Matrix4 rotation = glm::rotate(Matrix4(1.0f), glm::radians(transform->m_Rotation), Vector3(0.0f, 0.0f, 1.0f));
                Matrix4 scale = glm::scale(Matrix4(1.0f), Vector3(transform->m_Scale, 0.0f));

                model = translation * rotation * scale;

                /* Get the Sprite Data needed. */
                AtlasSpriteData spriteData = p_Atlas->GetSpriteData(currentTile->p_Sprite);

                /* Get Sprite Geometry. */
                Geometry* geometry = currentTile->p_Sprite->GetGeometry();

                /* Get UVs for Sprite. */
                List<Vector2> uvs = List<Vector2>(4);

                /* Diffuse UVs. */
                uvs[0].x = (1.0f * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
                uvs[1].x = (1.0f * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
                uvs[2].x = (0.0f * spriteData.m_Ratio.x) + spriteData.m_Offset.x;
                uvs[3].x = (0.0f * spriteData.m_Ratio.x) + spriteData.m_Offset.x;

                /* Diffuse UVs. */
                uvs[0].y = (1.0f * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
                uvs[1].y = (0.0f * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
                uvs[2].y = (0.0f * spriteData.m_Ratio.y) + spriteData.m_Offset.y;
                uvs[3].y = (1.0f * spriteData.m_Ratio.y) + spriteData.m_Offset.y;

                /* Quick Variables. */
                float halfWidth = geometry->GetSize().x / 2.0f;
                float halfHeight = geometry->GetSize().y / 2.0f;

                /* Vertex Data. */
                SpriteVertex topRight = SpriteVertex(model * Vector4(halfWidth, halfHeight, 0.0f, 1.0f),
                    uvs[0],
                    Vector2(0.0f),
                    Vector2(0.0f),
                    Vector3(0.0f, 0.0f, 1.0f),
                    Colour(1.0f));
                SpriteVertex bottomRight = SpriteVertex(model * Vector4(halfWidth, -halfHeight, 0.0f, 1.0f),
                    uvs[1],
                    Vector2(0.0f),
                    Vector2(0.0f),
                    Vector3(0.0f, 0.0f, 1.0f),
                    Colour(1.0f));
                SpriteVertex bottomLeft = SpriteVertex(model * Vector4(-halfWidth, -halfHeight, 0.0f, 1.0f),
                    uvs[2],
                    Vector2(0.0f),
                    Vector2(0.0f),
                    Vector3(0.0f, 0.0f, 1.0f),
                    Colour(1.0f));
                SpriteVertex topLeft = SpriteVertex(model * Vector4(-halfWidth, halfHeight, 0.0f, 1.0f),
                    uvs[3],
                    Vector2(0.0f),
                    Vector2(0.0f),
                    Vector3(0.0f, 0.0f, 1.0f),
                    Colour(1.0f));

                /* Grab the Current Vertex Count. */
                int vertexCount = m_Data.size();

                /* Attach the Indicies. */
                m_Indicies.push_back(0 + vertexCount);
                m_Indicies.push_back(1 + vertexCount);
                m_Indicies.push_back(2 + vertexCount);
                m_Indicies.push_back(2 + vertexCount);
                m_Indicies.push_back(3 + vertexCount);
                m_Indicies.push_back(0 + vertexCount);

                /* Attach the Vertex Data. */
                m_Data.push_back(topRight);
                m_Data.push_back(bottomRight);
                m_Data.push_back(bottomLeft);
                m_Data.push_back(topLeft);

                /* Update the Size. */
                m_BatchSize++;
            }
        }

        // Add Text Renderer Data to the Batch.
        void Attach(TextRenderer* renderer)
        {
            /* Check if we have the Right Vertex Type First. */
            static_assert(std::is_convertible<Type, TextVertex>::value, "Type must be of Text Vertex!");

            /* Get all of the Characters from the Renderer. */
            List<Character*> characters = renderer->m_TextCharacters;

            /* Get their Corresponding Sprites. */
            List<Sprite*> characterSprites;
            for (int i = 0; i < characters.size(); i++)
                characterSprites.push_back(characters[i]->GetSprite());
            
            /* Calculate the UVs and Vertex Data. */
            for (int i = 0; i < characterSprites.size(); i++)
            {
                /* Quick Variables. */
                List<Vector2> uvs = List<Vector2>(4);
                Vector2 spriteRatio = characterSprites[i]->GetUVRatio();
                Vector2 spriteOffset = characterSprites[i]->GetUVOffset();

                /* Calculate UVs. */
                uvs[0].x = (1.0f * spriteRatio.x) + spriteOffset.x;
                uvs[1].x = (1.0f * spriteRatio.x) + spriteOffset.x;
                uvs[2].x = (0.0f * spriteRatio.x) + spriteOffset.x;
                uvs[3].x = (0.0f * spriteRatio.x) + spriteOffset.x;

                uvs[0].y = (1.0f * spriteRatio.y) + spriteOffset.y;
                uvs[1].y = (0.0f * spriteRatio.y) + spriteOffset.y;
                uvs[2].y = (0.0f * spriteRatio.y) + spriteOffset.y;
                uvs[3].y = (1.0f * spriteRatio.y) + spriteOffset.y;
            
                /* Get the Model of the Text. */
                Matrix4 model;
                Matrix4 modelPosition = glm::translate(Matrix4(1.0f), Vector3(characters[i]->m_Position, 0.0f));
                Matrix4 modelRotation = glm::rotate(Matrix4(1.0f), glm::radians(0.0f), Vector3(0.0f, 0.0f, 1.0f)); /* Set this to Zero as text isn't rotating... */
                Matrix4 modelScale = glm::scale(Matrix4(1.0f), Vector3(characters[i]->m_Scale, 0.0f));			   /* Atleast not now anyway. */
                
                /* Update the Model. */
                model = modelPosition * modelRotation * modelScale;

                /* Grab the Current Sprite Geometry. */
                Geometry* geometry = characterSprites[i]->GetGeometry();

                /* Quick Variables. */
                float halfWidth = geometry->GetSize().x / 2.0f;
                float halfHeight = geometry->GetSize().y / 2.0f;
                
                /* Setup Vertex Data.*/
                TextVertex topRight = TextVertex(model * Vector4(halfWidth, halfHeight, 0.0f, 1.0f),
                    uvs[0],
                    renderer->GetColour());
                TextVertex bottomRight = TextVertex(model * Vector4(halfWidth, -halfHeight, 0.0f, 1.0f),
                    uvs[1],
                    renderer->GetColour());
                TextVertex bottomLeft = TextVertex(model * Vector4(-halfWidth, -halfHeight, 0.0f, 1.0f),
                    uvs[2],
                    renderer->GetColour());
                TextVertex topLeft = TextVertex(model * Vector4(-halfWidth, halfHeight, 0.0f, 1.0f),
                    uvs[3],
                    renderer->GetColour());
                    
                /* Grab the Current Vertex Count. */
                int vertexCount = m_Data.size();

                /* Attach the Indicies. */
                m_Indicies.push_back(0 + vertexCount);
                m_Indicies.push_back(1 + vertexCount);
                m_Indicies.push_back(2 + vertexCount);
                m_Indicies.push_back(2 + vertexCount);
                m_Indicies.push_back(3 + vertexCount);
                m_Indicies.push_back(0 + vertexCount);

                /* Attach the Vertex Data. */
                m_Data.push_back(topRight);
                m_Data.push_back(bottomRight);
                m_Data.push_back(bottomLeft);
                m_Data.push_back(topLeft);

            }
            
            /* Update the Size of the Batch. */
            m_BatchSize += characterSprites.size();
        }

        // Add Particle Data from an Emitter to the Batch.
        void Attach(ParticleEmitter* emitter)
        {
            /* Check if we have the Right Vertex Type First. */
            static_assert(std::is_convertible<Type, WaterVertex>::value, "Type must be of Text Vertex!");

            /* Grab Information Needed to pass to the Renderer. */
            for (int j = 0; j < emitter->GetParticleSystem().size(); j++)
            {
                b2Vec2* positions = emitter->GetParticleSystem()[j]->GetPositionBuffer();
                b2Vec2* velocities = emitter->GetParticleSystem()[j]->GetVelocityBuffer();
                int particleCount = emitter->GetParticleSystem()[j]->GetParticleCount();


                /* Go through each Particle. */
                for (int i = 0; i < particleCount; i++)
                {
                    /* Default Water Colour. */
                    //Colour waterColour = Colour(0.28f, 0.71f, 0.91f, 1.0f);
                    Colour waterColour = Colour(emitter->GetParticle(i)->GetColor());

                    /* Set the Vertex. */
                    WaterVertex waterDrop = WaterVertex(Vector2(positions[i].x, positions[i].y),
                        Vector2(velocities[i].x, velocities[i].y),
                        waterColour);
                    /* Grab the Vertex Count. */
                    int vertexCount = m_Data.size();

                    /* Attach the Index. */
                    m_Indicies.push_back(vertexCount);

                    /* Attach the Vertex Data. */
                    m_Data.push_back(waterDrop);
                }

                /* Update the Batch Size. */
                m_BatchSize += particleCount;
            }
        }

        // Gets if the Batch is Full.
        bool GetFullStatus() const { return (m_BatchSize >= m_MaxBatchSize); };

        // Gets if the Batch is Emptry.
        bool GetEmptyStatus() const { return (m_Data.size() == 0); };
        
    };
}