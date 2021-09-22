/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../../Core.h"
#include "../Filters/PhysicsFilters.h"

namespace Kross
{
    class KROSS_API ParticleEmitter;

    class KROSS_API AABBCollisionCallback : public b2QueryCallback
    {
    private:
        AABBCollisionData* p_Data;

    public:
        AABBCollisionCallback() :
            p_Data(nullptr)
        {};

        ~AABBCollisionCallback()
        {
            delete p_Data;
        }


        /// Called for each fixture found in the query AABB.
        /// @return false to terminate the query.
        bool ReportFixture(b2Fixture* fixture) override
        {
            p_Data->m_Fixture.push_back(fixture);
            return true;
        }

        /// Called for each particle found in the query AABB.
        /// @return false to terminate the query.
        bool ReportParticle(const b2ParticleSystem* particleSystem,
            int32 index) override
        {
            p_Data->p_ParticleSystem = particleSystem;
            p_Data->m_ParticleIndexs.push_back(index);
            return true;
        }

        /// Cull an entire particle system from b2World::QueryAABB. Ignored for
        /// b2ParticleSystem::QueryAABB.
        /// @return true if you want to include particleSystem in the AABB query,
        /// or false to cull particleSystem from the AABB query.
        bool ShouldQueryParticleSystem(const b2ParticleSystem* particleSystem) override
        {
            p_Data->p_ParticleSystem = particleSystem;
            return true;
        }

        /* Returns the fluid collision data */
        AABBCollisionData* GetAABBCollisionData()
        {
            return p_Data;
        }

        void SetAABBCollisionData(AABBCollisionData* data) { p_Data = data; }
    };
}
