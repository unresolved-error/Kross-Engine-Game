/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *      - Deklyn Palmer.
 */
#pragma once

#include "../Core.h"

#include "Renderer.h"
#include "../Renderer/LineRenderer.h"

namespace Kross
{
    class KROSS_API Rope;

    class KROSS_API RopeEmitter : public Renderer
    {
    private:
        PhysicsScene* p_PhysicsScene;
        Rope* p_Rope;

        LineRenderer* m_DebugRenderer;

    protected:
        friend class Object;

        /* RopeEmitter start method */
        void OnStart() override;

        /*!
            Rope Emitter Update Method. 
        */
        void OnUpdate() override;

        /* Sets the physics scene */
        void SetPhysicsScene(PhysicsScene* physicsScene) { p_PhysicsScene = physicsScene; };

        /*!
            Sends Draw Information to the Line Renderer.
        */
        void OnUpdateDrawInformation();

        /*!
            Sets the Line Renderer.
        */
        void SetDebugLineRenderer(LineRenderer* renderer) { m_DebugRenderer = renderer; };

    public:

        RopeEmitter() :
            p_PhysicsScene      (nullptr),
            p_Rope              (nullptr),
            m_DebugRenderer     (nullptr)
        {}
        ~RopeEmitter();

        PhysicsScene* GetPhysicsScene() { return p_PhysicsScene; }
    };
}