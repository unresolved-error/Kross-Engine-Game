/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */
#pragma once

#include "../Core.h"

#include "Component.h"
#include "Box2D/Box2D.h"
#include "../Physics/PhysicsScene.h"
#include "SpriteRenderer.h"

namespace Kross
{
    class KROSS_API Shape;

    class KROSS_API Rigidbody2D : public Component
    {
    private:
        Shape* p_Shape;
        b2Body* p_Body;
        b2MassData* p_MassData;
        PhysicsScene* p_PhysicsScene;


        #ifdef KROSS_DEBUG
        Shader* p_DebugShader;
        #endif

        ShapeType m_ShapeType;

        Sprite* p_Sprite = nullptr;
    protected:
        friend class PhysicsScene;


        void OnStart() override;

        void OnUpdate() override;

        #ifdef KROSS_DEBUG
        void OnRender() override;
        #endif

    public:

        Rigidbody2D();
        ~Rigidbody2D();

        void SetPhysicsScene(PhysicsScene* scene) { p_PhysicsScene = scene; }
        PhysicsScene* GetPhysicsScene() const { return p_PhysicsScene; }

        void SetBody(b2Body* body) { p_Body = body; }

        void OnApplyForce(Vector2 force);
        void OnApplyImpulse(Vector2 impulse);

        void CreateDynamicCircle(float radius, Vector2 pos);
        void CreateDynamicBox(Vector2 Dimensions, Vector2 pos);

        void CreateWorldCircle(float radius, Vector2 pos);
        void CreateWorldBox(Vector2 Dimensions, Vector2 pos);
        void SetMass(float mass) { p_MassData->mass = mass; }

        // Gets the Objects Position. 
        Vector2 GetPosition() const;
        Vector2 GetVelocity() const{ return Vector2(p_Body->GetLinearVelocity().x , p_Body->GetLinearVelocity().y); }

        void SetSprite(Sprite* sprite);


        b2Body* GetBody() const { return p_Body; }

    };
}