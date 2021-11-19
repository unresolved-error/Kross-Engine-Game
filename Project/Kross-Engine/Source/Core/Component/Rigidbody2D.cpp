/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
 *      - Chris Deitch
 */

#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/Time.h"
#include "Rigidbody2D.h"

namespace Kross
{
    Rigidbody2D::Rigidbody2D() :
        p_Body              (nullptr),
        p_PhysicsScene      (nullptr),
        p_Box               (nullptr),
        p_Capsule           (nullptr),
        p_Circle            (nullptr),
        p_DebugRenderer     (nullptr),
        p_RevJoint          (nullptr),
        m_ShapeType         (ShapeType::Count),
        m_CollisionState    (CollisionState::None),
        m_RigidbodyState    (RigidbodyState::Idle),
        m_ColliderFilter    (ColliderFilters::Default),
        p_Filter            (KROSS_NEW b2Filter),
        p_RayData           (KROSS_NEW RaycastData()),
        p_AABBCollisionData (KROSS_NEW AABBCollisionData())
    {}

    Rigidbody2D::~Rigidbody2D()
    {
        if (p_Body)
        {
            p_PhysicsScene->DetachBody(p_Body);
        }
        else
        {
            std::cout << "Body was null\n";
        }

        p_Body = nullptr;
        p_RayData = nullptr;
        p_PhysicsScene = nullptr;

        delete p_Circle;
        delete p_Box;
        delete p_Capsule;
        
        delete p_Filter;
        delete p_AABBCollisionData;
    }

    void Rigidbody2D::CreateDynamicCircle(float radius, Vector2 pos, bool fixedRotation, b2Filter* filter, float friction, float density)
    {
        SetFriction(friction);
        /* Sets the shape type */
        m_ShapeType = ShapeType::Circle;
        
        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        bodyDef.bullet = m_IsBullet;
        
        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
        p_Body->SetUserData(m_GameObject);
        
        p_Body->SetFixedRotation(fixedRotation);
        
        /* Creates the cirlce */
        CircleShape circleShape;
        /* Sets the circles radius */
        circleShape.m_radius = radius;
        
        /* Creates a fixtureDef and assigns the variables */
        FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.density = density;
        fixtureDef.friction = m_Friction;
        fixtureDef.filter = *filter;
        
        p_Body->CreateFixture(&fixtureDef);
        
        m_Bodies.push_back(p_Body);
        p_PhysicsScene->AttachBody(p_Body);
        
        /* Assigns the shape to the pointer */
        p_Circle = KROSS_NEW Circle(radius, Vector2(0, 0));
    }

    void Rigidbody2D::CreateDynamicBox(Vector2 dimensions, Vector2 pos, bool fixedRotation, b2Filter* filter, float friction)
    {
        SetFriction(friction);
        /* Sets the shape type */
        m_ShapeType = ShapeType::Box;

        /* Create a bodyDef and set the variables */
        BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
        p_Body->SetUserData(m_GameObject);

        /* Creates the shape */
        PolygonShape dynamicBox;
        /* Sets the shape as a box */
        dynamicBox.SetAsBox(dimensions.x * 0.5f, dimensions.y * 0.5f);

        /* Creates a fixtureDef and assigns all variables */
        FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = m_Friction;
        fixtureDef.filter = *filter;

        p_Body->CreateFixture(&fixtureDef);
        p_Body->SetFixedRotation(fixedRotation);

        m_Bodies.push_back(p_Body);
        p_PhysicsScene->AttachBody(p_Body);

        /* Assigns the shape to the pointer */
        p_Box = KROSS_NEW Box(dimensions, Vector2(0, 0));
    }

    void Rigidbody2D::CreateDynamicCapsule(Vector2 dimensions, Vector2 pos, bool fixedRotation, b2Filter* filter, float friction)
    {
        SetFriction(friction);
        /* Set the shape type */
        m_ShapeType = ShapeType::Capsule;

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x, pos.y);
        bodyDef.fixedRotation = true;

        /* Creates the body and assigns it to the pointer */
        p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
        p_Body->SetUserData(m_GameObject);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox((dimensions.x * 0.5f) - (dimensions.x * 0.05f), (dimensions.y - dimensions.x) * 0.5f);

        b2FixtureDef boxFixtureDef;
        boxFixtureDef.shape = &dynamicBox;
        boxFixtureDef.density = 0.5f;
        boxFixtureDef.friction = m_Friction;
        boxFixtureDef.filter = *filter;

        p_Body->CreateFixture(&boxFixtureDef);

        /* Top circle */
        b2CircleShape topCircleShape;
        topCircleShape.m_radius = (dimensions.x * 0.5f) + 0.005f;
        topCircleShape.m_p.Set(0.0f, (dimensions.y - dimensions.x) * 0.5f);

        b2FixtureDef topFixtureDef;
        topFixtureDef.shape = &topCircleShape;
        topFixtureDef.density = 0.5f;
        topFixtureDef.friction = m_Friction;
        topFixtureDef.filter = *filter;

        p_Body->CreateFixture(&topFixtureDef);

        p_Body->SetFixedRotation(fixedRotation);

        m_Bodies.push_back(p_Body);
        p_PhysicsScene->AttachBody(p_Body);


        /* bottom circle */
        b2BodyDef BottomCircleDef;
        BottomCircleDef.type = b2_dynamicBody;
        BottomCircleDef.position.Set(pos.x, (-dimensions.y + dimensions.x) * 0.5f);
        BottomCircleDef.fixedRotation = false;

        Body* bottomCircle = nullptr;
        bottomCircle = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&BottomCircleDef);
        bottomCircle->SetUserData(m_GameObject);

        b2CircleShape circleShape;
        circleShape.m_radius = (dimensions.x * 0.5f);

        b2FixtureDef bottomFixtureDef;
        bottomFixtureDef.shape = &circleShape;
        bottomFixtureDef.density = 0.5f;
        bottomFixtureDef.friction = 5.0f;
        bottomFixtureDef.filter = *filter;

        bottomCircle->CreateFixture(&bottomFixtureDef);

        bottomCircle->SetFixedRotation(false);

        m_Bodies.push_back(bottomCircle);
        p_PhysicsScene->AttachBody(bottomCircle);

        /* Creates the rev joint for the player */
        b2RevoluteJointDef revJoint;

        revJoint.bodyA = p_Body;
        revJoint.localAnchorA.Set(0.0f,0.0f);

        revJoint.bodyB = bottomCircle;
        revJoint.localAnchorB.Set(0.0f, 0.0f);

        revJoint.collideConnected = false;

        CreateRevJoint(revJoint);
        p_RevJoint->SetMaxMotorTorque(0.1f);
        p_RevJoint->EnableMotor(true);
        p_RevJoint->EnableLimit(false);


        ///* This is for display purposes */
        ///* Start of Jakes BS */
        //b2BodyDef RotationDisplay;
        //RotationDisplay.type = b2_dynamicBody;
        //RotationDisplay.position.Set(circleShape.m_p.x + circleShape.m_radius, circleShape.m_p.y);
        //RotationDisplay.fixedRotation = false;
        //
        //Body* bottomCircleDisplay = nullptr;
        //bottomCircleDisplay = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&RotationDisplay);
        //bottomCircleDisplay->SetUserData(m_GameObject);
        //
        //b2CircleShape circleShape2;
        //circleShape2.m_radius = dimensions.x * 0.25f;
        //
        //b2FixtureDef bottomFixtureDef2;
        //bottomFixtureDef2.shape = &circleShape2;
        //bottomFixtureDef2.density = 0.01f;
        //bottomFixtureDef2.filter.categoryBits = (uint16)ColliderFilters::Empty;
        //bottomFixtureDef2.filter.maskBits = (uint16)ColliderFilters::Empty;
        //
        //bottomCircleDisplay->CreateFixture(&bottomFixtureDef2);
        //
        //bottomCircleDisplay->SetFixedRotation(false);
        //
        //m_Bodies.push_back(bottomCircleDisplay);
        //p_PhysicsScene->AttachBody(bottomCircleDisplay);
        //
        //b2WeldJointDef weldJointDef;
        //weldJointDef.bodyA = bottomCircleDisplay;
        //weldJointDef.localAnchorA.Set(0.0f, 0.0f);
        //
        //weldJointDef.bodyB = bottomCircle;
        //weldJointDef.localAnchorB.Set(0.5f, 0.0f);
        //
        //weldJointDef.collideConnected = false;
        //
        //p_PhysicsScene->GetPhysicsWorld()->CreateJoint(&weldJointDef);
        ///* End of Jakes BS */

        p_Capsule = KROSS_NEW Capsule(dimensions, Vector2(0,0), m_Fixtures);
    }

    void Rigidbody2D::CreateWorldCircle(float radius, Vector2 pos, b2Filter* filter, float friction)
    {
        SetFriction(friction);
        if (!GetComponent<Collider>()->IsTileMapCollider())
        {
            /* Sets the shape type */
            m_ShapeType = ShapeType::Circle;

            /* Create a bodyDef and set the variables */
            BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(pos.x, pos.y);

            /* Creates the body and assigns it to the pointer */
            p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
            p_Body->SetUserData(m_GameObject);

            /* Creates the cirlce */
            CircleShape circleShape;
            /* Sets the circles radius */
            circleShape.m_radius = radius;

            /* Creates a fixtureDef and assigns the variables */
            FixtureDef fixtureDef;
            fixtureDef.shape = &circleShape;
            fixtureDef.density = 0.5f;
            fixtureDef.friction = m_Friction;
            fixtureDef.filter = *filter;

            p_Body->CreateFixture(&fixtureDef);

            p_PhysicsScene->AttachBody(p_Body);

            /* Assigns the shape to the pointer */
            p_Circle = KROSS_NEW Circle(radius, Vector2(0, 0));
        }
        else
        {
            /* Sets the shape type */
            m_ShapeType = ShapeType::Circle;

            /* Create a bodyDef and set the variables */
            BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(pos.x, pos.y);

            Body* tempBody;
            FixtureDef* tempFixture = KROSS_NEW FixtureDef();
            /* Creates the body and assigns it to the pointer */
            tempBody = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
            tempBody->SetUserData(m_GameObject);

            /* Creates the cirlce */
            CircleShape circleShape;
            /* Sets the circles radius */
            circleShape.m_radius = radius;

            /* Creates a fixtureDef and assigns the variables */
            tempFixture->shape = &circleShape;
            tempFixture->density = 0.5f;
            tempFixture->friction = m_Friction;
            tempFixture->filter = *filter;

            tempBody->CreateFixture(tempFixture);

            p_PhysicsScene->AttachBody(tempBody);

            /* Assigns the shape to the pointer */
            Circle* tempCircle = KROSS_NEW Circle(radius, Vector2(0, 0));

            m_TileCornerShapes.push_back(tempCircle);
            m_Fixtures.push_back(tempFixture);
            m_TileColliders.push_back(tempBody);
        }
    }

    void Rigidbody2D::CreateWorldBox(Vector2 Dimensions, Vector2 pos, b2Filter* filter, float friction)
    {
        SetFriction(friction);
        if (!GetComponent<Collider>()->IsTileMapCollider())
        {
            /* Sets the shape type */
            m_ShapeType = ShapeType::Box;

            /* Create a bodyDef and set the variables */
            BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.position.Set(pos.x, pos.y);

            /* Creates the body and assigns it to the pointer */
            p_Body = p_PhysicsScene->GetPhysicsWorld()->CreateBody(&bodyDef);
            p_Body->SetUserData(m_GameObject);

            /* Creates the shape */
            PolygonShape dynamicBox;
            /* Sets the shape as a box */
            dynamicBox.SetAsBox(Dimensions.x / 2.0f, Dimensions.y / 2.0f);

            /* Creates a fixtureDef and assigns all variables */
            FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = m_Friction;
            fixtureDef.filter = *filter;

            p_Body->CreateFixture(&fixtureDef);

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
            tempBody->SetUserData(m_GameObject);
            /* Creates the shape */
            PolygonShape dynamicBox;
            /* Sets the shape as a box */
            dynamicBox.SetAsBox(Dimensions.x * 0.5f, Dimensions.y * 0.5f);

            /* Creates a fixtureDef and assigns all variables */
            tempFixture->shape = &dynamicBox;
            tempFixture->density = 1.0f;
            tempFixture->friction = m_Friction;
            tempFixture->filter = *filter;

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
        Collider* collider = GetComponent<Collider>();

        //TODO: Add Collider Filter Data to Collider.
        SetColliderFilter(collider->GetCollisionFilters());

        

        if (!collider->IsTileMapCollider())
        {
           

            switch (collider->GetShapeType())
            {
            case Kross::ShapeType::Box:
            {
                if (collider->IsStatic())
                {
                    CreateWorldBox(Vector2(collider->GetWidth(), collider->GetHeight()), m_GameObject->m_Transform->m_Position,
                        GetColliderFilters(), collider->GetFriction());
                }
                else
                {
                    CreateDynamicBox(Vector2(collider->GetWidth(), collider->GetHeight()), m_GameObject->m_Transform->m_Position, collider->IsRotationLocked(),
                        GetColliderFilters(), collider->GetFriction());
                }
                break;
            }
            case Kross::ShapeType::Circle:
            {
                if (collider->IsStatic())
                {
                    CreateWorldCircle(collider->GetRadius(), m_GameObject->m_Transform->m_Position, GetColliderFilters(), collider->GetFriction());
                }
                else
                {
                    CreateDynamicCircle(collider->GetRadius(), m_GameObject->m_Transform->m_Position, collider->IsRotationLocked(),
                        GetColliderFilters(), collider->GetFriction(), collider->GetDensity());
                }
                break;
            }
            case Kross::ShapeType::Capsule:
            {
                CreateDynamicCapsule(Vector2(collider->GetWidth(), collider->GetHeight()), m_GameObject->m_Transform->m_Position, collider->IsRotationLocked(),
                    GetColliderFilters(), collider->GetFriction());
                break;
            }
            }
        }
        else
        {
            TileMapRenderer* rend = GetComponent<TileMapRenderer>();
            if (rend)
            {
                CreateTileMapColliders(rend->GetTileMap(), rend->GetTileList()[0]);
            }
        }

        /* Gets the body */
        p_Body = GetBody();

        if (p_Body)
        {
            p_Body->SetTransform(Getb2Vec2(m_GameObject->m_Transform->m_Position), glm::radians(m_GameObject->m_Transform->m_Rotation));
        }

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

    void Rigidbody2D::OnUpdateDrawInformation()
    {
        Collider* colliderData = GetComponent<Collider>();

        #ifndef KROSS_EDITOR
        if (!colliderData->IsTileMapCollider())
        {
            if (m_ShapeType == ShapeType::Capsule)
            {
                for (int i = 0; i < m_Bodies.size(); i++)
                {
                    p_DebugRenderer->DrawCapsule(m_Bodies[i], Vector2(p_Capsule->GetWidth(), p_Capsule->GetHeight()));
                }
            }
            else
            {
                p_DebugRenderer->DrawRigidBody(p_Body);
            }
        }
        #else
        if (!colliderData->IsTileMapCollider())
        {
            if (m_ShapeType == ShapeType::Capsule)
            {
                p_DebugRenderer->DrawCapsule(p_Body, Vector2(p_Capsule->GetWidth(), p_Capsule->GetHeight()), 16);
            }
            else
            {
                if (colliderData->IsStatic())
                {
                    Vector3 colour = Vector3(0.0f, 0.0f, 1.0f);
                    Vector2 objectPosition = m_GameObject->m_Transform->m_Position;

                    if (m_ShapeType == ShapeType::Box)
                    {
                        Vector4 topLeft = Vector4(-(colliderData->GetWidth() / 2.0f), (colliderData->GetHeight() / 2.0f), 0.0f, 1.0f);
                        Vector4 topRight = Vector4((colliderData->GetWidth() / 2.0f), (colliderData->GetHeight() / 2.0f), 0.0f, 1.0f);
                        Vector4 bottomLeft = Vector4(-(colliderData->GetWidth() / 2.0f), -(colliderData->GetHeight() / 2.0f), 0.0f, 1.0f);
                        Vector4 bottomRight = Vector4((colliderData->GetWidth() / 2.0f), -(colliderData->GetHeight() / 2.0f), 0.0f, 1.0f);

                        Matrix4 rotationMatrix = Matrix4(1.0f);
                        rotationMatrix = glm::rotate(Matrix4(1.0f), glm::radians(-m_GameObject->m_Transform->m_Rotation), Vector3(0.0f, 0.0f, 1.0f));

                        topLeft = topLeft * rotationMatrix;
                        topRight = topRight * rotationMatrix;
                        bottomLeft = bottomLeft * rotationMatrix;
                        bottomRight = bottomRight * rotationMatrix;

                        p_DebugRenderer->DrawLineSegment(objectPosition + Vector2(topLeft.x, topLeft.y), objectPosition + Vector2(topRight.x, topRight.y), colour);
                        p_DebugRenderer->DrawLineSegment(objectPosition + Vector2(topRight.x, topRight.y), objectPosition + Vector2(bottomRight.x, bottomRight.y), colour);
                        p_DebugRenderer->DrawLineSegment(objectPosition + Vector2(bottomRight.x, bottomRight.y), objectPosition + Vector2(bottomLeft.x, bottomLeft.y), colour);
                        p_DebugRenderer->DrawLineSegment(objectPosition + Vector2(bottomLeft.x, bottomLeft.y), objectPosition + Vector2(topLeft.x, topLeft.y), colour);
                    }
                    else
                    {
                        p_DebugRenderer->DrawCircle(objectPosition, colliderData->GetRadius(), colour);
                    }
                }
                else
                {
                    Vector3 colour = Vector3(0.0f, 1.0f, 0.0f);
                    Vector2 objectPosition = m_GameObject->m_Transform->m_Position;

                    if (m_ShapeType == ShapeType::Box)
                    {

                        Vector4 topLeft = Vector4(-(colliderData->GetWidth() / 2.0f), (colliderData->GetHeight() / 2.0f), 0.0f, 1.0f);
                        Vector4 topRight = Vector4((colliderData->GetWidth() / 2.0f), (colliderData->GetHeight() / 2.0f), 0.0f, 1.0f);
                        Vector4 bottomLeft = Vector4(-(colliderData->GetWidth() / 2.0f), -(colliderData->GetHeight() / 2.0f), 0.0f, 1.0f);
                        Vector4 bottomRight = Vector4((colliderData->GetWidth() / 2.0f), -(colliderData->GetHeight() / 2.0f), 0.0f, 1.0f);

                        Matrix4 rotationMatrix = Matrix4(1.0f);
                        rotationMatrix = glm::rotate(Matrix4(1.0f), glm::radians(-m_GameObject->m_Transform->m_Rotation), Vector3(0.0f, 0.0f, 1.0f));

                        topLeft = topLeft * rotationMatrix;
                        topRight = topRight * rotationMatrix;
                        bottomLeft = bottomLeft * rotationMatrix;
                        bottomRight = bottomRight * rotationMatrix;

                        p_DebugRenderer->DrawLineSegment(objectPosition + Vector2(topLeft.x, topLeft.y), objectPosition + Vector2(topRight.x, topRight.y), colour);
                        p_DebugRenderer->DrawLineSegment(objectPosition + Vector2(topRight.x, topRight.y), objectPosition + Vector2(bottomRight.x, bottomRight.y), colour);
                        p_DebugRenderer->DrawLineSegment(objectPosition + Vector2(bottomRight.x, bottomRight.y), objectPosition + Vector2(bottomLeft.x, bottomLeft.y), colour);
                        p_DebugRenderer->DrawLineSegment(objectPosition + Vector2(bottomLeft.x, bottomLeft.y), objectPosition + Vector2(topLeft.x, topLeft.y), colour);
                    }
                    else
                    {
                        p_DebugRenderer->DrawCircle(objectPosition, colliderData->GetRadius(), colour);
                    }
                }
            }
    }
        #endif
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
        ClearCloseObjects();

        if (p_Box != nullptr || p_Circle != nullptr || p_Capsule != nullptr)
        {
            /* Checks if the object is not static */
            if (p_Body->GetType() != b2_staticBody)
            {
                CollisionUpdate();
            }
        }

        #ifdef KROSS_DEBUG
        OnUpdateDrawInformation();
        #endif
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
        return m_GameObject->m_Transform->m_Position;
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

            particleCount = static_cast<int>(p_AABBCollisionData->m_ParticleIndexs.size());
        }

        if (particleCount != 0)
        {
            p_AABBCollisionData->m_Collision = true;

            averageVelocity = Vector2(0, 0);
            totalVelocity = Vector2(0, 0);

            for (int i = 0; i < p_AABBCollisionData->p_ParticleSystems.size(); i++)
            {
                for (int j = 0; j < p_AABBCollisionData->m_ParticleIndexs.size(); j++)
                {
                    Vector2 particleVelocity = Vector2(p_AABBCollisionData->p_ParticleSystems[i]->GetVelocityBuffer()[(int)p_AABBCollisionData->m_ParticleIndexs[j].y].x,
                        p_AABBCollisionData->p_ParticleSystems[i]->GetVelocityBuffer()[(int)p_AABBCollisionData->m_ParticleIndexs[j].y].y);

                    totalVelocity += particleVelocity;
                }
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

    RaycastData* Rigidbody2D::CalculateRayLength(float maxFraction, Vector2 direction, Vector2 pos)
    {
        p_RayData->maxFraction = maxFraction;
        p_RayData->direction = direction;
        p_RayData->pos = pos;

        p_RayData = Physics::OnRayCast(p_RayData->pos, p_RayData->direction, p_Body, p_RayData->maxFraction);

        return p_RayData;
    }

    std::vector<Body*> Rigidbody2D::GetSurroundingObjects(float size, Body* body)
    {
        AABBCollisionData* collisionData = KROSS_NEW AABBCollisionData;
        Physics::GetAABBCollisionCallback()->SetAABBCollisionData(collisionData);
        b2Shape* shape = body->GetFixtureList()->GetShape();

        for (int i = 0; i < GetCloseObjects().size(); i++)
        {
            GetCloseObjects()[i] = nullptr;
        }
        ClearCloseObjects();

        /* Checks if it is a circle */
        if (p_Circle != nullptr)
        {
            CircleShape circle = CircleShape();
            circle.m_radius += p_Circle->GetRadius() + size;

            /* Queries shape AABB */
            p_PhysicsScene->GetPhysicsWorld()->QueryShapeAABB(Physics::GetAABBCollisionCallback(),
                circle, body->GetTransform());
        }
        /* Checks if it is a poly */
        else if (p_Box != nullptr)
        {
            PolygonShape box = PolygonShape();
            box.SetAsBox((p_Box->GetWidth() + size) * 0.5f, (p_Box->GetHeight() + size) * 0.5f);

            /* Queries shape AABB */
            p_PhysicsScene->GetPhysicsWorld()->QueryShapeAABB(Physics::GetAABBCollisionCallback(),
                box, body->GetTransform());
        }
        else if (p_Capsule != nullptr)
        {
            PolygonShape box = PolygonShape();
            box.SetAsBox((p_Capsule->GetWidth() + size) * 0.5f, (p_Capsule->GetHeight() + size) * 0.5f);

            /* Queries shape AABB */
            p_PhysicsScene->GetPhysicsWorld()->QueryShapeAABB(Physics::GetAABBCollisionCallback(),
                box, body->GetTransform());

            float points[10] = 
            { 
                body->GetTransform().p.x + (p_Capsule->GetWidth() + size) * 0.5f, body->GetTransform().p.y + (p_Capsule->GetHeight() + size) * 0.5f,
                body->GetTransform().p.x + (p_Capsule->GetWidth() + size) * 0.5f, body->GetTransform().p.y - (p_Capsule->GetHeight() + size) * 0.5f,
                body->GetTransform().p.x - (p_Capsule->GetWidth() + size) * 0.5f, body->GetTransform().p.y - (p_Capsule->GetHeight() + size) * 0.5f,
                body->GetTransform().p.x - (p_Capsule->GetWidth() + size) * 0.5f, body->GetTransform().p.y + (p_Capsule->GetHeight() + size) * 0.5f,
                body->GetTransform().p.x + (p_Capsule->GetWidth() + size) * 0.5f, body->GetTransform().p.y + (p_Capsule->GetHeight() + size) * 0.5f
            };
            p_DebugRenderer->DrawRawShape(points, 5, Vector3(1.0f, 0.0f, 0.0f));
        }

        collisionData = Physics::GetAABBCollisionCallback()->GetAABBCollisionData();

        /* Goes through all of the fixtures and pushes them into a list */
        for (int j = 0; j < collisionData->m_Fixture.size(); j++)
        {
            /* Checks if the current fixture body is the same as the current body */
            if (collisionData->m_Fixture[j]->GetBody() != p_Body)
            {
                AddCloseObject(collisionData->m_Fixture[j]->GetBody());
            }
        }

        /* Goes through the particles */
        for (int j = 0; j < collisionData->m_ParticleIndexs.size(); j++)
        {
            /* Gets the positions of all the particles within the AABB */
                AddCloseParticle(Vector2(collisionData->m_ParticleIndexs[j]));
        }
        collisionData->m_ParticleIndexs.clear();
        

        //std::cout << "Close object count: " + std::to_string(GetCloseObjects().size()) << std::endl;
        //std::cout << "Close particle count: " + std::to_string(GetCloseParticles().size()) << std::endl;
        

        delete collisionData;
        return GetCloseObjects();
    }

    void Rigidbody2D::UpdateRigidbodyState()
    {
        if (GetCloseParticles().size() > 20)
        {
            if (GetCloseParticles().size() > 80)
            {
                SetRigidbodyState(RigidbodyState::Underwater);
            }
            else
            {
                SetRigidbodyState(RigidbodyState::Floating);
            }
        }
        else if (GetCollisionState() == CollisionState::None || GetCollisionState() == CollisionState::Exit)
        {
            if (p_Body->GetLinearVelocity().y > 0.0f)
            {
                SetRigidbodyState(RigidbodyState::Jumping);
            }
            else if (p_Body->GetLinearVelocity().y < -0.05f)
            {
                SetRigidbodyState(RigidbodyState::Falling);
            }
        }
        else
        {
            if (p_Body->GetLinearVelocity().x <= 0.2f && p_Body->GetLinearVelocity().x >= -0.2f && 
                p_Body->GetLinearVelocity().y <= 0.2f && p_Body->GetLinearVelocity().y >= -0.2f)
            {
                SetRigidbodyState(RigidbodyState::Idle);
            }
            else if (p_Body->GetLinearVelocity().x > 2.0f || p_Body->GetLinearVelocity().x < -2.0f)
            {
                SetRigidbodyState(RigidbodyState::Running);
            }
            else if (p_Body->GetLinearVelocity().x <= 2.0f && p_Body->GetLinearVelocity().x >= -2.0f)
            {
                SetRigidbodyState(RigidbodyState::Walking);
            }
        }
    }

    void Rigidbody2D::CollisionUpdate()
    {
        if (p_Box == nullptr && p_Circle == nullptr)
        {
            SetRigidbodyState(GetRigidbodyState());
            RaycastData* rightSideDown = KROSS_NEW RaycastData();
            RaycastData* leftSideDown = KROSS_NEW RaycastData();

            if (p_Capsule != nullptr)
            {
                delete rightSideDown;
                delete leftSideDown;

                rightSideDown = CalculateRayLength(0.15f, Vector2(0.0f, -1.0f), Vector2(p_Body->GetPosition().x + p_Capsule->GetWidth() * 0.5f, p_Body->GetPosition().y - 0.05f));
                leftSideDown = CalculateRayLength(0.15f, Vector2(0.0f, -1.0f), Vector2(p_Body->GetPosition().x - p_Capsule->GetWidth() * 0.5f, p_Body->GetPosition().y - 0.05f));

                m_BottomWheelRotation = m_Bodies[1]->GetTransform().q;
            }

            GetSurroundingObjects(0.065f, p_Body);
            UpdateRigidbodyState();

            if (rightSideDown->hit  || leftSideDown->hit)
            {
                /* Checks and sets the collision states for the rigidbody */
                if (GetCollisionState() == CollisionState::None || GetCollisionState() == CollisionState::Exit)
                {
                    SetCollisionState(CollisionState::Enter);
                }
                else if (GetCollisionState() == CollisionState::Enter)
                {
                    SetCollisionState(CollisionState::Stay);
                }

                p_DebugRenderer->SetColour(Vector3(1.0f, 0.0f, 0.0f));

                rightSideDown->hit = false;
                leftSideDown->hit = false;
            }
            else if (GetRigidbodyState() == RigidbodyState::Floating || GetRigidbodyState() == RigidbodyState::Underwater)
            {
                if (GetCollisionState() == CollisionState::None || GetCollisionState() == CollisionState::Exit)
                {
                    SetCollisionState(CollisionState::Enter);
                }
                else if (GetCollisionState() == CollisionState::Enter)
                {
                    SetCollisionState(CollisionState::Stay);
                }
            }
            else
            {
                if (p_Capsule != nullptr)
                {
                    rightSideDown->intersectionPoint = Vector2(p_Body->GetPosition().x + p_Capsule->GetWidth() * 0.5f, p_Body->GetPosition().y - 0.3f);
                    leftSideDown->intersectionPoint = Vector2(p_Body->GetPosition().x - p_Capsule->GetWidth() * 0.5f, p_Body->GetPosition().y - 0.3f);
                }
                /* Checks and sets the collision states for the rigidbody */
                if (GetCollisionState() == CollisionState::Enter || GetCollisionState() == CollisionState::Stay)
                {
                    SetCollisionState(CollisionState::Exit);
                }
                else if (GetCollisionState() == CollisionState::Exit)
                {
                    SetCollisionState(CollisionState::None);
                }

                p_DebugRenderer->SetColour(Vector3(0.0f, 0.0f, 1.0f));
            }

            /* Visulisation is broken, only displays one intersection point at a time */
            p_DebugRenderer->DrawLineSegment(rightSideDown->pos, rightSideDown->intersectionPoint);
            p_DebugRenderer->DrawCircle(rightSideDown->intersectionPoint, 0.1f, 8);
            
            p_DebugRenderer->DrawLineSegment(leftSideDown->pos, leftSideDown->intersectionPoint);
            p_DebugRenderer->DrawCircle(leftSideDown->intersectionPoint, 0.1f, 8);

            rightSideDown = nullptr;
            leftSideDown = nullptr;

            delete rightSideDown;
            delete leftSideDown;
        }

        #ifndef KROSS_EDITOR
        /* Gets the object position and updates it with the position of the body */
        m_GameObject->m_Transform->m_Position = Vector2(p_Body->GetPosition().x, p_Body->GetPosition().y);

        /* Gets the object rotation and updates it with the angle of the body */
        m_GameObject->m_Transform->m_Rotation = glm::degrees(p_Body->GetAngle());
        #else
        p_Body->SetTransform(Getb2Vec2(m_GameObject->m_Transform->m_Position), glm::radians(m_GameObject->m_Transform->m_Rotation));
        #endif

        ClearCloseObjects();
        ClearCloseParticles();
    }

    void Rigidbody2D::CreateTileMapColliders(TileMap* tileMap, Tile* tile, float friction)
    {
        std::vector<Vector4> tileColliders;
        std::vector<Vector3> tileCornerColliders;
        Vector2 tileDimensions = tile->GetSprite()->GetGeometry()->GetSize();
        float width = 0;
        float height = 0;

        float cuttOff = 0.1f;
        bool hasAirAbove = false;
        bool hasAirBelow = false;

        Vector2 objectPosition = m_GameObject->m_Transform->m_Position;
        
        Vector2 firstTile = Vector2(0,0);
        Vector2 previous = Vector2(-1.0f);
        int colliderCount = 0;
        std::vector<Vector2> colliderPositions;


        /* Rows */
        for (int y = 0; y < (int)tileMap->GetDimensions().y; y++)
        {
            for (int x = 0; x < (int)tileMap->GetDimensions().x; x++)
            {
                //get a full tile
                if (tileMap->GetCellValue(x, y) != -1)
                {
                    Vector2 tilePosition = Vector2(0.0f);
                    Vector2 offsetPosition = Vector2(0.0f);
                    offsetPosition.x = (tileDimensions.x) * x + tileDimensions.x / 2.0f;
                    offsetPosition.y = -((tileDimensions.y) * y) - tileDimensions.y / 2.0f;
                    
                    tilePosition = objectPosition + offsetPosition;
        
                    colliderPositions.push_back(tilePosition);
        
                  
                    if (y != 0 && y != tileMap->GetDimensions().y - 1)//Tile is required
                    {
                        if (tileMap->GetCellValue(x, y - 1) == -1)  //CELL HAS AIR
                        {
                            hasAirAbove = true;
                        }
                        if (tileMap->GetCellValue(x, y + 1) == -1)  //cell has air
                        {
                            hasAirBelow = true;
                        }

                    }
                    else
                    {
                        hasAirBelow = true;
                        hasAirAbove = true; 
                    }
                    
        
                    //Get to a tile that is on the next row
                    if (x == tileMap->GetDimensions().x - 1)
                    {
                        if (!colliderPositions.empty() && (hasAirAbove || hasAirBelow))
                        {
                            //Make a collision out of this list.
                            width = (colliderPositions[0].x + (tileDimensions.x * colliderPositions.size())) - colliderPositions[0].x;
                            tileColliders.push_back(Vector4(width - cuttOff, tileDimensions.y, (colliderPositions[0].x + (width * 0.5f)) - tileDimensions.x * 0.5f, colliderPositions[0].y));

                            if (hasAirAbove) 
                            {
                                tileCornerColliders.push_back(Vector3(colliderPositions[0].x - ((tileDimensions.x / 2.0f) - (cuttOff / 2.0f)), colliderPositions[0].y + ((tileDimensions.y / 2.0f) - (cuttOff / 2.0f)), cuttOff / 2.0f));

                                tileCornerColliders.push_back(Vector3(colliderPositions[colliderPositions.size() - 1].x + ((tileDimensions.x / 2.0f) - (cuttOff / 2.0f)), colliderPositions[0].y + ((tileDimensions.y / 2.0f) - (cuttOff / 2.0f)), cuttOff / 2.0f));
                            }
                            
                            if(hasAirBelow)
                            {
                                tileCornerColliders.push_back(Vector3(colliderPositions[0].x - ((tileDimensions.x / 2.0f) - (cuttOff / 2.0f)), colliderPositions[0].y - ((tileDimensions.y / 2.0f) - (cuttOff / 2.0f)), cuttOff / 2.0f));

                                tileCornerColliders.push_back(Vector3(colliderPositions[colliderPositions.size() - 1].x + ((tileDimensions.x / 2.0f) - (cuttOff / 2.0f)), colliderPositions[0].y - ((tileDimensions.y / 2.0f) - (cuttOff / 2.0f)), cuttOff / 2.0f));

                            }
                        }
                        colliderPositions.clear();
                        hasAirAbove = false;
                        hasAirBelow = false;
                    }
                }
                //Get to an empty tile
                else 
                {
                    if (!colliderPositions.empty() && (hasAirAbove || hasAirBelow)) 
                    {
                        //Make a collision out of this list.
                        width = (colliderPositions[0].x + (tileDimensions.x * colliderPositions.size())) - colliderPositions[0].x;
                        tileColliders.push_back(Vector4(width - cuttOff, tileDimensions.y, (colliderPositions[0].x + (width * 0.5f)) - tileDimensions.x * 0.5f, colliderPositions[0].y));

                        if (hasAirAbove)
                        {
                            tileCornerColliders.push_back(Vector3(colliderPositions[0].x - ((tileDimensions.x / 2.0f) - (cuttOff / 2.0f)), colliderPositions[0].y + ((tileDimensions.y / 2.0f) - (cuttOff / 2.0f)), cuttOff / 2.0f));
                            tileCornerColliders.push_back(Vector3(colliderPositions[colliderPositions.size() - 1].x + ((tileDimensions.x / 2.0f) - (cuttOff / 2.0f)), colliderPositions[0].y + ((tileDimensions.y / 2.0f) - (cuttOff / 2.0f)), cuttOff / 2.0f));
                        }

                        if (hasAirBelow)
                        {
                            tileCornerColliders.push_back(Vector3(colliderPositions[0].x - ((tileDimensions.x / 2.0f) - (cuttOff / 2.0f)), colliderPositions[0].y - ((tileDimensions.y / 2.0f) - (cuttOff / 2.0f)), cuttOff / 2.0f));
                            tileCornerColliders.push_back(Vector3(colliderPositions[colliderPositions.size() - 1].x + ((tileDimensions.x / 2.0f) - (cuttOff / 2.0f)), colliderPositions[0].y -  ((tileDimensions.y / 2.0f) - (cuttOff / 2.0f)), cuttOff / 2.0f));

                        }
                    }

                    colliderPositions.clear();
                    hasAirAbove = false;
                    hasAirBelow = false;
                }
            }
        }

        colliderPositions.clear();
        bool hasAir = false;

        ///* Collums, Collumbs */
        for (int x = 0; x < (int)tileMap->GetDimensions().x; x++)
        {
            for (int y = 0; y < (int)tileMap->GetDimensions().y; y++)
            {
                //get a full tile
                if (tileMap->GetCellValue(x, y) != -1)
                {
                    Vector2 tilePosition = Vector2(0.0f);
                    Vector2 offsetPosition = Vector2(0.0f);
                    offsetPosition.x = (tileDimensions.x) * x + tileDimensions.x / 2.0f;
                    offsetPosition.y = -((tileDimensions.y) * y) - tileDimensions.y / 2.0f;
        
                    tilePosition = objectPosition + offsetPosition;
        
                    colliderPositions.push_back(tilePosition);

                    if (!hasAir)
                    {
                        if (x != 0 && x != tileMap->GetDimensions().x - 1)//Tile is required
                        {
                            if (tileMap->GetCellValue(x - 1, y) == -1 || tileMap->GetCellValue(x + 1, y) == -1)  //CELL HAS AIR
                            {
                                hasAir = true;
                            }
                        }
                        else
                        {
                            hasAir = true;
                        }
                    }
        
                    //Get to a tile that is on the next row
                    if (y == tileMap->GetDimensions().y - 1)
                    {
                        if (!colliderPositions.empty() && hasAir)
                        {
                            //Make a collision out of this list.
                            height = (colliderPositions[0].y + (tileDimensions.y * colliderPositions.size())) - colliderPositions[0].y;
                            tileColliders.push_back(Vector4(tileDimensions.x, height - cuttOff, colliderPositions[0].x, (colliderPositions[0].y - (height * 0.5f)) + tileDimensions.y * 0.5f));
        
                            //tileColliders.push_back(Vector4(width - 0.05f, tileDimensions.y, (colliderPositions[0].x + (width * 0.5f)) - tileDimensions.x * 0.5f, colliderPositions[0].y));
                        }
                        colliderPositions.clear();
                        hasAir = false;
                    }
                }
                //Get to an empty tile
                else {
        
                    if (!colliderPositions.empty() && hasAir)
                    {
                        //Make a collision out of this list.
                        height = (colliderPositions[0].y + (tileDimensions.y * colliderPositions.size())) - colliderPositions[0].y;
                        tileColliders.push_back(Vector4(tileDimensions.x, height - cuttOff, colliderPositions[0].x, (colliderPositions[0].y - (height * 0.5f)) + tileDimensions.y * 0.5f));
        
                        //tileColliders.push_back(Vector4(width - 0.05f, tileDimensions.y, (colliderPositions[0].x + (width * 0.5f)) - tileDimensions.x * 0.5f, colliderPositions[0].y));
                    }
                    colliderPositions.clear();
                    hasAir = false;
                }
            }
        }


        for (int i = 0; i < tileColliders.size(); i++)
        {
            CreateWorldBox(Vector2(tileColliders[i].x, tileColliders[i].y), Vector2(tileColliders[i].z, tileColliders[i].w),
                GetColliderFilters(), friction);
        }

        for (int i = 0; i < tileCornerColliders.size(); i++)
        {
            CreateWorldCircle(tileCornerColliders[i].z, Vector2(tileCornerColliders[i].x, tileCornerColliders[i].y),
                GetColliderFilters(), friction);
        }
    }

    void Rigidbody2D::DeleteTileMapColliders()
    {
        for (int i = 0; i < m_TileColliders.size(); i++)
        {
            p_PhysicsScene->DetachBody(m_TileColliders[i]);
            m_TileColliders[i] = nullptr;
        }

        m_TileColliders.clear();

        for (int i = 0; i < m_TileCornerShapes.size(); i++)
        {
            delete m_TileCornerShapes[i];
            m_TileCornerShapes[i] = nullptr;
        }

        m_TileCornerShapes.clear();

        for (int i = 0; i < m_TileShapes.size(); i++)
        {
            delete m_TileShapes[i];
            m_TileShapes[i] = nullptr;
        }

        m_TileShapes.clear();
    }
}
