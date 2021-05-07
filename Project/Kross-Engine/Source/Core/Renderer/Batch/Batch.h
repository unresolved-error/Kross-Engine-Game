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

        unsigned int m_MaxBatchSize;
        unsigned int m_BatchSize;
    protected:

    public:
        Batch()
            : m_Data(List<Vertex>()), m_Indicies(List<unsigned int>()), m_MaxBatchSize(MAX_BATCH_SIZE), m_BatchSize(0)
        {};

        template<typename Type>
        void Attach(Type* renderer)
        {
            static_assert(std::is_convertible<Type*, Renderer*>::value, "Type must be convertable to Type Renderer.");
        }

        template<>
        void Attach<SpriteRenderer>(SpriteRenderer* renderer)
        {
            
        }
    };
}