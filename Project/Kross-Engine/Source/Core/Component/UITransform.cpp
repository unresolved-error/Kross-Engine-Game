/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "UITransform.h"

#include "../Manager/SceneManager.h"
#include "../Application.h"

namespace Kross
{
	UITransform::UITransform() :
		m_Ratio(Vector2(0.0f))
	{}

	UITransform::~UITransform()
	{}

	const Vector2 UITransform::GetRatio() const
	{
		return m_Ratio;
	}

	void UITransform::SetRatio(Vector2 offset)
	{
		m_Ratio = offset;
	}

	void UITransform::OnUpdate()
	{
		Window* window = Application::GetWindow();
		Camera* camera = SceneManager::GetCurrentScene()->GetCamera()->GetComponent<Camera>();

		float aspectRatio = window->GetApsectRatio();
		float screenPixelPositionWidth = m_Ratio.x * window->GetWidth();
		float screenPixelPositionHeight = m_Ratio.y * window->GetHeight();

		Vector2 screenPosition = Vector2(((screenPixelPositionWidth / window->GetWidth()) * 1.0f - 0.5f) * aspectRatio, -(((screenPixelPositionHeight / window->GetHeight()) * 1.0f) - 0.5f)) * camera->GetSize();
		Vector2 cameraPosition = camera->m_GameObject->m_Transform->m_Position;

		m_GameObject->m_Transform->m_Position = cameraPosition + screenPosition;
	}
}