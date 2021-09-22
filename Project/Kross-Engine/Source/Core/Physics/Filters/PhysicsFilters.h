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
        Default = 0,
        Player = 1 << 1,
        Enemy = 1 << 2,
        Level = 1 << 3,
        Environment = 1 << 4,
        Fluid = 1 << 5,
        BackGround = 1 << 6,
        Light = 1 << 7,
        Weapon = 1 << 8,
        Chain = 1 << 9,
        Puzzle = 1 << 10,
        Empty = 1 << 11
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
        /* Sets the variables to their default values */
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