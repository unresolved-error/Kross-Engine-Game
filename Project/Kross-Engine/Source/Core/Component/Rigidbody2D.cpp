
/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */

#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "Rigidbody2D.h"
#include "../Physics/Shape/Shape.h"
#include "../Manager/Time.h"

namespace Kross
{
    Rigidbody2D::Rigidbody2D()
        : p_Shape(nullptr), m_ShapeType(ShapeType::Count), p_Body(nullptr), p_PhysicsScene(nullptr)
    {
        #ifdef KROSS_DEBUG
        p_DebugShader = ResourceManager::GetResource<Shader>("LineShader");
        lines = new LineRenderer();
        #endif
    }

    Rigidbody2D::~Rigidbody2D()
    {
        p_Body = nullptr;
        p_PhysicsScene = nullptr;
    }

    void Rigidbody2D::CreateDynamicCircle(float radius, Vector2 pos)
    {
        m_ShapeType = ShapeType::Circle;

        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        p_Shape = p_PhysicsScene->CreateCircleBody(radius, p_Body);
    }

    void Rigidbody2D::CreateDynamicBox(Vector2 Dimensions, Vector2 pos)
    {
        m_ShapeType = ShapeType::Box;

        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);

        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        p_Shape = p_PhysicsScene->CreateBoxBody(Dimensions, p_Body);
    }

    void Rigidbody2D::CreateWorldCircle(float radius, Vector2 pos)
    {
        m_ShapeType = ShapeType::Circle;

        BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x, pos.y);

        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        p_Shape = p_PhysicsScene->CreateCircleBody(radius, p_Body);
    }

    void Rigidbody2D::CreateWorldBox(Vector2 Dimensions, Vector2 pos)
    {
        m_ShapeType = ShapeType::Box;

        BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x, pos.y);

        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        p_Shape = p_PhysicsScene->CreateBoxBody(Dimensions, p_Body);
    }

    void Rigidbody2D::OnStart()
    {
        p_Body = GetBody();

        p_PhysicsScene = GetPhysicsScene();

        #ifdef KROSS_DEBUG
        //p_DebugShader->SetUniform("u_Colour", Colour(1.0f, 0.5f, 0.0f, 1.0f));
        lines->Initialise();
        #endif
    }

    void Rigidbody2D::OnUpdate()
    {
        if (p_Body->GetType() != b2_staticBody)
        {
            GetObject()->GetTransform()->m_Position = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y);
            GetObject()->GetTransform()->m_Rotation = glm::degrees(p_Body->GetAngle());
        }
        /* Call Base Component Function. */
        Component::OnUpdate();
    }

    void Rigidbody2D::OnApplyForce(Vector2 force)
    {
        if (glm::length(force) > 0.0001f)
        {
            p_Body->ApplyForceToCenter({ force.x, force.y }, true);
        }
    }

    void Rigidbody2D::OnApplyImpulse(Vector2 impulse)
    {
        p_Body->ApplyLinearImpulse({ impulse.x, impulse.y }, { p_Body->GetPosition().x, p_Body->GetPosition().y }, true);
    }

    #ifdef KROSS_DEBUG
    void Rigidbody2D::OnRender()
    {
        lines->SetColour(Vector3(1.0f, 0.0f, 0.0f));

        if (m_ShapeType == ShapeType::Box)
        {
            if (p_Body->GetType() != b2_staticBody)
            {
                lines->DrawRigidBody(p_Body);
            }
            else
            {
                lines->DrawRigidBody(p_Body);
            }
        }
        else if (m_ShapeType == ShapeType::Circle)
        {
            if (p_Body->GetType() != b2_staticBody)
            {
                lines->DrawRigidBody(p_Body);
            }
            else
            {
                lines->DrawRigidBody(p_Body);
            }
        }

        p_DebugShader->Attach();
        lines->UpdateFrame();

        /* Call Base Component Function. */
        Component::OnRender();
    }
    #endif

    void Rigidbody2D::SetSprite(Sprite* sprite)
    {
        p_Sprite = sprite;
    }

    Vector2 Rigidbody2D::GetPosition() const
    {
        return Vector2(GetObject()->GetTransform()->m_Position.x, GetObject()->GetTransform()->m_Position.y);
    }

}