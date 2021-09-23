/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#include "Cog.h"
#include "../Manager/SceneManager.h"


namespace Kross
{
    void Cog::OnStart()
    {

        SpawnCog();
        m_MotorJoint->SetMaxMotorTorque(m_MaxMotorTorque);

    }

    void Cog::OnUpdate()
    {
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
        Object* cogAnchor = Object::OnCreate("cogAnchor");
        m_StaticBody = cogAnchor->AttachComponent<Rigidbody2D>();
        Collider* cogCollider = cogAnchor->GetComponent<Collider>();
        cogCollider->SetShapeType(ShapeType::Circle);
        cogCollider->SetRadius(0.1f);
        cogCollider->SetStatic(true);
        SceneManager::GetCurrentScene()->AttachObject(cogAnchor, true);

        //Anchor complete. Begin actual rotator:
        
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

        CogRotationPiece* newCogPiece = KROSS_NEW CogRotationPiece();
        newCogPiece->SetBody(body);
        m_PhysicsScene->AttachBody(body);

        //Whew boy. Lotta garbage there. Connect the bits together now.
        b2RevoluteJointDef jointDef = b2RevoluteJointDef();
        jointDef.bodyA = cogAnchor->GetComponent<Rigidbody2D>()->GetBody();
        jointDef.bodyB = newCogPiece->GetBody();

        jointDef.localAnchorA.Set(0.0f, 0.0f); //Dead center of both.
        jointDef.localAnchorB.Set(0.0f, 0.0f);
        

        m_MotorJoint = (b2RevoluteJoint*)m_PhysicsScene->GetPhysicsWorld()->CreateJoint(&jointDef);
        
        
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