/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../Collision/CollisionData.h"

namespace Kross
{
    class KROSS_API Raycast2DCallback : public b2RayCastCallback
    {
    private:
        float m_closestFraction = 1.0f;
        CollisionData* p_CollisionData;
        RaycastData* p_RayData;

    public:
        Raycast2DCallback() :
            p_CollisionData (KROSS_NEW CollisionData()),
            p_RayData       (KROSS_NEW RaycastData())
        {}
        ~Raycast2DCallback() 
        { 
            delete p_CollisionData;
            delete p_RayData;
        }

        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
            const b2Vec2& normal, float32 fraction) override
        {
            p_RayData->hit = true;
            p_RayData->fixture = fixture;
            p_RayData->body = fixture->GetBody();
            p_RayData->closestFraction = fraction;
            p_RayData->intersectionPoint = Vector2(point.x, point.y);
            p_RayData->intersectionNormal = Vector2(normal.x, normal.y);

            return p_RayData->closestFraction;
        }

        RaycastData* GetRayData() { return p_RayData; }

    };
}