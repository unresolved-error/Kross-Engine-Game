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

        virtual void Start() {};
        virtual void Update() {};
        virtual void CollisionEnter(Object* other) {};
        virtual void CollisionStay(Object* other) {};
        virtual void CollisionExit(Object* other) {};

    };
}