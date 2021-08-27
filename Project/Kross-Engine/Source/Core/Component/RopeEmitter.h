/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch
 */
#pragma once

#include "../Core.h"

#include "Renderer.h"
#include "../Renderer/Shader/Shader.h"
#include "../Manager/ResourceManager.h"

#include "../Physics/Rope/Rope.h"

namespace Kross
{
    class KROSS_API RopeEmitter : public Renderer
    {
    private:
        friend class PhyscisScene; ////LOL WE NEVER NOTICED.
        PhysicsScene* p_PhysicsScene;
        Rope* p_Rope;

    protected:

        /* RopeEmitter start method */
        void OnStart() override;

    public:

        RopeEmitter() :
            p_PhysicsScene(nullptr),
            p_Rope(nullptr)
        {}
        ~RopeEmitter();



        /* Sets the physics scene */
        void SetPhysicsScene(PhysicsScene* physicsScene) { p_PhysicsScene = physicsScene; }
        PhysicsScene* GetPhysicsScene() { return p_PhysicsScene; }



    };
}