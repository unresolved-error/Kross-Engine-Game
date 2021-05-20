/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
 */
#pragma once

#include "../Core.h"

#include "Renderer.h"
#include "../Physics/PhysicsScene.h"

#include "../Renderer/Shader/Shader.h"
#include "../Renderer/LineRenderer.h"
#include "../Physics/Collision/CollisionData.h"

namespace Kross
{
    class KROSS_API Shape;
    class KROSS_API Object;

    enum class KROSS_API CollisionState
    {
        None,
        Enter,
        Stay,
        Exit,
    };

    enum KROSS_API ColliderFilters
    {
        Default = 0x0000,
        Player = 0x0001,
        Environment = 0x0002,
        Fluid = 0x0004,
        BackGround = 0x0008,
        Light = 0x0010,
    };


    class KROSS_API Rigidbody2D : public Renderer
    {
    private:
        Box* p_Box;
        Circle* p_Circle;
        Body* p_Body;
        PhysicsScene* p_PhysicsScene;
        RaycastData* p_RayData;

        FixtureDef* p_FixtureDef;
        b2MassData* p_MassData;

        CollisionState m_CollisionState;

        #ifdef KROSS_DEBUG
        Shader* p_DebugShader;
        LineRenderer* lines;
        #endif

        ShapeType m_ShapeType;

    protected:
        friend class PhysicsScene;
        friend class Scene;

        /* Rigidbody2D start method */
        void OnStart() override;

        /* Rigidbody2D update method */
        void OnUpdate() override;

        /* The RigidBody outlines will only render in debug */
        #ifdef KROSS_DEBUG
        void OnRender() override;
        #endif

        Body* GetRayCollisionBody() const { return p_RayData->body; };

    public:

        Rigidbody2D();
        ~Rigidbody2D();

        /* Sets the mass and only the mass of the body */
        void SetMass(float mass)
        {
            /* A new mass data is created */
            /* The mass data variables are set */
            p_MassData->mass = mass;
            p_MassData->center = { 0, 0 };
            p_MassData->I = 0.0f;
        }

        /* Sets the physics scene */
        void SetPhysicsScene(PhysicsScene* scene) { p_PhysicsScene = scene; }
        /* Gets the physics scene */
        PhysicsScene* GetPhysicsScene() const { return p_PhysicsScene; }

        /* Sets the Body for the RigidBody */
        void SetBody(Body* body) { p_Body = body; }
        /* Gets the Body for the RigidBody */
        Body* GetBody() const { return p_Body; }

        /* Apply a force to the body */
        void OnApplyForce(Vector2 force);
        /* Apply an impulse to the body */
        void OnApplyImpulse(Vector2 impulse);

        /* Creates a new dynamic circle */
        void CreateDynamicCircle(float radius, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits);
        void CreateDynamicCircle(float radius, float friction, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits);
        /* Creates a new dynamic box */
        void CreateDynamicBox(Vector2 Dimensions, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits);
        void CreateDynamicBox(Vector2 Dimensions, float friction, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits);

        /* Creates a new static circle */
        void CreateWorldCircle(float radius, Vector2 pos, uint16 categoryBits, uint16 maskBits);
        void CreateWorldCircle(float radius, float friction, Vector2 pos, uint16 categoryBits, uint16 maskBits);
        /* Creates a new static box */
        void CreateWorldBox(Vector2 Dimensions, Vector2 pos, uint16 categoryBits, uint16 maskBits);
        void CreateWorldBox(Vector2 Dimensions, float friction, Vector2 pos, uint16 categoryBits, uint16 maskBits);

        /* Gets the Objects Position */
        Vector2 GetPosition() const;
        /* Gets the Objects velocity */
        Vector2 GetVelocity() const{ return Vector2(p_Body->GetLinearVelocity().x , p_Body->GetLinearVelocity().y); }

        /* Gets the friction of a specified object */
        float GetFriction();

        Vector2 SpringCalculation(Body* body1, Body* body2, float distance);

        Vector2 SpringUpdate(Vector2 force, float mass);

        CollisionState GetCollision() const { return m_CollisionState; }    
    };
}