#include "Rigidbody2D.h"
/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "../Manager/SceneManager.h"

namespace Kross
{
    Rigidbody2D::Rigidbody2D()
    {
        
    }

    Rigidbody2D::~Rigidbody2D()
    {
        
    }

    void Rigidbody2D::OnUpdate()
    {
        
    }

    Vector2 Rigidbody2D::GetPosition() const
    {
        return Vector2(GetObject()->GetTransform()->m_Position.x, GetObject()->GetTransform()->m_Position.y);
    }

    void Rigidbody2D::DebugDraw()
    {
        for (int i = 0; i < s_bodies.size(); i++)
        {
            s_bodies[i].
        }
    }
}