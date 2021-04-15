/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Camera.h"

#include "../Application.h"

namespace Kross
{
    void Camera::OnStart()
    {
        /* Update the View and Projection Matrixes. */
        m_Projection = glm::ortho(-m_Size, m_Size, -m_Size / m_AspectRatio, m_Size / m_AspectRatio, m_Near, m_Far);
        m_View = glm::translate(Matrix4(1.0f), Vector3(-GetObject()->GetTransform()->m_Position, 0.0f));

        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Start the Next Component. */
        if (nextComponent)
            nextComponent->OnStart();

        return;
    }

    void Camera::OnUpdate()
    {
        /* Update the View and Projection Matrixes. */
        m_Projection = glm::ortho(-m_Size, m_Size, -m_Size / 2.0f, m_Size / 2.0f, m_Near, m_Far);
        m_View = glm::translate(Matrix4(1.0f), Vector3(-GetObject()->GetTransform()->m_Position, 0.0f));

        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Update the Next Component. */
        if (nextComponent)
            nextComponent->OnUpdate();

        return;
    }

    void Camera::OnCollisionEnter()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Enter the Next Component. */
        if (nextComponent)
            nextComponent->OnCollisionEnter();

        return;
    }

    void Camera::OnCollisionStay()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Enter the Next Component. */
        if (nextComponent)
            nextComponent->OnCollisionStay();

        return;
    }

    void Camera::OnCollisionExit()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Enter the Next Component. */
        if (nextComponent)
            nextComponent->OnCollisionExit();

        return;
    }

    void Camera::OnRender()
    {
        /* Get the Next Component. */
        Component* nextComponent = GetNextComponent();

        /* Render the Next Component. */
        if (nextComponent)
            nextComponent->OnRender();

        return;
    }
}