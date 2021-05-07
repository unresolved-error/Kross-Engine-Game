/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../Physics.h"
#include "CollisionData.h"

namespace Kross
{
    class KROSS_API Raycast2DCallback : public b2RayCastCallback
    {
    private:
        float m_closestFraction = 1.0f;
        CollisionData* p_CollisionData = new CollisionData();
        RaycastData* p_RayData = new RaycastData();

    public:
        Raycast2DCallback() {};
        ~Raycast2DCallback() { delete p_RayData; }

        float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
            const b2Vec2& normal, float32 fraction) override
        {
            p_RayData->hit = true;
            p_RayData->fixture = fixture;
            p_RayData->body = fixture->GetBody();
            p_RayData->closestFraction = fraction;
            p_RayData->intersectionPoint = Vector2(point.x, point.y);
            p_RayData->intersectionNormal = Vector2(normal.x, normal.y);




            //if (fixture != nullptr)
            //{
            //    p_RayData->body = fixture->GetBody();
            //    p_RayData->hit = true;
            //}
            //else
            //{
            //    p_RayData->body = nullptr;
            //    p_RayData->hit = false;
            //}
            //
            //if (fraction < p_RayData->closestFraction)
            //{
            //    p_RayData->closestFraction = fraction;
            //    p_RayData->intersectionNormal = Vector2(normal.x, normal.y);
            //}
            //
            //p_RayData->intersectionPoint = Vector2(point.x, point.y);

            return p_RayData->closestFraction;
        }

        RaycastData* GetRayData() { return p_RayData; }

    };
}