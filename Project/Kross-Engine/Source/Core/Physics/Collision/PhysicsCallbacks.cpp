/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "PhysicsCallbacks.h"

namespace Kross
{
    FluidCollisionCallback::FluidCollisionCallback() : 
        p_Data(nullptr)
    {
    }

    FluidCollisionCallback::~FluidCollisionCallback()
    {
        delete p_Data;
    }

    bool FluidCollisionCallback::ReportFixture(b2Fixture* fixture)
    {
        return true;
    }

    bool FluidCollisionCallback::ReportParticle(const b2ParticleSystem* particleSystem, int32 index)
    {
        p_Data->p_ParticleSystem = particleSystem;
        p_Data->m_ParticleIndexs.push_back(index);
        return true;
    }

    bool FluidCollisionCallback::ShouldQueryParticleSystem(const b2ParticleSystem* particleSystem)
    {
        p_Data->p_ParticleSystem = particleSystem;
        return true;
    }

    FluidCollisionData* FluidCollisionCallback::GetFluidCollisionData()
    {
        return p_Data;
    }
}