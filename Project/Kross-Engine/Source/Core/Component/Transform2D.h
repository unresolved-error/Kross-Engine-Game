/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Math/Math.h"

#include "Component.h"

namespace Kross
{
	class KROSS_API Transform2D : public Component
	{
	public:
		Transform2D() :
			m_Rotation	(0.0f),
			m_Position	(Vector2(0.0f)),
			m_Scale		(Vector2(1.0f))
		{};
		~Transform2D() {};

		Vector2 m_Position;
		Vector2 m_Scale;

		float m_Rotation;
	};
}