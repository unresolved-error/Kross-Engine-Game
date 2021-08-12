/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../Core.h"

#include "Component.h"


namespace Kross
{
	class KROSS_API ParticleProperties : public Component
	{
	private:
		ParticleSystemDef* p_ParticleSystemDef;
		ParticleGroupDef* p_GroupDef;

	public:
		ParticleProperties() :
			p_ParticleSystemDef	(KROSS_NEW ParticleSystemDef()),
			p_GroupDef			(KROSS_NEW ParticleGroupDef())
		{};

		~ParticleProperties() {};

		/* Adds to the flags */
		void AddParticleFlags(uint32 flags) { p_GroupDef->flags += flags; }
		uint32 GetParticleFlags() { return p_GroupDef->flags; }

		/* Adds to the group flags */
		void AddGroupFlags(uint32 flags) { p_GroupDef->groupFlags += flags; }
		uint32 GetGroupFlags() { return p_GroupDef->groupFlags; }

		/* Sets the position */
		void SetPosition(Vector2 pos) { p_GroupDef->position = Getb2Vec2(pos); }
		b2Vec2 GetPosition() { return p_GroupDef->position; }

		/* Sets the angle */
		void SetAngle(float angle) { p_GroupDef->angle = angle; }
		float GetAngle() { return p_GroupDef->angle; }

		/* Sets the linear velocity */
		void SetLinearVelocity(Vector2 velocity) { p_GroupDef->linearVelocity = Getb2Vec2(velocity); }
		b2Vec2 GetLinearVelocity() { return p_GroupDef->linearVelocity; }

		/* Sets the angular velocity */
		void SetAngularVelocity(float velocity) { p_GroupDef->angularVelocity = velocity; }
		float GetAngularVelocity() { return p_GroupDef->angularVelocity; }

		/* Sets the color */
		void SetColor(b2ParticleColor color) { p_GroupDef->color = color; }
		b2ParticleColor GetColor() { return p_GroupDef->color; }

		/* Sets the strength */
		void SetStrength(float strength) { p_GroupDef->strength = strength; }
		float GetStrength() { return p_GroupDef->strength; }

		/* Sets the shape */
		void SetShape(b2Shape* shape) { p_GroupDef->shape = shape; }
		const b2Shape* GetShape() { return p_GroupDef->shape; }

		/* Sets the stride */
		void SetStride(float stride) { p_GroupDef->stride = stride; }
		float GetStride() { return p_GroupDef->stride; }

		/* Sets the lifetime */
		void SetLifetime(float lifetime) { p_GroupDef->lifetime = lifetime; }
		float GetLifetime() { return p_GroupDef->lifetime; }

		/* Sets the user data */
		void SetUserData(void* userData) { p_GroupDef->userData = userData; }
		void* GetUserData() { return p_GroupDef->userData; }

		/* Set the group */
		void SetGroup(b2ParticleGroup* group) { p_GroupDef->group = group; }
		b2ParticleGroup* GetGroup() { return p_GroupDef->group; }

		/* Sets the strict contact check */
		void SetStrictContactCheck(bool check) { p_ParticleSystemDef->strictContactCheck = check; }
		bool GetStrictContactCheck() { return p_ParticleSystemDef->strictContactCheck; }

		/* Sets the density of the system */
		void SetDensity(float density) { p_ParticleSystemDef->density = density; }
		float GetDensity() { return p_ParticleSystemDef->density; }

		/* Sets the gravity scale */
		void SetGravityScale(float gravScale) { p_ParticleSystemDef->gravityScale = gravScale; }
		float GetGravityScale() { return p_ParticleSystemDef->gravityScale; }

		/* Sets the radius of each particle */
		void SetRadius(float radius) { p_ParticleSystemDef->radius = radius; }
		float GetRadius() { return p_ParticleSystemDef->radius; }

		/* Sets the max count of the system */
		void SetMaxCount(int max) { p_ParticleSystemDef->maxCount = max; }
		int GetMaxCount() { return p_ParticleSystemDef->maxCount; }

		/* Sets the pressure strength */
		void SetPressureStrength(float strength) { p_ParticleSystemDef->pressureStrength = strength; }
		float GetPressureStrength() { return p_ParticleSystemDef->pressureStrength; }

		/* Sets the damping strength */
		void SetDamping(float damping) { p_ParticleSystemDef->dampingStrength = damping; }
		float GetDamping() { return p_ParticleSystemDef->dampingStrength; }

		/* Sets the elastic strength */
		void SetElastic(float elastic) { p_ParticleSystemDef->elasticStrength = elastic; }
		float GetElastic() { return p_ParticleSystemDef->elasticStrength; }

		/* Sets the spring strength */
		void SetSpring(float spring) { p_ParticleSystemDef->springStrength = spring; }
		float GetSpring() { return p_ParticleSystemDef->springStrength; }

		/* Sets the viscous strength */
		void SetViscous(float viscous) { p_ParticleSystemDef->viscousStrength = viscous; }
		float GetViscous() { return p_ParticleSystemDef->viscousStrength; }

		/* Sets surface tension pressure strength */
		void SetSurfaceTensionPressureStrength(float strength) { p_ParticleSystemDef->surfaceTensionPressureStrength = strength; }
		float GetSurfaceTensionPressureStrength() { return p_ParticleSystemDef->surfaceTensionPressureStrength; }

		/* Sets surface tension Normal strength */
		void SetSurfaceTensionNormalStrength(float strength) { p_ParticleSystemDef->surfaceTensionNormalStrength = strength; }
		float GetSurfaceTensionNormalStrength() { return p_ParticleSystemDef->surfaceTensionNormalStrength; }
	};
}