/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#pragma once

#include "../Core.h"
#include "../Physics/Cog/CogRotationPiece.h"
#include "Renderer.h"

namespace Kross
{
    class KROSS_API Cog : public Renderer
    {
    private:

        Rigidbody2D* m_StaticBody;
        Rigidbody2D* m_RotatingBody;

        CogRotationPiece* m_RotationPiece;

        PhysicsScene* m_PhysicsScene;

        b2RevoluteJoint* m_MotorJoint;

        float m_MaxMotorTorque = 0.0f;
        float m_MotorSpeed = 0.0f;

    protected:
        friend class Object;
        friend class Scene;

        
        void OnStart() override;

        void OnUpdate() override;

        /*!
            Sets the Physics Scene.
        */
        void SetPhysicsScene(PhysicsScene* scene) { m_PhysicsScene = scene; };

        /*!
            Gets the Physics Scene.
        */
        PhysicsScene* GetPhysicsScene() const { return m_PhysicsScene; };

    public:
        Cog() :
            m_PhysicsScene(nullptr),
            m_StaticBody(nullptr),
            m_RotatingBody(nullptr),
            m_MotorJoint(nullptr),
            m_RotationPiece(nullptr)
        {};
        ~Cog() {};

        void SetMotorSpeed(float newSpeed);

        void SetMaxMotorTorque(float newTorque);


        float GetMotorSpeed() { return m_MotorSpeed; };

        float GetMaxMotorTorque() { return m_MaxMotorTorque; };


        void SpawnCog();

        void StartRotation();





    };
}