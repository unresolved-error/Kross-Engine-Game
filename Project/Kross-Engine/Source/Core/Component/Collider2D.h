/*
 *  Author: Jake Warren.
 *  Editors:
 *		- Jake Warren.
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Rigidbody2D.h"

namespace Kross
{
    class KROSS_API Collider2D : public Component
    {
    private:

    protected:
        void OnStart() override;

        void OnRender() override;

    public:
        Collider2D() {}
        ~Collider2D() {}
    };
}