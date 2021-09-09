/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch.
 */

#include "RopeAvatar.h"

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
		for (int i = 0; i < m_Segments.size(); i++)
		{
			m_DebugRenderer->DrawRigidBody(m_Segments[i]->GetBody());
		}
	}

	void RopeAvatar::SpawnRope()
	{
		/* If the Physics Scene doesn't Exist, early out. */
		if (!m_PhysicsScene)
		{
			return;
		}

		/* Start Connection = KROSS_NEW Body()... etc positions.set etc.*/
		/* End Connection = KROSS_NEW Body()... etc positions.set etc.*/

		for (int i = 0; i < m_BasePositions.size() - 1; i++)
		{
			int nextOneAcross = i + 1;

			Vector2 positionA = m_BasePositions[i];
			Vector2 positionB = m_BasePositions[nextOneAcross];

			float totalDistance = glm::length(positionA - positionB);

			int numberOfSegments = (int)fmod(totalDistance, m_ChainLinkLength);

			/* Step 2, Generate the Bodies. between the ropes. */
			for (int j = 0; j < numberOfSegments; j++)
			{
				Vector2 bodyPosition = Math::Lerp(positionA, positionB, j * (int)(1.0f / (float)(numberOfSegments - 1)));

				BodyDef bodyDef;
				bodyDef.type = b2_dynamicBody;
				bodyDef.position.Set(bodyPosition.x, bodyPosition.y);

				Body* body = m_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

				CircleShape circle;
				circle.m_radius = m_ChainLinkLength * 0.5f;

				FixtureDef fixtureDef;
				fixtureDef.shape = &circle;
				//fixtureDef.filter.categoryBits = 
				//fixtureDef.filter.maskBits = 

				body->CreateFixture(&fixtureDef);

				RopeSegment* newRopeSegment = KROSS_NEW RopeSegment();
				newRopeSegment->SetBody(body);

				m_Segments.push_back(newRopeSegment);

				m_PhysicsScene->AttachBody(body);
			}
		}

		/* Generate a list of Revolute Joints. */
		for (int i = 0; i < m_Segments.size() - 1; i++) /* See what happens. */
		{
			b2RevoluteJointDef* jointDef = KROSS_NEW b2RevoluteJointDef();

			int nextOneAcross = i + 1;

			jointDef->bodyA = m_Segments[i]->GetBody();
			jointDef->bodyB = m_Segments[nextOneAcross]->GetBody();

			jointDef->localAnchorA = b2Vec2(0, -1); /* See if this Explodes. */
			jointDef->localAnchorB = b2Vec2(0, 1);

			m_RevolutionJoints.push_back((b2RevoluteJoint*)jointDef);
		}

		/* Step 4 Generate the end two b2 Weld Joints. */
		//if (m_IsStartStatic)
		//{
		//
		//}
	}

	void RopeAvatar::DetachPosition(int index)
	{
		if (index < 0 || index >= m_BasePositions.size())
			return;

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
	void RopeAvatar::SetEndReserveName(std::string name)
	{
		m_nameOfEndObjConnected = name;
	}
	std::string RopeAvatar::GetStartReserveName()
	{
		return m_nameOfStartObjConnected;
	}
	std::string RopeAvatar::GetEndReserveName()
	{

		return m_nameOfEndObjConnected;
	}
}
