/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Component.h"
#include "../Math/Math.h"

namespace Kross
{
	class KROSS_API UITransform : public Component
	{
	private:
		Vector2 m_Offset;

	protected:
		/*!
			Update Method.
		*/
		void OnUpdate() override;

	public:
		UITransform();
		~UITransform();

		/*!
			Get's the Offset from the Main Camera.
		*/
		const Vector2 GetOffset() const;

		/*!
			Set's the Offset from the Main Camera.
		*/
		void SetOffset(Vector2 offset);
	};
}