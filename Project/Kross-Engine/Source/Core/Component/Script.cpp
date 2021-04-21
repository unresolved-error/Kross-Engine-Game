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

        /* Call Base Component Function. */
        Component::OnStart();
    }

    void Script::OnUpdate()
    {
        /* Call Update Method. */
        Update();

        /* Call Base Component Function. */
        Component::OnUpdate();
    }

    void Script::OnCollisionEnter()
    {
        /* Call Collision Enter Method. */
        CollisionEnter();

        /* Call Base Component Function. */
        Component::OnCollisionEnter();
    }

    void Script::OnCollisionStay()
    {
        /* Call Collision Stay Method. */
        CollisionStay();

        /* Call Base Component Function. */
        Component::OnCollisionStay();
    }

    void Script::OnCollisionExit()
    {
        /* Call Collision Exit Method. */
        CollisionExit();

        /* Call Base Component Function. */
        Component::OnCollisionExit();
    }
}