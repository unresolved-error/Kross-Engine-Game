/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *		- Deklyn Palmer.
 */

#include "RopeEmitter.h"

namespace Kross
{
    void RopeEmitter::OnStart()
    {
        RopeProperties* properties = GetComponent<RopeProperties>();

        p_Rope = KROSS_NEW Rope();
        p_Rope->SetPhysicsScene(p_PhysicsScene);
        p_Rope->SpawnRope(properties);

    }
}