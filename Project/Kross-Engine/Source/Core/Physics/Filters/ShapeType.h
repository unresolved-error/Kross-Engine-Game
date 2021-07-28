/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../../Core.h"

namespace Kross
{
    // Instantiates the enum class for collision shapes.
    enum class KROSS_API ShapeType
    {
        Box,
        Circle,
        Capsule,
        Plane,
        Count
    };
}