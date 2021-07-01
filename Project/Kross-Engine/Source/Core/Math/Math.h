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

inline static Kross::Vector2 GetVector2(const b2Vec2& vector)
{
	return Kross::Vector2(vector.x, vector.y);
}

inline static Kross::Vector3 GetVector3(const b2Vec3& vector)
{
	return Kross::Vector3(vector.x, vector.y, vector.z);
}