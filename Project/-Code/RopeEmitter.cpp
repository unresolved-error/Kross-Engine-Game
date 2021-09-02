/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *		- Deklyn Palmer.
 */

#include "RopeEmitter.h"

#include "../Physics/Rope/Rope.h"

namespace Kross
{
    void RopeEmitter::OnStart()
    {
        RopeProperties* properties = GetComponent<RopeProperties>();

        p_Rope = KROSS_NEW Rope();
        p_Rope->SetPhysicsScene(p_PhysicsScene);
        p_Rope->SpawnRope(properties);

    }

    void RopeEmitter::OnUpdate()
    {
        #ifdef KROSS_DEBUG
        OnUpdateDrawInformation();
        #endif
    }

    void RopeEmitter::OnUpdateDrawInformation()
    {
        /* If we have a rope to begin with. */
        if (p_Rope)
        {
            for(int i = 0; i < p_Rope->segments.size(); i++)
            {
                m_DebugRenderer->DrawRigidBody(p_Rope->segments[i]);
            }
        }
    }
}