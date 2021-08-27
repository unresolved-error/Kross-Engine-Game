/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch.
 */

#pragma once

#include "../Core.h"

#include "Renderer.h"
#include "../Physics/PhysicsScene.h"

namespace Kross
{
	class KROSS_API RopeAvatar : public Renderer
	{
	private:
		std::vector<Vector2> m_BasePositions;
		//std::vector<RopeSegments*> m_Segments;

		Body* m_StartBody;
		Body* m_EndBody;

		/* Both for the Objects that gent connected to the Rope. */

		Body* m_StartBodyConnectedBody;
		Body* m_EndBodyConnectedBody;

		float m_ChainLinkLength;

		bool m_IsBreakable;
		bool m_IsStartStatic;

		/* Joins between Segments. */
		std::vector<b2RevoluteJoint*> m_RevolutionJoints;

		b2WeldJoint* m_StartWeld;
		b2WeldJoint* m_EndWeld;

		PhysicsScene* m_PhysicsScene;

	protected:
		friend class Object;

		/*!
			Sets the Physics Scene.
		*/
		void SetPhyicsScene(PhysicsScene* scene) { m_PhysicsScene = scene; };

		/*!
			Gets the Physics Scene.
		*/
		PhysicsScene* GetPhysicsScene() const { return m_PhysicsScene; };

	public:
		RopeAvatar() :
			m_BasePositions				(std::vector<Vector2>()),
			m_StartBody					(nullptr),
			m_EndBody					(nullptr),
			m_StartBodyConnectedBody	(nullptr),
			m_EndBodyConnectedBody		(nullptr),
			m_ChainLinkLength			(0.1f),
			m_IsBreakable				(false),
			m_IsStartStatic				(false),
			m_RevolutionJoints			(std::vector<b2RevoluteJoint*>()),
			m_StartWeld					(nullptr),
			m_EndWeld					(nullptr),
			m_PhysicsScene				(nullptr)
		{};
		~RopeAvatar() {};

		/*!
			Spawns the Rope.
		*/
		void SpawnRope() {};

		/*!
			Sets the Start's Connected Body.
		*/
		void ConnectBodyToStart(Rigidbody2D* rigidbody) { m_StartBodyConnectedBody = rigidbody->GetBody(); };

		/*!
			Sets the End's Connected Body.
		*/
		void ConnectBodyToEnd(Rigidbody2D* rigidbody) { m_EndBodyConnectedBody = rigidbody->GetBody(); };

		/*!
			Gets the Start's Connected Body.
		*/
		Body* GetRopeStartConnectedBody() const { return m_StartBodyConnectedBody; };

		/*!
			Gets the End's Connected Body.
		*/
		Body* GetRopeEndConnectedBody() const { return m_EndBodyConnectedBody; };

		void SetChainLinkLength(float length) { m_ChainLinkLength = length; };

		float GetChainLinkLength() const { return m_ChainLinkLength; };

		void SetBreakable(bool value) { m_IsBreakable = value; };

		bool IsBreakable() const { return m_IsBreakable; };

		void SetStartStatic(bool value) { m_IsStartStatic = value; };

		bool IsStartStatic() const { return m_IsStartStatic; };

		void AttachPosition(Vector2 position) { m_BasePositions.push_back(position); };

		void DetachPosition(int index);

		std::vector<Vector2> GetBasePositions() const { return m_BasePositions; };
	};
}