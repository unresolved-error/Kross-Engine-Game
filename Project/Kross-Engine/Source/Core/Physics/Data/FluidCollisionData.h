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
    struct KROSS_API AABBCollisionData
    {
        std::vector<b2Fixture*> m_Fixture;
        const b2ParticleSystem* p_ParticleSystem = nullptr;
        std::vector<int> m_ParticleIndexs;
        bool m_Collision = false;
    };
}