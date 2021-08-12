/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 *      - Deklyn Palmer.
 */
#pragma once

#include "../Core.h"

#include "Renderer.h"
#include "../Renderer/Shader/Shader.h"
#include "../Manager/ResourceManager.h"

#include "../Physics/Particles/Particle.h"

namespace Kross
{
    struct KROSS_API Metaball
    {
        Vector4 m_Colour;
        Vector2 m_Position;
        float m_Radius;
    };

    class KROSS_API ParticleEmitter : public Renderer
    {
    private:
        friend class PhyscisScene;
        friend class Particle;

        PhysicsScene* p_PhysicsScene;
        ParticleSystem* p_ParticleSystem;
        Particle* p_Particle;

    protected:

        /* ParticleEmitter start method */
        void OnStart() override;

    public:

        ParticleEmitter() :
            p_PhysicsScene      (nullptr),
            p_ParticleSystem    (nullptr),
            p_Particle          (nullptr)
        {}
        ~ParticleEmitter();

        /* Sets the physics scene */
        void SetPhysicsScene(PhysicsScene* physicsScene) { p_PhysicsScene = physicsScene; }
        PhysicsScene* GetPhysicsScene() { return p_PhysicsScene; }

        /* Returns the particle system */
        ParticleSystem* GetParticleSystem() { return p_ParticleSystem; }

        /* Creates the particle */
        void SpawnParticle(ParticleDef particleDef);
        void SpawnParticle(ParticleGroupDef particleDef);
        
    };
}