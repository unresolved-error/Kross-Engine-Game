/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Component.h"

namespace Kross
{
    class KROSS_API Camera : public Component
    {
    private:
        float m_Size, m_Near, m_Far, m_AspectRatio;

        Matrix4 m_Projection;
        Matrix4 m_View;

    protected:
        /*!
            Gives Scene access to all Protected and Private areas of the class.
        */
        friend class Scene;

        /*!
            Camera's Start Method.
        */
        void OnStart() override;

        /*!
            Camera's Update Method.
        */
        void OnUpdate() override;

        // Sets the Camera Aspect Ratio.
        void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; };

        // Gets the Camera Aspect Ratio.
        const float GetAspectRatio() const { return m_AspectRatio; };

        // Gets the Cameras Projection.
        const Matrix4 GetProjection() const { return m_Projection; };

        // Get the Cameras View.
        const Matrix4 GetView() const { return m_View; };

    public:
        /*!
            Camera's Constructor.
        */
        Camera() : 
            m_Size          (2.0f),
            m_Near          (-1.0f),
            m_Far           (1.0f), 
            m_AspectRatio   (16.0f / 9.0f),
            m_Projection    (Matrix4(1.0f)),
            m_View          (Matrix4(1.0f))
        {};
        /*!
            Camera's Destructor.
        */
        ~Camera() {};

        /*!
            Sets the Size of the Camera.
        */
        void SetSize(float value)
        {
            /* If the Value is Less than or Equal to Zero. */
            if (value < 0.0f)
                value = 0.0001f; /* Make One Ten Thousandth. */

            /* Set Size. */
            m_Size = value;
        }

        // Sets the Near Plane.
        void SetNear(float value) { m_Near = (value == m_Far || value > m_Far) ? m_Far - 0.0001f : value; };

        // Sets the Far Plane.
        void SetFar(float value) { m_Far = (value == m_Near || value < m_Near) ? m_Near + 0.0001f : value; };

        // Gets the Size of the Camera.
        float GetSize() const { return m_Size; };

        // Gets the Near Plane.
        float GetNear() const { return m_Near; };

        // Gets the Far Plane.
        float GetFar() const { return m_Far; };
    };
}