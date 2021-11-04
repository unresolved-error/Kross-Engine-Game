/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *      - Deklyn Palmer.
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
        
        UpdateMotorSpeed(0.0f);
        UpdateMaxMotorTorque(1000.0f);
    }

    void Cog::ConnectStaticBody()
    {
        Object* objToAttToStart = SceneManager::GetScene()->FindObject(m_nameOfStaticObjConnected);
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
            jointDef.bodyB = m_GameObject->GetComponent<Rigidbody2D>()->GetBody();
            jointDef.bodyA = m_StaticBodyConnectedBody->GetBody();
            jointDef.localAnchorA.Set(0.0f, 0.0f); //Dead center of both.
            jointDef.localAnchorB.Set(0.0f, 0.0f);
            // jointDef.enableLimit = true;
            // jointDef.lowerAngle = -4.71239; //LOCKS AT 270 degrees as limit. Will only rotate 270 either direction.
            // jointDef.upperAngle = 4.71239;
            
            m_MotorJoint = (b2RevoluteJoint*)m_PhysicsScene->GetPhysicsWorld()->CreateJoint(&jointDef);
            m_MotorJoint->SetMaxMotorTorque(m_MaxMotorTorque);
            fullInit = true;

            m_MotorJoint->EnableMotor(true);
          
            
        }
        
        if (m_MotorJoint->GetJointAngle() > 4.71239 || m_MotorJoint->GetJointAngle() < -4.71239)
        {
            m_RotationComplete = true;

            m_MotorJoint->EnableLimit(true);
            float currentAngle = m_MotorJoint->GetJointAngle();
            m_MotorJoint->SetLimits(currentAngle, currentAngle);
            m_MotorJoint->EnableMotor(false);
        }

        if (!m_RotationComplete && m_MotorTrigger)
        { 
            UpdateMotorSpeed(-1.0f); 
        }

        m_MotorJoint->SetMotorSpeed(m_MotorSpeed);
        m_MotorJoint->SetMaxMotorTorque(m_MaxMotorTorque);

    }

	void Cog::UpdateMotorSpeed(float newSpeed)
	{
        m_MotorSpeed = newSpeed;
	}

    void Cog::TriggerMotor() 
    {
        m_MotorTrigger = true;
    }

	void Cog::UpdateMaxMotorTorque(float newTorque)
	{
        m_MaxMotorTorque = newTorque;
	}

	void Cog::SpawnCog()
    {
        //Begin Rotator
        
        Collider* cogCollider = m_GameObject->GetComponent<Collider>();
        cogCollider->SetShapeType(ShapeType::Circle);
        cogCollider->SetRadius(0.5f);
        cogCollider->SetStatic(false);

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