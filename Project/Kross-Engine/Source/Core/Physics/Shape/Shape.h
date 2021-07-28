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
#include "../Filters/ShapeType.h"

namespace Kross
{
    class KROSS_API Shape
    {
    protected:
        Vector2 m_offset = {0,0};

    public:
        /* Gets the shape of the object */
        virtual ShapeType GetShapeType() const = 0;
    };
}
