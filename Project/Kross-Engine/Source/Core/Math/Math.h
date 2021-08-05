/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Core.h"

#include <cmath>

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

	class KROSS_API Math
	{
	public:
		static float Lerp(float a, float b, float t);
	};
}

inline static glm::vec2 GetVector2(const b2Vec2& vector)
{
	return glm::vec2(vector.x, vector.y);
}

inline static glm::vec3 GetVector3(const b2Vec3& vector)
{
	return glm::vec3(vector.x, vector.y, vector.z);
}

inline static b2Vec2 Getb2Vec2(const glm::vec2& vector)
{
	return b2Vec2(vector.x, vector.y);
}

inline static b2Vec3 Getb2Vec3(const glm::vec3& vector)
{
	return b2Vec3(vector.x, vector.y, vector.z);
}