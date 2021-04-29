/*
 *  Author: Jake Warren.
 *  Editors:
 *      - Jake Warren.
 */
#pragma once

#include "../Core.h"

#include "Component.h"
#include "../Physics/Physics.h"
#include "../Physics/PhysicsScene.h"
#include "../Physics/Particles/Particle.h"
#include "../Manager/ResourceManager.h"
#include "../Renderer/Shader/Shader.h"
#include "../Renderer/LineRenderer.h"

namespace Kross
{

    class KROSS_API ParticleEmitter : public Component
    {
    private:
        ParticleSystemDef m_ParticleSystemDef;
        ParticleSystem* p_ParticleSystem;
        Particle* p_Particle;
        PhysicsScene* p_PhysicsScene;
        World* p_World;
        LineRenderer* p_Lines;
        Shader* p_DebugShader;


    protected:
        void OnStart() override;

        void OnUpdate() override;

        void OnRender() override;
    public:

        ParticleEmitter() : m_ParticleSystemDef(ParticleSystemDef()), p_ParticleSystem(nullptr), p_World(nullptr), p_Particle(new Particle()), p_Lines(new LineRenderer()) {};
        ~ParticleEmitter();

        void OnCreateParticleSystem();

        void OnCreateParticle();

        Particle* GetParticle() { return p_Particle; }

        /* Only set when safe */
        void SetRadius(float radius) { p_ParticleSystem->SetRadius(radius); }
        float GetRadius() { return p_ParticleSystem->GetRadius(); }

        void SetDensity(float density) { p_ParticleSystem->SetDensity(density); }
        float GetDensity() { return p_ParticleSystem->GetDensity(); }

        void SetMaxCount(int max) { p_ParticleSystem->SetMaxParticleCount(max); }
        float GetMaxCount() { return p_ParticleSystem->GetMaxParticleCount(); }

        void SetLifetime(int index, float lifetime) { p_ParticleSystem->SetParticleLifetime(index, lifetime); }
        float GetLifetime(int index) { return p_ParticleSystem->GetParticleLifetime(index); }

        void SetDestroyByAge(bool destroy) { p_ParticleSystem->SetDestructionByAge(destroy); }
        bool GetDestroyByAge() { return p_ParticleSystem->GetDestructionByAge(); }

        void SetStrictContactCheck(bool contact) { p_ParticleSystem->SetStrictContactCheck(contact); }
        bool GetStrictContactCheck() { return p_ParticleSystem->GetStrictContactCheck(); }

        void SetPaused(bool paused) { p_ParticleSystem->SetPaused(paused); }
        bool GetPaused() { return p_ParticleSystem->GetPaused(); }

        void SetGravityScale(float scale) { p_ParticleSystem->SetGravityScale(scale); }
        float GetGravityScale() { return p_ParticleSystem->GetGravityScale(); }

        void SetParticleFlags(int index, ParticleFlag flags) { p_ParticleSystem->SetParticleFlags(index, flags); }
        int GetParticleFlags(int index) { return p_ParticleSystem->GetParticleFlags(index); }

        void SetStuckThreshold(int iterations) { p_ParticleSystem->SetStuckThreshold(iterations); }
        const int32* GetStuckCandidates() {return p_ParticleSystem->GetStuckCandidates(); }


        void SetPhysicsScene(PhysicsScene* physicsScene) { p_PhysicsScene = physicsScene; }
        
    };
}