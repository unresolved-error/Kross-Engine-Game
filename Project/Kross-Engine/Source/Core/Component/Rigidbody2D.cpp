
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

#include "../Physics/Physics.h"

namespace Kross
{
    Rigidbody2D::Rigidbody2D()
        : m_ShapeType(ShapeType::Count), p_Body(nullptr), p_PhysicsScene(nullptr),
        p_Box(nullptr), p_Circle(nullptr), p_RayData(nullptr), p_FixtureDef(new FixtureDef()), p_MassData(new b2MassData())
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
        delete p_FixtureDef;
        if (p_Circle)
            delete p_Circle;
        if (p_Box)
            delete p_Box;
        delete p_MassData;
    }

    void Rigidbody2D::CreateDynamicCircle(float radius, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits)
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

        /* Creates the cirlce */
        CircleShape circleShape;
        /* Sets the circles radius */
        circleShape.m_radius = radius;

        /* Creates a fixtureDef and assigns the variables */
        p_FixtureDef->shape = &circleShape;
        p_FixtureDef->density = 0.5f;
        p_FixtureDef->friction = 0.5f;
        p_FixtureDef->filter.categoryBits = categoryBits;
        p_FixtureDef->filter.maskBits = maskBits;

        p_Body->CreateFixture(p_FixtureDef);

        p_PhysicsScene->AttachBody(p_Body);

        /* Assigns the shape to the pointer */
        p_Circle = new Circle(radius, Vector2(0, 0));
    }

    void Rigidbody2D::CreateDynamicCircle(float radius, float friction, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits)
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

        /* Creates the cirlce */
        CircleShape circleShape;
        /* Sets the circles radius */
        circleShape.m_radius = radius;

        /* Creates a fixtureDef and assigns the variables */
        p_FixtureDef->shape = &circleShape;
        p_FixtureDef->density = 0.5f;
        p_FixtureDef->friction = friction;
        p_FixtureDef->filter.categoryBits = categoryBits;
        p_FixtureDef->filter.maskBits = maskBits;

        p_Body->CreateFixture(p_FixtureDef);

        p_PhysicsScene->AttachBody(p_Body);

        /* Assigns the shape to the pointer */
        p_Circle = new Circle(radius, Vector2(0, 0));
    }

    void Rigidbody2D::CreateDynamicBox(Vector2 Dimensions, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Box;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        bodyDef.linearDamping = 2.0f;

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        /* Creates the shape */
        PolygonShape dynamicBox;
        /* Sets the shape as a box */
        dynamicBox.SetAsBox(Dimensions.x / 2.0f, Dimensions.y / 2.0f);

        /* Creates a fixtureDef and assigns all variables */
        p_FixtureDef->shape = &dynamicBox;
        p_FixtureDef->density = 1.0f;
        p_FixtureDef->friction = 0.5f;
        p_FixtureDef->filter.categoryBits = categoryBits;
        p_FixtureDef->filter.maskBits = maskBits;

        p_Body->CreateFixture(p_FixtureDef);
        p_Body->SetFixedRotation(fixedRotation);

        p_PhysicsScene->AttachBody(p_Body);

        /* Assigns the shape to the pointer */
        p_Box = new Box(Dimensions, Vector2(0, 0));
    }

    void Rigidbody2D::CreateDynamicBox(Vector2 Dimensions, float friction, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Box;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        bodyDef.linearDamping = 2.0f;

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        /* Creates the shape */
        PolygonShape dynamicBox;
        /* Sets the shape as a box */
        dynamicBox.SetAsBox(Dimensions.x / 2.0f, Dimensions.y / 2.0f);

        /* Creates a fixtureDef and assigns all variables */
        p_FixtureDef->shape = &dynamicBox;
        p_FixtureDef->density = 1.0f;
        p_FixtureDef->friction = friction;
        p_FixtureDef->filter.categoryBits = categoryBits;
        p_FixtureDef->filter.maskBits = maskBits;

        p_Body->CreateFixture(p_FixtureDef);
        p_Body->SetFixedRotation(fixedRotation);

        p_PhysicsScene->AttachBody(p_Body);

        /* Assigns the shape to the pointer */
        p_Box = new Box(Dimensions, Vector2(0, 0));
    }

    void Rigidbody2D::CreateWorldCircle(float radius, Vector2 pos, uint16 categoryBits, uint16 maskBits)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Circle;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x, pos.y);

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        /* Creates the cirlce */
        CircleShape circleShape;
        /* Sets the circles radius */
        circleShape.m_radius = radius;

        /* Creates a fixtureDef and assigns the variables */
        p_FixtureDef->shape = &circleShape;
        p_FixtureDef->density = 0.5f;
        p_FixtureDef->friction = 0.5f;
        p_FixtureDef->filter.categoryBits = categoryBits;
        p_FixtureDef->filter.maskBits = maskBits;

        p_Body->CreateFixture(p_FixtureDef);

        p_PhysicsScene->AttachBody(p_Body);

        /* Assigns the shape to the pointer */
        p_Circle = new Circle(radius, Vector2(0, 0));
    }

    void Rigidbody2D::CreateWorldCircle(float radius, float friction, Vector2 pos, uint16 categoryBits, uint16 maskBits)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Circle;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x, pos.y);

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);

        /* Creates the cirlce */
        CircleShape circleShape;
        /* Sets the circles radius */
        circleShape.m_radius = radius;

        /* Creates a fixtureDef and assigns the variables */
        p_FixtureDef->shape = &circleShape;
        p_FixtureDef->density = 0.5f;
        p_FixtureDef->friction = friction;
        p_FixtureDef->filter.categoryBits = categoryBits;
        p_FixtureDef->filter.maskBits = maskBits;

        p_Body->CreateFixture(p_FixtureDef);

        p_PhysicsScene->AttachBody(p_Body);

        /* Assigns the shape to the pointer */
        p_Circle = new Circle(radius, Vector2(0, 0));
    }

    void Rigidbody2D::CreateWorldBox(Vector2 Dimensions, Vector2 pos, uint16 categoryBits, uint16 maskBits)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Box;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x, pos.y);

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
        /* Creates the shape */
        PolygonShape dynamicBox;
        /* Sets the shape as a box */
        dynamicBox.SetAsBox(Dimensions.x / 2.0f, Dimensions.y / 2.0f);

        /* Creates a fixtureDef and assigns all variables */
        p_FixtureDef->shape = &dynamicBox;
        p_FixtureDef->density = 1.0f;
        p_FixtureDef->friction = 0.5f;
        p_FixtureDef->filter.categoryBits = categoryBits;
        p_FixtureDef->filter.maskBits = maskBits;

        p_Body->CreateFixture(p_FixtureDef);

        p_PhysicsScene->AttachBody(p_Body);

        /* Assigns the shape to the pointer */
        p_Box = new Box(Dimensions, Vector2(0, 0));
    }

    void Rigidbody2D::CreateWorldBox(Vector2 Dimensions, float friction, Vector2 pos, uint16 categoryBits, uint16 maskBits)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Box;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pos.x, pos.y);

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
        /* Creates the shape */
        PolygonShape dynamicBox;
        /* Sets the shape as a box */
        dynamicBox.SetAsBox(Dimensions.x / 2.0f, Dimensions.y / 2.0f);

        /* Creates a fixtureDef and assigns all variables */
        p_FixtureDef->shape = &dynamicBox;
        p_FixtureDef->density = 1.0f;
        p_FixtureDef->friction = friction;
        p_FixtureDef->filter.categoryBits = categoryBits;
        p_FixtureDef->filter.maskBits = maskBits;

        p_Body->CreateFixture(p_FixtureDef);

        p_PhysicsScene->AttachBody(p_Body);

        /* Assigns the shape to the pointer */
        p_Box = new Box(Dimensions, Vector2(0, 0));
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
        if (p_Box != nullptr)
        {
            /* Checks if the object is not static */
            if (p_Body->GetType() != b2_staticBody)
            {
                float max = 5.0f;
                Vector2 direction = Vector2(0, -1);
                p_RayData = Physics::OnRayCast(Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y), direction, p_Body, max);

                if (p_RayData->closestFraction == 1.0f)
                {
                    p_RayData->intersectionPoint = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y + -1 * 1.0f);
                }
                
                float distance = glm::length(p_RayData->intersectionPoint - Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y + (p_Box->GetHeight() * 0.5f) * direction.y));
                if (distance < 0.075f)
                {
                    OnApplyForce(Vector2(0, 1 - distance / 1.0f));
                }

                #ifdef KROSS_DEBUG
                lines->SetColour(Vector3(1, 1, 1));
                lines->DrawLineSegment(Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y), p_RayData->intersectionPoint);
                lines->DrawCircle(p_RayData->intersectionPoint, 0.05f, 6);
                #endif // KROSS_DEBUG


                /* Gets the object position and updates it with the position of the body */
                GetObject()->GetTransform()->m_Position = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y);

                /* Gets the object rotation and updates it with the angle of the body */
                GetObject()->GetTransform()->m_Rotation = glm::degrees(p_Body->GetAngle());

            }
        }
        else if (p_Circle != nullptr)
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

    void Rigidbody2D::SetFriction(float friction)
    {
        
    }

    float Rigidbody2D::GetFriction(Object* target)
    {
        return 0.0f;
    }

}