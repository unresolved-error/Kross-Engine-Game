/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
 */

#pragma once
#include "../Core.h"

#include "../Math/Math.h"
#include "Box2D/Box2D.h"
#include "../Renderer/LineRenderer.h"
#include "Data/CollisionData.h"
#include "Collision/ContactFilter.h"
#include "Collision/AABBCollisionCallbacks.h"
#include "Collision/Raycast2DCallback.h"
#include "Filters/PhysicsFilters.h"

namespace Kross
{
    typedef b2ParticleSystem        ParticleSystem;
    typedef b2ParticleSystemDef     ParticleSystemDef;
    typedef b2ParticleFlag          ParticleFlag;
    typedef b2ParticleGroupFlag     ParticleGroupFlag;
    typedef b2ParticleDef           ParticleDef;
    typedef b2ParticleGroupDef      ParticleGroupDef;
    typedef b2Fixture               Fixture;
    typedef b2FixtureDef            FixtureDef;
    typedef b2PolygonShape          PolygonShape;
    typedef b2CircleShape           CircleShape;
    typedef b2World                 World;
    typedef b2Body                  Body;
    typedef b2Transform             Transform;
    typedef b2BodyType              BodyType;
    typedef b2BodyDef               BodyDef;

    class KROSS_API Physics
    {
    private:
        //static b2RayCastInput input;

        static Physics* m_Instance;

        Body* p_Body;

        Vector2 m_IntersectionNormal;

        RaycastData* p_RayData;
        CollisionData* p_CollisionData;

        /* Call Backs. */
        Raycast2DCallback* p_RayCallback;
        AABBCollisionCallback* p_AABBCollisionCallback;

        Physics() :
            p_Body                  (nullptr),
            m_IntersectionNormal    (Vector2(0.0f)),
            p_RayData               (KROSS_NEW RaycastData()),
            p_RayCallback           (KROSS_NEW Raycast2DCallback()),
            p_CollisionData         (KROSS_NEW CollisionData()),
            p_AABBCollisionCallback (KROSS_NEW AABBCollisionCallback())
        {};
        ~Physics();

    protected:
        friend class Application;

        // Creates the Instance of the Physics Manager.
        static void OnCreate();

        // Destroys the Instance of the Physics Manager.
        static void OnDestroy();

    public:

        static RaycastData* OnRayCast(Vector2 pos, Vector2 direction, Body* body,
            float max);

        static RaycastData* OnCircleCast(Vector2 pos, Vector2 direction, Body* body, float max, float radius);

        // Gets the Fluid Collision Callback.
        static AABBCollisionCallback* GetAABBCollisionCallback() { return m_Instance->p_AABBCollisionCallback; };
    };
}