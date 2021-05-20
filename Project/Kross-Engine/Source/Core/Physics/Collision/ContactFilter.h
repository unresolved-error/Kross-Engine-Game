/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once
#include "../../Core.h"

#include "../Physics.h"

namespace Kross
{
    class KROSS_API ParticleEmitter;

    enum class KROSS_API CollisionFilter
    {
        Entity,
        Ground,
        Wall,
        Fluids,
    };

    class KROSS_API ContactFilter : public b2ContactFilter
    {
    private:
        //int count = 0;

    public:
        ContactFilter() {}
        ~ContactFilter() {}

        bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override
        {
            const b2Filter& filterA = fixtureA->GetFilterData();
            const b2Filter& filterB = fixtureB->GetFilterData();

            if (filterA.groupIndex == filterB.groupIndex && filterA.groupIndex != 0)
            {
                return filterA.groupIndex > 0;
            }

            bool collide = (filterA.maskBits & filterB.categoryBits) != 0 && (filterA.categoryBits & filterB.maskBits) != 0;
            return collide;
        }

        bool ShouldCollide(b2Fixture* fixture,
                           b2ParticleSystem* particleSystem,
                           int32 particleIndex) override
        {
            //if (fixture->GetBody()->GetType() == b2_dynamicBody)
            //{
            //    count++;
            //}

            const b2Filter& filterA = fixture->GetFilterData();
            const b2Filter& filterB = *(b2Filter*)particleSystem->GetUserDataBuffer()[particleIndex];

            bool collide = (filterA.maskBits & filterB.categoryBits) != 0 && (filterA.categoryBits & filterB.maskBits) != 0;
            return collide;
        }

        bool ShouldCollide(b2ParticleSystem* particleSystem,
                           int32 particleIndexA, int32 particleIndexB) override
        {
            const b2Filter& filterA = *(b2Filter*)particleSystem->GetUserDataBuffer()[particleIndexA];
            const b2Filter& filterB = *(b2Filter*)particleSystem->GetUserDataBuffer()[particleIndexB];

            bool collide = (filterA.maskBits & filterB.categoryBits) != 0 && (filterA.categoryBits & filterB.maskBits) != 0;
            return collide;
        }
    };
}
