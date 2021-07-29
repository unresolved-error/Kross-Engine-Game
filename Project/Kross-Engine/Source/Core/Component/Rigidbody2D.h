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
#include "../Physics/Data/CollisionData.h"
#include "../Physics/Collision/ContactFilter.h"
#include "../Physics/Shape/Shape.h"
#include "../Physics/PlayerState.h"
#include "../Renderer/Tilemap/Tile.h"
#include "../Renderer/Tilemap/TileSet.h"
#include "../Renderer/Tilemap/TileMap.h"
#include "../Physics/Filters/CollisionFilter.h"

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
        Light = 0x0010
    };


    class KROSS_API Rigidbody2D : public Renderer
    {
    private:
        Body* p_Body;
        PhysicsScene* p_PhysicsScene;
        Box* p_Box;
        Capsule* p_Capsule;
        Circle* p_Circle;

        LineRenderer* p_DebugRenderer;

        ShapeType m_ShapeType;
        CollisionState m_CollisionState;
        PlayerState m_PlayerState;

        FixtureDef* p_FixtureDef;
        b2MassData* p_MassData;
        RaycastData* p_RayData;
        ContactFilter* p_Filter;
        AABBCollisionData* p_AABBCollisionData;

        List<AABBCollisionData*> m_AABBCollisions;
        List<Body*> m_CloseObjects;
        List<Body*> m_TileColliders;
        List<Box*> m_TileShapes;
        List<Circle*> m_TileCornerShapes;
        List<FixtureDef*> m_Fixtures;

    protected:
        friend class TileMapRenderer;
        friend class PhysicsScene;
        friend class Scene;

        /* Rigidbody2D start method */
        void OnStart() override;

        /* Rigidbody2D update method */
        void OnUpdate() override;

        // Sends Draw Informatin to the Line Renderer.
        void OnUpdateDrawInformation();

        // Attaches a Line Renderer.
        void AttachLineRenderer(LineRenderer* renderer) { p_DebugRenderer = renderer; };

        Body* GetRayCollisionBody() const { return p_RayData->body; }

        /* Sets the physics scene */
        void SetPhysicsScene(PhysicsScene* scene) { p_PhysicsScene = scene; }

        /* Gets the physics scene */
        PhysicsScene* GetPhysicsScene() const { return p_PhysicsScene; }

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


        /* Sets the Body for the RigidBody */
        void SetBody(Body* body) { p_Body = body; }

        /* Gets the Body for the RigidBody */
        Body* GetBody() const { return p_Body; }


        /* Apply a force to the body */
        void OnApplyForce(Vector2 force);

        /* Apply an impulse to the body */
        void OnApplyImpulse(Vector2 impulse);


        /* Creates a new dynamic circle */
        void CreateDynamicCircle(float radius, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits, float friction = 0.5f);

        /* Creates a new dynamic box */
        void CreateDynamicBox(Vector2 dimensions, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits, float friction = 0.5f);

        void CreateDynamicCapsule(Vector2 dimensions, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits, float friction = 0.5f);

        /* Creates a new static circle */
        void CreateWorldCircle(float radius, Vector2 pos, uint16 categoryBits, uint16 maskBits, float friction = 0.5f);

        /* Creates a new static box */
        void CreateWorldBox(Vector2 dimensions, Vector2 pos, uint16 categoryBits, uint16 maskBits, float friction = 0.5f);

        /* Gets the Objects Position */
        Vector2 GetPosition() const;

        /* Gets the Objects velocity */
        Vector2 GetVelocity() const{ return Vector2(p_Body->GetLinearVelocity().x , p_Body->GetLinearVelocity().y); }


        /* Gets the friction of a specified object */
        float GetFriction();

        void SetCollisionState(CollisionState state) { m_CollisionState = state; }
        CollisionState GetCollisionState() { return m_CollisionState; }

        void SetPlayerState(PlayerState state) { m_PlayerState = state; }
        PlayerState GetPlayerState() { return m_PlayerState; }

        /* Calculates the spring under the player */
        Vector2 SpringCalculation(Body* body1, Body* body2, float distance);


        /* Returns the current collision state */
        CollisionState GetCollision() const { return m_CollisionState; }

        /* Collides dynamic bodies with particles */
        Vector2 CollideParticles();


        float CalculateRayLength(float maxFraction, Vector2 direction, Vector2 pos);
    
        float CalculateCircleCast(float circleCastRadius, float maxFraction, Vector2 direction, Vector2 pos);

        void GetSurroundingObjects(float size, Body* body);

        void CreateTileMapColliders(TileMap* tileMap, Tile* tile, float friction = 0.5f);

        void DeleteTileMapColliders();

        /* Gets whatever is bellow the body */
        /* When calling on a circle the length must not be larger than the radius */
        /* Otherwise the length will default to the radius */
        /* When calling on a box direction must only be on one axis */
        void GetObjectsInDirection(float length, Body* body, Vector2 direction);

        /* Checks for the players current state */
        void CheckPlayerState();
    };
}
