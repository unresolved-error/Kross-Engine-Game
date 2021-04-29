/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../Physics.h"

namespace Kross
{
	class KROSS_API ParticleEmitter;

	class KROSS_API Particle
	{
	private:

	protected:
		int m_ParticleID;

		int m_Flags = 0;
		int m_GroupFlags = 0;
		Vector2 m_Position = Vector2(0,0);
		Vector4 m_Color = Vector4(255, 0, 0, 255);
		float m_Lifetime = 0.0f;

		float m_Angle = 0.0f;
		Vector2 m_LinearVelocity = Vector2(0,0);
		float m_AngularVelocity = 0.0f;
		float m_Strength = 0.0f;
		const b2Shape* m_Shape = NULL;

	public:
		/* The group bool is to determine where values need to be assigned */
		Particle() : m_ParticleID(-1) {}


		ParticleDef CreateParticle();
		ParticleGroupDef CreateParticleGroup();

		void AddParticleFlag(ParticleFlag flag) { m_Flags += flag; }

		void AddParticleGroupFlag(ParticleGroupFlag flag) { m_GroupFlags += flag; }

		void SetPosition(Vector2 pos) { m_Position = pos; }

		void SetColor(Vector4 color) { m_Color = color; }

		void SetLifetime(float lifetime) { m_Lifetime = lifetime; }

		void SetShape(PolygonShape shape) { m_Shape = &shape; }
		void SetShape(CircleShape shape) { m_Shape = &shape; }

		void SetAngle(float angle) { m_Angle = angle; }

		void SetStrength(float strength) { m_Strength = strength; }

	};
}