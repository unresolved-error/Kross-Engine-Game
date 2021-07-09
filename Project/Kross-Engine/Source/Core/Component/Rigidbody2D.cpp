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
    Rigidbody2D::Rigidbody2D() :
        p_Body              (nullptr),
        p_PhysicsScene      (nullptr),
        p_Box               (nullptr),
        p_Circle            (nullptr),
        m_ShapeType         (ShapeType::Count),
        m_CollisionState    (CollisionState::None),
        p_FixtureDef        (KROSS_NEW FixtureDef()),
        p_MassData          (KROSS_NEW b2MassData()),
        p_RayData           (KROSS_NEW RaycastData()),
        p_Filter            (KROSS_NEW ContactFilter()),
        p_AABBCollisionData (KROSS_NEW AABBCollisionData())
    {}

    Rigidbody2D::~Rigidbody2D()
    {
        p_Body = nullptr;
        p_PhysicsScene = nullptr;

        delete p_Circle;
        delete p_Box;

        delete p_MassData;
        delete p_RayData;
        delete p_FixtureDef;

        delete p_Filter;
        delete p_AABBCollisionData;
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
        p_Body->SetUserData(GetLinkObject());

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
        p_Circle = KROSS_NEW Circle(radius, Vector2(0, 0));
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
        p_Body->SetUserData(GetLinkObject());

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
        p_Circle = KROSS_NEW Circle(radius, Vector2(0, 0));
    }

    void Rigidbody2D::CreateDynamicBox(Vector2 Dimensions, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Box;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        //bodyDef.linearDamping = 2.0f;

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
        p_Body->SetUserData(GetLinkObject());

        /* Creates the shape */
        PolygonShape dynamicBox;
        /* Sets the shape as a box */
        dynamicBox.SetAsBox(Dimensions.x * 0.5f, Dimensions.y * 0.5f);

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
        p_Box = KROSS_NEW Box(Dimensions, Vector2(0, 0));
    }

    void Rigidbody2D::CreateDynamicBox(Vector2 Dimensions, float friction, Vector2 pos, bool fixedRotation, uint16 categoryBits, uint16 maskBits)
    {
        /* Sets the shape type */
        m_ShapeType = ShapeType::Box;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        //bodyDef.linearDamping = 2.0f;

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
        p_Body->SetUserData(GetLinkObject());

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
        p_Box = KROSS_NEW Box(Dimensions, Vector2(0, 0));
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
        p_Body->SetUserData(GetLinkObject());

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
        p_Circle = KROSS_NEW Circle(radius, Vector2(0, 0));
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
        p_Body->SetUserData(GetLinkObject());

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
        p_Circle = KROSS_NEW Circle(radius, Vector2(0, 0));
    }

    void Rigidbody2D::CreateWorldBox(Vector2 Dimensions, Vector2 pos, uint16 categoryBits, uint16 maskBits)
    {
        if (!m_TileMap)
        {
            /* Sets the shape type */
            m_ShapeType = ShapeType::Box;

            /* Create a bodyDef and set the variables */
            BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(pos.x, pos.y);

            /* Creates the body and assigns it to the pointer */
            p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
            p_Body->SetUserData(GetLinkObject());

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
            p_Box = KROSS_NEW Box(Dimensions, Vector2(0, 0));

        }
        else
        {
            /* Sets the shape type */
            m_ShapeType = ShapeType::Box;

            /* Create a bodyDef and set the variables */
            BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(pos.x, pos.y);

            Body* tempBody;
            FixtureDef* tempFixture = KROSS_NEW FixtureDef();
            Box* tempBox;

            /* Creates the body and assigns it to the pointer */
            tempBody = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
            tempBody->SetUserData(GetLinkObject());
            /* Creates the shape */
            PolygonShape dynamicBox;
            /* Sets the shape as a box */
            dynamicBox.SetAsBox(Dimensions.x / 2.0f, Dimensions.y / 2.0f);

            /* Creates a fixtureDef and assigns all variables */
            tempFixture->shape = &dynamicBox;
            tempFixture->density = 1.0f;
            tempFixture->friction = 0.5f;
            tempFixture->filter.categoryBits = categoryBits;
            tempFixture->filter.maskBits = maskBits;

            tempBody->CreateFixture(tempFixture);

            p_PhysicsScene->AttachBody(tempBody);

            /* Assigns the shape to the pointer */
            tempBox = KROSS_NEW Box(Dimensions, Vector2(0, 0));

            m_TileShapes.push_back(tempBox);
            m_Fixtures.push_back(tempFixture);
            m_TileColliders.push_back(tempBody);
        }
    }

    void Rigidbody2D::CreateWorldBox(Vector2 Dimensions, float friction, Vector2 pos, uint16 categoryBits, uint16 maskBits)
    {
        if (!m_TileMap)
        {
            /* Sets the shape type */
            m_ShapeType = ShapeType::Box;

            /* Create a bodyDef and set the variables */
            BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(pos.x, pos.y);

            /* Creates the body and assigns it to the pointer */
            p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
            p_Body->SetUserData(GetLinkObject());
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
            p_Box = KROSS_NEW Box(Dimensions, Vector2(0, 0));
        }
        else
        {
            /* Sets the shape type */
            m_ShapeType = ShapeType::Box;

            /* Create a bodyDef and set the variables */
            BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(pos.x, pos.y);

            Body* tempBody;
            FixtureDef* tempFixture = KROSS_NEW FixtureDef();
            Box* tempBox;

            /* Creates the body and assigns it to the pointer */
            tempBody = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
            tempBody->SetUserData(GetLinkObject());
            /* Creates the shape */
            PolygonShape dynamicBox;
            /* Sets the shape as a box */
            dynamicBox.SetAsBox(Dimensions.x * 0.5f, Dimensions.y * 0.5f);

            /* Creates a fixtureDef and assigns all variables */
            tempFixture->shape = &dynamicBox;
            tempFixture->density = 1.0f;
            tempFixture->friction = friction;
            tempFixture->filter.categoryBits = categoryBits;
            tempFixture->filter.maskBits = maskBits;

            tempBody->CreateFixture(tempFixture);

            p_PhysicsScene->AttachBody(tempBody);

            /* Assigns the shape to the pointer */
            tempBox = KROSS_NEW Box(Dimensions, Vector2(0, 0));
            
            m_TileShapes.push_back(tempBox);
            m_Fixtures.push_back(tempFixture);
            m_TileColliders.push_back(tempBody);
        }
    }

    void Rigidbody2D::OnStart()
    {
        /* Gets the body */
        p_Body = GetBody();

        /* Gets the physics scene */
        p_PhysicsScene = GetPhysicsScene();

        /* Send Draw Information. */
        if (m_TileColliders.size() > 0)
        {
            for (int i = 0; i < m_TileColliders.size(); i++)
            {
                p_DebugRenderer->DrawRigidBody(m_TileColliders[i]);
            }
        }
        else
        {
            p_DebugRenderer->DrawRigidBody(p_Body);
        }
    }

    void Rigidbody2D::OnUpdateDrawInformation() const
    {
        if (!m_TileMap)
        {
            p_DebugRenderer->DrawRigidBody(p_Body);
        }
        else
        {
            for (int i = 0; i < m_TileColliders.size(); i++)
            {
                p_DebugRenderer->DrawRigidBody(m_TileColliders[i]);
            }
        }
    }

    void Rigidbody2D::OnUpdate()
    {
        float circleCastRad = 0.075f;
        
        if (p_Box != nullptr)
        {
            /* Checks if the object is not static */
            if (p_Body->GetType() != b2_staticBody)
            {
                Vector2 particleForce = CollideParticles();

                if (p_AABBCollisionData->m_Collision)
                {
                    // player is swimming
                    OnApplyForce(particleForce * (p_Body->GetMass() * 0.5f));
                }

                float footSpringLength = 0.5f;

                GetSurroundingObjects(2.0f, p_Body);
                

                float distance = CalculateRayLength(footSpringLength, Vector2(0.0f, -1.0f),
                    GetVector2(p_Body->GetPosition()));

                if (p_RayData->hit)
                {
                    if (m_CollisionState == CollisionState::None)
                        m_CollisionState = CollisionState::Enter;

                    else if (m_CollisionState == CollisionState::Enter)
                        m_CollisionState = CollisionState::Stay;

                    //OnApplyForce(SpringCalculation(p_Body, p_RayData->body, distance) * p_RayData->intersectionNormal);

                    p_RayData->hit = false;
                }
                else
                {
                    p_RayData->intersectionPoint = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y - footSpringLength);

                    if (m_CollisionState == CollisionState::Enter || m_CollisionState == CollisionState::Stay)
                        m_CollisionState = CollisionState::Exit;

                    else if (m_CollisionState == CollisionState::Exit)
                        m_CollisionState = CollisionState::None;
                }
                
                /* Gets the object position and updates it with the position of the body */
                GetLinkObject()->GetTransform()->m_Position = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y);

                /* Gets the object rotation and updates it with the angle of the body */
                GetLinkObject()->GetTransform()->m_Rotation = glm::degrees(p_Body->GetAngle());

                p_DebugRenderer->DrawLineSegment(GetVector2(p_Body->GetPosition()), p_RayData->intersectionPoint);
                p_DebugRenderer->DrawCircle(p_RayData->intersectionPoint, circleCastRad, 8);
            }
        }
        else if (p_Circle != nullptr)
        {
            /* Checks if the object is not static */
            if (p_Body->GetType() != b2_staticBody)
            {
                Vector2 particleForce = CollideParticles();

                if (p_AABBCollisionData->m_Collision)
                {
                    // player is swimming
                    OnApplyForce(particleForce * (p_Body->GetMass() * 0.5f));
                }

                /* Gets the object position and updates it with the position of the body */
                GetLinkObject()->GetTransform()->m_Position = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y);
            
                /* Gets the object rotation and updates it with the angle of the body */
                GetLinkObject()->GetTransform()->m_Rotation = glm::degrees(p_Body->GetAngle());

                p_DebugRenderer->DrawLineSegment(GetVector2(p_Body->GetPosition()), p_RayData->intersectionPoint);
                p_DebugRenderer->DrawCircle(p_RayData->intersectionPoint, circleCastRad, 8);
            }
        }

        m_AABBCollisions.clear();
        m_CloseObjects.clear();

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

    Vector2 Rigidbody2D::GetPosition() const
    {
        return Vector2(GetLinkObject()->GetTransform()->m_Position.x, GetLinkObject()->GetTransform()->m_Position.y);
    }
    
    Vector2 Rigidbody2D::SpringCalculation(Body* body1, Body* body2, float dist)
    {
        Vector2 fs = { 0,0 };
        Vector2 velocity = { 0,0 };
        Vector2 acceleration = { 0,0 };
        float mass = 0.0f;

        Vector2 pos1 = Vector2(body1->GetPosition().x, body1->GetPosition().y);
        Vector2 pos2 = p_RayData->intersectionPoint;
        float distance = glm::length(pos2 - pos1);

        float distanceScale = 10.0f;
        float springConstant = 0.75f;
        float dampingConstant = 11.0f;
        float restLength = 0.55f;
        float size = 0.35f;

        float scalar = distanceScale * springConstant * (size - restLength);
        Vector2 direction = p_RayData->intersectionNormal;
        
        float s1 = glm::dot(Vector2(body1->GetLinearVelocity().x, body1->GetLinearVelocity().y), direction);
        float s2 = glm::dot(Vector2(body2->GetLinearVelocity().x, body2->GetLinearVelocity().y), direction);
        
        float dampingScalar = -dampingConstant * (s1 + s2);
        
        if (body1->GetMass() == 0)
        {
            fs = (scalar + dampingScalar) * direction;
            mass = body2->GetMass();
        }
        else
        {
            fs = (-scalar + dampingScalar) * direction;
            mass = body1->GetMass();
        }
        
        Vector2 fg = Vector2(Vector2(body1->GetWorld()->GetGravity().x, body1->GetWorld()->GetGravity().y) * mass);
        Vector2 force = fs + fg;

        return (springConstant * (size - distance)) * force;

    }

    Vector2 Rigidbody2D::CollideParticles()
    {
        Vector2 totalVelocity(0, 0);
        Vector2 averageVelocity(0, 0);
        int particleCount = 0;

        for (int i = 0; i < p_PhysicsScene->GetParticleSystem().size(); i++)
        {
            Physics::GetAABBCollisionCallback()->SetAABBCollisionData(p_AABBCollisionData);
            const b2Shape* shape = p_Body->GetFixtureList()->GetShape();

            p_PhysicsScene->GetParticleSystem()[i]->QueryShapeAABB(Physics::GetAABBCollisionCallback(),
                *(b2Shape*)shape, p_Body->GetTransform());
            p_AABBCollisionData = Physics::GetAABBCollisionCallback()->GetAABBCollisionData();

            particleCount = p_AABBCollisionData->m_ParticleIndexs.size();
        }

        if (particleCount != 0)
        {
            p_AABBCollisionData->m_Collision = true;

            averageVelocity = Vector2(0, 0);
            totalVelocity = Vector2(0, 0);

            for (int j = 0; j < p_AABBCollisionData->m_ParticleIndexs.size(); j++)
            {
                Vector2 particleVelocity = Vector2(p_AABBCollisionData->p_ParticleSystem->GetVelocityBuffer()[p_AABBCollisionData->m_ParticleIndexs[j]].x,
                    p_AABBCollisionData->p_ParticleSystem->GetVelocityBuffer()[p_AABBCollisionData->m_ParticleIndexs[j]].y);

                totalVelocity += particleVelocity;
            }

            p_AABBCollisionData->m_ParticleIndexs.clear();
            averageVelocity = glm::normalize(Vector2(totalVelocity.x / particleCount, totalVelocity.y / particleCount));
            particleCount = 0;
        }
        else
        {
            p_AABBCollisionData->m_Collision = false;
            averageVelocity = Vector2(0, 0);
        }
        
        return averageVelocity;
    }

    float Rigidbody2D::CalculateRayLength(float maxFraction, Vector2 direction, Vector2 pos)
    {
        p_RayData->maxFraction = maxFraction;
        p_RayData->direction = direction;
        p_RayData->pos = pos;

        p_RayData = Physics::OnRayCast(p_RayData->pos, p_RayData->direction, p_Body, p_RayData->maxFraction);

        return glm::length(p_RayData->intersectionPoint - GetVector2(p_Body->GetPosition()));
    }

    float Rigidbody2D::CalculateCircleCast(float circleCastRadius, float maxFraction, Vector2 direction, Vector2 pos)
    {
        List<RaycastData*> outputs;
        float closestFraction = 0;

        p_RayData->maxFraction = maxFraction;

        p_RayData->pos = pos;
        p_RayData->direction = direction;
        p_RayData->intersectionPoint = pos + maxFraction * direction;

        GetSurroundingObjects(2.0f, p_Body);

        for (int i = 0; i < p_AABBCollisionData->m_Fixture.size(); i++)
        {
            if (p_AABBCollisionData->m_Fixture[i]->GetBody() != p_Body)
            {
                p_RayData = Physics::OnCircleCast(p_RayData->pos, p_RayData->direction,
                    p_Body, p_RayData->maxFraction, circleCastRadius);

                if (p_RayData->hit == true)
                {
                    p_RayData->body = p_AABBCollisionData->m_Fixture[i]->GetBody();
                    outputs.push_back(p_RayData);
                }
            }
        }
        

        p_AABBCollisionData->m_Fixture.clear();
        outputs.clear();
        
        return closestFraction;
    }

    void Rigidbody2D::GetSurroundingObjects(float size, Body* body)
    {
        Physics::GetAABBCollisionCallback()->SetAABBCollisionData(p_AABBCollisionData);
        b2Shape* shape = body->GetFixtureList()->GetShape();

        /* Checks if it is a circle */
        if (shape->m_type == 0)
        {
            CircleShape circle = CircleShape();
            circle.m_radius += p_Circle->GetRadius() + size;

            /* Queries shape AABB */
            p_PhysicsScene->GetPhysicsWorld()->QueryShapeAABB(Physics::GetAABBCollisionCallback(),
                circle, body->GetTransform());
        }
        /* Checks if it is a poly */
        else if (shape->m_type == 2)
        {
            PolygonShape box = PolygonShape();
            box.SetAsBox(p_Box->GetWidth() + size, p_Box->GetHeight() + size);

            /* Queries shape AABB */
            p_PhysicsScene->GetPhysicsWorld()->QueryShapeAABB(Physics::GetAABBCollisionCallback(),
                box, body->GetTransform());
        }


        p_AABBCollisionData = Physics::GetAABBCollisionCallback()->GetAABBCollisionData();

        m_AABBCollisions.push_back(p_AABBCollisionData);


        /* Goes through all of the fixtures and pushes them into a list */
        for (int i = 0; i < m_AABBCollisions.size(); i++)
        {
            for (int j = 0; j < m_AABBCollisions[i]->m_Fixture.size(); j++)
            {
                /* Checks if the current fixture body is the same as the current body */
                if (m_AABBCollisions[i]->m_Fixture[j]->GetBody() != p_Body)
                {
                    m_CloseObjects.push_back(m_AABBCollisions[i]->m_Fixture[j]->GetBody());
                }
            }
        }

        //for (int i = 0; i < m_CloseObjects.size(); i++)
        //{
        //    std::cout << m_CloseObjects[i] << std::endl;
        //}

        p_AABBCollisionData->m_Fixture.clear();
    }

    void Rigidbody2D::CreateTileMapColliders(TileMap* tileMap, List<Tile*> tiles)
    {
        m_TileMap = true;
        List<Vector2> tilePosition;
        List<Vector4> tileColliders;
        Vector2 dimensions = tiles[0]->p_Sprite->GetGeometry()->GetSize();
        float width = 0;
        float height = 0;


        for (int i = 0; i < tiles.size(); i++)
        {
            Vector2 pos = GetLinkObject()->GetTransform()->m_Position + tiles[i]->m_Offset;
            tilePosition.push_back(pos);
        }
        
        Vector2 firstTile = Vector2(0,0);
        Vector2 previous = tilePosition[0];
        int colliderCount = 0;

        /* Rows */
        for (int i = 0; i <= tilePosition.size(); i++)
        {
            if (colliderCount == 0)
            {
                firstTile = previous;
                //tileColliders.push_back(Vector4(previous.x - dimensions.x, previous.y + dimensions.y,
                //    tilePosition[i].x + dimensions.x, tilePosition[i].y - dimensions.y));
                colliderCount++;
            }
            if (tilePosition[i].x - previous.x == dimensions.x && tilePosition[i].y == previous.y)
            {
                colliderCount++;
            }
            else
            {
                if (colliderCount != 0)
                {
                    width = (firstTile.x + (dimensions.x * colliderCount)) - firstTile.x;
                    tileColliders.push_back(Vector4(width - 0.05f, dimensions.y, (firstTile.x + (width * 0.5f)) - dimensions.x * 0.5f, firstTile.y));
                    colliderCount = 0;
                }
            }
            previous = tilePosition[i];
        }
        
        //previous = tilePosition[0];
        //colliderCount = 0;
        //List<int> index;
        ///* Collums */
        //for (int i = 0; i <= tilePosition.size(); i++)
        //{
        //    for (int j = 0; j < tilePosition.size(); j++)
        //    {
        //        if (colliderCount == 0)
        //        {
        //            firstTile = previous;
        //            colliderCount++;
        //        }
        //
        //        if (tilePosition[j].x == previous.x)
        //        {
        //            if (tilePosition[j].y - tilePosition[i].y == dimensions.y)
        //            {
        //                colliderCount++;
        //            }
        //            else
        //            {
        //                if (colliderCount != 0)
        //                {
        //                    height = (firstTile.y + (dimensions.y * colliderCount)) - firstTile.y;
        //                    tileColliders.push_back(Vector4(dimensions.x, height, firstTile.x, (firstTile.y + (height * 0.5f)) - dimensions.y * 0.5f));
        //                    colliderCount = 0;
        //                }
        //            }
        //
        //            previous = tilePosition[i];
        //        }
        //    }
        //}


        for (int i = 0; i < tileColliders.size(); i++)
        {
            CreateWorldBox(Vector2(tileColliders[i].x, tileColliders[i].y), 0.5f, Vector2(tileColliders[i].z, tileColliders[i].w),
                ColliderFilters::Environment, ColliderFilters::Player | ColliderFilters::Fluid);
        }
    }

    float Rigidbody2D::GetFriction()
    {
        return p_Body->GetFixtureList()->GetFriction();
    }
}
