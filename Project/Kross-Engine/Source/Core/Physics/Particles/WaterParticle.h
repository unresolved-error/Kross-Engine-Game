/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../Physics.h"
#include "Particle.h"

namespace Kross
{
    class KROSS_API WaterParticle : public Particle
    {
    public:
        void OnCreateParticle(Vector2 pos, ParticleFlag flag);
        void OnCreateParticle(Vector2 pos, ParticleFlag flag, Vector3 colour);

        void OnCreateParticleGroup(Vector2 pos, ParticleFlag flag, ParticleGroupFlag* groupFlag);
        void OnCreateParticleGroup(Vector2 pos, ParticleFlag flag, ParticleGroupFlag* groupFlag, Vector3 colour, float radius, float angle, float angularVelocity);
    };
}