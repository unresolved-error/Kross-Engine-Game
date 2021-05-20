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
        friend class Scene;

        // Camera Start Method.
        void OnStart() override;

        // Camera Update Method.
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
        Camera() : 
            m_Size          (2.0f),
            m_Near          (-1.0f),
            m_Far           (1.0f), 
            m_AspectRatio   (16.0f / 9.0f),
            m_Projection    (Matrix4(1.0f)),
            m_View          (Matrix4(1.0f))
        {};
        ~Camera() {};

        // Sets the Size of the Camera.
        void SetSize(float value) { m_Size = value; };

        // Sets the Near Plane.
        void SetNear(float value) { m_Near = value; };

        // Sets the Far Plane.
        void SetFar(float value) { m_Far = value; };

        // Gets the Size of the Camera.
        float GetSize() const { return m_Size; };

        // Gets the Near Plane.
        float GetNear() const { return m_Near; };

        // Gets the Far Plane.
        float GetFar() const { return m_Far; };
    };
}