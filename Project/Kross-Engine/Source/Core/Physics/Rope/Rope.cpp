/*
 *  Author: Chris Deitch
 *  Editors:
 *      - Chris Deitch
 *      - Jake Warren
 */
#include "Rope.h"
#include "../../Math/Math.h"

namespace Kross
{


    Rope* Rope::CreateRope(RopeProperties* properties, PhysicsScene* physicsScene)
    {

        Rope* newRope= KROSS_NEW Rope();
        newRope->SetPhysicsScene(physicsScene);
        //startConnection = KROSS_NEW b2Body() ... ect; position of postitionsToSet[0]
        //endConnection = KROSS_NEW b2Body() ... ect; position of   positionsToSet[positionsToSet.size - 1]

        
        ///1: Take the list of positions and the Size of chain segments
        for (int i = 0; i < properties->GetPositions().size() - 1; i++) 
        {
            Vector2 firstPos = properties->GetPositions()[i];
            Vector2 secondPos = properties->GetPositions()[i+1];

            float distanceX = firstPos.x - secondPos.x;
            float distanceY = firstPos.y - secondPos.y;

            float totalXYDist = glm::sqrt(glm::abs(distanceX*distanceX) + glm::abs(distanceY*distanceY));
            int numberOfLinks = (int)fmod(totalXYDist, properties->GetLinkSize());

            
            ///2: Generate a list of b2Bodies that are the links in the rope.
            for (int j = 0; j < numberOfLinks - 1; j++)
            {
                Vector2 positionOfNewBody = Math::Lerp(firstPos, secondPos, j * (1.0f / numberOfLinks - 1));
                //Create a new body.
                BodyDef bodyDef;
                bodyDef.type = b2_dynamicBody;
                bodyDef.position.Set(positionOfNewBody.x, positionOfNewBody.y);
                Body* body = newRope->GetPhysicsScene()->GetPhysicsWorld()->CreateBody(&bodyDef);
                CircleShape circular;
                circular.m_radius = (properties->GetLinkSize() * 0.5f);
                FixtureDef fixDef;
                fixDef.shape = &circular;
                fixDef.filter.categoryBits = properties->filterBits.categoryBits;
                fixDef.filter.maskBits = properties->filterBits.maskBits;

                body->CreateFixture(&fixDef);
                physicsScene->AttachBody(body);
                newRope->segments.push_back(body);

            }
        }



        ///3: Generate a list of b2Revolute Joints that are between each join in the chain. (each joint requires body "A" and body "B")
        for (int i =0; i <= newRope->segments.size()-2; i++)
        {
            //create a revolute joint between j and j+1;
            b2RevoluteJointDef* revJointDef = KROSS_NEW b2RevoluteJointDef();
            revJointDef->bodyA = newRope->segments[i];
            revJointDef->bodyB = newRope->segments[i+1];
            revJointDef->localAnchorA = Getb2Vec2(Vector2(0,1));
            revJointDef->localAnchorB = Getb2Vec2(Vector2(0,-1));
            newRope->joinsBetweenSegments.push_back(
                (b2RevoluteJoint*)newRope->p_PhysicsScene->GetPhysicsWorld()->CreateJoint(revJointDef)
            );
          
              
        }

        ///4: Generate 2 end point b2Weld joints for the connection to the object hanging from this rope and the roof or whatever its attached too.


        return newRope;
    }


}