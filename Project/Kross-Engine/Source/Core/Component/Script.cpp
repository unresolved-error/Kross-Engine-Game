/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Script.h"

namespace Kross
{
    void Script::OnStart()
    {
        /* Call Start Method. */
        Start();
    }

    void Script::OnUpdate()
    {
        /* Call Update Method. */
        Update();
    }

    void Script::OnCollisionEnter()
    {
        /* Call Collision Enter Method. */
        CollisionEnter();
    }

    void Script::OnCollisionStay()
    {
        /* Call Collision Stay Method. */
        CollisionStay();
    }

    void Script::OnCollisionExit()
    {
        /* Call Collision Exit Method. */
        CollisionExit();
    }
}