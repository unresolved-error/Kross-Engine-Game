/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#pragma once

#include "../../Core.h"

#include "../../Math/Math.h"
#include "../PhysicsScene.h"

#include "../../Component/RopeProperties.h"

namespace Kross
{
    class KROSS_API Rope
    {
    protected:
        friend class RopeEmitter;

        PhysicsScene* p_PhysicsScene;
        std::vector<b2Body*> segments;
        std::vector<b2RevoluteJoint*> joinsBetweenSegments;
        b2Body* objectTheStartIsConnectedTo = nullptr;
        b2Body* startConnection = nullptr;
        bool startIsStatic = false;
        b2WeldJoint* startJoin = nullptr;
        b2Body* objectTheEndIsConnectedTo = nullptr;
        b2Body* endConnection = nullptr;
        b2WeldJoint* endJoin = nullptr;

    public:
        /* The group bool is to determine where values need to be assigned */
        Rope() :
            p_PhysicsScene(nullptr)
        {};
        ~Rope() {};

        void SetPhysicsScene(PhysicsScene* physicsScene) { p_PhysicsScene = physicsScene; }
        PhysicsScene* GetPhysicsScene() { return p_PhysicsScene; }

        /*!
            Spawns a Rope to neck myself with.
        */
        void SpawnRope(RopeProperties* properties);
        
        void WeldStartToObject(b2Body* bodyToConnectTo) { objectTheStartIsConnectedTo = bodyToConnectTo; };
        void WeldEndToObject(b2Body* bodyToConnectTo) { objectTheEndIsConnectedTo = bodyToConnectTo; };


        void DeleteSegment(b2Body* segmentToDelete) {  };
        void AttachStartPoint();
        void AttachEndPoint();
        void SetStartPointStatic();


    };
}