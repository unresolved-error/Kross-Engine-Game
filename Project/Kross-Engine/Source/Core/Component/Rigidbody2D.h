/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */
#pragma once

#include "../Core.h"

#include "Component.h"
#include "Box2D/Box2D.h"

#include "../Physics/Shape/Shape.h"

namespace Kross
{
    class KROSS_API Shape;

    class KROSS_API Rigidbody2D : public Component
    {
    protected:
        // template<typename Type>
        // void OnCreate(Type* shape)
        // {
        //     static_assert<false, "Type must be of Type Shape!">();
        // }
        //
        // template<>
        // void OnCreate<float>(float* shape)
        // {
        //     
        // }

        Shape* p_CollisionShape = nullptr;

        b2Body* p_Body = nullptr;

        b2MassData* p_MassData;

        b2Vec2 m_Velocity = { 0, 0 };
        b2Vec2 m_Acceleration = { 0, 0 };
        b2Vec2 m_ForceAccumulator = { 0, 0 };



    public:

        Rigidbody2D();
        ~Rigidbody2D();

        void OnApplyForce();
        void OnApplyImpulse();

        void OnStart() override;

        void OnUpdate() override;

        void OnRender() override;

        // Gets the Objects Position. 
        Vector2 GetPosition() const;
        Vector2 GetVelocity() const{ return Vector2(m_Velocity.x, m_Velocity.y); }
        Vector2 GetAcceleration() const{ return Vector2(m_Acceleration.x, m_Acceleration.y); }

        void SetMass(float mass) { p_MassData->mass = mass; }

    };
}