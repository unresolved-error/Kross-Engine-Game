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
        m_Projection = glm::ortho((-m_Size / 2.0f) * m_AspectRatio,( m_Size / 2.0f) * m_AspectRatio,
            (-m_Size / 2.0f),(m_Size / 2.0f), m_Near, m_Far);

        m_View = glm::translate(Matrix4(1.0f), Vector3(-m_GameObject->m_Transform->m_Position, 0.0f)) * glm::rotate(Matrix4(1.0f),
            glm::radians(m_GameObject->m_Transform->m_Rotation), Vector3(0.0f, 0.0f, -1.0f));
    }

    void Camera::OnUpdate()
    {
        /* Update the View and Projection Matrixes. */
        m_Projection = glm::ortho((-m_Size / 2.0f) * m_AspectRatio,( m_Size / 2.0f) * m_AspectRatio,
            (-m_Size / 2.0f),(m_Size / 2.0f), m_Near, m_Far);

        m_View = glm::translate(Matrix4(1.0f), Vector3(-m_GameObject->m_Transform->m_Position, 0.0f)) * glm::rotate(Matrix4(1.0f),
            glm::radians(m_GameObject->m_Transform->m_Rotation), Vector3(0.0f, 0.0f, -1.0f));
    }
}