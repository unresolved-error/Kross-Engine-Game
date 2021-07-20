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
        #ifndef KROSS_EDITOR

        /* Call Update Method. */
        Update();
        #endif
    }

    void Script::OnCollisionEnter(Object* other)
    {
        #ifndef KROSS_EDITOR

        /* Call Collision Enter Method. */
        CollisionEnter(other);
        #endif
    }

    void Script::OnCollisionStay(Object* other)
    {
        #ifndef KROSS_EDITOR

        /* Call Collision Stay Method. */
        CollisionStay(other);
        #endif
    }

    void Script::OnCollisionExit(Object* other)
    {
        #ifndef KROSS_EDITOR

        /* Call Collision Exit Method. */
        CollisionExit(other);
        #endif
    }
}