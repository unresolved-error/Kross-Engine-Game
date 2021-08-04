/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Component.h"


namespace Kross
{
    class KROSS_API Script : public Component
    {
    private:

    protected:
        std::string m_Name;

        // Script Start Method.
        void OnStart() override;

        // Script Update Method.
        void OnUpdate() override;

        // Script Collision Enter Method.
        void OnCollisionEnter(Object* other) override;

        // Script Collision Stay Method.
        void OnCollisionStay(Object* other) override;

        // Script Collision Exit Method.
        void OnCollisionExit(Object* other) override;

    public:
        Script() {};
        ~Script() {};

        /* Use Wisely. */
        virtual Script* Duplicate() { return KROSS_NEW Script(); };

        virtual void Start() { Debug::LogLine((std::string)"Base Start!"); };
        virtual void Update() {};
        virtual void CollisionEnter(Object* other) {};
        virtual void CollisionStay(Object* other) {};
        virtual void CollisionExit(Object* other) {};

        std::string GetName() const { return m_Name; };

    };
}