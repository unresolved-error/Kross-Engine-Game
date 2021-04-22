/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "Box2D/Box2D.h"
#include "../../Component/Rigidbody2D.h"

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
        Rigidbody2D* p_RigidBody;

        Vector2 m_offset;
        // TODO: Fixed this thingy up or something. 
    public:
        virtual ShapeType GetShapeType() const = 0;

        Rigidbody2D* GetRigidBodyPointer() const { return p_RigidBody; }

        b2World* worldPointer = new b2World({ 0.0f, -9.81f });;
    };
}
