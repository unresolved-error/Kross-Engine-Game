/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "UITransform.h"

#include "../Manager/SceneManager.h"

namespace Kross
{
	UITransform::UITransform() :
		m_Offset(Vector2(0.0f))
	{}

	UITransform::~UITransform()
	{}

	const Vector2 UITransform::GetOffset() const
	{
		return m_Offset;
	}

	void UITransform::SetOffset(Vector2 offset)
	{
		m_Offset = offset;
	}

	void UITransform::OnUpdate()
	{
		Vector2 cameraPosition = SceneManager::GetCurrentScene()->GetCamera()->m_Transform->m_Position;
		m_GameObject->m_Transform->m_Position = cameraPosition + m_Offset;
	}
}