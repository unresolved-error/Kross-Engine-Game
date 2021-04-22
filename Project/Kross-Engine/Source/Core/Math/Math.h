/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include"../Core.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Box2D/Box2D.h"

namespace Kross
{
	typedef glm::vec1 Vector1;
	typedef glm::vec2 Vector2;
	typedef glm::vec3 Vector3;
	typedef glm::vec4 Vector4;
	typedef glm::vec4 Colour;

	typedef glm::mat2 Matrix2;
	typedef glm::mat3 Matrix3;
	typedef glm::mat4 Matrix4;

	
}

void operator =(b2Vec2& lhs, Kross::Vector2& rhs)
{
	lhs.x = rhs.x;
	lhs.y = rhs.y;
}