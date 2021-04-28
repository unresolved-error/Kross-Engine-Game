/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

/* --------- INFORMATION --------- */
/*
 * THIS IS TO WRAP COMPONENTS THAT RENDER THINGS!
 */
/* ------------------------------- */
#pragma once

#include "../Core.h"

#include "Component.h"

namespace Kross
{
    class KROSS_API Renderer : public Component
    {
    private:
        int m_Depth;

    protected:

    public:
        Renderer()
            : m_Depth(0)
        {};
        ~Renderer() {};

        // Sets the Depth.
        void SetDepth(int depth) { m_Depth = depth; };

        // Gets the Depth.
        const int GetDepth() const { return m_Depth; };
    };
}

#include "SpriteRenderer.h"
#include "TextRenderer.h"