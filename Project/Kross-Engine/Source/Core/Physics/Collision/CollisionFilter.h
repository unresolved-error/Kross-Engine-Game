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
    enum class KROSS_API CollisionFilters
    {
        Entity,
        Ground,
        Wall,
        Fluids,

    };

    class KROSS_API CollisionFilter
    {
    private:
        b2ContactFilter* p_ContactFilter;

    public:
        CollisionFilter() : p_ContactFilter(new b2ContactFilter()) {}
        ~CollisionFilter()
        {
            delete p_ContactFilter;
        }

        void SetParticleContactFilter(b2Fixture* fixture, b2ParticleSystem* particleSystem, int index)
        {
            p_ContactFilter->ShouldCollide(fixture, particleSystem, index);
        }

        void SetFixtureContactFilter(b2Fixture* fixtureA, b2Fixture* fixtureB)
        {
            p_ContactFilter->ShouldCollide(fixtureA, fixtureB);
        }
    };
}
