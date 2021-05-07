
/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
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
        /* When in debug set up the shader and renderer */
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

    void Rigidbody2D::CreateDynamicCircle(float radius, Vector2 pos, bool fixedRotation)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Circle;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        
        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
        p_Body->SetFixedRotation(fixedRotation);

        /* Assigns the shape to the pointer */
        p_Shape = p_PhysicsScene->CreateCircleBody(radius, p_Body);
    }

    void Rigidbody2D::CreateDynamicBox(Vector2 Dimensions, Vector2 pos, bool fixedRotation)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Box;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
        p_Body->SetFixedRotation(fixedRotation);

        /* Assigns the shape to the pointer */
        p_Shape = p_PhysicsScene->CreateBoxBody(Dimensions, p_Body);
    }

    void Rigidbody2D::CreateWorldCircle(float radius, Vector2 pos)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Circle;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x, pos.y);

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        /* Assigns the shape to the pointer */
        p_Shape = p_PhysicsScene->CreateCircleBody(radius, p_Body);
    }

    void Rigidbody2D::CreateWorldBox(Vector2 Dimensions, Vector2 pos)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Box;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x, pos.y);

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        /* Assigns the shape to the pointer */
        p_Shape = p_PhysicsScene->CreateBoxBody(Dimensions, p_Body);
    }

    void Rigidbody2D::OnStart()
    {
        /* Gets the body */
        p_Body = GetBody();

        /* Gets the physics scene */
        p_PhysicsScene = GetPhysicsScene();

        /* When in debug the line renderer is initialised */
        #ifdef KROSS_DEBUG
        lines->Initialise();
        #endif
    }

    void Rigidbody2D::OnUpdate()
    {
        /* Checks if the object is not static */
        if (p_Body->GetType() != b2_staticBody)
        {
            /* Gets the object position and updates it with the position of the body */
            GetObject()->GetTransform()->m_Position = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y);

            /* Gets the object rotation and updates it with the angle of the body */
            GetObject()->GetTransform()->m_Rotation = glm::degrees(p_Body->GetAngle());
        }
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

        GetObject()->GetTransform()->m_Position = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y);

        /* Checks the shape type of the body */
        if (m_ShapeType == ShapeType::Box)
        {
            /* Draws the rigid body */
            lines->DrawRigidBody(p_Body);
        }
        else if (m_ShapeType == ShapeType::Circle)
        {
            /* Draws the rigid body */
            lines->DrawRigidBody(p_Body);
        }

        else
            lines->DrawCross(Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y), 5.0f);

        /* Attatches the shader */
        p_DebugShader->Attach();

        /* Updates the line renderer */
        lines->UpdateFrame();
    }
    #endif

    Vector2 Rigidbody2D::GetPosition() const
    {
        return Vector2(GetObject()->GetTransform()->m_Position.x, GetObject()->GetTransform()->m_Position.y);
    }

}