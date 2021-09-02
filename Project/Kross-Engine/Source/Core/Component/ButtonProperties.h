/*
 *  Author: Chris Deitch.
 *  Editors:
 *		- Chris Deitch
 */

#pragma once

#include "../Core.h"

#include "Component.h"

namespace Kross
{
	class KROSS_API ButtonProperties : public Component
	{
	private:
		bool m_hasConstantEffect = true;
		bool m_hasMoveEffect = true;
		Vector2 m_moveDirection = Vector2(1.0f,0.0f);
		float m_moveStrength = 1.0f;
		float m_weightRequired = 1.0f;
		Object* m_objectToEffect = nullptr;


	public:
		ButtonProperties()
		{};

		~ButtonProperties()
		{
		}

		void SetHasConstantEffect(bool hasConstEff) { m_hasConstantEffect = hasConstEff; }
		void SetHasMoveEffect(bool hasMoveEff) { m_hasMoveEffect = hasMoveEff; }
		void SetMoveDirection(Vector2 direction) { m_moveDirection = direction; }
		void SetMoveStrength(float strength) { m_moveStrength = strength; }
		void SetWeightRequired(float weight) { m_weightRequired = weight; }
		void SetObjectToEffect(Object* obj) { m_objectToEffect = obj; }


		bool IsAConstantEffect() { return m_hasConstantEffect; }
		bool IsAMoveEffect() { return m_hasMoveEffect; }
		Vector2 GetMoveDirection() { return m_moveDirection; }
		float GetMoveStrength() { return m_moveStrength; }
		float GetWeightRequired() { return m_weightRequired; }
		Object* GetObjectToEffect() { return m_objectToEffect; }


	};
}