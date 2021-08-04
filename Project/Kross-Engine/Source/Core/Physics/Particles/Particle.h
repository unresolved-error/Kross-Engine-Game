/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../Physics.h"
#include "../Box2D/Box2D/Box2D.h"
#include "../Filters/ParticleType.h"

namespace Kross
{

	class KROSS_API Particle
	{
	protected:
		uint32 m_Flags = 0;
		uint32 m_GroupFlags = 0;

		Vector2 m_Position = Vector2(0,0);
		Vector2 m_LinearVelocity = Vector2(0,0);
		Vector4 m_Color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		int m_ParticleID = 0;
		bool m_IsParticleGroup = false;

		float m_Lifetime = 0.0f;
		float m_Angle = 0.0f;
		float m_AngularVelocity = 0.0f;
		float m_Strength = 0.0f;
		float m_Radius = 0.025f;

		b2Shape* p_Shape;
		b2ParticleDef* p_ParticleDef;
		b2Filter* p_Filter;

	public:
		/* The group bool is to determine where values need to be assigned */
		Particle() :
			p_Shape			(nullptr),
			p_ParticleDef	(nullptr),
			p_Filter		(nullptr)
		{}
		~Particle();

		ParticleDef* GetParticleDef() { return p_ParticleDef; }

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
			PolygonShape* shape = KROSS_ALLOCATION_REPORT(PolygonShape());
			shape->SetAsBox(dim.x, dim.y);
			p_Shape = shape;
		}
		/* Sets the shape of the particle as a circle */
		void SetShape(float radius) 
		{
			CircleShape* shape = KROSS_ALLOCATION_REPORT(CircleShape());
			shape->m_radius = radius;
			p_Shape = shape;
		}
		const b2Shape* GetShape() { return p_Shape; }

		/* Sets the angle of the particle group */
		void SetAngle(float angle) { m_Angle = angle; }
		float GetAngle() { return m_Angle; }

		void SetAngularVelocity(float angularVelocity) { m_AngularVelocity = angularVelocity; }
		float GetAngularVelocity() { return m_AngularVelocity; }

		/* Sets the strength of the particle group */
		void SetStrength(float strength) { m_Strength = strength; }
		float GetStrength() { return m_Strength; }

		void SetParticleGroupPosition(ParticleGroupDef* groupDef, Vector2 pos)
		{
			groupDef->position.Set(pos.x, pos.y);
		}

		void SetCollisionFilter(b2Filter* filter) { p_Filter = filter; };
		b2Filter* GetCollisionFilter() const { return p_Filter; };

		void SetParticleID(int id) { m_ParticleID = id; }
		int GetParticleID() { return m_ParticleID; }

		void SetRadius(float radius) { m_Radius = radius; }
		float GetRadius() { return m_Radius; }

		/* Sets the Particle group type */
		void ParticleGroup(bool isGroup) { m_IsParticleGroup = isGroup; }
		/* Returns true if there is a particle group */
		bool GetParticleGroupType() { return m_IsParticleGroup; }
	};
}

//Include all particles here
#include "WaterParticle.h"
#include "SpringParticle.h"
#include "ElasticParticle.h"
#include "ViscousParticle.h"
#include "PowderParticle.h"
#include "TensileParticle.h"
#include "ColourMixingParticle.h"
#include "StaticPressureParticle.h"
#include "ReactiveParticle.h"
#include "RepulsiveParticle.h"
