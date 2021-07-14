/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "AABBCollisionCallbacks.h"

namespace Kross
{
    AABBCollisionCallback::AABBCollisionCallback() : 
        p_Data(nullptr)
    {}

    AABBCollisionCallback::~AABBCollisionCallback()
    {
        delete p_Data;
    }

    bool AABBCollisionCallback::ReportFixture(b2Fixture* fixture)
    {
        p_Data->m_Fixture.push_back(fixture);
        return true;
    }

    bool AABBCollisionCallback::ReportParticle(const b2ParticleSystem* particleSystem, int32 index)
    {
        p_Data->p_ParticleSystem = particleSystem;
        p_Data->m_ParticleIndexs.push_back(index);
        return true;
    }

    bool AABBCollisionCallback::ShouldQueryParticleSystem(const b2ParticleSystem* particleSystem)
    {
        p_Data->p_ParticleSystem = particleSystem;
        return true;
    }

    AABBCollisionData* AABBCollisionCallback::GetAABBCollisionData()
    {
        return p_Data;
    }
}