/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../Physics.h"

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
        /* Gets the shape of the object */
        virtual ShapeType GetShapeType() const = 0;
    };
}
