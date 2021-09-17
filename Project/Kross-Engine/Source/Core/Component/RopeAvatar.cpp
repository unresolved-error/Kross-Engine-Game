/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch.
 */

#include "RopeAvatar.h"
#include "../Manager/SceneManager.h"

namespace Kross
{
	void RopeAvatar::OnStart()
	{
		#ifndef KROSS_EDITOR
		SpawnRope();
		#endif
	}

	void RopeAvatar::OnUpdate()
	{
		#ifdef KROSS_DEBUG
		OnUpdateDrawInformation();
		#endif
	}

	void RopeAvatar::OnUpdateDrawInformation()
	{
#ifndef KROSS_EDITOR
		for (int i = 0; i < m_Segments.size() - 1; i++)
		{
			m_DebugRenderer->DrawLineSegment(m_Segments[i]->GetPosition(), m_Segments[i + 1]->GetPosition(), Vector3(1.0f, 0.0f, 1.0f));
			m_DebugRenderer->DrawRigidBody(m_Segments[i]->GetBody());

		}
#else
		for (int i = 1; i < m_BasePositions.size(); i++)
		{
			m_DebugRenderer->DrawLineSegment(m_BasePositions[i - 1], m_BasePositions[i], Vector3(1.0f, 0.0f, 0.f));
		}
#endif
	}

	void RopeAvatar::SpawnRope()
	{
		/* If the Physics Scene doesn't Exist, early out. */
		if (!m_PhysicsScene)
		{
			return;
		}

		/* Grab the Objects Loaded in. */
		ConnectBodyToStart();
		ConnectBodyToEnd();

		/* Start Connection = KROSS_NEW Body()... etc positions.set etc.*/
		/* End Connection = KROSS_NEW Body()... etc positions.set etc.*/

		for (int i = 0; i < m_BasePositions.size() - 1; i++)
		{
			int nextOneAcross = i + 1;

			Vector2 positionA = m_BasePositions[i];
			Vector2 positionB = m_BasePositions[nextOneAcross];

			float totalDistance = glm::length(positionA - positionB);

			int numberOfSegments = (int)(totalDistance / m_ChainLinkLength);

			/* Step 2, Generate the Bodies. between the ropes. */
			for (int j = 0; j < numberOfSegments; j++)
			{
				Vector2 bodyPosition = Math::Lerp(positionA, positionB, ((float)j / (float)numberOfSegments));

				BodyDef bodyDef;
				bodyDef.type = b2_dynamicBody;
				bodyDef.position.Set(bodyPosition.x, bodyPosition.y);
				bodyDef.fixedRotation = false;
				bodyDef.userData = m_GameObject;

				Body* body = m_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

				CircleShape circle;
				circle.m_radius = m_ChainLinkLength * 0.5f;

				FixtureDef fixtureDef;
				fixtureDef.shape = &circle;
				fixtureDef.density = 1.0f;
				//fixtureDef.filter.categoryBits = NEED TO BE SET TO NOT INCLUDE PLAYERS.
				//fixtureDef.filter.maskBits = 

				body->CreateFixture(&fixtureDef);

				RopeSegment* newRopeSegment = KROSS_NEW RopeSegment();
				newRopeSegment->SetBody(body);

				m_Segments.push_back(newRopeSegment);

				m_PhysicsScene->AttachBody(body);
			}
		}

		/* Generate a list of Revolute Joints. */
		for (int i = 0; i < m_Segments.size() - 1; i++) 
		{
			b2RevoluteJointDef jointDef = b2RevoluteJointDef();

			int nextOneAcross = i + 1;

			jointDef.bodyA = m_Segments[i]->GetBody();
			jointDef.bodyB = m_Segments[nextOneAcross]->GetBody();

			Vector2 bodyAPos = m_Segments[i]->GetPosition();
			Vector2 bodyBPos = m_Segments[nextOneAcross]->GetPosition();

			jointDef.localAnchorA.Set( m_ChainLinkLength * 0.5f, 0.0f); 
			jointDef.localAnchorB.Set(-m_ChainLinkLength * 0.5f, 0.0f);

			jointDef.collideConnected = false;

			m_RevolutionJoints.push_back((b2RevoluteJoint*)m_PhysicsScene->GetPhysicsWorld()->CreateJoint(&jointDef));

			
		}

		/* Step 4 Generate the end two b2 Weld Joints. */
		//First manage start being static
		if (m_IsStartStatic)
		{
			Object* ropeAnchor = Object::OnCreate("StartAnchor");
			ropeAnchor->m_Transform->m_Position = m_BasePositions[0];
			m_StartBodyConnectedBody = ropeAnchor->AttachComponent<Rigidbody2D>();
			Collider* anchorCollider = ropeAnchor->GetComponent<Collider>();
			anchorCollider->SetShapeType(ShapeType::Circle);
			anchorCollider->SetRadius(m_ChainLinkLength * 0.5f);
			anchorCollider->SetStatic(true);
			SceneManager::GetCurrentScene()->AttachObject(ropeAnchor, true);
		}
		//Then use the end and start to generate last links.
		if (m_StartBodyConnectedBody) 
		{
			b2RevoluteJointDef firstJointDef = b2RevoluteJointDef();
			firstJointDef.bodyA = m_StartBodyConnectedBody->GetBody();
			firstJointDef.bodyB = m_Segments[0]->GetBody();
			
			firstJointDef.localAnchorA.Set(m_AttachmentPointOnStartObj.x, m_AttachmentPointOnStartObj.y);
			firstJointDef.localAnchorB.Set(0.0f, 0.0f);

			m_StartWeld = (b2RevoluteJoint*)m_PhysicsScene->GetPhysicsWorld()->CreateJoint(&firstJointDef);
		}

		if (m_EndBodyConnectedBody) 
		{
			b2RevoluteJointDef firstJointDef = b2RevoluteJointDef();
			firstJointDef.bodyA = m_Segments[m_Segments.size() - 1]->GetBody(); 
			firstJointDef.bodyB = m_EndBodyConnectedBody->GetBody();
			firstJointDef.localAnchorA.Set(m_ChainLinkLength * 0.5f, 0.0f); 
			firstJointDef.localAnchorB.Set(m_AttachmentPointOnEndObj.x, m_AttachmentPointOnEndObj.y);

			m_EndWeld = (b2RevoluteJoint*)m_PhysicsScene->GetPhysicsWorld()->CreateJoint(&firstJointDef);
		}

	}

	void RopeAvatar::ConnectBodyToStart()
	{
		Object* objToAttToStart = SceneManager::GetCurrentScene()->FindObject(m_nameOfStartObjConnected);
		if (objToAttToStart) 
		{
			Rigidbody2D* rigidToAttToStart = objToAttToStart->GetComponent<Rigidbody2D>();

			m_StartBodyConnectedBody = rigidToAttToStart;
		}
	}

	void RopeAvatar::ConnectBodyToEnd()
	{
		Object* objToAttToEnd = SceneManager::GetCurrentScene()->FindObject(m_nameOfEndObjConnected);
		if (objToAttToEnd)
		{
			Rigidbody2D* rigidToAttToEnd = objToAttToEnd->GetComponent<Rigidbody2D>();

			m_EndBodyConnectedBody = rigidToAttToEnd;
		}
	}

	void RopeAvatar::DetachPosition(int index)
	{
		if (index < 0 || index >= m_BasePositions.size())
		{
			return;
		}

		m_BasePositions.erase(m_BasePositions.begin() + index);
	}

	void RopeAvatar::SetBasePosition(int index, Vector2 newPos)
	{
		m_BasePositions[index] = newPos;
	}
	void RopeAvatar::SetStartReserveName(std::string name)
	{
		m_nameOfStartObjConnected = name;
	}
	void RopeAvatar::SetAttachmentPointOnStartObj(Vector2 attachPoint)
	{
		m_AttachmentPointOnStartObj = attachPoint;
	}
	void RopeAvatar::SetEndReserveName(std::string name)
	{
		m_nameOfEndObjConnected = name;
	}
	void RopeAvatar::SetAttachmentPointOnEndObj(Vector2 attachPoint)
	{
		m_AttachmentPointOnEndObj = attachPoint;
	}
	std::string RopeAvatar::GetStartReserveName()
	{
		return m_nameOfStartObjConnected;
	}
	Vector2 RopeAvatar::GetAttachmentPointOnStartObj()
	{
		return m_AttachmentPointOnStartObj;
	}
	std::string RopeAvatar::GetEndReserveName()
	{
		return m_nameOfEndObjConnected;
	}
	Vector2 RopeAvatar::GetAttachmentPointOnEndObj()
	{
		return m_AttachmentPointOnEndObj;
	}
}
