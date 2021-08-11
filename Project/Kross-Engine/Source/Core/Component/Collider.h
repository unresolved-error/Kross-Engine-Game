/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *		- Chris Deitch.
 */

#pragma once

#include "../Core.h"

#include "Component.h"
#include "../Physics/Filters/ShapeType.h"

namespace Kross
{
	class KROSS_API Collider : public Component
	{
	private:
		ShapeType m_Type;
		float m_Width, m_Height, m_Radius, m_Friction, m_Mass;

		bool m_IsStatic, m_FixedRotation, m_IsTileMap;


	protected:

	public:
		Collider() :
			m_Type				(ShapeType::Box),
			m_Width				(1.0f),
			m_Height			(1.0f),
			m_Radius			(0.5f),
			m_Friction			(0.5f),
			m_Mass				(1.0f),
			m_IsStatic			(false),
			m_FixedRotation		(false),
			m_IsTileMap			(false)
		{};

		~Collider() {};

		// Gets the Type of Shape of the Collider.
		ShapeType GetShapeType() const { return m_Type; };

		// Gets the Width of the Collider.
		float GetWidth() const { return m_Width; };

		// Gets the Height of the Collider.
		float GetHeight() const { return m_Height; };

		// Gets the Radius of the Collider.
		float GetRadius() const { return m_Radius; };

		// Gets the Friction of the Collider.
		float GetFriction() const { return m_Friction; };

		// Gets the Mass of the Collider.
		float GetMass() const { return m_Mass; };

		// Gets if the Collider is Static.
		bool IsStatic() const { return m_IsStatic; };

		// Gets if the Collider is Tile Map Generated.
		bool IsTileMapCollider() const { return m_IsTileMap; };

		// Gets if the Collider is Rotation Locked.
		bool IsRotationLocked() const { return m_FixedRotation; };

		// Sets the Type of Shape of the Collider.
		void SetShapeType(ShapeType type) { m_Type = type; };

		// Sets the Width of the Collider.
		void SetWidth(float width) { m_Width = width; m_Radius = width / 2.0f; };

		// Sets the Height of the Collider.
		void SetHeight(float height) { m_Height = height; };

		// Sets the Radius of the Collider.
		void SetRadius(float radius) { m_Radius = radius; m_Width = radius * 2.0f; };

		// Sets the Friction of the Collider.
		void SetFriction(float friction) { m_Friction = friction; };

		// Sets the Mass of the Collider.
		void SetMass(float mass) { m_Mass = mass; };

		// Sets if the Collider is Static.
		void SetStatic(bool value) { m_IsStatic = value; };

		// Sets if the Collider is Tile Map Generated.
		void SetTileMapCollider(bool value) { m_IsTileMap = value; };

		// Sets if the Collider is Rotation Locked.
		void SetRotationLock(bool value) { m_FixedRotation = value; };
	};
}