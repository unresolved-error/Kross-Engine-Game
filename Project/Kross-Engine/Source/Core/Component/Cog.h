/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#pragma once

#include "../Core.h"

#include "Renderer.h"

namespace Kross
{
    class KROSS_API Cog : public Renderer
    {
    private:
        bool fullInit = false;

        Rigidbody2D* m_StaticBody;
        Rigidbody2D* m_RotatingBody;
        
        std::string m_nameOfStaticObjConnected = "*";
        Rigidbody2D* m_StaticBodyConnectedBody = nullptr;


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
            m_MotorJoint(nullptr)
        {};
        ~Cog() {};

        void UpdateMotorSpeed(float newSpeed);

        void UpdateMaxMotorTorque(float newTorque);


        float GetMotorSpeed() { return m_MotorSpeed; };

        float GetMaxMotorTorque() { return m_MaxMotorTorque; };
        
        Rigidbody2D* GetRopeStartConnectedBody() const { return m_StaticBodyConnectedBody; };

        void SpawnCog();

        void StartRotation();

        void ConnectStaticBody();

        std::string GetStartReserveName();
        void SetStartReserveName(std::string name);

    };
}