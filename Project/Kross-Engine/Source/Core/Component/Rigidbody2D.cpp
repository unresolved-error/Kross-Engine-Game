
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
        : p_Shape(nullptr), m_ShapeType(ShapeType::Count), p_MassData(nullptr), p_Body(nullptr), p_PhysicsScene(nullptr)
    {
        #ifdef KROSS_DEBUG
        p_DebugShader = ResourceManager::GetResource<Shader>("StandardShader");
        #endif
    }

    Rigidbody2D::~Rigidbody2D()
    {
        p_Body = nullptr;
        p_PhysicsScene = nullptr;
        delete p_MassData;
    }

    void Rigidbody2D::CreateDynamicCircle(float radius, Vector2 pos)
    {
        m_ShapeType = ShapeType::Circle;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        p_Shape = p_PhysicsScene->CreateCircleBody(radius, p_Body);
    }

    void Rigidbody2D::CreateDynamicBox(Vector2 Dimensions, Vector2 pos)
    {
        m_ShapeType = ShapeType::Box;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);

        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        p_Shape = p_PhysicsScene->CreateBoxBody(Dimensions, p_Body);
    }

    void Rigidbody2D::CreateWorldCircle(float radius, Vector2 pos)
    {
        m_ShapeType = ShapeType::Circle;

        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x, pos.y);

        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        p_Shape = p_PhysicsScene->CreateCircleBody(radius, p_Body);
    }

    void Rigidbody2D::CreateWorldBox(Vector2 Dimensions, Vector2 pos)
    {
        m_ShapeType = ShapeType::Box;

        b2BodyDef bodyDef;
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
        p_DebugShader->SetUniform("u_Colour", Colour(1.0f, 0.5f, 0.0f, 1.0f));
        #endif

    }

    void Rigidbody2D::OnUpdate()
    {
        if (p_Body->GetType() != b2_staticBody)
        {
            GetObject()->GetTransform()->m_Position = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y);
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
        if (p_Sprite)
        {
            /* Get the Attached object Transform and update that in the Shader. */
            Transform2D* transform = GetObject()->GetTransform();

            Matrix4 model = Matrix4(1.0f);

            /* Update the Translation, Rotation and Scale Marixes. */
            Matrix4 translation = glm::translate(Matrix4(1.0f), Vector3(Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y), 0.0f));
            Matrix4 rotation = glm::rotate(Matrix4(1.0f), glm::radians(transform->m_Rotation), Vector3(0.0f, 0.0f, 1.0f));
            Matrix4 scale;
            if (m_ShapeType == ShapeType::Box)
            {

                if (p_Body->GetType() != b2_staticBody)
                {
                    Box* box = (Box*)p_Shape;
                    Vector2 boxDim = Vector2(box->GetWidth(), box->GetHeight());
                    scale = glm::scale(Matrix4(1.0f), Vector3((transform->m_Scale * boxDim), 1.0f));
                }
                else
                {
                    Box* box = (Box*)p_Shape;
                    Vector2 boxDim = Vector2(box->GetWidth(), box->GetHeight());
                    scale = glm::scale(Matrix4(1.0f), Vector3((transform->m_Scale * boxDim), 1.0f));
                }
            }

            else if (m_ShapeType == ShapeType::Circle)
            {
                if (p_Body->GetType() != b2_staticBody)
                {
                    Circle* circle = (Circle*)p_Shape;
                    float radius = circle->GetRadius();
                    scale = glm::scale(Matrix4(1.0f), Vector3((transform->m_Scale * radius), 1.0f));
                }
            }

            /* Apply the Matrixes to the Model. */
            model = translation * rotation * scale;
            p_DebugShader->SetUniform("u_Model", model);

            Texture* texture = p_Sprite->GetTexture();
            texture->SetSlot(0);
            texture->Attach();
            p_DebugShader->SetUniform("u_Texture", texture);

            p_DebugShader->Attach();
            p_Sprite->OnRender();

            Texture::Detach();
        }
        
        /* Call Base Component Function. */
        Component::OnRender();
    }
    #endif

    void Rigidbody2D::SetSprite(Sprite* sprite)
    {
        p_Sprite = sprite;

        #ifdef KROSS_DEBUG
        /* Set Shader Values. */
        p_DebugShader->SetUniform("u_UVRatio", p_Sprite->GetUVRatio());
        p_DebugShader->SetUniform("u_UVOffset", p_Sprite->GetUVOffset());
        #endif
    }

    Vector2 Rigidbody2D::GetPosition() const
    {
        return Vector2(GetObject()->GetTransform()->m_Position.x, GetObject()->GetTransform()->m_Position.y);
    }

}