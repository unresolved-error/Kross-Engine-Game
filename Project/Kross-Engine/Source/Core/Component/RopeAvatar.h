/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch.
 */

#pragma once

#include "../Core.h"

#include "Renderer.h"
#include "../Physics/Rope/RopeSegment.h"
#include "../Renderer/LineRenderer.h"

namespace Kross
{
	class KROSS_API RopeAvatar : public Renderer
	{
	private:
		std::vector<Vector2> m_BasePositions;
		std::vector<RopeSegment*> m_Segments;

		Vector2 m_AttachmentPointOnStartObj;
		Vector2 m_AttachmentPointOnEndObj;


		Body* m_StartAnchorBody;
		Body* m_EndAnchorBody;

		/* Both for the Objects that get connected to the Rope. */
		std::string m_nameOfStartObjConnected;
		std::string m_nameOfEndObjConnected;

		Rigidbody2D* m_StartBodyConnectedBody;
		Rigidbody2D* m_EndBodyConnectedBody;

		float m_ChainLinkLength;

		bool m_IsBreakable;
		bool m_IsStartStatic;

		/* Joints between Segments. */
		std::vector<b2RevoluteJoint*> m_RevolutionJoints;

		b2RevoluteJoint* m_StartWeld;
		b2RevoluteJoint* m_EndWeld;

		PhysicsScene* m_PhysicsScene;

		LineRenderer* m_DebugRenderer;

	protected:
		friend class Object;
		friend class Scene;

		/* Friend classing Batch. */
		template<typename Type> friend class Batch;

		void OnStart() override;

		void OnUpdate() override;

		void OnUpdateDrawInformation();

		void SetDebugRenderer(LineRenderer* renderer) { m_DebugRenderer = renderer; };

		/*!
			Sets the Physics Scene.
		*/
		void SetPhysicsScene(PhysicsScene* scene) { m_PhysicsScene = scene; };

		/*!
			Gets the Physics Scene.
		*/
		PhysicsScene* GetPhysicsScene() const { return m_PhysicsScene; };

	public:
		RopeAvatar() :
			m_BasePositions				(std::vector<Vector2>()),
			m_StartAnchorBody			(nullptr),
			m_EndAnchorBody				(nullptr),
			m_StartBodyConnectedBody	(nullptr),
			m_EndBodyConnectedBody		(nullptr),
			m_ChainLinkLength			(0.1f),
			m_IsBreakable				(false),
			m_IsStartStatic				(false),
			m_RevolutionJoints			(std::vector<b2RevoluteJoint*>()),
			m_StartWeld					(nullptr),
			m_EndWeld					(nullptr),
			m_nameOfStartObjConnected   ("*"),
			m_nameOfEndObjConnected		("*"),
			m_PhysicsScene				(nullptr),
			m_DebugRenderer             (nullptr),
			m_AttachmentPointOnStartObj (0,0),
			m_AttachmentPointOnEndObj	(0,0)

		{
			SetDepth(-2);
		};
		~RopeAvatar() {};

		/*!
			Spawns the Rope.
		*/
		void SpawnRope();

		/*!
			Sets the Start's Connected Body.
		*/
		void ConnectBodyToStart();

		/*!
			Sets the End's Connected Body.
		*/
		void ConnectBodyToEnd();

		/*!
			Gets the Start's Connected Body.
		*/
		Rigidbody2D* GetRopeStartConnectedBody() const { return m_StartBodyConnectedBody; };

		/*!
			Gets the End's Connected Body.
		*/
		Rigidbody2D* GetRopeEndConnectedBody() const { return m_EndBodyConnectedBody; };

		void SetChainLinkLength(float length) { m_ChainLinkLength = length; };

		float GetChainLinkLength() const { return m_ChainLinkLength; };

		void SetBreakable(bool value) { m_IsBreakable = value; };

		bool IsBreakable() const { return m_IsBreakable; };

		void SetStartStatic(bool value) { m_IsStartStatic = value; };

		bool IsStartStatic() const { return m_IsStartStatic; };

		void AttachPosition(Vector2 position) { m_BasePositions.push_back(position); };

		void DetachPosition(int index);
		
		void SetBasePosition(int index, Vector2 newPos);

		void SetStartReserveName(std::string name);
		void SetAttachmentPointOnStartObj(Vector2 attachPoint);
		void SetEndReserveName(std::string name);
		void SetAttachmentPointOnEndObj(Vector2 attachPoint);
		std::string GetStartReserveName();
		Vector2 GetAttachmentPointOnStartObj();
		std::string GetEndReserveName();
		Vector2 GetAttachmentPointOnEndObj();

		std::vector<Vector2> GetBasePositions() const { return m_BasePositions; };
	};
}