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
    struct KROSS_API FluidCollisionData
    {
        const b2ParticleSystem* p_ParticleSystem = nullptr;
        List<int> m_ParticleIndexs;
        bool m_Collision = false;
    };

    struct KROSS_API CircleCastData
    {
        List<b2Body*> m_Bodies;
    };
}