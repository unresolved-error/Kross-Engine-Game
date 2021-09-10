/*
 *  Author: ChrisDeitch
 *  Editors:
 *      - Chris Deitch.
 */

#pragma once
#include "../../Core.h"
#include "../PhysicsScene.h"

namespace Kross
{
    struct KROSS_API CogRotationPiece 
    {
    private:
        Body* m_Body;

        void SetBody(Body* body) { m_Body = body; };

        void Destroy(PhysicsScene* scene) { scene->DetachBody(m_Body); m_Body = nullptr; };

        Body* GetBody() const { return m_Body; };

    protected:
        friend class Cog;

    public:
        CogRotationPiece() :
            m_Body(nullptr)
        {};
        ~CogRotationPiece()
        {
            m_Body = nullptr;
        }
        Vector2 GetPosition() const { return GetVector2(m_Body->GetTransform().p); };

        float GetRotation() const { return glm::degrees(m_Body->GetAngle()); };

    
    };
}