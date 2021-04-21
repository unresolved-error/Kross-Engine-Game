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
        void OnCollisionEnter() override;

        // Script Collision Stay Method.
        void OnCollisionStay() override;

        // Script Collision Exit Method.
        void OnCollisionExit() override;

    public:
        Script() {};
        ~Script() {};

        virtual void Start() {};
        virtual void Update() {};
        virtual void CollisionEnter() {};
        virtual void CollisionStay() {};
        virtual void CollisionExit() {};

    };
}