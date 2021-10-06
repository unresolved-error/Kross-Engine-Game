/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include "Cog.h"
#include "../Object.h"
#include "../Manager/SceneManager.h"


namespace Kross
{
    void Cog::OnStart()
    {
        ConnectStaticBody();
        if (m_nameOfStaticObjConnected == "*") 
        { return; }
        SpawnCog();



    }

    void Cog::ConnectStaticBody()
    {
        Object* objToAttToStart = SceneManager::GetCurrentScene()->FindObject(m_nameOfStaticObjConnected);
        if (objToAttToStart)
        {
            Rigidbody2D* rigidToAttToCog = objToAttToStart->GetComponent<Rigidbody2D>();

            m_StaticBodyConnectedBody = rigidToAttToCog;


        }
    }

    std::string Cog::GetStartReserveName()
    {
        return m_nameOfStaticObjConnected;
    }

    void Cog::SetStartReserveName(std::string name)
    {
       
        m_nameOfStaticObjConnected = name;
        
    }


    void Cog::OnUpdate()
    {
        if (!fullInit) 
        {
            b2RevoluteJointDef jointDef = b2RevoluteJointDef();
            jointDef.bodyA = m_GameObject->GetComponent<Rigidbody2D>()->GetBody();
            jointDef.bodyB = m_StaticBodyConnectedBody->GetBody();
            jointDef.localAnchorA.Set(0.0f, 0.0f); //Dead center of both.
            jointDef.localAnchorB.Set(0.0f, 0.0f);
            
            m_MotorJoint = (b2RevoluteJoint*)m_PhysicsScene->GetPhysicsWorld()->CreateJoint(&jointDef);
            m_MotorJoint->SetMaxMotorTorque(m_MaxMotorTorque);
            fullInit = true;
            
            
        }
        
    }

	void Cog::SetMotorSpeed(float newSpeed)
	{
        m_MotorSpeed = newSpeed;
	}

	void Cog::SetMaxMotorTorque(float newTorque)
	{
        m_MaxMotorTorque = newTorque;
	}

	void Cog::SpawnCog()
    {
        //Begin Rotator
        
        Collider* cogCollider = m_GameObject->GetComponent<Collider>();
        cogCollider->SetShapeType(ShapeType::Circle);
        cogCollider->SetRadius(0.1f);
        cogCollider->SetStatic(false);
        
        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.fixedRotation = false;
        bodyDef.userData = m_GameObject;

        Body* body = m_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        CircleShape circle;
        circle.m_radius = 0.1f;

        FixtureDef fixtureDef;
        fixtureDef.shape = &circle;
        fixtureDef.density = 1.0f;
        //fixtureDef.filter.categoryBits = 
        //fixtureDef.filter.maskBits = 

        body->CreateFixture(&fixtureDef);

        //NOW START STATIC COMPONENT.
        if (m_nameOfStaticObjConnected == "*")
        {
            return;
        }

    }

    

    void Cog::StartRotation()
    {
        m_MotorJoint->SetMotorSpeed(m_MotorSpeed);
        m_MotorJoint->EnableMotor(true);


        /*
            NOTE: I HAVE NO IDEA HOW TORQUE IS USED IN BOX2D AT TIME OF WRITING. 
            THIS MAY NEED TO BE LARGER, SMALLER, OR FINE AS IS.
            PLEASE TEST.
            THIS COULD BE IN WEIGHT LIFTED, OR AS A PERCENTAGE OF MAXIMUM FORCE.
        */
    }
}