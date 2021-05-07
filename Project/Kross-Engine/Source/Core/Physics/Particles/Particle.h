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

	class KROSS_API Particle
	{
	private:
	protected:
		int m_ParticleID = 0;

		uint32 m_Flags = 0;
		uint32 m_GroupFlags = 0;
		Vector2 m_Position = Vector2(0,0);
		Vector4 m_Color = Vector4(255, 0, 0, 255);
		float m_Lifetime = 0.0f;

		float m_Angle = 0.0f;
		Vector2 m_LinearVelocity = Vector2(0,0);
		float m_AngularVelocity = 0.0f;
		float m_Strength = 0.0f;
		const b2Shape* m_Shape = NULL;

		b2ParticleDef m_ParticleDef;

	public:
		/* The group bool is to determine where values need to be assigned */
		Particle()	{}

		ParticleDef GetParticleDef() { return m_ParticleDef; }

		void CreateParticle(ParticleSystem* particleSystem);
		/* Creates a particle def with the supplied information */
		ParticleDef CreateParticleDef();

		void CreateParticleGroup(ParticleSystem* particleSystem);
		/* Creates a particle group def with the supplied information */
		ParticleGroupDef CreateParticleGroupDef();

		/* Adds a particle flag by combining the enum */
		void AddParticleFlag(uint32 flag) { m_Flags = flag; }
		int GetParticleFlag() { return m_Flags; }

		/* Adds a particle group flag by combining the enum */
		void AddParticleGroupFlag(uint32 flag) { m_GroupFlags = flag; }
		int GetParticleGroupFlag() { return m_GroupFlags; }

		/* Sets the position of the particle */
		void SetPosition(Vector2 pos) { m_Position = pos; }
		Vector2 GetPosition() { return m_Position; }

		/* Sets the color of the particle */
		void SetColor(Vector4 color) { m_Color = color; }
		Vector4 GetColor() { return m_Color; }

		/* Sets the lifetime of the particle */
		void SetLifetime(float lifetime) { m_Lifetime = lifetime; }
		float GetLifetime() { return m_Lifetime; }

		/* Sets the shape of the particle as a polygon */
		void SetShape(Vector2 dim) 
		{ 
			PolygonShape shape;
			shape.SetAsBox(dim.x, dim.y);
			m_Shape = &shape;
		}
		/* Sets the shape of the particle as a circle */
		void SetShape(float radius) 
		{
			CircleShape shape;
			shape.m_radius = radius;
			m_Shape = &shape;
		}
		const b2Shape* GetShape() { return m_Shape; }

		/* Sets the angle of the particle group */
		void SetAngle(float angle) { m_Angle = angle; }
		float GetAngle() { return m_Angle; }

		void SetAngularVelocity(float angularVelocity) { m_AngularVelocity = angularVelocity; }
		float GetAngularVelocity() { return m_AngularVelocity; }

		/* Sets the strength of the particle group */
		void SetStrength(float strength) { m_Strength = strength; }
		float GetStrength() { return m_Strength; }

	};
}