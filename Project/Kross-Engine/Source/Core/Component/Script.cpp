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

    void Script::OnCollisionEnter(Object* other)
    {
        /* Call Collision Enter Method. */
        CollisionEnter(other);
    }

    void Script::OnCollisionStay(Object* other)
    {
        /* Call Collision Stay Method. */
        CollisionStay(other);
    }

    void Script::OnCollisionExit(Object* other)
    {
        /* Call Collision Exit Method. */
        CollisionExit(other);
    }
}