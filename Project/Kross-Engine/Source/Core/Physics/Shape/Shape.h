/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "Box2D/Box2D.h"

namespace Kross
{
    // Instantiates the enum class for collision shapes.
    enum class KROSS_API ShapeType
    {
        Box,
        Circle,
        Plane,
        Count
    };


    class KROSS_API Shape
    {
    protected:
        Vector2 m_offset;

    public:
        virtual ShapeType GetShapeType() const = 0;
    };
}
