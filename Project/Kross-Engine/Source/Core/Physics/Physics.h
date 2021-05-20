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
#include "Collision/CollisionData.h"
#include "Collision/ContactFilter.h"
#include "Collision/PhysicsCallbacks.h"
#include "Collision/Raycast2DCallback.h"

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

    class KROSS_API LineRenderer;

    class KROSS_API Physics
    {
    private:
        //static b2RayCastInput input;

        static Body* p_Body;

        static Vector2 m_IntersectionNormal;

        static LineRenderer* p_Lines;

        static Physics* p_Instance;
        static RaycastData* p_RayData;
        static Raycast2DCallback* p_RayCallback;
        static CollisionData* p_CollisionData;

        Physics() {};
        ~Physics();

    protected:
        friend class Application;

        // Creates the Instance of the Physics Manager.
        static void OnCreate();

        // Destroys the Instance of the Physics Manager.
        static void OnDestroy();

    public:
        static RaycastData* OnRayCast(Vector2 pos, Vector2 direction, Body* body,
            float max, LineRenderer* lines = nullptr);
    };


}