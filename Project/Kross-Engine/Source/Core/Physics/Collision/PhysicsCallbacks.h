/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once
#include "../../Core.h"

#include "Box2D/Box2D.h"

namespace Kross
{
    class KROSS_API ParticleEmitter;

    struct KROSS_API FluidCollisionData
    {
        const b2ParticleSystem* p_ParticleSystem = nullptr;
        List<int> m_ParticleIndexs;
        bool m_Collision = false;

    };

    class KROSS_API FluidCollisionCallback : public b2QueryCallback
    {
    private:
        FluidCollisionData* p_Data;

    public:
        FluidCollisionCallback();
        ~FluidCollisionCallback();


        /// Called for each fixture found in the query AABB.
        /// @return false to terminate the query.
        bool ReportFixture(b2Fixture* fixture) override;

        /// Called for each particle found in the query AABB.
        /// @return false to terminate the query.
        bool ReportParticle(const b2ParticleSystem* particleSystem,
            int32 index) override;

        /// Cull an entire particle system from b2World::QueryAABB. Ignored for
        /// b2ParticleSystem::QueryAABB.
        /// @return true if you want to include particleSystem in the AABB query,
        /// or false to cull particleSystem from the AABB query.
        bool ShouldQueryParticleSystem(
            const b2ParticleSystem* particleSystem) override;

        void SetFluidCollisionData(FluidCollisionData* data) { p_Data = data; }

        /* Returns the fluid collision data */
        FluidCollisionData* GetFluidCollisionData();

    };

}
