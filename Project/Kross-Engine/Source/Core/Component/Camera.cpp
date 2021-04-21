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

        /* Call Base Component Function. */
        Component::OnStart();
    }

    void Camera::OnUpdate()
    {
        /* Update the View and Projection Matrixes. */
        m_Projection = glm::ortho(-m_Size, m_Size, -m_Size / 2.0f, m_Size / 2.0f, m_Near, m_Far);
        m_View = glm::translate(Matrix4(1.0f), Vector3(-GetObject()->GetTransform()->m_Position, 0.0f));

        /* Call Base Component Function. */
        Component::OnUpdate();
    }
}