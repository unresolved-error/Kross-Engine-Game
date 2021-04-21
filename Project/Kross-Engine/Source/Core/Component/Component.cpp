
#include "Component.h"

namespace Kross
{
	void Component::OnStart()
	{
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Start the Next Component. */
        if (nextComponent)
            nextComponent->OnStart();

        return;
	}

    void Component::OnUpdate()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Update the Next Component. */
        if (nextComponent)
            nextComponent->OnUpdate();

        return;
    }

    void Component::OnCollisionEnter()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Go into the Next Component. */
        if (nextComponent)
            nextComponent->OnCollisionEnter();

        return;
    }

    void Component::OnCollisionStay()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Go into the Next Component. */
        if (nextComponent)
            nextComponent->OnCollisionStay();

        return;
    }

    void Component::OnCollisionExit()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Go into the Next Component. */
        if (nextComponent)
            nextComponent->OnCollisionExit();

        return;
    }

    void Component::OnRender()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Render the Next Component. */
        if (nextComponent)
            nextComponent->OnRender();

        return;
    }
}