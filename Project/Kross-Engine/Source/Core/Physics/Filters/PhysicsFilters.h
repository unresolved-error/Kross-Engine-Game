/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once
#include "../../Core.h"

namespace Kross
{
    /* The Physical collider filters */
    enum class KROSS_API ColliderFilters
    {
        Default = 0x0000,
        Player = 0x0001,
        Environment = 0x0002,
        Fluid = 0x0004,
        BackGround = 0x0008,
        Light = 0x0010
    };


    /* The collision states */
    enum class KROSS_API CollisionState
    {
        None,
        Enter,
        Stay,
        Exit,
    };


    /* Instantiates the enum class for collision shapes */ 
    enum class KROSS_API ShapeType
    {
        Box,
        Circle,
        Capsule,
        Plane,
        Count
    };


    /* Enum class for player states */
    enum class KROSS_API RigidbodyState
    {
        Idle,
        Grounded,
        Walking,
        Running,
        Jumping,
        Falling,
        Swimming,
        Count
    };


    /* Collision detection data */
    struct KROSS_API AABBCollisionData
    {
        std::vector<b2Fixture*> m_Fixture;
        const b2ParticleSystem* p_ParticleSystem = nullptr;
        std::vector<int> m_ParticleIndexs;
        bool m_Collision = false;
    };


    /* The data from the raycast */
    struct KROSS_API RaycastData
    {
        bool hit = false;
        float closestFraction = 1.0f;
        float maxFraction = 1.0f;

        Vector2 pos = Vector2(0, 0);
        Vector2 direction = Vector2(0, 0);

        Vector2 intersectionPoint = pos + maxFraction * direction;
        Vector2 intersectionNormal = Vector2(0, 0);

        b2Fixture* fixture = nullptr;
        b2Body* body = nullptr;
    };
}