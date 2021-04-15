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

        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Start the Next Component. */
        if (nextComponent)
            nextComponent->OnStart();

        return;
    }

    void Script::OnUpdate()
    {
        /* Call Update Method. */
        Update();

        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Update the Next Component. */
        if (nextComponent)
            nextComponent->OnUpdate();

        return;
    }

    void Script::OnCollisionEnter()
    {
        /* Call Collision Enter Method. */
        CollisionEnter();

        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Enter the Next Component. */
        if (nextComponent)
            nextComponent->OnCollisionEnter();

        return;
    }

    void Script::OnCollisionStay()
    {
        /* Call Collision Stay Method. */
        CollisionStay();

        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Enter the Next Component. */
        if (nextComponent)
            nextComponent->OnCollisionStay();

        return;
    }

    void Script::OnCollisionExit()
    {
        /* Call Collision Exit Method. */
        CollisionExit();

        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Enter the Next Component. */
        if (nextComponent)
            nextComponent->OnCollisionExit();

        return;
    }

    void Script::OnRender()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Render the Next Component. */
        if (nextComponent)
            nextComponent->OnRender();

        return;
    }
}